/// Lab 02 - Analog Signal Acquisition
// Sample the analog output of the hall sensor sensor
// and print the value to the serial port


void setup() {
  // setup the serial connection
  Serial.begin(115200);
}

void loop() {


  // initialize your parameters
  float max_voltage = 3.3;
  float min_voltage = 0;
  int resolution = 4095;
  float voltage_step = (max_voltage - min_voltage) / resolution;
  int analogPin = 26;  //will be checked in the lab whether this is also the correct pin on the featherboard and not the online environment we call. (we want A0 = GPIO 26 = ADC2 = DAC2)


  // check if the serial port is available and if something is received from the serial port
  if( Serial.read() == 'r')
  {
    int i = 0;
    float sum = 0;
    for(i=0; i<20; i++){
      
      // Read the the hall sensor voltage
      sum += analogRead(analogPin);
      }    
      Serial.println(sum/20);
    }

    // Print the hall sensor voltage and the digital sampled value to the serial port
    //float hall_voltage = hall_read * voltage_step;
    //Serial.println(hall_voltage);
 
 delay(20);

}
