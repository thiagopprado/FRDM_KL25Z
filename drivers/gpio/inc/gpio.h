/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>
#include "mkl25_registers.h"
#include "gpio_types.h"

gpio_err_t gpio_init(gpio_port_t gpio_port);
gpio_err_t gpio_mode(gpio_port_t gpio_port, gpio_mode_t mode, uint8_t pin);
gpio_err_t gpio_write(GPIO_p gpio_ptr, gpio_value_t value, uint8_t pin);
void gpio_set(GPIO_p gpio_ptr, uint8_t pin);
void gpio_clear(GPIO_p gpio_ptr, uint8_t pin);
void gpio_toggle(GPIO_p gpio_ptr, uint8_t pin);
gpio_value_t gpio_read(GPIO_p gpio_ptr, uint8_t pin);

#endif /* GPIO_H */
