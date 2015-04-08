--TEST--
enum equality using == and ===

--FILE--
<?php

enum A {
	a, b
}

var_dump(A::a == A::a);
var_dump(A::a === A::a);

var_dump(A::b == A::b);
var_dump(A::b === A::b);

var_dump(A::a == A::b);
var_dump(A::a === A::b);

--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(false)
bool(false)
