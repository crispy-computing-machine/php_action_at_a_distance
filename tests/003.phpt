--TEST--
test_test2() Basic action_at_a_distance
--SKIPIF--
<?php
if (!extension_loaded('action_at_a_distance')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(test_test2());
var_dump(test_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
