--TEST--
SplFixedArray::slice with negative offset and negative length

--FILE--
<?php

$input = SplFixedArray::fromArray([1, 2, 3]);

$output = $input->slice(-3, -1);

var_export($output->toArray());

?>
--EXPECTF--
array (
  0 => 1,
  1 => 2,
)
