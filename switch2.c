#include <stdio.h>
#include <wiringPi.h>

#define ledpin 1
#define buttonpin 0

void main(void){
    wiringPiSetup();
    pinMode(ledpin,OUTPUT);
    pinMode(buttonpin,INPUT);
    while (1){
        if (digitalRead(buttonpin)==LOW){
            digitalWrite(ledpin,HIGH);
        } else {
            digitalWrite(ledpin,LOW);
        }
    }
}