// Make sure these libraries are installed
// If not the case, use Tools > Manage Libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// declare variables
int servo_num = 0;
int servo_freq = 50;
int analog_pin = 26;
int poti_reading = 0;
int mapping = 0;
int mapped_pwm_duration = 0;
// create a pwm object to control the servo
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  
  // _______________ Begin - Setup _______________

  // Begin the serial communication
  Serial.begin(115200);
  // Begin PWM communication and set servo frequency
  pwm.begin();
  pwm.setPWMFreq(50); //equals to 20ms 
  delay(200);
  
  
  // _______________ End - Setup _______________
  
}

void loop() {
  // _______________ Begin - Loop _______________

  // Read values from the analog pin and map/scale them to the movment range of the servo.
  // Optionally display the reading from the potentiometer on the serial monitor
  // Set the servo position according to the mapped/scaled value
  
  poti_reading = analogRead(analog_pin);
  mapped_pwm_duration = map(poti_reading, 0, 4095, 550, 2250); //the max range of 2400 had to be corrected to 2250 for the setup in the lab (discussed with alex)
  Serial.println(mapped_pwm_duration);
  pwm.writeMicroseconds(1, mapped_pwm_duration);
  
  // _______________ End - Loop _______________
  
  delay(15); // wait for the servo to get there
}
