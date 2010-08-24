--TEST--
Annotation in method using properties test
--FILE--

<?php

class Foo {
    [Annotation(name="value", foo="bar")]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!