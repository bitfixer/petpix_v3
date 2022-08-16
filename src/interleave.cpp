#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* first = argv[1];
    char* second = argv[2];
    int size = atoi(argv[3]);

    FILE* fp_first = fopen(first, "rb");
    FILE* fp_second = fopen(second, "rb");

    int frameSize = sizeof(float) + size;
    uint8_t* firstData = new uint8_t[frameSize];
    uint8_t* secondData = new uint8_t[frameSize];

    int pick = 0;

    while (1)
    {
        if (fread(firstData, 1, frameSize, fp_first) != frameSize)
        {
            break;
        }
    
        if (fread(secondData, 1, frameSize, fp_second) != frameSize)
        {
            break;
        }

        if (pick == 0)
        {
            fwrite(firstData, 1, frameSize, stdout);
            pick = 1;
        }
        else
        {
            fwrite(secondData, 1, frameSize, stdout);
            pick = 0;
        }
    }

    fclose(fp_first);
    fclose(fp_second);
}