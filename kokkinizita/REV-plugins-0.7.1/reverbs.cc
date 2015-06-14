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


void Ladspa_zita_reverb::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_zita_reverb::active (bool act)
{
    if (! act)
    {
        _zreverb->reset ();
	_nprep = 0;
    }
}


void Ladspa_zita_reverb::runproc (unsigned long frames, bool add)
{
    unsigned long k;
    float *inp [2] = { _port [A_INPL], _port [A_INPR] };
    float *out [2] = { _port [A_OUTL], _port [A_OUTR] };

    _zreverb->set_delay (_port [C_DELAY][0]);   
    _zreverb->set_xover (_port [C_XOVER][0]);   
    _zreverb->set_rtlow (_port [C_RTLOW][0]);   
    _zreverb->set_rtmid (_port [C_RTMID][0]);   
    _zreverb->set_fdamp (_port [C_FDAMP][0]);   
    _zreverb->set_eq1 (_port [C_FREQ1][0], _port [C_GAIN1][0]);
    _zreverb->set_eq2 (_port [C_FREQ2][0], _port [C_GAIN2][0]);
    _zreverb->set_opmix (_port [C_OPMIX][0]);
    while (frames)
    {
	if (!_nprep)
	{
	    _zreverb->prepare (FRAGM);
	    _nprep = FRAGM;
	}
	k = (_nprep < frames) ? _nprep : frames;
        _zreverb->process (k, inp, out);
        inp [0] += k;
        inp [1] += k;
        out [0] += k;
        out [1] += k;
	frames -= k;
	_nprep -= k;
    }
}



void Ladspa_zita_reverb_amb::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_zita_reverb_amb::active (bool act)
{
    if (! act)
    {
        _zreverb->reset ();
	_nprep = 0;
    }
}


void Ladspa_zita_reverb_amb::runproc (unsigned long frames, bool add)
{
    unsigned long k;
    float *inp [2] = { _port [A_INPL], _port [A_INPR] };
    float *out [4] = { _port [A_OUTW], _port [A_OUTX], _port [A_OUTY], _port [A_OUTZ] };

    _zreverb->set_delay (_port [C_DELAY][0]);   
    _zreverb->set_xover (_port [C_XOVER][0]);   
    _zreverb->set_rtlow (_port [C_RTLOW][0]);   
    _zreverb->set_rtmid (_port [C_RTMID][0]);   
    _zreverb->set_fdamp (_port [C_FDAMP][0]);   
    _zreverb->set_eq1 (_port [C_FREQ1][0], _port [C_GAIN1][0]);
    _zreverb->set_eq2 (_port [C_FREQ2][0], _port [C_GAIN2][0]);
    _zreverb->set_rgxyz (_port [C_RGXYZ][0]);
    while (frames)
    {
	if (!_nprep)
	{
	    _zreverb->prepare (FRAGM);
	    _nprep = FRAGM;
	}
	k = (_nprep < frames) ? _nprep : frames;
        _zreverb->process (k, inp, out);
        inp [0] += k;
        inp [1] += k;
        out [0] += k;
        out [1] += k;
        out [2] += k;
        out [3] += k;
	frames -= k;
	_nprep -= k;
    }
}
