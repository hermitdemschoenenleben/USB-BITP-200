OBJ=delib/delib.o delib/orig.o delib/ftdi_base.o

INCLUDEFLAGS := -Idelib/
CXXFLAGS := -g -Wall -std=c++11 $(INCLUDEFLAGS)
LDLIBS := -L. -ldelib -Ldelib/orig_delib -lorigdelib -lftdi
LDFLAGS := 
CC=g++


all: libdelib.a liborigdelib usb_bpg_200_demo 

usb_bpg_200_demo: src/usb_bpg_200_demo.o src/usb_bpg_200.o
	$(CC) $(LDFLAGS) -o $@ $?  $(LOADLIBES) $(LDLIBS)

libdelib.a: $(OBJ)
	ar rv $@ $(OBJ)
	ranlib $@

liborigdelib:
	$(MAKE) -C delib/orig_delib

clean:
	rm -f $(OBJ) libdelib.a usb_bpg_200_demo src/usb_bpg_200_demo.o
	$(MAKE) -C delib/orig_delib clean
