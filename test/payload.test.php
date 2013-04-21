<?php

require_once __DIR__ . '/../payload.inc';
require_once __DIR__ . '/../repository.inc';

class PayloadTest extends PHPUnit_Framework_TestCase {
	
	const REQUEST_FILE = 'request.json';
	
	
	public 	$request;
	
	function setUp() {
		$this->request = json_decode(file_get_contents(__DIR__ . DIRECTORY_SEPARATOR . self::REQUEST_FILE), true);
	}
	
	function testConstruction() {
		return new Payload($this->request);
	}
	
	/**
	 * 
	 * @depends testConstruction
	 * 
	 */
	
	function testIntegrity(Payload $payload) {
		$this->assertEquals($this->request['ref'], $payload->ref);

		$this->assertInternalType('array', $payload->commits);
		
		$this->assertInstanceOf('Repository', $payload->repository);
		
		foreach ($payload->commits as $commit)
			$this->assertInstanceOf('Commit', $commit);
		
		if ($payload->after) {
			$this->assertInstanceOf('Commit', $payload->after);
			
			$id = $payload->after->get_id();
			$this->assertArrayHasKey($id, $payload->commits);
			$this->assertSame($payload->commits[$id], $payload->after);
		}
		
		if (is_string($payload->before)){
			$this->assertInstanceOf('Commit', $payload->before);
			
			$id = $payload->before->get_id();
			$this->assertArrayHasKey($id, $payload->commits);
			$this->assertSame($payload->commits[$id], $payload->before);
		}

	}
	
	
}