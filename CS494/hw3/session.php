<?php
session_start();
// We got a Post, save the data and redirect to domath.php
if($_SERVER['REQUEST_METHOD'] == "POST"){
	$_SESSION['name'] = $_POST['username'];
	$_SESSION['num1'] = $_POST['num1'];
	$_SESSION['num2'] = $_POST['num2'];
	header('Location: domath.php');
	exit();
}

// there is a session but no post, redired to domath.php
// without changing any session data
if($_SERVER['REQUEST_METHOD'] != "POST" && isset($_SESSION['name'])){
	header('Location: domath.php');
	exit();
}

//no saved session so redired to input.php
if(!isset($_SESSION['name'])){
	header('Location: input.php');
	exit();
}
?>
