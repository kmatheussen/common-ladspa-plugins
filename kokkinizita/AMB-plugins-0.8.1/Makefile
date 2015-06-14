#    Copyright (C) 2004-2010 Fons Adriaensen <fons@kokkinizita.net>
#    
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


CPPFLAGS += -I. -fPIC -D_REENTRANT -Wall -O3


all:	ambisonic0.so ambisonic1.so ambisonic2.so ambisonic3.so


ambisonic0.so:	ambisonic0.o ambisonic0_if.o virtmic.o allpass.o
	g++ -shared -o $@ ambisonic0.o ambisonic0_if.o virtmic.o allpass.o

ambisonic0.o:	ladspaplugin.h ambisonic0.h
ambisonic0_if.o:	ladspaplugin.h ambisonic0.h


ambisonic1.so:	ambisonic1.o ambisonic1_if.o filter1.o
	g++ -shared -o $@ ambisonic1.o ambisonic1_if.o filter1.o

ambisonic1.o:	ladspaplugin.h ambisonic1.h filter1.h
ambisonic1_if.o:	ladspaplugin.h ambisonic1.h


ambisonic2.so:	ambisonic2.o ambisonic2_if.o 
	g++ -shared -o $@ ambisonic2.o ambisonic2_if.o

ambisonic2.o:	ladspaplugin.h ambisonic2.h
ambisonic2_if.o:	ladspaplugin.h ambisonic2.h


ambisonic3.so:	ambisonic3.o ambisonic3_if.o 
	g++ -shared -o $@ ambisonic3.o ambisonic3_if.o

ambisonic3.o:	ladspaplugin.h ambisonic3.h
ambisonic3_if.o:	ladspaplugin.h ambisonic3.h


install:	all
	/usr/bin/install -m 755 *.so /usr/lib/ladspa
#       Remove incompatible old versions
	/bin/rm -rf /usr/lib/ladspa/ambisonic.so
	/bin/rm -rf /usr/lib/ladspa/ambis1.so
	/bin/rm -rf /usr/lib/ladspa/ambis2.so


DIR := $(shell basename `pwd`)

archive:	clean
	cd ..; /bin/rm -f $(DIR).tar.bz2; tar cvf $(DIR).tar $(DIR); bzip2 $(DIR).tar


clean:
	/bin/rm -f *~ *.o *.so

