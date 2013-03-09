# project name, version, email
AC_INIT( [KitchenSink-Cs1], 1.0, [barbara@copperspice.com] )

# location of temp autotools files
# note: space can not exist between ] and  )
AC_CONFIG_AUX_DIR([autotools/build-aux])
AC_CONFIG_MACRO_DIR([autotools/m4]) 

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# name of one source file
AC_CONFIG_SRCDIR([main.cpp])

# not a gnu project
AM_INIT_AUTOMAKE( [foreign] )

# checking build environment
LT_INIT
AC_PROG_INSTALL
AC_PROG_CC_C99
AC_PROG_CC_C_O
AC_PROG_CXX

# set flags for c+11
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext])

# location of .am files that will create Makefiles
AC_CONFIG_FILES( [Makefile bin/Makefile ] )
AC_OUTPUT