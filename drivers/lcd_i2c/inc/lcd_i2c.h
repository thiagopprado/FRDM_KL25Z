/************************************************
 *  Author: Thiago Pereira do Prado             *
 *          thiagopereiraprado@gmail.com        *
 ************************************************/
/************************************************
 * This file maps the MKL25 registers
 ************************************************/
#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdlib.h>
#include "mkl25_registers.h"
#include "lcd_i2c_types.h"

lcd_i2c_err_t lcd_i2c_init (uint8_t i2c_addr, I2C_p i2c_p);
lcd_i2c_err_t lcd_i2c_cmd (uint8_t data);
lcd_i2c_err_t lcd_i2c_data (uint8_t data);

#endif /* LCD_I2C_H */
