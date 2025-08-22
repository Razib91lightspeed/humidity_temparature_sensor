#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pin connected to the sensor
#define DHTPIN A0  // Pin A0 is used for the sensor

// Define the type of DHT sensor (DHT11, DHT22, or DHT21)
#define DHTTYPE DHT11  // Change to DHT22 if it's a DHT22 sensor

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Define the LED pin
#define LEDPIN 12  // Pin 12 is used for the LED

// Initialize I2C LCD (20x4 display, I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Address 0x27, 20 columns, 4 rows

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Print initialization messages once
  Serial.println("DHT Sensor Test");

  // Initialize the DHT sensor
  dht.begin();

  // Set LED pin as output
  pinMode(LEDPIN, OUTPUT);

  // Initialize the I2C LCD
  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("Initializing...");
  Serial.println("LCD initialized. Waiting for 2 seconds...");
  delay(2000);       // Wait for 2 seconds
  lcd.clear();       // Clear the LCD
  Serial.println("LCD cleared. Starting loop...");
}

void loop() {
  // Blink the LED before taking a measurement
  digitalWrite(LEDPIN, HIGH);  // Turn the LED on
  Serial.println("LED ON");
  delay(500);                  // Wait 500ms
  digitalWrite(LEDPIN, LOW);   // Turn the LED off
  Serial.println("LED OFF");
  delay(500);                  // Wait 500ms

  // Read temperature as Celsius
  Serial.println("Reading temperature...");
  float tempC = dht.readTemperature();
  Serial.println("Temperature read complete.");

  // Read humidity
  Serial.println("Reading humidity...");
  float humidity = dht.readHumidity();
  Serial.println("Humidity read complete.");

  // Check if any reads failed
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);  // Set cursor to the first row
    lcd.print("Sensor Error!");
    return;
  }

  // Print the results to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  // Display the results on the LCD
  lcd.clear();  // Clear the LCD before updating
  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(0, 1);  // Set cursor to the second row
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  // Wait before the next measurement
  Serial.println("Waiting for 7 seconds...");
  delay(7000);  // Total wait time between measurements (8 seconds overall)
}