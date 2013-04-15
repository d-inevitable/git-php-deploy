<?php


class Git {
	
	public $dir;
	
	static $remote = 'github.com';

	function __construct($work_tree = null) {
		if (is_null($work_dir))
			$this->dir = getcwd();
		else
			$this->dir = $work_dir;
	}
	
	function run($command) {
		$path = escapeshellarg($this->dir);

		return `git --work-tree=$this->dir $command`;
	}
	
	function pull() {
		return $this->run('pull');
	}
	
	function status() {
		return $this->run('status');
	}
	
	function submodule($action) {
		return $this->run("submodule $action");
	}
	
	
	function ref($target = 'HEAD') {
		$target = escapeshellarg($target);

		return $this->run("symbolic-ref $target");
	}
	
	function name($origin = 'origin') {
		$fetch = $this->run("remote -v | grep fetch | grep " . escapeshellarg($origin));

		$origin = preg_quote($origin, '!');
		
		if (preg_match("!$origin\s+(.*?)\s+\(fetch\)$!", $subject, $match))
			$url = $match[1];
		else
			return null;
		
		$info = parse_url($url);
		
		if ($info['host'] !== $this->remote)
			return null;
		
		if (preg_match('!^(\w+/\w+)\.git$!i', $info['path'], $match))
			return $match[1];
		else
			return null;
	}
}