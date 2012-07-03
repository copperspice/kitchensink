# project name, version, email
AC_INIT( [KitchenSink-Cs1], 1.0, [barbara@copperspice.com] )

# location of temp autotools files
# note: space can not exist between ] and  )
AC_CONFIG_AUX_DIR([autotools/build-aux])
AC_CONFIG_MACRO_DIR([autotools/m4]) 

# name of one source of your files
AC_CONFIG_SRCDIR( [main.cpp] )

# not a gnu project
AM_INIT_AUTOMAKE( [foreign] )

# checking build environment
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_CC_C99
AC_PROG_CXX
AC_PROG_CC_C_O

# value of 'bin' is the folder were the build will be located
AC_CONFIG_FILES( [bin/Makefile] )
AC_OUTPUT