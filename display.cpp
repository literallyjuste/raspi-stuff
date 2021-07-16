#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>
#include "DHT.hpp"
#include "DHT.cpp"

int pcf8574_address = 0x27;
#define BASE 64
#define DHT11_Pin 0
#define RS BASE+0
#define RW BASE+1
#define EN BASE+2
#define LED BASE+3
#define D4 BASE+4
#define D5 BASE+5
#define D6 BASE+6
#define D7 BASE+7

int lcdhd;

void printCPUTemperature() {
    FILE *fp;
    char str_temp[15];
    float CPU_temp;
    fp=fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fgets(str_temp, 15, fp);
    CPU_temp = atof(str_temp)/1000.0;
    printf("CPU's temperature : %.2f \n", CPU_temp);
    lcdPosition(lcdhd, 0, 0);
    lcdPrintf(lcdhd, "CPU:%.2fC", CPU_temp);
    fclose(fp);
}

void printDataTime() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("%s \n", asctime(timeinfo));
    lcdPosition(lcdhd, 0, 1);

    lcdPrintf(lcdhd, "Time:%02d:%02d:%02d", timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
}

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

void MicroStuff() {
        printCPUTemperature();
        printDataTime();
        delay(1000);
}

void DHTStuff() {
    DHT dht;
    int chk, counts;
    counts++;
    printf("Measurement counts : %d \n", counts);
    for(int i = 0; i<15;i++) {
        chk = dht.readDHT11(DHT11_Pin);
        if(chk == DHTLIB_OK) {
            printf("DHT11,OK!\n");
            break;
        }
        delay(100);
    }
    printf("Humidity is %.2f %% \t Temperature is %.2f *C\n\n", dht.humidity, dht.temperature);
    lcdPosition(lcdhd, 0, 0);
    lcdPrintf(lcdhd, "Hum:%.2f", dht.humidity);
    lcdPosition(lcdhd, 0, 1);
    lcdPrintf(lcdhd, "Temp:%.2f", dht.temperature);
    delay(2000);
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
        MicroStuff();
        delay(20000);
        DHTStuff();
        delay(20000);
    }
    return 0;
}