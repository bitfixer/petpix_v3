#include "petpix.h"
#include <wiringPi.h>
#include <stdint.h>

const int dataPins[] = {DATA0, DATA1, DATA2, DATA3, DATA4, DATA5, DATA6, DATA7};

void init()
{
    wiringPiSetupPhys();
    pinMode(DIR, OUTPUT);
    pinMode(OUTPUT_ENABLE_BAR, OUTPUT);

    for (int i = 0; i < 8; i++)
    {
        pinMode(dataPins[i], OUTPUT);
    }

    pinMode(H1, OUTPUT);
    pinMode(H2, OUTPUT);

    digitalWrite(DIR, 0);
    digitalWrite(OUTPUT_ENABLE_BAR, 0);
    
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(dataPins[i], 0);
    }

    digitalWrite(H1, 0);
    digitalWrite(H2, 0);
}

void outputDataByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {

    }
}

int main(int argc, char** argv)
{
    init();
    while (1) {
        digitalWrite(H1, 1);
        delay(1000);
        digitalWrite(H1, 0);
        delay(1000);
    }
}