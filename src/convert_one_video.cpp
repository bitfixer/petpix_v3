#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getFps(char* inputPrefix)
{
    char ffmpegCmd[1024];
    sprintf(ffmpegCmd, "ffmpeg -i %s.mp4 2>%s_info.txt", inputPrefix, inputPrefix);
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

void convert_video(char* videoFname, char* outputDir)
{
    printf("converting %s to %s\n", videoFname, outputDir);
    
    char prefix[256];
    char cmd[1024];
    // get prefix
    strcpy(prefix, videoFname);
    char* ext = strstr(prefix, ".mp4");
    *ext = 0;

    // get framerate
    int fps = getFps(prefix);
    printf("fps: %d\n", fps);

    // 40 column
    sprintf(cmd, "./stream2.sh %s %d 320 200 %s.p40 4000 -z", videoFname, fps, prefix);
    printf("%s\n", cmd);
    system(cmd);

    // 40 column dct
    sprintf(cmd, "./stream2.sh %s %d 320 200 %s_dct.p40 80", videoFname, fps, prefix);
    printf("%s\n", cmd);
    system(cmd);

    // 80 column
    sprintf(cmd, "./stream2.sh %s %d 640 200 %s.p80 4000 -z", videoFname, fps, prefix);
    printf("%s\n", cmd);
    system(cmd);

    // 80 column dct
    sprintf(cmd, "./stream2.sh %s %d 640 200 %s_dct.p80 80", videoFname, fps, prefix);
    printf("%s\n", cmd);
    system(cmd);
}

int main(int argc, char** argv)
{
    printf("arg count: %d\n", argc);
    char* outputDir = argv[1];
    for(int i = 2; i < argc; i++)
    {
        printf("%d: %s %s\n", i, argv[i], outputDir);
        convert_video(argv[i], outputDir);
    }
}