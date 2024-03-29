<?php
    if (isset($_GET["p"]) && $_GET["p"] == "1")
    {
        // read current conversion progress
        $progress = "0";
        $progressFile = "/mnt/tmp/prog";
        if (file_exists($progressFile))
        {
            $progress = file_get_contents($progressFile);
        }
        printf("%s", $progress);
    }
    else
    {
        $target_dir = "uploads/";
        $target_file = $target_dir . basename($_FILES["videoFile"]["name"]);
        $tmp_name = $_FILES["videoFile"]["tmp_name"];

        if (move_uploaded_file($tmp_name, $target_file)) {
            printf("file %s successfully uploaded.\n", $target_file);

            // get columns
            $columns = "40";
            if (isset($_GET['c']) && $_GET['c'] != "")
            {
                $columns = $_GET['c'];
            }

            $cmd = sprintf("bin/convert_one_video -v %s -c %s", $target_file, $columns);

            shell_exec($cmd);
            unlink($target_file);
            unlink("/mnt/tmp/prog");
        } else {
            printf("error uploading %s\n", $target_file);
        }
    }

?>