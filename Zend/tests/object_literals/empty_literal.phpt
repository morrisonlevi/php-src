--TEST--
Empty object literal
--FILE--
<?php

$obj = {};

var_export(is_object($obj));

?>
--EXPECT--
true
