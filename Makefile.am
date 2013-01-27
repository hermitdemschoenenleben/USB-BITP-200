ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(DEPS_CFLAGS) -I@top_srcdir@/delib
AM_CXXFLAGS = -std=c++11

lib_LTLIBRARIES = libdelib-@PACKAGE_VERSION@.la libusb_bpg_200-@PACKAGE_VERSION@.la
libdelib_@PACKAGE_VERSION@_la_SOURCES = delib/delib.cc delib/ftdi_base.cc
libusb_bpg_200_@PACKAGE_VERSION@_la_SOURCES = src/usb_bpg_200.cc

bin_PROGRAMS = usb_bpg_200_demo
usb_bpg_200_demo_SOURCES = src/usb_bpg_200_demo.cc
usb_bpg_200_demo_LDADD = libdelib-@PACKAGE_VERSION@.la libusb_bpg_200-@PACKAGE_VERSION@.la $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh
