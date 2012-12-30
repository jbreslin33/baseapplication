<?php
//get current client id then update record
$conn = pg_connect("host=localhost dbname=abcandyou user=postgres password=mibesfat")
       or die('Could not connect: ' . pg_last_error());

$query = "select client_id from client where id = 1;";

$result = pg_query($conn,$query);
$row = pg_fetch_array($result, 0);

$client_id = $row["client_id"];
/*
//now update the record
$new_client_id = $client_id + 1;
$query = "update client set client_id = ";
$query .= $new_client_id;
$query .= " where id = 1";

$result = pg_query($conn,$query);
*/
//send client id back to client browser
echo $client_id;
?>
