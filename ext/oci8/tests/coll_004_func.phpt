--TEST--
oci_collection_assign()
--SKIPIF--
<?php if (!extension_loaded('oci8')) die("skip no oci8 extension"); ?>
--FILE--
<?php

require dirname(__FILE__)."/connect.inc";
require dirname(__FILE__)."/create_type.inc";

$coll1 = oci_new_collection($c, $type_name);
$coll2 = oci_new_collection($c, $type_name);

var_dump(oci_collection_append($coll1, 1));

var_dump(oci_collection_assign($coll2, $coll1));

var_dump(oci_collection_element_get($coll2, 0));

echo "Done\n";

require dirname(__FILE__)."/drop_type.inc";

?>
--EXPECT--
bool(true)
bool(true)
float(1)
Done
