--TEST--
SPL: BidirectionalArrayIterator on associative array
--FILE--
<?php

require __DIR__ . '/ReverseIterator.inc';

$ar = ["one" => 1, "two" => 2];
$it = new BidirectionalArrayIterator($ar);

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

echo "-----\n";

foreach (new ReverseIterator($it) as $key => $value) {
    echo "{$key}: {$value}\n";
}

?>
--EXPECT--
one: 1
two: 2
-----
two: 2
one: 1

