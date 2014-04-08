<?php session_start(); ?>
<!DOCTYPE html>
<!--
CS494 - Assignment 3 - sessions
Jason Dorweiler
02 - 12 - 2014
This page get a user name and two number.  It
does a post to session.php where the three variables
are saved as session variables.  Then redirected to
domath.php.    
-->
<head>
	<meta charset="utf-8">
	<script src="jquery-1.10.2.min.js"></script>
	<script src="jquery.validate.js"></script>
	<title>Sessions</title>
</head>
 
<body>
<script>
    $(document).ready(function(){
        $("#form").validate();
    });
</script>
<form id="form" method="POST" action="session.php">
	UserName:	<input id='username' name='username' class="required"><br>
	Number 1:  <input id='num1' name='num1' class="required digits"><br>
	Number 2:  <input id='num2' name='num2' class="required digits"><br>
	<input value="Go do math!" id="submit" type="submit">
</form>

</body></html>