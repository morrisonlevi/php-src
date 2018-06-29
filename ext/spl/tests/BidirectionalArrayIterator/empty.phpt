--TEST--
SPL: BidirectionalArrayIterator on empty array
--FILE--
<?php

$ar = [];
$it = new BidirectionalArrayIterator($ar);
$it->rewind();
echo $it->valid() ? "not empty\n" : "empty\n";

?>
--EXPECT--
empty

