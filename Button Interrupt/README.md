# Button Interrupt

Toggles the LED on the launchpad when the button is pressed

The MSP430G2553 and MSP430F5529 are officially supported, and the source code is in the g2553 and f5529 folders, respectivly.

# Usage

By default, this uses a button on P1.1 and a led on P1.0 for the f5529 and P1.3 for the button and P1.6 for th led on the g2553
To change the pin (and thus the LED), change the #define in main.c. Note that only a couple pins actually have LEDs connected on the launchpads.
If you want to use an enirely different port, you will need to change the P1 references throughout the code (P1OUT, P1DIR, etc)
The same can be done for the button.

Note that the g2553 version requires a hardware pullup for the button, because the launchpad includes one.

The LED is toggled using an interrupt on the button pin. There is no software debouncing; you must do this in hardware.

# Compiling and uploading

Ensure that you have msp430gcc installed. In particular, `msp430-elf-gcc` and `msp430-elf-objcopy` are used to compile the program and convert the elf to a hex for uploading.

To flash the msp430, you will need the official TI MSP Flasher installed. It will need to be avaiable as `mspflash`. This allows a wrapper script to set the `LD_LIBRARY_PATH` correctly for MSP Flasher.

Simply type `make` in the correct directory for your processor, and the program will be compiled and uploaded to an attached Launchpad.

