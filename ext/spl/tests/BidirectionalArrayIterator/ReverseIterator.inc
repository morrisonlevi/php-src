<?php

final class ReverseIterator implements OuterIterator, BidirectionalIterator {
	private $inner;

	function __construct(BidirectionalIterator $iter) {
		$this->inner = $iter;
	}

	function getInnerIterator(): BidirectionalIterator {
		return $this->inner;
	}

	function rewind(): void {
		$this->inner->end();
	}

	function end(): void {
		$this->inner->rewind();
	}

	function valid(): bool {
		return $this->inner->valid();
	}

	function next(): void {
		$this->inner->prev();
	}

	function prev(): void {
		$this->inner->next();
	}

	function key() {
		return $this->inner->key();
	}

	function current() {
		return $this->inner->current();
	}
}

?>
