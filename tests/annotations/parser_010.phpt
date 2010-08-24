--TEST--
Annotation in property using single property test
--FILE--

<?php

class Foo {
    [Annotation(name="value")]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!