--TEST--
JIT HOT LOOP: 002
--INI--
opcache.enable=1
opcache.enable_cli=1
opcache.file_update_protection=0
opcache.jit=tracing
opcache.jit_hot_func=2
opcache.jit_hot_loop=2
opcache.jit_hot_side_exit=0
;opcache.jit_debug=257
--EXTENSIONS--
opcache
--FILE--
<?php
function foo($n) {
  $res = 0;
  for ($i = 1; $i < $n; $i++)
    $res = $res + $i;
  return $res;
}
print foo(5);
?>
--EXPECT--
10
