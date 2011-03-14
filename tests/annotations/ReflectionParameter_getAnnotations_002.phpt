--TEST--
ReflectionMethod::getAnnotations with no annotation 
--SKIPIF--
<?php extension_loaded('reflection') or die('skip'); ?>
--FILE--
<?php

function foo($bar)
{
}

$r = new ReflectionFunction('foo');
foreach ($r->getParameters() as $argument) {
	var_dump($argument->getAnnotations());
}
?>
--EXPECTF--
array(0) {
}
