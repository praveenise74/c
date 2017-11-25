<?php
 $conn = new mysqli("localhost","root","","second");
 if($conn->connect_error)
  die("Connection error " . $conn->connect_error);
 if(!isset($_POST["all"]))
  $sql = "select * from details where name='".$_POST["srch"]."' or id='".$_POST["srch"]."' or mob='".$_POST["srch"]."'";
 else
  $sql = "select * from details";

 $result = $conn->query($sql);  
 if ($result->num_rows > 0) {
    echo "<center><table border='2' cellspacing='0'><tr><th>ID</th><th>Name</th><th>Mobile</th><th>Email</th><th>Marks</th></tr>";
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>".$row["id"]."</td><td>".$row["name"]."</td><td>".$row["mob"]."</td><td>".$row["email"]."</td><td>".$row["marks"]."</td></tr>";
    }
    echo "</table></center>";
 } 
 else 
    echo "0 results"; 
 $conn->close();
?>
