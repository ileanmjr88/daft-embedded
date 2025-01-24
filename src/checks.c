#include "checks.h"

bool check(struct i2c_payload *i2csim, struct i2c_payload *i2cdev) {
    if (i2csim->device_address != i2cdev->device_address) {
        perror("[check]: Device address was not set correctly");
        return false;
    }
    if (i2csim->register_address != i2cdev->register_address) {
        perror("[check]: Register address was not set correctly");
        return false;
    }
    if (i2csim->data != i2cdev->data) {
        perror("[check]: Data was not set correctly");
        return false;
    }
    return true;
}