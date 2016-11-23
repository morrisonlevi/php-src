--TEST--
SplFixedArray::slice from offset 1 to end

--FILE--
<?php

$input = SplFixedArray::fromArray([1, 2, 3]);

$output = $input->slice(1);

var_export($output->toArray());

?>
--EXPECTF--
array (
  0 => 2,
  1 => 3,
)
