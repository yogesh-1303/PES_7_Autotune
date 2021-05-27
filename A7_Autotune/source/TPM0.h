#define CLK_FREQ			(48000000L)
#define DMA_SAMPLE_FREQ		(48000)

//intialization function, configures the TPM0: sets clock,
//MOD, prescaler, etc values and enables the DMA
void TPM0_init();

//sets the value of CMOD to start the TPM0 timer
void start_TPM();



