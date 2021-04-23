#include "hw_init.h"

void HW_init() {
    MX_DMA_Init();   // Initializes DMA for transferring TIM2 data
    MX_DAC_Init();   // Initializes DAC w/ DMA capabilities
    MX_TIM2_Init();     // Initializes simple timer for running DMA
    MX_TIM3_Init();
}
