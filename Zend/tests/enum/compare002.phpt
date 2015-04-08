--TEST--
enum in implicit conditional

--FILE--
<?php

enum Singleton { Value }

if (Singleton::Value) {
    echo 'True. ';
}

echo 'Done.';

--EXPECT--
True. Done.
