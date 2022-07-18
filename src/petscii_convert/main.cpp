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
                          int frameNumber);
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
    bool simple_search = false;
    
    while ((c = getopt(argc, argv, "f:w:h:p:i:ots:z")) != -1)
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
        else if (c == 'z')
        {
            simple_search = true;
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
                convertImageFromGraySimple(frame, width, height, 8, frameTime, stdout, output_image, output_pts, frameNumber);
            }
            else
            {
                convertImageFromGray2(frame, width, height, 8, frameTime, stdout, output_image, output_pts, searchRange, frameNumber);
            }
        }
        frameTime += frameInterval;
        frameNumber++;
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

void convertImageFromGraySimple(unsigned char* gray,
                                int width,
                                int height,
                                int dim,
                                float time,
                                FILE* fp_out,
                                bool output_image,
                                bool output_pts,
                                int frameNumber)
{
    char bmpFname[100];
    char ditheredFname[100];
    Image outputImage(width, height);
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

    sprintf(bmpFname, "image_%d.ppm", frameNumber);
    sprintf(ditheredFname, "dithered_%d.ppm", frameNumber);
    if (output_pts)
    {
        fwrite(&time, sizeof(time), 1, fp_out);
    }

    inputImage.writePPM(ditheredFname);

    uint8_t* region = new uint8_t[dim*dim];
    for (int y = 0; y < height; y += dim)
    {
        for (int x = 0; x < width; x += dim)
        {
            //printf("x, y, %d %d\n", x, y);
            // copy values into input buffer
            int index = 0;
            for (int yy = 0; yy < dim; yy++)
            {
                for (int xx = 0; xx < dim; xx++)
                {
                    region[index++] = gray[(y+yy)*width + (x+xx)];
                    //region[index++] = 128;
                }
            }

            //printf("1\n");
            uint32_t min_error = 999999999;
            uint8_t matching = 0;
            // now find glyph with minimum error
            // compare this region against petscii glyphs
            for (int g = 0; g < 256; g++)
            {
                //printf("g %d\n", g);
                int glyphIndex = (g < 128) ? g : g-128;
                bool inverse = g >= 128;

                unsigned char* glyph = &glyphs[glyphIndex * 8 * 8];
                uint32_t error = 0;
                for (int p = 0; p < dim*dim; p++)
                {
                    //printf("p %d\n", p);
                    //int glyphPix = inverse ? glyph[p] : 1 - glyph[p];
                    int glyphPix = glyph[p] == '1' ? 255 : 0;
                    if (inverse)
                    {
                        glyphPix = 255 - glyphPix;
                    }

                    int e = glyphPix - (int)region[p];
                    //printf("x %d y %d g %d p %d gp %d r %d\n", x, y, g, p, glyphPix, region[p]);
                    error += e*e;
                }

                if (error < min_error)
                {
                    min_error = error;
                    matching = g;
                }
            }

            fwrite(&matching, 1, 1, fp_out);
            if (output_image)
            {
                /*
                // write to png
                unsigned char *glyphString;
                int glyphPix = dim*dim;
                
                if (matching < 128)
                {
                    glyphString = &glyphs[matching * glyphPix];
                }
                else
                {
                    glyphString = &glyphs[(matching - 128)*glyphPix];
                }
                
                int ind;
                ind = 0;
                for (int yy = 0; yy < dim; yy ++)
                {
                    for (int xx = 0; xx < dim; xx++)
                    {
                        Pixel* pixel = outputImage.pixelAt(x+xx, y+yy);
                        
                        if ((glyphString[ind] == '0' && matching < 128) ||
                            (glyphString[ind] == '1' && matching >= 128))
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
                */
                writeGlyphToImageAtXY(outputImage, x, y, matching, dim);
            }
        }
    }
    if (output_image)
    {
        outputImage.writePPM(bmpFname);
    }
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
        sprintf(bmpFname, "image_%d.ppm", frameNumber);
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
}
