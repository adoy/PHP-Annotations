--TEST--
ReflectionClass::getAnnotations with Inherit 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php
[inherited]
class Annotation1 extends ReflectionAnnotation {}
class Annotation2 extends ReflectionAnnotation {}

[Annotation1("inherited")]
abstract class TestBase {
}
[Annotation2("declared")]
class Test extends TestBase {
}

$r = new ReflectionClass('Test');
var_dump($r->getAnnotations(ReflectionAnnotation::INHERITED));
var_dump($r->getAnnotations(ReflectionAnnotation::DECLARED));
var_dump($r->getAnnotations(ReflectionAnnotation::ALL));
?>
--EXPECTF--
array(1) {
  ["Annotation1"]=>
  object(Annotation1)#%d (1) {
    ["value"]=>
    string(9) "inherited"
  }
}
array(1) {
  ["Annotation2"]=>
  object(Annotation2)#%d (1) {
    ["value"]=>
    string(8) "declared"
  }
}
array(2) {
  ["Annotation2"]=>
  object(Annotation2)#%d (1) {
    ["value"]=>
    string(8) "declared"
  }
  ["Annotation1"]=>
  object(Annotation1)#%d (1) {
    ["value"]=>
    string(9) "inherited"
  }
}
