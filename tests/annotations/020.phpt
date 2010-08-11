--TEST--
Multiple Annotations in method test
--FILE--

<?php

class Foo {
    [Annotation({"foo", "bar", "red"})]
    [AnotherAnnotation]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!