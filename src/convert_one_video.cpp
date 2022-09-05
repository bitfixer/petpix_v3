#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int getFps(char* inputPrefix, char* inputFname)
{
    char ffmpegCmd[1024];
    sprintf(ffmpegCmd, "ffmpeg -i %s 2>%s_info.txt", inputFname, inputPrefix);
    system(ffmpegCmd);

    char grepCmd[256];
    sprintf(grepCmd, "grep \" fps\" %s_info.txt > %s_fps.txt", inputPrefix, inputPrefix);
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

    // clean up
    char cleanCmd[256];
    sprintf(cleanCmd, "rm %s_info.txt", inputPrefix);
    system(cleanCmd);

    sprintf(cleanCmd, "rm %s_fps.txt", inputPrefix);
    system(cleanCmd);
    return (int)round(fps);
}

// ffmpeg -i $1 -vf scale=$3:$4 -y -r $2 -vcodec rawvideo -pix_fmt gray -f rawvideo pipe:1 2>/dev/null | \
// bin/petscii_convert -f $2 -w $3 -h $4 -p gray -t $8 $7 -s $6 -n 5 -m 1 2>/dev/null > $5

void convert_video(char* videoFname, int columns, int method)
{
    char prefix[256];
    char cmd[1024];
    // get prefix
    strcpy(prefix, videoFname);
    char* ext = &prefix[strlen(prefix) - 4];
    *ext = 0;
    printf("prefix: %s\n", prefix);

    // get framerate
    int fps = getFps(prefix, videoFname);
    printf("fps: %d\n", fps);

    char ffmpegCmd[256];
    char convertCmd[256];
    char fullCmd[1024];

    if (columns == 40)
    {
        if (method == 1)
        {
            // 40 column
            sprintf(cmd, "./stream2.sh %s %d 320 200 %s.p40 4000 -z", videoFname, fps, prefix);
            printf("%s\n", cmd);
            system(cmd);
        }
        else if (method == 2)
        {
            // 40 column dct
            sprintf(cmd, "./stream2.sh %s %d 320 200 %s_dct.p40 80", videoFname, fps, prefix);
            printf("%s\n", cmd);
            system(cmd);
        }
    }
    else if (columns == 80)
    {
        if (method == 1)
        {
            // 80 column
            sprintf(cmd, "./stream2.sh %s %d 640 200 %s.p80 4000 -z", videoFname, fps, prefix);
            printf("%s\n", cmd);
            system(cmd);
        }
        else if (method == 2)
        {
            // 80 column dct
            sprintf(cmd, "./stream2.sh %s %d 640 200 %s_dct.p80 80", videoFname, fps, prefix);
            printf("%s\n", cmd);
            system(cmd);
        }
    }
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