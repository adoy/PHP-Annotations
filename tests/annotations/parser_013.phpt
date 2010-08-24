--TEST--
Multiple Annotations in property test
--FILE--

<?php

class Foo {
    [Annotation({"foo", "bar", "red"})]
    [AnotherAnnotation]
    public $bar;
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!