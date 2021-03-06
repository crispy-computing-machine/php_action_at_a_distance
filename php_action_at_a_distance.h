/**
 * @file php_action_at_a_distance.h
 * @brief action_at_a_distance extension for PHP
 * @version 0.1
 * @date 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "php.h"
#include "ext/standard/info.h"

#ifndef ACTION_AT_A_DISTANCE_H
# define ACTION_AT_A_DISTANCE_H

extern zend_module_entry action_at_a_distance_module_entry;
# define phpext_action_at_a_distance_ptr &action_at_a_distance_module_entry

// Varseion string for phpinfo
# define ACTION_AT_A_DISTANCE_VERSION "0.1.0"

// Defained namespace
# define PHP_ACTION_AT_A_DISTANCE_NS "Action"

# if defined(ZTS) && defined(COMPILE_DL_ACTION_AT_A_DISTANCE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

// Global var declarations
ZEND_BEGIN_MODULE_GLOBALS(action_at_a_distance)
	zend_long debug;
ZEND_END_MODULE_GLOBALS(action_at_a_distance)
ZEND_EXTERN_MODULE_GLOBALS(action_at_a_distance)

// Global variable access macro
# define ACTION_AT_A_DISTANCE_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(action_at_a_distance, v)

#endif	/* ACTION_AT_A_DISTANCE_H */