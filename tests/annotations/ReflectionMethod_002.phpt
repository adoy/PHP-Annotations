--TEST--
ReflectionMethod::getAnnotations with no annotation 
--FILE--
<?php

class Foo {
	public function bar() {}
}

$r = new ReflectionMethod('Foo','bar');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
