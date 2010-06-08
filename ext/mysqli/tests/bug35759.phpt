--TEST--
Bug #35759 (mysqli_stmt_bind_result() makes huge allocation when column empty)
--SKIPIF--
<?php
require_once('skipif.inc');
require_once('skipifconnectfailure.inc');
?>
--FILE--
<?php

$sql=<<<EOSQL
CREATE TABLE blobby (
  a1 MEDIUMBLOB NOT NULL,


EOSQL;
	require_once("connect.inc");
	$col_num= 1000;

	$mysql = new mysqli($host, $user, $passwd, $db, $port, $socket);
	$mysql->query("DROP TABLE IF EXISTS blobby");
	$create = "CREATE TABLE blobby (a0 MEDIUMBLOB NOT NULL DEFAULT ''";
	$i= 0;
	while (++$i < $col_num) {
		$create .= ", a$i MEDIUMBLOB NOT NULL DEFAULT ''";
	}
        $create .= ")";

        $mysql->query($create);
	$mysql->query("INSERT INTO blobby (a0) VALUES ('')");

	$stmt = $mysql->prepare("SELECT * FROM blobby");
	$stmt->execute();
	$stmt->store_result();
	for ($i = 0; $i < $col_num; $i++) {
		$params[] = &$col_num;
	}
	call_user_func_array(array($stmt, "bind_result"), $params);
	$stmt->fetch();

	$stmt->close();

	$mysql->query("DROP TABLE blobby");

	$mysql->close();
	echo "OK\n";
?>
--CLEAN--
<?php
require_once("connect.inc");
if (!$link = my_mysqli_connect($host, $user, $passwd, $db, $port, $socket))
   printf("[c001] [%d] %s\n", mysqli_connect_errno(), mysqli_connect_error());

if (!mysqli_query($link, "DROP TABLE IF EXISTS blobby"))
	printf("[c002] Cannot drop table, [%d] %s\n", mysqli_errno($link), mysqli_error($link));

mysqli_close($link);
?>
--EXPECT--
OK
