/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2010 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        | 
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Pierrick Charron <pierrick@php.net>                         |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "zend.h"
#include "zend_API.h"
#include "php.h"
#include "zend_annotations.h"

#define ZEND_ANNOTATION_PRINT_NAME "Annotation object"

static ZEND_API zend_class_entry *zend_ce_annotation;

void zend_annotation_value_dtor(void **ptr) { /* {{{ */
    zend_annotation_value *value = (zend_annotation_value *) *ptr;
    if (value->type == ZEND_ANNOTATION_ZVAL) {
        zval_dtor(value->value.zval);
        efree(value->value.zval);
    } else if (value->type == ZEND_ANNOTATION_HASH) {
        zend_hash_destroy(value->value.ht);
        efree(value->value.ht);
    } else if (value->type == ZEND_ANNOTATION_ANNO) {
        zend_annotation **a = &value->value.annotation;
        zend_annotation_dtor((void *) a);
    }
    efree(*ptr);
}
/* }}} */

void zend_annotation_dtor(void **ptr) { /* {{{ */
    zend_annotation *a = (zend_annotation *) *ptr;
    efree(a->annotation_name);
    if (a->values) {
        zend_hash_destroy(a->values);
        efree(a->values);
    }
    efree(*ptr);
}
/* }}} */

static void zend_create_annotation_parameters(zval *params, HashTable *ht TSRMLS_DC) /* {{{ */
{
	zend_annotation_value **value_ref_ref, *value_ref;
	zval *val;

	char *string_key;
	uint str_key_len;
	ulong num_key;

	array_init(params);

	zend_hash_internal_pointer_reset(ht);
	while (zend_hash_get_current_data(ht, (void **) &value_ref_ref) == SUCCESS) {
		value_ref = *value_ref_ref;

		switch(value_ref->type) {
			case ZEND_ANNOTATION_ZVAL:
				val = value_ref->value.zval;
				Z_ADDREF_P(val);
				break;
			case ZEND_ANNOTATION_HASH:
				MAKE_STD_ZVAL(val);
				zend_create_annotation_parameters(val, value_ref->value.ht TSRMLS_CC);
				break;
			case ZEND_ANNOTATION_ANNO:
				MAKE_STD_ZVAL(val);
				zend_create_annotation(val, value_ref->value.annotation TSRMLS_CC);
				break;
		}

		switch (zend_hash_get_current_key_ex(ht, &string_key, &str_key_len, &num_key, 0, NULL)) {
			case HASH_KEY_IS_STRING:
				zend_symtable_update(Z_ARRVAL_P(params), string_key, str_key_len, &val, sizeof(val), NULL);
				break;
			case HASH_KEY_IS_LONG:
				zend_hash_index_update(Z_ARRVAL_P(params), num_key, &val, sizeof(val), NULL);
				break;
		}
		zend_hash_move_forward(ht);
	}
}
/* }}} */

ZEND_API void zend_create_annotation(zval *res, zend_annotation *annotation TSRMLS_DC) /* {{{ */
{
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval *retval_ptr;
	zend_class_entry *ce = NULL;

	ce = zend_fetch_class(annotation->annotation_name, annotation->aname_len, ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	if (!ce) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not find class '%s'", annotation->annotation_name);
	}
	
	object_init_ex(res, ce);

	if (ce->constructor) {
		zval *params = NULL;
		MAKE_STD_ZVAL(params);

		zend_create_annotation_parameters(params, annotation->values TSRMLS_CC);

		fci.size = sizeof(fci);
		fci.function_table = &ce->function_table;
		fci.function_name = NULL;
		fci.symbol_table = NULL;

		fci.object_ptr = res;
		fci.retval_ptr_ptr = &retval_ptr;

		// PARAMS
		fci.param_count = 1;
		fci.params = (zval***) safe_emalloc(sizeof(zval*), 1, 0);
		fci.params[0] = &params;

		fcc.initialized = 1;
		fcc.function_handler = ce->constructor;
		fcc.calling_scope = EG(scope);
		fcc.called_scope = Z_OBJCE_P(res);
		fcc.object_ptr = res;

		if (zend_call_function(&fci, &fcc TSRMLS_CC) == FAILURE) {
			zend_throw_exception_ex(zend_exception_get_default(TSRMLS_C), 0 TSRMLS_CC, "Could not execute %s::%s()", ce->name, ce->constructor->common.function_name);
		} else {
			if (retval_ptr) {
				zval_ptr_dtor(&retval_ptr);
			}
		}
		if (fci.params) {
			efree(fci.params);
		}
		zval_ptr_dtor(&params);
	}
}
/* }}} */

ZEND_API void zend_create_all_annotations(zval *res, HashTable *annotations TSRMLS_DC) /* {{{ */
{
	zend_annotation **annotation_ref_ref, *annotation_ref;
	zval *annotation_zval;
	array_init(res);
	
	for (zend_hash_internal_pointer_reset(annotations); zend_hash_get_current_data(annotations, (void **)&annotation_ref_ref) == SUCCESS; zend_hash_move_forward(annotations)) {
		MAKE_STD_ZVAL(annotation_zval);
		annotation_ref = *annotation_ref_ref;
		zend_create_annotation(annotation_zval, annotation_ref TSRMLS_CC);
		add_assoc_zval_ex(res, annotation_ref->annotation_name, annotation_ref->aname_len +1, annotation_zval);
	}
}
/* }}} */

void zend_register_annotation_ce(TSRMLS_D) /* {{{ */
{
}
/* }}} */
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
