// -----------------------------------------------------------------------
//
//  Copyright (C) 2010-2014 Fons Adriaensen <fons@linuxaudio.org>
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
#include "stereo.h"



void Ladspa_Stwidth::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Stwidth::active (bool act)
{
}


void Ladspa_Stwidth::runproc (unsigned long frames, bool add)
{
    float *inpL = _port [A_INPL];
    float *inpR = _port [A_INPR];
    float *outL = _port [A_OUTL];
    float *outR = _port [A_OUTR];
    float b = _port [C_IPBAL][0];
    float w = _port [C_WIDTH][0];
    float gL, gR, dL, dR, dw, xL, xR, s, d;

    gR = powf (10.0f, 0.05f * b);
    gL = 1.0f / gR;
    dL = (gL - _gL) / frames;
    dR = (gR - _gR) / frames;
    if (fabsf (dL) < 1e-6f) dL = 0;
    if (fabsf (dR) < 1e-6f) dR = 0;
    gL = _gL;
    gR = _gR;

    dw = (w - _w) / frames;
    if (fabsf (dw) < 1e-6f) dw = 0;
    w = _w;

    while (frames--)
    {
	gR += dR;
	gL += dL;
	w  += dw;
	xL = *inpL++ * gL;
	xR = *inpR++ * gR;
	s = xL + xR;
	d = xL - xR;
	*outL++ = 0.5f * (s + w * d);
	*outR++ = 0.5f * (s - w * d);
    }
    
    _gL = gL;
    _gR = gR;
    _w = w;
}



void Ladspa_Stpanner::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Stpanner::active (bool act)
{
}


void Ladspa_Stpanner::runproc (unsigned long frames, bool add)
{
    float *inpL = _port [A_INPL];
    float *inpR = _port [A_INPR];
    float *outL = _port [A_OUTL];
    float *outR = _port [A_OUTR];
    float b = _port [C_IPBAL][0];
    float lp = _port [C_LPAN][0];
    float rp = _port [C_RPAN][0];

    float gLL, gLR, gRL, gRR;
    float dLL, dLR, dRL, dRR;
    float xL, xR;

    xL = (1 - b) * (5 + b) / 40;
    xR = (1 + b) * (5 - b) / 40;
    gLL = xL * (1 - lp) * (5 + lp);
    gLR = xL * (1 + lp) * (5 - lp);
    gRL = xR * (1 - rp) * (5 + rp);
    gRR = xR * (1 + rp) * (5 - rp);

    dLL = (gLL - _gLL) / frames;
    if (fabsf (dLL) < 1e-6f) dLL = 0;
    dLR = (gLR - _gLR) / frames;
    if (fabsf (dLR) < 1e-6f) dLR = 0;
    dRL = (gRL - _gRL) / frames;
    if (fabsf (dRL) < 1e-6f) dRL = 0;
    dRR = (gRR - _gRR) / frames;
    if (fabsf (dRR) < 1e-6f) dRR = 0;

    gLL = _gLL;
    gLR = _gLR;
    gRL = _gRL;
    gRR = _gRR;
    while (frames--)
    {
	gLL += dLL;
	gLR += dLR;
	gRL += dRL;
	gRR += dRR;
	xL = *inpL++;
	xR = *inpR++;
	*outL++ = gLL * xL + gRL * xR;
	*outR++ = gLR * xL + gRR * xR;
    }
    _gLL = gLL;
    _gLR = gLR;
    _gRL = gRL;
    _gRR = gRR;
}



