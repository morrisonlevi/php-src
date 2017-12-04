--TEST--
Parameterized Traits - parameter type fails
--FILE--
<?php

trait Receiver<T> {
    function check(T $t) {}
}

class ReceiverOfStdClass {
    use Receiver<StdClass>;
}

$obj = new ReceiverOfStdClass;

try {
    $obj->check(0);
    echo "Parameter type unexpectedly passes.";
} catch (TypeError $e) {
    echo $e->getMessage();
}

?>
--EXPECTF--
Argument 1 passed to ReceiverOfStdClass::check() must be an instance of stdClass, integer given%s
