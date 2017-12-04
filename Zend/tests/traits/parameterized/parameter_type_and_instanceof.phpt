--TEST--
Parameterized Traits - parameter type and instanceof
--FILE--
<?php

trait Receiver<T> {
    function check(T $t) {
        return $t instanceof T;
    }
}

class ReceiverOfStdClass {
    use Receiver<StdClass>;
}

$obj = new ReceiverOfStdClass;
var_export($obj->check(new StdClass));

?>
--EXPECT--
true
