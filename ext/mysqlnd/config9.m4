dnl
dnl $Id: config9.m4 298023 2010-04-15 11:01:30Z andrey $
dnl config.m4 for mysqlnd driver


PHP_ARG_ENABLE(disable_mysqlnd_compression_support, whether to disable compressed protocol support in mysqlnd,
[  --disable-mysqlnd-compression-support
                            Enable support for the MySQL compressed protocol in mysqlnd], yes)

if test -z "$PHP_ZLIB_DIR"; then
  PHP_ARG_WITH(zlib-dir, for the location of libz,
  [  --with-zlib-dir[=DIR]       mysqlnd: Set the path to libz install prefix], no, no)
fi

dnl If some extension uses mysqlnd it will get compiled in PHP core
if test "$PHP_MYSQLND_ENABLED" = "yes"; then
  mysqlnd_sources="mysqlnd.c mysqlnd_charset.c mysqlnd_wireprotocol.c \
                   mysqlnd_ps.c mysqlnd_loaddata.c mysqlnd_net.c \
                   mysqlnd_ps_codec.c mysqlnd_statistics.c \
				   mysqlnd_result.c mysqlnd_result_meta.c mysqlnd_debug.c\
				   mysqlnd_block_alloc.c php_mysqlnd.c"

  PHP_NEW_EXTENSION(mysqlnd, $mysqlnd_sources, no)
  PHP_ADD_BUILD_DIR([ext/mysqlnd], 1)
  PHP_INSTALL_HEADERS([ext/mysqlnd/])

  dnl Windows uses config.w32 thus this code is safe for now

  if test "$PHP_MYSQLND_COMPRESSION_SUPPORT" != "no"; then
    AC_DEFINE([MYSQLND_COMPRESSION_ENABLED], 1, [Enable compressed protocol support])
    if test "$PHP_ZLIB_DIR" != "no"; then
      PHP_ADD_LIBRARY_WITH_PATH(z, $PHP_ZLIB_DIR, MYSQLND_SHARED_LIBADD)
      MYSQLND_LIBS="$MYSQLND_LIBS -L$PHP_ZLIB_DIR/$PHP_LIBDIR -lz"
    else
      PHP_ADD_LIBRARY(z,, MYSQLND_SHARED_LIBADD)
      MYSQLND_LIBS="$MYSQLND_LIBS -lz"
    fi
  fi
  AC_DEFINE([MYSQLND_SSL_SUPPORTED], 1, [Enable SSL support])
fi

if test "$PHP_MYSQLND_ENABLED" = "yes" || test "$PHP_MYSQLI" != "no"; then
  PHP_ADD_BUILD_DIR([ext/mysqlnd], 1)

  dnl This creates a file so it has to be after above macros
  PHP_CHECK_TYPES([int8 uint8 int16 uint16 int32 uint32 uchar ulong int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t], [
    ext/mysqlnd/php_mysqlnd_config.h
  ],[
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
  ])
fi
