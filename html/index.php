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
<body style="background-color:black;">

<div id="container">
    <h1><span>PetPix</span>
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
?>
}
</script>
<button id="flip" onclick="flipCamera();">flip camera</button>

<div class="slider">
<input type="range" id="rslider" min="0" max="100" value="33" oninput="handleSlider(0,1,2);">
<input type="range" id="gslider" min="0" max="100" value="33" oninput="handleSlider(1,0,2);">
<input type="range" id="bslider" min="0" max="100" value="33" oninput="handleSlider(2,0,1);">
</div>
<button onclick="resetColors();">reset colors</button>


<script>
    var sliders = new Array(3);
    sliders[0] = document.getElementById("rslider");
    sliders[1] = document.getElementById("gslider");
    sliders[2] = document.getElementById("bslider");

    var rval = 1/3;
    var gval = 1/3;
    var bval = 1/3;

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
</script>

<script src="js/glyphdata.js"></script>
<script src="js/main.js" async></script>

</body>
</html>