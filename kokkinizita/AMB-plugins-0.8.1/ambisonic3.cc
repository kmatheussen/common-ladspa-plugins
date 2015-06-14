/*
    Copyright (C) 2009 Fons Adriaensen <fons@kokkinizita.net>
    and Jörn Nettingsmeier <nettings@stackingdwarves.net>
    
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
#include "ambisonic3.h"


#define DEG2RAD 0.01745329f
#define MIN3DB  0.707107f


void Ladspa_Monopan31::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Monopan31::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f);
}


void Ladspa_Monopan31::calcpar (float az, float el)
{
    float t, x2, y2;

    az *= DEG2RAD;
    el *= DEG2RAD;
    t = cosf (el);
    _xx = t * cosf (-az);
    _yy = t * sinf (-az);
    _zz = sinf (el);
    x2 = _xx * _xx;
    y2 = _yy * _yy;
    _uu = x2 - y2;
    _vv = 2 * _xx * _yy;
    _pp = (x2 - 3 * y2) * _xx;
    _qq = (3 * x2 - y2) * _yy;
}


void Ladspa_Monopan31::runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, uu, vv, pp, qq;
    float dxx, dyy, dzz, duu, dvv, dpp, dqq;
           
    float *in, *out_w, *out_x, *out_y, *out_z, *out_u, *out_v, *out_p, *out_q;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    uu = _uu;
    vv = _vv;
    pp = _pp;
    qq = _qq;
    
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]);

    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;
    duu = (_uu - uu) / len;
    dvv = (_vv - vv) / len;
    dpp = (_pp - pp) / len;
    dqq = (_qq - qq) / len;
    
    in = _port [INP];

    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];
    out_u = _port [OUT_U];
    out_v = _port [OUT_V];
    out_p = _port [OUT_P];
    out_q = _port [OUT_Q];
    
    while (len--)
    {
	xx += dxx;
	yy += dyy;
	zz += dzz;
	uu += duu;
	vv += dvv;
	pp += dpp;
	qq += dqq;
	
        t = *in++;        
        *out_w++ = MIN3DB * t;
        *out_x++ = xx * t;
        *out_y++ = yy * t;
        *out_z++ = zz * t;
        *out_u++ = uu * t;
        *out_v++ = vv * t;
        *out_p++ = pp * t;
        *out_q++ = qq * t;
    }
}



void Ladspa_Rotator31::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Rotator31::active (bool act)
{
    if (act) calcpar (0.0f);
}


void Ladspa_Rotator31::calcpar (float az)
{
    az *= DEG2RAD;
    _c1 = cosf (az);
    _s1 = sinf (az);
    _c2 = _c1 * _c1 - _s1 * _s1;
    _s2 = 2 * _c1 * _s1;
    _c3 = _c2 * _c1 - _s2 * _s1;
    _s3 = _c2 * _s1 + _c1 * _s2;
}


void Ladspa_Rotator31::runproc (unsigned long len, bool add)
{
    int    k;
    float  c1, s1, c2, s2, c3, s3;
    float  x, y, dc, ds;
    float  *inp1, *inp2, *out1, *out2;

   // W and Z are invariant under rotation around the z axis.

    memcpy (_port [OUT_W], _port [INP_W], len * sizeof (float));
    memcpy (_port [OUT_Z], _port [INP_Z], len * sizeof (float));
   
    c1 = _c1;
    s1 = _s1;
    c2 = _c2;
    s2 = _s2;
    c3 = _c3;
    s3 = _s3; 
    
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

    inp1 = _port [INP_P];
    inp2 = _port [INP_Q];
    out1 = _port [OUT_P];
    out2 = _port [OUT_Q];
    k = len;
    dc = (_c3 - c3) / len;
    ds = (_s3 - s3) / len;
    while (k--)
    {
	c3 += dc;
	s3 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c3 * x + s3 * y;
        *out2++ = c3 * y - s3 * x;
    }
}




void Ladspa_Monopan33::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Monopan33::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f);
}


void Ladspa_Monopan33::calcpar (float az, float el)
{
    float t, x2, y2, z2;

    az *= DEG2RAD;
    el *= DEG2RAD;
    t = cosf (el);
    _xx = t * cosf (-az);
    _yy = t * sinf (-az);
    _zz = sinf (el);
    x2 = _xx * _xx;
    y2 = _yy * _yy;
    z2 = _zz * _zz;
    _uu = x2 - y2;
    _vv = 2 * _xx * _yy;
    _ss = 2 * _zz * _xx;
    _tt = 2 * _zz * _yy;
    _rr = (3 * z2 - 1) / 2;
    _pp = (x2 - 3 * y2) * _xx;
    _qq = (3 * x2 - y2) * _yy;
    t = 2.598076f * _zz; 
    _nn = t * _uu;
    _oo = t * _vv;
    t = 0.726184f * (5 * z2 - 1);
    _ll = t * _xx;
    _mm = t * _yy;
    _kk = _zz * (5 * z2 - 3) / 2;
}


void Ladspa_Monopan33::runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, rr, ss, tt, uu, vv, kk, ll, mm, nn, oo, pp, qq;
    float dxx, dyy, dzz, drr, dss, dtt, duu, dvv, dkk, dll, dmm, dnn, doo, dpp, dqq;
    float *in, *out_w, *out_x, *out_y, *out_z, *out_r, *out_s, *out_t, *out_u, *out_v,
          *out_k, *out_l, *out_m, *out_n, *out_o, *out_p, *out_q;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    rr = _rr;
    ss = _ss;
    tt = _tt;
    uu = _uu;
    vv = _vv;
    kk = _kk; 
    ll = _ll; 
    mm = _mm; 
    nn = _nn; 
    oo = _oo;
    pp = _pp;
    qq = _qq;
    
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]);

    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;
    drr = (_rr - rr) / len;
    dss = (_ss - ss) / len;
    dtt = (_tt - tt) / len;
    duu = (_uu - uu) / len;
    dvv = (_vv - vv) / len;
    dkk = (_kk - kk) / len;
    dll = (_ll - ll) / len;
    dmm = (_mm - mm) / len;
    dnn = (_nn - nn) / len;
    doo = (_oo - oo) / len;
    dpp = (_pp - pp) / len;
    dqq = (_qq - qq) / len;
    
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
    out_k = _port [OUT_K];
    out_l = _port [OUT_L];
    out_m = _port [OUT_M];
    out_n = _port [OUT_N];
    out_o = _port [OUT_O];
    out_p = _port [OUT_P];
    out_q = _port [OUT_Q];
    
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
	kk += dkk;
	ll += dll;
	mm += dmm;
	nn += dnn;
	oo += doo;
	pp += dpp;
	qq += dqq;
	
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
        *out_k++ = kk * t;
        *out_l++ = ll * t;
        *out_m++ = mm * t;
        *out_n++ = nn * t;
        *out_o++ = oo * t;
        *out_p++ = pp * t;
        *out_q++ = qq * t;
    }
}


void Ladspa_Rotator33::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Rotator33::active (bool act)
{
    if (act) calcpar (0.0f);
}


void Ladspa_Rotator33::calcpar (float az)
{
    az *= DEG2RAD;
    _c1 = cosf (az);
    _s1 = sinf (az);
    _c2 = _c1 * _c1 - _s1 * _s1;
    _s2 = 2 * _c1 * _s1;
    _c3 = _c2 * _c1 - _s2 * _s1;
    _s3 = _c2 * _s1 + _c1 * _s2;
}


void Ladspa_Rotator33::runproc (unsigned long len, bool add)
{
    int    k;
    float  c1, s1, c2, s2, c3, s3;
    float  x, y, dc, ds;
    float  *inp1, *inp2, *inp3, *inp4, *inp5, *inp6;
    float  *out1, *out2, *out3, *out4, *out5, *out6;

    // W, Z, R and K are invariant under rotation around the z axis.

    memcpy (_port [OUT_W], _port [INP_W], len * sizeof (LADSPA_Data));
    memcpy (_port [OUT_Z], _port [INP_Z], len * sizeof (LADSPA_Data));
    memcpy (_port [OUT_R], _port [INP_R], len * sizeof (LADSPA_Data));
    memcpy (_port [OUT_K], _port [INP_K], len * sizeof (LADSPA_Data));
   
    c1 = _c1;
    s1 = _s1;
    c2 = _c2;
    s2 = _s2;
    c3 = _c3;
    s3 = _s3; 
    
    calcpar (_port [CTL_AZIM][0]);

    inp1 = _port [INP_X];
    inp2 = _port [INP_Y];
    inp3 = _port [INP_S];
    inp4 = _port [INP_T];
    inp5 = _port [INP_L];
    inp6 = _port [INP_M];
    out1 = _port [OUT_X];
    out2 = _port [OUT_Y];
    out3 = _port [OUT_S];
    out4 = _port [OUT_T];
    out5 = _port [OUT_L];
    out6 = _port [OUT_M];
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
        x = *inp5++;
        y = *inp6++; 
        *out5++ = c1 * x + s1 * y;
        *out6++ = c1 * y - s1 * x;
    }

    inp1 = _port [INP_U];
    inp2 = _port [INP_V];
    inp3 = _port [INP_N];
    inp4 = _port [INP_O];
    out1 = _port [OUT_U];
    out2 = _port [OUT_V];
    out3 = _port [OUT_N];
    out4 = _port [OUT_O];
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
        x = *inp3++;
        y = *inp4++; 
        *out3++ = c2 * x + s2 * y;
        *out4++ = c2 * y - s2 * x;
    }

    inp1 = _port [INP_P];
    inp2 = _port [INP_Q];
    out1 = _port [OUT_P];
    out2 = _port [OUT_Q];
    k = len;
    dc = (_c3 - c3) / len;
    ds = (_s3 - s3) / len;
    while (k--)
    {
	c3 += dc;
	s3 += ds;
        x = *inp1++;
        y = *inp2++; 
        *out1++ = c3 * x + s3 * y;
        *out2++ = c3 * y - s3 * x;
    }
}


