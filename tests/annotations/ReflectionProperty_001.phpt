--TEST--
ReflectionProperty::getAnnotations with simple annotation
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

class Foo {
	[SimpleAnnotation]
	public $bar;
}

$r = new ReflectionProperty('Foo','bar');
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
