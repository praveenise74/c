<?php 
 $countryId=intval($_GET['country']);
 $stateId=intval($_GET['state']);
 $con = new mysqli('localhost', 'root', '','third'); 
 if ($con->connect_error) {
    die('Could not connect: ' . $con->connect_error);
 }
 $sql="SELECT id,cityname FROM city WHERE countryid='$countryId' AND stateid='$stateId'";
 $result=$con->query($sql);
?>
 <select name="city">
 <option>Select City</option>
 <?php while($row=$result->fetch_assoc()) { ?>
 <option value=<?php echo $row['id']?>><?php echo $row['cityname']?></option>
 <?php } ?>
</select>
