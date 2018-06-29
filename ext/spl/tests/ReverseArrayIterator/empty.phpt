--TEST--
SPL: ReverseArrayIterator on empty array
--FILE--
<?php

$ar = [];
$it = new ReverseArrayIterator($ar);
$it->rewind();
echo $it->valid() ? "not empty\n" : "empty\n";

?>
--EXPECT--
empty

