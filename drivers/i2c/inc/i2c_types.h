/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef I2C_TYPES_H
#define I2C_TYPES_H

typedef enum {
    I2C_ERR_NO_ERROR = 0,
    I2C_ERR_INVALID_ARGS,
    I2C_ERR_INVALID_MOD,
} i2c_err_t;

typedef enum {
    I2C_MOD_I2C0 = 0,
    I2C_MOD_I2C1,
    I2C_MOD_INVALID,
} i2c_mod_t;

typedef struct {
    uint8_t i2c_addr;
    uint8_t* message;
    uint8_t size;
} i2c_msg_t;

#endif /* I2C_TYPES_H */
