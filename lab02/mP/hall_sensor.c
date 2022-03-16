
#include "hall_sensor.h"
//Function hall_sensor_get_field converts the measured voltage value to a magnetic field (in milli-tesla)
float hall_sensor_get_field(float serial_reading, float voltage_0)
{
   // Insert your code here
   float max_voltage = 3.3;
   int sensitivity = 4095;
   float sensor_sensitivity = 0.05; // V/mT from Prelab
   float field = 0;

   // Convert the sensor value to a voltage
   float voltage_reading_calibrated = serial_reading * (max_voltage/sensitivity) - voltage_0;

   // Return fieldstrength in [mT]
   return voltage_reading_calibrated/sensor_sensitivity;
}
