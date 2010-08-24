--TEST--
Annotation in function without value test
--FILE--

<?php

[Annotation]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!