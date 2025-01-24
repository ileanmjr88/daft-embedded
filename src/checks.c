#include "checks.h"

/**
 * @brief Checks if the I2C payloads are correctly set.
 *
 * This function compares the device address, register address, and data
 * between two I2C payload structures to ensure they are set correctly.
 *
 * @param i2csim Pointer to the simulated I2C payload structure.
 * @param i2cdev Pointer to the actual I2C device payload structure.
 * @return true if all fields match, false otherwise.
 */
bool check(struct i2c_payload *i2csim, struct i2c_payload *i2cdev) {
    if (i2csim->device_address != i2cdev->device_address) {
        fprintf(stderr, "[%s]:  Device address was not set correctly\n", __func__);
        return false;
    }
    if (i2csim->register_address != i2cdev->register_address) {
        fprintf(stderr, "[%s]:  Register address was not set correctly\n", __func__);
        return false;
    }
    if (i2csim->data != i2cdev->data) {
        fprintf(stderr, "[%s]:  Data was not set correctly\n", __func__);
        return false;
    }
    return true;
}