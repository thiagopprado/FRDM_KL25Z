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

/** Port Control and Interrupts - Chapter 11 */
typedef struct {
    volatile uint32_t PCR[32];      /**< Pin Control Register (R/W) */
    volatile uint32_t GPCLR;        /**< Global Pin Control Low Register (W) */
    volatile uint32_t GPCHR;        /**< Global Pin Control High Register (W) */
    uint8_t RESERVED_0[24];         /**< Reserved 24 Memory Bytes */
    volatile uint32_t ISFR;         /**< Interrupt Status Flag Register (R/W) */
} PORT_t, *PORT_p;

#define PORTA_base  0x40049000u
#define PORTB_base  0x4004A000u
#define PORTC_base  0x4004B000u
#define PORTD_base  0x4004C000u
#define PORTE_base  0x4004D000u

#define PORTA   	((PORT_p)PORTA_base)
#define PORTB   	((PORT_p)PORTB_base)
#define PORTC   	((PORT_p)PORTC_base)
#define PORTD   	((PORT_p)PORTD_base)
#define PORTE   	((PORT_p)PORTE_base)

/** System Integration Module - Chapter 12 */
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

#define SIM_base 	0x40047000u
#define SIM     	((SIM_p)SIM_base)

/** Multipurpose Clock Generator (MCG) - Chapter 24 */
typedef struct {
    volatile uint8_t C1;            /**< MCG Control 1 Register, offset: 0x0 */
    volatile uint8_t C2;            /**< MCG Control 2 Register, offset: 0x1 */
    volatile uint8_t C3;            /**< MCG Control 3 Register, offset: 0x2 */
    volatile uint8_t C4;            /**< MCG Control 4 Register, offset: 0x3 */
    volatile uint8_t C5;            /**< MCG Control 5 Register, offset: 0x4 */
    volatile uint8_t C6;            /**< MCG Control 6 Register, offset: 0x5 */
    volatile uint8_t S;             /**< MCG Status Register, offset: 0x6 */
    uint8_t RESERVED_0[1];
    volatile uint8_t SC;            /**< MCG Status and Control Register, offset: 0x8 */
    uint8_t RESERVED_1[1];
    volatile uint8_t ATCVH;         /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
    volatile uint8_t ATCVL;         /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
    volatile const uint8_t C7;      /**< MCG Control 7 Register, offset: 0xC */
    volatile uint8_t C8;            /**< MCG Control 8 Register, offset: 0xD */
    volatile const uint8_t C9;      /**< MCG Control 9 Register, offset: 0xE */
    volatile const uint8_t C10;     /**< MCG Control 10 Register, offset: 0xF */
} MCG_t, *MCG_p;

#define MCG_base  0x40064000u
#define MCG       ((MCG_p)MCG_base)

/** Oscillator (OSC) - Chapter 25 */
typedef struct {
    volatile uint8_t CR;            /**< OSC Control Register (R/W) */
} OSC_t, *OSC_p;

#define OSC0_base 0x40065000u
#define OSC0      ((OSC_p)OSC0_base)

/** Timer/PWM Module (TPM) - Chapter 31 */
typedef struct {
    volatile uint32_t SC;           /**< Status and Control (R/W) */
    volatile uint32_t CNT;          /**< Counter (R/W) */
    volatile uint32_t MOD;          /**< Modulo (R/W) */
    struct {
        volatile uint32_t CnSC;     /**< Channel Statis and Control (R/W) */
        volatile uint32_t CnV;      /**< Channel Value (R/W) */
    } CONTROLS[6];                  /**< Six Channels Registers */
    uint8_t RESERVED_0[20];
    volatile uint32_t STATUS;       /**< Capture and Compare Status (R/W) */
    uint8_t RESERVED_1[48];
    volatile uint32_t CONF;         /**< Configuration (R/W) */
} TPM_t, *TPM_p;

#define TPM0_base  0x40038000u
#define TPM1_base  0x40039000u
#define TPM2_base  0x4003A000u

#define TPM0       ((TPM_p)TPM0_base)
#define TPM1       ((TPM_p)TPM1_base)
#define TPM2       ((TPM_p)TPM2_base)

/** Inter-Integrated Circuit (I2C) - Chapter 38 */
typedef struct {
    volatile uint8_t A1;           /**< Address Register 1 (R/W) */
    volatile uint8_t F;            /**< Frequency Divider (R/W) */
    volatile uint8_t C1;           /**< Control Register 1 (R/W) */
    volatile uint8_t S;            /**< Status Register (R/W) */
    volatile uint8_t D;            /**< Data I/O Register (R/W) */
    volatile uint8_t C2;           /**< Control Register 2 (R/W) */
    volatile uint8_t FLT;          /**< Programmable Input Glitch Filter Register (R/W) */
    volatile uint8_t RA;           /**< Range Address Register (R/W) */
    volatile uint8_t SMB;          /**< SMBus Control and Status Register (R/W) */
    volatile uint8_t A2;           /**< Address Register 2 (R/W) */
    volatile uint8_t SLTH;         /**< SCL Low Timeout Register High (R/W) */
    volatile uint8_t SLTL;         /**< SCL Low Timeout Register Low (R/W) */
} I2C_t, *I2C_p;

#define I2C0_base  0x40066000u
#define I2C1_base  0x40067000u

#define I2C0       ((I2C_p)I2C0_base)
#define I2C1       ((I2C_p)I2C1_base)

/** General-Purpose Input/Output (GPIO) - Chapter 41 */
typedef struct {
    volatile uint32_t PDOR;         /**< Port Data Output Register (R/W) */
    volatile uint32_t PSOR;         /**< Port Set Output Register (W) */
    volatile uint32_t PCOR;         /**< Port Clear Output Register (W) */
    volatile uint32_t PTOR;         /**< Port Toggle Output Register (W) */
    volatile const uint32_t PDIR;   /**< Port Data Input Register (R) */
    volatile uint32_t PDDR;         /**< Port Data Direction Register (R/W) */
} GPIO_t, *GPIO_p;

#define GPIOA_base  0x400FF000u
#define GPIOB_base  0x400FF040u
#define GPIOC_base  0x400FF080u
#define GPIOD_base  0x400FF0C0u
#define GPIOE_base  0x400FF100u

#define GPIOA       ((GPIO_p)GPIOA_base)
#define GPIOB       ((GPIO_p)GPIOB_base)
#define GPIOC       ((GPIO_p)GPIOC_base)
#define GPIOD       ((GPIO_p)GPIOD_base)
#define GPIOE       ((GPIO_p)GPIOE_base)

#endif /* MKL25_REGISTERS_H */
