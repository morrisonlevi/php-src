--TEST--
SPL: BidirectionalArrayIterator is rewindable
--FILE--
<?php

require __DIR__ . '/ReverseIterator.inc';

$ar = ["one" => 1, "two" => 2];
$it = new BidirectionalArrayIterator($ar);

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

echo "-----\n";

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

echo "-----\n";

$reverse = new ReverseIterator($it);
foreach ($reverse as $key => $value) {
    echo "{$key}: {$value}\n";
}

echo "-----\n";

foreach ($reverse as $key => $value) {
    echo "{$key}: {$value}\n";
}

?>
--EXPECT--
one: 1
two: 2
-----
one: 1
two: 2
-----
two: 2
one: 1
-----
two: 2
one: 1

