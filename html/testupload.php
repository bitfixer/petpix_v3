<?php
	file_put_contents('/home/pi/petpix_images/test.img', file_get_contents('php://input'));
	shell_exec("cat /home/pi/petpix_images/test.img | nc -N 127.0.0.1 9600");
?>