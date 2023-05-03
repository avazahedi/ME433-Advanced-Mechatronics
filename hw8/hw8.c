#include "nu32dip.h"
#include "ssd1306.h"
#include "i2c_master_noint.h"
#include "font.h"
#include "mpu6050.h"

void drawChar(char letter, char x, char y);
void drawString(char*m, char x, char y);
void delay(int time_ms);

int main(void) {
    NU32DIP_Startup();
    init_mpu6050();
    ssd1306_setup();

    // char array for the raw data
    unsigned char d[14];

	// floats to store the data
    float ax, ay, az, gx, gy, gz, temp;

    // write to screen
    char m[100];
    sprintf(m, "z acceleration: ");
    drawString(m, 0, 0);

    while (1) {
        _CP0_SET_COUNT(0);

        // read IMU
        burst_read_mpu6050(d);

		// convert data
        az = conv_zXL(d);

        // print data to screen
        char zval[100];
        sprintf(zval, "%f", az);
        drawString(zval, 0, 10);

         int t = _CP0_GET_COUNT();
         float fps = 1.0/(t/48000000.0);
         char fps_arr[100];
         sprintf(fps_arr, "%2.2f FPS", fps);
         drawString(fps_arr, 0, 24);

        while (_CP0_GET_COUNT() < 48000000) {}

        // ssd1306_drawPixel(3, 3, 1);
        // ssd1306_update();        
        // NU32DIP_YELLOW = 0;
        // delay(500);
        // ssd1306_clear();
        // ssd1306_update();
        // NU32DIP_YELLOW = 1;
        // delay(500);
    }
}

void drawChar(char letter, char x, char y) {
    for (int j=0; j<5; j++) {
        char col = ASCII[letter - 0x20][j];

        for (int i=0; i<8; i++) {   // might have to start at 8 and go to 0 depending on orientation of OLED
            ssd1306_drawPixel(x+j, y+i, (col>>i)&0b1); // tell if bit is 1 or 0
        }
    }
    // ssd1306_update();
}

void drawString(char*m, char x, char y) {
    int k = 0;
    int xc = x;
    while (m[k] != 0) {     // at the end of every string there is a null character. here we can check for when the word ends
        drawChar(m[k], xc, y);
        k++;
        xc+=7;
    }
    ssd1306_update();
}



void delay(int time_ms) {
    unsigned int t;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 24000*time_ms){}
}