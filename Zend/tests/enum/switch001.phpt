--TEST--
enum in switch statement

--FILE--
<?php

enum Either { A, B }

$either = Either::A;
switch ($either) {
    case Either::B:
        echo "B";
        break;
    case Either::A:
        echo "A";
        break;
}

--EXPECT--
A
