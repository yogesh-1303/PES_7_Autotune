#define DAC_POS 30

//Initializes the DAC0 module
//provides clock to DAC0 and pin 30 at PORTE
//make the PORTE pin 30 analog and disables buffer mode
//Enables the DAC0 providing the reference clock
void DAC_init();
