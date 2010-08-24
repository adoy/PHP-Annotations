--TEST--
Annotation in function using properties test
--FILE--

<?php

[Annotation(name="value", foo="bar")]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!