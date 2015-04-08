--TEST--
mismatch enum as parameter type

--FILE--
<?php

enum Singleton { Value }

function type_check(Singleton $value) {
    return $value;
}

try {
	type_check(0);
} catch (TypeException $e) {
	echo "Caught. ";
}

echo "Done.";

--EXPECT--
Caught. Done.
