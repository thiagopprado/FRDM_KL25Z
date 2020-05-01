/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef MMA8451Q_TYPES_H
#define MMA8451Q_TYPES_H

#include "i2c_types.h"
#include "mma8451q-defs.h"

typedef enum {
    MMA8451Q_ERR_NO_ERROR = 0,
    MMA8451Q_ERR_INVALID_ARGS,
} mma8451q_err_t;

typedef enum {
    MMA8451Q_RANGE_2G = 0,
    MMA8451Q_RANGE_4G,
    MMA8451Q_RANGE_8G,
    MMA8451Q_RANGE_INVALID,
} mma8451q_range_t;

typedef enum {
    MMA8451Q_AXIS_X = MMA8451Q_OUT_X,
    MMA8451Q_AXIS_Y = MMA8451Q_OUT_Y,
    MMA8451Q_AXIS_Z = MMA8451Q_OUT_Z,
    MMA8451Q_AXIS_INVALID,
} mma8451q_axis_t;

typedef struct {
    int16_t x, y, z;
} mma8451q_values_t;

typedef struct {
    i2c_msg_t i2c_message;
    I2C_p i2c_ptr;
    uint8_t tx_data[MMA8451Q_MAX_TX_SIZE];
    uint8_t rx_data[MMA8451Q_MAX_RX_SIZE];
} mma8451q_ctl_t;

#endif /* MMA8451Q_TYPES_H */
