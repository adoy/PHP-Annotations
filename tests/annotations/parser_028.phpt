--TEST--
Duplicated annotation
--FILE--

<?php

[Annotation(name="value", foo="bar")]
[Annotation(name="value", foo="bar")]
class foo() {
}

echo 'OK!';

?>
--EXPECTF--
Fatal error: Cannot redeclare annotation 'Annotation' in %s on line %d
