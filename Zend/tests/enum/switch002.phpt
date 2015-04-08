--TEST--
compare enum with scalars in switch statement

--FILE--
<?php

enum Either { A, B }

$either = Either::A;
switch ($either) {
    case 0:
        echo 0;
        break;
    case 1:
        echo 1;
        break;

    case 'A':
        echo 'A';
        break;
    case 'B':
        echo 'B';
        break;
}

echo 'Done.';

--EXPECT--
Done.
