# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
# Copyright (c) 2017-2021 Brett Sheffield <bacs@librecast.net>

SHELL = /bin/sh
ifndef VERSION
$(error VERSION not set)
endif
ifndef ABIVERS
$(error ABIVERS not set)
endif
.SUFFIXES:
.SUFFIXES: .c .o
CFLAGS += -O3 -Wall -Wextra -Wpedantic -g -fPIC -I. -I../include
ifndef USE_LIBSODIUM
CFLAGS += -I../libs/blake3/c
endif
LIBNAME := librecast
HEADERS = ../include/$(LIBNAME).h $(sort $(wildcard ../include/$(LIBNAME)/*.h))
INSTALL ?= install
LDCONFIG ?= ldconfig
INSTALL_DATA := $(INSTALL) -m 644
PREFIX ?= /usr/local
LIBDIR := $(DESTDIR)$(PREFIX)/lib
INCLUDEDIR := $(DESTDIR)$(PREFIX)/include
OBJS_BLAKE3 := ../libs/blake3/c/blake3.c ../libs/blake3/c/blake3_dispatch.c ../libs/blake3/c/blake3_portable.c $(sort $(wildcard ../libs/blake3/c/*.o))
OBJECTS := errors.o hash.o
ifeq ($(OSNAME),Linux)
OBJECTS += if_linux.o
else ifeq ($(OSNAME),NetBSD)
OBJECTS += if_netbsd.o
else
OBJECTS += if.o
endif
LIBS := -pthread -lpthread
ifdef USE_LIBSODIUM
CFLAGS += -DUSE_LIBSODIUM=$(USE_LIBSODIUM)
LIBS += -lsodium
else
OBJECTS += $(OBJS_BLAKE3)
endif
SOFILES := liblibrecast.so
SOVFILES := $(foreach f,$(SOFILES),$f.$(VERSION))
ABIFILES := $(foreach f,$(SOFILES),$f.$(ABIVERS))

all: $(SOFILES)

liblibrecast.so: librecast.o $(OBJECTS)
	$(CC) -shared -O3 -fPIC -Wl,-soname,liblibrecast.so.$(ABIVERS) -o $@ $^ $(LIBS)

%.o: %.c %.h librecast_pvt.h $(HEADERS)
	$(CC) $(CFLAGS) -c $<

%.o: %.c librecast_pvt.h
	$(CC) $(CFLAGS) -c $<

install: $(SOFILES)
	$(INSTALL) -d $(LIBDIR)
	$(INSTALL) -d $(INCLUDEDIR)
	$(INSTALL_DATA) liblibrecast.so $(LIBDIR)/liblibrecast.so.$(VERSION)
	cp -r ../include/* $(INCLUDEDIR)
	$(LDCONFIG) -n $(LIBDIR)
	ln -sf liblibrecast.so.$(ABIVERS) $(LIBDIR)/liblibrecast.so

.PHONY: clean realclean uninstall

uninstall:
	rm -f $(foreach f,$(SOFILES),$(DESTDIR)$(LIBDIR)/$f.$(VERSION))
	$(LDCONFIG) -n $(LIBDIR)
	cd $(LIBDIR)/ && rm -f $(SOFILES)

clean:
	$(RM) *.o $(SOFILES) $(ABIFILES)

realclean: clean
