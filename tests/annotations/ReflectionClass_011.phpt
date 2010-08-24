--TEST--
ReflectionClass::hasAnnotation with Inherit 
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
var_dump($r->hasAnnotation('Annotation1', ReflectionClass::GET_INHERITED));
var_dump($r->hasAnnotation('Annotation1', ReflectionClass::GET_DECLARED));
var_dump($r->hasAnnotation('Annotation1', ReflectionClass::GET_BOTH));
var_dump($r->hasAnnotation('Annotation2', ReflectionClass::GET_INHERITED));
var_dump($r->hasAnnotation('Annotation2', ReflectionClass::GET_DECLARED));
var_dump($r->hasAnnotation('Annotation2', ReflectionClass::GET_BOTH));
?>
--EXPECTF--
bool(true)
bool(false)
bool(true)
bool(false)
bool(true)
bool(true)
