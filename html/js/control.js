function addVideo(video) {
    let playlist = document.querySelector('#playlist');
    let li = document.createElement('li');
    li.innerHTML = video;
    playlist.append(li);
}

function playPlaylist() {
    let playlist = document.querySelector('#playlist');
    var items = playlist.getElementsByTagName("li");
    let playlistStr = "";
    for (var i = 0; i < items.length; i++)
    {
        playlistStr += items[i].innerHTML + "\n";
    }

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "playlist.php", true);

    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == 4 && xhttp.status == 200) {
            //alert(xhttp.responseText);
            var statusField = document.getElementById("status");
            statusField.innerHTML = xhttp.responseText;
        }
    }
    xhttp.send(playlistStr);
}