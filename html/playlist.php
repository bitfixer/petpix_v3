<?php
    $payload = file_get_contents('php://input');
    $playlist_file = fopen("control/playlist.txt", "w");
    fwrite($playlist_file, $payload);
    fclose($playlist_file);

    // write control byte
    $control_byte = 1;
    $control_file = fopen("/mnt/tmp/p.ctl", "r");
    if ($control_file)
    {
        $byte = fread($control_file, 1);
        $control_byte = ord($byte);
        $control_byte += 1;
        if ($control_byte > 255)
        {
            $control_byte = 1;
        }
        fclose($control_file);
    }
    $control_file = fopen("/mnt/tmp/p.ctl", "w");
    $bs = pack("C", $control_byte);
    fwrite($control_file, $bs);
    fclose($control_file);

    printf("Playing");
?>