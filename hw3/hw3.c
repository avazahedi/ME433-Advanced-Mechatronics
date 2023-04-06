#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include <stdio.h>

void blink(int, int); // blink the LEDs function
void send_sine();     // send a sine wave

int main(void) {
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
	if (!NU32DIP_USER){
        send_sine();
	}
  }
}

// send a sine wave
void send_sine(){
	int i;
	unsigned int t;
    char message[100];
	for (i=0; i< 100; i++){
        sprintf(message, "%f\r\n", sin((float)(i/100.0)*2*3.14159265)+1.0);
        NU32DIP_WriteUART1(message); // send message back

		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait 10 ms
		while(_CP0_GET_COUNT() < t + 240000){}
	}
}