#include "nu32dip.h"


void blink(int, int); // blink the LEDs function

int main() {
    // nu32 startup()

    // init i2c pins
    // init the mcp23008 chip
        // write to IODIR register, make GP7 output and GP0 input
    
    while(1) {
        // blink the yellow LED at 20 Hz
        blink(10, 200); // blink green and yellow LEDs

        unsigned char r = read_gp0();
        if (r == 1) {
            turn_on_gp7();
        }
        else {
            turn_off_gp7();
        }
    
        /*
        // blink the LED on GP7
        turn_on_gp7();
        delay();
        turn_off_gp7();
        delay();
        */
    }
}

void turn_on_gp7() {
    // send the start bit
    // send the address of the chip with a write bit
        0b01000000
    // send the register to change (OLAT)
        0x0A
    // send the value to put in that register
        0b1 << 7 // same as 0b10000000
    // send the stop bit
}

unsigned char read_gp0(){
    // send start
    // send the address with the write bit
    // send the register you want to read from
    // send restart
    // send the address with read bit
    unsigned char a = recv(); // receive
    // send an ack bit (acknowledge bit)
    // send stop
    return a&0b00000001 // checks that the last bit is a 1 (we don't care about the rest)
}

void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value) {
    // send start bit
    // send the address of the chip
    address
    // send the register name
    reg
    // send the value to turn on GP7
    value
    // send stop bit
}

///////////////////////////////////////////////////////////////////////////////////////////
// int main(void) {
//   char message[100];
  
//   NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
//   while (1) {
//     NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
//     NU32DIP_WriteUART1(message); // send message back
//     NU32DIP_WriteUART1("\r\n"); // carriage return and newline
// 	if (NU32DIP_USER){
// 		blink(5, 500); // 5 times, 500ms each time
// 	}
//   }
// }

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}