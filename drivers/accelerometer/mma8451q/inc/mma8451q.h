/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef MMA8451Q_H
#define MMA8451Q_H

#include <stdlib.h>
#include "mkl25_registers.h"
#include "mma8451q_types.h"

/**<
 * PTE24 - SCL - I2C0
 * PTE25 - SDA - I2C0
 * PTA14 - INT1
 * PTA15 - INT2
 *
 * PORT's and I2C must be setup before Accelerometer
 *
 * Example:
 *
 * SIM->SCGC5 |= (1 << 13); // PORTE Clock gate
 * PORTE->PCR[24] = (PORTE->PCR[24] & ~(7 << 8)) | (5 << 8); // MUX PORTE24 SCL I2C0
 * PORTE->PCR[25] = (PORTE->PCR[25] & ~(7 << 8)) | (5 << 8); // MUX PORTE25 SDA I2C0
 *
 */

mma8451q_err_t mma8451q_setup(uint8_t i2c_addr, mma8451q_range_t range, I2C_p i2c_ptr);
int16_t mma8451q_read(mma8451q_axis_t axis);
mma8451q_err_t mma8451q_read_all(mma8451q_values_t* values);

#endif /* MMA8451Q_H */
