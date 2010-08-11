--TEST--
Annotation in property without value test
--FILE--

<?php

class Foo {
    [Annotation]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!
