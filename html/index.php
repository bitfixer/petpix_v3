<!DOCTYPE html>
<html>
<head>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, user-scalable=yes, initial-scale=1, maximum-scale=1">
    <meta name="mobile-web-app-capable" content="yes">
    <meta id="theme-color" name="theme-color" content="#ffffff">
    <base target="_blank">

    <title>PETPix</title>
    <link href="//fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="../../../css/main.css">
</head>
<body style="background-color:black; color:green">

<div id="container">
    <h1><span>PETpix</span>
    </h1>
    <canvas></canvas>
    <video playsinline autoplay></video>
</div>

<div id="testdiv"></div>
<script>
<?php
    $facing = 'f';
    if (isset($_GET["f"])) {
        $facing = $_GET["f"];
    }

    $flip = ($facing == "f") ? "r" : "f";

    printf("var facing=\"%s\";\n", $facing);
    printf("function flipCamera() {\n");
    printf("document.location.href = \"https://%s?f=%s\";\n", $_SERVER["HTTP_HOST"], $flip);
    printf("}\n");
?>
</script>
<button id="flip" onclick="flipCamera();">flip camera</button><br>
R<input type="range" id="rslider" min="0" max="100" value="33" oninput="handleSlider(0,1,2);"><br>
G<input type="range" id="gslider" min="0" max="100" value="33" oninput="handleSlider(1,0,2);"><br>
B<input type="range" id="bslider" min="0" max="100" value="33" oninput="handleSlider(2,0,1);"><br>
<button onclick="resetColors();">reset colors</button><br><br>

Capture Delay (MS) <input type="range" id="captureDelay" min="0" max="33" value="15" oninput="handleCaptureDelay();"><br>
<div id="captureDelayVal">15</div><br><br>

<input type="range" id="brightnessRangeSlider" min="1000" max="6000" value="4000" oninput="handleBrightnessRangeChange();"><br>
<div id="brightnessRangeVal">4000</div>
<button onclick="resetBrightnessRange();">reset brightness range</button>


<script>
    var sliders = new Array(3);
    sliders[0] = document.getElementById("rslider");
    sliders[1] = document.getElementById("gslider");
    sliders[2] = document.getElementById("bslider");

    var captureDelaySlider = document.getElementById("captureDelay");
    var captureDelayVal = document.getElementById("captureDelayVal");

    var brightnessRangeSlider = document.getElementById("brightnessRangeSlider");
    var brightnessRangeVal = document.getElementById("brightnessRangeVal");

    var rval = 1/3;
    var gval = 1/3;
    var bval = 1/3;
    var cdelay = 15;
    var brightnessRange = 4000;

    function setRGBVal()
    {
        rval = sliders[0].value / 100;
        gval = sliders[1].value / 100;
        bval = sliders[2].value / 100;
    }

    function handleSlider(c,a,b)
    {
        var thisValue = sliders[c].value;

        var val1 = sliders[a].value;
        var val2 = sliders[b].value;

        var newV1 = 0;
        var newV2 = 0;
        var remainder = 100 - thisValue;

        if (val2 == 0)
        {
            newV1 = remainder;
        }
        else
        {
            var ratio = val1/val2;
            var newV2 = remainder / (ratio+1);
            var newV1 = remainder - newV2;
        }

        sliders[a].value = newV1;
        sliders[b].value = newV2;
        setRGBVal();
    }

    function resetColors()
    {
        sliders[0].value = 100/3;
        sliders[1].value = 100/3;
        sliders[2].value = 100/3;

        setRGBVal();
    }

    function handleCaptureDelay()
    {
        cdelay = captureDelay.value;
        captureDelayVal.innerHTML = cdelay;
    }

    function resetBrightnessRange()
    {
        brightnessRange = 4000;
        brightnessRangeVal.innerHTML = brightnessRange;
        brightnessRangeSlider.value = brightnessRange;
    }

    function handleBrightnessRangeChange()
    {
        brightnessRange = Number(brightnessRangeSlider.value);
        brightnessRangeVal.innerHTML = brightnessRangeSlider.value;
    }
</script>

<script src="js/glyphdata.js"></script>
<script src="js/main.js" async></script>

</body>
</html>