--TEST--
void return with expr

--FILE--
<?php

function foo(): void {
    return 1;
}

foo();

echo "Done.";

--EXPECTF--
Fatal error: Void function 'foo' may not return a value in %s on line %d
