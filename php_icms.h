/* $Id$ */

#ifndef PHP_ICMS_H
#define PHP_ICMS_H

extern zend_module_entry icms_module_entry;
#define phpext_icms_ptr &icms_module_entry

#ifdef PHP_WIN32
#define PHP_ICMS_API __declspec(dllexport)
#else
#define PHP_ICMS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(icms);
PHP_MSHUTDOWN_FUNCTION(icms);
PHP_RINIT_FUNCTION(icms);
PHP_RSHUTDOWN_FUNCTION(icms);
PHP_MINFO_FUNCTION(icms);

PHP_FUNCTION(icms_tpl_find_begin);
PHP_FUNCTION(icms_tpl_find_end);
PHP_FUNCTION(icms_tpl_find_char);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(icms)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(icms)
*/

/* In every utility function you add that needs to use variables 
   in php_icms_globals, call TSRM_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as ICMS_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define ICMS_G(v) TSRMG(icms_globals_id, zend_icms_globals *, v)
#else
#define ICMS_G(v) (icms_globals.v)
#endif

#endif	/* PHP_ICMS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
