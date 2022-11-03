CC := gcc
#CC := clang
RM := rm
AR := ar

INCLUDEDIR := ../include
LIBDIR := ../lib

INCLUDE := -I. -I$(INCLUDEDIR)
LDFLAGS := -L$(LIBDIR)
LIBS := -lenigma -lm
HILLCLIMBDEBUG := -DHILLCLIMBDEBUG
BOMBEDEBUG := -DBOMBEDEBUG
CFLAGS := -O3 -Wall -Wextra

all:	test libenigma_attack.a libenigma_attack.so

frequtil.o:	frequtil.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -fPIC -c -o $@ $< $(LIBS)

hillclimb_plugboard.o:	hillclimb_plugboard.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -fPIC -c -o $@ $< $(LIBS)

bombe_plugboard.o:	bombe_plugboard.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -fPIC -c -o $@ $< $(LIBS)

libenigma_attack.so:	bombe_plugboard.o hillclimb_plugboard.o frequtil.o
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -shared -fPIC -o $@ $^
	mv $@ $(LIBDIR)

libenigma_attack.a:	bombe_plugboard.o hillclimb_plugboard.o frequtil.o
	$(AR) rcs $@ $^
	mv $@ $(LIBDIR)
	ln -s $(LIBDIR)/$@ $@

libenigma.a:
	ln -s $(LIBDIR)/$@ $@

test:	testenigmaattack.c libenigma_attack.a libenigma.a
	$(CC) $(CFLAGS) $(INCLUDE) -L. -o testenigmaattack $< -lenigma_attack $(LIBS)

clean:
	$(RM) testenigmaattack $(LIBDIR)/libenigma_attack.so $(LIBDIR)/libenigma_attack.a *.a *.o

