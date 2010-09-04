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
   | Author: Pierrick Charron <pierrick@php.net>                          |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "zend.h"
#include "zend_API.h"
#include "zend_constants.h"
#include "zend_annotations.h"
#include "zend_exceptions.h"

ZEND_API zend_class_entry *(*zend_get_annotation_ce)(const char *name, const uint nameLength TSRMLS_DC);

void zend_create_annotation_parameters(zval *params, HashTable *ht TSRMLS_DC) /* {{{ */
{
	zend_annotation_value **value_ref_ref, *value_ref;
	zval *val;
	int constant_index;

	char *string_key;
	uint str_key_len;
	ulong num_key;

	zval const_value;
	char *colon;

	array_init(params);

	if (ht) {
		zend_hash_internal_pointer_reset(ht);
		while (zend_hash_get_current_data(ht, (void **) &value_ref_ref) == SUCCESS) {
			value_ref = *value_ref_ref;

			if (value_ref->type & IS_CONSTANT_INDEX) {
				value_ref->type &= ~IS_CONSTANT_INDEX;
				constant_index = 1;
			} else {
				constant_index = 0;
			}

			switch(value_ref->type) {
				case ZEND_ANNOTATION_ZVAL:
					if ((Z_TYPE_P(value_ref->value.zval) & IS_CONSTANT_TYPE_MASK) == IS_CONSTANT ||
							Z_TYPE_P(value_ref->value.zval)==IS_CONSTANT_ARRAY) {
						char *str = Z_STRVAL_P(value_ref->value.zval);
						zval_update_constant(&value_ref->value.zval, 0 TSRMLS_CC);
						efree(str);
					} 
					val = value_ref->value.zval;
					Z_ADDREF_P(val);
					break;
				case ZEND_ANNOTATION_HASH:
					MAKE_STD_ZVAL(val);
					zend_create_annotation_parameters(val, value_ref->value.ht TSRMLS_CC);
					break;
				case ZEND_ANNOTATION_ANNO:
					MAKE_STD_ZVAL(val);
					zend_create_annotation(val, value_ref->value.annotation, NULL TSRMLS_CC);
					break;
			}

			if (constant_index) {
				value_ref->type |= IS_CONSTANT_INDEX;
			}

			switch (zend_hash_get_current_key_ex(ht, &string_key, &str_key_len, &num_key, 0, NULL)) {
				case HASH_KEY_IS_STRING:
					if (constant_index) {
						if (!zend_get_constant_ex(string_key, str_key_len - 3, &const_value, NULL, string_key[str_key_len - 2] TSRMLS_CC)) {
							char *actual, *save = string_key;
							if ((colon = zend_memrchr(string_key, ':', str_key_len - 3))) {
								zend_error(E_ERROR, "Undefined class constant '%s'", string_key);
								str_key_len -= ((colon - string_key) + 1);
								string_key = colon;
							} else {
								if (string_key[str_key_len - 2] & IS_CONSTANT_UNQUALIFIED) {
									if ((actual = (char *)zend_memrchr(string_key, '\\', str_key_len - 3))) {
										actual++;
										str_key_len -= (actual - string_key);
										string_key = actual;
									}
								}
								if (string_key[0] == '\\') {
									++string_key;
									--str_key_len;
								}
								if (save[0] == '\\') {
									++save;
								}
								if ((string_key[str_key_len - 2] & IS_CONSTANT_UNQUALIFIED) == 0) {
									zend_error(E_ERROR, "Undefined constant '%s'", save);
								}
								zend_error(E_NOTICE, "Use of undefined constant %s - assumed '%s'", string_key, string_key);
							}
							ZVAL_STRINGL(&const_value, string_key, str_key_len-3, 1);
						}

						switch (Z_TYPE(const_value)) {
							case IS_STRING:
								zend_symtable_update(Z_ARRVAL_P(params), Z_STRVAL(const_value), Z_STRLEN(const_value) + 1, &val, sizeof(val), NULL);
								break;
							case IS_BOOL:
							case IS_LONG:
								zend_hash_index_update(Z_ARRVAL_P(params), Z_LVAL(const_value), &val, sizeof(val), NULL);
								break;
							case IS_DOUBLE:
								zend_hash_index_update(Z_ARRVAL_P(params), zend_dval_to_lval(Z_DVAL(const_value)), &val, sizeof(val), NULL);
								break;
							case IS_NULL:
								zend_symtable_update(Z_ARRVAL_P(params), "", 1, &val, sizeof(val), NULL);
								break;
						}
						zval_dtor(&const_value);
					} else {
						zend_symtable_update(Z_ARRVAL_P(params), string_key, str_key_len, &val, sizeof(val), NULL);
					}
					break;
				case HASH_KEY_IS_LONG:
					zend_hash_index_update(Z_ARRVAL_P(params), num_key, &val, sizeof(val), NULL);
					break;
			}
			zend_hash_move_forward(ht);
		}
	}
}
/* }}} */

void zend_create_annotation(zval *res, zend_annotation *annotation, zend_class_entry *ce TSRMLS_DC) /* {{{ */
{
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval *retval_ptr;

	if (!annotation->instance) {

		if (ce == NULL) {
			ce = zend_get_annotation_ce(annotation->annotation_name, annotation->aname_len TSRMLS_CC);
		}

		MAKE_STD_ZVAL(annotation->instance);
		object_init_ex(annotation->instance, ce);

		if (ce->constructor) {
			zval *params = NULL;
			MAKE_STD_ZVAL(params);

			zend_create_annotation_parameters(params, annotation->values TSRMLS_CC);

			fci.size = sizeof(fci);
			fci.function_table = &ce->function_table;
			fci.function_name = NULL;
			fci.symbol_table = NULL;

			fci.object_ptr = annotation->instance;
			fci.retval_ptr_ptr = &retval_ptr;

			fci.param_count = 1;
			fci.params = (zval***) safe_emalloc(sizeof(zval*), 1, 0);
			fci.params[0] = &params;

			fcc.initialized = 1;
			fcc.function_handler = ce->constructor;
			fcc.calling_scope = EG(scope);
			fcc.called_scope = Z_OBJCE_P(annotation->instance);
			fcc.object_ptr = annotation->instance;

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

	*res = *annotation->instance;
	zval_copy_ctor(res);
	INIT_PZVAL(res);
}
/* }}} */

void zend_add_declared_annotations(zval *res, HashTable *annotations TSRMLS_DC) /* {{{ */
{
	zend_annotation **annotation_ref_ref, *annotation_ref;
	zval *annotation_zval;

	for (zend_hash_internal_pointer_reset(annotations); zend_hash_get_current_data(annotations, (void **)&annotation_ref_ref) == SUCCESS; zend_hash_move_forward(annotations)) {
		MAKE_STD_ZVAL(annotation_zval);
		annotation_ref = *annotation_ref_ref;
		zend_create_annotation(annotation_zval, annotation_ref, NULL TSRMLS_CC);
		add_assoc_zval_ex(res, annotation_ref->annotation_name, annotation_ref->aname_len +1, annotation_zval);
	}
}
/* }}} */

void zend_add_inherited_annotations(zval *res, HashTable *annotations TSRMLS_DC) /* {{{ */
{
	zend_annotation **annotation_ref_ref, *annotation_ref;
	zend_class_entry *ce = NULL;
	zval *annotation_zval;

	for (zend_hash_internal_pointer_reset(annotations);
			zend_hash_get_current_data(annotations, (void **)&annotation_ref_ref) == SUCCESS; zend_hash_move_forward(annotations)) {

		annotation_ref = *annotation_ref_ref;
		if (zend_symtable_exists(Z_ARRVAL_P(res), annotation_ref->annotation_name, annotation_ref->aname_len+ 1)) {
			continue;
		}

		ce = zend_get_annotation_ce(annotation_ref->annotation_name, annotation_ref->aname_len TSRMLS_CC);

		if (ce->type == ZEND_USER_CLASS && ce->annotations && 
				zend_symtable_exists(ce->annotations, "inherited", sizeof("inherited"))) {
			MAKE_STD_ZVAL(annotation_zval);
			zend_create_annotation(annotation_zval, annotation_ref, ce TSRMLS_CC);
			add_assoc_zval_ex(res, annotation_ref->annotation_name, annotation_ref->aname_len +1, annotation_zval);
		}
	}
}
/* }}} */

int zend_get_inherited_annotation(HashTable *annotations, const char *name, const uint nameLength, zval *res TSRMLS_DC) /* {{{ */
{
	zend_class_entry *annotation_ce;
	zend_annotation **annotation_ref_ref, *annotation_ref;
	if (zend_hash_find(annotations, name, nameLength+1, (void **) &annotation_ref_ref) == SUCCESS) {
		
		annotation_ref = *annotation_ref_ref;

		annotation_ce = zend_get_annotation_ce(annotation_ref->annotation_name, annotation_ref->aname_len TSRMLS_CC);

		if (annotation_ce->type == ZEND_USER_CLASS && annotation_ce->annotations && zend_symtable_exists(annotation_ce->annotations, "inherited", sizeof("inherited"))) {
			if (res != NULL) {
				zend_create_annotation(res, annotation_ref, annotation_ce TSRMLS_CC);
			}
			return SUCCESS;
		}   
	}
	return FAILURE;
}
/* }}} */
