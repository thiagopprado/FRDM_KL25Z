#include "gpio.h"

gpio_err_t gpio_init(PORT_p port_ptr) {
    if (port_ptr == NULL) {
        return GPIO_ERR_INVALID_ARGS;
    }

    switch (port_ptr) {
        case PORTA:
            SIM->SCGC5 |= SCG5_PORTA_POS;
        break;
        case PORTB:
            SIM->SCGC5 |= SCG5_PORTB_POS;
        break;
        case PORTC:
            SIM->SCGC5 |= SCG5_PORTC_POS;
        break;
        case PORTD:
            SIM->SCGC5 |= SCG5_PORTD_POS;
        break;
        case PORTE:
            SIM->SCGC5 |= SCG5_PORTE_POS;
        break;
        default:
            return GPIO_ERR_INVALID_PORT;
    }

    return GPIO_ERR_NO_ERROR;
}

gpio_err_t gpio_mode(GPIO_p gpio_ptr, gpio_mode_t mode, uint8_t pin) {
    PORT_p port_ptr = NULL;
    
    if (gpio_ptr == NULL || pin >= PORT_MAX_CH_NR) {
        return GPIO_ERR_INVALID_ARGS;
    }

    switch (gpio_ptr) {
        case GPIOA:
            port_ptr = PORTA;
        break;
        case GPIOB:
            port_ptr = PORTB;
        break;
        case GPIOC:
            port_ptr = PORTC;
        break;
        case GPIOD:
            port_ptr = PORTD;
        break;
        case GPIOE:
            port_ptr = PORTE;
        break;
        default:
            return GPIO_MODE_INVALID;
    }

    port_ptr->PCR[pin] &= ~PCR_MUX_RESET;
    port_ptr->PCR[pin] |= PCR_MUX_GPIO;

    port_ptr->PCR[pin] &= ~PCR_PULL_RESET;

    switch (mode) {
        case GPIO_MODE_OUTPUT:
            gpio_ptr->PDDR |= (1 << pin);
            break;
        case GPIO_MODE_INPUT:
            gpio_ptr->PDDR &= ~(1 << pin);
            break;
        case GPIO_MODE_INPUT_PULL_UP:
            gpio_ptr->PDDR &= ~(1 << pin);
            port_ptr->PCR[pin] |= PCR_PULL_UP;
            break;
        case GPIO_MODE_INPUT_PULL_DOWN:
            gpio_ptr->PDDR &= ~(1 << pin);
            port_ptr->PCR[pin] |= PCR_PULL_DOWN;
            break;
        default:
            return GPIO_MODE_INVALID;
    }

    return GPIO_ERR_NO_ERROR;
}

inline gpio_err_t gpio_write(GPIO_p gpio_ptr, gpio_value_t value, uint8_t pin) {
    if (gpio_ptr == NULL || pin >= PORT_MAX_CH_NR) {
        return GPIO_ERR_INVALID_ARGS;
    }
    
    switch (value) {
        case GPIO_VALUE_LOW:
            gpio_ptr->PDOR &= ~((uint32_t)1 << pin);
        break;
        case GPIO_VALUE_HIGH:
            gpio_ptr->PDOR |= (uint32_t)1 << pin;
        break;
        default:
            return GPIO_ERR_INVALID_VALUE;
    }
    
    return GPIO_ERR_NO_ERROR;
}

inline gpio_err_t gpio_set(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PSOR = (uint32_t)1 << pin;
    return GPIO_ERR_NO_ERROR;
}

inline gpio_err_t gpio_clear(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PCOR = (uint32_t)1 << pin;
    return GPIO_ERR_NO_ERROR;
}

inline gpio_err_t gpio_toggle(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PTOR = (uint32_t)1 << pin;
    return GPIO_ERR_NO_ERROR;
}

inline gpio_err_t gpio_read(GPIO_p gpio_ptr, gpio_value_t* value, uint8_t pin) {
    *value = (gpio_ptr->PDIR & (uint32_t) 1 << pin) != 0;
}
