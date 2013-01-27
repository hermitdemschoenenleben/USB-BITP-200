ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(DEPS_CFLAGS) -I@top_srcdir@/delib
AM_CXXFLAGS = -std=c++11

lib_LTLIBRARIES = libusb_bpg_200-@PACKAGE_VERSION@.la libdelib-@PACKAGE_VERSION@.la 
libusb_bpg_200_@PACKAGE_VERSION@_la_SOURCES = src/usb_bpg_200.cc
libdelib_@PACKAGE_VERSION@_la_SOURCES = delib/delib.cc delib/ftdi_base.cc 

if BUILD_ORIG
libdelib_@PACKAGE_VERSION@_la_SOURCES += delib/orig.cc delib/orig_delib/delib/delib_io_seriellFTDI.c delib/orig_delib/delib/delib_Dapi_di_do_ad_da_befehle-usb.c delib/orig_delib/delib/delib_set_get_error.c delib/orig_delib/delib/delib_Dapi_register_commands-usb.c delib/orig_delib/delib/delib_io_ftdi_linux.c delib/orig_delib/delib/delib_io_ftdi.c delib/orig_delib/delib/delib_open_close_linux-usb.c delib/orig_delib/delib/delib_open_close-usb.c delib/orig_delib/delib/convert_functions.c delib/orig_delib/usb/ftdi.c delib/orig_delib/usb/usb.c delib/orig_delib/usb/linux.c delib/orig_delib/usb/error.c delib/orig_delib/usb/descriptors.c
endif

bin_PROGRAMS = usb_bpg_200_demo
usb_bpg_200_demo_SOURCES = src/usb_bpg_200_demo.cc
usb_bpg_200_demo_LDADD = libdelib-@PACKAGE_VERSION@.la libusb_bpg_200-@PACKAGE_VERSION@.la $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh
