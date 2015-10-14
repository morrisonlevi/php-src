--TEST--
void return with implicit return

--FILE--
<?php

function foo(): void {
}

foo();

echo "Done.";

--EXPECT--
Done.
