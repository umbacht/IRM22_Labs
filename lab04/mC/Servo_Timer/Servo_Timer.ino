// Make sure these libraries are installed
// If not the case, use Tools > Manage Libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// declaring variables

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int servo_num = 0;
int servo_freq = 50;

float pos = 0;                // current position initialized at 0, minimum (0°) & maximum (180°) pulse length of the servo in µs
int MinPulse = 550;
int MaxPulse = 2400;             
float secondStep;             // unrounded pulse length increase in µs that corresponds to an increase of 1 second
float exactPos;               // Exact, unrounded position of the servo in µs
char serialVariable;          // Character received through the serial communication

void setup() {
  Serial.begin(115200);                 // open serial communication

  //_________________Begin - Setup_______________
  
  // Begin PWM communication and set servo frequency
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(200);
  
  //_________________End - Setup_______________

}

void loop() {
  
  // Only run the loop if the serial communication is available
  if( Serial.available())
  {
    
    // read the incoming character and save it in "serialVariable"
    serialVariable = Serial.read();

    // If "a" is received reset the servo to its starting position.
    //_________________Begin - Reset_______________
    if (serialVariable == 'a'){
      pwm.writeMicroseconds(1, MinPulse);
      pos = 0;
    }
    //_________________End - Reset_______________


    // If "b" is received move the motor by one step.
    
    //_________________Begin - Advance_______________
    if (serialVariable == 'b'){
      pos += 1.2;           // as we enter a time in between 0 and 150s and wand to access the angle of the servo from 0 to 180 degree, we need to increase the position by 1.2 degree every second to arrive at 180degree after 150 seconds. 
    }
    
    int mapped_pwm_duration = map(pos, 0, 180, 550, 2250);
    Serial.println(mapped_pwm_duration);
    pwm.writeMicroseconds(1, mapped_pwm_duration);
     
    //_________________End - Advance_______________

    
  }
}
