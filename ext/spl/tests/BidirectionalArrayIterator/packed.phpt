--TEST--
SPL: BidirectionalArrayIterator on packed array
--FILE--
<?php

require __DIR__ . '/ReverseIterator.inc';

$ar = [1, 2];
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
0: 1
1: 2
-----
1: 2
0: 1
