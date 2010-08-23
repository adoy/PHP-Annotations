--TEST--
ReflectionMethod::getAnnotations with simple annotation
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
    ["value"]=>
    NULL
  }
}
