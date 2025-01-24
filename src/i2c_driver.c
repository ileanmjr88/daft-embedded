#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Helper macros to set the R/W bit
#define I2C_WRITE_BIT 0
#define I2C_READ_BIT 1

bool i2c_register_read(uint8_t device_address, uint8_t register_address, uint8_t data) {

    // Set up the Read/Write Bit
    uint8_t write_address = (device_address << 1) | I2C_READ_BIT;

    // Setting up buffer, register address first, then data
    uint8_t buffer[2] = {
        register_address, // Register Address
        data              // Device Address
    };

    // Write the register address to the device
    if (!i2c_mock_write(write_address, buffer, 2)) {
        return false;
    }
}

bool i2c_mock_write() {}

bool i2c_mock_read() {}