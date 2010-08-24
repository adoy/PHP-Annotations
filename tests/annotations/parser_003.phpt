--TEST--
Annotation in class using single property test
--FILE--

<?php

[Annotation(name="value")]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!