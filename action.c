#include "php_action_at_a_distance.h"

// Method Delarations
static const zend_function_entry action_at_a_distance_methods[] = {
    ZEND_FE_END
};

ZEND_BEGIN_ARG_INFO(action_at_a_distance_perform_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

PHP_METHOD(AtADistance, perform)
{
    char * path;
	size_t len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &path, &len) == FAILURE) {
		    return;
	    }
	RETVAL_TRUE;
}