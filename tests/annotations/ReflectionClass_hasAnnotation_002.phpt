--TEST--
ReflectionClass::hasAnnotation with no annotation 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->hasAnnotation('SimpleAnnotation'));

?>
--EXPECTF--
bool(false)
