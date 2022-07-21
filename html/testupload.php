<?php

	//shell_exec("echo \"test\" | nc -N 127.0.0.1 9600");

	// test upload endpoint
	file_put_contents('/home/pi/petpix_images/test.img', file_get_contents('php://input'));
	//print("done");
	//$contents = file_get_contents('php://input');
	//file_put_contents("/home/pi/petpix_images/test.img")
	shell_exec("cat /home/pi/petpix_images/test.img | nc -N 127.0.0.1 9600");

	/*
	$contents = "message12354";

	$server_ip = '127.0.0.1';
	$server_port = 8081;

	$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
	socket_sendto($socket, $contents, strlen($contents), 0, $server_ip, $server_port);

	print("done");
	*/

?>