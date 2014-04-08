<!DOCTYPE html>
<!--
CS494 - Assignment 3 - database storage
Jason Dorweiler
02 - 12 - 2014
This page gets works with a mysqli database.  
The database is prefilled with a few rows. New rows 
can be added with the input boxes.    
-->
<head>
	<script src="jquery-1.10.2.min.js"></script>
	<script src="jquery.validate.js"></script>
	<meta charset="utf-8">
	<style>
		body{background-color: rgb(205,205,205);}
		table, tr, td{border: 1px solid black;}
	</style>
	<title>Databases</title>
</head>
<body>
<br><br>
	<form id="form" action="#" method="POST">
	<input id='id' placeholder="ID Number" name='id' class="required digits">
	<input id='name' placeholder="Name" name='name' class="required">
	<input id='item' placeholder="Item" name='item' class='required'>
	<input id='num' placeholder="Number" name='num' class="required digits"><br>
	<input value="Add to Database" id="submit" type="submit">
</form> 
<div id="numRobots"></div>

<script>
    $(document).ready(function(){
        $("#form").validate();
    });
</script>

<?php
	ini_set('display_errors', 'On');
	include 'password.php';

	// open the database
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "dorweilj-db", $myPWD, "dorweilj-db");
	if($mysqli->connect_errno){
        echo "Failed to connect to mysql: (" . $mysqli->errno . ")" . $mysqli->connect_error;
    } 

    // check to see if we got a post and add values to the databse 
	if($_SERVER['REQUEST_METHOD'] == "POST"){
    	$id = $_POST['id']; 
    	$name = $_POST['name'];
    	$item = $_POST['item'];
    	$num = $_POST['num'];
    	$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES ($id, '$name', '$item', $num)"); 
	}
	else{
    	$stringData = "didnt work";
	}   

    // add three test cases to database if they're not already there
	if(
    	!$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (1, 'robots are awesome', 'blueberry', 4)") ||
    	!$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (2, 'robotrobotrobot', 'paper', 100)") ||
    	!$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (3, 'automation', 'ruler', 2)")){
	}

    //prepared statment to get data from database sort by last 10 elements
	if (!($stmt = $mysqli->prepare("SELECT id, name, item, num FROM hw4Databse ORDER BY id DESC LIMIT 10"))) {
    	echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}

	if (!$stmt->execute()) {
    	echo "Execute failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}

	// variables to hold database values
	$out_id = NULL;
	$out_name = NULL;
	$out_item = NULL;
	$out_num = NULL;

	if (!$stmt->bind_result($out_id, $out_name, $out_item, $out_num)) {
    	echo "Binding output parameters failed: (" . $stmt->errno . ") " . $stmt->error;
	}

	// print out the table
	$numRobots = NULL;
	printf("<table><tr><td>ID</td><td>Name</td><td>Item</td><td>Number</td></tr>");
	while ($stmt->fetch()) {
    	printf("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>", $out_id, $out_name, $out_item, $out_num);
    	$numRobots += substr_count($out_name, "robot") + substr_count($out_name, "Robot") + substr_count($out_name, "ROBOT");
    	$numRobots += substr_count($out_item, "robot") + substr_count($out_item, "Robot") + substr_count($out_item, "ROBOT");
	}
	printf("</table>");
	echo "Number of 'Robots' found in the table is: ".$numRobots;
?>
</body></html>