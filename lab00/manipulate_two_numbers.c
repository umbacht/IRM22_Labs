// lab00, lab procesure, task 4

// source file for the program manipulate_two_numbers

/*
 * This file is used to generate an executable program that reads two
 * numbers from the terminal and output the merged result in 
 * hexadecimal, and the sum in hexadecimal and binary format.
*/

// again, the header of our function library is already included 
#include "functions.h"
#include <stdint.h>

// main
int main(int argc, char *argv[])
{
	uint16_t var1;
	uint16_t var2;
	
	while(1)
	{
	scanf("%hx %hx", &var1, &var2);
	
	if((var1 == 0x0000) && (var2 == 0x0000))
	{
		break;
	}

	uint16_t var3 = var1 +var2;

	printf("merging 0x%x and 0x%x results in 0x%x \n", var1, var2, bit_merge(var1, var2));
	printf("\tthe sum is ");
	print_bits(var3);
	}

	return 0;
}
