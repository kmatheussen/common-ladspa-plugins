// -----------------------------------------------------------------------
//
//  Copyright (C) 2003-2014 Fons Adriaensen <fons@linuxaudio.org>
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


#include <stdio.h>
#include <math.h>
#include "reverbs.h"


extern float exp2ap (float x);


void Ladspa_G2reverb::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_G2reverb::active (bool act)
{
    if (! act) _greverb->reset ();
}


void Ladspa_G2reverb::runproc (unsigned long frames, bool add)
{
    _greverb->set_roomsize (_port [C_SIZE][0]);   
    _greverb->set_revbtime (_port [C_RT60][0]);   
    _greverb->set_ipbandw (0.1f + 0.9f * _port [C_IPBW][0]);   
    _greverb->set_damping (0.9f * _port [C_DAMP][0]);   
    _greverb->set_dryslev (exp2ap (0.1661f * _port [C_DRYS][0]));   
    _greverb->set_refllev (exp2ap (0.1661f * _port [C_REFL][0]));   
    _greverb->set_taillev (exp2ap (0.1661f * _port [C_TAIL][0]));   
    _greverb->process (frames, _port [A_INPL], _port [A_INPR], _port [A_OUTL], _port [A_OUTR]);
}

