--TEST--
SplFixedArray::map with no elements

--FILE--
<?php

function donotcall() {
    echo "fail";
}

$input = new SplFixedArray(0);

$output = $input->map('donotcall');

var_dump(count($output));

?>
--EXPECTF--
int(0)
