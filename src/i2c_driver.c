
#include "i2c_driver.h"
#include <string.h>

/**
 * @brief Reads a register from an I2C device.
 *
 * This function reads a single byte from a specified register of an I2C device.
 * It sets up the device address with the read bit, prepares the buffer with the
 * register address and data, and uses mock functions to simulate the I2C read
 * operation.
 *
 * @param ptr Pointer to an i2c_payload structure where the read data will be stored. Simulation of I2C device
 * @param device_address The I2C address of the device to read from.
 * @param register_address The register address within the device to read from.
 * @param data The variable to store the read data.
 * @return true if the read operation was successful, false otherwise.
 */
bool i2c_register_read(struct i2c_payload *ptr, uint8_t device_address, uint8_t register_address, uint8_t *data) {

    // Set up the Read/Write Bit

    uint8_t address = i2c_adding_rw_bit(device_address, I2C_READ_BIT);
    uint8_t buffer[2] = {register_address, 0};
    /*
        Write the register address to the device, since we are mocking up the hardware, we will use the mock function,
        if we were creating this for linux we would use the ioctl function, and for any other embedded system we would
        use the appropriate function for that platform.
        For this one we are just writing the memory addres of the i2c_payload struct to the device and
        manually setting device_address
    */
    ptr->device_address = address; // setting up the device address with the read bit, simulation.
    ptr->register_address = 0;     // clearing the register address, simulation.
    // We will not clear ptr->data this will be set by the main function.
    memset(data, 0, 1);

    // Write the register address to the device
    if (!i2c_mock_hw_write(ptr, &register_address, 1)) {
        perror("[i2c_register_read]: Failed to write register address to device");
        return false;
    }

    // Read the data from the device, pasisng the buffer and the length of the buffer, to verify I am reading the correct register
    if (!i2c_mock_hw_read(ptr, data, 1)) {
        perror("[i2c_register_read]: Failed to read data from device");
        return false;
    }

    return true;
}

/**
 * @brief Writes a byte of data to a specific register of an I2C device.
 *
 * This function sets up the device address with the write bit, prepares the data buffer,
 * and writes the register address and data to the I2C device using a mock write function.
 *
 * @param ptr Pointer to the i2c_payload structure.
 * @param device_address The I2C address of the device.
 * @param register_address The register address to write to.
 * @param data The data byte to write to the register.
 * @return true if the write operation was successful, false otherwise.
 */
bool i2c_register_write(struct i2c_payload *ptr, uint8_t device_address, uint8_t register_address, uint8_t data) {
    // Set up the Read/Write Bit
    uint8_t address = i2c_adding_rw_bit(device_address, I2C_WRITE_BIT);

    uint8_t buffer[2] = {register_address, data};

    /*
        Write the register address to the device, since we are mocking up the hardware, we will use the mock function,
        if we were creating this for linux we would use the ioctl function, and for any other embedded system we would
        use the appropriate function for that platform.
        For this one we are just writing the memory addres of the i2c_payload struct to the device and manually
        clearning the other memory fields.
    */
    ptr->device_address = address; // setting up the device address with the write bit, simulation.
    ptr->register_address = 0;     //
    ptr->data = 0;

    // Write the register address to the device
    if (!i2c_mock_hw_write(ptr, buffer, 2)) {
        perror("Failed to write register address to device");
        return false;
    }
    return true;
}

/**
 * @brief Mock hardware write function for I2C communication.
 *
 * This function simulates writing data to an I2C device. It determines whether
 * the operation is a read or write based on the device address and the length
 * of the data. For read operations, it sets the register address to be read.
 * For write operations, it sets the register address and writes the data.
 *
 * @param ptr Pointer to the I2C payload structure containing device and register addresses.
 * @param buffer Pointer to the data buffer containing the data to be written.
 * @param length Length of the data buffer.
 * @return true if the data was successfully written, false otherwise.
 */
bool i2c_mock_hw_write(struct i2c_payload *ptr, uint8_t *buffer, size_t length) {
    // Determine if we are setting for Read or only Write
    if (ptr->device_address & I2C_READ_BIT && length == 1) {
        // Setting the register to be read
        ptr->register_address = buffer[0];
        if (ptr->register_address != buffer[0]) {
            perror("[i2c_mock_hw_write]: Register address was not set correctly");
            return false;
        }
    } else {
        // Writing the register address
        ptr->register_address = buffer[0];
        // Writing data
        ptr->data = buffer[1];
        if (ptr->register_address != buffer[0] || ptr->data != buffer[1]) {
            perror("[i2c_mock_hw_write]: Register address or data was not set correctly");
            return false;
        }
    }
    // Check if data was written
    return true;
}

/**
 * @brief Mock hardware read function for I2C.
 *
 * This function simulates reading data from an I2C device. It checks if the device address
 * has the read bit set and if the register address is set correctly before reading data.
 *
 * @param ptr Pointer to the I2C payload structure containing device and register addresses.
 * @param buffer Pointer to the buffer where the read data will be stored.
 * @param length Length of the buffer.
 * @return true if the read operation was successful, false otherwise.
 */
bool i2c_mock_hw_read(struct i2c_payload *ptr, uint8_t *buffer, size_t length) {
    // Check if the device address has the read bit set if not functions was used in error
    // or error with device
    if (!(ptr->device_address & I2C_READ_BIT) || length != 1) {
        perror("[i2c_mock_hw_read]: Device address does not have read bit set");
        return false;
    }

    // Read the data from the device
    memcpy(buffer, &ptr->data, length);

    // Check if data was read correctly
    if (buffer[0] != ptr->data) {
        perror("[i2c_mock_hw_read]: Data was not read correctly");
        return false;
    }

    return true;
}

/**
 * @brief Adds the read/write bit to the I2C device address.
 */
uint8_t i2c_adding_rw_bit(uint8_t device_address, uint8_t rw_bit) { return (device_address << 1) | rw_bit; }

/**
 * @brief Prints the I2C payload details.
 *
 * This function prints the device address, register address, and data
 * of the given I2C payload structure in a formatted manner.
 *
 * @param ptr Pointer to the i2c_payload structure containing the data to be printed.
 */
void print_i2c_payload(struct i2c_payload *ptr) {
    printf("Device Address: 0x%02X\n", ptr->device_address);
    printf("Register Address: 0x%02X\n", ptr->register_address);
    printf("Data: 0x%02X\n", ptr->data);
}