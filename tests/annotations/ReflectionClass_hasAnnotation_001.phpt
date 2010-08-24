--TEST--
ReflectionClass::hasAnnotation with simple annotation
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
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
