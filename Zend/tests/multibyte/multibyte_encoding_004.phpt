--TEST--
test for mbstring script_encoding for flex unsafe encoding (Shift_JIS)
--SKIPIF--
<?php
if (!in_array("detect_unicode", array_keys(ini_get_all()))) {
  die("skip Requires configure --enable-zend-multibyte option");
}
if (!extension_loaded("mbstring")) {
  die("skip Requires mbstring extension");
}
?>
--INI--
mbstring.script_encoding=Shift_JIS
mbstring.internal_encoding=Shift_JIS
--FILE--
<?php
	function �\�\�\($����)
	{
		echo $����;
	}

	�\�\�\("�h���~�t�@�\");
?>
--EXPECT--
�h���~�t�@�\
