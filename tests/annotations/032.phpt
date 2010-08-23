--TEST--
ReflectionProperty::getAnnotations with no annotation 
--FILE--
<?php

class Foo {
	public $bar;
}

$r = new ReflectionProperty('Foo','bar');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
