INSTALLDIR=/usr/local/bin
LIBNAME=librecast
LIBDIR=/usr/local/lib
LIBFILE=lib${LIBNAME}.so
INCLUDEDIR=/usr/local/include

all: src docker tests

install: all
	cp src/librecastd ${INSTALLDIR}
	cp src/${LIBFILE} ${LIBDIR}/${LIBFILE}.1.0
	ln -sf ${LIBDIR}/${LIBFILE}.1.0 ${LIBDIR}/${LIBFILE}.1
	ln -sf ${LIBDIR}/${LIBFILE}.1 ${LIBDIR}/${LIBFILE}
	cp src/${LIBNAME}.h ${INCLUDEDIR}
	cp src/lctl ${INSTALLDIR}
	cp src/nodewatch ${INSTALLDIR}

docker: tests/docker/librecastd/Dockerfile
	docker build -t librecastd -f tests/docker/librecastd/Dockerfile .

.PHONY: clean src tests

src:
	cd src && make
tests:
	cd tests && make

clean:
	cd src && make clean
	cd tests && make clean
