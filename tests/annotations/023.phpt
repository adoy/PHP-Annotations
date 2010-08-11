--TEST--
Annotation in function using unique value test
--FILE--

<?php

[Annotation("value")]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!