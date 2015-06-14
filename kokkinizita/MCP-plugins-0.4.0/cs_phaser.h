/*
  Copyright (C) 2003-2008 Fons Adriaensen <fons@kokkinizita.net>
    
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef __CS_PHASER_H
#define __CS_PHASER_H

#include "ladspaplugin.h"


class Ladspa_CS_phaser1 : public LadspaPlugin
{
public:

    enum { NPORT = 12, NSECT = 30 };

    Ladspa_CS_phaser1 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_CS_phaser1 (void) {}  

private:

    float *_port [NPORT];
    float _w, _z, _c [NSECT];
};


class Ladspa_CS_phaser1lfo : public LadspaPlugin
{
public:

    enum { NPORT = 10, NSECT = 30 };

    Ladspa_CS_phaser1lfo (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_CS_phaser1lfo (void) {}  

private:

    enum { DSUB = 32 };

    float *_port [NPORT];
    float _z, _w, _v, _p, _c [NSECT];
    unsigned int _gi;
};

#endif
