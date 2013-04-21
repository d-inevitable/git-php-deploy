<?php

require_once __DIR__ . '/git_env.inc';


class GitTest extends PHPUnit_Framework_TestCase {
	
	const 	TEST_REPOSITORY = 'git://github.com/d-inevitable/git-php-deploy.git',
			TEST_NAME = 'd-inevitable/git-php-deploy';
	
	use GitEnv;
	
	function mock_git(PHPUnit_Framework_MockObject_Matcher_Invocation $matcher, 
			PHPUnit_Framework_MockObject_Stub $run) {
		
		$git = $this->getMock('Git', ['run']);
		
		$method = $git->expects($matcher)->method('run');
		
		$method->will($run);
		
		return $git;
	}
	
	function testNameMocked() {
		
		$name = static::TEST_NAME;
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
	
	function testClone() {
		$git = $this->try_git();
		
		$this->assertFileExists("$git->dir/.git");
		$this->assertFileExists("$git->dir/README.md");
		
		return $git;
	}
	
	/**
	 * @depends testClone
	 */
	
	function testNameReal(Git $git) {
		$this->assertEquals(static::TEST_NAME, $git->name());
		
		return $git;
	}

	/**
	 * @depends testClone
	 */
	
	function testRef(Git $git) {
		$this->assertEquals('refs/heads/master', $git->ref());
	}
	
}