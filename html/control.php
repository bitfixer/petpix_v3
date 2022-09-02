<html>
<body style="background-color: #000000; color: #00FF00;">
<script src="js/control.js"></script>

<form action="upload.php" method="post" enctype="multipart/form-data">
    Upload Video:<br/>
    <input name="videoFile" type="file"/><br/>
    <input type="submit" value="Upload Video"/>
</form>
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
<button onclick="playPlaylist()">PLAY</button><div id="status"></div>

</html>