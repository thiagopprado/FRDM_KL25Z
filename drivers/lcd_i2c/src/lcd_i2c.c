#include "i2c.h"
#include "lcd_i2c.h"
#include "lcd_i2c-defs.h"
#include "gpio.h"

uint8_t msg = 0;
i2c_msg_t lcd_i2c_msg = { 0 };
I2C_p i2c_ptr = NULL;

static inline void delay_5ms(void);
static inline void delay_10us(void);
static inline lcd_i2c_err_t lcd_i2c_pulse(uint8_t data);

lcd_i2c_err_t lcd_i2c_init (uint8_t i2c_addr, I2C_p i2c_p) {
    i2c_err_t i2c_err = I2C_ERR_NO_ERROR;
    lcd_i2c_err_t lcd_i2c_err = LCD_I2C_ERR_NO_ERROR;
    uint16_t i = 0;

    if (i2c_p == NULL) {
        return LCD_I2C_ERR_INVALID_ARGS;
    }

    i2c_ptr = i2c_p;
    lcd_i2c_msg.i2c_addr = i2c_addr;
    lcd_i2c_msg.tx_data = &msg;
    lcd_i2c_msg.tx_size = LCD_I2C_TRX_SIZE;
    lcd_i2c_msg.read = false;

    // Wait 50ms for LCD to start
    for (i = 0; i < 10; i++) {
        delay_5ms();
    }

    msg = LCD_I2C_L; // Only Backlight ON
    i2c_err = i2c_write(i2c_ptr, &lcd_i2c_msg);
    if (i2c_err != I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    // 1s
    for (i = 0; i < 200; i++) {
        delay_5ms();
    }

    // Try to switch to 8 bits mode
    lcd_i2c_err = lcd_i2c_pulse(0x30);
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    delay_5ms();

    // Second Try
    lcd_i2c_err = lcd_i2c_pulse(0x30);
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    delay_5ms();

    // Third Try
    lcd_i2c_err = lcd_i2c_pulse(0x30);
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    delay_5ms();

    // 4 bits mode
    lcd_i2c_err = lcd_i2c_pulse(0x20);
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    lcd_i2c_err = lcd_i2c_cmd(0x28); // 4 bits, 2 lines, 5x8
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    
    lcd_i2c_err = lcd_i2c_cmd(0x06); // incremental
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    
    lcd_i2c_err = lcd_i2c_cmd(0x0C); // display on, cursor and blinking off
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    
    lcd_i2c_err = lcd_i2c_cmd(0x03); // zera contadores internos
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }
    
    lcd_i2c_err = lcd_i2c_cmd(0x01); // limpar display  
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    delay_5ms();

    return LCD_I2C_ERR_NO_ERROR;
}

lcd_i2c_err_t lcd_i2c_cmd (uint8_t data) {    
	lcd_i2c_err_t lcd_i2c_err = LCD_I2C_ERR_NO_ERROR;
    lcd_i2c_err = lcd_i2c_pulse(data & 0xF0);
    if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

   lcd_i2c_err = lcd_i2c_pulse(data << 4);

   return lcd_i2c_err;
}

lcd_i2c_err_t lcd_i2c_data (uint8_t data) {
	lcd_i2c_err_t lcd_i2c_err = LCD_I2C_ERR_NO_ERROR;
	lcd_i2c_err = lcd_i2c_pulse((data & 0xF0) | LCD_I2C_RS);
	if (lcd_i2c_err != LCD_I2C_ERR_NO_ERROR) {
		return LCD_I2C_ERR_TRX_FAIL;
	}
	lcd_i2c_err = lcd_i2c_pulse((data << 4) | LCD_I2C_RS);

	return lcd_i2c_err;
}

static inline lcd_i2c_err_t lcd_i2c_pulse(uint8_t data) {
    i2c_err_t i2c_err = I2C_ERR_NO_ERROR;
    uint8_t i = 0;

    // Write Data + LED ON
    msg = data | LCD_I2C_L;
    i2c_err = i2c_write(i2c_ptr, &lcd_i2c_msg);
    if (i2c_err != I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    msg |= LCD_I2C_E; // Enable Pulse
    i2c_err = i2c_write(i2c_ptr, &lcd_i2c_msg);
    if (i2c_err != I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    delay_10us();

    // Write Data + LED ON
    msg = data | LCD_I2C_L;
    i2c_err = i2c_write(i2c_ptr, &lcd_i2c_msg);
    if (i2c_err != I2C_ERR_NO_ERROR) {
        return LCD_I2C_ERR_TRX_FAIL;
    }

    // Delay 50us
    for (i = 0; i < 5; i++) {
        delay_10us();
    }

    return LCD_I2C_ERR_NO_ERROR;
}

static inline void delay_5ms(void) {
    uint16_t i = 0;
    for (i = 0; i < 500; i++) {
        delay_10us();
    }
}

static inline void delay_10us(void) {
    uint16_t i = 0;
    for (i = 0; i < 40; i++);
}
