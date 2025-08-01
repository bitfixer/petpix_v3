
'use strict';

// Put variables in global scope to make them available to the browser console.
const video = document.querySelector('video');
const canvas = window.canvas = document.querySelector('canvas');

var screenWidth = window.innerWidth;
var screenHeight = window.innerHeight;

var rows = 25;
var characters = columns*rows;
var charDim = 8;

canvas.width = columns * charDim;
canvas.height = rows * charDim;

canvas.style.width = screenWidth + 'px';

var canvasRatio = screenWidth / canvas.width;
var canvasStyleHeight = canvas.height * canvasRatio;

if (columns == 40) {
    canvas.style.height = canvasStyleHeight + 'px';
} else {
    canvas.style.height = canvasStyleHeight*2 + 'px';
}

video.style.width = '1px';
video.style.height = '1px';

const testdiv = document.querySelector('#testdiv');
var captureInterval;
var pixRegion = new Float32Array(glyphDim * glyphDim);
var glyphResult = new Uint8Array(characters);
var glyphBrightness = new Float32Array(256);
var requestInProgress = false;
var queuedImage = false;

var drawGlyphs = true;

function getGlyphBrightness() {
    var g = 0;
    var gi = 0;
    var p = 0;
    for (g = 0; g < 256; g++)
    {
        var brightness = 0;
        gi = g*64;
        for (p = 0; p < glyphDim*glyphDim; p++)
        {
            brightness += glyphs[gi + p];
        }
        glyphBrightness[g] = brightness;
    }
}

function sendImageData() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "testupload.php", true);
    xhttp.onload = function() {
        captureInterval = setInterval(postSend, 0);
    }
    xhttp.send(glyphResult);
}

function drawGlyph(glyphIndex, pictureIndex, imdata) {
    var gind = glyphIndex*64;
    var regionIndex = 0;
    var imageIndex = 0;
    var yy;
    var xx;
    // write glyph pixels back into canvas
    for (yy = 0; yy < 8; yy++)
    {
        imageIndex = pictureIndex + (yy*canvas.width*4);
        for (xx = 0; xx < 8; xx++)
        {
            var vv = glyphs[gind + regionIndex];
            imdata.data[imageIndex] = vv;
            imdata.data[imageIndex+1] = vv;
            imdata.data[imageIndex+2] = vv;
            regionIndex++;
            imageIndex += 4;
        }
    }
}

// get pixels from the video element
// draw into canvas
// do video processing in the canvas
function captureImage() {
    clearInterval(captureInterval);

    var xScale = canvas.width / video.videoWidth;
    var scaledy, scaledYOffset, yOffset, outHeight;

    if (columns == 40) {
        // original logic
        scaledy = video.videoHeight * xScale;
        scaledYOffset = (scaledy - canvas.height) / 2.0;
        yOffset = scaledYOffset / xScale;
        outHeight = video.videoHeight - (2 * yOffset);
    } else if (columns == 80) {
        // pull twice as many vertical pixels from source
        // halve the vertical scale so we get a taller crop
        var adjustedScale = xScale;
        scaledy = video.videoHeight * adjustedScale * 0.5;
        scaledYOffset = (scaledy - canvas.height) / 2.0;
        yOffset = scaledYOffset / (adjustedScale * 0.5);
        outHeight = video.videoHeight - (2 * yOffset);
    } else {
        console.warn("Unsupported columns value:", columns);
        return;
    }

    var ctx = canvas.getContext('2d');
    preCapture();
    ctx.drawImage(video, 0, yOffset, video.videoWidth, outHeight, 0, 0, canvas.width, canvas.height);
    postCapture();


    var imdata = ctx.getImageData(0, 0, canvas.width, canvas.height);

    // get grayscale image
    var p = 0;
    var input_index = 0;
    var output_index = 0;
    var numpixels = canvas.width * canvas.height;

    var y = 0;
    var x = 0;
    var yy = 0;
    var xx = 0;
    var gind = 0;
    var glyph = 0;
    var pind = 0;
    var perr = 0;
    var glyphError = 0;
    var glyphResultIndex = 0;
    var imageIndex = 0;

    var horizGlyphDim = glyphDim;
    var horizGlyphScale = 1;
    var hg;

    //if (columns == 80)
    //{
    //    horizGlyphDim = glyphDim / 2;
    //    horizGlyphScale = 2;
    //}

    for (y = 0; y < canvas.height; y += glyphDim)
    {
        for (x = 0; x < canvas.width; x += horizGlyphDim)
        {
            pind = (y*canvas.width + x) * 4;
            var regionIndex = 0;
            var regionBrightness = 0;
            // copy block into pixel region
            for (yy = 0; yy < 8; yy++)
            {
                imageIndex = pind + (yy*canvas.width*4);
                for (xx = 0; xx < horizGlyphDim; xx++)
                {
                    var b = rval*imdata.data[imageIndex] + gval*imdata.data[imageIndex+1] + bval*imdata.data[imageIndex+2];
                    imageIndex = imageIndex + 4;

                    for (hg = 0; hg < horizGlyphScale; hg++)
                    {
                        pixRegion[regionIndex] = b;
                        regionBrightness += pixRegion[regionIndex];
                        regionIndex++;
                    }
                }
            }

            var minError = 999999999;
            var minErrorIndex = 0;
            // get error against every glyph for match
            for (glyph = 0; glyph < 256; glyph++)
            {
                // remove glyphs with brightness far from region brightness
                if (glyphBrightness[glyph] >= regionBrightness - brightnessRange && 
                    glyphBrightness[glyph] <= regionBrightness + brightnessRange)
                {
                    gind = glyph*64;
                    regionIndex = 0;
                    glyphError = 0;
                    for (yy = 0; yy < 8; yy++)
                    {
                        for (xx = 0; xx < 8; xx++)
                        {
                            perr = glyphs[gind + regionIndex] - pixRegion[regionIndex];
                            glyphError += perr*perr;
                            regionIndex++;
                        }
                    }

                    if (glyphError < minError)
                    {
                        minError = glyphError;
                        minErrorIndex = glyph;
                    }
                }
            }

            if (drawGlyphs) {
                drawGlyph(minErrorIndex, pind, imdata);
            }

            glyphResult[glyphResultIndex] = minErrorIndex;
            glyphResultIndex++;
        }
    }

    if (drawGlyphs) {
        canvas.getContext('2d').putImageData(imdata, 0, 0);
    }
    sendImageData();
}

getGlyphBrightness();