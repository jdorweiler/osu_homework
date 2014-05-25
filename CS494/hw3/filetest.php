<?php

if($_SERVER['REQUEST_METHOD'] == "POST"){
	var_dump($_FILES);
	$errorinfo = $_FILES["myfile"]["error"];
	$filename = $_FILES["myfile"]["name"];
	$tmpfile = $_FILES["myfile"]["tmp_name"];
	$filesize = $_FILES["myfile"]["size"];
	$filetype = $_FILES["myfile"]["type"];

	if($filetype == "image/png" && $filesize < 1048576)
		move_uploaded_file($tmpfile, "mydirectory/".$filename);
	else
		echo "wft".$filename;
}

?>