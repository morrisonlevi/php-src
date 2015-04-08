--TEST--
compare equality of two enum types

--FILE--
<?php

enum Color {
	Red,
	Blue
}

enum Button {
	A,
	B
}

var_dump(Color::Red != Button::A);
var_dump(Color::Red != Button::B);

var_dump(Color::Blue != Button::A);
var_dump(Color::Blue != Button::B);

--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
