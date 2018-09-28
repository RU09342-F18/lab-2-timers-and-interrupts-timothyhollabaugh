# Button based delay

Toggles the LED on the launchpad continuously, depending on how long the button was pressed.

The MSP430G2553 and MSP430F5529 are officially supported, and the source code is in the g2553 and f5529 folders, respectivly.

# Usage

By default, this uses P1.2 for the led and P1.1 for the button for the f5529 and P1.6 for the led and P1.2 for the button on the g2553.

Note that the g2553 does not have a button on P1.2. You will need to install a jumper between P1.2 and P1.3 to use the onboard button. A jumper can be obtained from the bank of jumpers that connects the g2553 to the programmer. Use something like TXD since that is not used to program the g2553.
Note that the f5529 does not have a led on P1.2. You will have to run a jumper from P1.2 to the led.

# Compiling and uploading

Ensure that you have msp430gcc installed. In particular, `msp430-elf-gcc` and `msp430-elf-objcopy` are used to compile the program and convert the elf to a hex for uploading.

To flash the msp430, you will need the official TI MSP Flasher installed. It will need to be avaiable as `mspflash`. This allows a wrapper script to set the `LD_LIBRARY_PATH` correctly for MSP Flasher.

Simply type `make` in the correct directory for your processor, and the program will be compiled and uploaded to an attached Launchpad.

