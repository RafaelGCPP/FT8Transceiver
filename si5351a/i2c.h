#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#define I2C_BR_STANDARD 100000
#define I2C_BR_FULLSPEED 400000
#define I2C_BR_FASTMODE 1000000

class I2C {
    public:
        I2C(i2c_inst_t *inst, int sda_pin, int scl_pin, int baudrate);
        int read_blocking(uint8_t addr, uint8_t *dst, size_t len, bool nostop);
        int write_blocking(uint8_t addr, uint8_t *src, size_t len, bool nostop);
    private:
        i2c_inst_t *instance;
};