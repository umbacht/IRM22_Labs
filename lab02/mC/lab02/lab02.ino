/// Lab 02 - Analog Signal Acquisition
// Sample the analog output of the hall sensor sensor
// and print the value to the serial port


void setup() {
  // setup the serial connection
  Serial.begin(115200);
}

void loop() {


  // initialize your parameters
  float max_voltage = 5;
  float min_voltage = 0;
  int resolution = 1024;
  float voltage_step = (max_voltage - min_voltage) / resolution;
  int analogPin = 0;


  // check if the serial port is available and if something is received from the serial port
  if( Serial.read() == 'r')
  {

    // Read the the hall sensor voltage
    unsigned int hall_read = analogRead(analogPin);


    // Print the hall sensor voltage and the digital sampled value to the serial port
    float hall_voltage = hall_read * voltage_step;
    Serial.println(hall_voltage);

  }
 delay(20);

}
