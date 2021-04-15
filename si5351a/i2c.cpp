#include "i2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"


I2C::I2C(i2c_inst_t inst=i2c0_inst, int sda_pin=PICO_DEFAULT_I2C_SDA_PIN, int scl_pin=PICO_DEFAULT_I2C_SCL_PIN, int baudrate=I2C_BR_FULLSPEED)
{
    i2c_init(&inst, baudrate);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    // Make the I2C pins available to picotool
    //bi_decl( bi_2pins_with_func(sda_pi, scl_pin, GPIO_FUNC_I2C));


}