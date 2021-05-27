/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    A7_Autotune.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "TPM0.h"
#include "DMA.h"
#include "sin.h"
#include "DAC.h"
#include "ADC.h"
#include <stdlib.h>
#include "systick.h"
#include "autocorrelate.h"



/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
	extern ticktime_t tick;

	uint16_t buffer_A4[SIZE_A4];
	uint16_t buffer_D5[SIZE_D5];
	uint16_t buffer_E5[SIZE_E5];
	uint16_t buffer_A5[SIZE_A5];
	extern uint16_t adc_buffer[SIZE];
	extern int16_t num_samples_pp, freq, samples_gen;

//changes the tone based on systick timer tick
//takes no arguments and return void
void change_tone(){
	//the input to the samples_generated function is the frequency of the wave
	switch(tick){
		case 0:	samples_generated(440);
				DMA_init(buffer_A4, SIZE_A4);
				start_DMA_transfer();
			break;
		case 1:	samples_generated(587);
				DMA_init(buffer_D5, SIZE_D5);
				start_DMA_transfer();
			break;
		case 2:	samples_generated(659);
				DMA_init(buffer_E5, SIZE_E5);
				start_DMA_transfer();
			break;
		case 3:	samples_generated(880);
				DMA_init(buffer_A5, SIZE_A5);
				start_DMA_transfer();
			break;
		}
	}

int main(void) {

  	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    //basic initialization
    uint16_t i, adc_freq;
    DAC_init();
    tone_to_samples(D5, buffer_D5);
    tone_to_samples(E5, buffer_E5);
    tone_to_samples(A5, buffer_A5);
    tone_to_samples(A4, buffer_A4);
    __enable_irq();
    DMA_init(buffer_A4, SIZE_A4);
    TPM0_init();
    start_TPM();
    start_DMA_transfer();
    ADC0_init();
    Init_SysTick();
    TPM1_init();

    /* Enter an infinite loop. */

    while(1){
    		//accumulating the ADC samples in the buffer
    		ADC0->SC1[0] = ADC_SC1_ADCH(23);
    		while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
    			;
    		adc_buffer[i] = ADC0->R[0];
    		i++;
    		if(i==SIZE){
    		//compute the period of adc buffer using autocorrelate
    		int period = autocorrelate_detect_period(&adc_buffer[0], 1024, kAC_16bps_unsigned);
    		adc_freq = ADC_TIMER_FREQ/period;
    		printf("\r\n samples generated = %d at %d Hz, computed period = %d samples", samples_gen, freq, num_samples_pp);
    		//compute min, max, and avg of the adc buffer
    		analyse_ADC_buff(adc_buffer);
    		printf(", period = %d, samples frequency = %u", period, adc_freq);
    		//change the tone
    		change_tone();
    		i=0;
    		}
    }
    return 0 ;
  }
