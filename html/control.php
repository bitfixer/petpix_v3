<html>
<body style="background-color: #000000; color: #00FF00;">
<script src="js/control.js"></script>
<form id="uploadVideoForm" action="upload.php" method="post" enctype="multipart/form-data">
    Upload Video:<br/>
    <input name="videoFile" type="file"/><br/>
</form>
<input type="radio" id="40col" name="columns" value="40" checked="checked">
<label for="40col">40 Columns</label><br>
<input type="radio" id="80col" name="columns" value="80">
<label for="80col">80 Columns</label><br>
<button onclick="uploadVideo()">Upload Video</button>
<br>
<div id="uploadStatus"></div>
<div id="uploadProgress"></div>
<br>
Available PETpix videos:<br>
<table>
<?php
// list available videos
$dir = 'uploads';
$files = scandir($dir, 0);
sort($files);
for ($i = 0; $i < count($files); $i++)
{
    if (strpos($files[$i], ".p40") || strpos($files[$i], ".p80"))
    {
        printf("<tr><td>%s</td><td><button onclick=\"addVideo('%s')\">add</button></td>\n", $files[$i], $files[$i]);
    }
}
?>
</table>

PETpix playlist:<br>
<ul id="playlist">
</ul>
<button onclick="clearPlaylist()">Clear</button>
<button onclick="playPlaylist()">PLAY</button>
<button onclick="stopPlaylist()">STOP</button>
<div id="status"></div>

</html>