<?php

require_once 'array_parser.inc';

require_once 'contributor.inc';

class Repository {
	
	use ArrayParser;
	
	public 	$created_at,
			$description = "",
			$fork = false,
			$forks = 0,
			$has_downloads = false,
			$has_issues = false,
			$has_wiki = false,
			$language,
			$master_branch,
			$name,
			$open_issues = 0,
			$organization,
			$owner,
			$private,
			$pushed_at,
			$size,
			$stargazers = 0,
			$url,
			$watchers = 0;
	
	private $contributors = [],
			$id;

	function __construct(array $repository) {
		$this->created_at = date_create()->setTimestamp($repository['created_at']);
		$this->pushed_at = date_create()->setTimestamp($repository['pushed_at']);
		
		$this->parse_required([
				'id', 
				'url', 
				'name', 
				'master_branch'
			], $repository);
		
		$this->parse_optional([
				'description', 
				'fork', 
				'forks', 
				'has_downloads',
				'has_issues',
				'has_wiki',
				'language',
				'open_issues',
				'organization',
				'size',
				'stargazers',
				'watchers'
			], $repository);
		
		if (isset($repository['owner']))
			$this->owner = $this->find_or_create_contributor($repository['owner']);

	}

	function get_id() {
		return $this->id;
	}
	
	/**
	 * @return Contributor
	 */
	
	function find_or_create_contributor(array $details) {
		@$contributor = &$this->contributors[$details['name']];

		if (!$contributor)
			$contributor = new Contributor($this, $details);
		
		return $contributor;
	}
	
	function full_name() {
		$owner = $this->organization ? $this->organization : $this->owner->name;
		
		return "$owner/$this->name";
	}
	
	
}