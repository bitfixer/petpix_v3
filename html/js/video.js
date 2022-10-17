var skipped = 0;
var currentFrame = 0;

function preCapture() {

}

function postCapture() {

}

function postSend() {
    clearInterval(captureInterval);
    skipped = 0;
    currentFrame++;
    video.play().then(nextFrame);
}

function nextFrame() {
    clearInterval(captureInterval);
    captureInterval = setInterval(checkFrame, 0);
}

function checkFrame() {
    clearInterval(captureInterval);
    var vt = video.currentTime;
    var seekTime = currentFrame / 30.0;

    if (vt < seekTime)
    {
        skipped++;
        captureInterval = setInterval(checkFrame, 0);
        return;
    }

    video.pause();
    console.log(vt, seekTime, vt-seekTime, skipped);
    captureInterval = setInterval(captureImage, 0);
}

let fileInput = document.getElementById("fileselector");
fileInput.addEventListener("input", (event) => {
    let [file] = fileInput.files;
    let url = URL.createObjectURL(file, { type: "video/mp4" });
    video.src = url;
    console.debug({ url, file });
    currentFrame = 0;
    video.currentTime = 0;
    video.play();
    video.playbackRate = 1.5;
    captureInterval = setInterval(checkFrame, 0);
});