--TEST--
SPL: ReverseArrayIterator is countable
--FILE--
<?php

$empty = new ReverseArrayIterator([]);
$packed = new ReverseArrayIterator([1, 2]);
$assoc = new ReverseArrayIterator(["one" => 1, "two" => 2, "three" => 3]);

echo $empty->count(), "\n";
echo $packed->count(), "\n";
echo $assoc->count(), "\n";


?>
--EXPECT--
0
2
3

