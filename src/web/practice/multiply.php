<!DOCTYPE html>
<meta http-equiv="Content-type" content="text/html;charset=UTF-8">
<html>

<head>
	<title>Multiply</title>
<link rel="stylesheet" type="text/css" href="<?php getenv("DOCUMENT_ROOT")?>/css/green_block.css" />
</head>

<body>
<?php
session_start();
//db connection
include(getenv("DOCUMENT_ROOT") . "/src/database/db_connect.php");
$conn = dbConnect();

include(getenv("DOCUMENT_ROOT") . "/web/navigation/top_links_for_practice.php");
echo "<br>";
?>
	<p><b> MULTIPLY PRACTICE LINKS: </p></b>
	
	<a href="multiply2.php">Multiply by 2 Practice</a>
	<a href="multiply3.php">Multiply by 3 Practice</a>

</body>

</html>

