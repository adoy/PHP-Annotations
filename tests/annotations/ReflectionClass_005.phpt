--TEST--
ReflectionClass::getAnnotation with simple annotation
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

[SimpleAnnotation]
class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotation('SimpleAnnotation'));

?>
--EXPECTF--
object(SimpleAnnotation)#2 (1) {
  ["value"]=>
  NULL
}
