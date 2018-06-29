--TEST--
SPL: BidirectionalArrayIterator is countable
--FILE--
<?php

$empty = new BidirectionalArrayIterator([]);
$packed = new BidirectionalArrayIterator([1, 2]);
$assoc = new BidirectionalArrayIterator(["one" => 1, "two" => 2, "three" => 3]);

echo $empty->count(), "\n";
echo $packed->count(), "\n";
echo $assoc->count(), "\n";


?>
--EXPECT--
0
2
3

