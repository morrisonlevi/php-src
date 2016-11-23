--TEST--
SplFixedArray::slice with negative length

--FILE--
<?php

$input = SplFixedArray::fromArray([1, 2, 3]);

$output = $input->slice(1, -1);

var_export($output->toArray());

?>
--EXPECTF--
array (
  0 => 2,
)
