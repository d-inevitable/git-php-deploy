<?php

require_once 'logging.inc';

require_once 'payload.inc';
require_once 'git.inc';


$log = new Logging('deploy.log');

$log->log_ob_start();

$payload = Payload::receive();


if ($payload) {
	echo 'Payload received at ', date(DateTime::ISO8601), PHP_EOL;
	
	$config = parse_ini_file('config.ini', true);
	
	array_walk($config, function (array $target, $name) use($payload) {
		if (isset($target['payload']))
			throw new InvalidArgumentException('Bad configuration argument "payload" encounterred');
		
		extract($target);
		
		$git = new Git($path);

		$target_name = $git->name();
		$target_ref = $git->ref();
		
		if ($payload->reqository->name !== $target_name or $payload->ref !== $target_ref) {
			echo "Payload doesn't apply to $name", PHP_EOL;
			
			if ($payload->ref !== $target_ref)
				echo "$name has ref $target_ref, but incoming is $payload->ref", PHP_EOL;
			if ($payload->reqository->name !== $target_name)
				echo "$name has name $target_name, but incoming is {$payload->reqository->name}", PHP_EOL;

			return;
		}
			
			
		echo "Pulling $name as $path", PHP_EOL;
		
		$git->pull();
		
		echo "Done pulling $name at $path", PHP_EOL;
	});
}
else
	echo 'Invalid payload', PHP_EOL;


echo "Operation complete", PHP_EOL;

$log->log_ob_end();

