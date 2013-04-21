<?php

require_once 'array_parser.inc';

require_once 'commit.inc';
require_once 'repository.inc';

class Payload {
	
	use ArrayParser;
	
	public 	$before,
			$after,
			$ref,
			$commits = [],
			$repository;
	
	static function receive() {
		try {
			if (isset($_REQUEST['payload']))
				return new static(json_decode($_REQUEST['payload'], true));
			else
				return null;
		}
		catch (Exception $e) {
			return null;
		}
	}
	
	function __construct(array $request) {
		$this->parse_required(['ref'], $request);
		
		$this->repository = $this->create_repository($request['repository']);
		
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
		return new Repository($repository);
	}

	/** Creats a new commit object.
	 * 
	 * @return Commit
	 */
	
	protected function create_commit(array $commit) {
		return new Commit($this->repository, $commit);
	}
	
	function find_applicable_work_trees(array $paths) {
		require_once __DIR__ . '/git.inc';
		
		$gits = array_map(function($path) { 
			return new Git($path);	
		}, $paths);
		
		return array_filter($gits, function (Git $working) {
			return $this->ref === $working->ref() and $this->repository->full_name() === $working->name();
		});
	}
	
}