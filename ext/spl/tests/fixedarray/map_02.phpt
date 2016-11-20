--TEST--
SplFixedArray::map with one or more elements

--FILE--
<?php

function negate($b) {
    return !$b;
}

$input = new SplFixedArray(2);
$input[0] = false;
$input[1] = true;

$output = $input->map('negate');

var_export($output->toArray());
echo "\n";

// ensure original is untouched
var_export($input->toArray());
?>
--EXPECTF--
array (
  0 => true,
  1 => false,
)
array (
  0 => false,
  1 => true,
)
