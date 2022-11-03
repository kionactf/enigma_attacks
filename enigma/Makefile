CC := gcc
#CC := clang
RM := rm
AR := ar

INCLUDEDIR := ../include
LIBDIR := ../lib

INCLUDE := -I. -I$(INCLUDEDIR)
DEBUG := -DDEBUG
CFLAGS := -O3 -Wall -Wextra

all:	test libenigma.a libenigma.so

enigma.o:	enigma.c
	$(CC) $(CFLAGS) $(INCLUDE) -fPIC -c -o $@ $<

libenigma.so:	enigma.o
	$(CC) $(CFLAGS) $(INCLUDE) -shared -fPIC -o $@ $^
	mv $@ $(LIBDIR)

libenigma.a:	enigma.o
	$(AR) rcs $@ $^
	mv $@ $(LIBDIR)
	ln -s $(LIBDIR)/$@ $@

test:	testenigma.c libenigma.a
	$(CC) $(CFLAGS) $(INCLUDE) -o testenigma -L. $< -lenigma

clean:
	$(RM) testenigma $(LIBDIR)/libenigma.a $(LIBDIR)/libenigma.so *.a *.o


