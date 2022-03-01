// lab00, lap procedure, task 2

// source file for the program sum_numbers

/*
 * This file is used to generate an executable program that prints the 
 * sum of the two numbers in binary and hexadecimal format.
*/

// Since we will be using our own functions, we need to add the header
// file where the functions are declared.
// Keep in mind that the header file already includes standard libraries
// so they do not to be included here.
#include "functions.h"
 
 // main function
int main(int argc, char *argv[])
{
	int16_t a_1 = 0x0004;
	int16_t b_1 = 0x0006;

	int16_t a_2 = 0x0034;
	int16_t b_2 = 0x0056;

	int16_t a_3 = 0x2001;
	int16_t b_3 = 0x35FA;

	int16_t a_4 = 0x3401;
	int16_t b_4 = 0x25EE;

	print_bits(a_1+b_1);
	print_bits(a_2+b_2);
	print_bits(a_3+b_3);
	print_bits(a_4+b_4);

	int16_t c = 0x1234;
	int16_t d = 0x2334;
	
	printf("mergin 0x%x and 0x%x results in 0x%x \n", c,d, bit_merge(c, d));
	printf("\tthe sum is hex: 0");

	return 0;
}
