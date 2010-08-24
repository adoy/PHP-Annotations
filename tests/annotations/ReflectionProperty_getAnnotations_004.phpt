--TEST--
ReflectionProperty::getAnnotations with inherited property 
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
}

$r = new ReflectionProperty('Foo','bar');
var_dump($r->getAnnotations());

?>
--EXPECTF--
array(1) {
  ["SimpleAnnotation"]=>
  object(SimpleAnnotation)#%d (1) {
    ["value"]=>
    NULL
  }
}
