--TEST--
SplFixedArray::map with by-ref parameter

--FILE--
<?php

function by_ref(&$arg) {
	$arg = !$arg;
    return $arg;
}

$input = new SplFixedArray(2);
$input[0] = false;
$input[1] = true;

try {
    $output = $input->map('by_ref');
} catch (InvalidArgumentException $e) {
    echo "Caught\n";
}
?>
--EXPECTF--
Caught

