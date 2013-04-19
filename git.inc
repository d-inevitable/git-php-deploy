<?php


class Git {
	
	public $dir;
	
	static $remote = 'github.com';

	function __construct($work_tree = null) {
		if (is_null($work_tree))
			$this->dir = getcwd();
		else
			$this->dir = $work_tree;
	}
	
	
	function run($command) {
		$path = escapeshellarg($this->dir);

		$git = "git --work-tree=$path $command"; 
		
		echo "\033[0;34mRUNNING GIT:\033[0m $git", PHP_EOL;
		
		return `$command`;
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
		
		if (!preg_match("!$origin\s+(?<url>.*?)\s+\(fetch\)$!", $fetch, $info))
			return null;

		//parse_url doesn't work with non-numeric "port" so we need to do it by reg exp too:
		
		$url = $info['url'];
		$remote = preg_quote(static::$remote, '!');
		
		if (!preg_match("!^(?:\w+://)?(?:\w+@)?$remote:(?<name>[\w-+_]+/[\w-+_]+)\.git?$!i", $url, $info))
			throw new Exception("Unrecognized URL '$url'");
		
		return $info['name'];
	}
}