--TEST--
compare enum to boolean

--FILE--
<?php

enum Singleton { Value }

var_dump(Singleton::Value == true);
var_dump(Singleton::Value == false);

var_dump(Singleton::Value === true);
var_dump(Singleton::Value === false);

--EXPECT--
bool(true)
bool(false)
bool(false)
bool(false)
