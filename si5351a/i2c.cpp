#include "i2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

I2C::I2C(i2c_inst_t *inst = &i2c0_inst, int sda_pin = PICO_DEFAULT_I2C_SDA_PIN, int scl_pin = PICO_DEFAULT_I2C_SCL_PIN, int baudrate = I2C_BR_FULLSPEED) : instance(inst)
{
    i2c_init(instance, baudrate);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    // Make the I2C pins available to picotool
    //bi_decl(bi_2pins_with_func(sda_pin, scl_pin, GPIO_FUNC_I2C));
}

int I2C::read_blocking(uint8_t addr, uint8_t *dst, size_t len, bool nostop)
{
    return i2c_read_blocking(instance, addr, dst, len, nostop);
}

int I2C::write_blocking(uint8_t addr, uint8_t *src, size_t len, bool nostop)
{
    return i2c_write_blocking(instance, addr, src, len, nostop);
}


