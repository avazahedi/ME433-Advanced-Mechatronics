

int main() {
    // nu32 startup()

    // init i2c
    // init the mcp23008 chip
        // write to IODIR register, make GP7 output and GP0 input
    
    while(1) {
        // blink the yellow LED at 20 Hz

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