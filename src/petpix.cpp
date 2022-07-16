#include "petpix.h"
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

    uint8_t test[1024];
    uint8_t testval = 0;
    delay(1000);

    int page = 0;
    //while (1) 
    {
        /*
        for (int i = 0; i < 1024; i++)
        {
            test[i] = testval;
            testval++;
        }
        */

        
        int page = 0;
        int pagesInSecond = 0;
        int lastsecond = 0;
        digitalWrite(CA1, 1);
        printf("starting in 5 seconds..\n");
        delay(5000);
        printf("started.\n");

        while (1) 
        {
            //printf("page %d\n", page);
            int testindex = 0;
            for (int r = 0; r < 25; r++)
            {
                for (int c = 0; c < 40; c++)
                {
                    test[testindex++] = r + page;
                }
            }
            page++;
            pagesInSecond++;
            int currSecond = millis() / 1000;
            if (currSecond > lastsecond) {
                printf("%d FPS\n", pagesInSecond);
                pagesInSecond = 0;
                lastsecond = currSecond;
            }

            for (int i = 0; i < 1024; i += 2)
            {
                outputDataByte(test[i]);
                // signal ready
                digitalWrite(CA1, 1);
                delayMicroseconds(dd);
                digitalWrite(CA1, 0);
                //delay(dd);
                
                //digitalWrite(CA1, 1);
                // wait for CB2 low
                while (digitalRead(CB2) != 0) {
                    //printf("1");
                };
                
                // output data
                outputDataByte(test[i+1]);
                // signal ready
                digitalWrite(CA1, 1);
                delayMicroseconds(dd);
                digitalWrite(CA1, 0);
                //delay(dd);
                
                // wait for CB2 high
                while (digitalRead(CB2) != 1) {
                    //printf("2");
                };
            }
        }
    }


}