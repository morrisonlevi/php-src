--TEST--
SPL: ReverseArrayIterator is final
--FILE--
<?php

class MyReverseArrayIterator extends ReverseArrayIterator {}

?>
--EXPECTF--
Fatal error: Class MyReverseArrayIterator may not inherit from final class (ReverseArrayIterator) in %s
