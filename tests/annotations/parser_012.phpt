--TEST--
Annotation in property using array test
--FILE--

<?php

class Foo {
    [Annotation({"foo", "bar", "red"})]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!