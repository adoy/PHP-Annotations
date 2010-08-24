--TEST--
Annotation in class using unique value test
--FILE--

<?php

[Annotation("value")]
class Foo {
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!