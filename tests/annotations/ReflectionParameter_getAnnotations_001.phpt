--TEST--
ReflectionParameter::getAnnotations with simple annotation
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

function foo([SimpleAnnotation] $bar)
{
}

$r = new ReflectionFunction('foo');
foreach ($r->getParameters() as $argument) {
	var_dump($argument->getAnnotations());
}

?>
--EXPECTF--
array(1) {
  ["SimpleAnnotation"]=>
  object(SimpleAnnotation)#%d (1) {
    ["value":protected]=>
    NULL
  }
}
