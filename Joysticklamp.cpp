/*
GPIO18 = Blue Lamp
GPIO17 = Green Lamp
GPIO25 = Joystick
GPIO23 = Red Lamp
GPIO22 = Yellow Lamp

Left = Blue
Up = Red
Down = Green
Right = Yellow

Up = x = 0
Down = x = 255
Left = y = 255
Right = y = 0
*/

#include <ADCDevice.hpp>
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define stick 6
#define red 4
#define yellow 3
#define blue 1
#define green 0

ADCDevice *adc;

int main(void){
    adc = new ADS7830();
    wiringPiSetup();
    pinMode(stick,INPUT);
    pinMode(blue,OUTPUT);
    pinMode(green,OUTPUT);
    pinMode(red,OUTPUT);
    pinMode(yellow,OUTPUT);
    pullUpDnControl(stick,PUD_UP);
    while (1){
        int Z = digitalRead(stick);
        int X = adc->analogRead(1);
        int Y = adc->analogRead(0);
        printf("X Axis: %d, \t Y Axis: %d\t, Z : %d\n",X,Y,Z);
        delay(100);
        if(digitalRead(stick)==LOW){//Press
            digitalWrite(blue,HIGH);
            digitalWrite(red,HIGH);
            digitalWrite(green,HIGH);
            digitalWrite(yellow,HIGH);
            printf("Press");
        }
        else if(X<=70 && Y>=70 && Y<=170){ //Up
            digitalWrite(blue,LOW);
            digitalWrite(red,HIGH);
            digitalWrite(green,LOW);
            digitalWrite(yellow,LOW);
            printf("Up");
        }
        else if(Y>170 && X>=70 && X<=170){//Left
            digitalWrite(blue,HIGH);
            digitalWrite(red,LOW);
            digitalWrite(green,LOW);
            digitalWrite(yellow,LOW);
            printf("Left");
        }
        else if(Y<=70 && X>=70 && X<=170){//Right
            digitalWrite(blue,LOW);
            digitalWrite(red,LOW);
            digitalWrite(green,LOW);
            digitalWrite(yellow,HIGH);
            printf("Right");
        }
        else if(X>=170 && Y>=70 && Y<=170){//Down
            digitalWrite(blue,LOW);
            digitalWrite(red,LOW);
            digitalWrite(green,HIGH);
            digitalWrite(yellow,LOW);
            printf("Down");
        }
        else if(X<=70 && Y>=170){//UpLeft
            digitalWrite(blue,HIGH);
            digitalWrite(red,HIGH);
            digitalWrite(green,LOW);
            digitalWrite(yellow,LOW);
            printf("UpLeft");
        }
        else if(X<=70 && Y<=70){//UpRight
            digitalWrite(blue,LOW);
            digitalWrite(red,HIGH);
            digitalWrite(green,LOW);
            digitalWrite(yellow,HIGH);
            printf("UpRight");
        }
        else if(X>=170 && Y>=170){//DownLeft
            digitalWrite(blue,HIGH);
            digitalWrite(red,LOW);
            digitalWrite(green,HIGH);
            digitalWrite(yellow,LOW);
            printf("DownLeft");
        }
        else if(X>=170 && Y<=70){//DownRight
            digitalWrite(blue,LOW);
            digitalWrite(red,LOW);
            digitalWrite(green,HIGH);
            digitalWrite(yellow,HIGH);
            printf("DownRight");
        }
        else {//AFK
            digitalWrite(blue,LOW);
            digitalWrite(red,LOW);
            digitalWrite(green,LOW);
            digitalWrite(yellow,LOW);
            printf("AFK");
        }
    }
    return 0;
}