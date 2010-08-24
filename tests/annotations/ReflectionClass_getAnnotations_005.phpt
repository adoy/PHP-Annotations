--TEST--
ReflectionClass::getAnnotations with missing class 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

[SimpleAnnotation]
class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
Fatal error: Class 'SimpleAnnotation' not found in %s line %d
