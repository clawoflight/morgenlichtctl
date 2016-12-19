#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([morgenlichtctl], [0.1.2], [bennett@piater.name])
AC_CONFIG_SRCDIR([src/morgenlichtctl.c])
AC_CONFIG_AUX_DIR(autotools)
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_CHECK_PROG(PANDOC,pandoc,yes)
if test x"$PANDOC" != x"yes" ; then
    AC_MSG_ERROR([Please install pandoc, which is required for man-page compilation])
fi

# Checks for libraries.
AC_CHECK_LIB([argtable2], [arg_nullcheck], [], AC_MSG_ERROR([Please install the 'argtable' library and headers.]))

AM_CFLAGS="$AM_CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 man/Makefile])
AC_OUTPUT
