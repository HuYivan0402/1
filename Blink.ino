/*
  Blink with Breathing Effect

  Turns an LED on and off with a breathing effect, controlled by a temperature sensor.
  The higher the temperature, the faster the breathing frequency, and vice versa.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 4 May 2023
  by Little B

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// Pin number for the LED
const int LED_PIN = 9;

// Temperature sensor pin
const int TEMP_SENSOR_PIN = A0;

// The minimum and maximum temperature values to map the breathing frequency
const float MIN_TEMP = 20.0; // Celsius
const float MAX_TEMP = 30.0; // Celsius

// The minimum and maximum frequencies for the breathing effect
const float MIN_FREQ = 0.5; // Hz
const float MAX_FREQ = 5.0; // Hz

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
}

// the loop function runs over and over again forever
void loop() {
  // Read the temperature from the sensor (in Celsius)
  float temp = analogRead(TEMP_SENSOR_PIN) * 0.00488; // V / LSB
  temp = (temp - 0.5) * 100.0;

  // Map the temperature value to a frequency for the breathing effect
  float freq = map(temp, MIN_TEMP, MAX_TEMP, MIN_FREQ, MAX_FREQ);

  // Calculate the period of the breathing effect
  float period = 1.0 / freq;

  // Calculate the time for the LED to fade in and out (in milliseconds)
  int fade_time = period / 2.0 * 1000;

  // Turn the LED on with a fading effect
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(LED_PIN, brightness);
    delay(fade_time / 255);
  }

  // Turn the LED off with a fading effect
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(LED_PIN, brightness);
    delay(fade_time / 255);
  }
}
