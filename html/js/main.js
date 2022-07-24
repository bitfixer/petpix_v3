
'use strict';

// Put variables in global scope to make them available to the browser console.
const video = document.querySelector('video');
const canvas = window.canvas = document.querySelector('canvas');

canvas.width = 320;
canvas.height = 200;
canvas.style.width = '320px';
canvas.style.height = '200px';

video.style.width = '1px';
video.style.height = '1px';

const testdiv = document.querySelector('#testdiv');
var captureInterval;
var pixRegion = new Float32Array(glyphDim * glyphDim);
var glyphResult = new Uint8Array(1000);
var glyphBrightness = new Float32Array(256);

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

function captureImage() {
    clearInterval(captureInterval);

    var xScale = 320.0 / video.videoWidth;
    var scaledy = video.videoHeight * xScale;
    var scaledYOffset = (scaledy - 200.0) / 2.0;
    var yOffset = scaledYOffset / xScale;
    var outHeight = video.videoHeight - (2 * yOffset);

    var ctx = canvas.getContext('2d');

    if (facing == "f") 
    {
        ctx.translate(320,0);
        ctx.scale(-1,1);
    }   
    canvas.getContext('2d').drawImage(video, 0, yOffset, video.videoWidth, outHeight, 0, 0, canvas.width, canvas.height);
    if (facing == "f")
    {
        ctx.setTransform(1,0,0,1,0,0);
    }

    var imdata = canvas.getContext('2d').getImageData(0, 0, canvas.width, canvas.height);

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
    for (y = 0; y < canvas.height; y += glyphDim)
    {
        for (x = 0; x < canvas.width; x += glyphDim)
        {
            pind = (y*canvas.width + x) * 4;
            var regionIndex = 0;
            var regionBrightness = 0;
            // copy block into pixel region
            for (yy = 0; yy < 8; yy++)
            {
                imageIndex = pind + (yy*canvas.width*4);
                for (xx = 0; xx < 8; xx++)
                {
                    //pixRegion[regionIndex] = imdata.data[pind + (yy*canvas.width*4) + xx*4];
                    //pixRegion[regionIndex] = imdata.data[imageIndex + (xx*4)];

                    //var b = 0.3 * imdata.data[imageIndex] + 0.59 * imdata.data[imageIndex+1] + 0.11 * imdata.data[imageIndex+2]
                    var b = (imdata.data[imageIndex] + imdata.data[imageIndex+1] + imdata.data[imageIndex+2]) / 3.0;
                    imageIndex = imageIndex + 4;
                    pixRegion[regionIndex] = b;

                    regionBrightness += pixRegion[regionIndex];
                    regionIndex++;
                }
            }

            var minError = 999999999;
            var minErrorIndex = 0;
            var bRange = 4000;
            // get error against every glyph for match
            for (glyph = 0; glyph < 256; glyph++)
            {
                // remove glyphs with brightness far from region brightness
                if (glyphBrightness[glyph] >= regionBrightness - bRange && glyphBrightness[glyph] <= regionBrightness + bRange)
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
            glyphResult[glyphResultIndex] = minErrorIndex;
            glyphResultIndex++;
        }
    }

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "testupload.php", true);
    xhttp.onload = function() {
      captureInterval = setInterval(captureImage, 0);
    }
    xhttp.send(glyphResult);
}

const rVidConstraints = {
    facingMode: 'environment'
};

const fVidConstraints = {
    facingMode: 'self'
};

const rConstraints = {
  audio: false,
  video: rVidConstraints
};

const fConstraints = {
    audio: false,
    video: fVidConstraints
}

function handleSuccess(stream) {
  window.stream = stream; // make stream available to browser console
  video.srcObject = stream;
  captureInterval = setInterval(captureImage, 33);
}

function handleError(error) {
  console.log('navigator.MediaDevices.getUserMedia error: ', error.message, error.name);
}

getGlyphBrightness();
if (facing == 'r')
{
    navigator.mediaDevices.getUserMedia(rConstraints).then(handleSuccess).catch(handleError);
} 
else
{
    navigator.mediaDevices.getUserMedia(fConstraints).then(handleSuccess).catch(handleError);
}