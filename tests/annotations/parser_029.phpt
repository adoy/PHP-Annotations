--TEST--
Duplicated annotation value
--FILE--

<?php

[Annotation(name="value", name="bar")]
class foo() {
}

echo 'OK!';

?>
--EXPECTF--
Fatal error: Cannot redeclare property 'name' on annotation 'Annotation' in %s on line %d
