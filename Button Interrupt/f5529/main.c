
// Include all the msp430 defines
#include <msp430.h>

// define what pin the led is connected to
#define LED1_PIN 0

// define what pin the button is connected to
#define BUTTON_PIN 1

// Needed for gcc compiler
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void) {

    // Clear interrupt flag
    P1IFG &= ~(1<<BUTTON_PIN);

    // toggle led
    P1OUT ^= 1<<LED1_PIN;
}

void setup_watchdog() {
    // disable the watchdog
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {
    // set the correct pin on port 1 to be an output for the led
    P1DIR |= 1<<LED1_PIN;

    // turn off the led output
    P1OUT &= ~(1<<LED1_PIN);
}

void setup_button() {

    // Set button to input
    P1DIR &= ~(1<<BUTTON_PIN);

    // Enable pullup resistor on button
    P1REN |= 1<<BUTTON_PIN;
    P1OUT |= 1<<BUTTON_PIN;

    // Clear iterrupt flags
    P1IFG = 0x00;

    // Set interrupt slope to falling for button pin
    P1IES &= ~(1<<BUTTON_PIN);

    // Enable interrupt for button pin
    P1IE |= 1<<BUTTON_PIN;
}

int main() {
    // run setup functions above
    setup_watchdog();
    setup_led();
    setup_button();

    // Enable global interrupt flag, enter low power mode
    _BIS_SR(GIE);

    // Enter infinite loop
    // since there is nothing to exit to, there is no point
    // in not having an infinite loop
    while(1);
}
