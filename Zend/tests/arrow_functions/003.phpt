--TEST--
Arrow function closing over variable
--FILE--
<?php

$b = 1;

var_dump((fn () => $b)());

?>
--EXPECTF--
int(1)

