--TEST--
void return with no expr

--FILE--
<?php

function foo(): void {
    return;
}

foo();

echo "Done.";

--EXPECT--
Done.
