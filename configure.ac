#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([morgenlichtctl], [0.1.2], [bennett@piater.name])
AC_CONFIG_SRCDIR([src/morgenlichtctl.c])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([argtable2], [arg_nullcheck], [], AC_MSG_ERROR([Please install the 'argtable' library and headers.]))
AC_CHECK_LIB([SDL2_net], [SDLNet_Init], [], AC_MSG_ERROR([Please install the 'sdl2_net' library and headers.]))
SDL_VERSION=2.0.4
AM_PATH_SDL2($SDL_VERSION, :, AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

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
