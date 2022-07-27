#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "timer.hpp"

// read frames with timestamps from stdin
// parse the timestamps and send them over udp at appropriate times
int main(int argc, char** argv)
{
    Tools::Timer* timer = Tools::Timer::createTimer();
    Tools::Timer* runTimer = Tools::Timer::createTimer();
    float lastDisplayTime = -1;
    float time;
    uint8_t data[1000];
    char destAddr[256];
    int port = 9600;
    char tempFile[256];
    char ncCmdString[1024];
    int c;
    int framesPerSecond = 0;
    int lastSecond = 0;
    bool useTime = true;

    sprintf(destAddr, "127.0.0.1");
    sprintf(tempFile, "/mnt/tmp/temp.img");

    while ((c = getopt(argc, argv, "a:f:p:x")) != -1)
    {
        if (c == 'a')
        {
            strcpy(destAddr, optarg);
        }
        else if (c == 'f')
        {
            strcpy(tempFile, optarg);
        }
        else if (c == 'p')
        {
            port = atoi(optarg);
        }
        else if (c == 'x')
        {
            useTime = false;
        }
    }

    // prepare command string
    sprintf(ncCmdString, "cat %s | nc -N %s %d", tempFile, destAddr, port);
    runTimer->start();

    while (1)
    {
        if (fread(&time, sizeof(float), 1, stdin) != 1)
        {
            break;
        }

        if (fread(data, 1, 1000, stdin) != 1000)
        {
            break;
        }

        // check the timing of this frame and wait if needed
        if (lastDisplayTime < 0 || time < lastDisplayTime)
        {
            // start the timer
            timer->start();
        }

        if (useTime)
        {
            double timeNow = timer->getTime();
            while (timeNow < time)
            {
                // sleep while frame is still early
                usleep(100);
                timeNow = timer->getTime();
            }
        }
        lastDisplayTime = (double)time;

        // write to file
        FILE* fp = fopen(tempFile, "wb");
        fwrite(data, 1, 1000, fp);
        fclose(fp);

        system(ncCmdString);
        framesPerSecond++;

        // display fps once per second
        double runTime = runTimer->getTime();
        if ((int)runTime > lastSecond)
        {
            lastSecond = (int)runTime;
            printf("%d FPS\n", framesPerSecond);
            framesPerSecond = 0;
        }
    }
}