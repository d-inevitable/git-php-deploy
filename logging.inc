<?php

class Logging extends SplFileObject {
	
	private $handler;
	
	function __construct($file_name) {

		if (!file_exists($file_name))
			touch($file_name);
		
		parent::__construct($file_name, 'w');
		
		$this->fseek(0, SEEK_END);
	}
	
	private function lock() {
		while (!$this->flock(LOCK_EX))
			if ($retries > 100)
				throw new Exception('Cannot lock log file');
			else
				usleep(100);
	}

	private function unlock() {
		$this->flock(LOCK_UN);
	}
	
	function safe_write($str) {
		$this->lock();
		
		if (is_null($this->fwrite($str)))
			throw new RuntimeException('Failed to write');
		
		$this->unlock();
	}
	
	protected function ob_enabled() {
		return !!$this->handler or in_array($this->handler, ob_list_handlers()); 	
	}
	
	private function get_handler() {
		if (!$this->handler)
			$this->handler = function ($buffer) {
			$this->safe_write($buffer);
		};
		
		return $this->handler;
	}
	
	function log_ob_start() {
		if (!$this->ob_enabled())
			ob_start($this->get_handler());
	}
	
	function log_ob_end() {
		if ($this->ob_enabled())
			ob_end_flush();
		
		$this->handler = null;
	}
	
}