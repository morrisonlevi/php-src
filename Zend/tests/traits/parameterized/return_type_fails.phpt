--TEST--
Parameterized Traits - return type fails
--FILE--
<?php

trait Maker<T> {
    function make(): T {
        return 0;
    }
}

class MakerOfStdClass {
    use Maker<StdClass>;
}

$obj = new MakerOfStdClass;
try {
    $obj->make();
    echo "Return type unexpectedly passes.";
} catch (TypeError $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
Return value of MakerOfStdClass::make() must be an instance of stdClass, integer returned
