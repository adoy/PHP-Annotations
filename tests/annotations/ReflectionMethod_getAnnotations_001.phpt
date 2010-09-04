--TEST--
ReflectionMethod::getAnnotations with simple annotation
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

class Foo {
	[SimpleAnnotation]
	public function bar() {}
}

$r = new ReflectionMethod('Foo','bar');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(1) {
  ["SimpleAnnotation"]=>
  object(SimpleAnnotation)#%d (1) {
    ["value":protected]=>
    NULL
  }
}
