--TEST--
ReflectionClass::getAnnotations with no annotation 
--FILE--
<?php

class Foo {
}

$r = new ReflectionClass('Foo');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
