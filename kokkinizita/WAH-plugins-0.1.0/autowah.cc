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


#include <math.h>
#include <string.h>
#include "autowah.h"


void Ladspa_Autowah::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


#define G_RES 4.0f
#define F_MIN 300.0f
#define F_RAT 10
#define B_MIN 0.03f
#define B_RAT 4
#define T_MIN 0.05f 
#define T_LOG 2


void Ladspa_Autowah::active (bool act)
{
    if (! act) return;

    _wbase = F_MIN * 6.28f / _fsam;
    _bbase = B_MIN;
    _rfact = 64.0f / (_fsam * T_MIN);
    _z1 = _z2 = 0;
    _s1 = _s2 = 0;
    _gx = _gy = 0;
    _dr = 0;
}


void Ladspa_Autowah::runproc (unsigned long len, bool add)
{
    int   i, k;
    float *inp = _port [A_INP];
    float *out = _port [A_OUT];
    float z1, z2, s1, s2, gx, gy;
    float ds1, ds2, dgx, dgy;
    float gd, rf, md, fr, dr;
    float b, p, t, w, x, y;

    gx = _gx;
    gy = _gy;
    t = _port [C_OPMIX][0];
    _gy = G_RES * t;
    _gx = _gy + 1 - t;
    dgx = (_gx - gx) / len;
    dgy = (_gy - gy) / len;

    gd = 10 * powf (10.0f, 0.05f * _port [C_DRIVE][0]);
    rf = 1.0f - _rfact / powf (10.0f, T_LOG * _port [C_DECAY][0]);
    md = _port [C_RANGE][0];
    fr = _port [C_FREQ][0];

    z1 = _z1;
    z2 = _z2;
    s1 = _s1;
    s2 = _s2;
    dr = _dr;

    while (len)
    {
	k = (len > 80) ? 64 : len;

	p = 0;
	for (i = 0; i < k; i++)
	{
	    x = inp [i];
	    p += x * x;
	}
	p = gd * sqrtf (p / k);

	if (p > dr) dr += 0.1f * (p - dr);
	if (dr > md) dr = md;
	t = dr + fr; 
	dr = dr * rf + 1e-10f;
	w = _wbase  * (1 + (F_RAT - 1) * t * t); 
	b = w * _bbase * (1 + (B_RAT - 1) * t);
        if (w > 0.7f) w = 0.7f;

	_s1 = -cosf (w);
	_s2 = (1 - b) / (1 + b);
	ds1 = (_s1 - s1) / k;
	ds2 = (_s2 - s2) / k;
  
	for (i = 0; i < k; i++)
	{
	    s1 += ds1;
	    s2 += ds2;
            gx += dgx;
            gy += dgy;
            x = inp [i];
            y = x - s2 * z2;
            out [i] = gx * x - gy * (z2 + s2 * y);                           
            y -= s1 * z1;
            z2 = z1 + s1 * y;
            z1 = y + 1e-10f;
	}
	inp += k;
	out += k;
	len -= k;
    }

    _z1 = z1;
    _z2 = z2;
    _dr = dr;
}

