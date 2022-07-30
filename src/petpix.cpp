#include "petpix.h"
#include "timer.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TESTONLY 1
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
    int c;
    bool output_image = true;
    bool read_times = false;
    int start_delay = 2;
    int dd = 3;
    int columns = 40;
    int rows = 25;

    while ((c = getopt(argc, argv, "txd:s:c:")) != -1)
    {
        if (c == 'x')
        {
            output_image = false;
        }
        else if (c == 'd')
        {
            dd = atoi(optarg);
        }
        else if (c == 't')
        {
            read_times = true;
        }
        else if (c == 's')
        {
            start_delay = atoi(optarg);
        }
        else if (c == 'c')
        {
            columns = atoi(optarg);
        }
    }

    init();
    setDataOutput();
    uint8_t t = 0;
    outputDataByte(0);

    //int dd = atoi(argv[1]);
    Tools::Timer* timer = Tools::Timer::createTimer();
    FILE* fp = stdin;

    //uint8_t test[1024];
    int charactersInPage = columns * rows;
    int charactersToSend = charactersInPage;
    if (charactersToSend == 2000)
    {
        charactersToSend = 2048;
    }

    uint8_t* test = new uint8_t[charactersToSend];
    uint8_t testval = 0;
    int page = 0;
    int pagesInSecond = 0;
    int lastsecond = 0;
    digitalWrite(CA1, 1);
    printf("starting in %d seconds..\n", start_delay);
    delay(start_delay * 1000);
    printf("started.\n");

    double handshakeWaitTime = 0.0;
    double outputWaitTime = 0.0;

    memset(test, 0, charactersToSend);

    while (1) 
    {
        int testindex = 0;
        float time;
        if (read_times)
        {
            fread(&time, 1, sizeof(time), fp);
        }
        fread(test, 1, charactersInPage, fp);
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

        if (output_image)
        {
            for (int i = 0; i < charactersToSend; i += 2)
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

}