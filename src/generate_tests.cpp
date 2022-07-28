#include <stdio.h>
#include <stdlib.h>

//./stream2.sh $1 30 320 200 $2 $3 -z
//ffmpeg -i $1 -vf scale=$3:$4 -y -r $2 -vcodec rawvideo -pix_fmt gray -f rawvideo pipe:1 2>/dev/null | \
//bin/petscii_convert -f $2 -w $3 -h $4 -p gray -t $8 $7 -s $6 -n 5 -m 1 2>/dev/null > $5

void generateTest(char* inputPrefix, bool brightnessOnly, bool useDct, int searchRange, int width, int height, int fps)
{
    char convertCmd[1024];
    char outputFname[256];

    int mask = 1;
    if (brightnessOnly)
    {
        sprintf(outputFname, "%s_br.psc", inputPrefix);
        mask = 0;
    }
    else if (useDct)
    {
        sprintf(outputFname, "%s_%d_dct.psc", inputPrefix, searchRange);
    }
    else
    {
        sprintf(outputFname, "%s_%d.psc", inputPrefix, searchRange);
    }
    sprintf(convertCmd, "cat %s.raw | bin/petscii_convert -f %d -w %d -h %d -p gray -t -o %s %s -s %d -n 5 -m %d 2>/dev/null > %s", 
        inputPrefix,
        fps, 
        width,
        height, 
        useDct ? "" : "-z",
        brightnessOnly ? "-b" : "",
        searchRange,
        mask,
        outputFname);

    printf("running:\n%s\n", convertCmd);
    system(convertCmd);
    printf("done.\n");

    // now create petscii mp4
    char outMp4Fname[256];
    if (brightnessOnly)
    {
        sprintf(outMp4Fname, "%s_br.mp4", inputPrefix);
    }
    else if (useDct)
    {
        sprintf(outMp4Fname, "%s_pet_%d_dct.mp4", inputPrefix, searchRange);
    }
    else
    {
        sprintf(outMp4Fname, "%s_pet_%d.mp4", inputPrefix, searchRange);
    }
    printf("output mp4: %s\n", outMp4Fname);

    char ffmpegCmd[1024];
    sprintf(ffmpegCmd, "ffmpeg -i image_%%04d.ppm -y -c:v libx264 -pix_fmt yuv420p -r %d %s", fps, outMp4Fname);
    printf("running:\n%s\n", ffmpegCmd);
    system(ffmpegCmd);

    char cleanCmd[256];
    sprintf(cleanCmd, "rm *.ppm");
    system(cleanCmd);
}

int main(int argc, char** argv)
{
    char* inputPrefix = argv[1];
    int duration = -1;
    if (argc > 2)
    {
        duration = atoi(argv[2]);
    }

    int width = 320;
    int height = 200;
    int fps = 30;

    char ffmpegCmd[1024];
    char dur[10];
    if (duration > 0)
    {
        sprintf(dur, "-t %d", duration);
    }
    else
    {
        sprintf(dur, "");
    }

    sprintf(ffmpegCmd, "ffmpeg -i %s.mp4 %s -vf scale=%d:%d -y -r %d -vcodec rawvideo -pix_fmt gray -f rawvideo %s.raw 2>/dev/null", 
        inputPrefix,
        dur,
        width, 
        height, 
        fps,
        inputPrefix);

    printf("running:\n%s\n", ffmpegCmd);
    system(ffmpegCmd);

    generateTest(inputPrefix, true, false, 3000, width, height, fps);
    generateTest(inputPrefix, false, false, 3000, width, height, fps);
    generateTest(inputPrefix, false, false, 4000, width, height, fps);
    generateTest(inputPrefix, false, false, 8000, width, height, fps);
    generateTest(inputPrefix, false, false, 17000, width, height, fps);
    generateTest(inputPrefix, false, true, 80, width, height, fps);
    

    char cleanCmd[256];
    sprintf(cleanCmd, "rm %s.raw", inputPrefix);
    system(cleanCmd);
}