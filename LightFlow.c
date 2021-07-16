#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>

#define dataPin 0
#define latchPin 2
#define clockPin 3 

void _shiftOut(int dPin, int cPin, int order, int val) {
    int i;
    for(i = 0; i < 8; i++) {
        digitalWrite(cPin, LOW);
        if(order == LSBFIRST) {
            digitalWrite(dPin,((0x01&(val>>i)) == 0x01) ? HIGH : LOW);
            delayMicroseconds(10);
        } else {
            digitalWrite(dPin, ((0x80&(val<<i)) == 0x80) ? HIGH : LOW);
            delayMicroseconds(10);
        }
        digitalWrite(cPin, HIGH);
        delayMicroseconds(10);
    }
}

int main(void) {
    int i;
    unsigned char x;
    printf("Program is starting...\n");

    wiringPiSetup();

    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    while (1) {
        x=0x01;
        for(i=0;i<8;i++) {
            digitalWrite(latchPin, LOW);
            _shiftOut(dataPin, clockPin, LSBFIRST, x);
            digitalWrite(latchPin, HIGH);
            x<<=1;
            delay(100);
        }
        x=0x80;
        for(i=0;i<8;i++) {
            digitalWrite(latchPin, LOW);
            _shiftOut(dataPin, clockPin, LSBFIRST, x);
            digitalWrite(latchPin, HIGH);
            x>>=1;
            delay(100);
        }
    }
    return 0;
}