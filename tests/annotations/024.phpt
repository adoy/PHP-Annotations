--TEST--
Annotation in function using single property test
--FILE--

<?php

[Annotation(name="value")]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!