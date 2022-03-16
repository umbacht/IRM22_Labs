
#include "hall_sensor.h"
//Function hall_sensor_get_field converts the measured voltage value to a magnetic field (in milli-tesla)
float hall_sensor_get_field(float voltage, float voltage_0)
{
   // Insert your code here
   float sensitivity = 0.05; // V/mT from Prelab
   float field = 0;
   
   float voltage_reading_calibrated = voltage - voltage_0;

   return voltage_reading_calibrated/sensitivity;
}
