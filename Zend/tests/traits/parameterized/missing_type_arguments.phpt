--TEST--
Parameterized Traits - missing type arguments
--FILE--
<?php

trait TraitOf2<T, U> {}

class C {
    use TraitOf2<int>;
}

?>
--EXPECTF--
Fatal error: Number of type arguments %d does not match expected %d for parameterized type %s
