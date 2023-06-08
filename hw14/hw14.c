#include "nu32dip.h"
#include <stdio.h>

int main() {
    NU32DIP_Startup();
    NU32DIP_GREEN = 1;
    NU32DIP_YELLOW = 0;

    RPA0Rbits.RPA0R = 0b0101; // enables OC1 on RA0 (pin 2)
    T2CONbits.TCKPS = 0b111;     // Timer2 prescaler N=4 (1:4)  // highest prescalar
    PR2 = 3749;
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 200; //500;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 500; //500;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1

    // 1.5/20 * 3750 to 2.5/20 * 3750 
    // 0 deg is 1.5
    // 180 deg is 2.5
    // 45 is 1.75
    // 135 is 2.25


    while (1) {

        // sweep the servo from 45 deg to 135 deg every 4 seconds
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000*2) {
            NU32DIP_GREEN = 0;
            NU32DIP_YELLOW = 1;

            OC1RS = (int) ((float)25/100.0 * 3750);
            OC1RS = (int) 1.75/20.0 * 3750;
        }
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000*2) {
            NU32DIP_GREEN = 1;
            NU32DIP_YELLOW = 0;

            OC1RS = (int) 2.25/20.0 * 3750;
        }

    }


}