MAKE := make

LIBDIR := ./lib
INCLUDEDIR := ./include

all:	test $(LIBDIR)/libenigma_attack.so $(LIBDIR)/libenigma.so

$(LIBDIR)/libenigma.so:
	$(MAKE) -C enigma libenigma.so

$(LIBDIR)/libenigma_attack.so:
	$(MAKE) -C attack libenigma_attack.so

test:	attack/testenigmaattack.c enigma/testenigma.c
	$(MAKE) -C enigma test
	$(MAKE) -C attack test

clean:
	$(MAKE) -C attack clean
	$(MAKE) -C enigma clean

