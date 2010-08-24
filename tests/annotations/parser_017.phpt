--TEST--
Annotation in method using single property test
--FILE--

<?php

class Foo {
    [Annotation(name="value")]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!