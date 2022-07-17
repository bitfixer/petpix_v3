#include "petpix.h"
#include "timer.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const int dataPins[] = {DATA0, DATA1, DATA2, DATA3, DATA4, DATA5, DATA6, DATA7};

void setDataInput()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(dataPins[i], INPUT);
    }
    digitalWrite(DIR, 1);
}

void setDataOutput()
{
    digitalWrite(DIR, 0);
    for (int i = 0; i < 8; i++)
    {
        pinMode(dataPins[i], OUTPUT);
    }
}

void init()
{
    wiringPiSetupPhys();
    pinMode(DIR, OUTPUT);
    pinMode(OUTPUT_ENABLE_BAR, OUTPUT);
    pinMode(CA1, OUTPUT);
    digitalWrite(CA1, 1);

    pinMode(CB2, INPUT);

    digitalWrite(OUTPUT_ENABLE_BAR, 0);
    setDataInput();
}

void outputDataByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(dataPins[i], (byte & (1 << i)) >> i);
    }
}

uint8_t inputDataByte()
{
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++)
    {
        byte |= (digitalRead(dataPins[i]) << i);
    }
    return byte;
}

int main(int argc, char** argv)
{
    init();
    setDataOutput();
    uint8_t t = 0;
    outputDataByte(0);

    int dd = atoi(argv[1]);
    Tools::Timer* timer = Tools::Timer::createTimer();
    FILE* fp = stdin;

    uint8_t test[1024];
    uint8_t testval = 0;
    delay(1000);
    int page = 0;
    int pagesInSecond = 0;
    int lastsecond = 0;
    digitalWrite(CA1, 1);
    printf("starting in 5 seconds..\n");
    delay(5000);
    printf("started.\n");

    double handshakeWaitTime = 0.0;
    double outputWaitTime = 0.0;

    while (1) 
    {
        int testindex = 0;
        /*
        for (int r = 0; r < 25; r++)
        {
            for (int c = 0; c < 40; c++)
            {
                test[testindex++] = r + page;
            }
        }
        */
        fread(test, 1, 1000, fp);
        page++;
        pagesInSecond++;
        int currSecond = millis() / 1000;
        if (currSecond > lastsecond) {
            printf("%d FPS hw %f ow %f\n", pagesInSecond, handshakeWaitTime, outputWaitTime);
            pagesInSecond = 0;
            lastsecond = currSecond;
            handshakeWaitTime = 0.0;
            outputWaitTime = 0.0;
        }

        for (int i = 0; i < 1000; i += 2)
        {
            double t1 = timer->getTime();
            outputDataByte(test[i]);
            double t2 = timer->getTime();
            // signal ready
            digitalWrite(CA1, 0);
            delayMicroseconds(dd);
            digitalWrite(CA1, 1);
            
            // wait for CB2 low
            double t3 = timer->getTime();
            while (digitalRead(CB2) != 0) {
                //printf("1");
            };
            double t4 = timer->getTime();
            
            // output data
            double t5 = timer->getTime();
            outputDataByte(test[i+1]);
            double t6 = timer->getTime();
            // signal ready
            digitalWrite(CA1, 0);
            delayMicroseconds(dd);
            digitalWrite(CA1, 1);
            //delay(dd);
            
            double t7 = timer->getTime();
            // wait for CB2 high
            while (digitalRead(CB2) != 1) {
                //printf("2");
            };
            double t8 = timer->getTime();

            handshakeWaitTime += (t4-t3) + (t8-t7);
            outputWaitTime += (t2-t1) + (t6-t5);
        }
    }

}