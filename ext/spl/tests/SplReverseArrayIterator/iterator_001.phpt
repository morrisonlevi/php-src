--TEST--
Spl\ReverseArrayIterator: Iterator interface (empty)
--FILE--
<?php

$ht = []; 

$it = new Spl\ReverseArrayIterator($ht);

var_dump($it);
foreach ($it as $key => $value) {
    var_export([$key => $value]);
    echo "\n";
}
var_dump($it);

echo "\nagain, manually this time\n\n";

$it->rewind();
var_dump($it);
while ($it->valid()) {
    var_export([$it->key() => $it->current()]);
    echo "\n";
}
var_dump($it);

?>
--EXPECTF--
object(Spl\ReverseArrayIterator)#%d (2) {
  ["inner"]=>
  array(0) {
  }
  ["offset"]=>
  int(0)
}
object(Spl\ReverseArrayIterator)#%d (2) {
  ["inner"]=>
  array(0) {
  }
  ["offset"]=>
  int(0)
}

again, manually this time

object(Spl\ReverseArrayIterator)#%d (2) {
  ["inner"]=>
  array(0) {
  }
  ["offset"]=>
  int(0)
}
object(Spl\ReverseArrayIterator)#%d (2) {
  ["inner"]=>
  array(0) {
  }
  ["offset"]=>
  int(0)
}
