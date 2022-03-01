// lab00, lab procedure, tasks 1 & 3

// source file

/* 
 * this file contains the implementation of the functions relevant for
 * lab00.
 * The declarations of the functions are in the corresponding header 
 * file (functions.h).
*/

// the header file needs to be included
#include "functions.h"

/* task 1
 * The function print_bits() accepts an input of type uint16_t 
 * (arg_word) and has no return value (void).
 * The function simply writes the binary and hexadecimal number of the
 * input to the terminal.
*/
void print_bits(uint16_t arg_word)
{
	// only a simple implementation of a for loop is given
	// you are free to use it or solve the problem in another way

    int arg_word_bin[16];
    uint16_t n = arg_word;

	for(int i = 0; i <= 15; i++)
	{
		arg_word_bin[i] = n % 2;
        n = n / 2;
	}

    printf("hex: 0x%04x, bin: ",arg_word);

    for(int i = 15; i>=0; i--)
    {
        printf("%d", arg_word_bin[i]);
        if(i%4==0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

/* task 3
 * The function bit_merge() accepts two uint16_t as inputs (lsb and msb) 
 * and combines them to a uint32_t number by merging them.
 * The return value is a uint32_t number.
 */
 uint32_t bit_merge(uint16_t lsb, uint32_t msb)
 {
    uint32_t merged_number;
    msb = msb << 16;
    merged_number = lsb|msb;

	 // for the moment, the function only returns 0
	 return merged_number;
 }
