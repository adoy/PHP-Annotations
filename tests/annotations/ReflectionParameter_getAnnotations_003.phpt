--TEST--
ReflectionMethod::getAnnotations with complex annotations
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

class SimpleAnnotation1 extends ReflectionAnnotation {
}
class SimpleAnnotation2 extends ReflectionAnnotation {
	public $foo;	
}

function foo([SimpleAnnotation1(value=array(
		[SimpleAnnotation2()],
		[SimpleAnnotation2("test")],
		[SimpleAnnotation2(foo="bar")]
	))] $bar) 
{
}

$r = new ReflectionFunction('foo');
foreach ($r->getParameters() as $argument) {
	    var_dump($argument->getAnnotations());
} 
?>
--EXPECTF--
array(1) {
  ["SimpleAnnotation1"]=>
  object(SimpleAnnotation1)#%d (1) {
    ["value":protected]=>
    array(3) {
      [0]=>
      object(SimpleAnnotation2)#%d (2) {
        ["foo"]=>
        NULL
        ["value":protected]=>
        NULL
      }
      [1]=>
      object(SimpleAnnotation2)#%d (2) {
        ["foo"]=>
        NULL
        ["value":protected]=>
        string(4) "test"
      }
      [2]=>
      object(SimpleAnnotation2)#%d (2) {
        ["foo"]=>
        string(3) "bar"
        ["value":protected]=>
        NULL
      }
    }
  }
}
