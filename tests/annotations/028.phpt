--TEST--
ReflectionClass::getAnnotations with simple annotation
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

[SimpleAnnotation]
class Foo {
}

$r = new ReflectionClass('Foo');
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
