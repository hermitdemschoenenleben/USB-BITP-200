OBJ=delib.o orig.o ftdi_base.o ftdi_serial.o usb_bpg_200.o

CXXFLAGS := -g -Wall -std=c++11 $(INCLUDEFLAGS)
LDLIBS := -L. -ldelib -Lorig_delib -lorigdelib
LDFLAGS := 
CC=g++


all: usb_bpg_200_demo

usb_bpg_200_demo: usb_bpg_200_demo.o libdelib.a liborigdelib
	$(CC) $(LDFLAGS) -o $@ $<  $(LOADLIBES) $(LDLIBS)

libdelib.a: $(OBJ)
	ar rv $@ $(OBJ)
	ranlib $@

liborigdelib:
	$(MAKE) -C orig_delib

clean:
	rm -f $(OBJ) libdelib.a usb_bpg_200_demo usb_bpg_200_demo.o
	$(MAKE) -C orig_delib clean
