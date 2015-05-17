--TEST--
return type of null

--FILE--
<?php

function foo(): null {
    return null;
}

foo();

echo "Done.";

--EXPECT--
Done.
