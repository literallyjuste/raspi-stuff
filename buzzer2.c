#include <wiringPi.h>
#include <stdio.h>

#define buttonpin 0
#define buzzerpin 1

void main(void) {
    wiringPiSetup();
    pinMode(buzzerpin,OUTPUT);
    pinMode(buttonpin,INPUT);
    pullUpDnControl(buttonpin, PUD_UP);
    while(1){
        if(digitalRead(buttonpin)==LOW){
            digitalWrite(buzzerpin,HIGH);
        }
        if(digitalRead(buttonpin)==HIGH){
            digitalWrite(buzzerpin,LOW);
        }
    }
}