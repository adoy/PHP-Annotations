--TEST--
Multiple Annotations in function test
--FILE--

<?php

[Annotation({"foo", "bar", "red"})]
[AnotherAnnotation]
function foo() {
}

echo 'OK!';

?>
--EXPECT--
OK!