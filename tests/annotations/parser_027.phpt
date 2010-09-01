--TEST--
Multiple Annotations in function test
--FILE--

<?php

[Annotation(array("foo", "bar", "red"))]
[AnotherAnnotation]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!
