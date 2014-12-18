IFLAGS = -Iduktape-1.0.2/src

ifeq ($(MAKECMDGOALS), libc)
	LDFLAGS =  -lrt -lm
	CC = gcc
	_PLATFORM_DIR = platforms/libc/
	HOST_PLATFORM = '\#define HOST_PLATFORM_LIBC'
endif

ifeq ($(MAKECMDGOALS), win32)
	LDFLAGS = -lgdi32 -luser32 -lshell32 -lkernel32
	CC = i686-w64-mingw32-gcc
	_PLATFORM_DIR = platforms/win32/
	_MAIN = platforms/win32/main.c
	HOST_PLATFORM = '\#define HOST_PLATFORM_WIN32'
endif

ifeq ($(MAKECMDGOALS), e)
	LDFLAGS = `pkg-config --cflags --libs ecore eio`
	CC = gcc
	_PLATFORM_DIR = platforms/e/
	HOST_PLATFORM = '\#define HOST_PLATFORM_E'
endif

objects = main.o duktape.o

libc : $(objects) defs
	$(CC) -o libccbc $(objects) $(LDFLAGS)
e : $(objects) defs
	$(CC) -o ecbc $(objects) $(LDFLAGS)
win32 : $(objects) defs
	$(CC) -o cbc.exe $(objects) $(LDFLAGS)

defs :
	touch defs.h
main.o : main.c $(_PLATFORM_DIR)*
	echo $(HOST_PLATFORM) > defs.h
	$(CC) -c $(IFLAGS) main.c

duktape.o : duktape-1.0.2/src/duktape.c
	$(CC) -c $(IFLAGS) duktape-1.0.2/src/duktape.c

clean :
	rm -f defs.h
	rm -f libccbc
	rm -f ecbc
	rm -f cbc.exe
	rm -f main.o
	rm -f duktape.o

