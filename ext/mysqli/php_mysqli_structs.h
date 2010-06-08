/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Georg Richter <georg@php.net>                               |
  |          Andrey Hristov <andrey@php.net>                             |
  |          Ulf Wendel <uw@php.net>                                     |
  +----------------------------------------------------------------------+

  $Id: php_mysqli_structs.h 299782 2010-05-26 13:30:19Z andrey $ 
*/

#ifndef PHP_MYSQLI_STRUCTS_H
#define PHP_MYSQLI_STRUCTS_H

/* A little hack to prevent build break, when mysql is used together with
 * c-client, which also defines LIST.
 */
#ifdef LIST
#undef LIST
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef MYSQLI_USE_MYSQLND
#include "ext/mysqlnd/mysqlnd.h"
#include "mysqli_mysqlnd.h"
#else
#include <mysql.h>
#include <errmsg.h>
#include "mysqli_libmysql.h"
#endif

#ifdef PHP_MYSQL_UNIX_SOCK_ADDR
#ifdef MYSQL_UNIX_ADDR
#undef MYSQL_UNIX_ADDR
#endif
#define MYSQL_UNIX_ADDR PHP_MYSQL_UNIX_SOCK_ADDR
#endif

#include "php_mysqli.h"

/* character set support */
#if defined(MYSQLND_VERSION_ID) || MYSQL_VERSION_ID > 50009
#define HAVE_MYSQLI_GET_CHARSET
#endif

#if defined(MYSQLND_VERSION_ID) || (MYSQL_VERSION_ID > 40112 && MYSQL_VERSION_ID < 50000) || MYSQL_VERSION_ID > 50005
#define HAVE_MYSQLI_SET_CHARSET
#endif

#define MYSQLI_VERSION_ID		101009

enum mysqli_status {
	MYSQLI_STATUS_UNKNOWN=0,
	MYSQLI_STATUS_CLEARED,
	MYSQLI_STATUS_INITIALIZED,
	MYSQLI_STATUS_VALID
};

typedef struct {
	char		*val;
	ulong		buflen;
	ulong		output_len;
	ulong		type;
} VAR_BUFFER;

typedef struct {
	unsigned int	var_cnt;
	VAR_BUFFER		*buf;
	zval			**vars;
	char			*is_null;
} BIND_BUFFER;

typedef struct {
	MYSQL_STMT	*stmt;
	BIND_BUFFER	param;
	BIND_BUFFER	result;
	char		*query;
} MY_STMT;

typedef struct {
	MYSQL			*mysql;
	char			*hash_key;
	zval			*li_read;
	php_stream		*li_stream;
	unsigned int 	multi_query;
	zend_bool		persistent;
#if defined(MYSQLI_USE_MYSQLND)
	int				async_result_fetch_type;				
#endif
} MY_MYSQL;

typedef struct {
	int			mode;
	int			socket;
	FILE		*fp;
} PROFILER;

typedef struct {
	void				*ptr;		/* resource: (mysql, result, stmt)   */
	void				*info;		/* additional buffer				 */
	enum mysqli_status	status;		/* object status */
} MYSQLI_RESOURCE;

typedef struct _mysqli_object {
	zend_object 		zo;
	void 				*ptr;
	HashTable 			*prop_handler;
} mysqli_object; /* extends zend_object */

typedef struct st_mysqli_warning MYSQLI_WARNING;

struct st_mysqli_warning {
	zval	reason;
	zval	sqlstate;
	int		errorno;
   	MYSQLI_WARNING	*next;
};

typedef struct _mysqli_property_entry {
	const char *pname;
	size_t pname_length;
	int (*r_func)(mysqli_object *obj, zval **retval TSRMLS_DC);
	int (*w_func)(mysqli_object *obj, zval *value TSRMLS_DC);
} mysqli_property_entry;

#if !defined(MYSQLI_USE_MYSQLND)
typedef struct {
	char	error_msg[LOCAL_INFILE_ERROR_LEN];
  	void	*userdata;
} mysqli_local_infile;
#endif

typedef struct {
	zend_ptr_stack free_links;
} mysqli_plist_entry;

#ifdef PHP_WIN32
#define PHP_MYSQLI_API __declspec(dllexport)
#define MYSQLI_LLU_SPEC "%I64u"
#define MYSQLI_LL_SPEC "%I64d"
#define L64(x) x##i64
typedef __int64 my_longlong;
#else
# if defined(__GNUC__) && __GNUC__ >= 4
#  define PHP_MYSQLI_API __attribute__ ((visibility("default")))
# else
#  define PHP_MYSQLI_API
# endif
/* we need this for PRIu64 and PRId64 */
#include <inttypes.h>
#define MYSQLI_LLU_SPEC "%" PRIu64
#define MYSQLI_LL_SPEC "%" PRId64
#define L64(x) x##LL
typedef int64_t my_longlong;
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_MYSQLI_EXPORT(__type) PHP_MYSQLI_API __type

extern const zend_function_entry mysqli_functions[];
extern const zend_function_entry mysqli_link_methods[];
extern const zend_function_entry mysqli_stmt_methods[];
extern const zend_function_entry mysqli_result_methods[];
extern const zend_function_entry mysqli_driver_methods[];
extern const zend_function_entry mysqli_warning_methods[];
extern const zend_function_entry mysqli_exception_methods[];

extern const mysqli_property_entry mysqli_link_property_entries[];
extern const mysqli_property_entry mysqli_result_property_entries[];
extern const mysqli_property_entry mysqli_stmt_property_entries[];
extern const mysqli_property_entry mysqli_driver_property_entries[];
extern const mysqli_property_entry mysqli_warning_property_entries[];

extern zend_property_info mysqli_link_property_info_entries[];
extern zend_property_info mysqli_result_property_info_entries[];
extern zend_property_info mysqli_stmt_property_info_entries[];
extern zend_property_info mysqli_driver_property_info_entries[];
extern zend_property_info mysqli_warning_property_info_entries[];

extern void php_mysqli_fetch_into_hash(INTERNAL_FUNCTION_PARAMETERS, int override_flag, int into_object);
extern void php_clear_stmt_bind(MY_STMT *stmt TSRMLS_DC);
extern void php_clear_mysql(MY_MYSQL *);
extern MYSQLI_WARNING *php_get_warnings(MYSQL *mysql TSRMLS_DC);
extern void php_clear_warnings(MYSQLI_WARNING *w);
extern void php_free_stmt_bind_buffer(BIND_BUFFER bbuf, int type);
extern void php_mysqli_report_error(const char *sqlstate, int errorno, const char *error TSRMLS_DC);
extern void php_mysqli_report_index(const char *query, unsigned int status TSRMLS_DC);
extern void php_set_local_infile_handler_default(MY_MYSQL *);
extern void php_mysqli_throw_sql_exception(char *sqlstate, int errorno TSRMLS_DC, char *format, ...);
extern zend_class_entry *mysqli_link_class_entry;
extern zend_class_entry *mysqli_stmt_class_entry;
extern zend_class_entry *mysqli_result_class_entry;
extern zend_class_entry *mysqli_driver_class_entry;
extern zend_class_entry *mysqli_warning_class_entry;
extern zend_class_entry *mysqli_exception_class_entry;
extern int php_le_pmysqli(void);
extern void php_mysqli_dtor_p_elements(void *data);

extern void php_mysqli_close(MY_MYSQL * mysql, int close_type, int resource_status TSRMLS_DC);

extern zend_object_iterator_funcs php_mysqli_result_iterator_funcs;
extern zend_object_iterator *php_mysqli_result_get_iterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC);

extern void php_mysqli_fetch_into_hash_aux(zval *return_value, MYSQL_RES * result, long fetchtype TSRMLS_DC);

#ifdef HAVE_SPL
extern PHPAPI zend_class_entry *spl_ce_RuntimeException;
#endif

PHP_MYSQLI_EXPORT(zend_object_value) mysqli_objects_new(zend_class_entry * TSRMLS_DC);

#define MYSQLI_DISABLE_MQ if (mysql->multi_query) { \
	mysql_set_server_option(mysql->mysql, MYSQL_OPTION_MULTI_STATEMENTS_OFF); \
	mysql->multi_query = 0; \
} 

#define MYSQLI_ENABLE_MQ if (!mysql->multi_query) { \
	mysql_set_server_option(mysql->mysql, MYSQL_OPTION_MULTI_STATEMENTS_ON); \
	mysql->multi_query = 1; \
} 

#define REGISTER_MYSQLI_CLASS_ENTRY(name, mysqli_entry, class_functions) { \
	zend_class_entry ce; \
	INIT_CLASS_ENTRY(ce, name,class_functions); \
	ce.create_object = mysqli_objects_new; \
	mysqli_entry = zend_register_internal_class(&ce TSRMLS_CC); \
} \

#define MYSQLI_REGISTER_RESOURCE_EX(__ptr, __zval)  \
	((mysqli_object *) zend_object_store_get_object(__zval TSRMLS_CC))->ptr = __ptr;

#define MYSQLI_RETURN_RESOURCE(__ptr, __ce) \
	Z_TYPE_P(return_value) = IS_OBJECT; \
	(return_value)->value.obj = mysqli_objects_new(__ce TSRMLS_CC); \
	MYSQLI_REGISTER_RESOURCE_EX(__ptr, return_value)

#define MYSQLI_REGISTER_RESOURCE(__ptr, __ce) \
{\
	zval *object = getThis();\
	if (!object || !instanceof_function(Z_OBJCE_P(object), mysqli_link_class_entry TSRMLS_CC)) {\
		object = return_value;\
		Z_TYPE_P(object) = IS_OBJECT;\
		(object)->value.obj = mysqli_objects_new(__ce TSRMLS_CC);\
	}\
	MYSQLI_REGISTER_RESOURCE_EX(__ptr, object)\
}

#define MYSQLI_FETCH_RESOURCE(__ptr, __type, __id, __name, __check) \
{ \
	MYSQLI_RESOURCE *my_res; \
	mysqli_object *intern = (mysqli_object *)zend_object_store_get_object(*(__id) TSRMLS_CC);\
	if (!(my_res = (MYSQLI_RESOURCE *)intern->ptr)) {\
  		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Couldn't fetch %s", intern->zo.ce->name);\
  		RETURN_NULL();\
  	}\
	__ptr = (__type)my_res->ptr; \
	if (__check && my_res->status < __check) { \
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid object or resource %s\n", intern->zo.ce->name); \
		RETURN_NULL();\
	}\
}

#define MYSQLI_FETCH_RESOURCE_BY_OBJ(__ptr, __type, __obj, __name, __check) \
{ \
	MYSQLI_RESOURCE *my_res; \
	if (!(my_res = (MYSQLI_RESOURCE *)(__obj->ptr))) {\
  		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Couldn't fetch %s", intern->zo.ce->name);\
  		return;\
  	}\
	__ptr = (__type)my_res->ptr; \
	if (__check && my_res->status < __check) { \
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid object or resource %s\n", intern->zo.ce->name); \
		return;\
	}\
}


#define MYSQLI_FETCH_RESOURCE_CONN(__ptr, __id, __check) \
{ \
	MYSQLI_FETCH_RESOURCE((__ptr), MY_MYSQL *, (__id), "mysqli_link", (__check)); \
	if (!(__ptr)->mysql) { \
		mysqli_object *intern = (mysqli_object *)zend_object_store_get_object(*(__id) TSRMLS_CC);\
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid object or resource %s\n", intern->zo.ce->name); \
		RETURN_NULL();\
	} \
}

#define MYSQLI_FETCH_RESOURCE_STMT(__ptr, __id, __check) \
{ \
	MYSQLI_FETCH_RESOURCE((__ptr), MY_STMT *, (__id), "mysqli_stmt", (__check)); \
	if (!(__ptr)->stmt) { \
		mysqli_object *intern = (mysqli_object *)zend_object_store_get_object(*(__id) TSRMLS_CC);\
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid object or resource %s\n", intern->zo.ce->name); \
		RETURN_NULL();\
	} \
}


#define MYSQLI_SET_STATUS(__id, __value) \
{ \
	mysqli_object *intern = (mysqli_object *)zend_object_store_get_object(*(__id) TSRMLS_CC);\
	((MYSQLI_RESOURCE *)intern->ptr)->status = __value; \
} \

#define MYSQLI_CLEAR_RESOURCE(__id) \
{ \
	mysqli_object *intern = (mysqli_object *)zend_object_store_get_object(*(__id) TSRMLS_CC);\
	efree(intern->ptr); \
	intern->ptr = NULL; \
}

#define MYSQLI_RETURN_LONG_LONG(__val) \
{ \
	if ((__val) < LONG_MAX) {		\
		RETURN_LONG((long) (__val));		\
	} else {				\
		char *ret;			\
		/* always used with my_ulonglong -> %llu */ \
		int l = spprintf(&ret, 0, MYSQLI_LLU_SPEC, (__val));	\
		RETURN_STRINGL(ret, l, 0);		\
	}					\
}

#define MYSQLI_STORE_RESULT 0
#define MYSQLI_USE_RESULT 	1
#ifdef MYSQLI_USE_MYSQLND
#define MYSQLI_ASYNC	 	8
#else
/* libmysql */
#define MYSQLI_ASYNC	 	0
#endif

/* for mysqli_fetch_assoc */
#define MYSQLI_ASSOC	1
#define MYSQLI_NUM		2
#define MYSQLI_BOTH		3

/* fetch types */
#define FETCH_SIMPLE		1
#define FETCH_RESULT		2

/*** REPORT MODES ***/
#define MYSQLI_REPORT_OFF           0
#define MYSQLI_REPORT_ERROR			1
#define MYSQLI_REPORT_STRICT		2
#define MYSQLI_REPORT_INDEX			4
#define MYSQLI_REPORT_CLOSE			8	
#define MYSQLI_REPORT_ALL		  255

#define MYSQLI_REPORT_MYSQL_ERROR(mysql) \
if ((MyG(report_mode) & MYSQLI_REPORT_ERROR) && mysql_errno(mysql)) { \
	php_mysqli_report_error(mysql_sqlstate(mysql), mysql_errno(mysql), mysql_error(mysql) TSRMLS_CC); \
}

#define MYSQLI_REPORT_STMT_ERROR(stmt) \
if ((MyG(report_mode) & MYSQLI_REPORT_ERROR) && mysql_stmt_errno(stmt)) { \
	php_mysqli_report_error(mysql_stmt_sqlstate(stmt), mysql_stmt_errno(stmt), mysql_stmt_error(stmt) TSRMLS_CC); \
}

void mysqli_common_connect(INTERNAL_FUNCTION_PARAMETERS, zend_bool is_real_connect, zend_bool in_ctor);

void php_mysqli_init(INTERNAL_FUNCTION_PARAMETERS);


ZEND_BEGIN_MODULE_GLOBALS(mysqli)
	long			default_link;
	long			num_links;
	long			max_links;
	long 			num_active_persistent;
	long 			num_inactive_persistent;
	long			max_persistent;
	long			allow_persistent;
	unsigned long	default_port;
	char			*default_host;
	char			*default_user;
	char			*default_socket;
	char			*default_pw;
	long			reconnect;
	long			allow_local_infile;
	long			strict;
	long			error_no;
	char			*error_msg;
	long			report_mode;
	HashTable		*report_ht;
	unsigned long	multi_query;
	unsigned long	embedded;
ZEND_END_MODULE_GLOBALS(mysqli)


#ifdef ZTS
#define MyG(v) TSRMG(mysqli_globals_id, zend_mysqli_globals *, v)
#else
#define MyG(v) (mysqli_globals.v)
#endif

#define my_estrdup(x) (x) ? estrdup(x) : NULL
#define my_efree(x) if (x) efree(x)

ZEND_EXTERN_MODULE_GLOBALS(mysqli)


PHP_MINIT_FUNCTION(mysqli);
PHP_MSHUTDOWN_FUNCTION(mysqli);
PHP_RINIT_FUNCTION(mysqli);
PHP_RSHUTDOWN_FUNCTION(mysqli);
PHP_MINFO_FUNCTION(mysqli);

PHP_FUNCTION(mysqli);
PHP_FUNCTION(mysqli_affected_rows);
PHP_FUNCTION(mysqli_autocommit);
PHP_FUNCTION(mysqli_change_user);
PHP_FUNCTION(mysqli_character_set_name);
PHP_FUNCTION(mysqli_set_charset);
PHP_FUNCTION(mysqli_close);
PHP_FUNCTION(mysqli_commit);
PHP_FUNCTION(mysqli_connect);
PHP_FUNCTION(mysqli_connect_errno);
PHP_FUNCTION(mysqli_connect_error);
PHP_FUNCTION(mysqli_data_seek);
PHP_FUNCTION(mysqli_debug);
PHP_FUNCTION(mysqli_dump_debug_info);
PHP_FUNCTION(mysqli_errno);
PHP_FUNCTION(mysqli_error);
PHP_FUNCTION(mysqli_fetch_all);
PHP_FUNCTION(mysqli_fetch_array);
PHP_FUNCTION(mysqli_fetch_assoc);
PHP_FUNCTION(mysqli_fetch_object);
PHP_FUNCTION(mysqli_fetch_field);
PHP_FUNCTION(mysqli_fetch_fields);
PHP_FUNCTION(mysqli_fetch_field_direct);
PHP_FUNCTION(mysqli_fetch_lengths);
PHP_FUNCTION(mysqli_fetch_row);
PHP_FUNCTION(mysqli_field_count);
PHP_FUNCTION(mysqli_field_seek);
PHP_FUNCTION(mysqli_field_tell);
PHP_FUNCTION(mysqli_free_result);
PHP_FUNCTION(mysqli_get_client_stats);
PHP_FUNCTION(mysqli_get_connection_stats);
PHP_FUNCTION(mysqli_get_charset);
PHP_FUNCTION(mysqli_get_client_info);
PHP_FUNCTION(mysqli_get_client_version);
PHP_FUNCTION(mysqli_get_host_info);
PHP_FUNCTION(mysqli_get_proto_info);
PHP_FUNCTION(mysqli_get_server_info);
PHP_FUNCTION(mysqli_get_server_version);
PHP_FUNCTION(mysqli_get_warnings);
PHP_FUNCTION(mysqli_info);
PHP_FUNCTION(mysqli_insert_id);
PHP_FUNCTION(mysqli_init);
PHP_FUNCTION(mysqli_kill);
PHP_FUNCTION(mysqli_link_construct);
PHP_FUNCTION(mysqli_set_local_infile_default);
PHP_FUNCTION(mysqli_set_local_infile_handler);
PHP_FUNCTION(mysqli_more_results);
PHP_FUNCTION(mysqli_multi_query);
PHP_FUNCTION(mysqli_next_result);
PHP_FUNCTION(mysqli_num_fields);
PHP_FUNCTION(mysqli_num_rows);
PHP_FUNCTION(mysqli_options);
PHP_FUNCTION(mysqli_ping);
PHP_FUNCTION(mysqli_poll);
PHP_FUNCTION(mysqli_prepare);
PHP_FUNCTION(mysqli_query);
PHP_FUNCTION(mysqli_stmt_result_metadata);
PHP_FUNCTION(mysqli_report);
PHP_FUNCTION(mysqli_read_query_result);
PHP_FUNCTION(mysqli_real_connect);
PHP_FUNCTION(mysqli_real_query);
PHP_FUNCTION(mysqli_real_escape_string);
PHP_FUNCTION(mysqli_reap_async_query);
PHP_FUNCTION(mysqli_rollback);
PHP_FUNCTION(mysqli_row_seek);
PHP_FUNCTION(mysqli_select_db);
PHP_FUNCTION(mysqli_stmt_attr_get);
PHP_FUNCTION(mysqli_stmt_attr_set);
PHP_FUNCTION(mysqli_stmt_bind_param);
PHP_FUNCTION(mysqli_stmt_bind_result);
PHP_FUNCTION(mysqli_stmt_execute);
PHP_FUNCTION(mysqli_stmt_field_count);
PHP_FUNCTION(mysqli_stmt_init);
PHP_FUNCTION(mysqli_stmt_prepare);
PHP_FUNCTION(mysqli_stmt_fetch);
PHP_FUNCTION(mysqli_stmt_param_count);
PHP_FUNCTION(mysqli_stmt_send_long_data);
PHP_FUNCTION(mysqli_embedded_server_end);
PHP_FUNCTION(mysqli_embedded_server_start);
PHP_FUNCTION(mysqli_sqlstate);
PHP_FUNCTION(mysqli_ssl_set);
PHP_FUNCTION(mysqli_stat);
PHP_FUNCTION(mysqli_refresh);
PHP_FUNCTION(mysqli_stmt_affected_rows);
PHP_FUNCTION(mysqli_stmt_close);
PHP_FUNCTION(mysqli_stmt_data_seek);
PHP_FUNCTION(mysqli_stmt_errno);
PHP_FUNCTION(mysqli_stmt_error);
PHP_FUNCTION(mysqli_stmt_free_result);
PHP_FUNCTION(mysqli_stmt_get_result);
PHP_FUNCTION(mysqli_stmt_get_warnings);
PHP_FUNCTION(mysqli_stmt_reset);
PHP_FUNCTION(mysqli_stmt_insert_id);
PHP_FUNCTION(mysqli_stmt_more_results);
PHP_FUNCTION(mysqli_stmt_next_result);
PHP_FUNCTION(mysqli_stmt_num_rows);
PHP_FUNCTION(mysqli_stmt_sqlstate);
PHP_FUNCTION(mysqli_stmt_store_result);
PHP_FUNCTION(mysqli_store_result);
PHP_FUNCTION(mysqli_thread_id);
PHP_FUNCTION(mysqli_thread_safe);
PHP_FUNCTION(mysqli_use_result);
PHP_FUNCTION(mysqli_warning_count);

PHP_FUNCTION(mysqli_stmt_construct);
PHP_FUNCTION(mysqli_result_construct);
PHP_FUNCTION(mysqli_driver_construct);
PHP_METHOD(mysqli_warning,__construct);

#endif	/* PHP_MYSQLI_STRUCTS.H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
