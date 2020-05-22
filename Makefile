BASEFLAGS = -Wall -Werror -m64
LIB_CFLAGS = ${BASEFLAGS} -I. -fPIC -shared
LIB_DBFLAGS = ${LIB_CFLAGS} -ggdb

# Allow program to link to local library
LOCAL_LINK = -Wl,-R -Wl,. -lclargs

CFLAGS = -Wall -Werror -m64 -ggdb -I. -fPIC -shared

CC = cc

libclargs.so: clargs.c clargs.h
	$(CC) ${LIB_CFLAGS} -o libclargs.so clargs.c

debug:
	$(CC) ${LIB_DBFLAGS} -o libclargsd.so clargs.c
	$(CC) ${BASEFLAGS} -ggdb -L. -o test test.c ${LOCAL_LINK}d

install:
	install -D --mode=755 libclargs.so /usr/lib
	install -D --mode=775 clargs.h     /usr/local/include

uninstall:
	rm -f /usr/lib/libclargs.so
	rm -f /usr/local/include/clargs.h


clean:
	rm -f libclargs.so libclargsd.so test
