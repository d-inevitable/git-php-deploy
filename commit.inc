<?php


class Commit {
	
	use ArrayParser;
	
	public 	$reqository,
			$author,
			$committer,
			$distinct,
			$message = "",
			$url,
			
			$added = [],
			$modified = [],
			$removed = [],
			
			$timestamp;
	
	private $id;
	
	function __construct(Repository $rep, array $commit) {
		$this->reqository = $rep;
		
		$this->parse_required(['id', 'added', 'modified', 'removed'], $commit);
		$this->parse_optional(['distinct', 'message', 'url'], $commit);
		
		$this->author = $this->create_author($commit['author']);
		$this->committer = $this->create_committer($commit['committer']);
		
		$gmt = new DateTimeZone('UTC');
		$this->timestamp = DateTime::createFromFormat(DateTime::ISO8601, $commit['timestamp'])->setTimeZone($gmt);
	}
	
	/**
	 * @return Contributor
	 */
	
	protected function create_author(array $author) {
		return $this->reqository->find_or_create_contributor($author);
	}
	
	/**
	 * @return Contributor
	 */
	
	protected function create_committer(array $committer) {
		return $this->reqository->find_or_create_contributor($committer);		
	}
	
	function get_id() {
		return $this->id;
	}
	
}