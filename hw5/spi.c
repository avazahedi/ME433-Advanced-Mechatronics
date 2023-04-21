#include "spi.h"
#include "nu32dip.h"

// NOTES //
/*
// SHDN always hi
// LDAC always low
TRISBbits.TRISB3 = 0; // make B3 an output
LATBbits.LATB3 = 1; // make the output high

ANSELBbits.ANSELB11 = 0;  // example of making ANSELB11 a digital pin (not analog)
*/

// HW 5

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn off analog pins
    //...
    // Make an output pin for CS
    // TRISBCLR = 0x1; // this clears bit 0 on TRISB, which corresponds to B0
    TRISBbits.TRISB0 = 0; // make B0 an output
    LATBbits.LATB0 = 1; // set high
    // Set SDO1
    RPA1Rbits.RPA1R = 0b0011;
    // Set SDI1
    SDI1Rbits.SDI1R = 0b0010;

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 2000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    // 2000 is for 12 kHz (2000 = 48,000,000 / 2 * 12,000)
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}