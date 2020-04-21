/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef I2C_DEFS_H
#define I2C_DEFS_H

#define SCGC4_I2C0_POS      (1 << 6)
#define SCGC4_I2C1_POS      (1 << 7)
#define I2C_C1_ENABLE       0x80
#define I2C_START           0x30            // Master + Transmit = START
#define I2C_WAIT            0x02
#define I2C_STOP            (~I2C_START)    // Slave + Receive = STOP

#ifndef PCR_MUX_POS
    #define PCR_MUX_POS     8
#endif /* PCR_MUX_POS */
#ifndef PCR_MUX_RESET
    #define PCR_MUX_RESET   (0x0007 << PCR_MUX_POS)
#endif /* PCR_MUX_RESET */

#endif /* I2C_DEFS_H */