#include "nu32dip.h"
#include "ws2812b.h"

void delay(int time_ms);

int main(void) {
    NU32DIP_Startup();
    ws2812b_setup();

    // traffic light gradient (sort of)

    // wsColor colors[8];
    // for (int i=0; i < 8; i++) {
    //     char r = 255 - 30*i;
    //     char g = 0 + 30*i;
    //     char b = 0;

    //     wsColor c;
    //     c.r = r;
    //     c.g = g;
    //     c.b = b;

    //     colors[i] = c;
    // }


    // while(1) {
    //     ws2812b_setColor(colors, 8);
    //     delay(1000);
    // }


    // moving rainbow
    wsColor rainbow[8];
    wsColor red = {.r = 0, .g = 255, .b = 0};
    // wsColor orange = {.r = 128, .g = 255, .b = 0};
    wsColor orange = {.r = 80, .g = 255, .b = 0};
    wsColor yellow = {.r = 255, .g = 255, .b = 0};
    wsColor yellowgreen = {.r = 255, .g = 128, .b = 0};
    wsColor green = {.r = 255, .g = 0, .b = 0};
    wsColor bluegreen = {.r = 255, .g = 0, .b = 190};
    wsColor blue = {.r = 0, .g = 0, .b = 255};
    // wsColor purple = {.r = 0, .g = 127, .b = 255};
    wsColor purple = {.r = 0, .g = 76, .b = 153};

    ///// if red and green weren't flipped
    // wsColor red = {.r = 255, .g = 0, .b = 0};
    // wsColor orange = {.r = 255, .g = 128, .b = 0};
    // wsColor yellow = {.r = 255, .g = 255, .b = 0};
    // wsColor yellowgreen = {.r = 128, .g = 255, .b = 0};
    // wsColor green = {.r = 0, .g = 255, .b = 0};
    // wsColor bluegreen = {.r = 0, .g = 255, .b = 190};
    // wsColor blue = {.r = 0, .g = 0, .b = 255};
    // wsColor purple = {.r = 127, .g = 0, .b = 255};

    rainbow[0] = red;
    rainbow[1] = orange;
    rainbow[2] = yellow;
    rainbow[3] = yellowgreen;
    rainbow[4] = green;
    rainbow[5] = bluegreen;
    rainbow[6] = blue;
    rainbow[7] = purple;

    wsColor colors[8];
    for (int i=0; i < 8; i++) {
        colors[i] = rainbow[i];
    }

    // _CP0_SET_COUNT(0);
    while(1) {
        _CP0_SET_COUNT(0);

        unsigned int t;
        t = _CP0_GET_COUNT();

        ws2812b_setColor(colors, 8);
        delay(1000);
    }

}

void delay(int time_ms) {
    unsigned int t;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 24000*time_ms){}
}