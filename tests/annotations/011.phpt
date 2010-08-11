--TEST--
Annotation in property using properties test
--FILE--

<?php

class Foo {
    [Annotation(name="value", foo="bar")]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!