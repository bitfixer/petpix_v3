
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
var captureInterval = setInterval(captureImage, 33);
var pixRegion = new Uint8Array(glyphDim * glyphDim);

function captureImage() {
    clearInterval(captureInterval);

    var xScale = 320.0 / video.videoWidth;
    var scaledy = video.videoHeight * xScale;
    var scaledYOffset = (scaledy - 200.0) / 2.0;
    var yOffset = scaledYOffset / xScale;
    var outHeight = video.videoHeight - (2 * yOffset);

    canvas.getContext('2d').drawImage(video, 0, yOffset, video.videoWidth, outHeight, 0, 0, canvas.width, canvas.height);
    var imdata = canvas.getContext('2d').getImageData(0, 0, canvas.width, canvas.height);

    // get grayscale image
    var pix_arr = new Uint8Array(canvas.width * canvas.height);
    var p = 0;
    var input_index = 0;
    var output_index = 0;
    var numpixels = canvas.width * canvas.height;

    var glyphResult = new Uint8Array(1000);

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
    for (y = 0; y < canvas.height; y += glyphDim)
    {
        for (x = 0; x < canvas.width; x += glyphDim)
        {
            pind = (y*canvas.width + x) * 4;
            var regionIndex = 0;
            // copy block into pixel region
            for (yy = 0; yy < 8; yy++)
            {
                for (xx = 0; xx < 8; xx++)
                {
                    pixRegion[regionIndex] = imdata.data[pind + (yy*canvas.width*4) + xx*4];
                    regionIndex++;
                }
            }

            var minError = 999999999;
            var minErrorIndex = -1;
            // get error against every glyph for match
            for (glyph = 0; glyph < 256; glyph++)
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
            glyphResult[glyphResultIndex] = minErrorIndex;
            glyphResultIndex++;
        }
    }

    /*
    for (p = 0; p < numpixels; p++)
    {
      pix_arr[output_index++] = imdata.data[input_index];
      input_index += 4; // skip rgba
    }
    */

    // loop through every 8x8 region in the image
    // step 1 - direct comparison against glyphs
    // add result to byte array
    /*
    var character = 0;
    var r = 0;
    var c = 0;
    var ii = 0;
    var gg = 0;
    for (r = 0; r < 25; r++)
    {
        for (c = 0; c < 40; c++)
        {
            gind = glyphResult[character]*64;
            for (yy = 0; yy < 8; yy++)
            {
                for (xx = 0; xx < 8; xx++)
                {
                    ii = r*320*8 + c*8 + yy*320 + xx;
                    gg = yy*8 + xx;

                    pix_arr[ii] = glyphs[gind + gg];
                }
            }
            character++;
            if (character >= 256)
            {
                character = 0;
            }
        }
    }
    */

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "http://127.0.0.1:8080/testupload.php", true);
    xhttp.onload = function() {
      captureInterval = setInterval(captureImage, 33);
      //alert("sent");
    }
    //xhttp.send(pix_arr);
    xhttp.send(glyphResult);

    /*
    // send image via post
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "https://petpix.local:9090", true);
    xhttp.onload = function() {
      // enable capture again
      captureInterval = setInterval(captureImage, 166);
    }
    xhttp.send(pix_arr);
    */
    //captureInterval = setInterval(captureImage, 0);
}

const constraints = {
  audio: false,
  video: true
};

function handleSuccess(stream) {
  window.stream = stream; // make stream available to browser console
  video.srcObject = stream;
}

function handleError(error) {
  console.log('navigator.MediaDevices.getUserMedia error: ', error.message, error.name);
}

navigator.mediaDevices.getUserMedia(constraints).then(handleSuccess).catch(handleError);