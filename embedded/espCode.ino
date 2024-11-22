#include <DHT.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define DHTPIN 2      // GPIO pin where DHT11 is connected
#define DHTTYPE DHT11 // Specify DHT type: DHT11
DHT dht(DHTPIN, DHTTYPE);

int samplingTime = 280;
int deltaTime = 40;

// Define the analog pin for MQ-131 and MQ-135 sensors
const int mq131Pin = 34; // Analog-capable GPIO pin on ESP32
const int mq135Pin = 35; // Analog-capable GPIO pin on ESP32
const int gp2yPin = 32; // Analog-capable GPIO pin on ESP32
const int gp2yLedPin = 12; // Digital Pin for LED on GP2Y Sensor

// WiFi and ThingSpeak credentials
const char *ssid = "Toshiba SmartWashing Machine";
const char *pass = "dheerujaanu";
const char *url = "https://api.thingspeak.com/update";
const char *api_key = "HXP7C8Y6UO827R9F";

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT11 Sensor initialized");

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  // Read DHT11 data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  digitalWrite(gp2yLedPin, LOW); // power ON
  delayMicroseconds(samplingTime);

  // MQ-131 and MQ-135 readings
  int mq131SensorValue = analogRead(mq131Pin);
  int mq135SensorValue = analogRead(mq135Pin);
  int gp2ySensorValue = analogRead(gp2yPin);
  float mq131Voltage = mq131SensorValue * (3.3 / 4095.0);
  float mq135Voltage = mq135SensorValue * (3.3 / 4095.0);
  float gp2yVoltage = gp2ySensorValue * (5.0/1024.0);
  float ozoneConcentration = mq131Voltage * 10.0; // Adjust based on calibration
  float airQualityIndex = mq135Voltage * 10.0; // Adjust based on calibration
  float dustDensity = 170 * gp2yVoltage - 0.1;

  delayMicroseconds(deltaTime);
  digitalWrite(gp2yLedPin, HIGH); // power OFF

  Serial.print("Approx Ozone Concentration (ppm): ");
  Serial.println(ozoneConcentration);
  Serial.print("Approx Air Quality Index: ");
  Serial.println(airQualityIndex);
  Serial.print("Approx Dust Density: ");
  Serial.println(gp2ySensorValue);
  delay(1000); // Delay for readability

  // Send data to ThingSpeak
  sendToThingSpeak(humidity, temperature, ozoneConcentration, airQualityIndex, dustDensity);
}

void sendToThingSpeak(float humidity, float temperature, float ozoneConcentration, float airQualityIndex, float dustDensity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare the POST data
    String postData = String("api_key=") + api_key + 
                      "&field1=" + String(humidity) +
                      "&field2=" + String(temperature) +
                      "&field3=" + String(ozoneConcentration) +
                      "&field4=" + String(airQualityIndex) +
                      "&field5=" + String(dustDensity);
    
    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
      Serial.println("Response body: ");
      Serial.println(http.getString());
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected...");
  }
}

