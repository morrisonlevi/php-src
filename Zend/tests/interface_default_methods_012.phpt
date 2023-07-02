--TEST--
Interface default methods are callable by `parent` in subclass of inheriter.
--FILE--
<?php

interface Interface1{
    function method1() { echo __METHOD__, "\n"; }
}

class Class1 implements Interface1 {
    // Method Interface1::method1() has been inherited here...
}

class Class2 extends Class1 {
    // ... so it's callable by `parent` here.
    function method1() { parent::method1(); }
}

(new Class1())->method1();

?>
--EXPECTF--
Interface1::method1
