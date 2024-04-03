--TEST--
Spl\ForwardArrayIterator: get_iterator handler
--FILE--
<?php

$it = new Spl\ForwardArrayIterator([0, 4, 8, 12]);


$array = [];
array_push($array, ...$it);

var_export($array);
echo PHP_EOL;

?>
--EXPECT--
array (
  0 => 0,
  1 => 4,
  2 => 8,
  3 => 12,
)
