<?php

$file = fopen("tokens.txt", "w");
if(isset($_GET["t"])){
	fwrite($file, $_GET["t"]);
}

?>
