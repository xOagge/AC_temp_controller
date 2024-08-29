## Arduino Environmental Monitoring System

  This project involves an Arduino-based environmental monitoring system that uses various sensors to display time, temperature, and humidity on an I2C LCD. The system also includes a servo motor that can be used to control a device (though not actively used in the provided code). The code continuously monitors environmental conditions and updates the display.

  **Components Required:**
  - Arduino Uno (or similar)
  - DHT11 Sensor (for temperature and humidity)
  - I2C LCD Display (20x4 or similar)
  - RTC DS3231 (Real-Time Clock)
  - Servo Motor (for control, but not actively used in the provided code)
  - Connecting wires and breadboard

  **Code Overview:**

  **Arduino Code:**
  - **Sensors:**
    - DHT11 Sensor: Measures temperature and humidity.
    - RTC DS3231: Provides real-time clock functionality.

  - **LCD Display:**
    - Display: Shows the current time, temperature, and humidity.

  - **Functions:**
    - `setup()`: Initializes serial communication, the LCD display, DHT sensor, and RTC. Sets up the servo motor.
    - `loop()`: Continuously processes inputs, updates the display, and manages the AC status.
    - `UpdateACStatus()`: Controls the AC based on temperature and time criteria.
    - `switchAcState()`: Toggles the state of the AC and adjusts the servo motor position.
    - `processInputs()`: Processes and validates time, temperature, and humidity readings.
    - `processTimeAndValidate()`: Reads the current time from the RTC and updates if necessary.
    - `processTempAndValidate()`: Reads temperature from the DHT sensor and updates if necessary.
    - `processHumidAndValidate()`: Reads humidity from the DHT sensor and updates if necessary.
    - `UpdateDisplay()`: Updates the LCD display with the latest time, temperature, and humidity.
    - `InitializeDisplay()`: Initializes the LCD and sets up initial display values.

  **Libraries Used:**
  - `Wire.h`: For I2C communication with the LCD.
  - `LiquidCrystal_I2C.h`: For controlling the I2C LCD display.
  - `DHT.h`: For interfacing with the DHT11 sensor.
  - `RTClib.h`: For interfacing with the DS3231 RTC.
  - `Servo.h`: For controlling the servo motor.

  **Setup:**
  1. **Connect Components:**
    - **DHT11 Sensor:**
      - Connect the data pin to analog pin A4.
    - **I2C LCD Display:**
      - Connect to the I2C bus (typically SDA to A4 and SCL to A5 on Arduino Uno).
    - **RTC DS3231:**
      - Connect to the I2C bus (typically SDA to A4 and SCL to A5 on Arduino Uno).
    - **Servo Motor:**
      - Connect to digital pin 2.

  2. **Upload Arduino Code:**
     - Use the Arduino IDE to upload the provided code to your Arduino board.

  3. **Open Serial Monitor:**
     - Set to 9600 baud to view debugging messages (if any).

  **Troubleshooting:**
  - **Incorrect Display:**
    - Ensure the I2C address for the LCD is correct.
    - Verify connections and check for proper library installation.
  - **Joystick Not Responding:**
    - Check the wiring and make sure the joystick is correctly connected.
    - Verify that the analog pins are properly defined and working.
  - **LCD Issues:**
    - Confirm the I2C address and wiring.
    - Ensure the LCD library is correctly installed and compatible with your display.

  **License:**
  This project is open-source and licensed under the [MIT License](https://opensource.org/licenses/MIT).
*/
