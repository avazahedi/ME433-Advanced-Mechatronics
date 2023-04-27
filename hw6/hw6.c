#include "nu32dip.h"
#include "i2c_master_noint.h"

void turn_on_gp7();
void turn_off_gp7();
unsigned char read_gp0();
void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value);
void delay(int time_ms);

// connect wire directly from PIC to I2C, then in the same row (on either side) put resistor to 3.3V

int main() {
    // nu32 startup()
    NU32DIP_Startup();
    i2c_master_setup();

    // init i2c pins
    // init the mcp23008 chip
        // write to IODIR register, make GP7 output and GP0 input, make other pins inputs
        // IODIR sets pins as input/output
        // OLAT sets pins high or low
        // GPIO reads if a pin is high or low
    
    unsigned char address = 0b01000000;  // device opcode - 0100 always, then 0 0 0 because pins A2, A1, A0 are low (ground), 0 at end for write bit
    unsigned char reg = 0x00;    // hex address of IODIR register is 00
    unsigned char value = 0b01111111;    // bit 7 needs to be 0 and bit 0 needs to be 1 - we are also making all the other pins input
    generic_i2c_write(address, reg, value);
    
    while(1) {
        // blink the yellow LED at 20 Hz

        unsigned char r = read_gp0();
        if (r == 1) {
            turn_on_gp7();
        }
        else {
            turn_off_gp7();
        }
    
        // // blink the LED on GP7
        // turn_on_gp7();
        // delay(200);
        // turn_off_gp7();
        // delay(200);
    }
}

void turn_on_gp7() {
    // send the start bit
    i2c_master_start();
    // send the address of the chip with a write bit
    unsigned char address = 0b01000000;
    i2c_master_send(address);
    // send the register to change (OLAT)
    unsigned char reg = 0x0A;
    i2c_master_send(reg);
    // send the value to put in that register
    unsigned char val = 0b1 << 7; // same as 0b10000000
    i2c_master_send(val);
    // send the stop bit
    i2c_master_stop();
}

void turn_off_gp7() {
    // send the start bit
    i2c_master_start();
    // send the address of the chip with a write bit
    unsigned char address = 0b01000000;
    i2c_master_send(address);
    // send the register to change (OLAT)
    unsigned char reg = 0x0A;
    i2c_master_send(reg);
    // send the value to put in that register
    unsigned char val = 0b0 << 7; // same as 0b00000000
    i2c_master_send(val);
    // send the stop bit
    i2c_master_stop();
}

unsigned char read_gp0(){
    // send start
    i2c_master_start();
    // send the address with the write bit
    unsigned char address = 0b01000000;
    i2c_master_send(address);
    // send the register you want to read from (GPIO)
    unsigned char reg = 0x09;
    i2c_master_send(reg);
    // send restart
    i2c_master_restart();
    // send the address with read bit
    unsigned char read_address = 0b01000001;
    i2c_master_send(read_address);
    // receive from the chip
    unsigned char recv = i2c_master_recv(); // receive
    // send an ack bit (acknowledge bit)
    i2c_master_ack(1);
    // send stop
    i2c_master_stop();

    return recv&0b00000001; // checks that the last bit is a 1 (we don't care about the rest)
}

void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value) {
    // send start bit
    i2c_master_start();
    // send the address of the chip
    i2c_master_send(address);
    // send the register name
    i2c_master_send(reg);
    // send the value to turn on GP7
    i2c_master_send(value);
    // send stop bit
    i2c_master_stop();
}

unsigned char generic_i2c_read(unsigned char write_address, unsigned char reg, unsigned char read_address){
    // send start
    i2c_master_start();
    // send the address with the write bit
    i2c_master_send(write_address);
    // send the register you want to read from
    i2c_master_send(reg);
    // send restart
    i2c_master_restart();
    // send the address with read bit
    i2c_master_send(read_address);
    // receive from the chip
    unsigned char recv = i2c_master_recv(); // receive
    // send an ack bit (acknowledge bit)
    i2c_master_ack(1);
    // send stop
    i2c_master_stop();

    return recv&0b00000001; // checks that the last bit is a 1 (we don't care about the rest)
}

///////////////////////////////////////////////////////////////////////////////////////////

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

void blinkgreen(){
    int i;
    unsigned int t;
    for (i=0; i<100; i++) {
        NU32DIP_GREEN = 0;
        t = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() < t + 12000){}
        NU32DIP_GREEN = 1;
        t = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() < t + 12000){}
    }
}

void delay(int time_ms) {
    unsigned int t;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 24000*time_ms){}
}