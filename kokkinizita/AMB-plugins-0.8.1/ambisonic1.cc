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
#include "ambisonic1.h"


#define DEG2RAD 0.01745329f
#define MIN3DB  0.707107f


void Ladspa_Monopan11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Monopan11::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f);
}


void Ladspa_Monopan11::calcpar (float az, float el)
{
    float ce; 

    az *= DEG2RAD;
    el *= DEG2RAD;
    _zz = sinf (el);
    ce = cosf (el);
    _xx = ce * cosf (-az);
    _yy = ce * sinf (-az);
}


void Ladspa_Monopan11::runproc (unsigned long len, bool add)
{
    float t, xx, yy, zz, dxx, dyy, dzz; 
    float *in, *out_w, *out_x, *out_y, *out_z;

    xx = _xx;
    yy = _yy;
    zz = _zz;
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0]);
    dxx = (_xx - xx) / len;
    dyy = (_yy - yy) / len;
    dzz = (_zz - zz) / len;

    in = _port [INP];
    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];

    while (len--)
    {
	xx += dxx;
	yy += dyy;
	zz += dzz;
        t = *in++;        
        *out_w++ = MIN3DB * t;
        *out_x++ = xx * t;
        *out_y++ = yy * t;
        *out_z++ = zz * t;
    }
}



void Ladspa_Stereopan11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Stereopan11::active (bool act)
{
    if (act) calcpar (0.0f, 0.0f, 90.0f);
}


void Ladspa_Stereopan11::calcpar (float az, float el, float wd)
{
    float a, ce; 

    az *= DEG2RAD;
    el *= DEG2RAD;
    wd *= 0.5f * DEG2RAD;
    _zz = sinf (el);
    ce = cosf (el);
    a = (az - wd);
    _xl = ce * cosf (-a);
    _yl = ce * sinf (-a);
    a = (az + wd);
    _xr = ce * cosf (-a);
    _yr = ce * sinf (-a);
}


void Ladspa_Stereopan11::runproc (unsigned long len, bool add)
{
    float  xl, xr, yl, yr, zz, dxl, dxr, dyl, dyr, dzz, u, v; 
    float *in_l, *in_r, *out_w, *out_x, *out_y, *out_z;

    xl = _xl;
    xr = _xr;
    yl = _yl;
    yr = _yr;
    zz = _zz;
    calcpar (_port [CTL_AZIM][0], _port [CTL_ELEV][0], _port [CTL_WIDTH][0]);
    dxl = (_xl - xl) / len;
    dxr = (_xr - xr) / len;
    dyl = (_yl - yl) / len;
    dyr = (_yr - yr) / len;
    dzz = (_zz - zz) / len;

    in_l = _port [INP_L];
    in_r = _port [INP_R];
    out_w = _port [OUT_W];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];
    out_z = _port [OUT_Z];

    while (len--)
    {
	xl += dxl;
	xr += dxr;
	yl += dyl;
	yr += dyr;
	zz += dzz;
        u = *in_l++;        
        v = *in_r++;        
        *out_w++ = MIN3DB * (u + v);
        *out_z++ = zz * (u + v);
        *out_x++ = xl * u + xr * v;
        *out_y++ = yl * u + yr * v;
    }
}



void Ladspa_Rotator11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_Rotator11::active (bool act)
{
    if (act) calcpar (0.0f);
}


void Ladspa_Rotator11::calcpar (float az)
{
    az *= DEG2RAD;
    _c = cosf (az);
    _s = sinf (az);
}


void Ladspa_Rotator11::runproc (unsigned long len, bool add)
{

    float c, s, dc, ds, x, y;
    float *in_x, *in_y, *out_x, *out_y;

    memcpy (_port [OUT_W], _port [INP_W], len * sizeof (float));
    memcpy (_port [OUT_Z], _port [INP_Z], len * sizeof (float));

    c = _c;
    s = _s;
    calcpar (_port [CTL_AZIM][0]);
    dc = (_c - c) / len;
    ds = (_s - s) / len;

    in_x  = _port [INP_X];
    in_y  = _port [INP_Y];
    out_x = _port [OUT_X];
    out_y = _port [OUT_Y];

    while (len--)
    {
	c += dc;
	s += ds;
        x = *in_x++;
        y = *in_y++; 
        *out_x++ = c * x + s * y;
        *out_y++ = c * y - s * x;
    }
}



void Ladspa_SquareDec11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_SquareDec11::active (bool act)
{
    _wsh.reset ();
    _xsh.reset ();
    _ysh.reset ();
    _xlp.reset ();
    _ylp.reset ();
}


void Ladspa_SquareDec11::runproc (unsigned long len, bool add)
{
    int   m;
    float t, w, x, y;
    float *in_w, *in_x, *in_y;
    float *out_1, *out_2, *out_3, *out_4;

    m = 0;
    if (_port [CTL_SHELF][0] > 0)
    {
        m |= SHELF;
        if (   (_port [CTL_HFG1][0] != _hfg1) 
            || (_port [CTL_LFG1][0] != _lfg1) 
            || (_port [CTL_FREQ][0] != _freq)) 
	{
	    _hfg1 = _port [CTL_HFG1][0];        
	    _lfg1 = _port [CTL_LFG1][0];        
	    _freq = _port [CTL_FREQ][0];        
            _wsh.init (_fsam, _freq, sqrtf (_hfg1 / _lfg1), -1.0f);            
            _xsh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
            _ysh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
        }
    }
    else _hfg1 = _port [CTL_HFG1][0];              
    _mode = m & SHELF;

    if (_dist != _port [CTL_DIST][0])
    {
	_dist = _port [CTL_DIST][0];
        t = 54.0f / _dist;
        _xlp.init (_fsam, t);
        _ylp.init (_fsam, t);
    }

    in_w = _port [INP_W];
    in_x = _port [INP_X];
    in_y = _port [INP_Y];
    out_1 = _port [OUT_1];
    out_2 = _port [OUT_2];
    out_3 = _port [OUT_3];
    out_4 = _port [OUT_4];

    if (_port [CTL_FRONT][0])
    {
        if (_mode & SHELF)
	{
	    while (len--)
	    {
		x = 0.7071f * *in_x++;
		x = _xsh.process (x - _xlp.process (x));  
		y = 0.7071f * *in_y++;
		y = _ysh.process (y - _ylp.process (y));  
		w = _wsh.process (*in_w++);
		*out_1++ = w + x;
		*out_2++ = w - y;
		*out_3++ = w - x;
		*out_4++ = w + y;
	    }
	}
	else
	{
	    while (len--)
	    {
		x = 0.7071f * *in_x++;
		x = _hfg1 * (x - _xlp.process (x));  
		y = 0.7071f * *in_y++;
		y = _hfg1 * (y - _ylp.process (y));  
		w = *in_w++;
		*out_1++ = w + x;
		*out_2++ = w - y;
		*out_3++ = w - x;
		*out_4++ = w + y;
	    }
	}
    }
    else
    {
	if (_mode & SHELF)
	{
	    while (len--)
	    {
		x = 0.5f * *in_x++;
		x = _xsh.process (x - _xlp.process (x));  
		y = 0.5f * *in_y++;
		y = _ysh.process (y - _ylp.process (y));  
		w = _wsh.process (*in_w++);
		*out_1++ = w + x + y;
		*out_2++ = w + x - y;
		*out_3++ = w - x - y;
		*out_4++ = w - x + y;
	    }
	}
	else
	{
	    while (len--)
	    {
		x = 0.5f * *in_x++;
		x = _hfg1 * (x - _xlp.process (x));  
		y = 0.5f * *in_y++;
		y = _hfg1 * (y - _ylp.process (y));  
		w = *in_w++;
		*out_1++ = w + x + y;
		*out_2++ = w + x - y;
		*out_3++ = w - x - y;
		*out_4++ = w - x + y;
	    }
	}
    }
}


void Ladspa_HexaDec11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_HexaDec11::active (bool act)
{
    _wsh.reset ();
    _xsh.reset ();
    _ysh.reset ();
    _xlp.reset ();
    _ylp.reset ();
}


void Ladspa_HexaDec11::runproc (unsigned long len, bool add)
{

    int   m;
    float t, w, x, y;
    float *in_w, *in_x, *in_y;
    float *out_1, *out_2, *out_3, *out_4, *out_5, *out_6;

    m = 0;
    if (_port [CTL_SHELF][0] > 0)
    {
        m |= SHELF;
        if (   (_port [CTL_HFG1][0] != _hfg1) 
            || (_port [CTL_LFG1][0] != _lfg1) 
            || (_port [CTL_FREQ][0] != _freq)) 
	{
	    _hfg1 = _port [CTL_HFG1][0];        
	    _lfg1 = _port [CTL_LFG1][0];        
	    _freq = _port [CTL_FREQ][0];        
            _wsh.init (_fsam, _freq, sqrtf (_hfg1 / _lfg1), -1.0f);            
            _xsh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
            _ysh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
        }
    }
    else _hfg1 = _port [CTL_HFG1][0];              
    _mode = m & SHELF;

    if (_dist != _port [CTL_DIST][0])
    {
	_dist = _port [CTL_DIST][0];
        t = 54.0f / _dist;
        _xlp.init (_fsam, t);
        _ylp.init (_fsam, t);
    }

    in_w = _port [INP_W];
    in_x = _port [INP_X];
    in_y = _port [INP_Y];
    out_1 = _port [OUT_1];
    out_2 = _port [OUT_2];
    out_3 = _port [OUT_3];
    out_4 = _port [OUT_4];
    out_5 = _port [OUT_5];
    out_6 = _port [OUT_6];

    if (_port [CTL_FRONT][0])
    {
	if (_mode & SHELF)
	{
	    while (len--)
	    {
		x = 0.7071f * *in_x++;
		x = _xsh.process (x - _xlp.process (x));  
		y = 0.6124f * *in_y++;
		y = _ysh.process (y - _ylp.process (y));  
		w = _wsh.process (*in_w++);
		*out_1++ = w + x;
		*out_2++ = w + 0.5f * x - y;
		*out_3++ = w - 0.5f * x - y;
		*out_4++ = w - x;
		*out_5++ = w - 0.5f * x + y;
		*out_6++ = w + 0.5f * x + y;
	    }
	}
	else
	{
	    while (len--)
	    {
		x = 0.7071f * *in_x++;
		x = _hfg1 * (x - _xlp.process (x));  
		y = 0.6124f * *in_y++;
		y = _hfg1 * (y - _ylp.process (y));  
		w = *in_w++;
		*out_1++ = w + x;
		*out_2++ = w + 0.5f * x - y;
		*out_3++ = w - 0.5f * x - y;
		*out_4++ = w - x;
		*out_5++ = w - 0.5f * x + y;
		*out_6++ = w + 0.5f * x + y;
	    }
	}
    }
    else
    {
	if (_mode & SHELF)
	{
	    while (len--)
	    {
		x = 0.6124f * *in_x++;
		x = _xsh.process (x - _xlp.process (x));  
		y = 0.7071f * *in_y++;
		y = _ysh.process (y - _ylp.process (y));  
		w = _wsh.process (*in_w++);
		*out_1++ = w + x + 0.5f * y;
		*out_2++ = w + x - 0.5f * y;
		*out_3++ = w - y;
		*out_4++ = w - x - 0.5f * y;
		*out_5++ = w - x + 0.5f * y;
		*out_6++ = w + y;
	    }
	}
	else
	{
	    while (len--)
	    {
		x = 0.6124f * *in_x++;
		x = _hfg1 * (x - _xlp.process (x));  
		y = 0.7071f * *in_y++;
		y = _hfg1 * (y - _ylp.process (y));  
		w = *in_w++;
		*out_1++ = w + x + 0.5f * y;
		*out_2++ = w + x - 0.5f * y;
		*out_3++ = w - y;
		*out_4++ = w - x - 0.5f * y;
		*out_5++ = w - x + 0.5f * y;
		*out_6++ = w + y;
	    }
	}
    }
}


void Ladspa_CubeDec11::setport (unsigned long port, LADSPA_Data *data)
{
    _port [port] = data;
}


void Ladspa_CubeDec11::active (bool act)
{
    _wsh.reset ();
    _xsh.reset ();
    _ysh.reset ();
    _zsh.reset ();
    _xlp.reset ();
    _ylp.reset ();
    _zlp.reset ();
}


void Ladspa_CubeDec11::runproc (unsigned long len, bool add)
{
    int   m;
    float t, w, x, y, z;
    float *in_w, *in_x, *in_y, *in_z;
    float *out_1, *out_2, *out_3, *out_4, *out_5, *out_6, *out_7, *out_8;

    m = 0;
    if (_port [CTL_SHELF][0] > 0)
    {
        m |= SHELF;
        if (   (_port [CTL_HFG1][0] != _hfg1) 
            || (_port [CTL_LFG1][0] != _lfg1) 
            || (_port [CTL_FREQ][0] != _freq)) 
	{
	    _hfg1 = _port [CTL_HFG1][0];        
	    _lfg1 = _port [CTL_LFG1][0];        
	    _freq = _port [CTL_FREQ][0];        
            _wsh.init (_fsam, _freq, sqrtf (_hfg1 / _lfg1), -1.0f);            
            _xsh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
            _ysh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
            _zsh.init (_fsam, _freq, sqrtf (_hfg1 * _lfg1), -_hfg1);            
        }
    }
    else _hfg1 = _port [CTL_HFG1][0];              
    _mode = m & SHELF;

    if (_dist != _port [CTL_DIST][0])
    {
	_dist = _port [CTL_DIST][0];
        t = 54.0f / _dist;
        _xlp.init (_fsam, t);
        _ylp.init (_fsam, t);
        _zlp.init (_fsam, t);
    }

    in_w = _port [INP_W];
    in_x = _port [INP_X];
    in_y = _port [INP_Y];
    in_z = _port [INP_Z];
    out_1 = _port [OUT_1];
    out_2 = _port [OUT_2];
    out_3 = _port [OUT_3];
    out_4 = _port [OUT_4];
    out_5 = _port [OUT_5];
    out_6 = _port [OUT_6];
    out_7 = _port [OUT_7];
    out_8 = _port [OUT_8];

    if (_mode & SHELF)
    {
	while (len--)
	{
	    x = 0.4082f * *in_x++;
	    x = _xsh.process (x - _xlp.process (x));  
	    y = 0.4082f * *in_y++;
	    y = _ysh.process (y - _ylp.process (y));  
	    z = 0.4082f * *in_z++;
	    z = _zsh.process (z - _zlp.process (z));  
	    w = _wsh.process (*in_w++);
	    *out_1++ = w + x + y - z;
	    *out_2++ = w + x - y - z;
	    *out_3++ = w - x - y - z;
	    *out_4++ = w - x + y - z;
	    *out_5++ = w + x + y + z;
	    *out_6++ = w + x - y + z;
	    *out_7++ = w - x - y + z;
	    *out_8++ = w - x + y + z;
	}
    }
    else
    {
	while (len--)
	{
	    x = 0.4082f * *in_x++;
	    x = _hfg1 * (x - _xlp.process (x));  
	    y = 0.4082f * *in_y++;
	    y = _hfg1 * (y - _ylp.process (y));  
	    z = 0.4082f * *in_z++;
	    z = _hfg1 * (z - _zlp.process (z));  
	    w = *in_w++;
	    *out_1++ = w + x + y - z;
	    *out_2++ = w + x - y - z;
	    *out_3++ = w - x - y - z;
	    *out_4++ = w - x + y - z;
	    *out_5++ = w + x + y + z;
	    *out_6++ = w + x - y + z;
	    *out_7++ = w - x - y + z;
	    *out_8++ = w - x + y + z;
	}
    }
}

