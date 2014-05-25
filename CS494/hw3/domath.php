<?php
	session_start();

	//no saved session so redired to input.php
	if(!isset($_SESSION['name'])){
		header('Location: input.php');
		exit();
	}

	$result = NULL;
	if(isset($_GET['op'])){
		$op = $_GET['op'];
		if($op == 'add')
			$result = $_SESSION["num1"] + $_SESSION["num2"];
		if($op == 'sub')
			$result = $_SESSION["num1"] - $_SESSION["num2"];
		if($op == 'mul')
			$result = $_SESSION["num1"] * $_SESSION["num2"];
		if($op == 'div')
			$result = $_SESSION["num1"] / $_SESSION["num2"];
	}

?>
<!DOCTYPE html>
<!--
CS494 - Assignment 3 - database storage
Jason Dorweiler
02 - 12 - 2014
Page that does math with the session variables it gets
from input.php   
-->
<head>
	<meta charset="utf-8">
	<title>Do Math!</title>
</head>
<body>
	Welccome <?php echo $_SESSION["name"] ?>, lets do some math with 
	your numbers [<?php echo $_SESSION["num1"] ?>] and [<?php echo $_SESSION["num2"] ?>]!

	<form action='domath.php' method='get'>
	  <button name='op' value='add'>Add</button>
	  <button name='op' value='sub'>Subtract</button>
	  <button name='op' value='mul'>Multiply</button>
	  <button name='op' value='div'>Divide</button>
	</form>

	<?php if($result)
			echo "<h1> Your result is ".$result."</h1>";
	?>
</body>
</html>