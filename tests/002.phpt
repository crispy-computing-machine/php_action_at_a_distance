--TEST--
test_test1() Basic action_at_a_distance
--SKIPIF--
<?php
if (!extension_loaded('action_at_a_distance')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = action_at_a_distance_extension_loaded();

var_dump($ret);
?>
--EXPECT--
The extension action_at_a_distance is loaded and working!
NULL
