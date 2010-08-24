--TEST--
ReflectionClass::getAnnotation with Inherit 
--FILE--
<?php
[Inherit]
class Annotation1 extends ReflectionAnnotation {}
class Annotation2 extends ReflectionAnnotation {}

[Annotation1("inherited")]
abstract class TestBase {
}
[Annotation2("declared")]
class Test extends TestBase {
}

$r = new ReflectionClass('Test');
var_dump($r->getAnnotation('Annotation1', ReflectionAnnotation::INHERITED));
var_dump($r->getAnnotation('Annotation1', ReflectionAnnotation::DECLARED));
var_dump($r->getAnnotation('Annotation1', ReflectionAnnotation::ALL));
var_dump($r->getAnnotation('Annotation2', ReflectionAnnotation::INHERITED));
var_dump($r->getAnnotation('Annotation2', ReflectionAnnotation::DECLARED));
var_dump($r->getAnnotation('Annotation2', ReflectionAnnotation::ALL));
?>
--EXPECTF--
object(Annotation1)#%d (1) {
  ["value"]=>
  string(9) "inherited"
}
bool(false)
object(Annotation1)#%d (1) {
  ["value"]=>
  string(9) "inherited"
}
bool(false)
object(Annotation2)#%d (1) {
  ["value"]=>
  string(8) "declared"
}
object(Annotation2)#%d (1) {
  ["value"]=>
  string(8) "declared"
}
