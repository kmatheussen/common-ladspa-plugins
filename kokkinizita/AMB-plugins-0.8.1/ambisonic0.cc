/*
    Copyright (C) 2010 Fons Adriaensen <fons@kokkinizita.net>
    
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


#include <string.h>
#include <math.h>
#include "ambisonic0.h"


void Ladspa_Tricard2amb::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Tricard2amb::active (bool act)
{
}


void Ladspa_Tricard2amb::runproc (unsigned long len, bool add)
{
    int   i;
    float lt, rt, bk;
    float *inp_L, *inp_R, *inp_B, *out_W, *out_X, *out_Y;

    inp_L = _port [INP_L];
    inp_R = _port [INP_R];
    inp_B = _port [INP_B];
    out_W = _port [OUT_W];
    out_X = _port [OUT_X];
    out_Y = _port [OUT_Y];
    memset (_port [OUT_Z], 0, len * sizeof (float));

    for (i = 0; i < (int)len; i++)
    {
	lt = inp_L [i];
	rt = inp_R [i];
	bk = inp_B [i];
	out_W [i] = 0.47140f * (lt + rt + bk);
	out_X [i] = 0.66667f * (lt + rt) - 1.33333f * bk;
	out_Y [i] = 1.15470f * (lt - rt);
    }
}



void Ladspa_Virtualmic::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Virtualmic::active (bool act)
{
}


void Ladspa_Virtualmic::runproc (unsigned long len, bool add)
{
    _vmic.set_elev (_port [CTL_ELEV][0]);
    _vmic.set_azim (_port [CTL_AZIM][0]);
    _vmic.set_angle (_port [CTL_ANGLE][0]);
    _vmic.set_direc (_port [CTL_POLAR][0]);
    _vmic.process (len,
                   _port [INP_W], _port [INP_X], _port [INP_Y], _port [INP_Z],
                   _port [OUT_L], _port [OUT_R]);
}




Ladspa_UHJ_encoder::Ladspa_UHJ_encoder (unsigned long fsam) :
    LadspaPlugin (fsam),
    _err (false)
{
    if (   Allpass22::initquad (&_Wfilt_r, &_Wfilt_i, fsam)
        || Allpass22::initquad (&_Xfilt_r, &_Xfilt_i, fsam)
        || Allpass22::initquad (&_Yfilt_r, 0, fsam)) _err = true;
}


void Ladspa_UHJ_encoder::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_UHJ_encoder::active (bool act)
{
    if (act)
    {
	_Wfilt_r.reset ();
	_Wfilt_i.reset ();
	_Xfilt_r.reset ();
	_Xfilt_i.reset ();
	_Yfilt_r.reset ();
    }
}


void Ladspa_UHJ_encoder::runproc (unsigned long len, bool add)
{
//     |         W                   X                Y         Z
// ------------------------------------------------------------------
//  L  |   0.4698 - 0.1710j    0.0928 + 0.2550j    0.3277       0 
//  R  |   0.4698 + 0.1710j    0.0928 - 0.2550j   -0.3277       0

    float *W, *X, *Y, *L, *R;
    float s, d;
    int   j, k;
    float Wdata_r [80];
    float Wdata_i [80];
    float Xdata_r [80];
    float Xdata_i [80];
    float Ydata_r [80];

    W = _port [INP_W];
    X = _port [INP_X];
    Y = _port [INP_Y];
    L = _port [OUT_L];
    R = _port [OUT_R];

    if (_err)
    {
	memset (L, 0, len *sizeof (float));
	memset (R, 0, len *sizeof (float));
	return;
    }

    while (len)
    {
	k = (len < 80) ? len : 64;
	_Wfilt_r.process (k, W, Wdata_r);
	_Wfilt_i.process (k, W, Wdata_i);
	_Xfilt_r.process (k, X, Xdata_r);
	_Xfilt_i.process (k, X, Xdata_i);
	_Yfilt_r.process (k, Y, Ydata_r);
	for (j = 0; j < k; j++)
	{
	    s =  0.4698f * Wdata_r [j] + 0.0928f * Xdata_r [j];
	    d = -0.1710f * Wdata_i [j] + 0.2550f * Xdata_i [j] + 0.3277f * Ydata_r [j];
	    L [j] = s + d;
	    R [j] = s - d;
	}
	W += k;
	X += k;
	Y += k;
	L += k;
        R += k;
	len -= k;
    }
}



Ladspa_UHJ_decoder::Ladspa_UHJ_decoder (unsigned long fsam) :
    LadspaPlugin (fsam),
    _err (false)
{
    if (   Allpass22::initquad (&_Lfilt_r, &_Lfilt_i, fsam)
        || Allpass22::initquad (&_Rfilt_r, &_Rfilt_i, fsam)) _err = true;
}


void Ladspa_UHJ_decoder::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_UHJ_decoder::active (bool act)
{
    if (act)
    {
	_Lfilt_r.reset ();
	_Lfilt_i.reset ();
	_Rfilt_r.reset ();
	_Rfilt_i.reset ();
    }
}


void Ladspa_UHJ_decoder::runproc (unsigned long len, bool add)
{
//      |         L                   R
// ---------------------------------------------
//  W   |   0.491 + 0.082j      0.491 - 0.082j
//  X   |   0.210 - 0.414j      0.210 + 0.414j
//  Y   |   0.382 + 0.193j     -0.382 + 0.193j

    float *L, *R, *W, *X, *Y, *Z;
    float sr, dr, si, di;
    int   j, k;
    float Ldata_r [80];
    float Ldata_i [80];
    float Rdata_r [80];
    float Rdata_i [80];

    L = _port [INP_L];
    R = _port [INP_R];
    W = _port [OUT_W];
    X = _port [OUT_X];
    Y = _port [OUT_Y];
    Z = _port [OUT_Z];

    memset (Z, 0, len *sizeof (float));
    if (_err)
    {
	memset (W, 0, len *sizeof (float));
	memset (X, 0, len *sizeof (float));
	memset (Y, 0, len *sizeof (float));
	return;
    }

    while (len)
    {
	k = (len < 80) ? len : 64;
	_Lfilt_r.process (k, L, Ldata_r);
	_Lfilt_i.process (k, L, Ldata_i);
	_Rfilt_r.process (k, R, Rdata_r);
	_Rfilt_i.process (k, R, Rdata_i);
	for (j = 0; j < k; j++)
	{
	    sr = Ldata_r [j] + Rdata_r [j];
	    dr = Ldata_r [j] - Rdata_r [j];
	    si = Ldata_i [j] + Rdata_i [j];
	    di = Ldata_i [j] - Rdata_i [j];
	    W [j] = 0.491f * sr + 0.082f * di;
	    X [j] = 0.210f * sr - 0.414f * di;
	    Y [j] = 0.382f * dr + 0.193f * si;
	}
	L += k;
        R += k;
	W += k;
	X += k;
	Y += k;
	len -= k;
    }
}


