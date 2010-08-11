--TEST--
Annotation in class using properties test
--FILE--

<?php

[Annotation(name="value", foo="bar")]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!