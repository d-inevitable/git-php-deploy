<?php

require_once __DIR__ . '/../git.inc';


class GitTest extends PHPUnit_Framework_TestCase {
	
	
	function mock_git(PHPUnit_Framework_MockObject_Matcher_Invocation $matcher, 
			PHPUnit_Framework_MockObject_Stub $run) {
		
		$git = $this->getMock('Git', ['run']);
		
		$method = $git->expects($matcher)->method('run');
		
		$method->will($run);
		
		return $git;
	}
	
	function testName() {
		
		$name = 'd-inevitable/git-php-deploy';
		$origin = 'origin';
		
		$callback = $this->returnCallback(function($command) use(&$name, &$origin) {
			$host = Git::$remote;
			return "$origin	git@$host:$name.git (fetch)";
		});
		
		$git = $this->mock_git($this->once(), $callback);

		$this->assertEquals($name, $git->name());
		
		$git = $this->mock_git($this->once(), $callback);
		
		$this->assertNull($git->name('foo'));
		
		$git = $this->mock_git($this->once(), $callback);
		$origin = 'foo';
		
		$this->assertEquals($name, $git->name($origin));

		$git = $this->mock_git($this->once(), $callback);
		$this->assertNull($git->name('origin'));
	}
	
}