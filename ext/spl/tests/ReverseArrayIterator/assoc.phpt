--TEST--
SPL: ReverseArrayIterator on associative array
--FILE--
<?php

$ar = ["one" => 1, "two" => 2];
$it = new ReverseArrayIterator($ar);

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

?>
--EXPECT--
two: 2
one: 1
