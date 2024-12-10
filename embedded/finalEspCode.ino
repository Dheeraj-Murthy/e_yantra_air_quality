#include <DHT.h>
#include <HTTPClient.h>
#include <WiFi.h>

// DHT11 Sensor Setup
#define DHTPIN 2      // GPIO pin where DHT11 is connected
#define DHTTYPE DHT11 // Specify DHT type: DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensor Pins
const int MQ131_PIN = 34;    // Analog pin for MQ-131
const int MQ135_PIN = 35;    // Analog pin for MQ-135
const int GP2Y_PIN = 32;     // Analog pin for GP2Y1010
const int GP2Y_LED_PIN = 12; // LED pin for GP2Y1010

// Constants
const float VOLTAGE_REF = 3.3;      // Reference voltage for ESP32 ADC
const int ADC_RESOLUTION = 4095;   // ESP32 ADC resolution
const float GP2Y_BASELINE = -0.1;  // Baseline for dust density calculation
const float GP2Y_SENSITIVITY = 170.0;

// WiFi and ThingSpeak credentials
const char *SSID = "Toshiba SmartWashing Machine";
const char *PASSWORD = "dheerujaanu";
const char *THINGSPEAK_URL = "https://api.thingspeak.com/update";
const char *API_KEY = "HXP7C8Y6UO827R9F";

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(GP2Y_LED_PIN, OUTPUT);
  digitalWrite(GP2Y_LED_PIN, HIGH); // Turn off GP2Y LED by default

  Serial.println("Initializing sensors...");

  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  // Read sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float ozoneConcentration = readSensor(MQ131_PIN) * 10.0; // Adjust based on calibration
  float airQualityIndex = readSensor(MQ135_PIN) * 10.0;    // Adjust based on calibration
  float dustDensity = readGP2Y();

  // Print readings
  printReadings(humidity, temperature, ozoneConcentration, airQualityIndex, dustDensity);

  // Send to ThingSpeak
  sendToThingSpeak(humidity, temperature, ozoneConcentration, airQualityIndex, dustDensity);

  delay(1000); // Wait for next cycle
}

void connectToWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

float readSensor(int pin) {
  int rawValue = analogRead(pin);
  float voltage = rawValue * (VOLTAGE_REF / ADC_RESOLUTION);
  return voltage;
}

float readGP2Y() {
  digitalWrite(GP2Y_LED_PIN, LOW); // Turn on LED
  delayMicroseconds(280);
  float voltage = readSensor(GP2Y_PIN);
  delayMicroseconds(40);
  digitalWrite(GP2Y_LED_PIN, HIGH); // Turn off LED
  return GP2Y_SENSITIVITY * voltage + GP2Y_BASELINE;
}

void printReadings(float humidity, float temperature, float ozoneConcentration, float airQualityIndex, float dustDensity) {
  Serial.println("\nSensor Readings:");
  Serial.printf("Humidity: %.2f %%\n", humidity);
  Serial.printf("Temperature: %.2f °C\n", temperature);
  Serial.printf("Ozone Concentration: %.2f ppm\n", ozoneConcentration);
  Serial.printf("Air Quality Index: %.2f\n", airQualityIndex);
  Serial.printf("Dust Density: %.2f mg/m³\n", dustDensity);
}

void sendToThingSpeak(float humidity, float temperature, float ozoneConcentration, float airQualityIndex, float dustDensity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(THINGSPEAK_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Create POST data
    String postData = String("api_key=") + API_KEY + 
                      "&field1=" + String(humidity) +
                      "&field2=" + String(temperature) +
                      "&field3=" + String(ozoneConcentration) +
                      "&field4=" + String(airQualityIndex) +
                      "&field5=" + String(dustDensity);

    // Send POST request
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      Serial.printf("ThingSpeak Response: %d\n", httpResponseCode);
      Serial.println(http.getString());
    } else {
      Serial.printf("HTTP Error: %d\n", httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected...");
  }
}
