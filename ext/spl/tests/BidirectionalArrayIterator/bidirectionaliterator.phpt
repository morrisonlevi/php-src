--TEST--
SPL: BidirectionalArrayIterator is BidirectionalIterator
--FILE--
<?php

$empty = new BidirectionalArrayIterator([]);

var_export($empty instanceof BidirectionalIterator);

?>
--EXPECT--
true
