# daft-embedded
This application, implements in C the write and read operations of an I2C driver. It simulates the I2C device, the mock functions will write and read data to a memory pointer these functions can be replaced in the future for any specific functions of the embedded platform or even converted to linux.

## Build and Run
```bash
mkdir build
cd build
cmake ..
make
./i2cdriver
```
**Note: when application prints out the Device Address, it is shifted 1 bit to the left and if its reading it will add a 1 at the right most**

## Limitation 
- Read of 1 byte of data.
- Write of 1 byte of data.
- 7 bit I2C device address, not implemented for 10bit addresses

