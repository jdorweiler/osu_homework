<?php
ini_set('display_errors', 'On');
include 'password.php';

if($_SERVER['REQUEST_METHOD'] == "POST"){
    $id = $_POST['id']; 
    $name = $_POST['name'];
    $item = $_POST['item'];
    $num = $_POST['num'];
}
else{
	$stringData = "didnt work";
}
    $myFile = "testFile.txt";
    $fh = fopen($myFile, 'w') or die("can't open file");
    fwrite($fh, $name);
    fclose($fh);

$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "dorweilj-db", $myPWD, "dorweilj-db");
if($mysqli->connect_errno){
        echo "Failed to connect to mysql: (" . $mysqli->errno . ")" . $mysqli->connect_error;
    } 

$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES ($id, '$name', '$item', $num)");
?>
