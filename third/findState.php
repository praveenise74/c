<?php 
 $country=intval($_GET['country']);
 $con = new mysqli('localhost', 'root', '','third'); 
 if ($con->connect_error) {
     die('Could not connect: ' . $con->connect_error);
 }
 $sql="SELECT id,statename FROM state WHERE countryid='$country'";
 $result=$con->query($sql);
?>
 <select name="state" onchange="getCity(<?php echo $country?>,this.value)">
 <option>Select State</option>
 <?php while ($row=$result->fetch_assoc()) { ?>
 <option value=<?php echo $row['id']?>><?php echo $row['statename']?></option>
 <?php } ?>
 </select>
