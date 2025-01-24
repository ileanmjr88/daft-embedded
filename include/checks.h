#pragma once
#include "i2c_driver.h"
#include <stdbool.h>
#include <stdint.h>

bool check(struct i2c_payload *i2csim, struct i2c_payload *i2cdev);