dnl $Id$
dnl config.m4 for extension icms
PHP_ARG_ENABLE(icms, whether to enable icms support,
[  --enable-icms           Enable icms support])

if test "$PHP_ICMS" != "no"; then
  PHP_NEW_EXTENSION(icms, icms.c, $ext_shared)
fi
