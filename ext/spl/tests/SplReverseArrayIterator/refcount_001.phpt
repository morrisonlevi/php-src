--TEST--
Spl\ReverseArrayIterator: protected from changes
--FILE--
<?php

$ht = [1];

$it = new Spl\ReverseArrayIterator($ht);

\array_pop($ht);
var_export($ht);
echo "\n";

foreach ($it as $key => $value) {
    var_export([$key => $value]);
    echo "\n";
}

?>
--EXPECTF--
array (
)
array (
  0 => 1,
)

