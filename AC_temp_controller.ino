#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <RTClib.h>
#include <Servo.h>

// Define the LCD I2C address and dimensions (20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;

// DHT sensor settings
#define DHTPIN A4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//servo
#define SERVO_PIN 2
Servo myServo;
float servoAngle = 180.0;  // Start at the center position
uint32_t acOnTime = 1000 * 10; // Define time that the AC shall be turned ON
uint32_t CurrentAcOnTime = 0; // Starting value high
int32_t startTime = 0; // Last system time that AC was turned ON so we can calculate CurrentAcOnTime
bool ON = false; // Suppose system is initiated with the AC turned off
float switchOnTemp = 26;
float switchOffTemp = 25.5;

//software
bool TempChanged = false;
bool HumidChanged = false;
bool TimeChanged = false;

float temp = 0;
float humidity = 0;
String currentTime = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  InitializeDisplay();
  dht.begin(); // TH sensor
  //clock
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //servo motor
  myServo.attach(SERVO_PIN);
  // Set the initial servo position
  myServo.write(servoAngle);
}

void loop() {
  processInputs();
  UpdateDisplay();
  UpdateACStatus();
}

// AC TURN ON/OFF LOGIC
void UpdateACStatus() {
  // Turn AC ON/OFF when a certain temperature is met (CurrentAcOnTime >= acOnTime)
  if (temp >= switchOnTemp && !ON) {
    switchAcState(); // Turn ON
  } else if (CurrentAcOnTime >= acOnTime && temp <= switchOffTemp && ON) { // If time has passed, temp is cold, and AC is ON
    switchAcState(); // Turn OFF
  } else if (ON) {
    CurrentAcOnTime = millis() - startTime; // Track time
  }
}

void switchAcState() {
  startTime = millis();
  CurrentAcOnTime = 0;
  myServo.write(0);
  delay(2000);
  myServo.write(180);
  ON = !ON;
}

void processInputs() {
  processTimeAndValidate();
  processTempAndValidate();
  processHumidAndValidate();
}

// PROCESS RTC TIME
void processTimeAndValidate() {
  DateTime now = rtc.now(); // Get the current time from the RTC
  String timeRead = (String(now.hour() < 10 ? "0" : "") + String(now.hour()) + ":" +
                     String(now.minute() < 10 ? "0" : "") + String(now.minute()) + ":" +
                     String(now.second() < 10 ? "0" : "") + String(now.second()) + " " +
                     String(now.day() < 10 ? "0" : "") + String(now.day()) + "/" +
                     String(now.month() < 10 ? "0" : "") + String(now.month()));
  if (timeRead != currentTime) {
    currentTime = timeRead;
    TimeChanged = true;
  }
}

// READ TEMP AND VALIDATE
void processTempAndValidate() {
  float tempRead = dht.readTemperature();
  if (!isnan(tempRead) && temp != tempRead) {
    temp = tempRead;
    TempChanged = true;
  }
}

// READ HUMIDITY AND VALIDATE
void processHumidAndValidate() {
  float humidityRead = dht.readHumidity();
  if (!isnan(humidityRead) && humidity != humidityRead) {
    humidity = humidityRead;
    HumidChanged = true;
  }
}

// UPDATE DISPLAY
void UpdateDisplay() {
  if (TimeChanged || TempChanged || HumidChanged) {
    // Update time
    if (TimeChanged) {
      lcd.setCursor(0, 0);
      lcd.print("                "); // Clear the line
      lcd.setCursor(0, 0);
      lcd.print("Time: ");
      lcd.print(currentTime);
    }

    // Update temperature
    if (TempChanged) {
      lcd.setCursor(6, 1);
      lcd.print("        "); // Clear the line
      lcd.setCursor(6, 1);
      lcd.print(temp);
      lcd.print(" C");
    }

    // Update humidity
    if (HumidChanged) {
      lcd.setCursor(10, 2);
      lcd.print("      "); // Clear the line
      lcd.setCursor(10, 2);
      lcd.print(humidity);
      lcd.print("%");
    }

    // Send data to the serial monitor for debugging
    Serial.print(currentTime);
    Serial.print(" T: ");
    Serial.println(temp);
    Serial.print(currentTime);
    Serial.print(" H: ");
    Serial.println(humidity);

    // Reset change flags after updating the display
    TimeChanged = false;
    TempChanged = false;
    HumidChanged = false;
  }
}

void InitializeDisplay() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(0, 2);
  lcd.print("Humidity:");
}
