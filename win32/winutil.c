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
   | Author:                                                              |
   +----------------------------------------------------------------------+
 */

/* $Id: winutil.c 294724 2010-02-07 20:15:58Z pajoye $ */

#include "php.h"

PHPAPI char *php_win_err(int error)
{
	char *buf = NULL;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |	FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	(LPTSTR)&buf, 0, NULL
	);

	return (buf ? (char *) buf : "");
}

int php_win32_check_trailing_space(const char * path, const int path_len) {
	if (path_len < 1) {
		return 1;
	}
	if (path) {
		if (path[0] == ' ' || path[path_len - 1] == ' ') {
			return 0;
		} else {
			return 1;
		}
	} else {
		return 0;
	}
}
