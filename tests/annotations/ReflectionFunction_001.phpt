--TEST--
ReflectionFunction::getAnnotations with simple annotation
--FILE--
<?php

class SimpleAnnotation extends ReflectionAnnotation {
}

[SimpleAnnotation]
function foo() {}

$r = new ReflectionFunction('Foo');
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
