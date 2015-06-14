# --------------------------------------------------------------------------
#
#  Copyright (C) 2009-2014 Fons Adriaensen <fons@linuxaudio.org>
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
#
# --------------------------------------------------------------------------


CPPFLAGS += -I. -D_REENTRANT
CXXFLAGS += -ffast-math -fPIC -Wall -O3


all:	autowah.so


WAHPLUGINS_O = wahplugins.o autowah.o
WAHPLUGINS_H = ladspaplugin.h autowah.h

autowah.so:	$(WAHPLUGINS_O)
	g++ -shared  -o autowah.so $(WAHPLUGINS_O)

$(WAHPLUGINS_O):	$(WAHPLUGINS_H)


install:	all
	cp  *.so /usr/lib/ladspa

clean:
	/bin/rm -f *~ *.o *.so

