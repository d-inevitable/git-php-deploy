<?php

require_once __DIR__ . '/../git.inc';

function recursiveDelete($str){
	if(is_file($str))
		return @unlink($str);

	elseif(is_dir($str)){
		foreach(glob(rtrim($str,'/').'/*') as $index=>$path)
			recursiveDelete($path);

		return @rmdir($str);
	}
}


trait GitEnv {
	
	private $trash = [];
	
	function tearDown() {
		foreach($this->trash as $garbage)
			recursiveDelete($garbage->dir);
	}
	
	/**
	 * @throws Exception
	 * @return Git
	 */
	
	
	function try_git() {

		do {
			$file = tempnam(sys_get_temp_dir(), 'git');
			unlink($file);
			try {
				$git = new Git($file);
				$git->clone_repository(static::TEST_REPOSITORY);
			} catch (Exception $e) {
				$git = $e;
			}
		} while ($git instanceof Exception and $e->getMessage() === "Directory '$file' already exists");
	
		if ($git instanceof Exception)
			throw $git;
		
		return $trash[] = $git;
	}
	
}