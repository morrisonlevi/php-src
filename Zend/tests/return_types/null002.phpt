--TEST--
implicit return type of null

--FILE--
<?php

function foo(): null {
    return;
}

foo();

echo "Done.";

--EXPECT--
Done.
