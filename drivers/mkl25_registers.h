/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef MKL25_REGISTERS_H
#define MKL25_REGISTERS_H

#include <stdint.h>

/** Port control and interrupts - Chapter 11 */
typedef struct {
    volatile uint32_t PCR[32];  /**< Pin control register (R/W) */
    volatile uint32_t GPCLR;    /**< Global Pin Control Low Register (W) */
    volatile uint32_t GPCHR;    /**< Global Pin Control High Register (W) */
    uint8_t RESERVED_0[24];     /**< Reserved 24 memory bytes */
    volatile uint32_t ISFR;     /**< Interrupt Status Flag Register (R/W) */
} PORT_t, *PORT_p;

#define PORTA   ((PORT_p)0x40049000u)
#define PORTB   ((PORT_p)0x4004A000u)
#define PORTC   ((PORT_p)0x4004B000u)
#define PORTD   ((PORT_p)0x4004C000u)
#define PORTE   ((PORT_p)0x4004D000u)

#endif /* MKL25_REGISTERS_H */