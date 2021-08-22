#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>
#include <unistd.h>

#define dataPin 5
#define latchPin 4
#define clockPin 1

const int digitPin[]={0,2,3,12};

unsigned char num[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xA3};

void _selectDigit(int digit) {
    digitalWrite(digitPin[0], ((digit&0x08) == 0x08) ? LOW : HIGH);
    digitalWrite(digitPin[1], ((digit&0x04) == 0x04) ? LOW : HIGH);
    digitalWrite(digitPin[2], ((digit&0x02) == 0x02) ? LOW : HIGH);
    digitalWrite(digitPin[3], ((digit&0x01) == 0x01) ? LOW : HIGH);
}

void _shiftOut(int dPin, int cPin, int order, int val) {
    int i;
    for(i = 0; i < 8; i++) {
        digitalWrite(cPin, LOW);
        if(order == LSBFIRST) {
            digitalWrite(dPin, ((0x01&(val>>i)) == 0x01) ? HIGH : LOW);
            delayMicroseconds(1);
        } else {
            digitalWrite(dPin, ((0x80&(val<<i)) == 0x80) ? HIGH : LOW);
            delayMicroseconds(1);
        }
        digitalWrite(cPin, HIGH);
        delayMicroseconds(1);
    }
}

void outData(int8_t data) {
    digitalWrite(latchPin,LOW);
    _shiftOut(dataPin, clockPin,MSBFIRST,data);
    digitalWrite(latchPin, HIGH);
}

int display(int dec) {
    int delays = 1;

    outData(0xff);
    _selectDigit(0x01);
    outData(num[11]);

    delay(delays);

    outData(0xff);
    _selectDigit(0x02);
    outData(num[17]);

    delay(delays);

    outData(0xff);
    _selectDigit(0x04);
    outData(num[17]);

    delay(delays);

    outData(0xff);
    _selectDigit(0x08);
    outData(num[11]);

    delay(delays);
}

int main (void) {
    int i;

    wiringPiSetup();

    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    for(i=0;i<4;i++) {
        pinMode(digitPin[i],OUTPUT);
        digitalWrite(digitPin[i], HIGH);
    }
    while(1) {
        display(0xc0);
    }
    return(0);
}