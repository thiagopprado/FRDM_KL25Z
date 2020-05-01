/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef I2C_H
#define I2C_H

#include <stdlib.h>
#include "mkl25_registers.h"
#include "i2c_types.h"

/**<
 * PORT's must be setup before I2C
 *
 * Example:
 *
 * SIM->SCGC5 |= (1 << 10); // PORTB Clock gate
 * PORTB->PCR[0] = (PORTB->PCR[0] & ~(7 << 8)) | (2 << 8); // MUX PORTB0 SCL I2C0
 * PORTB->PCR[1] = (PORTB->PCR[1] & ~(7 << 8)) | (2 << 8); // MUX PORTB1 SDA I2C0
 *
 */

i2c_err_t i2c_setup(i2c_mod_t i2c_mod, uint8_t f_divider);
i2c_err_t i2c_transmit(I2C_p i2c_ptr, i2c_msg_t* i2c_msg);

#endif /* I2C_H */
