#include <stdio.h>
#include "MKL25Z4.h"
#include "sin.h"


#define ADC_SIZE	(65535)
#define ADC_POS 	23

uint16_t adc_buffer[SIZE];

//initializes the TPM1 timer for operating at 96000 KHz frquency
void TPM1_init(){
	//Providing clocks to ports and TMP0
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	//enable clock
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//set MOD and prescalar according to 96KHz frequency
	TPM1->SC = 0;
	TPM1->MOD = 500-1;
	TPM1->SC |= TPM_SC_PS(0);
	//set debug mode
	TPM1->CONF |= TPM_CONF_DBGMODE(3);
	//start timer
	TPM1->SC |= TPM_SC_CMOD(1);
}

//initializes the ADC0 module for converting the data coming from DAC
void ADC0_init(){
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	//select analog pin
	PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);
	//clock is busclock/2 and ADIV=2
	ADC0->CFG1 &= ~ADC_CFG1_ADLPC_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADIV(1) | ADC_CFG1_MODE(3) |
			ADC_CFG1_ADICLK(1);
	//select default reference clock
	ADC0->SC2 = ADC_SC2_REFSEL(0) | ADC_SC2_ADTRG_MASK;
	//configure for hardware trigger with TPM1
	SIM->SOPT7 &= ~SIM_SOPT7_ADC0PRETRGSEL_MASK;
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN_MASK |
			SIM_SOPT7_ADC0TRGSEL(9);
}

//calculates the minimum, maximum and average sample values in the buffer
//takes a buffer of type uint16_t as the argument
//returns void
void analyse_ADC_buff(uint16_t *buff){
	uint16_t min_index=0, max_index=0, avg_val=0;
	uint32_t sum=0;
	for (uint16_t i=0; i<SIZE; i++){
		if(buff[i]<buff[min_index])
			min_index = i;
		if(buff[i]>buff[max_index])
			max_index = i;
		sum += buff[i];
		}
	//avg = sum of buff values / total size
	avg_val = sum/SIZE;
	printf("\r\nMIN = %u, MAX = %u, AVG = %u", buff[min_index], buff[max_index], avg_val);
}













