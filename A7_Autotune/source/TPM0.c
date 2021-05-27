#include <stdio.h>
#include "MKL25Z4.h"
#include "TPM0.h"
#include <stdint.h>
#include "DMA.h"
#include "DAC.h"


//initializes the TPM0 clock for DMA transfer at 48Khz
//Provides clock, sets MOD and presaclar values, and enables DMA request
//takes no arguments and returns void
void TPM0_init(){
	//Providing clocks to ports and TMP0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK); //Enable TPM clock
	//disable TPM
	TPM0->SC = 0;
	//TPM0 MOD for 48Khz operation
	TPM0->MOD = (CLK_FREQ/DMA_SAMPLE_FREQ) - 1;
	//set prescaler=1, enable DMA
	TPM0->SC = TPM_SC_DMA_MASK | TPM_SC_PS(0);
}

//starts the TPM0 timer
//takes no arguments and returns void
void start_TPM(){
	//Enable TPM0 counter
	TPM0->SC |= TPM_SC_CMOD(1);
}


