#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// include your function definitions here
#include "feather_serial.h"
#include "hall_sensor.h"

int main()
{
    // initialize all parameters
    char buffer[4];
    char command_read = 'r';
    int serial_reading;
    float quiescent_voltage = 1.65;

    // initialize the serial port on the port /dev/ttyUSB0, with baud rate 115200
    int serial_port = serialport_init( "/dev/cu.SLAB_USBtoUART", 115200);    // CHANGE PORT IF USING MAC
    
    // write to the serial port to get a value
    int return_value_of_serialwrite = serialport_write(serial_port, &command_read); //sending char 'r'

    // Let the user know if you were able to write to the port
    if (return_value_of_serialwrite == -1){
        printf("ERROR: WAS NOT ABLE TO WRITE TO SERIAL PORT\n");
    }

    // Read the sensor value into the buffer from the serial port
    int serial_read_return = serialport_read(serial_port, buffer, 4, 100);
    //printf("buffer: %c", buffer);
    serial_reading = atoi(buffer);

    // Let the user know if you were able to read from the port
    if (serial_read_return == -1){
        printf("ERROR: WAS NOT ABLE TO READ FROM SERIAL PORT\n");
    }

    float field_strength = hall_sensor_get_field(serial_reading, quiescent_voltage); 
    printf("%f\n", field_strength);

    // Close the serial port
    serialport_close(serial_port);

	return 0;
}
