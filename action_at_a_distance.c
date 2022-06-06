/**
 * @file action_at_a_distance.c
 * @brief action_at_a_distance extension for PHP
 * @version 0.1
 * @date 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_action_at_a_distance.h"

// For compatibility with older PHP versions
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

// INI Setup
ZEND_DECLARE_MODULE_GLOBALS(action_at_a_distance)
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("action_at_a_distance.debug", "1", PHP_INI_ALL, OnUpdateLong, debug, zend_action_at_a_distance_globals, action_at_a_distance_globals)
PHP_INI_END()

// Extension loaded test function
PHP_FUNCTION(action_at_a_distance_extension_loaded)
{
	ZEND_PARSE_PARAMETERS_NONE();
	php_printf("The extension %s is loaded and working!\r\n", "action_at_a_distance");
}

// Hello world test
PHP_FUNCTION(hello_world)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}


// Global variable setup 
static PHP_GINIT_FUNCTION(action_at_a_distance)
{
#if defined(COMPILE_DL_ACTION_AT_A_DISTANCE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	// Acces with ACTION_AT_A_DISTANCE_G(debug)
	action_at_a_distance_globals->debug = 1;
}

// Module Init, load ini file
PHP_MINIT_FUNCTION(action_at_a_distance)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}


// Info function, used by PHP
PHP_MINFO_FUNCTION(action_at_a_distance)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "action_at_a_distance support", "enabled");
	php_info_print_table_end();
}

// Function argument delcarations
ZEND_BEGIN_ARG_INFO(arginfo_action_at_a_distance_extension_loaded, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_hello_world, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()


// Function Delarations
static const zend_function_entry action_at_a_distance_functions[] = {
	PHP_FE(action_at_a_distance_extension_loaded,		arginfo_action_at_a_distance_extension_loaded)
	PHP_FE(hello_world,		arginfo_hello_world)
	PHP_FE_END
};


// action_at_a_distance_module_entry
zend_module_entry action_at_a_distance_module_entry = {
	STANDARD_MODULE_HEADER,
	"action_at_a_distance",					/* Extension name */
	action_at_a_distance_functions,			/* zend_function_entry */
	PHP_MINIT(action_at_a_distance),				/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	NULL,							/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(action_at_a_distance),			/* PHP_MINFO - Module info */
	ACTION_AT_A_DISTANCE_VERSION,		/* Version */
	PHP_MODULE_GLOBALS(action_at_a_distance),	/* Module globals */
	PHP_GINIT(action_at_a_distance),			/* PHP_GINIT - Globals initialization */
	NULL,					/* PHP_GSHUTDOWN - Globals shutdown */
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

// ZTS cache setup
#ifdef COMPILE_DL_ACTION_AT_A_DISTANCE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(action_at_a_distance)
#endif
