
CPPFLAGS += -I. -fPIC -D_REENTRANT -Wall -O3


blvco.so:	blvco.o blvco_if.o exp2ap.o
	g++ -shared  blvco.o blvco_if.o exp2ap.o -o blvco.so

blvco.o:	ladspaplugin.h blvco.h ladspa.h
blvco_if.o:	ladspaplugin.h blvco.h ladspa.h


install:
	/bin/cp  blvco.so /usr/lib/ladspa
	/bin/cp  blvco.so /usr/lib/ladspa/vco_sawpulse.so


DIR := $(shell basename `pwd`)

archive:	clean
	cd ..; /bin/rm -f $(DIR).tar.bz2; tar cvf $(DIR).tar $(DIR); bzip2 $(DIR).tar


clean:
	/bin/rm -f *~ *.o *.so

