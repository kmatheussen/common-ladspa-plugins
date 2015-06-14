// -----------------------------------------------------------------------
//
//  Copyright (C) 2009-2014 Fons Adriaensen <fons@linuxaudio.org>
//    
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// -----------------------------------------------------------------------


#ifndef __AUTOWAH_H
#define __AUTOWAH_H


#include "ladspaplugin.h"


class Ladspa_Autowah : public LadspaPlugin
{
public:

    enum { A_INP, A_OUT, C_DRIVE, C_DECAY, C_RANGE, C_FREQ, C_OPMIX, NPORT };

    Ladspa_Autowah (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Autowah (void) {}  

private:

    float     *_port [NPORT];
    float      _wbase;
    float      _bbase;
    float      _rfact;
    float      _z1, _z2;
    float      _s1, _s2;
    float      _gx, _gy;
    float      _dr;
};


#endif
