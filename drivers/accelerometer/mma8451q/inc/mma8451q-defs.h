/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef MMA8451Q_DEFS_H
#define MMA8451Q_DEFS_H

#define MMA8451Q_CTRL_REG1              0x2A

#define MMA8451Q_CTRL_REG1_STD_BY       0x00
#define MMA8451Q_CTRL_REG1_ACTIVE       0x01
#define MMA8451Q_CTRL_REG1_FAST_READ    0x02
#define MMA8451Q_CTRL_REG1_LOW_NOISE    0x04
#define MMA8451Q_CTRL_REG1_800_HZ       (0x00 << 3)
#define MMA8451Q_CTRL_REG1_400_HZ       (0x01 << 3)
#define MMA8451Q_CTRL_REG1_200_HZ       (0x02 << 3)
#define MMA8451Q_CTRL_REG1_100_HZ       (0x03 << 3)
#define MMA8451Q_CTRL_REG1_50_HZ        (0x04 << 3)
#define MMA8451Q_CTRL_REG1_12_5_HZ      (0x05 << 3)
#define MMA8451Q_CTRL_REG1_6_25_HZ      (0x06 << 3)
#define MMA8451Q_CTRL_REG1_1_56_HZ      (0x07 << 3)

#define MMA8451Q_XYZ_DATA_CFG           0x0E

#define MMA8451Q_OUT_X                  0x01
#define MMA8451Q_OUT_Y                  0x03
#define MMA8451Q_OUT_Z                  0x05

#define MMA8451Q_MAX_TX_SIZE            2
#define MMA8451Q_MAX_RX_SIZE            6


#ifndef PCR_MUX_POS
    #define PCR_MUX_POS     8
#endif /* PCR_MUX_POS */
#ifndef PCR_MUX_RESET
    #define PCR_MUX_RESET   (0x0007 << PCR_MUX_POS)
#endif /* PCR_MUX_RESET */

#endif /* MMA8451Q_DEFS_H */
