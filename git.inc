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
	
	/** Runs system command returning both outputs.
	 * 
	 * @param string $command
	 * @return number|string
	 */
	
	private function system($command) {
		if (!($p=popen("($command)2>&1","r"))) {
			return 126;
		}
	
		while (!feof($p)) {
			$line=fgets($p,1000);
			$out .= $line;
		}
		
		pclose($p);

		return $out;
	}
	
	
	function run($command) {
		$path = escapeshellarg($this->dir);

		$git = "git --work-tree=$path $command"; 
		
		echo "\033[1;30mRUNNING GIT:\033[0m $git";
		
		return `$command 1>&2`;
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