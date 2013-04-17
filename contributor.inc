<?php


class Contributor {
	
	use ArrayParser;
	
	public 	$repository,
			$email,
			$name,
			$username;
	
	function __construct(Repository $rep, array $params) {
		$this->repository = $rep;
		$this->parse_required(['name'], $params);
		$this->parse_optional(['email', 'username'], $params);
	}
}