--TEST--
SPL: BidirectionalArrayIterator is final
--FILE--
<?php

class MyBidirectionalArrayIterator extends BidirectionalArrayIterator {}

?>
--EXPECTF--
Fatal error: Class MyBidirectionalArrayIterator may not inherit from final class (BidirectionalArrayIterator) in %s
