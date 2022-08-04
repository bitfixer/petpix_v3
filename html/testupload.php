<?php
	file_put_contents('/mnt/tmp/test.img', file_get_contents('php://input'));
	shell_exec("cat /mnt/tmp/test.img | nc -N 127.0.0.1 9600");
?>