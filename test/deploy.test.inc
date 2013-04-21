<?php

require_once  __DIR__ . '/git_env.inc';

require_once __DIR__ . '/../payload.inc';
require_once __DIR__ . '/../deploy.inc';



class DeployTest extends PHPUnit_Framework_TestCase {

	const 	TEST_REPOSITORY = 'git://github.com/d-inevitable/git-php-deploy.git',
			TEST_NAME = 'd-inevitable/git-php-deploy';
	
	use GitEnv;
	
	function testDeploy() {
		$payload = new Payload(json_decode(file_get_contents(__DIR__ . '/request.json'), true));
		
		
		$git = $this->try_git();
		
		$this->assertEquals($payload->ref, $git->ref());
		$this->assertEquals($payload->repository->full_name(), $git->name());
		
		$this->assertContains($git->dir, deploy($payload, [$git->dir]), 'Working copy wasn\'t deployed as expected');
	}
	
	
}