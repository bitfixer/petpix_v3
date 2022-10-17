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

function preCapture() {
    var ctx = canvas.getContext('2d');
    if (facing == "f") 
    {
        ctx.translate(canvas.width,0);
        ctx.scale(-1,1);
    }   
}

function postCapture() {
    var ctx = canvas.getContext('2d');
    if (facing == "f")
    {
        ctx.setTransform(1,0,0,1,0,0);
    }
}

function postSend() {
    clearInterval(captureInterval);
    captureInterval = setInterval(captureImage, cdelay);
}

function handleSuccess(stream) {
  window.stream = stream; // make stream available to browser console
  video.srcObject = stream;
  captureInterval = setInterval(captureImage, 0);
}

function handleError(error) {
  console.log('navigator.MediaDevices.getUserMedia error: ', error.message, error.name);
}

if (facing == 'r')
{
    navigator.mediaDevices.getUserMedia(rConstraints).then(handleSuccess).catch(handleError);
} 
else
{
    navigator.mediaDevices.getUserMedia(fConstraints).then(handleSuccess).catch(handleError);
}
