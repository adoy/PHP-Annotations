--TEST--
Annotation in property using unique value test
--FILE--

<?php

class Foo {
    [Annotation("value")]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!