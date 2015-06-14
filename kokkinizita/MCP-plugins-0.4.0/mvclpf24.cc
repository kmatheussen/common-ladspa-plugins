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
#include "mvclpf24.h"


extern float exp2ap (float x);


void Ladspa_Moogvcf1::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Moogvcf1::active (bool act)
{
    _c1 = _c2 = _c3 = _c4 = _c5 = _w = _r = 0;
}


void Ladspa_Moogvcf1::runproc (unsigned long len, bool add)
{
    int   k;
    float *p0, *p1, *p2, *p3, *p4;
    float c1, c2, c3, c4, c5;
    float g0, g1, r, dr, w, dw, x, t;

    p0 = _port [A_INPUT];
    p1 = _port [A_OUTPUT];
    p2 = _port [A_FREQ] - 1;
    p3 = _port [A_FMOD] - 1;
    p4 = _port [A_RESO] - 1;
    g0 = exp2ap (0.1661f * _port [C_IPGAIN][0]) / 4;
    g1 = exp2ap (0.1661f * _port [C_OPGAIN][0]) * 4;
    if (add) g1 *= _gain;

    c1 = _c1 + 1e-6f;
    c2 = _c2;
    c3 = _c3;
    c4 = _c4;
    c5 = _c5;
    w = _w; 
    r = _r;
 
    do
    {
        k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        p4 += k;
        len -= k;

        t = exp2ap (_port [C_FMODG][0] * *p3 + _port [C_FREQ][0] + *p2 + 10.82f) / _fsam;
	if (t < 0.8f) t *= 1 - 0.4f * t - 0.125f * t * t;
        else 
	{
            t *= 0.6f; 
            if (t > 0.92f) t = 0.92f;
	}
        dw = (t - w) / k;

        t = _port [C_RESOG][0] * *p4 + _port [C_RESO][0];
        if (r > 1) r = 1;
        if (r < 0) r = 0;
        dr = (t - r) / k;  

        while (k--)
	{
            w += dw;                        
            r += dr;
	    x = -4.2 * r * c5 + *p0++ * g0 + 1e-10f;
            t = c1 / (1 + fabsf (c1));
            c1 += w * (x - t);
            x = c1 / (1 + fabsf (c1));
            c2 += w * (x  - c2);
            c3 += w * (c2 - c3);
            c4 += w * (c3 - c4);
	    if (add) *p1++ += g1 * c4;
	    else     *p1++  = g1 * c4;
	    c5 += 0.5f * (c4 - c5);
	}
    }
    while (len);

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _c5 = c5;
    _w = w;
    _r = r;
}



void Ladspa_Moogvcf2::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Moogvcf2::active (bool act)
{
    _c1 = _c2 = _c3 = _c4 = _c5 = _w = _r = 0;
}


void Ladspa_Moogvcf2::runproc (unsigned long len, bool add)
{
    int   k;
    float *p0, *p1, *p2, *p3, *p4;
    float c1, c2, c3, c4, c5;
    float g0, g1, r, dr, w, dw, x, t;

    p0 = _port [A_INPUT];
    p1 = _port [A_OUTPUT];
    p2 = _port [A_FREQ] - 1;
    p3 = _port [A_FMOD] - 1;
    p4 = _port [A_RESO] - 1;
    g0 = exp2ap (0.1661f * _port [C_IPGAIN][0]) / 4;
    g1 = exp2ap (0.1661f * _port [C_OPGAIN][0]) * 4;
    if (add) g1 *= _gain;

    c1 = _c1 + 1e-6f;
    c2 = _c2;
    c3 = _c3;
    c4 = _c4;
    c5 = _c5;
    w = _w; 
    r = _r;

    do
    {
        k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        p4 += k;
        len -= k;

        t = exp2ap (_port [C_FMODG][0] * *p3 + _port [C_FREQ][0] + *p2 + 10.71f) / _fsam;
	if (t < 0.8f) t *= 1 - 0.4f * t - 0.125f * t * t;
        else 
	{
            t *= 0.6f; 
            if (t > 0.92f) t = 0.92f;
	}
        dw = (t - w) / k;

        t = _port [C_RESOG][0] * *p4 + _port [C_RESO][0];
        if (t > 1) t = 1;
        if (t < 0) t = 0;
        dr = (t - r) / k;  

        while (k--)
	{
            w += dw;                        
            r += dr;

	    x = -4.5f * r * c5 + *p0++ * g0 + 1e-10f;
//	    x = tanhf (x); 
            x /= sqrtf (1 + x * x);
            c1 += w * (x  - c1) / (1 + c1 * c1);            
            c2 += w * (c1 - c2) / (1 + c2 * c2);            
            c3 += w * (c2 - c3) / (1 + c3 * c3);            
            c4 += w * (c3 - c4) / (1 + c4 * c4);            

	    if (add) *p1++ += g1 * (c4);
	    else     *p1++  = g1 * (c4);
	    c5 += 0.5f * (c4 - c5);
	}
    }
    while (len);

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _c5 = c5;
    _w = w;
    _r = r;
}



void Ladspa_Moogvcf3::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Moogvcf3::active (bool act)
{
    _c1 = _c2 = _c3 = _c4 = _c5 = _w = _r = 0;
}


void Ladspa_Moogvcf3::runproc (unsigned long len, bool add)
{
    int   k;
    float *p0, *p1, *p2, *p3, *p4;
    float c1, c2, c3, c4, c5;
    float g0, g1, r, dr, w, dw, x, t, d;

    p0 = _port [A_INPUT];
    p1 = _port [A_OUTPUT];
    p2 = _port [A_FREQ] - 1;
    p3 = _port [A_FMOD] - 1;
    p4 = _port [A_RESO] - 1;
    g0 = exp2ap (0.1661f * _port [C_IPGAIN][0]) / 4;
    g1 = exp2ap (0.1661f * _port [C_OPGAIN][0]) * 4;
    if (add) g1 *= _gain;

    c1 = _c1;
    c2 = _c2;
    c3 = _c3;
    c4 = _c4;
    c5 = _c5;
    w = _w; 
    r = _r;

    do
    {
        k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        p4 += k;
        len -= k;

        t = exp2ap (_port [C_FMODG][0] * *p3 + _port [C_FREQ][0] + *p2 + 9.70f) / _fsam;
        if (t < 0.75f) t *= 1.005f - t * (0.624f - t * (0.65f - t * 0.54f));
        else
	{
	    t *= 0.6748f;
            if (t > 0.82f) t = 0.82f;
	}
        dw = (t - w) / k;

        t = _port [C_RESOG][0] * *p4 + _port [C_RESO][0];
        if (t > 1) t = 1;
        if (t < 0) t = 0;
        dr = (t - r) / k;  

        while (k--)
	{
            w += dw;                        
            r += dr;

	    x = *p0 * g0 - (4.3f - 0.2f * w) * r * c5 + 1e-10f; 
//            x = tanhf (x);
            x /= sqrtf (1 + x * x);
            d = w * (x  - c1) / (1 + c1 * c1);            
            x = c1 + 0.77f * d;
            c1 = x + 0.23f * d;        
            d = w * (x  - c2) / (1 + c2 * c2);            
            x = c2 + 0.77f * d;
            c2 = x + 0.23f * d;        
            d = w * (x  - c3) / (1 + c3 * c3);            
            x = c3 + 0.77f * d;
            c3 = x + 0.23f * d;        
            d = w * (x  - c4);
            x = c4 + 0.77f * d;
            c4 = x + 0.23f * d;        
            c5 += 0.85f * (c4 - c5);

	    x = *p0++ * g0 -(4.3f - 0.2f * w) * r * c5;
//            x = tanhf (x);
            x /= sqrtf (1 + x * x);
            d = w * (x  - c1) / (1 + c1 * c1);            
            x = c1 + 0.77f * d;
            c1 = x + 0.23f * d;        
            d = w * (x  - c2) / (1 + c2 * c2);            
            x = c2 + 0.77f * d;
            c2 = x + 0.23f * d;        
            d = w * (x  - c3) / (1 + c3 * c3);            
            x = c3 + 0.77f * d;
            c3 = x + 0.23f * d;        
            d = w * (x  - c4);
            x = c4 + 0.77f * d;
            c4 = x + 0.23f * d;        
            c5 += 0.85f * (c4 - c5);

	    if (add) *p1++ += g1 * c4;
            else     *p1++  = g1 * c4;
	}
    }
    while (len);

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _c5 = c5;
    _w = w;
    _r = r;
}


void Ladspa_Moogvcf4::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Moogvcf4::active (bool act)
{
    _c1 = _c2 = _c3 = _c4 = _c5 = _w = _r = 0;
}


void Ladspa_Moogvcf4::runproc (unsigned long len, bool add)
{
    int   k, op;
    float *p0, *p1, *p2, *p3, *p4;
    float c1, c2, c3, c4, c5;
    float g0, g1, r, dr, w, dw, x, t, d, y;

    p0 = _port [A_INPUT];
    p1 = _port [A_OUTPUT];
    p2 = _port [A_FREQ] - 1;
    p3 = _port [A_FMOD] - 1;
    p4 = _port [A_RESO] - 1;
    g0 = exp2ap (0.1661f * _port [C_IPGAIN][0]) / 4;
    g1 = exp2ap (0.1661f * _port [C_OPGAIN][0]) * 4;
    op = (int)(floorf (_port [C_LPFILT][0] + 0.5));
    if (add) g1 *= _gain;

    c1 = _c1 + 1e-6f;
    c2 = _c2;
    c3 = _c3;
    c4 = _c4;
    c5 = _c5;
    w = _w; 
    r = _r;

    do
    {
        k = (len > 24) ? 16 : len;
        p2 += k;
        p3 += k;
        p4 += k;
        len -= k;

        t = exp2ap (_port [C_FMODG][0] * *p3 + _port [C_FREQ][0] + *p2 + 9.70f) / _fsam;
        if (t < 0.75f) t *= 1.005f - t * (0.624f - t * (0.65f - t * 0.54f));
        else
	{
	    t *= 0.6748f;
            if (t > 0.82f) t = 0.82f;
	}
        dw = (t - w) / k;

        t = _port [C_RESOG][0] * *p4 + _port [C_RESO][0];
        if (t > 1) t = 1;
        if (t < 0) t = 0;
        dr = (t - r) / k;  

        while (k--)
	{
            w += dw;                        
            r += dr;

	    x = *p0 * g0 - (4.3f - 0.2f * w) * r * c5 + 1e-10f; 
//            x = tanhf (x);
            x /= sqrtf (1 + x * x);
	    d = w * (x  - c1) / (1 + c1 * c1);           
            x = c1 + 0.77f * d;
            c1 = x + 0.23f * d;        
            d = w * (x  - c2) / (1 + c2 * c2);            
            x = c2 + 0.77f * d;
            c2 = x + 0.23f * d;        
            d = w * (x  - c3) / (1 + c3 * c3);            
            x = c3 + 0.77f * d;
            c3 = x + 0.23f * d;        
            d = w * (x  - c4);
            x = c4 + 0.77f * d;
            c4 = x + 0.23f * d;        
            c5 += 0.85f * (c4 - c5);

	    x = y = *p0++ * g0 -(4.3f - 0.2f * w) * r * c5;
//            x = tanhf (x);
            x /= sqrtf (1 + x * x);
            d = w * (x  - c1) / (1 + c1 * c1);            
            x = c1 + 0.77f * d;
            c1 = x + 0.23f * d;        
            d = w * (x  - c2) / (1 + c2 * c2);            
            x = c2 + 0.77f * d;
            c2 = x + 0.23f * d;        
            d = w * (x  - c3) / (1 + c3 * c3);            
            x = c3 + 0.77f * d;
            c3 = x + 0.23f * d;        
            d = w * (x  - c4);
            x = c4 + 0.77f * d;
            c4 = x + 0.23f * d;        
            c5 += 0.85f * (c4 - c5);

            switch (op)
	    {
            case 1: y = c1; break;
            case 2: y = c2; break;
            case 3: y = c3; break;
            case 4: y = c4; break;
	    }

	    if (add) *p1++ += g1 * y;
            else     *p1++  = g1 * y;
	}
    }
    while (len);

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _c5 = c5;
    _w = w;
    _r = r;
}


