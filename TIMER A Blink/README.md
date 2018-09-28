# Timer A blink

Toggles the LED on the launchpad continuously

The MSP430G2553 and MSP430F5529 are officially supported, and the source code is in the g2553 and f5529 folders, respectivly.

# Usage

By default, this uses P1.2 for the f5529 and P1.6 g2553.

Note that f5529 does not have a led on P1.2. You will have to run a jumper from P1.2 to the led.

# Compiling and uploading

Ensure that you have msp430gcc installed. In particular, `msp430-elf-gcc` and `msp430-elf-objcopy` are used to compile the program and convert the elf to a hex for uploading.

To flash the msp430, you will need the official TI MSP Flasher installed. It will need to be avaiable as `mspflash`. This allows a wrapper script to set the `LD_LIBRARY_PATH` correctly for MSP Flasher.

Simply type `make` in the correct directory for your processor, and the program will be compiled and uploaded to an attached Launchpad.

