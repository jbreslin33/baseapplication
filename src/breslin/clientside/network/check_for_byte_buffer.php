<?php
$id = $_POST["id"];

//*****************DATABASE
/*
//create connection
$conn = pg_connect("host=localhost dbname=abcandyou user=postgres password=mibesfat")
       or die('Could not connect: ' . pg_last_error());

$query = "select password from passwords where id = "
$query .= $id; 
$query .= ";";

$result = pg_query($conn,$query);
$row = pg_fetch_array($result, 0);
$numrows = pg_numrows($result);
	
$password = $row["password"];

//send password  back to browser
$numrows = "g";
echo $numrows;
*/
echo $id;

?>

