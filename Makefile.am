AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
AM_CPPFLAGS = $(DEPS_CFLAGS) -I@top_srcdir@/delib
AM_CXXFLAGS = -std=c++11

noinst_LIBRARIES = libdelib.a
libdelib_a_SOURCES = delib/delib.cc delib/ftdi_base.cc

bin_PROGRAMS = usb_bpg_200_demo
usb_bpg_200_demo_SOURCES = src/usb_bpg_200.cc src/usb_bpg_200_demo.cc
usb_bpg_200_demo_LDADD = libdelib.a $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh
