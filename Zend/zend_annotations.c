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
#include "zend_annotations.h"

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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
