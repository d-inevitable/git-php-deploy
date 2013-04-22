<?php


class Git {
	
	public $dir;
	
	static 	$remote = 'github.com',
			$git = 'git';

	function __construct($work_tree = null) {
		if (is_null($work_tree))
			$this->dir = getcwd();
		else
			$this->dir = $work_tree;
	}
	
	protected function tell($action, $command) {
		echo "\033[0;34m$action:\033[0m $command", PHP_EOL;
	}
	
	function run($command) {
		$worktree = escapeshellarg($this->dir);
		$gitdir = escapeshellarg("$this->dir/.git");
		
		$git = static::$git . " --git-dir=$gitdir --work-tree=$worktree $command";
		
		return `$git`;
	}
	
	function clone_repository($url) {
		if (file_exists($this->dir))
			throw new Exception("Directory '$this->dir' already exists");
		
		$url = escapeshellarg($url);
		$git = static::$git;
		$command = "$git clone $url $this->dir";
		
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

		return trim($this->run("symbolic-ref $target"), PHP_EOL);
	}
	
	function name($origin = 'origin') {
		$fetch = $this->run("remote -v | grep fetch | grep " . escapeshellarg($origin));

		$origin = preg_quote($origin, '!');
		
		if (!preg_match("!$origin\s+(?<url>.*?)\s+\(fetch\)$!", $fetch, $info))
			return null;

		//parse_url doesn't work with non-numeric "port" so we need to do it by reg exp too:
		
		$url = $info['url'];
		$remote = preg_quote(static::$remote, '!');
		
		if (!preg_match("!^(?:\w+://)?(?:\w+@)?{$remote}[:/](?<name>[\w-+_]+/[\w-+_]+)\.git?$!i", $url, $info))
			throw new Exception("Unrecognized URL '$url'");
		
		return $info['name'];
	}
}