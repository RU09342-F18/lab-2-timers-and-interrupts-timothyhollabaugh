
// Include all the msp430 defines
#include <msp430.h>

// define what pin the led is connected to
#define LED1_PIN BIT6
#define BUTTON_PIN BIT2

#define LED2_PIN BIT0

// Button interrupt
// Needed for gcc compiler
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void) {
    P1IFG &= ~BUTTON_PIN;

    // button pressed

    // reset timer
    TA0R = 0;

    // Set to continuous mode
    TA0CTL &= ~MC_3;
    TA0CTL |= MC_2;

    // enable capture mode
    TA0CCTL1 |= BIT8;

    // Disable interrupt for button pin
    P1IE &= ~BUTTON_PIN;

    // set button to use peripheral function
    P1SEL |= BUTTON_PIN;

    // Turn on debug led
    P1OUT |= LED2_PIN;
}

// Timer A interrupt
// CCR0 only
void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A0 (void) {
    TA0CTL &= ~TAIFG;
    //P1OUT ^= LED2_PIN;
}

// the rest of the interrupts
void __attribute__((interrupt(TIMER0_A1_VECTOR))) Timer_A1 (void) {

    switch (TA0IV) {
        case 2: // CCR1

            // copy compare register
            TA0CCR0 = TA0CCR1;

            // set to up mode
            TA0CTL &= ~MC_3;
            TA0CTL |= MC_1;

            // disable capture mode
            TA0CCTL1 &= ~BIT8;

            // set button to normal function
            P1SEL &= ~BUTTON_PIN;

            // set interrupt slope to falling
            P1IES |= BUTTON_PIN;

            // enable interrupt for button
            P1IE |= BUTTON_PIN;

            // Turn off debug led
            P1OUT &= ~LED2_PIN;

            break;
        case 4: // CCR2
            break;
        case 10: // Overflow
            break;
    }
}

void setup_watchdog() {
    // disable the watchdog
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {

    // set led to use peripheral function
    P1SEL |= LED1_PIN;

    // set the correct pin on port 1 to be an output for the led
    P1DIR |= LED1_PIN;

    // turn off the led output
    P1OUT &= ~LED1_PIN;

    P1DIR |= LED2_PIN;

}

void setup_button() {

    // set button to input
    P1DIR &= ~BUTTON_PIN;

    // set button to use peripheral function
    //P1SEL |= BUTTON_PIN;

    // clear interrupt flag
    P1IFG = 0x00;

    // set interrupt slope to falling
    P1IES |= BUTTON_PIN;

    // Enable interrupt for button pin
    P1IE |= BUTTON_PIN;
}

void setup_timer() {

    // Select clock source to SMCLK
    TA0CTL |= TASSEL_2;

    // Divide SMCLK by 8
    BCSCTL2 |= DIVS_3;

    // Set to up mode
    TA0CTL |= MC_1;

    // divide timer clock by 8
    TA0CTL |= ID_3;

    // Set capture/compare 1 to half
    TA0CCR1 = 0x7FFF;

    // Set to toggle every TA0CCR1
    TA0CCTL1 |= OUTMOD_4;

    // Enable CCR0 interrupt
    TA0CCTL0 |= CCIE;
    TA0CCTL1 |= CCIE;

    // Set to capture to rising edge
    TA0CCTL1 |= CM_1;

    // enable capture mode
    //TA0CCTL1 |= 1<<8;

    // Enable Timer A0
    TA0CTL |= TAIE;
}

int main() {
    // run setup functions above
    setup_watchdog();
    setup_led();
    setup_button();
    setup_timer();

    // Enable global interrupt flag, enter low power mode
    _BIS_SR(GIE);

    // Enter infinite loop
    // since there is nothing to exit to, there is no point
    // in not having an infinite loop
    while(1) {
        __no_operation();
    }
}
