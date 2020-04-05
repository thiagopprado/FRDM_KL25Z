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
    volatile uint32_t PCR[32];      /**< Pin Control Register (R/W) */
    volatile uint32_t GPCLR;        /**< Global Pin Control Low Register (W) */
    volatile uint32_t GPCHR;        /**< Global Pin Control High Register (W) */
    uint8_t RESERVED_0[24];         /**< Reserved 24 Memory Bytes */
    volatile uint32_t ISFR;         /**< Interrupt Status Flag Register (R/W) */
} PORT_t, *PORT_p;

#define PORTA   ((PORT_p)0x40049000u)
#define PORTB   ((PORT_p)0x4004A000u)
#define PORTC   ((PORT_p)0x4004B000u)
#define PORTD   ((PORT_p)0x4004C000u)
#define PORTE   ((PORT_p)0x4004D000u)

/** System integration module - Chapter 12 */
typedef struct {
    volatile uint32_t SOPT1;        /**< System Options Register 1 (R/W) */
    volatile uint32_t SOPT1CFG;     /**< System Configuration Register 1 (R/W) */
    uint8_t RESERVED_0[4092];
    volatile uint32_t SOPT2;        /**< System Options Register 2 (R/W) */
    uint8_t RESERVED_1[4];
    volatile uint32_t SOPT4;        /**< System Options Register 4 (R/W) */
    volatile uint32_t SOPT5;        /**< System Options Register 5 (R/W) */
    uint8_t RESERVED_2[4];
    volatile uint32_t SOPT7;        /**< System Options Register 7 (R/W) */
    uint8_t RESERVED_3[8];
    volatile const uint32_t SDID;   /**< System Device Identification Register (R) */
    uint8_t RESERVED_4[12];
    volatile uint32_t SCGC4;        /**< System Clock Gating Control Register 4 (R/W) */
    volatile uint32_t SCGC5;        /**< System Clock Gating Control Register 5 (R/W) */
    volatile uint32_t SCGC6;        /**< System Clock Gating Control Register 6 (R/W) */
    volatile uint32_t SCGC7;        /**< System Clock Gating Control Register 7 (R/W) */
    volatile uint32_t CLKDIV1;      /**< System Clock Divider Register 1 (R/W) */
    uint8_t RESERVED_5[4];
    volatile uint32_t FCFG1;        /**< Flash Configuration Register 1 (R/W) */
    volatile const uint32_t FCFG2;  /**< Flash Configuration Register 2 (R) */
    uint8_t RESERVED_6[4];
    volatile const uint32_t UIDMH;  /**< Unique Identification Register Mid-High (R) */
    volatile const uint32_t UIDML;  /**< Unique Identification Register Mid-Low (R) */
    volatile const uint32_t UIDL;   /**< Unique Identification Register Low~> (R) */
    uint8_t RESERVED_7[156];
    volatile uint32_t COPC;         /**< COP Control Register (R/W) */
    volatile uint32_t SRVCOP;       /**< Service COP Register (W) */
} SIM_t, *SIM_p;

#define SIM     ((SIM_p)0x40047000u)

#endif /* MKL25_REGISTERS_H */