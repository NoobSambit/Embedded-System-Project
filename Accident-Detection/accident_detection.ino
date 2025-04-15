#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <math.h>

// Initialize LCD: I2C address 0x27, 16x2 screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define accelerometer analog pins
#define xPin A1
#define yPin A2
#define zPin A3

// Define Buzzer and Button pins
#define BUZZER 12
#define BUTTON 11

// Initialize GSM and GPS serial ports
SoftwareSerial sim800(2, 3); // GSM: RX=D2, TX=D3
AltSoftSerial neogps;        // GPS: RX=D8, TX=D9

// Sensor and logic variables
int x, y, z;
bool sent = false;
unsigned long lastAccidentTime = 0;

// Calibration baseline values for accelerometer
const int centerX = 375;
const int centerY = 370;
const int centerZ = 590;

// Accident trigger threshold (adjustable based on sensitivity)
const float magnitudeThreshold = 500.0;

// For GPS display toggling
bool showGPS = false;
unsigned long lastToggleTime = 0;

// Store GPS coordinates
String latitude = "NA";
String longitude = "NA";

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  neogps.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Accident Alert");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read accelerometer data
  x = analogRead(xPin);
  y = analogRead(yPin);
  z = analogRead(zPin);

  // Calculate magnitude from calibrated center
  float magnitude = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2) + pow(z - centerZ, 2));

  // Debug log
  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" Z: "); Serial.print(z);
  Serial.print(" | Magnitude: "); Serial.println(magnitude);

  // Accident detection condition
  bool isAccident = magnitude > magnitudeThreshold;

  // Display magnitude on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Magnitude:");
  lcd.setCursor(10, 0);
  lcd.print((int)magnitude);

  if (isAccident && !sent) {
    // Accident Detected
    lcd.setCursor(0, 1);
    lcd.print("Accident Detected");

    tone(BUZZER, 2000);  // Buzzer ON
    delay(3000);
    noTone(BUZZER);      // Buzzer OFF

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending Location");

    sendLocation();     // Send SMS with GPS location

    sent = true;
    lastAccidentTime = millis();
  } 
  else if (!isAccident) {
    // Reset buzzer state
    noTone(BUZZER);
    digitalWrite(BUZZER, LOW);

    // Display alternating GPS/Status info if no accident
    if (!sent) {
      if (millis() - lastToggleTime > 2500) {
        showGPS = !showGPS;
        lastToggleTime = millis();
      }

      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear second line

      if (showGPS && latitude != "NA" && longitude != "NA") {
        lcd.setCursor(0, 1);
        lcd.print("Lat:");
        lcd.print(latitude.substring(0, 5));
        lcd.setCursor(9, 1);
        lcd.print("Lon:");
        lcd.print(longitude.substring(0, 5));
      } else {
        lcd.setCursor(0, 1);
        lcd.print("No Accident     ");
      }
    }
  }

  // Reset status after 30 seconds
  if (sent && millis() - lastAccidentTime > 30000) {
    sent = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ready Again");
    delay(1000);
  }

  // Manual reset via Button
  if (digitalRead(BUTTON) == LOW) {
    sent = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reset by Button");
    delay(1000);
  }

  delay(3000);
}

// Send SMS with Google Maps location link
void sendLocation() {
  String gpsData = "";
  unsigned long start = millis();

  // Collect GPS raw data for 5 seconds
  while (millis() - start < 5000) {
    if (neogps.available()) {
      char c = neogps.read();
      gpsData += c;
    }
  }

  Serial.println("GPS Raw: " + gpsData);

  // Search for GPGGA NMEA sentence
  int index = gpsData.indexOf("$GPGGA");
  if (index != -1) {
    String gpgga = gpsData.substring(index, index + 80);
    Serial.println("GPGGA Sentence: " + gpgga);

    // Parse latitude and longitude fields from GPGGA
    int firstComma = gpgga.indexOf(',', 7);
    int secondComma = gpgga.indexOf(',', firstComma + 1);
    int thirdComma = gpgga.indexOf(',', secondComma + 1);
    int fourthComma = gpgga.indexOf(',', thirdComma + 1);

    latitude = gpgga.substring(firstComma + 1, secondComma);
    longitude = gpgga.substring(thirdComma + 1, fourthComma);

    // If parsing fails, default to NA
    if (latitude == "" || longitude == "") {
      latitude = "NA";
      longitude = "NA";
    }

    // Convert coordinates to decimal
    float lat = convertToDecimal(latitude);
    float lon = convertToDecimal(longitude);

    // Build Google Maps link
    String googleMapLink = "https://maps.google.com/?q=" + String(lat, 6) + "," + String(lon, 6);

    // Send SMS using GSM module
    sim800.println("AT");
    delay(1000);
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+91XXXXXXXXXX\"");  // Replace with your real number
    delay(1000);
    sim800.println("Accident detected! Location:");
    sim800.println("Lat: " + String(lat, 6));
    sim800.println("Lon: " + String(lon, 6));
    sim800.println(googleMapLink);
    sim800.write(26); // End SMS
    delay(1000);
  } else {
    Serial.println("GPS data not found!");
    latitude = "NA";
    longitude = "NA";
  }
}

// Converts GPS NMEA coordinates to Decimal Degrees
float convertToDecimal(String coord) {
  if (coord.length() < 6) return 0.0;

  float deg = coord.substring(0, 2).toFloat();
  float min = coord.substring(2).toFloat();
  return deg + (min / 60.0);
}
