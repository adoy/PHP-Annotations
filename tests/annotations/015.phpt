--TEST--
Annotation in method without value test
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
