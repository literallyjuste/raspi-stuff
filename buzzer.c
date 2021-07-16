#include <wiringPi.h>
#include <stdio.h>

#define buzzerPin 0
#define buttonPin 1

void main(void) {
    
    printf("Program is starting...\n");

    wiringPiSetup();

    pinMode(buttonPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    pullUpDnControl(buttonPin, PUD_UP);

    while(1) {
        if(digitalRead(buttonPin) == LOW) {
            digitalWrite(buzzerPin, HIGH);
            printf("Buzzer is on.\n");
        } else {
            digitalWrite(buzzerPin, LOW);
        }
    }
}