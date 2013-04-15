<?php

class MissingFieldException extends Exception {
	
	public $field;
	
	function __construct($field, $code = null, $previous = null) {
		$this->field = $field;
		
		parent::__construct("Missing field '$field'", $code, $previous);
	}
}


trait ArrayParser {
	
	function parse_required(array $fields, array $request) {
		foreach ($fields as $field)
			if (isset($request[$field]))
				$this->$field = $request[$field];
			else
				throw new MissingFieldException($field);	
	}
	
	function parse_optional(array $fields, array $request) {
		foreach ($fields as $field)
			if (isset($request[$field]))
				$this->$field = $request[$field];
	}
	
}