--TEST--
Annotation in method test
--FILE--

<?php

class Foo {
    [Annotation]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!