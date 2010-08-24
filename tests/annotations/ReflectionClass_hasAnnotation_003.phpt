--TEST--
ReflectionClass::hasAnnotation with Inherit 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
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
var_dump($r->hasAnnotation('Annotation1', ReflectionAnnotation::INHERITED));
var_dump($r->hasAnnotation('Annotation1', ReflectionAnnotation::DECLARED));
var_dump($r->hasAnnotation('Annotation1', ReflectionAnnotation::ALL));
var_dump($r->hasAnnotation('Annotation2', ReflectionAnnotation::INHERITED));
var_dump($r->hasAnnotation('Annotation2', ReflectionAnnotation::DECLARED));
var_dump($r->hasAnnotation('Annotation2', ReflectionAnnotation::ALL));
?>
--EXPECTF--
bool(true)
bool(false)
bool(true)
bool(false)
bool(true)
bool(true)
