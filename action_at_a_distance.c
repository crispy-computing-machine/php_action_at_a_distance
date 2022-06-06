/* action_at_a_distance extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_action_at_a_distance.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(action_at_a_distance)

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("action_at_a_distance.scale", "1", PHP_INI_ALL, OnUpdateLong, scale,
		zend_action_at_a_distance_globals, action_at_a_distance_globals)
PHP_INI_END()

/* {{{ void action_at_a_distance_extension_loaded()
 */
PHP_FUNCTION(action_at_a_distance_extension_loaded)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "action_at_a_distance");
}
/* }}} */

/* {{{ string hellow_world( [ string $var ] )
 */
PHP_FUNCTION(hellow_world)
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
/* }}}*/

static int do_scale_ref(zval *x, zend_long factor)
{
	ZVAL_DEREF(x);
	if (Z_TYPE_P(x) == IS_LONG) {
		Z_LVAL_P(x) *= factor;
	} else if (Z_TYPE_P(x) == IS_DOUBLE) {
		Z_DVAL_P(x) *= factor;
	} else if (Z_TYPE_P(x) == IS_STRING) {
		size_t len = Z_STRLEN_P(x);
		char *p;

		ZVAL_STR(x, zend_string_safe_realloc(Z_STR_P(x), len, factor, 0, 0));
		p = Z_STRVAL_P(x) + len;
		while (--factor > 0) {
			memcpy(p, Z_STRVAL_P(x), len);
			p += len;
		}
		*p = '\000';
	} else if (Z_TYPE_P(x) == IS_ARRAY) {
		zval *val;

		SEPARATE_ARRAY(x);
		ZEND_HASH_FOREACH_VAL(Z_ARR_P(x), val) {
			if (do_scale_ref(val, factor) != SUCCESS) {
				return FAILURE;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		php_error_docref(NULL, E_WARNING, "unexpected argument type");
		return FAILURE;
	}
	return SUCCESS;
}

PHP_FUNCTION(action_at_a_distance_scale_ref)
{
	zval *x;
	zend_long factor = action_at_a_distance_G(scale); // default value

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(x)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(factor)
	ZEND_PARSE_PARAMETERS_END();

	do_scale_ref(x, factor);
}

static PHP_GINIT_FUNCTION(action_at_a_distance)
{
#if defined(COMPILE_DL_BCMATH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	action_at_a_distance_globals->scale= 1;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(action_at_a_distance)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(action_at_a_distance)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "action_at_a_distance support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_action_at_a_distance_extension_loaded, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_hellow_world, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

ZEND_BEGIN_ARG_INFO(arginfo_action_at_a_distance_scale_ref, 0)
	ZEND_ARG_INFO(1, x) // pass by reference
	ZEND_ARG_INFO(0, factor)
ZEND_END_ARG_INFO()

/* {{{ action_at_a_distance_functions[]
 */
static const zend_function_entry action_at_a_distance_functions[] = {
	PHP_FE(action_at_a_distance_extension_loaded,		arginfo_action_at_a_distance_extension_loaded)
	PHP_FE(hellow_world,		arginfo_hellow_world)
	PHP_FE(action_at_a_distance_scale_ref,	arginfo_action_at_a_distance_scale_ref)
	PHP_FE_END
};
/* }}} */

/* {{{ action_at_a_distance_module_entry
 */
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
/* }}} */

#ifdef COMPILE_DL_TEST
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(action_at_a_distance)
#endif
