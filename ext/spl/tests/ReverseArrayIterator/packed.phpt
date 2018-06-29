--TEST--
SPL: ReverseArrayIterator on packed array
--FILE--
<?php

$ar = [1, 2];
$it = new ReverseArrayIterator($ar);

foreach ($it as $key => $value) {
    echo "{$key}: {$value}\n";
}

?>
--EXPECT--
1: 2
0: 1
