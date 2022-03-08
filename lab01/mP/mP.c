#include <stdio.h>
#include <stdint.h>
#include "feather_serial.h"


// ***** print_bits() can be implemented here ***** //
int print_bits(uint8_t arg_word)
{
	// only a simple implementation of a for loop is given
	// you are free to use it or solve the problem in another way

    int arg_word_bin[8];
    uint8_t n = arg_word;

	for(int i = 0; i <= 8; i++)
	{
		arg_word_bin[i] = n % 2;
        n = n / 2;
	}

    printf("hex: 0x%04x, bin: ",arg_word);

    for(int i = 7; i>=0; i--)
    {
        printf("%d", arg_word_bin[i]);
        if(i%4==0)
        {
            printf(" ");
        }
    }
    printf("\n");
 }

int32_t main()
{
  int n1;
  int n2;
  int n;
  // initialization of serial communication, port and baud rate are specified
  int fd = serialport_init( "/dev/ttyUSB0", 115200);    // IMPORTANT CHANGE PORT IF USING MAC!!!!
  uint8_t arg = (uint8_t)245;

  int first_int;
  int second_int;

  while(1)
  {
  	scanf("%i %i", &first_int, &second_int);

  	if(first_int==0 && second_int==0){
  		break;
  	}

		
  	// send arg via serial communication to the mC
    // type casting is again needed to match type
    arg = (uint8_t) first_int + (uint8_t) second_int;
    printf("%i %i %i %i %i", first_int, second_int, (uint8_t) first_int, (uint8_t) second_int, arg);
    print_bits(arg);

    n = serialport_writebyte(fd,((char*)&arg));
    if(n == -1 )
    printf("Unable to write the port \n");
  }
  
  // close serial communication
  serialport_close(fd);
  return 0;
}

