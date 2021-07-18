#include <stdio.h>
#include <wiringPi.h>

#define ledpin 0 

void main (void) {
    wiringPiSetup();
    pinMode (ledpin,OUTPUT);
    while (1) {
        digitalWrite(ledpin,HIGH);
        delay (1000);
        digitalWrite (ledpin,LOW);
        delay (1000);
    }
}