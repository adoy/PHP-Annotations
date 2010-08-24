--TEST--
ReflectionClass::getAnnotations with bad class 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation {}

[SimpleAnnotation]
class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
Fatal error: ReflectionClass::getAnnotations(): 'SimpleAnnotation' must extend 'ReflectionAnnotation' to act as an annotation in %s on line %d 
