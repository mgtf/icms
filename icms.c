/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_icms.h"

/* If you declare any globals in php_icms.h uncomment this: ZEND_DECLARE_MODULE_GLOBALS(icms) */

/* True global resources - no need for thread safety here */
static int le_icms;

function_entry icms_functions[] = {
  PHP_FE(icms_tpl_find_end,	NULL)
  PHP_FE(icms_tpl_find_char,	NULL)
  PHP_FE(icms_tpl_find_begin,	NULL)
  {NULL, NULL, NULL}
};

zend_module_entry icms_module_entry = {
  STANDARD_MODULE_HEADER,
  "icms",
  icms_functions,
  PHP_MINIT(icms),
  PHP_MSHUTDOWN(icms),
  PHP_RINIT(icms),	/* Replace with NULL if there's nothing to do at request start */
  PHP_RSHUTDOWN(icms),	/* Replace with NULL if there's nothing to do at request end */
  PHP_MINFO(icms),
  "0.1",
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ICMS
ZEND_GET_MODULE(icms)
#endif

	/* {{{ PHP_INI
	*/
	/* Remove comments and fill if you need to have entries in php.ini
	   PHP_INI_BEGIN()
	   STD_PHP_INI_ENTRY("icms.global_value",      "42", PHP_INI_ALL, OnUpdateInt, global_value, zend_icms_globals, icms_globals)
	   STD_PHP_INI_ENTRY("icms.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_icms_globals, icms_globals)
	   PHP_INI_END()
	   */
	/* }}} */

	/* {{{ php_icms_init_globals
	*/
	/* Uncomment this function if you have INI entries
	   static void php_icms_init_globals(zend_icms_globals *icms_globals)
	   {
	   icms_globals->global_value = 0;
	   icms_globals->global_string = NULL;
	   }
	   */
	/* }}} */

	/* {{{ PHP_MINIT_FUNCTION
	*/
PHP_MINIT_FUNCTION(icms)
{
  /* If you have INI entries, uncomment these lines 
	 ZEND_INIT_MODULE_GLOBALS(icms, php_icms_init_globals, NULL);
	 REGISTER_INI_ENTRIES();
	 */
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(icms)
{
  /* uncomment this line if you have INI entries
	 UNREGISTER_INI_ENTRIES();
	 */
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(icms)
{
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(icms)
{
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(icms)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "iota content management system support", "enabled");
  php_info_print_table_end();
  /* Remove comments if you have entries in php.ini DISPLAY_INI_ENTRIES(); */
}
/* }}} */

PHP_FUNCTION(icms_tpl_find_begin)
{
  char *string;
  long string_len;
  int i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &string, &string_len) == FAILURE) {
    return;
  }
  if(string_len < 1)
    RETURN_FALSE;
  if(string[0] == '{')
    RETURN_LONG(0);
  for(i = 1; i < string_len; i++) {
    if((string[i] == '{') && (string[i - 1] != '\\'))
      RETURN_LONG(i);
  }
  RETURN_FALSE;
}

PHP_FUNCTION(icms_tpl_find_end)
{
  char *string;
  long string_len, begin, i;
  long nb = 1;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &string, &string_len, &begin) == FAILURE) {
    return;
  }
  for(i = begin + 1; nb && (string_len > i); i++) {
    if((string[i] == '{') && (string[i - 1] != '\\'))
      nb++;
    if((string[i] == '}') && (string[i - 1] != '\\'))
      nb--;
  }
  if(nb)
    RETURN_FALSE;
  RETURN_LONG(i);
}

PHP_FUNCTION(icms_tpl_find_char)
{
  char *string;
  char *mychar;
  long string_len, mychar_len, i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &string, &string_len, &mychar, &mychar_len) == FAILURE) {
    return;
  }
  if(mychar_len > 1) {
    zend_error(E_WARNING, "Wrong value for parameter 2 in call to %s()", get_active_function_name(TSRMLS_C));
    return;
  }
  for(i = 1; i < string_len; i++) {
    if((string[i] == mychar[0]) && (string[i - 1] != '\\'))
      RETURN_LONG(i);
  }
  RETURN_FALSE;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
