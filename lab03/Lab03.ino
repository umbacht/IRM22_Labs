#include <analogWrite.h>

#define maxWaveform 4   //No. of waveforms in the array  
#define maxSamplesNum 120  //No. of samples of each wave 

static int waveformsTable[maxWaveform][maxSamplesNum] = {  
  // Sin wave
  {
    0x80,0x86,0x8d,0x93,0x9a,0xa0,0xa7,0xad,
    0xb3,0xb9,0xbf,0xc5,0xca,0xd0,0xd5,0xda,
    0xde,0xe3,0xe7,0xea,0xee,0xf1,0xf4,0xf7,
    0xf9,0xfb,0xfc,0xfd,0xfe,0xff,0xff,0xff,
    0xfe,0xfd,0xfc,0xfb,0xf9,0xf7,0xf4,0xf1,
    0xee,0xea,0xe7,0xe3,0xde,0xda,0xd5,0xd0,
    0xca,0xc5,0xbf,0xb9,0xb3,0xad,0xa7,0xa0,
    0x9a,0x93,0x8d,0x86,0x80,0x79,0x72,0x6c,
    0x65,0x5f,0x58,0x52,0x4c,0x46,0x40,0x3a,
    0x35,0x2f,0x2a,0x25,0x21,0x1c,0x18,0x15,
    0x11,0xe,0xb,0x8,0x6,0x4,0x3,0x2,
    0x1,0x0,0x0,0x0,0x1,0x2,0x3,0x4,
    0x6,0x8,0xb,0xe,0x11,0x15,0x18,0x1c,
    0x21,0x25,0x2a,0x2f,0x35,0x3a,0x40,0x46,
    0x4c,0x52,0x58,0x5f,0x65,0x6c,0x72,0x79,
  }
  ,

  // Triangular wave
  {
    0x4,0x9,0xd,0x11,0x15,0x1a,0x1e,0x22,
    0x26,0x2b,0x2f,0x33,0x37,0x3c,0x40,0x44,
    0x48,0x4d,0x51,0x55,0x59,0x5e,0x62,0x66,
    0x6a,0x6f,0x73,0x77,0x7b,0x80,0x84,0x88,
    0x8c,0x91,0x95,0x99,0x9d,0xa2,0xa6,0xaa,
    0xae,0xb3,0xb7,0xbb,0xbf,0xc4,0xc8,0xcc,
    0xd0,0xd5,0xd9,0xdd,0xe1,0xe6,0xea,0xee,
    0xf2,0xf7,0xfb,0xff,0xfb,0xf7,0xf2,0xee,
    0xea,0xe6,0xe1,0xdd,0xd9,0xd5,0xd0,0xcc,
    0xc8,0xc4,0xbf,0xbb,0xb7,0xb3,0xae,0xaa,
    0xa6,0xa2,0x9d,0x99,0x95,0x91,0x8c,0x88,
    0x84,0x80,0x7b,0x77,0x73,0x6f,0x6a,0x66,
    0x62,0x5e,0x59,0x55,0x51,0x4d,0x48,0x44,
    0x40,0x3c,0x37,0x33,0x2f,0x2b,0x26,0x22,
    0x1e,0x1a,0x15,0x11,0xd,0x9,0x4,0x0,
  }
};



void setup() {

  analogWriteResolution(8);  // sets the analog output resolution to 8 bit (256 levels)
 
}

void loop() {
 
  int i = 0 ; 
  while(1)  
  {
  	dacWrite(DAC1, waveformsTable[0][i]);  // Output the analog sine waveform on DAC1 pin  
  	i++; //incrementing the counter to choose the next sample 
  
  	if(i == maxSamplesNum -1 )  // Reset the counter to repeat the wave 
   	 i = 0;

    // use delayMicroseconds to change the frequency of your output
    float output_frequency_wanted = 20.0;
    float delay_time = ((1/(120 * output_frequency_wanted/1000000)) - (18.85));
    delayMicroseconds(delay_time);
  }
}
