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
    bool fake = false;
    int pagedelay = 0;
    int chardelay = 0;
    uint8_t fchar = 0;
    bool do_pin_test = false;
    FILE* logfp = stdout;

    while ((c = getopt(argc, argv, "ftxd:s:c:l:p:h:n")) != -1)
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
        else if (c == 'l')
        {
            logfp = fopen(optarg, "wb");
        }
        else if (c == 'f')
        {
            fake = true;
        }
        else if (c == 'p')
        {
            pagedelay = atoi(optarg);
        }
        else if (c == 'h')
        {
            chardelay = atoi(optarg);
        }
        else if (c == 'n')
        {
            do_pin_test = true;
        }
    }

    init();
    setDataOutput();
    uint8_t t = 0;
    outputDataByte(0);

    if (do_pin_test) {
        uint8_t tb = 0x1;
        for (int i = 0; i < 8; i++) {
            printf("test byte: %X\n", tb);
            outputDataByte(tb);
            tb <<= 1;
            delayMicroseconds(5 * 1000000);
        }

        exit(0);
    }

    //int dd = atoi(argv[1]);
    Tools::Timer* timer = Tools::Timer::createTimer();
    FILE* fp = stdin;

    //uint8_t test[1024];
    int charactersInPage = columns * rows;
    int charactersToSend = charactersInPage;

    uint8_t* test = new uint8_t[charactersToSend];
    uint8_t testval = 0;
    int page = 0;
    int pagesInSecond = 0;
    int lastsecond = 0;
    digitalWrite(CA1, 1);
    fprintf(logfp, "starting in %d seconds..\n", start_delay);
    delay(start_delay * 1000);
    fprintf(logfp, "started.\n");
    fflush(logfp);

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

        if (fake) { 
            uint8_t* ptr = test;
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    *ptr = fchar;
                    ptr++;
                    fchar++;
                }
            }
        } else {
            fread(test, 1, charactersInPage, fp);
        }
        
        page++;
        pagesInSecond++;
        int currSecond = millis() / 1000;
        if (currSecond > lastsecond) {
            fprintf(logfp, "%d FPS hw %f ow %f\n", pagesInSecond, handshakeWaitTime, outputWaitTime);
            fflush(logfp);
            pagesInSecond = 0;
            lastsecond = currSecond;
            handshakeWaitTime = 0.0;
            outputWaitTime = 0.0;
        }

        if (digitalRead(CB2) == 0)
        {
            //printf("pet is off, skip frame\n");
            continue;
        }

        if (output_image)
        {
            for (int i = 0; i < charactersToSend; i += 2)
            {
                double t1 = timer->getTime();
                outputDataByte(test[i]);
                double t2 = timer->getTime();

                if (chardelay > 0) {
                    delayMicroseconds(chardelay);
                }
                // signal ready
                digitalWrite(CA1, 0);
                delayMicroseconds(dd);
                digitalWrite(CA1, 1);
                
                // wait for CB2 low
                double t3 = timer->getTime();

                bool exit = false;
                while (digitalRead(CB2) != 0 && !exit) 
                {
                    //printf("1");
                    if (timer->getTime() - t3 > (1.0/100.0))
                    {
                        // PET is off
                        exit = true;
                    }
                }

                if (exit)
                {
                    break;
                }
                double t4 = timer->getTime();
                
                // output data
                double t5 = timer->getTime();
                outputDataByte(test[i+1]);
                double t6 = timer->getTime();

                if (chardelay > 0) {
                    delayMicroseconds(chardelay);
                }
                // signal ready
                digitalWrite(CA1, 0);
                delayMicroseconds(dd);
                digitalWrite(CA1, 1);
                //delay(dd);
                
                double t7 = timer->getTime();
                // wait for CB2 high
                while (digitalRead(CB2) != 1 && !exit) 
                {
                    if (timer->getTime() - t7 > (1.0/100.0))
                    {
                        // PET is off
                        exit = true;
                    }
                }
                
                if (exit)
                {
                    break;
                }
                double t8 = timer->getTime();

                handshakeWaitTime += (t4-t3) + (t8-t7);
                outputWaitTime += (t2-t1) + (t6-t5);
            }
        }

        if (pagedelay > 0) {
            delayMicroseconds(pagedelay);
        }
    }

}