--TEST--
Annotation in class using array test
--FILE--

<?php

[Annotation(array("foo", "bar", "red"))]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!
