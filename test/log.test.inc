<?php

require_once __DIR__ . '/../logging.inc';

class LogTest extends PHPUnit_Framework_TestCase {
	
	private $file;
	
	function __construct () {
		$this->file = tempnam(sys_get_temp_dir(), 'test'); 
	}

	function clear() {
		unlink($this->file);
	}
	
	function blahblah() {
		echo 'The quick brown fox jumped over the lazy dog', PHP_EOL;
		echo 'Lorem ipsum', PHP_EOL;
	}
	
	function testAppend() {
		$this->clear();

		$data = ['a', 'b', 'c', 'd'];
		
		foreach ($data as $line) {
			$log = $this->create();
			$log->safe_write($line);
		}
		
		$this->assertEquals(implode('', $data), file_get_contents($this->file));
	}
	
	function create() {
		return new Logging($this->file);
	}
	
	function testOb() {
		$this->clear();
		$log = $this->create();

		ob_start();
		$this->blahblah();
		$contents = ob_get_contents();
		ob_end_clean();
		
		$this->assertNotEquals(0, strlen($contents));
		
		$log->log_ob_start();
		$this->blahblah();
		$log->log_ob_end();
		
		$this->assertEquals($contents, file_get_contents($this->file));
		
		$this->expectOutputString($contents);
		
		$this->blahblah();
	}
	
}