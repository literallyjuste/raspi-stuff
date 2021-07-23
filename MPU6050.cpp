#include <stdio.h>
#include <stdint.h> 
#include <unistd.h> 
#include "I2Cdev.h"
#include "MPU6050.h"
#include <softTone.h>
#include <math.h>
#include <wiringPi.h>

#define Buzzer 0 

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
    accelgyro.initialize();
    wiringPiSetup();
    printf(accelgyro.testConnection() ? "MPU connected successfully" : "MPU connection failed");
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    printf("Accel: %6hd %6hd %6hd  Gyro: %6hd %6hd %6hd\n", ax, ay, az, gx, gy, gz);
    printf("a/g: %.2f g %.2f g %.2f g   %.2f d/s %.2f d/s %.2f d/s \n",(float)ax/16384,(float)ay/16384,(float)az/16384,(float)gx/131,(float)gy/131,(float)gz/131);
}

void startBuzzer(int pin) {
    int x; 
    double sinVal, toneVal;
    for(x=0;x<360;x++) {
        sinVal = sin(x * (M_PI / 180));
        toneVal = 2000 + sinVal * 500;
        softToneWrite(pin, toneVal);
        delay(1);
    }
}

void stopBuzzer(int pin) {
    softToneWrite(pin, 0);
}

int main() {
    setup();
    pinMode(Buzzer, OUTPUT);
    softToneCreate(Buzzer);
    while(1){
        loop();
    }
    return 0;
}