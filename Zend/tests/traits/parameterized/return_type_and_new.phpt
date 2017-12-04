--TEST--
Parameterized Traits - return type and new
--FILE--
<?php

trait Maker<T> {
    function make(): T {
        return new T();
    }
}

class MakerOfStdClass {
    use Maker<StdClass>;
}

$obj = new MakerOfStdClass;
echo strtolower(get_class($obj->make()));

?>
--EXPECT--
stdclass
