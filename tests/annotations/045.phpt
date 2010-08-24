--TEST--
ReflectionClass::hasAnnotation with simple annotation
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

[SimpleAnnotation]
class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->hasAnnotation('SimpleAnnotation'));

?>
--EXPECTF--
bool(true)
