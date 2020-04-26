#include "i2c.h"
#include "i2c-defs.h"

i2c_err_t i2c_setup(i2c_mod_t i2c_mod, uint8_t f_divider) {
    I2C_p i2c_ptr = NULL;

    switch (i2c_mod) {
        case I2C_MOD_I2C0:
            i2c_ptr = I2C0;
            SIM->SCGC4 |= SCGC4_I2C0_POS; // I2C0 Clock Enable
        break;
        case I2C_MOD_I2C1:
            i2c_ptr = I2C1;
            SIM->SCGC4 |= SCGC4_I2C1_POS; // I2C1 Clock Enable
        break;
        default:
            return I2C_ERR_INVALID_MOD;
    }

    i2c_ptr->F = f_divider;
    i2c_ptr->C1 |= I2C_C1_ENABLE;

    return I2C_ERR_NO_ERROR;
}

i2c_err_t i2c_write(I2C_p i2c_ptr, i2c_msg_t* i2c_msg) {
    uint8_t i = 0;

    if (i2c_ptr == NULL || i2c_msg == NULL || i2c_msg->tx_size == 0) {
        return I2C_ERR_INVALID_ARGS;
    }

    // Wait bus be available
    while(i2c_ptr->S & I2C_S_BUS_BUSY);

    i2c_ptr->C1 |= I2C_START; // Start

    i2c_ptr->D = (i2c_msg->i2c_addr << 1); // Write Address
    while (!(i2c_ptr->S & I2C_WAIT)); // Wait Flag
    i2c_ptr->S |= I2C_WAIT; // Clear Flag

    for(i = 0; i < i2c_msg->tx_size; i++) {
        i2c_ptr->D = i2c_msg->tx_data[i]; // Write Data
        while (!(i2c_ptr->S & I2C_WAIT)); // Wait
        i2c_ptr->S |= I2C_WAIT; // Clear
    }

    if (i2c_msg->read == true) {
        i2c_ptr->C1 |= I2C_RPT_START;
        I2C0->C1 |= 0x08; // Disable ACK

        i2c_ptr->D = (i2c_msg->i2c_addr << 1) | 0x01; // Read Address
        while (!(i2c_ptr->S & I2C_WAIT)); // Wait Flag
        i2c_ptr->S |= I2C_WAIT; // Clear Flag

        i2c_ptr->C1 &= ~I2C_RECEIVE;

        i2c_msg->rx_data[0] = i2c_ptr->D;
        while (!(i2c_ptr->S & I2C_WAIT)); // Wait
        i2c_ptr->S |= I2C_WAIT; // Clear

        for(i = 0; i < i2c_msg->rx_size-1; i++) {
            i2c_msg->rx_data[i] = i2c_ptr->D; // Read Data
            while (!(i2c_ptr->S & I2C_WAIT)); // Wait
            i2c_ptr->S |= I2C_WAIT; // Clear
        }

        i2c_ptr->C1 &= I2C_STOP;
        i2c_msg->rx_data[i] = i2c_ptr->D; // Last byte

        return I2C_ERR_NO_ERROR;
    }

    i2c_ptr->C1 &= I2C_STOP;

    return I2C_ERR_NO_ERROR;
}
