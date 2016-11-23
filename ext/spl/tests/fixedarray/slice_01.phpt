--TEST--
SplFixedArray::slice from beginning to end

--FILE--
<?php

$input = SplFixedArray::fromArray([1, 2, 3]);

$output = $input->slice(0);

var_export($output->toArray());

?>
--EXPECTF--
array (
  0 => 1,
  1 => 2,
  2 => 3,
)
