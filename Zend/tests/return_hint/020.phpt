--TEST--
Throw exception from hinted function
--FILE--
<?php
function test() : array {
	throw new Exception();
}

test();
--EXPECTF--
Fatal error: Uncaught exception 'Exception' in %s:%d
Stack trace:
#0 %s(%d): test()
#1 {main}
  thrown in %s on line %d

