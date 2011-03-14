--TEST--
Test namespace usage within annotations
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

use Foo\Bar as Foobar;

require('namespace_001.inc');

[Foobar]
class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(1) {
  ["Foo\Bar"]=>
  object(Foo\Bar)#2 (1) {
    ["value":protected]=>
    NULL
  }
}
