--TEST--
Annotations on parameters
--FILE--

<?php

function foo([Annotation(name="value")] $bar)
{
}

class foo {
	public function foo([Annotations()] $bar)
	{
	}
}

echo 'OK!';

?>
--EXPECTF--
OK!
