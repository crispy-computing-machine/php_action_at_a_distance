--TEST--
Check if action_at_a_distance is loaded
--SKIPIF--
<?php
if (!extension_loaded('action_at_a_distance')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "action_at_a_distance" is available';
?>
--EXPECT--
The extension "action_at_a_distance" is available
