--TEST--
Spl\ReverseArrayIterator: get_iterator handler
--FILE--
<?php

$it = new Spl\ReverseArrayIterator([0, 4, 8, 12]);


$array = [];
array_push($array, ...$it);

var_export($array);
echo PHP_EOL;

?>
--EXPECT--
array (
  0 => 12,
  1 => 8,
  2 => 4,
  3 => 0,
)
