--TEST--
Annotation in property test
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