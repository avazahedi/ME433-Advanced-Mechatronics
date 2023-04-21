#include "nu32dip.h"
#include "spi.h"
#include <math.h>
#include <stdio.h>

int main() {
    // call all init
    NU32DIP_Startup();
    initSPI();

    while(1) {
        unsigned int ts;
        unsigned int sineval;
        unsigned short voltage;
        unsigned short t;
        unsigned char a_or_b;
        for (int i=0; i < 200; i++) {
            ts = _CP0_GET_COUNT();
            // figure out the voltage for sine wave - 2Hz (2 sine waves per sec)  V = A*sin(2*pi*t/sample_rate)+B
            sineval = sin((float)(i/100.0)*2*3.14159265)*511.5 + 511.5;
            // convert to binary
            voltage = sineval;

            // byte: [a_or_b 1 1 1 [10 bit voltage] 0 0]
            t = 0;
            t = 0b111<<12;
            a_or_b = 0b0; // this is 0b0 (channel A) or 0b1 (channel B)
            t = t | (a_or_b<<15);
            // insert the voltage
            t = t | (voltage<<2);
            
            // send the voltage with SPI
            LATBbits.LATB0 = 0; // CS = 0
            spi_io(t>>8);
            spi_io(t);
            LATBbits.LATB0 = 1; // CS = 1

            // delay for 10ms (because we have 100 data points) - this would be for 1 sine wave per second ts + 240000
            // delay for 5ms instead (ts + 120000) - 2 sine waves per second
            while(_CP0_GET_COUNT() < ts + 120000){}
        }

        // figure out the voltage for triangle wave - 1 Hz (1 triangle per sec)
        unsigned int ts2;
        unsigned int trival;
        for (int j=0; j < 100; j++) {
            ts2 = _CP0_GET_COUNT();
            // calculate triangle wave
            if (j < 50) {
                trival = (1023.0/50.0)*j;
            }
            else {
                trival = -(1023.0/50.0)*(j-50) + 1023;
            }
            // convert to binary
            unsigned short voltage = trival;

            // byte: [a_or_b 1 1 1 [10 bit voltage] 0 0]
            unsigned short t2 = 0;
            t2 = 0b111<<12;
            unsigned char a_or_b = 0b1; // this is 0b0 (channel A) or 0b1 (channel B)
            t2 = t2 | (a_or_b<<15);
            // insert the voltage
            t2 = t2 | (voltage<<2);
            
            // send the voltage with SPI
            LATBbits.LATB0 = 0; // CS = 0
            spi_io(t2>>8);
            spi_io(t2);
            LATBbits.LATB0 = 1; // CS = 1

            // delay for 10ms (because we have 100 data points)
            while(_CP0_GET_COUNT() < ts2 + 240000){}
        }
    }

}