#include <wiringPi.h>
#include <stdio.h>

#define ledPin 0
#define buttonPin 1 

void main(void)
{
    printf("Program is starting...\n");

    wiringPiSetup();

    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    pullUpDnControl(buttonPin, PUD_UP);

    while(1) {
        if(digitalRead(buttonPin) == LOW) {
            digitalWrite(ledPin, HIGH);
            printf("Button is pressed, LED is on.\n");
        } else {
            digitalWrite(ledPin, LOW);
            printf("Button is released, LED is off.\n");
        }
    }
}