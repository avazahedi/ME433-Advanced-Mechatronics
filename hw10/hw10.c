#include "nu32dip.h"
#include "ws2812b.h"

void delay(int time_ms);

int main(void) {
    NU32DIP_Startup();
    ws2812b_setup();

    wsColor colors[8];
    for (int i=0; i < 8; i++) {
        char r = 255 - 30*i;
        char g = 0 + 30*i;
        char b = 0; // 255 - 30*i;

        // char r = 0;
        // char g = 255;
        // char b = 0;

        wsColor c;
        c.r = r;
        c.g = g;
        c.b = b;

        colors[i] = c;
    }


    while(1) {
        ws2812b_setColor(colors, 8);
        delay(1000);
    }

}

void delay(int time_ms) {
    unsigned int t;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 24000*time_ms){}
}