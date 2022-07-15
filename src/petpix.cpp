#include "petpix.h"
#include <wiringPi.h>
#include <stdint.h>

void init()
{
    wiringPiSetupPhys();
    pinMode(DIR, OUTPUT);
    pinMode(OUTPUT_ENABLE_BAR, OUTPUT);
    pinMode(DATA0, OUTPUT);
    pinMode(DATA1, OUTPUT);
    pinMode(DATA2, OUTPUT);
    pinMode(DATA3, OUTPUT);
    pinMode(DATA4, OUTPUT);
    pinMode(DATA5, OUTPUT);
    pinMode(DATA6, OUTPUT);
    pinMode(DATA7, OUTPUT);

    digitalWrite(DIR, 0);
    digitalWrite(OUTPUT_ENABLE_BAR, 1);
    digitalWrite(DATA0, 0);
    digitalWrite(DATA1, 0);
    digitalWrite(DATA2, 0);
    digitalWrite(DATA3, 0);
    digitalWrite(DATA4, 0);
    digitalWrite(DATA5, 0);
    digitalWrite(DATA6, 0);
    digitalWrite(DATA7, 0);
}

void outputDataByte(uint8_t byte)
{

}

int main(int argc, char** argv)
{
    init();
    while (1) {
        digitalWrite(DATA0, 1);
        delay(1000);
        digitalWrite(DATA0, 0);
        delay(1000);
    }
}