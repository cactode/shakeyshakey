#include "hw_init.h"

// set serial to max speed
static BufferedSerial pc{PA_2, PA_3, 115200};
FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}

void HW_init() {
    MX_DMA_Init();   // Initializes DMA for transferring TIM2 data
    MX_DAC_Init();   // Initializes DAC w/ DMA capabilities
    MX_TIM2_Init();  // Initializes simple timer for running DMA
    MX_TIM3_Init();  // Initializes simple timer for running SPI collection interrupts
    ADXL_init();     // Initializes accelerometer, enables measurements
    sinLUT_init();   // Initializes sine wave lookup table, not hardware but close enough
    MAX_init();      // Initializes amplifier, sets volume to zero
}
