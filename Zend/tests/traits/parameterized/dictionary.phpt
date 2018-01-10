--TEST--
Parameterized Traits - dictionary
--FILE--
<?php

trait Dictionary<Key, Value> {

	private $size = 0;
	private $data = [];
	private $hashing_fn;
	private $equality_fn;

	function __construct(callable $hashing_fn, callable $equality_fn) {
		$this->hashing_fn = $hashing_fn;
		$this->equality_fn = $equality_fn;
	}
	
	private function location($key) {
		$hashcode = ($this->hashing_fn)($key);
		foreach ($this->data[$hashcode] as $offset => list($k, $v)) {
			if (($this->equality_fn)($key, $k)) {
				return [$hashcode, $offset];
			}
		}
		return [$hashcode, null];
	}

	function put(Key $key, Value $value): void {
		$location = $this->location($key);
		$this->data[$location[0]][$location[1]] = [$key, $value];
		$this->size += 1;
	}

	function get(Key $key): ?Value {
		$location = $this->location($key);
		if ($location[1] != null) {
			return $this->data[$location[0]][$location[1]][1];
		}
		return null;
	}

	function remove(Key $key): ?array {
		$location = $this->location($key);
		if ($location[1] != null) {
			$this->size--;
			// todo: read source to determine edge-cases
			$pair = \array_splice($this->data[$location[0]], $location[1], 1);
			return $pair;
		}
		return null;
	}

	function getIterator(): \Iterator {
		foreach ($this->data as $hashcode => $bucket) {
			foreach ($bucket as $offset => $pair) {
				yield [$hashcode, $offset] => $pair;
			}
		}
	}

	function count(): Int {
		return $this->size;
	}

}

class DictionaryIS implements \IteratorAggregate, \Countable {
	use Dictionary<Int, String>;
}

$dict = new DictionaryIS(
	function (Int $int) { return $int; },
	function (Int $a, Int $b) { return $a === $b; }
);

$dict->put(0, "zero");
$dict->put(1, "one");

assert(\count($dict) === 2);
assert($dict->get(1) === "one");
assert($dict->get(0) === "zero");

?>
--EXPECT--
