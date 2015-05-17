--TEST--
final return type of null

--FILE--
<?php

function foo(): null {
}

foo();

echo "Done.";

--EXPECT--
Done.
