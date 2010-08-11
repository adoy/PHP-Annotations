--TEST--
Annotation in class without value test
--FILE--

<?php

[Annotation]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!