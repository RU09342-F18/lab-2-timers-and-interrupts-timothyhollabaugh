
// Include all the msp430 defines
#include <msp430.h>

// define what pin the led is connected to
#define LED1_PIN 6

void setup_watchdog() {
    // disable the watchdog
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {

    // set led to use peripheral function
    P1SEL |= 1<<LED1_PIN;

    // set the correct pin on port 1 to be an output for the led
    P1DIR |= 1<<LED1_PIN;

    // turn off the led output
    P1OUT &= ~(1<<LED1_PIN);
}

void setup_timer() {

    // Select clock source
    TA0CTL |= TASSEL_2;

    // Divide SMCLK by 1
    BCSCTL2 |= DIVS_0;

    // Set to continuous mode
    TA0CTL |= MC_2;

    // divide timer clock by 8
    TA0CTL |= ID_3;

    // Set capture/compare 1 to half
    TA0CCR1 = 0x7FFF;

    // Set to toggle every TACCR1
    TA0CCTL1 |= OUTMOD_4;

    // Enable Timer A0
    TA0CTL |= TAIE;
}

int main() {
    // run setup functions above
    setup_watchdog();
    setup_led();
    setup_timer();

    // Enable global interrupt flag, enter low power mode
    //_BIS_SR(GIE);

    // Enter infinite loop
    // since there is nothing to exit to, there is no point
    // in not having an infinite loop
    while(1) {
        __no_operation();
    }
}
