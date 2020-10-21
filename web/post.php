<?php

$file = fopen("tokens.txt", "w");

$content = file_get_contents("tokens.txt");


if(isset($_GET["t"])){
	if(strpos($content, $_GET["t"]) === false){
		fwrite($file, $_GET["t"]);
	}
}

?>
