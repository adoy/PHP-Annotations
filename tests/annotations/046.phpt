--TEST--
ReflectionClass::hasAnnotation with no annotation 
--FILE--
<?php

class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->hasAnnotation('SimpleAnnotation'));

?>
--EXPECTF--
bool(false)
