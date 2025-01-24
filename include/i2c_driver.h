#pragma once
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Helper macros to set the R/W bit
#define I2C_WRITE_BIT 0
#define I2C_READ_BIT 1

struct i2c_payload {
    uint8_t device_address;
    uint8_t register_address;
    uint8_t data;
};

bool i2c_register_read(struct i2c_payload *ptr, uint8_t device_address, uint8_t register_address, uint8_t *data);
bool i2c_register_write(struct i2c_payload *ptr, uint8_t device_address, uint8_t register_address, uint8_t data);
bool i2c_mock_hw_write(struct i2c_payload *ptr, uint8_t *buffer, size_t length);
bool i2c_mock_hw_read(struct i2c_payload *ptr, uint8_t *buffer, size_t length);

uint8_t i2c_adding_rw_bit(uint8_t device_address, uint8_t rw_bit);

void print_i2c_payload(struct i2c_payload *ptr);