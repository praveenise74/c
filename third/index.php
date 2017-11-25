<?php 
 $con = new mysqli('localhost', 'root', '','third'); 
 if ($con->connect_error) {
    die('Could not connect: '.$con->connect_error);
 }
 $sql="SELECT * FROM country";
 $result=$con->query($sql); 
?>

<html>
 <head>
  <title>Country State City Dropdown Using Ajax</title>
  <script>
   function getState(countryId) {				
	var strURL="findState.php?country="+countryId;
	var req = new XMLHttpRequest();	
	if (req) {
		req.onreadystatechange = function() {
			if (req.readyState == 4)
				if(req.status == 200) {						
					document.getElementById('statediv').innerHTML=req.responseText;
					//document.getElementById('citydiv').innerHTML='<select name="city">'+'<option>Select City</option>'+'</select>';	
				} else
					alert("Problem while using XMLHTTP:\n" + req.statusText);
			}
			req.open("GET", strURL, true);
			req.send(null);		
		}
	}
    function getCity(countryId,stateId) {		
	var strURL="findCity.php?country="+countryId+"&state="+stateId;
	var req = new XMLHttpRequest();
	if (req) {
		req.onreadystatechange = function() {
			if (req.readyState == 4)
				if(req.status == 200)
					document.getElementById('citydiv').innerHTML=req.responseText;						
				else
					alert("Problem while using XMLHTTP:\n" + req.statusText);							
			}
			req.open("GET", strURL, true);
			req.send(null);
		}
				
	}
</script>
</head>

<body>
 <form method="post" action="">
 <center>
 <table width="45%"  cellspacing="0" cellpadding="0">
  <tr>
    <td>Country</td>
    <td>:</td>
    <td>
	<select name="country" onChange="getState(this.value)">
	<option value="">Select Country</option>
	<?php while ($row=$result->fetch_assoc()) { ?>
	<option value=<?php echo $row['id']?>><?php echo $row['country']?></option>
	<?php } ?>
	</select>
   </td>
  </tr>
  <tr>
    <td>State</td>
    <td>:</td>
    <td ><div id="statediv"><select name="state" >
	<option>Select State</option>
        </select></div></td>
  </tr>
  <tr>
    <td>City</td>
    <td>:</td>
    <td><div id="citydiv"><select name="city">
	<option>Select City</option>
        </select></div></td>
  </tr>
  
</table>
</center>
</form>
</body>
</html>
