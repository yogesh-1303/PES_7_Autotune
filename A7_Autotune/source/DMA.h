

//initializes the DMA (clock gating to DMA and DMAMUX, setting
//source and destination byte size to transfer at once, sets
//values as source addr increments but destination addr is same
//sets for interrupt and DMAMUX for TPM0)
void DMA_init(uint16_t *, uint32_t);

//sets source address, destination address, number of bytes to
//transfer, clears done flag and enables the flag
void start_DMA_transfer();

