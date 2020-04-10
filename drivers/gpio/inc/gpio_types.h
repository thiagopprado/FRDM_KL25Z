/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

typedef enum {
    GPIO_ERR_NO_ERROR = 0,
    GPIO_ERR_INVALID_ARGS,    
    GPIO_ERR_INVALID_PORT,    
    GPIO_ERR_INVALID_GPIO,    
    GPIO_ERR_INVALID_VALUE,    
} gpio_err_t;

typedef enum {
    GPIO_MODE_OUTPUT = 0,
    GPIO_MODE_INPUT,
    GPIO_MODE_INPUT_PULL_UP,
    GPIO_MODE_INPUT_PULL_DOWN,
    GPIO_MODE_INVALID,
} gpio_mode_t;

typedef enum {
    GPIO_VALUE_LOW = 0,
    GPIO_VALUE_HIGH,
    GPIO_VALUE_INVALID,
} gpio_value_t;

typedef enum {
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
} gpio_port_t;

#endif /* GPIO_TYPES_H */