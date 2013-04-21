<?php

function deploy(Payload $payload, array $paths) {
	$deployed = [];
	
	foreach ($payload->find_applicable_work_trees($paths) as $git) {
		$git->pull();
		$deployed[] = $git->dir;
	}

	return $deployed;
}