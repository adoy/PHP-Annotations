--TEST--
ReflectionFunction::getAnnotations with no annotation 
--FILE--
<?php

function foo() {}

$r = new ReflectionFunction('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
