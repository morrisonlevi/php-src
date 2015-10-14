--TEST--
void parameter

--FILE--
<?php

function foo(void $p) {
    return 1;
}

foo();

echo "Done.";

--EXPECTF--
Fatal error: Parameter 'p' may not have void type in %s on line %d
