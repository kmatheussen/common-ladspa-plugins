# -----------------------------------------------------------------------
#
#  Copyright (C) 2010-2014 Fons Adriaensen <fons@linuxaudio.org>
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
# -----------------------------------------------------------------------


CPPFLAGS += -I. -fPIC -D_REENTRANT
CXXFLAGS += -Wall -O2

all:	stereo-plugins.so

STEREO_O = stereo.o stereo_if.o 
stereo-plugins.so:	$(STEREO_O)	
	g++ -shared  -o $@  $(STEREO_O)

stereo.o:	ladspaplugin.h stereo.h
stereo_if.o:	ladspaplugin.h stereo.h


install:	stereo-plugins.so
	cp  *.so /usr/lib/ladspa

clean:
	rm -rf *~ *.o *.so
