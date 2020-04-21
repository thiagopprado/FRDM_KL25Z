/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef LCD_I2C_TYPES_H
#define LCD_I2C_TYPES_H

typedef enum {
    LCD_I2C_ERR_NO_ERROR = 0,
    LCD_I2C_ERR_INVALID_ARGS,
    LCD_I2C_ERR_TRX_FAIL,
} lcd_i2c_err_t;

#endif /* LCD_I2C_TYPES_H */
