--TEST--
Annotation in method using unique value test
--FILE--

<?php

class Foo {
    [Annotation("value")]
    public function bar() {
        echo 'do nothing';
    }
}

$foo = new Foo();

echo 'OK!';

?>
--EXPECT--
OK!