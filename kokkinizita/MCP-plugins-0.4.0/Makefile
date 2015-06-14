#  Copyright (C) 2003-2008 Fons Adriaensen <fons@kokkinizita.net>
#    
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


CPPFLAGS += -I. -fPIC -D_REENTRANT -Wall -O3


all:	mvclpf24.so mvchpf24.so cs_phaser.so cs_chorus.so


mvclpf24.so:	mvclpf24.o mvclpf24_if.o exp2ap.o
	g++ -shared  mvclpf24.o mvclpf24_if.o exp2ap.o -o mvclpf24.so

mvclpf24.o:	ladspaplugin.h mvclpf24.h
mvclpf24_if.o:	ladspaplugin.h mvclpf24.h


mvchpf24.so:	mvchpf24.o mvchpf24_if.o exp2ap.o
	g++ -shared  mvchpf24.o mvchpf24_if.o exp2ap.o -o mvchpf24.so

mvchpf24.o:	ladspaplugin.h mvchpf24.h
mvchpf24_if.o:	ladspaplugin.h mvchpf24.h


cs_phaser.so:	cs_phaser.o cs_phaser_if.o exp2ap.o
	g++ -shared cs_phaser.o cs_phaser_if.o exp2ap.o -o cs_phaser.so

cs_phaser.o:	ladspaplugin.h cs_phaser.h
cs_phaser_if.o:	ladspaplugin.h cs_phaser.h


cs_chorus.so:	cs_chorus.o cs_chorus_if.o exp2ap.o
	g++ -shared  cs_chorus.o cs_chorus_if.o exp2ap.o -o cs_chorus.so

cs_chorus.o:	ladspaplugin.h cs_chorus.h
cs_chorus_if.o:	ladspaplugin.h cs_chorus.h


install:	all
	cp  *.so /usr/lib/ladspa


DIR := $(shell basename `pwd`)

archive:	clean
	cd ..; /bin/rm -f $(DIR).tar.bz2; tar cvjf $(DIR).tar.bz2 $(DIR)

clean:
	/bin/rm -f *~ *.o *.so

