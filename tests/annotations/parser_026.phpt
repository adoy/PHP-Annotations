--TEST--
Annotation in function using array test
--FILE--

<?php

[Annotation({"foo", "bar", "red"})]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!