# daft-embedded
This application, implements in C the write and read operations of an I2C driver. It simulates the I2C device, the mock functions will write and read data to a memory pointer these functions can be replaced in the future for any specific functions of the embedded platform or even converted to linux.

# Build and Run
```
mkdir build
cd build
cmake ..
make
./i2cdriver
```
