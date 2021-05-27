#include <stdint.h>

#define SIZE 			(1024)
#define SIZE_A4 		(981)
#define SIZE_D5 		(972)
#define SIZE_E5 		(1008)
#define SIZE_A5 		(972)

//tones
typedef enum {
    A4, D5, E5, A5} tones ;

//takes the sin angle in as argument from 0 to half_pi (0 to 3200)
//returns the value of sin(x) using linear interpolation taking reference values from sin_lookup table
int16_t interpolate(int16_t x);

//calculates the value of sin(i) where i is from -2pi to 2pi
//uses interpolate() function to calculate the values
//returns the value of sin(i)
//uses integer maths to calculate the values
int16_t fp_sin(int16_t i);

//tests the error and sum of square error in fp_sin() function (vaues of sin(i))
//takes no argument and returns void
void test_sin();

//calculates the samples for each tone from the sin function calculated using fp_sin()
//also calculates the number of samples generated for each tone
//takes the tone type and a buffer (where samples will be stored) as arguments
//returns void
void tone_to_samples(tones, uint16_t *);

//computes values of the generated samples in DAC buffer as well as samples per period for a tone
//takes the frequency of the tone in input and returns void
void samples_generated(uint16_t);
