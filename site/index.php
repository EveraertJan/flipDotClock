
<?php

if(isset($_POST['submit_timer'])){
	$file = 'rules.xml';

	$xml = simplexml_load_file($file);

	$rules = $xml->rules;

	$rule = $rules->addChild('rule', $_POST['naam']);
	$rule->addAttribute('type', 'timr');
	$rule->addAttribute('start', $_POST['startVal']);
	$rule->addAttribute('length', $_POST['length']);
	$xml->asXML($file);
	echo "added a timer";
}

if(isset($_POST['submit_marquee'])){
	$file = 'rules.xml';

	$xml = simplexml_load_file($file);

	$rules = $xml->rules;

	echo $rules;
	$rule = $rules->addChild('rule', $_POST['naam']);
	$rule->addAttribute('type', 'marquee');
	$rule->addAttribute('start', $_POST['startVal']);
	$rule->addAttribute('end', $_POST['endVal']);
	$xml->asXML($file);
	echo "added a marquee";
}
?>
<!DOCTYPE html>
<head>
	<title>new rule</title>
	<link href="stylesheet.css" rel="stylesheet" />
	<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js" ></script>

</head>
<body>

	<div id="timer">
		<h2>timer:</h2>

		<form action="<? echo $_SERVER[PHP_SELF]; ?>" method="post">
			<input type="text" name="naam" placeholder="naam" />
			<input type="text" name="startVal" placeholder="start tijd (eg. 1420)" />
			<input type="text" name="length" placeholder="lengte van de timer" />
			<input type="submit" value="submit" name="submit_timer" />
		</form>
	</div>
	<div id="marquee">
		<h2>marquee: </h2>
		<form action="<? echo $_SERVER[PHP_SELF]; ?>" method="post">
			<input type="text" name="naam" placeholder="displayed string"/>
			<input type="text" name="startVal" placeholder="startTijd (eg. 1240)" />
			<input type="text" name="endVal" placeholder="eindtijd (eg. 1245)" />
			<input type="submit" value="submit" name="submit_marquee" />
		</form>
	</div>
	</html>