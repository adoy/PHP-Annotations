--TEST--
ReflectionClass::getAnnotation with no annotation 
--FILE--
<?php

class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotation('SimpleAnnotation'));

?>
--EXPECTF--
bool(false)
