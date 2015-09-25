--TEST--
Basic test cases for short Closure syntax
--FILE--
<?php

error_reporting(-1);

$foo = function() => 1;
var_dump($foo());

var_dump((function($a) => $foo)()());

$n = 2;

var_dump((function(&$a) => $a++)($n), $n);

var_dump((function($b, ...$a) => [$b] + $a)(1, 2, 3));

var_dump((function($b) => function($a) => $a + $b)(1)(2));

var_dump((function($a) => $b)(1));

var_dump(function($a) => $b);

?>
--EXPECTF--
int(1)

Warning: Missing argument 1 for {closure}(), called in %s on line %d and defined in %s on line %d
int(1)
int(2)
int(3)
array(2) {
  [0]=>
  int(1)
  [1]=>
  int(3)
}
int(3)

Notice: Undefined variable: b in %s on line %d
NULL
object(Closure)#%d (2) {
  ["static"]=>
  array(%d) {
  }
  ["parameter"]=>
  array(1) {
    ["$a"]=>
    string(10) "<required>"
  }
}

