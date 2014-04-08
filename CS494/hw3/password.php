<?php
$myPWD = '8LTU3uXdsu2dFxlD'
?>


<?php
ini_set('display_errors', 'On');
include 'password.php';

$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "dorweilj-db", $myPWD, "dorweilj-db");
if($mysqli->connect_errno){
		echo "Failed to connect to mysql: (" . $mysqli->errno . ")" . $mysqli->connect_error;
	} 

if (!$mysqli->query("DROP TABLE IF EXISTS hw4Databse") ||
    !$mysqli->query("CREATE TABLE hw4Databse(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, name CHAR(55), item CHAR(55), num INT)")) {
    echo "Table creation failed: (" . $mysqli->errno . ") " . $mysqli->error;
}
    // add three test cases to database
if(
    !$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (1, 'robots are awesome', 'blueberry', 4)") ||
    !$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (2, 'robotrobotrobot', 'paper', 100)") ||
    !$mysqli->query("INSERT INTO hw4Databse(id, name, item, num) VALUES (3, 'automation', 'ruler', 2)")){
    echo "adding to databse failed";
}

    //prepared statment to get data from database
if (!($stmt = $mysqli->prepare("SELECT id, name, item, num FROM hw4Databse"))) {
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


printf("<table><tr><td>ID</td><td>Name</td><td>Item</td><td>Number<tr></tr>");
while ($stmt->fetch()) {
    printf("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s<tr></tr>", $out_id, $out_name, $out_item, $out_num);
}
printf("</table>");
?>