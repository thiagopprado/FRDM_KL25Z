#include "gpio.h"
#include "gpio-defs.h"

gpio_err_t gpio_init(gpio_port_t gpio_port) {

    switch (gpio_port) {
        case GPIO_PORTA:
            SIM->SCGC5 |= SCG5_PORTA_POS;
        break;
        case GPIO_PORTB:
            SIM->SCGC5 |= SCG5_PORTB_POS;
        break;
        case GPIO_PORTC:
            SIM->SCGC5 |= SCG5_PORTC_POS;
        break;
        case GPIO_PORTD:
            SIM->SCGC5 |= SCG5_PORTD_POS;
        break;
        case GPIO_PORTE:
            SIM->SCGC5 |= SCG5_PORTE_POS;
        break;
        default:
            return GPIO_ERR_INVALID_PORT;
    }

    return GPIO_ERR_NO_ERROR;
}

gpio_err_t gpio_mode(gpio_port_t gpio_port, gpio_mode_t mode, uint8_t pin) {
    PORT_p port_ptr = NULL;
    GPIO_p gpio_ptr = NULL;
    
    if (pin >= PORT_MAX_CH_NR) {
        return GPIO_ERR_INVALID_ARGS;
    }

    switch (gpio_port) {
        case GPIO_PORTA:
            port_ptr = PORTA;
            gpio_ptr = GPIOA;
        break;
        case GPIO_PORTB:
            port_ptr = PORTB;
            gpio_ptr = GPIOB;
        break;
        case GPIO_PORTC:
            port_ptr = PORTC;
            gpio_ptr = GPIOC;
        break;
        case GPIO_PORTD:
            port_ptr = PORTD;
            gpio_ptr = GPIOD;
        break;
        case GPIO_PORTE:
            port_ptr = PORTE;
            gpio_ptr = GPIOE;
        break;
        default:
            return GPIO_ERR_INVALID_PORT;
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

gpio_err_t gpio_write(GPIO_p gpio_ptr, gpio_value_t value, uint8_t pin) {
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

inline void gpio_set(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PSOR = (uint32_t)1 << pin;
}

inline void gpio_clear(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PCOR = (uint32_t)1 << pin;
}

inline void gpio_toggle(GPIO_p gpio_ptr, uint8_t pin) {
    gpio_ptr->PTOR = (uint32_t)1 << pin;
}

inline gpio_value_t gpio_read(GPIO_p gpio_ptr, uint8_t pin) {
    return (gpio_ptr->PDIR & ((uint32_t) 1 << pin)) != 0;
}
