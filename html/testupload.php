<?php
	// test upload endpoint
	file_put_contents('test.img', file_get_contents('php://input'));
	print("done");
?>