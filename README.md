# STM32F103_25LC512_EEPromExample
This is example code for 25LC512 EEprom  with STM32F103 mcu. The language is C++

This is example code uses two separate 25LC512 via SPI serial communication. Both of eeprom are connected with mcu via following diagram. To use cpp with smt32fxxx microcontroller’s user needs to done following changes.

1)	Right click main.c Options for File ‘main.c’->File Type in this combo box change C source file to C++ source file then click ok. Or discard main.c file and add main.cpp file and recompile.
2)	Compile project and run.


The code start with configuration and it test reading and writing code in int, char, short data forms 
The connection diagram is like following  

![stm32f103_25lc512_pinout](https://user-images.githubusercontent.com/21033733/48670628-8c041900-eb2b-11e8-9659-03638cc9162f.png)
