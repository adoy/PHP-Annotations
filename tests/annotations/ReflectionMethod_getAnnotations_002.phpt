--TEST--
ReflectionMethod::getAnnotations with no annotation 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
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
