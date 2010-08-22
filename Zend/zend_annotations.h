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

#ifndef ZEND_ANNOTATIONS_H
#define ZEND_ANNOTATIONS_H

BEGIN_EXTERN_C()

#define ZEND_ANNOTATION_ZVAL 1
#define ZEND_ANNOTATION_ANNO 2
#define ZEND_ANNOTATION_HASH 3

typedef struct _annotation_object {
        zend_object std;
} annotation_object_t; 

extern ZEND_API zend_class_entry *zend_ce_annotation;

void zend_annotation_value_dtor(void **ptr);
void zend_annotation_dtor(void **ptr);

void zend_register_annotation_ce(TSRMLS_D);

ZEND_API void zend_create_annotation(zval *res, zend_annotation *annotation TSRMLS_DC);
ZEND_API void zend_create_all_annotations(zval *return_value, HashTable *annotations TSRMLS_DC); 

END_EXTERN_C()

#endif
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
