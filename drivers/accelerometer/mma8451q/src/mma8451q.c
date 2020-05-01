#include "mma8451q.h"
#include "i2c.h"
#include "gpio.h"

mma8451q_ctl_t mma8451_ctl = { 0 };

mma8451q_err_t mma8451q_setup(uint8_t i2c_addr, mma8451q_range_t range, I2C_p i2c_ptr) {
    if (range >= MMA8451Q_RANGE_INVALID || i2c_ptr == NULL) {
        return MMA8451Q_ERR_INVALID_ARGS;
    }
    mma8451_ctl.i2c_ptr = i2c_ptr;
    mma8451_ctl.i2c_message.i2c_addr = i2c_addr;
    mma8451_ctl.i2c_message.tx_data = mma8451_ctl.tx_data;
    mma8451_ctl.i2c_message.rx_data = mma8451_ctl.rx_data;    

    // Stand By mode
    mma8451_ctl.i2c_message.tx_data[0] = MMA8451Q_CTRL_REG1;
    mma8451_ctl.i2c_message.tx_data[1] = MMA8451Q_CTRL_REG1_STD_BY;
    mma8451_ctl.i2c_message.tx_size = 2;
    mma8451_ctl.i2c_message.read = false;
	i2c_transmit(mma8451_ctl.i2c_ptr, &mma8451_ctl.i2c_message);

    // Config Accelereation range
    mma8451_ctl.i2c_message.tx_data[0] = MMA8451Q_XYZ_DATA_CFG;
    mma8451_ctl.i2c_message.tx_data[1] = range;
    mma8451_ctl.i2c_message.tx_size = 2;
    mma8451_ctl.i2c_message.read = false;
	i2c_transmit(mma8451_ctl.i2c_ptr, &mma8451_ctl.i2c_message);

    // Active + Low Noise
    mma8451_ctl.i2c_message.tx_data[0] = MMA8451Q_CTRL_REG1;
    mma8451_ctl.i2c_message.tx_data[1] = MMA8451Q_CTRL_REG1_ACTIVE | MMA8451Q_CTRL_REG1_LOW_NOISE;
    mma8451_ctl.i2c_message.tx_size = 2;
    mma8451_ctl.i2c_message.read = false;
	i2c_transmit(mma8451_ctl.i2c_ptr, &mma8451_ctl.i2c_message);

    return MMA8451Q_ERR_NO_ERROR;
}

int16_t mma8451q_read(mma8451q_axis_t axis) {
    int16_t accel_value = 0;
    if (axis >= MMA8451Q_AXIS_INVALID) {
        return 0;
    }

    mma8451_ctl.i2c_message.tx_data[0] = axis;
    mma8451_ctl.i2c_message.tx_size = 1;
    mma8451_ctl.i2c_message.read = true;
    mma8451_ctl.i2c_message.rx_size = 2;
    i2c_transmit(mma8451_ctl.i2c_ptr, &mma8451_ctl.i2c_message);

    accel_value = ((mma8451_ctl.i2c_message.rx_data[0] << 8) + mma8451_ctl.i2c_message.rx_data[1]) >> 2;
    if (accel_value & 0x2000) {
        // Negative
        accel_value |= 0xC000; // Set 2 MSB
    } else {
        accel_value &= ~0xC000; // Clear 2 MSB
    }

    return accel_value;
}

mma8451q_err_t mma8451q_read_all(mma8451q_values_t* values) {

    if (values == NULL) {
        return MMA8451Q_ERR_INVALID_ARGS;
    }

    mma8451_ctl.i2c_message.tx_data[0] = MMA8451Q_OUT_X;
    mma8451_ctl.i2c_message.tx_size = 1;
    mma8451_ctl.i2c_message.read = true;
    mma8451_ctl.i2c_message.rx_size = 6;
    i2c_transmit(mma8451_ctl.i2c_ptr, &mma8451_ctl.i2c_message);

    values->x = ((mma8451_ctl.i2c_message.rx_data[0] << 8) + mma8451_ctl.i2c_message.rx_data[1]) >> 2;
    if (values->x & 0x2000) {
        // Negative
        values->x |= 0xC000; // Set 2 MSB
    } else {
        values->x &= ~0xC000; // Clear 2 MSB
    }

     values->y = ((mma8451_ctl.i2c_message.rx_data[2] << 8) + mma8451_ctl.i2c_message.rx_data[3]) >> 2;
    if (values->y & 0x2000) {
        // Negative
        values->y |= 0xC000; // Set 2 MSB
    } else {
        values->y &= ~0xC000; // Clear 2 MSB
    }

     values->z = ((mma8451_ctl.i2c_message.rx_data[4] << 8) + mma8451_ctl.i2c_message.rx_data[5]) >> 2;
    if (values->z & 0x2000) {
        // Negative
        values->z |= 0xC000; // Set 2 MSB
    } else {
        values->z &= ~0xC000; // Clear 2 MSB
    }

    return MMA8451Q_ERR_NO_ERROR;
}
