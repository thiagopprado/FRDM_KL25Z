/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

#define SCG5_PORTA_POS      (1 << 9)
#define SCG5_PORTB_POS      (1 << 10)
#define SCG5_PORTC_POS      (1 << 11)
#define SCG5_PORTD_POS      (1 << 12)
#define SCG5_PORTE_POS      (1 << 13)

#define PORT_MAX_CH_NR      32
#define PCR_MUX_POS         8
#define PCR_MUX_RESET       (0x0007 << PCR_MUX_POS)
#define PCR_MUX_GPIO        (0x0001 << PCR_MUX_POS)
#define PCR_PULL_RESET      (0x0003)
#define PCR_PULL_UP         (0x0003)
#define PCR_PULL_DOWN       (0x0002)

#endif /* GPIO_DEFS_H */