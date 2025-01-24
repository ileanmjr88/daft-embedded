#include "i2c_driver.h"
#include "checks.h"
#include <stdlib.h>


int main() {
    struct i2c_payload i2csim;
    i2csim.data = 0x30; // data simulated from I2C device

    // Set the I2C device address and register address for read operation
    uint8_t device_address = 0x50;
    uint8_t register_address = 0x20;
    uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t)); // Allocate memory for the data to compare if we read the data from simulates I2C device

    // Read a register from the I2C device
    if (!i2c_register_read(&i2csim, device_address, register_address, data)) {
        perror("Failed to read register from I2C device");
        return EXIT_FAILURE;
    }

    // Print the I2C payload details
    struct i2c_payload temp;
    temp.device_address = i2c_adding_rw_bit(device_address, I2C_READ_BIT);
    temp.register_address = register_address;
    temp.data = *data;
    if(check(&i2csim, &temp)){
        printf("[main]: I2C read is correct\n");
        print_i2c_payload(&temp);
    } else {
        perror("[main]: Failed to check I2C payload\n");
        return EXIT_FAILURE;
    }

    //Write Operation
    // Simulate device being cleared, i2c_register_write will also do it incase user forgets to clear it. 
    i2csim.device_address = 0;
    i2csim.register_address = 0;
    i2csim.data = 0x00;

    // Data to write to the I2C device
    device_address = 0xF0;
    register_address = 0x10;
    uint8_t write_data = 0x55;

    // Write a byte of data to the I2C device
    if (!i2c_register_write(&i2csim, device_address, register_address, write_data)) {
        perror("Failed to write data to I2C device");
        return EXIT_FAILURE;
    }

    temp.device_address = i2c_adding_rw_bit(device_address, I2C_WRITE_BIT);
    temp.register_address = register_address;
    temp.data = write_data;
    if(check(&i2csim, &temp)){
        printf("[main]: I2C read is correct\n");
        print_i2c_payload(&temp);
    } else {
        perror("[main]: Failed to check I2C payload\n");
        return EXIT_FAILURE;
    }


    // Free the allocated memory
    free(data);

    return EXIT_SUCCESS;
}


