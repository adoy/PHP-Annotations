--TEST--
ReflectionFunction::getAnnotations with no annotation 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

function foo() {}

$r = new ReflectionFunction('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
