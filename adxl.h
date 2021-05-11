#include "mbed.h"

//Registers.
constexpr uint8_t ADXL345_DEVID_REG          = 0x00;
constexpr uint8_t ADXL345_THRESH_TAP_REG     = 0x1D;
constexpr uint8_t ADXL345_OFSX_REG           = 0x1E;
constexpr uint8_t ADXL345_OFSY_REG           = 0x1F;
constexpr uint8_t ADXL345_OFSZ_REG           = 0x20;
constexpr uint8_t ADXL345_DUR_REG            = 0x21;
constexpr uint8_t ADXL345_LATENT_REG         = 0x22;
constexpr uint8_t ADXL345_WINDOW_REG         = 0x23;
constexpr uint8_t ADXL345_THRESH_ACT_REG     = 0x24;
constexpr uint8_t ADXL345_THRESH_INACT_REG   = 0x25;
constexpr uint8_t ADXL345_TIME_INACT_REG     = 0x26;
constexpr uint8_t ADXL345_ACT_INACT_CTL_REG  = 0x27;
constexpr uint8_t ADXL345_THRESH_FF_REG      = 0x28;
constexpr uint8_t ADXL345_TIME_FF_REG        = 0x29;
constexpr uint8_t ADXL345_TAP_AXES_REG       = 0x2A;
constexpr uint8_t ADXL345_ACT_TAP_STATUS_REG = 0x2B;
constexpr uint8_t ADXL345_BW_RATE_REG        = 0x2C;
constexpr uint8_t ADXL345_POWER_CTL_REG      = 0x2D;
constexpr uint8_t ADXL345_INT_ENABLE_REG     = 0x2E;
constexpr uint8_t ADXL345_INT_MAP_REG        = 0x2F;
constexpr uint8_t ADXL345_INT_SOURCE_REG     = 0x30;
constexpr uint8_t ADXL345_DATA_FORMAT_REG    = 0x31;
constexpr uint8_t ADXL345_DATAX0_REG         = 0x32;
constexpr uint8_t ADXL345_DATAX1_REG         = 0x33;
constexpr uint8_t ADXL345_DATAY0_REG         = 0x34;
constexpr uint8_t ADXL345_DATAY1_REG         = 0x35;
constexpr uint8_t ADXL345_DATAZ0_REG         = 0x36;
constexpr uint8_t ADXL345_DATAZ1_REG         = 0x37;
constexpr uint8_t ADXL345_FIFO_CTL           = 0x38;
constexpr uint8_t ADXL345_FIFO_STATUS        = 0x39;

//Data rate codes.
constexpr uint8_t ADXL345_3200HZ      = 0x0F;
constexpr uint8_t ADXL345_1600HZ      = 0x0E;
constexpr uint8_t ADXL345_800HZ       = 0x0D;
constexpr uint8_t ADXL345_400HZ       = 0x0C;
constexpr uint8_t ADXL345_200HZ       = 0x0B;
constexpr uint8_t ADXL345_100HZ       = 0x0A;
constexpr uint8_t ADXL345_50HZ        = 0x09;
constexpr uint8_t ADXL345_25HZ        = 0x08;
constexpr uint8_t ADXL345_12HZ5       = 0x07;
constexpr uint8_t ADXL345_6HZ25       = 0x06;

constexpr uint8_t ADXL345_SPI_READ    = 0x80;
constexpr uint8_t ADXL345_SPI_WRITE   = 0x00;
constexpr uint8_t ADXL345_MULTI_BYTE  = 0x40;  // incorrect in original library, fixed here

constexpr uint8_t ADXL345_X           = 0x00;
constexpr uint8_t ADXL345_Y           = 0x01;
constexpr uint8_t ADXL345_Z           = 0x02;

class ADXL {
    private:
        SPI _spi;
        DigitalOut _cs;
    public:
        ADXL(PinName mosi, PinName miso, PinName sck, PinName cs) : _spi{mosi, miso, sck}, _cs{cs} {
            _spi.frequency(5e6);
            _spi.format(8, 3);
            _cs = 0;
        }
        void init();
        uint8_t read_single(uint8_t reg);
        int16_t read_y();
        void write(uint8_t reg, uint8_t value);
};