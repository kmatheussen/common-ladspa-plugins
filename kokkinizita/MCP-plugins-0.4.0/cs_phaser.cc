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


#include <stdio.h>
#include <math.h>
#include "cs_phaser.h"


extern float exp2ap (float);



void Ladspa_CS_phaser1::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_CS_phaser1::active (bool act)
{
    if (act)
    {
        _w = _z = 0;
        for (int i = 0; i < NSECT; i++) _c [i] = 0;
    }
}


void Ladspa_CS_phaser1::runproc (unsigned long len, bool add)
{
    int   i, k, ns;
    float *p0, *p1, *p2, *p3, *p4;
    float g0, gf, gi, gm;
    float d, t, w, dw, x, z;

    p0 = _port [0];    
    p1 = _port [1];    
    p2 = _port [2] - 1;    
    p3 = _port [3] - 1;    
    p4 = _port [4] - 1;    
    
    ns = (int)(floor (_port [6][0] + 0.5));
    g0 = exp2ap (0.1661f * _port [5][0]);
    gf = _port [10][0];
    gm = _port [11][0];
    gi = 1 - fabs (gm);
   
    w = _w;
    z = _z + 1e-10f;

    do
    {
	k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        p4 += k;
        len -= k;

        t = (exp2ap (_port [8][0] * *p3 + _port [7][0] + *p2 + 9.683f) + _port [9][0] * *p4 * 1000.0f) / _fsam;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.5f) t = 1.5f;
        t = (sinf (t) - 1) / cosf (t) + 1;
        dw = (t - w) / k;

        while (k--)
	{
	    w += dw;
            x = g0 * *p0++;
            z = gf * z + x;
            z = 4 * tanhf (0.25f * z);
            for (i = 0; i < ns; i++)
	    {
                t = _c [i];
                d = w * (2 * z - t);
                t += d;
                _c [i] = t + d;
                z = t - z;
	    }  
            t = gm * z + gi * x;                
            if (add) *p1++ += t * _gain;
            else     *p1++  = t;
	} 
    }
    while (len);

    _w = w;
    _z = z;
}



void Ladspa_CS_phaser1lfo::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_CS_phaser1lfo::active (bool act)
{
    if (act)
    {
        _gi = 0;
        _z = _w = _v = _p = 0;
        for (int i = 0; i < NSECT; i++) _c [i] = 0;
    }
}




void Ladspa_CS_phaser1lfo::runproc (unsigned long len, bool add)
{
    int   i, k, ns;
    float *p0, *p1;
    float g0, gf, gi, gm;
    float d, t, w, v, x, z;

    p0 = _port [0];    
    p1 = _port [1];    

    ns = (int)(floor (_port [3][0] + 0.5));
    g0 = exp2ap (0.1661f * _port [2][0]);
    gf = _port [8][0];
    gm = _port [9][0];
    gi = 1 - fabs (gm);

    z = _z + 1e-10f;
    w = _w;
    v = _v;

    do
    {
        if (_gi == 0)
	{
	    _gi = DSUB;
            _p += 2 * DSUB * _port [5][0] / _fsam;
            if (_p > 1) _p -= 2;
            x = 0.999f * _port [6][0];
            d = _p - x;
            if (d < 0) t = 0.5f + d / (1 + x);
            else       t = 0.5f - d / (1 - x);            
            t = exp2ap (_port [7][0] * t + _port [4][0] + 9.683f) / _fsam;
            if (t < 0.0f) t = 0.0f;
            if (t > 1.5f) t = 1.5f;
            t = (sinf (t) - 1) / cosf (t) + 1;
            v = (t - w) / DSUB;
	}

        k = (_gi < len) ? _gi : len;
        _gi -= k;
        len -= k;
        while (k--)
	{
            x = g0 * *p0++;
            z = gf * z + x;
            z = 4 * tanhf (0.25f * z);
            for (i = 0; i < ns; i++)
	    {
                t = _c [i];
                d = w * (2 * z - t);
                t += d;
                _c [i] = t + d;
                z = t - z;
	    }  
            t = gm * z + gi * x;                
            if (add) *p1++ += t * _gain;
            else     *p1++  = t;
	    w += v;
	} 
    }
    while (len);

    _z = z;
    _w = w;
    _v = v;
}


