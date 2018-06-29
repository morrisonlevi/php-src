--TEST--
SPL: ReverseArrayIterator is rewindable
--FILE--
<?php

$ar = ["one" => 1, "two" => 2];
$it = new ReverseArrayIterator($ar);

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

echo "-----\n";

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

?>
--EXPECT--
two: 2
one: 1
-----
two: 2
one: 1

