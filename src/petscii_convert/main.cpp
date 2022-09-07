#include <stdio.h>
#include "petsciiGlyphs.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "dct.h"
#include "timer.hpp"
#include "Image.hpp"
#include "Ditherer.hpp"

#include <array>
#include <algorithm>
#include <thread>

#define USE_1D_DCT 1
#define NUM_THREADS 25

#define FILTER_BY_BRIGHTNESS 0x01
#define FILTER_BY_QUAD 0x02
#define FILTER_BY_SIXTEENTHS 0x04
#define FILTER_BY_PIXELS 0x08

double **dctInput;
double *dctOutput;

double ***dctInputs;
double **dctOutputs;

double **dctSignatures;
double ****cosLookup;
double **cos1DLookup;
double **alphaLookup;
double *squareLookup;
double *sigSquareLookup;

unsigned char* outputGlyphs;

int* glyphScoreLookup;
int* sortedGlyphDctIndices;
int num_files;

uint8_t* glyphPixels;
uint32_t* glyphTotalBrightness;

uint32_t** glyphQuadrantTotalBrightness;
uint32_t** glyph16TotalBrightness;

//uint8_t* glyphIndexByBrightness;
uint8_t* glyphResults;
uint8_t* includedChars;

void init();
void convertImage(char *filename, int dim, float time = 0.0);
void convertImageFromRGB(unsigned char* rgb,
                         int width,
                         int height,
                         int dim,
                         float time,
                         FILE* fp_out,
                         bool output_image,
                         bool output_pts,
                         int searchRange);
void convertImageFromGray(unsigned char* gray,
                          int width,
                          int height,
                          int dim,
                          float time,
                          FILE* fp_out,
                          bool output_image,
                          bool output_pts,
                          int searchRange);
void convertImageFromGray2(unsigned char* gray,
                          int width,
                          int height,
                          int dim,
                          float time,
                          FILE* fp_out,
                          bool output_image,
                          bool output_pts,
                          int searchRange,
                          int frameNumber);
void convertImageFromGraySimple(unsigned char* gray,
                          int width,
                          int height,
                          int dim,
                          float time,
                          FILE* fp_out,
                          bool output_image,
                          bool output_pts,
                          int searchRange,
                          int quadRange,
                          int frameNumber);
void convertImageFromGraySimpleMultithreaded(
                                unsigned char* gray,
                                int width,
                                int height,
                                int dim,
                                float time,
                                FILE* fp_out,
                                bool output_image,
                                bool output_pts,
                                int searchRange,
                                int quadRange,
                                int frameNumber,
                                int numThreads,
                                int quadMeanDivisor,
                                uint8_t filterMask,
                                int quadFilterPct,
                                int sixteenthFilterPct,
                                bool excludeLetters,
                                bool brightnessOnly);
void writeGlyphToImageAtXY(Image& image,
                           int x,
                           int y,
                           int glyphIndex);

int getMatchingGlyph(double *dctSearch, int searchRange);

typedef enum {
    RGB,
    GRAY
} pixelFormat;

int main (int argc, char * const argv[]) {
    init();
    
    int c;
    float framerate = 10.0;
    int width = 320;
    int height = 200;
    FILE* fp_in = stdin;
    pixelFormat pf = RGB;
    bool output_image = false;
    bool output_pts = false;
    int searchRange = 30;
    int quadRange = 500;
    bool simple_search = false;
    int numThreads = 1;
    int quadMeanDivisor = 1;
    int quadFilterPct = 50;
    int sixteenthFilterPct = 50;
    bool excludeLetters = false;
    bool brightnessOnly = false;
    int totalFrames = 0;
    bool outputProgress = false;
    char progressFile[64];
    int progressPct = 0;

    sprintf(progressFile, "/mnt/tmp/prog");

    uint8_t filterMask = FILTER_BY_BRIGHTNESS | FILTER_BY_QUAD | FILTER_BY_SIXTEENTHS;
    
    while ((c = getopt(argc, argv, "f:w:h:p:i:ots:zq:n:d:m:e:r:t:xbg:v:")) != -1)
    {
        if (c == 'f') // framerate
        {
            framerate = atof(optarg);
        }
        else if (c == 'w') // width
        {
            width = atoi(optarg);
        }
        else if (c == 'h') // height
        {
            height = atoi(optarg);
        }
        else if (c == 'p') // pixel format
        {
            if (strcmp(optarg, "rgb") == 0)
            {
                pf = RGB;
            }
            else if (strcmp(optarg, "gray") == 0)
            {
                pf = GRAY;
            }
        }
        else if (c == 'i') // input fname
        {
            fp_in = fopen(optarg, "rb");
        }
        else if (c == 'o') // output image flag
        {
            output_image = true;
        }
        else if (c == 't') // output pts
        {
            output_pts = true;
        }
        else if (c == 's') // search range for dct match
        {
            searchRange = atoi(optarg);
        }
        else if (c == 'q')
        {
            quadRange = atoi(optarg);
        }
        else if (c == 'z')
        {
            simple_search = true;
        }
        else if (c == 'n')
        {
            numThreads = atoi(optarg);
        }
        else if (c == 'd')
        {
            quadMeanDivisor = atoi(optarg);
        }
        else if (c == 'm')
        {
            filterMask = atoi(optarg);
        }
        else if (c == 'e')
        {
            quadFilterPct = atoi(optarg);
        }
        else if (c == 'r')
        {
            sixteenthFilterPct = atoi(optarg);
        }
        else if (c == 'x')
        {
            excludeLetters = true;
        }
        else if (c == 'b')
        {
            brightnessOnly = true;
        }
        else if (c == 'g')
        {
            totalFrames = atoi(optarg);
            outputProgress = true;
            progressPct = 0;
        }
        else if (c == 'v')
        {
            strcpy(progressFile, optarg);
        }
    }
    
    int framesize = (pf == RGB) ? width * height * 3 : width * height;
    unsigned char* frame = new unsigned char[framesize];
    float frameTime = 0.0;
    float frameInterval = 1.0 / framerate;
    int frameNumber = 0;
    while (fread(frame, 1, framesize, fp_in) == framesize)
    {
        if (pf == RGB)
        {
            convertImageFromRGB(frame, width, height, 8, frameTime, stdout, output_image, output_pts, searchRange);
        }
        else if (pf == GRAY)
        {
            if (simple_search)
            {
                //convertImageFromGraySimple(frame, width, height, 8, frameTime, stdout, output_image, output_pts, searchRange, quadRange, frameNumber);
                convertImageFromGraySimpleMultithreaded(
                    frame, 
                    width, 
                    height, 
                    8, 
                    frameTime, 
                    stdout, 
                    output_image,
                    output_pts, 
                    searchRange, 
                    quadRange, 
                    frameNumber, 
                    numThreads, 
                    quadMeanDivisor, 
                    filterMask,
                    quadFilterPct,
                    sixteenthFilterPct,
                    excludeLetters,
                    brightnessOnly);
            }
            else
            {
                convertImageFromGray2(frame, width, height, 8, frameTime, stdout, output_image, output_pts, searchRange, frameNumber);
            }
        }
        frameTime += frameInterval;
        frameNumber++;

        float prog = (float)frameNumber * 100.0 / (float)totalFrames;
        if ((int)prog > progressPct)
        {
            progressPct = (int)prog;
            FILE* fp = fopen(progressFile, "wb");
            fprintf(fp, "%d", progressPct);
            fclose(fp);
        }
    }
    
    if (fp_in != stdin)
    {
        fclose(fp_in);
    }
    
    return 0;
}

double pixelBrightness(unsigned char *imageData, int width, int x, int y, int bytesPerPixel)
{
    int scale = 1;
    int pixelinfo = (((width*scale) * (y*scale)) + (x*scale)) * bytesPerPixel;
    
    unsigned char red = imageData[pixelinfo];
    unsigned char green = imageData[pixelinfo+1];
    unsigned char blue = imageData[pixelinfo+2];
    
    double dist;
    dist = sqrt((double)red*(double)red + (double)green*(double)green + (double)blue*(double)blue);
    dist = dist / sqrt(3.0);
    
    return dist;
}

void convertImageFromRGB(unsigned char* rgb,
                         int width,
                         int height,
                         int dim,
                         float time,
                         FILE* fp_out,
                         bool output_image,
                         bool output_pts,
                         int searchRange)
{
    unsigned char* gray = new unsigned char[width*height];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            gray[y*width + x] = (unsigned char)pixelBrightness(rgb, width, x, y, 3);
        }
    }
    
    convertImageFromGray(gray, width, height, dim, time, fp_out, output_image, output_pts, searchRange);
    delete[] gray;
}

void convertThreadFunc(unsigned char* gray,
                      int width,
                      int height,
                      int dim,
                      int searchRange,
                      double** ddctInput,
                      double* ddctOutput,
                      unsigned char* outputGlyphs)
{
    int matching;
    unsigned char glyphIndex;
    int numGlyphs = 0;

    for (int y = 0; y < height; y += dim)
    {
        for (int x = 0; x < width; x += dim)
        {
            // copy values into input buffer
            for (int yy = 0; yy < dim; yy ++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    ddctInput[xx][yy] = gray[(y+yy)*width + (x+xx)];
                }
            }
            
            dct1WithInput(ddctInput, ddctOutput, cos1DLookup, dim);
            matching = getMatchingGlyph(ddctOutput, searchRange);
            glyphIndex = (unsigned char)matching;
            
            outputGlyphs[numGlyphs++] = glyphIndex;
        }
    }
}

void writeGlyphToImageAtXY(Image& image, int x, int y, int glyphIndex, int dim)
{
    // write to png
    unsigned char *glyphString;
    int glyphPix = dim*dim;
    
    if (glyphIndex < 128)
    {
        glyphString = &glyphs[glyphIndex * glyphPix];
    }
    else
    {
        glyphString = &glyphs[(glyphIndex - 128)*glyphPix];
    }
    
    int ind;
    ind = 0;
    for (int yy = 0; yy < dim; yy ++)
    {
        for (int xx = 0; xx < dim; xx++)
        {
            Pixel* pixel = image.pixelAt(x+xx, y+yy);
            
            if ((glyphString[ind] == '0' && glyphIndex < 128) ||
                (glyphString[ind] == '1' && glyphIndex >= 128))
            {
                pixel->rgb[0] = 0;
                pixel->rgb[1] = 0;
                pixel->rgb[2] = 0;
            }
            else
            {
                pixel->rgb[0] = 1.0;
                pixel->rgb[1] = 1.0;
                pixel->rgb[2] = 1.0;
            }
            
            ind++;
        }
    }
}

void convertImageFromGray(unsigned char* gray,
                          int width,
                          int height,
                          int dim,
                          float time,
                          FILE* fp_out,
                          bool output_image,
                          bool output_pts,
                          int searchRange)
{
    int numThreads = NUM_THREADS;
    int numglyphs = (width/dim) * (height/dim);
    std::thread threads[numThreads];

    int sliceHeight = height / numThreads;
    int glyphsPerSlice = numglyphs / numThreads;

    if (output_pts)
    {
        // write pts to output stream
        fwrite(&time, sizeof(time), 1, fp_out);
    }

    for (int i = 0; i < numThreads; i++)
    {
        unsigned char* imgPtr = &gray[(sliceHeight*i)*width];
        threads[i] = std::thread(convertThreadFunc,
                                 imgPtr, 
                                 width, 
                                 sliceHeight, 
                                 dim, 
                                 searchRange, 
                                 dctInputs[i], 
                                 dctOutputs[i], 
                                 &outputGlyphs[glyphsPerSlice*i]);
    }

    // wait for threads to exit
    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }
    
    // write the output
    fwrite(outputGlyphs, 1 ,numglyphs, fp_out);
}

void convertThread(uint8_t* pixels,
                   uint8_t* results,
                   int width,
                   int height,
                   int dim,
                   int brightnessRange,
                   int quadRange,
                   int quadMeanDivisor,
                   uint8_t filterMask,
                   int quadFilterPct,
                   int sixteenthFilterPct,
                   bool excludeLetters,
                   bool brightnessOnly)
{
    uint8_t* region = new uint8_t[dim*dim];
    int numpixels = dim*dim;
    int resultIndex = 0;
    uint32_t sixteenthBrightness[16];
    uint32_t quadrantBrightness[4];

    uint8_t checkGlyph[256];
    uint8_t errorBuckets[163][256];
    uint8_t numInBucket[163];
    int maxToCheck = 0;
    int totalChecked = 0;

    bool filterByBrightness = (filterMask & FILTER_BY_BRIGHTNESS) > 0 ? true : false;
    bool filterByQuadBrightness = (filterMask & FILTER_BY_QUAD) > 0 ? true : false;
    bool filterbySixteenths = (filterMask & FILTER_BY_SIXTEENTHS) > 0 ? true : false;

    for (int y = 0; y < height; y += dim)
    {
        for (int x = 0; x < width; x += dim)
        {
            int index = 0;
            uint32_t totalBrightness = 0;
            for (int yy = 0; yy < dim; yy++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    region[index] = pixels[(y+yy)*width + (x+xx)];
                    index++;
                }
            }

            // get 16th brightness
            int section = 0;
            index = 0;
            for (int sy = 0; sy < 4; sy++)
            {
                for (int sx = 0; sx < 4; sx++)
                {
                    sixteenthBrightness[section] = 0;
                    for (int yy = 0; yy < dim/4; yy++)
                    {
                        for (int xx = 0; xx < dim/4; xx++)
                        {
                            int ii = index + (sy*2*8) + (sx*2) + (yy*8) + xx;
                            sixteenthBrightness[section] += region[ii];
                        }
                    }
                    section++;
                }
            }

            quadrantBrightness[0] = sixteenthBrightness[0] + sixteenthBrightness[1] + sixteenthBrightness[4] + sixteenthBrightness[5];
            quadrantBrightness[1] = sixteenthBrightness[2] + sixteenthBrightness[3] + sixteenthBrightness[6] + sixteenthBrightness[7];
            quadrantBrightness[2] = sixteenthBrightness[8] + sixteenthBrightness[9] + sixteenthBrightness[12] + sixteenthBrightness[13];
            quadrantBrightness[3] = sixteenthBrightness[10] + sixteenthBrightness[11] + sixteenthBrightness[14] + sixteenthBrightness[15];

            totalBrightness = quadrantBrightness[0] + quadrantBrightness[1] + quadrantBrightness[2] + quadrantBrightness[3];

            uint32_t min_error = 999999999;
            uint8_t matching = 0;

            uint32_t minBrightness = (totalBrightness >= brightnessRange) ? totalBrightness-brightnessRange : 0;
            uint32_t maxBrightness = totalBrightness + brightnessRange;

            //int32_t mean_error = 0;
            int32_t totalGlyphsToCheck = 256;
            int32_t totalGlyphsSecondStage = 256;

            // clear buckets
            memset(numInBucket, 0, 163);
            memset(checkGlyph, 1, 256);

            if (excludeLetters)
            {
                memcpy(checkGlyph, includedChars, 256);
            }
            
            if (filterByBrightness)
            {
                // filter only glyphs close enough to total brightness of this region
                totalGlyphsToCheck = 0;
                for (int g = 0; g < 256; g++)
                {
                    if (checkGlyph[g]) 
                    {
                        if (glyphTotalBrightness[g] >= minBrightness && glyphTotalBrightness[g] <= maxBrightness)
                        {
                            //checkGlyph[g] = 1;
                            totalGlyphsToCheck++;
                        }
                        else
                        {
                            checkGlyph[g] = 0;
                        }
                    }
                }
            }

            if (filterByQuadBrightness)
            {
                // get quad brightness error
                for (int g = 0; g < 256; g++)
                {
                    if (checkGlyph[g])
                    {
                        // check error from quadrant brightness
                        uint32_t quad_error = 0;
                        for (int q = 0; q < 4; q++)
                        {
                            int e = (int)glyphQuadrantTotalBrightness[g][q] - quadrantBrightness[q];
                            quad_error += e >= 0 ? e : -e;
                        }
                        int bindex = quad_error / 100;
                        errorBuckets[bindex][numInBucket[bindex]] = g;
                        numInBucket[bindex]++;
                    }
                    checkGlyph[g] = 0;
                }

                totalGlyphsSecondStage = 0;
                //int maxToCheck = totalGlyphsToCheck / 2;
                //maxToCheck = 30;
                maxToCheck = totalGlyphsToCheck * quadFilterPct / 100;
                if (maxToCheck < 1)
                {
                    maxToCheck = 1;
                }
                for (int b = 0; b < 163; b++)
                {
                    for (int gi = 0; gi < numInBucket[b]; gi++)
                    {
                        checkGlyph[errorBuckets[b][gi]] = true;
                        totalGlyphsSecondStage++;
                        if (totalGlyphsSecondStage >= maxToCheck)
                        {
                            b = 163;
                            break;
                        }
                    }
                }

                memset(numInBucket, 0, 163);
            }

            
            if (filterbySixteenths)
            {
                // second stage
                for (int g = 0; g < 256; g++)
                {
                    if (checkGlyph[g])
                    {
                        uint32_t sError = 0;
                        for (int i = 0; i < 16; i++)
                        {
                            int e = (int)glyph16TotalBrightness[g][i] - (int)sixteenthBrightness[i];
                            sError += e >= 0 ? e : -e;
                        }
                        int bindex = sError / 100;
                        errorBuckets[bindex][numInBucket[bindex]] = g;
                        numInBucket[bindex]++;
                    }
                    checkGlyph[g] = 0;
                }

                totalChecked = 0;
                maxToCheck = totalGlyphsSecondStage * sixteenthFilterPct / 100;
                if (maxToCheck < 1)
                {
                    maxToCheck = 1;
                }
                for (int b = 0; b < 163; b++)
                {
                    for (int gi = 0; gi < numInBucket[b]; gi++)
                    {
                        checkGlyph[errorBuckets[b][gi]] = true;
                        totalChecked++;
                        if (totalChecked >= maxToCheck)
                        {
                            b = 163;
                            break;
                        }
                    }
                }
            }

            if (brightnessOnly)
            {
                for (int g = 0; g < 256; g++)
                {
                    if (checkGlyph[g])
                    {
                        uint32_t error = 0;
                        if (totalBrightness > glyphTotalBrightness[g])
                        {
                            error = totalBrightness - glyphTotalBrightness[g];
                        }
                        else
                        {
                            error = glyphTotalBrightness[g] - totalBrightness;
                        }

                        if (error < min_error)
                        {
                            min_error = error;
                            matching = g;
                        }
                    }
                }
            }
            else
            {
                for (int g = 0; g < 256; g++)
                {
                    if (checkGlyph[g])
                    {
                        uint8_t* glyph = &glyphPixels[g * 64];
                        uint32_t error = 0;
                        for (int p = 0; p < numpixels; p++)
                        {
                            int e = (int)glyph[p] - (int)region[p];
                            error += e*e;
                        }

                        if (error < min_error)
                        {
                            min_error = error;
                            matching = g;
                        }
                    }
                }
            }

            //fprintf(stderr, "check1 %d check2 %d total checked %d matched %d\n", totalGlyphsToCheck, totalGlyphsSecondStage, totalChecked, matching);

            results[resultIndex++] = matching;
            //results[resultIndex] = resultIndex;
            //resultIndex++;
        }
    }
    delete(region);
}

void convertImageFromGraySimpleMultithreaded(
                                unsigned char* gray,
                                int width,
                                int height,
                                int dim,
                                float time,
                                FILE* fp_out,
                                bool output_image,
                                bool output_pts,
                                int searchRange,
                                int quadRange,
                                int frameNumber,
                                int numThreads,
                                int quadMeanDivisor,
                                uint8_t filterMask,
                                int quadFilterPct,
                                int sixteenthFilterPct,
                                bool excludeLetters,
                                bool brightnessOnly)
{
    Tools::Timer* timer = Tools::Timer::createTimer();
    Image outputImage(width, height);
    int rows = height / dim;
    int cols = width / dim;
    int rowsPerThread = rows / numThreads; // make sure this is divisible evenly
    int charactersPerRow = width / dim;
    int charactersPerThread = rowsPerThread * charactersPerRow;
    int numCharacters = rows*cols;

    /*
    uint8_t** threadResults = (uint8_t**)malloc(sizeof(uint8_t*) * numThreads);
    for (int i = 0; i < numThreads; i++)
    {
        threadResults[i] = (uint8_t*)malloc(sizeof(uint8_t) * charactersPerThread);
    }
    */

    uint8_t* threadRowPtr = gray;
    std::thread** threads = (std::thread**)malloc(sizeof(std::thread*) * numThreads);

    uint8_t* threadResults = glyphResults;

    timer->start();
    for (int i = 0; i < numThreads; i++)
    {
        // launch one thread per section
        threads[i] = new std::thread(
            convertThread, 
            threadRowPtr, 
            threadResults,
             width, 
             rowsPerThread*dim, 
             dim, 
             searchRange, 
             quadRange, 
             quadMeanDivisor,
             filterMask,
             quadFilterPct,
             sixteenthFilterPct,
             excludeLetters,
             brightnessOnly);
        //convertThread(threadRowPtr, threadResults[i], width, rowsPerThread*dim, dim, searchRange, quadRange);
        threadRowPtr += (rowsPerThread*dim) * width;
        threadResults += charactersPerThread;
    }

    for (int i = 0; i < numThreads; i++)
    {
        threads[i]->join();
        delete(threads[i]);
    }
    double elapsed = timer->getTime();

    if (output_image)
    {
        int y = 0;
        int x = 0;
        for (int c = 0; c < numCharacters; c++)
        {
            writeGlyphToImageAtXY(outputImage, x, y, glyphResults[c], dim);
            x += dim;
            if (x >= width)
            {
                x = 0;
                y += dim;
            }
        }

        char fname[100];
        sprintf(fname, "image_%04d.ppm", frameNumber);
        outputImage.writePPM(fname);
    }

    if (output_pts)
    {
        fwrite(&time, sizeof(time), 1, fp_out);
    }

    fwrite(glyphResults, 1, numCharacters, fp_out);

    free(threads);
    //fprintf(stderr, "elapsed: %f\n", elapsed);
}


void convertImageFromGraySimple(unsigned char* gray,
                                int width,
                                int height,
                                int dim,
                                float time,
                                FILE* fp_out,
                                bool output_image,
                                bool output_pts,
                                int searchRange,
                                int quadRange,
                                int frameNumber)
{
    char bmpFname[100];
    bool predither = false;
    Tools::Timer* timer = Tools::Timer::createTimer();
    double matchTime = 0.0;
    int brightnessRange = searchRange;
    
    if (predither) {
        char ditheredFname[100];
        Image inputImage(width, height);

        unsigned char bw_colors[] =
        {
            0,      0,      0,
            255,    255,    255
        };

        int num_bw_colors = 2;
        Palette bwPalette(bw_colors, num_bw_colors);
        Ditherer* ditherer = Ditherer::createFloydSteinbergDitherer();

        int index = 0;
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                float p = (float)gray[index++] / 255.0;
                Pixel* pixel = inputImage.pixelAt(w, h);
                pixel->rgb[0] = p;
                pixel->rgb[1] = p;
                pixel->rgb[2] = p;
            }
        }

        ditherer->ditherImageInPlaceWithPalette(inputImage, bwPalette);

        index = 0;
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                Pixel* pixel = inputImage.pixelAt(w, h);
                if (pixel->rgb[0] > 0.5)
                {
                    gray[index++] = 255;
                }
                else
                {
                    gray[index++] = 0;
                }
            }
        }

        sprintf(ditheredFname, "dithered_%d.ppm", frameNumber);
        inputImage.writePPM(ditheredFname);
    }

    Image outputImage(width, height);
    sprintf(bmpFname, "image_%04d.ppm", frameNumber);
    
    if (output_pts)
    {
        fwrite(&time, sizeof(time), 1, fp_out);
    }

    uint8_t* region = new uint8_t[dim*dim];
    for (int y = 0; y < height; y += dim)
    {
        for (int x = 0; x < width; x += dim)
        {
            //printf("x, y, %d %d\n", x, y);
            // copy values into input buffer
            int index = 0;
            uint32_t totalBrightness = 0;
            uint32_t quadrantBrightness[4];

            for (int yy = 0; yy < dim; yy++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    region[index] = gray[(y+yy)*width + (x+xx)];
                    totalBrightness += region[index];
                    index++;
                }
            }

            int quadrant = 0;
            index = 0;
            for (int qy = 0; qy < 2; qy++)
            {
                for (int qx = 0; qx < 2; qx++)
                {
                    quadrantBrightness[quadrant] = 0;
                    for (int yy = 0; yy < dim/2; yy++)
                    {
                        for (int xx = 0; xx < dim/2; xx++)
                        {
                            int ii = index + (qx*4) + (yy*8) + xx;
                            quadrantBrightness[quadrant] += region[ii];
                        }
                    }
                    quadrant++;
                }
                index += 4*8;
            }

            /*
            for (int yy = 0; yy < dim; yy++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    region[index] = gray[(y+yy)*width + (x+xx)];
                    //region[index++] = 128;
                    totalBrightness += region[index];
                    index++;
                }
            }
            */

            //printf("1\n");
            uint32_t min_error = 999999999;
            uint8_t matching = 0;
            int numpixels = dim*dim;
            // now find glyph with minimum error
            // compare this region against petscii glyphs
            timer->start();
            uint32_t minBrightness;
            uint32_t maxBrightness;

            minBrightness = (totalBrightness >= brightnessRange) ? totalBrightness-brightnessRange : 0;
            maxBrightness = totalBrightness + brightnessRange;

            uint32_t minQuadBrightness[4];
            uint32_t maxQuadBrightness[4];
            for (int i = 0; i < 4; i++)
            {
                if (quadrantBrightness[i] >= quadRange) {
                    minQuadBrightness[i] = quadrantBrightness[i] - quadRange;
                } else {
                    minQuadBrightness[i] = 0;
                }

                maxQuadBrightness[i] = quadrantBrightness[i] + quadRange;
            }
            


            for (int g = 0; g < 256; g++)
            {
                if (glyphTotalBrightness[g] >= minBrightness && glyphTotalBrightness[g] <= maxBrightness)
                {
                    bool check = true;
                    //int gi = glyphIndexByBrightness[g];
                    int gi = g;
                    for (int i = 0; i < 4; i++)
                    {
                        if (glyphQuadrantTotalBrightness[gi][i] < minQuadBrightness[i] || glyphQuadrantTotalBrightness[gi][i] > maxQuadBrightness[i])
                        {
                            check = false;
                            break;
                        }
                    }

                    if (check)
                    {

                        uint8_t* glyph = &glyphPixels[gi * 64];
                        uint32_t error = 0;
                        for (int p = 0; p < numpixels; p++)
                        {
                            int e = (int)glyph[p] - (int)region[p];
                            error += e*e;
                        }

                        if (error < min_error)
                        {
                            min_error = error;
                            matching = gi;
                        }
                    }
                }
            }
            matchTime += timer->getTime();

            fwrite(&matching, 1, 1, fp_out);
            if (output_image)
            {
                writeGlyphToImageAtXY(outputImage, x, y, matching, dim);
            }
        }
    }
    delete(region);

    if (output_image)
    {
        outputImage.writePPM(bmpFname);
    }

    fprintf(stderr, "match time %f\n", matchTime);
}

void convertImageFromGray2(unsigned char* gray,
                          int width,
                          int height,
                          int dim,
                          float time,
                          FILE* fp_out,
                          bool output_image,
                          bool output_pts,
                          int searchRange,
                          int frameNumber)
{
    char bmpFname[100];
    Image outputImage(width, height);
    Tools::Timer* timer = Tools::Timer::createTimer();
    double dctTime = 0.0;
    double matchTime = 0.0;
    double convTime = 0.0;
    
    int matching;
    unsigned char glyphIndex;
    //fprintf(stderr, "converting rgb frame at time %f\n", time);
    
    if (output_pts)
    {
        // write pts to output stream
        fwrite(&time, sizeof(time), 1, fp_out);
    }

    for (int y = 0; y < height; y += dim)
    {
        for (int x = 0; x < width; x += dim)
        {
            // copy values into input buffer
            for (int yy = 0; yy < dim; yy ++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    dctInput[xx][yy] = gray[(y+yy)*width + (x+xx)];
                }
            }
            
            timer->start();
#ifdef USE_1D_DCT
            dct1WithInput(dctInput, dctOutput, cos1DLookup, dim);
#else
            dctWithInput(dctInput, dctOutput, cosLookup, dim);
#endif
            dctTime += timer->getTime();
            
            timer->start();
            matching = getMatchingGlyph(dctOutput, searchRange);
            matchTime += timer->getTime();
            
            glyphIndex = (unsigned char)matching;
            
            fwrite(&glyphIndex, 1, 1, fp_out);
            
            if (output_image)
            {
                writeGlyphToImageAtXY(outputImage, x, y, matching, dim);
            }
        }
    }
    if (output_image)
    {
        sprintf(bmpFname, "image_%04d.ppm", frameNumber);
        outputImage.writePPM(bmpFname);
    }
    
    fprintf(stderr, "dct time %lf match time %lf\n", dctTime, matchTime);
}

double getDctDiffBetween(double *inputA, double *inputB, double sum_A, double sum_B, int dim)
{
    double score, diff;
    int points = dim*dim;
    score = 0;
    
    for (int i = 0; i < points; i++)
    {
        diff = inputA[i]*inputB[i];
        score += diff;
    }
    
    score = sum_A + sum_B - 2*score;
    return score;
}

int getMatchingGlyph(double *dctSearch, int searchRange)
{
    double lowest = -1;
    double curr_score;
    int matchIndex;
    
    double sumOfSquares;
    sumOfSquares = 0;
    
    for (int i = 0; i < 64; i++)
    {
        sumOfSquares += (dctSearch[i]*dctSearch[i]);
    }
    
    // get closest index into sorted glyph table
    int lookupIndex = (int)dctSearch[0];
    int sortedIndex = glyphScoreLookup[lookupIndex];
    
    int startIndex = sortedIndex - searchRange;
    if (startIndex < 0)
    {
        startIndex = 0;
    }
    
    int endIndex = sortedIndex + searchRange;
    if (endIndex > 255)
    {
        endIndex = 255;
    }
    
    for (int d = startIndex; d < endIndex; d++)
    {
        int dctIndex = sortedGlyphDctIndices[d];
        curr_score = getDctDiffBetween(dctSearch, dctSignatures[dctIndex], sumOfSquares, sigSquareLookup[dctIndex], 8);
        
        if (lowest == -1)
        {
            matchIndex = dctIndex;
            lowest = curr_score;
        }
        else if (curr_score < lowest)
        {
            matchIndex = dctIndex;
            lowest = curr_score;
        }
    }
    
    return matchIndex;
}

int getMatchingGlyph2(double *dctSearch)
{
    double lowest = -1;
    double curr_score;
    int matchIndex;
    
    double sumOfSquares;
    sumOfSquares = 0;
    
    for (int i = 0; i < 64; i++)
    {
        sumOfSquares += (dctSearch[i]*dctSearch[i]);
    }
    
    for (int d = 0; d < 256; d++)
    {
        curr_score = getDctDiffBetween(dctSearch, dctSignatures[d], sumOfSquares, sigSquareLookup[d], 8);
        
        if (d == 0)
        {
            matchIndex = d;
            lowest = curr_score;
        }
        else if (curr_score < lowest)
        {
            matchIndex = d;
            lowest = curr_score;
        }
    }
    
    return matchIndex;
}

void prepareGlyphSignatures()
{
    unsigned char *glyphString;
    
    for (int ch = 0; ch < 256; ch++)
    {
        if (ch < 128)
        {
            glyphString = &glyphs[ch * 64];
        }
        else 
        {
            glyphString = &glyphs[(ch - 128) * 64];
        }
        
        int index = 0;
        unsigned char bit;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                
                bit = glyphString[index];
                
                if (bit == '0')
                {
                    if (ch < 128)
                        dctInput[x][y] = 0;
                    else 
                        dctInput[x][y] = 255;
                }
                else 
                {
                    if (ch < 128)
                        dctInput[x][y] = 255;
                    else 
                        dctInput[x][y] = 0;
                }
                
                index++;
            }
        }
        
#ifdef USE_1D_DCT
        dct1WithInput(dctInput, dctSignatures[ch], cos1DLookup, 8);
#else
        dctWithInput(dctInput, dctSignatures[ch], cosLookup, 8);
#endif
        
        double thissig;
        thissig = 0;
        for (int i = 0; i < 64; i++)
        {
            thissig += (dctSignatures[ch][i] * dctSignatures[ch][i]);
        }
        sigSquareLookup[ch] = thissig;
    }
    
    // create sorted list of indices
    std::array<int, 256> indices;
    for (int i = 0; i < 256; i++)
    {
        indices[i] = i;
    }
    
    // sort function
    struct {
        bool operator()(int a, int b) const
        {
            return dctSignatures[a][0] < dctSignatures[b][0];
        }
    } compFn;
    std::sort(indices.begin(), indices.end(), compFn);
    
    sortedGlyphDctIndices = new int[256];
    
    for (int i = 0; i < 256; i++)
    {
        sortedGlyphDctIndices[i] = indices[i];
    }
    
    // create score lookup table
    glyphScoreLookup = new int[4096];
    for (int i = 0; i < 4096; i++)
    {
        double lookupScore = (double)i;
        int j = 0;
        for (j = 0; j < 256; j++)
        {
            if (dctSignatures[sortedGlyphDctIndices[j]][0] >= lookupScore)
            {
                break;
            }
        }
        
        if (j < 256)
        {
            glyphScoreLookup[i] = j;
        }
        else
        {
            glyphScoreLookup[i] = 255;
        }
    }
}

void init()
{
    dctSignatures = (double **)malloc(sizeof(double *) * 256);
    for (int i = 0; i < 256; i++)
    {
        dctSignatures[i] = (double *)malloc(sizeof(double) * 64);
    }
    
    dctInput = (double **)malloc(sizeof(double *) * 8);
    for (int i = 0; i < 8; i++)
    {
        dctInput[i] = (double *)malloc(sizeof(double) * 8);
    }

    dctInputs = (double ***)malloc(sizeof(double**) * NUM_THREADS);
    for (int t = 0; t < NUM_THREADS; t++)
    {
        dctInputs[t] = (double **)malloc(sizeof(double *) * 8);
        for (int i = 0; i < 8; i++)
        {
            dctInputs[t][i] = (double *)malloc(sizeof(double) * 8);
        }
    }
    
    dctOutput = (double *)malloc(sizeof(double) * 64);

    dctOutputs = (double**)malloc(sizeof(double*) * NUM_THREADS);
    for (int t = 0; t < NUM_THREADS; t++)
    {
        dctOutputs[t] = (double *)malloc(sizeof(double) * 64);
    }
    
    
    cosLookup = (double ****)malloc(sizeof(double ***) * 8);
    for (int i = 0; i < 8; i++)
    {
        cosLookup[i] = (double ***)malloc(sizeof(double**) * 8);
        
        for (int j = 0; j < 8; j++)
        {
            cosLookup[i][j] = (double **)malloc(sizeof(double *) * 8);
            
            for (int k = 0; k < 8; k++)
            {
                cosLookup[i][j][k] = (double *)malloc(sizeof(double) * 8);
            }
        }
    }
    
    cos1DLookup = (double**)malloc(sizeof(double*) * 8);
    for (int i = 0; i < 8; i++)
    {
        cos1DLookup[i] = (double*)malloc(sizeof(double) * 8);
    }
    
    alphaLookup = (double **)malloc(sizeof(double *) * 8);
    for (int i = 0; i < 8; i++)
    {
        alphaLookup[i] = (double *)malloc(sizeof(double) * 8);
    }
    
    outputGlyphs = (unsigned char*)malloc(sizeof(unsigned char) * 2000);

    sigSquareLookup = (double *)malloc(sizeof(double) * 256);
    generateAlphaLookup(alphaLookup, 8);
    generateCosLookup(cosLookup, alphaLookup, 8);
    generateCos1DLookup(cos1DLookup, 8);
    prepareGlyphSignatures();

    glyphPixels = (uint8_t*)malloc(sizeof(uint8_t) * 256 * 64);
    glyphTotalBrightness = (uint32_t*)malloc(sizeof(uint32_t) * 256);
    //glyphIndexByBrightness = (uint8_t*)malloc(sizeof(uint8_t) * 256);
    // no inverse
    int gi = 0;

    int32_t tempBrightness[256];
    //int32_t tempQuadrantBrightness[256][4];
    for (int i = 0; i < 128; i++)
    {
        tempBrightness[i] = 0;
        for (int j = 0; j < 64; j++)
        {
            glyphPixels[gi] = (glyphs[gi] == '1') ? 255 : 0;
            tempBrightness[i] += glyphPixels[gi];
            gi++;
        }
    }

    // inverse
    gi = 0;
    for (int i = 0; i < 128; i++)
    {
        tempBrightness[i+128] = 0;
        for (int j = 0; j < 64; j++)
        {
            glyphPixels[gi + (128*64)] = (glyphs[gi] == '1') ? 0 : 255;
            tempBrightness[i+128] += glyphPixels[gi + (128*64)];
            gi++;
        }
    }

    glyphQuadrantTotalBrightness = (uint32_t**)malloc(sizeof(uint32_t*) * 256);
    for (int i = 0; i < 256; i++)
    {
        glyphQuadrantTotalBrightness[i] = (uint32_t*)malloc(sizeof(uint32_t) * 4);
    }

    // quadrant brightness
    for (int i = 0; i < 256; i++)
    {
        gi = i*64;
        int quadrant = 0;
        for (int qy = 0; qy < 2; qy++)
        {
            for (int qx = 0; qx < 2; qx++)
            {
                // new quadrant
                glyphQuadrantTotalBrightness[i][quadrant] = 0;
                for (int yy = 0; yy < 4; yy++)
                {
                    for (int xx = 0; xx < 4; xx++)
                    {
                        int gii = gi + (qy*4*8) + (qx*4) + (yy*8) + xx;
                        glyphQuadrantTotalBrightness[i][quadrant] += glyphPixels[gii];
                    }
                }
                quadrant++;
            }
        }
        fprintf(stderr, "glyph %d tb %d qb %d %d %d %d\n", 
            i,
            tempBrightness[i],
            glyphQuadrantTotalBrightness[i][0],
            glyphQuadrantTotalBrightness[i][1],
            glyphQuadrantTotalBrightness[i][2],
            glyphQuadrantTotalBrightness[i][3]);
    }

    glyph16TotalBrightness = (uint32_t**)malloc(sizeof(uint32_t*) * 256);
    for (int i = 0; i < 256; i++)
    {
        glyph16TotalBrightness[i] = (uint32_t*)malloc(sizeof(uint32_t) * 16);
    }

    for (int i = 0; i < 256; i++)
    {
        gi = i*64;
        int section = 0;
        for (int sy = 0; sy < 4; sy++)
        {
            for (int sx = 0; sx < 4; sx++)
            {
                glyph16TotalBrightness[i][section] = 0;
                for (int yy = 0; yy < 2; yy++)
                {
                    for (int xx = 0; xx < 2; xx++)
                    {
                        int gii = gi + (sy*2*8) + (sx*2) + (yy*8) + xx;
                        glyph16TotalBrightness[i][section] += glyphPixels[gii];
                    }
                }
                section++;
            }
        }
    }

    for (int i = 0; i < 256; i++)
    {
        glyphTotalBrightness[i] = tempBrightness[i];
    }

    glyphResults = (uint8_t*)malloc(sizeof(uint8_t) * 2000);

    includedChars = (uint8_t*)malloc(sizeof(uint8_t) * 256);

    memset(includedChars, 1, 256);
    memset(includedChars, 0, 64);
    includedChars[65] = 0;
    includedChars[81] = 0;
    includedChars[83] = 0;
    includedChars[88] = 0;
    includedChars[90] = 0;
    includedChars[94] = 0;

    memcpy(includedChars+128, includedChars, 128);
}
