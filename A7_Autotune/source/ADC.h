
#define ADC_TIMER_FREQ  (96000)

//initializes the TPM1 timer for operating at 96000 KHz frquency
void TPM1_init();

//initializes the ADC0 module for converting the data coming from DAC
void ADC0_init();

void print_buffer();

//calculates the minimum, maximum and average sample values in the buffer
//takes a buffer of type uint16_t as the argument
//returns void
void analyse_ADC_buff(uint16_t *);

