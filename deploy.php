<?php

require_once 'logging.inc';

require_once 'payload.inc';
require_once 'git.inc';


$log = new Logging('deploy.log');

$log->log_ob_start();

$payload = Payload::receive();

$payload or exit;


array_walk(parse_ini_file('config.ini', true), function (array $target) use($payload) {
	
	
	
	if (isset($target['payload']))
		throw new InvalidArgumentException('Bad configuration argument "payload" encounterred');
		
	extract($target);
	
	$git = new Git($path);
	
	if ($payload->reqository->name !== $git->name() or $payload->ref !== $git->ref())
		return;

	$git->pull();
});

$log->log_ob_end();

