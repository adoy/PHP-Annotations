--TEST--
ReflectionProperty::getAnnotations with overrided property 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

abstract class Base {
	[SimpleAnnotation]
	public $bar;
}
class Foo extends Base {
	public $bar;
}

$r = new ReflectionProperty('Foo','bar');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(0) {
}
