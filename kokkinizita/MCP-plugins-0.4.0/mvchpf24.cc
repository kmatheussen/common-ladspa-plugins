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
#include "mvchpf24.h"


extern float exp2ap (float x);


void Ladspa_Mvchpf1::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Mvchpf1::active (bool act)
{
    _c1 = _c2 = _c3 = _c4 = _x = 0;
    _w = 1e5;
}


void Ladspa_Mvchpf1::runproc (unsigned long len, bool add)
{
    int   k;
    float *p0, *p1, *p2, *p3;
    float c1, c2, c3, c4;
    float g0, g1, d, w, dw, t, x, y;

    p0 = _port [AINP];
    p1 = _port [AOUT];
    p2 = _port [AFREQ] - 1;
    p3 = _port [AFMOD] - 1;
    g0 = exp2ap (0.1661f * _port [CINP][0]) / 4;
    g1 = exp2ap (0.1661f * _port [COUT][0]) * 4;
    if (add) g1 *= _gain;

    c1 = _c1;
    c2 = _c2;
    c3 = _c3;
    c4 = _c4;
    w = _w; 
    x = _x;

    do
    {
        k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        len -= k;

        t = _fsam / exp2ap (_port [CFMOD][0] * *p3 + *p2 + _port [CFREQ][0] + 9.2f);
        if (t < 2) t = 2;
        dw = (t - w) / k;

        while (k--)
	{
            w += dw;                        

            x = y = *p0++ * g0 - 0.3f * x;

            d = x - c1 + 1e-10f;
            t = d * d;
            d *= (1 + t) / (w + t);            
            c1 += d;
            x -= c1;
            c1 += d;

            d = x - c2 + 1e-10f;
            t = d * d;
            d *= (1 + t) / (w + t);            
            c2 += d;
            x -= c2;
            c2 += d;

            d = x - c3 + 1e-10f;
            t = d * d;
            d *= (1 + t) / (w + t);            
            c3 += d;
            x -= c3;
            c3 += d;

            d = x - c4 + 1e-10f;
            t = d * d;
            d *= (1 + t) / (w + t);            
            c4 += d;
            x -= c4;
            c4 += d;

            if (add) *p1++ += g1 * x;
            else     *p1++  = g1 * x;

            x -= y;
	}
    }
    while (len);

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _w = w;
    _x = x;
}



