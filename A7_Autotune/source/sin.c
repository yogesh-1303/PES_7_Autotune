#define TRIG_SCALE_FACTOR  (2037)
#define HALF_PI            (3200)  // pi * TRIG_SCALE_FACTOR / 2
#define PI                 (6399)  // pi * TRIG_SCALE_FACTOR
#define THREE_HALF_PI 		(9599)
#define TWO_PI            (12799)  // 2 * pi * TRIG_SCALE_FACTOR
#define DAC_SIZE			(4095)

#include "sin.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "systick.h"
#include "TPM0.h"

#define TRIG_TABLE_STEPS     (32)
#define TRIG_TABLE_STEP_SIZE (HALF_PI/TRIG_TABLE_STEPS)
//#define TEST

int16_t num_samples_pp, freq, samples_gen;

//lookup table for sine wave computation
static const int16_t sin_lookup[TRIG_TABLE_STEPS+1] =
  {0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960,
   1047, 1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694,
   1747, 1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
   2037};

//takes the sin angle in as argument from 0 to half_pi (0 to 3200)
//returns the value of sin(x) using linear interpolation taking reference values from sin_lookup table
int16_t interpolate(int16_t x){
	int16_t y2, y1, x1, x2, k=0, temp_y;
	//find the two points between which the i lie
	//apply y-y1 = [(y2-y1)/(x2-x1)] (x-x1)
	//x = k*100 (k: loop iteration variable)
	while(k <= (x/100))
			k++;
		y2 = sin_lookup[k];
		y1 = sin_lookup[k-1];
		x2 = k*100;
		x1 = (k-1)*100;
		temp_y = ((y2-y1)*(x-x1));
		temp_y += (x2-x1)/2;
		temp_y /= (x2-x1);
		temp_y += y1;
		return (temp_y);
}

//calculates the value of sin(i) where i is from -2pi to 2pi
//uses interpolate() function to calculate the values
//returns the value of sin(i)
//uses integer maths to calculate the values
int16_t fp_sin(int16_t i){
	 int16_t y;
	 //when i is between 0 and pi/2
	if(((0<=i)&&(i<=HALF_PI))||((-TWO_PI<=i)&&(i<=-THREE_HALF_PI))){
		if(i<0)
			i += (TWO_PI);
		y = interpolate(i);
	}
	//when i is between pi/2 and pi
	//reverse the sin lookup table i.e., sin(3201)=2037 and sin(6399) = 100
	else if(((HALF_PI<i)&&(i<=PI))||((-THREE_HALF_PI<i)&&(i<=-PI))){
		if(i<0)
			i += (TWO_PI);//((THREE_HALF_PI+1) + HALF_PI);
		y = interpolate((PI)-i);
	}
	else if(((PI<i)&&(i<=THREE_HALF_PI))||((-PI<i)&&(i<-HALF_PI))){
		if(i<0)
			i += (TWO_PI);//((PI+1) + PI);
		y = -interpolate(i-(PI));
	}
	//when i is between 3pi/2 and 2pi
	else if(((THREE_HALF_PI<i)&&(i<=TWO_PI))||((-HALF_PI<=i)&&(i<=0))){
		if(i<0){
			 i += (TWO_PI);//-1;
		//	i += THREE_HALF_PI;
		}
		y = -interpolate((TWO_PI)-i);
	}
	return(y);
	}

//tests the error and sum of square error in fp_sin() function (vaues of sin(i))
//takes no argument and returns void
#ifdef TEST
void test_sin()
{
 double act_sin;
 double exp_sin;
double err;
 double sum_sq = 0;
 double max_err = 0;
 for (int i=-TWO_PI; i <= TWO_PI; i++) {
 exp_sin = sin( (double)i / TRIG_SCALE_FACTOR) * TRIG_SCALE_FACTOR;
 act_sin = fp_sin(i);
 err = act_sin - exp_sin;
 if (err < 0)
 err = -err;
 if (err > max_err)
 max_err = err;
 sum_sq += err*err;
 }
 printf("max_err=%f sum_sq=%f\n", max_err, sum_sq);
}
#endif


//calculates the samples for each tone from the sin function calculated using fp_sin()
//also calculates the number of samples generated for each tone
//takes the tone type and a buffer (where samples will be stored) as arguments
//returns void
void tone_to_samples(tones tone, uint16_t *sin_buffer){
	uint16_t samples;
	switch(tone){
	case A4: freq = 440;
				goto num_samples;
				break;
	case D5: freq = 587;
				goto num_samples;
				break;
	case E5: freq = 659;
				goto num_samples;
				break;
	case A5: freq = 880;
				goto num_samples;
				break;
	num_samples: num_samples_pp = (DMA_SAMPLE_FREQ/freq);
	}
	samples_gen = SIZE/num_samples_pp;
	samples_gen *= num_samples_pp;
    //printf("\r\n samples generated = %d at %d Hz, sample period = %d", samples_gen, freq, num_samples_pp);
	for(samples=0; samples<samples_gen; samples++){
		sin_buffer[samples] = TRIG_SCALE_FACTOR + fp_sin((samples % num_samples_pp)*(TWO_PI+1)/num_samples_pp);
	}
}

//computes values of the generated samples in DAC buffer as well as samples per period for a tone
//takes the frequency of the tone in input and returns void
void samples_generated(uint16_t frequency){
	freq = frequency;
	num_samples_pp = (DMA_SAMPLE_FREQ)/frequency;
	samples_gen = SIZE/num_samples_pp;
    samples_gen *= num_samples_pp;
}

