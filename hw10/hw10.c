#include "nu32dip.h"
#include "ws2812b.h"

void delay(int time_ms);

int main(void) {
    NU32DIP_Startup();
    ws2812b_setup();

    //// moving rainbow ////
    while(1) {
        for (int j=0; j < 8; j++) {
            wsColor colors[8];
            for (int i=0; i < 8; i++) {
                colors[(i+j)%8] = HSBtoRGB(45*(i), 1, 0.2);
            }

            ws2812b_setColor(colors, 8);
            delay(100);
        }

    }

}

void delay(int time_ms) {
    unsigned int t;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 24000*time_ms){}
}