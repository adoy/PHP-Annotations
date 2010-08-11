--TEST--
Multiple Annotations in class test
--FILE--

<?php

[Annotation({"foo", "bar", "red"})]
[AnotherAnnotation]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!