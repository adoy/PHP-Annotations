--TEST--
ReflectionClass::getAnnotations with constant value 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {}

[SimpleAnnotation(Foo::OK)]
class Foo {
	const OK = "OK!";
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(1) {
  ["SimpleAnnotation"]=>
  object(SimpleAnnotation)#%d (1) {
    ["value"]=>
    string(3) "OK!"
  }
}
