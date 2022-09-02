<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["videoFile"]["name"]);
$tmp_name = $_FILES["videoFile"]["tmp_name"];
if (move_uploaded_file($tmp_name, $target_file)) {
    printf("file %s successfully uploaded.\n", $target_file);
    $cmd = sprintf("bin/convert_one_video -v %s", $target_file);
    shell_exec($cmd);
} else {
    printf("error uploading %s\n", $target_file);
}

?>