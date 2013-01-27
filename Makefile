OBJ=src/delib.o src/orig.o src/ftdi_base.o src/usb_bpg_200.o

CXXFLAGS := -g -Wall -std=c++11 $(INCLUDEFLAGS)
LDLIBS := -L. -ldelib -Lsrc/orig_delib -lorigdelib
LDFLAGS := 
CC=g++


all: usb_bpg_200_demo

usb_bpg_200_demo: src/usb_bpg_200_demo.o libdelib.a liborigdelib
	$(CC) $(LDFLAGS) -o $@ $<  $(LOADLIBES) $(LDLIBS)

libdelib.a: $(OBJ)
	ar rv $@ $(OBJ)
	ranlib $@

liborigdelib:
	$(MAKE) -C src/orig_delib

clean:
	rm -f $(OBJ) libdelib.a usb_bpg_200_demo src/usb_bpg_200_demo.o
	$(MAKE) -C src/orig_delib clean
