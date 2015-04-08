--TEST--
use enum as parameter and return type

--FILE--
<?php

enum Singleton { Value }


function type_check(Singleton $value): Singleton {
    return $value;
}

type_check(Singleton::Value);

echo "Done.";

--EXPECT--
Done.
