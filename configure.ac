AC_INIT([USB_BPG_200 C++], [0.1], [alessandro@razeto.it], [USB_BPG_200], [http://www.deditec.de/en/entwicklungstools/prod/bit-pattern-generator-36.html])
AC_PREREQ([2.59])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign])
LT_INIT
PKG_CHECK_MODULES([DEPS], [libftdi >= 0.20])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
AC_PROG_CXX
AC_ARG_ENABLE([orig], AS_HELP_STRING([--enable-orig], [Enable bindings to original delib]), enable_orig="$enableval")
AM_CONDITIONAL(DELIB_ORIG, [test "x$enable_orig" = "xyes"])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
