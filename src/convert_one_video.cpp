#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

void getVideoInfo(char* inputPrefix, char* inputFname, int* fpsVal, int* numFrames)
{
    char ffmpegCmd[1024];
    sprintf(ffmpegCmd, "ffmpeg -i %s 2>%s_info.txt", inputFname, inputPrefix);
    system(ffmpegCmd);

    char grepCmd[256];
    sprintf(grepCmd, "grep \" fps\" %s_info.txt > %s_fps.txt", inputPrefix, inputPrefix);
    system(grepCmd);

    sprintf(grepCmd, "grep \"Duration:\" %s_info.txt > %s_duration.txt", inputPrefix, inputPrefix);
    system(grepCmd);

    char info[1024];
    char infoFname[64];
    sprintf(infoFname, "%s_fps.txt", inputPrefix);
    FILE* fp = fopen(infoFname, "rb");
    fread(info, 1, 1024, fp);
    fclose(fp);

    char* ff = strstr(info, " fps");
    char* fpsStart = ff - 1;
    while (*fpsStart != ' ')
    {
        fpsStart--;
    }

    *ff = 0;
    float fps = atof(fpsStart);

    sprintf(infoFname, "%s_duration.txt", inputPrefix);
    fp = fopen(infoFname, "rb");
    fread(info, 1, 1024, fp);
    fclose(fp);

    int hours;
    int minutes;
    float seconds;
    ff = strstr(info, "Duration:");
    ff += strlen("Duration: ");
    sscanf(ff, "%02d:%02d:%f,", &hours, &minutes, &seconds);
    
    float totalSeconds = (float)(hours*60*60) + (float)(minutes*60) + seconds;
    float totalFrames = totalSeconds * fps;

    // clean up
    char cleanCmd[256];
    sprintf(cleanCmd, "rm %s_info.txt", inputPrefix);
    system(cleanCmd);

    sprintf(cleanCmd, "rm %s_fps.txt", inputPrefix);
    system(cleanCmd);
    *fpsVal = (int)round(fps);
    *numFrames = (int)round(totalFrames);
}

void runConversion(char* videoFname, int fps, int numFrames, char* prefix, int columns, int rows, int method)
{
    char ffmpegCmd[512];
    char convertCmd[512];
    char fullCmd[2048];
    char outputFname[256];
    char options[128];

    int width = columns * 8;
    int height = rows * 8;

    sprintf(ffmpegCmd, "ffmpeg -i %s -vf scale=%d:%d -y -r %d -vcodec rawvideo -pix_fmt gray -f rawvideo pipe:1 2>/dev/null",
        videoFname,
        width,
        height,
        fps);

    if (columns == 40)
    {
        sprintf(outputFname, "%s.p40", prefix);
    }
    else if (columns == 80)
    {
        sprintf(outputFname, "%s.p80", prefix);
    }

    if (method == 1)
    {
        sprintf(options, "-s 4000 -z");
        //sprintf(convertCmd, "bin/petscii_convert -f %s -w %d -h %d -p gray -t -z -s 4000 -n 5 -m 1 2>/dev/null > %s", videoFname, width, height,)
    }
    else if (method == 2)
    {
        sprintf(options, "-s 80");
    }

    sprintf(convertCmd, "bin/petscii_convert -f %d -w %d -h %d -p gray -t -n 5 -m 1 -g %d %s 2>/dev/null > %s",
        fps,
        width,
        height,
        numFrames,
        options,
        outputFname);

    sprintf(fullCmd, "%s | %s", ffmpegCmd, convertCmd);

    printf("command: %s\n", fullCmd);
    system(fullCmd);
}

void convert_video(char* videoFname, int columns, int method)
{
    char prefix[256];
    char cmd[1024];
    // get prefix
    strcpy(prefix, videoFname);
    char* ext = &prefix[strlen(prefix) - 4];
    *ext = 0;

    // get framerate
    int fps;
    int numFrames;
    //int fps = getFps(prefix, videoFname);
    //int numFrames = getNumFrames()
    getVideoInfo(prefix, videoFname, &fps, &numFrames);
    printf("numframes: %d\n", numFrames);
    runConversion(videoFname, fps, numFrames, prefix, columns, 25, method);
}

int main(int argc, char** argv)
{
    int c;
    int columns = 40;
    bool method = 1;
    char videoFname[256];

    while ((c = getopt(argc, argv, "c:m:v:")) != -1)
    {
        if (c == 'c')
        {
            columns = atoi(optarg);
        }
        else if (c == 'm')
        {
            method = atoi(optarg);
        }
        else if (c == 'v')
        {
            strcpy(videoFname, optarg);
        }
    }

    convert_video(videoFname, columns, method);
}