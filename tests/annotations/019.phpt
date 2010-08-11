--TEST--
Annotation in method using array test
--FILE--

<?php

class Foo {
    [Annotation({"foo", "bar", "red"})]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!