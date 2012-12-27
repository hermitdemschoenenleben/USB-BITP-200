OBJ=delib.o orig_delib.o usb_bpg_200.o

CXXFLAGS := -g -Wall -std=c++11 $(INCLUDEFLAGS)
LDLIBS := -L. -ldelib -Lorig_delib -lorigdelib
LDFLAGS := 
CC=g++


all: usb_bpg_200_demo

usb_bpg_200_demo: usb_bpg_200_demo.o libdelib.a orig_delib/liborigdelib.a

libdelib.a: ${OBJ}
	ar rv $@ ${OBJ}
	ranlib $@

orig_delib/liborigdelib.a:
	${MAKE} -C orig_delib

clean:
	rm -f ${OBJ} libdelib.a usb_bpg_200_demo usb_bpg_200_demo.o
	${MAKE} -C orig_delib clean
