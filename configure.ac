#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([morgenlichtctl], [0.1.1], [bennett@piater.name])
AC_CONFIG_SRCDIR([src/morgenlichtctl.c])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([argtable2], [arg_nullcheck], [], AC_MSG_ERROR([Please install the 'argtable' library and headers.]))

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
