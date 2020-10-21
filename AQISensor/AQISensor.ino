#include <bsec.h>
#include <MQTTClient.h>
#include <WiFiClientSecure.h>
#include "WiFi.h"
#include <ArduinoJson.h>
#include "certs.h"
#include <SD.h>
#include "FS.h"
#include "RTClib.h"

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

RTC_PCF8523 rtc;

WiFiClientSecure net = WiFiClientSecure();

bsec_virtual_sensor_t sensorList[7] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
};

const int chipSelect = 33;
String logFilename;
File logFile;

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
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
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

void sendJsonToAWS(uint32_t timestamp, float temperature, float humidity, float iaq, float co2)
{
  StaticJsonDocument<512> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");

  reportedObj["timestamp"] = timestamp;
  reportedObj["temperature"] = temperature;
  reportedObj["humidity"] = humidity;
  reportedObj["iaq"] = iaq;
  reportedObj["co2"] = co2;
  
  // Create a nested object "location"
  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["name"] = "Murrelet_HQ";

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
    } else {
      output = "BSEC warning code : " + String(iaqSensor.status);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme680Status != BME680_OK) {
    if (iaqSensor.bme680Status < BME680_OK) {
      output = "BME680 error code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
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
  Wire.begin();\
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
    abort();
  }
  
  iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  checkIaqSensorStatus();
  iaqSensor.updateSubscription(sensorList, 4, BSEC_SAMPLE_RATE_ULP);
  checkIaqSensorStatus();

  connectToWiFi();
  connectToAWS();
  
  DateTime now = rtc.now();
  String epochString = String(now.unixtime());
  
  logFilename = "/log_" + epochString + ".csv";
  logFile = SD.open(logFilename, FILE_WRITE);
  output = "timestamp,raw_temperature,raw_relative_humidity,iaq,co2_equivalent";
  logFile.println(output);
  logFile.close();

  rtc.start();
}

void loop() 
{
  String output;
  uint32_t unix_timestamp;
  
  DateTime now = rtc.now();
  if (iaqSensor.run()) 
  {
    unix_timestamp = now.unixtime();
    logFile = SD.open(logFilename, FILE_APPEND);
    output = String(unix_timestamp) + "," + iaqSensor.rawTemperature + "," + iaqSensor.rawHumidity + "," + iaqSensor.iaq + "," + iaqSensor.co2Equivalent;
    //Serial.println(output);
    logFile.println(output);
    logFile.close();
    
    if (WiFi.status() == WL_CONNECTED)
    {
      if (!client.connect(DEVICE_NAME))
      {
        Serial.println("Can't connect to AWS");
      }
      else
      {
        sendJsonToAWS(unix_timestamp, iaqSensor.rawTemperature, iaqSensor.rawHumidity, iaqSensor.iaq, iaqSensor.co2Equivalent);
        client.loop();
      }
    }
    else
    {
      Serial.println("Lost WIFI Connection!");
      WiFi.reconnect();
    }
  } else {
    checkIaqSensorStatus();
  }
}
