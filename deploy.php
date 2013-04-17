<?php

require_once 'logging.inc';

require_once 'payload.inc';
require_once 'git.inc';


$log = new Logging('deploy.log');

$log->log_ob_start();

$payload = Payload::receive();


if ($payload) {
	echo 'Payload received at ', date(DateTime::ISO8601), PHP_EOL;
	
	array_walk(parse_ini_file('config.ini', true), function (array $target, $name) use($payload) {
		if (isset($target['payload']))
			throw new InvalidArgumentException('Bad configuration argument "payload" encounterred');
		
		extract($target);
		
		$git = new Git($path);
		
		if ($payload->reqository->name !== $git->name() or $payload->ref !== $git->ref()) {
			echo "Payload doesn't apply to $name", PHP_EOL;
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

