--TEST--
compar enum values with =<, <, >, >=

--FILE--
<?php

enum DayOfWeek {
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
}

var_dump(DayOfWeek::Sunday < DayOfWeek::Monday);
var_dump(DayOfWeek::Tuesday > DayOfWeek::Wednesday);
var_dump(DayOfWeek::Thursday <= DayOfWeek::Friday);
var_dump(DayOfWeek::Friday >= DayOfWeek::Saturday);

--EXPECT--
bool(false)
bool(false)
bool(false)
bool(false)
