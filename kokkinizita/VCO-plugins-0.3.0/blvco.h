/*
  Copyright (C) 2003 Fons Adriaensen
    
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


#ifndef __VCOSAWPULSE_H
#define __VCOSAWPULSE_H

#include "ladspaplugin.h"


class Ladspa_VCO_pulse1 : public LadspaPlugin
{
public:

    enum { NPHASE = 8, NCOEFF = 12, FILLEN = 256 };
    enum { OUTP, FREQ, EXPM, LINM, OCTN, TUNE, EXPG, LING, FILT, NPORT };

    Ladspa_VCO_pulse1 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_VCO_pulse1 (void) {}  

private:

    float   *_port [NPORT];
    float   _p, _w, _y, _z;
    float   _f [FILLEN + NCOEFF];
    int     _j;
};


class Ladspa_VCO_saw1 : public LadspaPlugin
{
public:

    enum { NPHASE = 8, NCOEFF = 12, FILLEN = 256 };
    enum { OUTP, FREQ, EXPM, LINM, SYNC, OCTN, TUNE, EXPG, LING, FILT, NPORT };

    Ladspa_VCO_saw1 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_VCO_saw1 (void) {}  

private:

    float   *_port [NPORT];
    float   _p, _w, _x, _y, _z, _d;
    float   _f [FILLEN + NCOEFF];
    int     _j;
};


class Ladspa_VCO_rec1 : public LadspaPlugin
{
public:

    enum { NPHASE = 8, NCOEFF = 12, FILLEN = 256 };
    enum { OUTP, FREQ, EXPM, LINM, WAVM, SYNC, OCTN, TUNE, EXPG, LING, WAVE, WMOD, FILT, NPORT };

    Ladspa_VCO_rec1 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_VCO_rec1 (void) {}  

private:

    float   *_port [NPORT];
    float   _p, _w, _b, _x, _y, _z, _d;
    float   _f [FILLEN + NCOEFF];
    int     _j, _k;
};


#endif
