/*
    Copyright (C) 2004-2009 Fons Adriaensen <fons@kokkinizita.net>
    
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
#include "ambisonic2.h"


#define DEG2RAD 0.01745329f
#define MIN3DB  0.707107f


void Ladspa_Monopan21::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Monopan21::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f);
}


void Ladspa_Monopan21::calcpar (float az, float el)
{
    float ce; 

    az *= DEG2RAD;
    el *= DEG2RAD;
    ce = cosf (el);
    _xx = ce * cosf (-az);
    _yy = ce * sinf (-az);
    _zz = sinf (el);
    _uu = _xx * _xx - _yy * _yy;
    _vv = 2 * _xx * _yy;
}


void Ladspa_Monopan21::runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, uu, vv, dxx, dyy, dzz, duu, dvv; 
    float *in, *out_w, *out_x, *out_y, *out_z, *out_u, *out_v;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    uu = _uu;
    vv = _vv;
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]); 
    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;
    duu = (_uu - uu) / len;
    dvv = (_vv - vv) / len;

    in = _port [INP];
    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];
    out_u = _port [OUT_U];
    out_v = _port [OUT_V];

    while (len--)
    {
	xx += dxx;
	yy += dyy;
	zz += dzz;
	uu += duu;
	vv += dvv;
        t = *in++;        
        *out_w++ = MIN3DB * t;
        *out_x++ = xx * t;
        *out_y++ = yy * t;
        *out_z++ = zz * t;
        *out_u++ = uu * t;
        *out_v++ = vv * t;
    }
}



void Ladspa_Rotator21::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Rotator21::active (bool act)
{
    if (act) calcpar (0.0f);
}


void Ladspa_Rotator21::calcpar (float az)
{
    az *= DEG2RAD;
    _c1 = cosf (az);
    _s1 = sinf (az);
    _c2 = _c1 * _c1 - _s1 * _s1;
    _s2 = 2 * _c1 * _s1;
}


void Ladspa_Rotator21::runproc (unsigned long len, bool add)
{
    unsigned long k;
    float x, y;
    float c1, s1;
    float c2, s2;
    float dc, ds;
    float *inp1, *inp2; 
    float *out1, *out2;

    memcpy (_port [OUT_W], _port [INP_W], len * sizeof (float));
    memcpy (_port [OUT_Z], _port [INP_Z], len * sizeof (float));

    c1 = _c1;
    s1 = _s1;
    c2 = _c2;
    s2 = _s2;
    calcpar (_port [CTL_AZIM][0]);

    inp1 = _port [INP_X];
    inp2 = _port [INP_Y];
    out1 = _port [OUT_X];
    out2 = _port [OUT_Y];
    k = len;
    dc = (_c1 - c1) / len;
    ds = (_s1 - s1) / len;
    while (k--)
    {
	c1 += dc;
	s1 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c1 * x + s1 * y;
        *out2++ = c1 * y - s1 * x;
    }

    inp1 = _port [INP_U];
    inp2 = _port [INP_V];
    out1 = _port [OUT_U];
    out2 = _port [OUT_V];
    k = len;
    dc = (_c2 - c2) / len;
    ds = (_s2 - s2) / len;
    while (k--)
    {
	c2 += dc;
	s2 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c2 * x + s2 * y;
        *out2++ = c2 * y - s2 * x;
    }
}



void Ladspa_Monopan22::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Monopan22::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f);
}


void Ladspa_Monopan22::calcpar (float az, float el)
{
    float ce; 

    az *= DEG2RAD;
    el *= DEG2RAD;
    ce = cosf (el);
    _xx = ce * cosf (-az);
    _yy = ce * sinf (-az);
    _zz = sinf (el);
    _rr = 1.5f * _zz * _zz - 0.5f;
    _ss = 2 * _xx * _zz;
    _tt = 2 * _yy * _zz;  
    _uu = _xx * _xx - _yy * _yy;
    _vv = 2 * _xx * _yy;
}


void Ladspa_Monopan22::runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, rr, ss, tt, uu, vv, dxx, dyy, dzz, drr, dss, dtt, duu, dvv; 
    float *in, *out_w, *out_x, *out_y, *out_z, *out_r, *out_s, *out_t, *out_u, *out_v;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    rr = _rr;
    ss = _ss;
    tt = _tt;
    uu = _uu;
    vv = _vv;
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]); 
    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;
    drr = (_rr - rr) / len;
    dss = (_ss - ss) / len;
    dtt = (_tt - tt) / len;
    duu = (_uu - uu) / len;
    dvv = (_vv - vv) / len;

    in = _port [INP];
    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];
    out_r = _port [OUT_R];
    out_s = _port [OUT_S];
    out_t = _port [OUT_T];
    out_u = _port [OUT_U];
    out_v = _port [OUT_V];

    while (len--)
    {
	xx += dxx;
	yy += dyy;
	zz += dzz;
	rr += drr;
	ss += dss;
	tt += dtt;
	uu += duu;
	vv += dvv;
        t = *in++;        
        *out_w++ = MIN3DB * t;
        *out_x++ = xx * t;
        *out_y++ = yy * t;
        *out_z++ = zz * t;
        *out_r++ = rr * t;
        *out_s++ = ss * t;
        *out_t++ = tt * t;
        *out_u++ = uu * t;
        *out_v++ = vv * t;
    }
}



void Ladspa_Rotator22::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Rotator22::active (bool act)
{
    if (act) calcpar (0.0f);
}


void Ladspa_Rotator22::calcpar (float az)
{
    az *= DEG2RAD;
    _c1 = cosf (az);
    _s1 = sinf (az);
    _c2 = _c1 * _c1 - _s1 * _s1;
    _s2 = 2 * _c1 * _s1;
}


void Ladspa_Rotator22::runproc (unsigned long len, bool add)
{
    unsigned long k;
    float x, y;
    float c1, s1;
    float c2, s2;
    float dc, ds;
    float *inp1, *inp2, *inp3, *inp4; 
    float *out1, *out2, *out3, *out4;

    memcpy (_port [OUT_W], _port [INP_W], len * sizeof (float));
    memcpy (_port [OUT_Z], _port [INP_Z], len * sizeof (float));
    memcpy (_port [OUT_R], _port [INP_R], len * sizeof (float));

    c1 = _c1;
    s1 = _s1;
    c2 = _c2;
    s2 = _s2;
    calcpar (_port [CTL_AZIM][0]);

    inp1 = _port [INP_X];
    inp2 = _port [INP_Y];
    inp3 = _port [INP_S];
    inp4 = _port [INP_T];
    out1 = _port [OUT_X];
    out2 = _port [OUT_Y];
    out3 = _port [OUT_S];
    out4 = _port [OUT_T];
    k = len;
    dc = (_c1 - c1) / len;
    ds = (_s1 - s1) / len;
    while (k--)
    {
	c1 += dc;
	s1 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c1 * x + s1 * y;
        *out2++ = c1 * y - s1 * x;
        x = *inp3++;
        y = *inp4++; 
        *out3++ = c1 * x + s1 * y;
        *out4++ = c1 * y - s1 * x;
    }

    inp1 = _port [INP_U];
    inp2 = _port [INP_V];
    out1 = _port [OUT_U];
    out2 = _port [OUT_V];
    k = len;
    dc = (_c2 - c2) / len;
    ds = (_s2 - s2) / len;
    while (k--)
    {
	c2 += dc;
	s2 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c2 * x + s2 * y;
        *out2++ = c2 * y - s2 * x;
    }
}



