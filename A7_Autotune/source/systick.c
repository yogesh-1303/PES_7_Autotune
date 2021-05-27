#include <stdio.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include "core_cm0plus.h"
#include "systick.h"
#include "sin.h"

ticktime_t tick = 0;
ticktime_t temp = 0;
//extern uint16_t buffer[STEPS];
//extern uint16_t samples;

//Systick timer initialization
void Init_SysTick()
{
	SysTick->LOAD = (48000000L/16);				//for 1s res
	NVIC_SetPriority (SysTick_IRQn, 1);
	SysTick->VAL = 0;							//Initial value of counter
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk); 		//frequency = 3Mhz (ext clock)
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; //enable interrupt
}

//interrupt handler
void SysTick_Handler()
{
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	tick ++;
	if(tick>3)
		tick=0;

}



