# PES_7_Autotune
INTRODUCTION:
The assignment is made using C language on MCUXpresso IDE with KL25Z MCU.

CODE STRUCTURE:

The assignment consists of following .c and their corresponding .h files:

A7_Autotune.c: Contains the main function and the function to change the tones after one second.

TPM0.c: contains function to initialize the TPM0 module (using interrupt) for DMA transfer. Also contains the function to start the timer.

DMA.c: Contains the functions to initialize the DMA0 module and transfer the data from a buffer to the DAC. Also contains the DMA Interrupt handler for starting over the DMA cycle again when buffer is full.

DAC.c: contains a function to initialize as well as enable  the DAC module for data transfer.

ADC.c: Contains function to initialize the ADC0 module for converting the data coming from the DAC. It also contains the function to initialize the TPM1 module used to on interrupt generation to read the samples from ADC. Further, a function to analyse the ADC buffer is also present which computes the minimum, maximum and average values of the buffer.

systick.c: This file has a function that initializes the systick module used for generating one second delay (for a tone to play for one second). The file also contains the systick handler as the timer is running on interrupt basis.

sin.c: this file contains all the functions relation to the sine wave that we are using in this assignment. It contains following type of functions:

•	A function to perform linear interpolation for computing values other than those in lookup table. It works on the angles from zero to half pi.

•	fp_sin() function which computes the whole sine wave from -2pi to 2pi using the interpolate function.

•	A function to compute the samples from the tone (sine) that we computed using above functions. This function also provides the number of samples generated and samples per period.
Other than the functions, the file also contains a sine lookup table for taking reference for creating the sine wave.

•	A function that computes the number of samples generated and the number of samples per period for a tone.

autocorrelated.c:  This is the function that calculates the period of the ADC buffer. This file is pre given and only incorporated in the code to compute and verify the period of the ADC buffer.
