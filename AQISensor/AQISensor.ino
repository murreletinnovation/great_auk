#include <bsec.h>
#include <MQTTClient.h>
#include <WiFiClientSecure.h>
#include "WiFi.h"
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "certs.h"

const char *SSID = "TacoCorp";
const char *WiFiPassword = "albertross";

// The name of the device. This MUST match up with the name defined in the AWS console
#define DEVICE_NAME "AQISensor00"

// The MQTTT endpoint for the device (unique for each AWS account but shared amongst devices within the account)
#define AWS_IOT_ENDPOINT "a2rft9avt13x3b-ats.iot.us-west-2.amazonaws.com"

// The MQTT topic that this device should publish to
#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"

// How many times we should attempt to connect to AWS
#define AWS_MAX_RECONNECT_TRIES 50

Bsec iaqSensor;
MQTTClient client = MQTTClient(256);

WiFiClientSecure net = WiFiClientSecure();

  bsec_virtual_sensor_t sensorList[7] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
  };

void connectToWiFi()
{
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
}

void connectToAWS()
{
  // Configure WiFiClientSecure to use the AWS certificates we generated
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Try to connect to AWS and count how many times we retried.
  int retries = 0;
  Serial.println("Connecting to AWS IOT");

  while (!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES) {
    Serial.print(".");
    delay(100);
    retries++;
  }

  // Make sure that we did indeed successfully connect to the MQTT broker
  // If not we just end the function and wait for the next loop.
  if(!client.connected()){
    Serial.println(" Timeout!");
    return;
  }

  // If we land here, we have successfully connected to AWS!
  // And we can subscribe to topics and send messages.
  Serial.println("Connected!");
}

void sendJsonToAWS(float temp, float humidity, float iaq)
{
  StaticJsonDocument<512> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");
  
  reportedObj["temperature"] = temp;
  reportedObj["humidity"] = humidity;
  reportedObj["iaq"] = iaq;
  
  // Create a nested object "location"
  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["name"] = "Murrelet";

  Serial.println("Publishing message to AWS...");
  char jsonBuffer[512];
  serializeJson(jsonDoc, jsonBuffer);

  client.publish(AWS_IOT_TOPIC, jsonBuffer);
}

// Helper function definitions
void checkIaqSensorStatus(void)
{
  String output;
  
  if (iaqSensor.status != BSEC_OK) {
    if (iaqSensor.status < BSEC_OK) {
      output = "BSEC error code : " + String(iaqSensor.status);
      Serial.println(output);
      while(1);
    } else {
      output = "BSEC warning code : " + String(iaqSensor.status);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme680Status != BME680_OK) {
    if (iaqSensor.bme680Status < BME680_OK) {
      output = "BME680 error code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
      while(1);
    } else {
      output = "BME680 warning code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
    }
  }
}

void setup() 
{
  String output;
  
  Serial.begin(115200);
  Wire.begin();
  
  iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  checkIaqSensorStatus();
  iaqSensor.updateSubscription(sensorList, 7, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();

  connectToWiFi();
  connectToAWS();

  output = "Timestamp [ms], raw temperature [°C], pressure [hPa], raw relative humidity [%], gas [Ohm], IAQ, static IAQ, CO2 equivalent";
  Serial.println(output); 
}

void loop() 
{
  unsigned long time_trigger = millis();
  if (iaqSensor.run()) 
  {
    sendJsonToAWS(iaqSensor.rawTemperature, iaqSensor.rawHumidity, iaqSensor.iaq);
    client.loop();
  } else {
    checkIaqSensorStatus();
  }
}
