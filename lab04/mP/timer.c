#include "feather_serial.h"

/* These are system level includes */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

void delay(int number_of_seconds)
{
    int micro_seconds = 1000000 * number_of_seconds;
  
    clock_t start_time = clock();
  
    while (clock() < start_time + micro_seconds);
}


int main()
{   // Intialize serial port and variables
    int serial_port = serialport_init( "/dev/cu.SLAB_USBtoUART", 115200);
    
    int correct_input_value = 0;    // "boolean" value that switches to 1 when a suitable input has been received
    int run_time;                   // Amount of seconds the timer is supposed to run
    int i;                          // Iteration variable
    int n;                          // returnvariable for serialport writebyte reset
    int q;                          // returnvariable for serialport writebyte increase

    char* reset = "a";              // Character to be sent through the serial port to reset the servo to its 0° position.
    char* increase = "b";           // Character to be sent through the serial port to tell the Arduino to advance by 1 second.
    
    // loop until the user wants to quit the timer program
    while (1) {
        
        /*_________________Begin - Input Section_________________*/
        //At startup: ask the user how long you want the watch to run (between 0 and 150 seconds) or if you want to quit the program.
        printf("How long would you like the clock to run (value between 0 and 150 [s] enter '0' to quit): ");
        scanf("%i", &run_time);

        if(run_time==0){
            break;
        }
        /*_________________End - Input Section_________________*/

        
        /*_________________Begin - Reset Section_________________*/
        if(run_time >0 && run_time<150){
            n = serialport_writebyte(serial_port, ((char*)reset));

            if (n == -1){
                printf("Unable to write to the port. \n");
            }
        }
        else{
            printf("Invalid input entered. \n");
        }
        /*_________________End - Reset Section_________________*/
        
    
		delay(1); // Wait 1 second before starting the timer
        printf("%d seconds will be timed, starting now! \n", run_time);
        
        
        /*_________________Begin - Advance Section_________________*/
        for(i=0; i<run_time; i++){
            q = serialport_writebyte(serial_port, ((char*)increase));
            if (q == -1){
                printf("Unable to write to the port \n");
            }
            delay(1);
        }
        
        /*_________________End - Advance Section_________________*/
    }
    
    // Close the serial port
	serialport_close(serial_port);
    
	return 0;
    
}
