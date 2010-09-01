--TEST--
Multiple Annotations in class test
--FILE--

<?php

[Annotation(array("foo", "bar", "red"))]
[AnotherAnnotation]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!
