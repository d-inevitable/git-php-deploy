<?php

require_once 'array_parser.inc';

require_once 'commit.inc';
require_once 'repoistory.inc';

class Payload extends ArrayObject {
	
	use ArrayParser;
	
	public 	$before,
			$after,
			$ref,
			$commits = [],
			$reqository;
	
	static function receive() {
		try {
			return new static(json_decode($_REQUEST['payload']));
		}
		catch (Exception $e) {
			return null;
		}
	}
	
	function __construct(array $request) {
		$this->parse_required(['ref'], $request);
		
		$this->reqository = $this->create_repsitory($request['repository']);
		
		foreach ($request['commits'] as $commit) {
			$commit = $this->create_commit($commit);
			$this->commits[$commit->get_id($commit)] = $commit;
		}
		
		$this->after = @$this->commits[@$request['after']];
		$this->before = @$this->commits[@$request['before']];
	}
	
	/**
	 * @return Repository
	 */

	protected function create_repository(array $repository) {
		return new Respository($repository);
	}

	/** Creats a new commit object.
	 * 
	 * @return Commit
	 */
	
	protected function create_commit(array $commit) {
		return new Commit($this->reqository, $commit);
	}
	
}