/* action_at_a_distance extension for PHP */

#ifndef ACTION_AT_A_DISTANCE_H
# define ACTION_AT_A_DISTANCE_H

extern zend_module_entry test_module_entry;
# define phpext_test_ptr &test_module_entry

# define ACTION_AT_A_DISTANCE_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TEST)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

ZEND_BEGIN_MODULE_GLOBALS(action_at_a_distance)
	zend_long scale;
ZEND_END_MODULE_GLOBALS(action_at_a_distance)

ZEND_EXTERN_MODULE_GLOBALS(action_at_a_distance)

#define TEST_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(action_at_a_distance, v)

#endif	/* ACTION_AT_A_DISTANCE_H */
