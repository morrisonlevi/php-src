--TEST--
Parameterized Traits - use requires type arguments
--FILE--
<?php

trait Maker<T> {
    function make(): T {
        return new T();
    }
}

class MakerOfStdClass {
    use Maker;
}

?>
--EXPECTF--
Number of type arguments 0 does not match expected %d for parameterized type %s
