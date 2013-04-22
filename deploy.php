<?php

require_once __DIR__ . '/logging.inc';

require_once __DIR__ . '/deploy.inc';
require_once __DIR__ . '/payload.inc';

$log = new Logging('deploy.log');

$log->log_ob_start();

$payload = Payload::receive();

if ($payload) {
	echo 'Payload received at ', date(DateTime::ISO8601), PHP_EOL;
	
	$config = parse_ini_file('config.ini', true);
	
	echo 'Deploying working dirs:', PHP_EOL;
	
	print_r(deploy($payload, array_map(function(array $config) {
		return $config['path'];
	}, $config)));
}
else
	echo 'Invalid payload', PHP_EOL;


echo "Operation complete", PHP_EOL;

$log->log_ob_end();

