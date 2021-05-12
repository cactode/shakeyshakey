#include "mbed.h"

//Registers.
constexpr uint8_t ADXL_DEVID_REG          = 0x00;
constexpr uint8_t ADXL_THRESH_TAP_REG     = 0x1D;
constexpr uint8_t ADXL_OFSX_REG           = 0x1E;
constexpr uint8_t ADXL_OFSY_REG           = 0x1F;
constexpr uint8_t ADXL_OFSZ_REG           = 0x20;
constexpr uint8_t ADXL_DUR_REG            = 0x21;
constexpr uint8_t ADXL_LATENT_REG         = 0x22;
constexpr uint8_t ADXL_WINDOW_REG         = 0x23;
constexpr uint8_t ADXL_THRESH_ACT_REG     = 0x24;
constexpr uint8_t ADXL_THRESH_INACT_REG   = 0x25;
constexpr uint8_t ADXL_TIME_INACT_REG     = 0x26;
constexpr uint8_t ADXL_ACT_INACT_CTL_REG  = 0x27;
constexpr uint8_t ADXL_THRESH_FF_REG      = 0x28;
constexpr uint8_t ADXL_TIME_FF_REG        = 0x29;
constexpr uint8_t ADXL_TAP_AXES_REG       = 0x2A;
constexpr uint8_t ADXL_ACT_TAP_STATUS_REG = 0x2B;
constexpr uint8_t ADXL_BW_RATE_REG        = 0x2C;
constexpr uint8_t ADXL_POWER_CTL_REG      = 0x2D;
constexpr uint8_t ADXL_INT_ENABLE_REG     = 0x2E;
constexpr uint8_t ADXL_INT_MAP_REG        = 0x2F;
constexpr uint8_t ADXL_INT_SOURCE_REG     = 0x30;
constexpr uint8_t ADXL_DATA_FORMAT_REG    = 0x31;
constexpr uint8_t ADXL_DATAX0_REG         = 0x32;
constexpr uint8_t ADXL_DATAX1_REG         = 0x33;
constexpr uint8_t ADXL_DATAY0_REG         = 0x34;
constexpr uint8_t ADXL_DATAY1_REG         = 0x35;
constexpr uint8_t ADXL_DATAZ0_REG         = 0x36;
constexpr uint8_t ADXL_DATAZ1_REG         = 0x37;
constexpr uint8_t ADXL_FIFO_CTL           = 0x38;
constexpr uint8_t ADXL_FIFO_STATUS        = 0x39;

//Data rate codes.
constexpr uint8_t ADXL_3200HZ             = 0x0F;
constexpr uint8_t ADXL_1600HZ             = 0x0E;
constexpr uint8_t ADXL_800HZ              = 0x0D;
constexpr uint8_t ADXL_400HZ              = 0x0C;
constexpr uint8_t ADXL_200HZ              = 0x0B;
constexpr uint8_t ADXL_100HZ              = 0x0A;
constexpr uint8_t ADXL_50HZ               = 0x09;
constexpr uint8_t ADXL_25HZ               = 0x08;
constexpr uint8_t ADXL_12HZ5              = 0x07;
constexpr uint8_t ADXL_6HZ25              = 0x06;

constexpr uint8_t ADXL_SPI_READ           = 0x80;
constexpr uint8_t ADXL_SPI_WRITE          = 0x00;
constexpr uint8_t ADXL_MULTI_BYTE         = 0x40;  // incorrect in original library, fixed here

constexpr uint8_t ADXL_X                  = 0x00;
constexpr uint8_t ADXL_Y                  = 0x01;
constexpr uint8_t ADXL_Z                  = 0x02;

enum class ADXL_RANGE {
    G_2 =  0b00,
    G_4 =  0b01,
    G_8 =  0b10,
    G_16 = 0b11
};

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
        void range(ADXL_RANGE range);
};