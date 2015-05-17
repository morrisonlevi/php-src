--TEST--
return type of null; something returned

--FILE--
<?php

function foo(): null {
    return 1;
}

try {
    foo();
} catch (TypeException $e) {
    echo $e->getMessage();
}

--EXPECTF--
Return value of foo() must be of the type null, integer returned in %s on line %d

