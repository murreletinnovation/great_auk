#include <SD.h>
#include "FS.h"
#include "RTClib.h"
#include "Adafruit_PM25AQI.h"
#include "Adafruit_BME680.h"

RTC_PCF8523 rtc;

Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

const int chipSelect = 33;
String logFilename;
File logFile;

Adafruit_BME680 bme;

void setup() 
{
  String output;
  
  Serial.begin(115200);
  Wire.begin();
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  else
  {
    Serial.println("RTC Found!");
  }

  if (! rtc.initialized() || rtc.lostPower()) {
      Serial.println("RTC is NOT initialized, let's set the time!");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();

  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
    abort();
  }
  else
  {
    Serial.println("SD card Found!");
  }
  
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  else
  {
    Serial.println("Found BME680!");
  }
  
  /*iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  checkIaqSensorStatus();
  iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();*/
  
  DateTime now = rtc.now();
  String epochString = String(now.unixtime());
  
  logFilename = "/log_" + epochString + ".csv";
  logFile = SD.open(logFilename, FILE_WRITE);
  output = "timestamp,raw_temperature,raw_relative_humidity,pm2.5,pm10,pm25,pm100";
  logFile.println(output);
  logFile.close();

  rtc.start();

  delay(1000);
  if (! aqi.begin_I2C())
  {
    Serial.println("Could not find PM 2.5 sensor!");
    //abort();
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() 
{
  String output;
  uint32_t unix_timestamp;
  PM25_AQI_Data data;
  
  DateTime now = rtc.now();

  if (!aqi.read(&data))
  {
    Serial.println("Could not read from AQI");
    return;
  }

  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  delay(50); // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  
  unix_timestamp = now.unixtime();
  logFile = SD.open(logFilename, FILE_APPEND);
  output = String(unix_timestamp) + "," + bme.temperature + "," + bme.humidity + "," + data.pm10_standard + "," + data.pm25_standard + "," + data.pm100_standard;
  Serial.println(output);
  logFile.println(output);
  logFile.close();
  
  delay(3000);
}
