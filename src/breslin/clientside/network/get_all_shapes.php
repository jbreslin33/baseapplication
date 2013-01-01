<?php
//get current client id then update record
$conn = pg_connect("host=localhost dbname=abcandyou user=postgres password=mibesfat")
       or die('Could not connect: ' . pg_last_error());

$query = "select id, position_x, position_z from shapes;";

$result = pg_query($conn,$query);
$numrows = pg_numrows($result);


//send client id back to client browser
echo "<table id=\"get_all_shapes_table\" border='1'>
<tr>
<th>id</th>
<th>client</th>
<th>x</th>
<th>z</th>
<th>rx</th>
<th>rz</th>
<th>m</th>
<th>a</th>
</tr>";
for($i = 0; $i < $numrows; $i++) 
{
$row = pg_fetch_array($result, $i);
echo "<tr>";
echo "<td>" . $row[0] . "</td>";
echo "<td>" . $row[1] . "</td>";
echo "<td>" . $row[2] . "</td>";
echo "<td>" . $row[3] . "</td>";
echo "<td>" . $row[4] . "</td>";
echo "<td>" . $row[5] . "</td>";
echo "<td>" . $row[6] . "</td>";
echo "<td>" . $row[7] . "</td>";
echo "</tr>";
}
echo "</table>";

?>
