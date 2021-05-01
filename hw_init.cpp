#include "hw_init.h"

static BufferedSerial pc{PA_2, PA_3, 115200};
FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}
void HW_init() {
    MX_DMA_Init();   // Initializes DMA for transferring TIM2 data
    MX_DAC_Init();   // Initializes DAC w/ DMA capabilities
    MX_TIM2_Init();  // Initializes simple timer for running DMA
    MX_TIM3_Init();  // Initializes simple timer for running SPI collection interrupts
}
