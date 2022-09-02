#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "timer.hpp"

uint8_t getControlByte(char* controlFileName)
{
    FILE* fp = fopen(controlFileName, "rb");
    if (fp == NULL)
    {
        return 0;
    }

    uint8_t b;
    fread(&b, 1, 1, fp);
    return b;
}

int loadPlaylist(char* playlistFileName, char** playlistEntries)
{
    FILE* fp = fopen(playlistFileName, "rb");
    if (fp == NULL)
    {
        return 0;
    }

    int i = 0;

    bool done = false;
    //while (fgets(playlistEntries[i], 256, fp) != NULL)
    while (!done)
    {
        if (fp == NULL) { printf("done!!\n"); }
        printf("here, %d *%s*\n", i, playlistEntries[i]);
        if (fgets(playlistEntries[i], 256, fp) == NULL)
        {
            done = true;
            break;
        }
        fprintf(stderr, "%d: %s\n", i, playlistEntries[i]);

        i++;
        printf("line %d\n", i);
        if (fp == NULL)
        {
            printf("null\n");
        }
    }

    return i;
}

bool waitForFrame(float time, Tools::Timer* timer)
{
    bool skip = false;
    double timeNow = timer->getTime();
    if (timeNow > time + 1.0/30.0)
    {
        // too late for this frame, skip it
        skip = true;
    }
    else
    {
        while (timeNow < time)
        {
            usleep(100);
            timeNow = timer->getTime();
        }
    }

    return skip;
}

int main(int argc, char** argv)
{
    int c;
    Tools::Timer* timer = Tools::Timer::createTimer();
    Tools::Timer* runTimer = Tools::Timer::createTimer();
    uint8_t* data = NULL;
    char destAddr[256];
    char tempFile[256];
    int port = 9600;
    char controlFileName[256];
    char playlistFileName[256];
    char** playlistEntries;
    char ncCmdString[1024];
    int numPlaylistEntries = 0;
    FILE* fpInput = NULL;
    float time;
    int columns = 40;
    int rows = 25;
    int framesSkipped = 0;

    uint8_t controlByte = -1;
    int currPlaylistItem = 0;
    float lastDisplayTime = -1;
    int framesPerSecond = 0;
    int lastSecond = 0;

    /*
    playlistEntries = new (char*[])
    for (int i = 0; i < 256; i++)
    {
        playlistEntries[i] = new char[256];
        playlistEntries[i][0] = 0;
    }
    */

    playlistEntries = (char**)malloc(sizeof(char*) * 256);
    for (int i = 0; i < 256; i++)
    {
        playlistEntries[i] = (char*)malloc(sizeof(char) * 256);
        playlistEntries[i][0] = 0;
    }

    sprintf(destAddr, "127.0.0.1");
    sprintf(tempFile, "/mnt/tmp/temp.img");
    sprintf(controlFileName, "/mnt/tmp/p.ctl");
    sprintf(playlistFileName, "playlist.txt");

    while ((c = getopt(argc, argv, "a:f:p:c:l:n:")) != -1)
    {
        if (c == 'a')
        {
            // address to send udp packets to
            strcpy(destAddr, optarg);
        } 
        else if (c == 'f')
        {   
            // location of temporary file used to store image data
            strcpy(tempFile, optarg);
        }
        else if (c == 'p')
        {
            // port for sending udp packets
            port = atoi(optarg);
        }
        else if (c == 'c')
        {
            // number of columns in image data
            columns = atoi(optarg);
        }
        else if (c == 'l')
        {
            strcpy(playlistFileName, optarg);
        }
        else if (c == 'n')
        {
            strcpy(controlFileName, optarg);
        }
    }

    int bytesInFrame = rows * columns;
    data = new uint8_t[bytesInFrame];

    // prepare command string
    sprintf(ncCmdString, "cat %s | nc -N %s %d", tempFile, destAddr, port);
    runTimer->start();

    // main loop
    while (1)
    {
        // check if there is an open file to read from
        if (fpInput == NULL)
        {
            // first check for an update
            uint8_t b = getControlByte(controlFileName);
            if (b != controlByte)
            {
                // reload the playlist
                numPlaylistEntries = loadPlaylist(playlistFileName, playlistEntries);
                printf("npe: %s\n", numPlaylistEntries);
                exit(1);
                currPlaylistItem = 0;
            }

            // read playlist and move to next file
            char* playlistEntry = playlistEntries[currPlaylistItem];
            fpInput = fopen(playlistEntry, "rb");
            if (fpInput)
            {
                printf("playing: %s\n", playlistEntry);
            }
            else
            {
                printf("could not open %s\n", playlistEntry);
            }

            currPlaylistItem++;
            if (currPlaylistItem >= numPlaylistEntries)
            {
                currPlaylistItem = 0;
            }
            lastDisplayTime = -1;
        }
        else
        {
            // a file is currently open
            // try to read a frame from the file
            if (fread(&time, sizeof(float), 1, fpInput) != 1)
            {
                // nothing more to read, stop playing this file
                fclose(fpInput);
                fpInput = NULL;
                continue;
            }

            // try to read entire frame from file
            if (fread(data, 1, bytesInFrame, fpInput) != bytesInFrame)
            {
                fclose(fpInput);
                fpInput = NULL;
                continue;
            }

            printf("time: %f\n", time);

            if (lastDisplayTime < 0 || time < lastDisplayTime)
            {
                timer->start();
            }

            bool skip = waitForFrame(time, timer);
            lastDisplayTime = (double)time;

            if (skip)
            {
                framesSkipped++;
            }
            else
            {
                FILE* fp = fopen(tempFile, "wb");
                fwrite(data, 1, bytesInFrame, fp);
                fclose(fp);

                system(ncCmdString);
                framesPerSecond++;

                double runTime = runTimer->getTime();
                if ((int)runTime > lastSecond)
                {
                    lastSecond = (int)runTime;
                    printf("%d FPS %d frames skipped\n", framesPerSecond, framesSkipped);
                    framesPerSecond = 0;
                    framesSkipped = 0;
                }
            }
        }
    }

}