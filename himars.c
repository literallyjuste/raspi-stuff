#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>

int pcf8574_address = 0x27;
#define BASE 64

#define RS BASE+0
#define RW BASE+1
#define EN BASE+2
#define LED BASE+3
#define D4 BASE+4
#define D5 BASE+5
#define D6 BASE+6
#define D7 BASE+7

int lcdhd;

int detectI2C(int addr) {
    int _fd = wiringPiI2CSetup(addr);
    if (_fd < 0) {
        printf("Error address : 0x%x \n", addr);
        return 0;
    } else {
        if(wiringPiI2CWrite(_fd, 0) < 0) {
            printf("No device on address 0x%x found. \n", addr);
            return 0;
        } else {
            printf("Found device on address 0x%x", addr);
            return 1;
        }
    }
}

int main(void) {
    int i;
    printf("Program is starting...\n");
    wiringPiSetup();
    if(detectI2C(0x27)) {
        pcf8574_address = 0x27;
    } else if(detectI2C(0x3F)) {
        pcf8574_address = 0x3F;
    } else {
        printf("No I2C address found.");
        return -1;
    }
    pcf8574Setup(BASE, pcf8574_address);
    for(i=0;i<8;i++) {
        pinMode(BASE+i, OUTPUT);
    }
    digitalWrite(LED, HIGH);
    digitalWrite(RW, LOW);
    lcdhd = lcdInit(2, 16, 4, RS, EN, D4, D5, D6, D7, 0, 0, 0, 0);
    if(lcdhd == -1) {
        printf("lcdinit failed.");
        return 1;
    }
    while(1) {
        lcdPosition(lcdhd, 0, 0);
        lcdPrintf(lcdhd, "Hi mars");
        lcdPosition(lcdhd, 0, 1);
        lcdPrintf(lcdhd, "I love you <3");
        delay(20000);
        lcdPosition(lcdhd, 0, 0);
        lcdPrintf(lcdhd, "Look at me,");
        lcdPosition(lcdhd, 0 , 1);
        lcdPrintf(lcdhd, "I deserve attention");
        delay(20000);
        lcdPosition(lcdhd, 0, 0);
        lcdPrintf(lcdhd, "8=====D");
        lcdPosition(lcdhd, 0, 1);
        lcdPrintf(lcdhd, "-Stripe");
    }
    return 0;
}