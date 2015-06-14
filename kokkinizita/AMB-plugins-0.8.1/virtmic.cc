//  -----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2009 Fons Adriaensen <fons@kokkinizita.net>
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
//  -----------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>
#include <math.h>
#include "virtmic.h"


#define TWOPI 6.283185f


Virtmic::Virtmic (void) :
    _azim (0),
    _azim1 (0),
    _elev (0),
    _elev1 (0),
    _angle (0),
    _angle1 (0),
    _direc (0),
    _direc1 (0),
    _csw (0),
    _csx (0),
    _csy (0),
    _csz (0),
    _cdx (0),
    _cdy (0)
{
}   


Virtmic::~Virtmic (void)
{
}


void Virtmic::process (int n, float *W, float *X, float *Y, float *Z, float *L, float *R)
{
    int    i, k;
    float  w, dw, x, dx, y, dy, z, dz;
    float  ca, sa, ce, se, cv, sv;
    float  S [80];
    float  D [80];

    while (n)
    {
	k = (n > 80) ? 64 : n;
        if (  circheck (_azim, _azim1)
            + lincheck (_elev, _elev1)
            + lincheck (_angle, _angle1)
            + lincheck (_direc, _direc1))
	{                
            ca = cosf (TWOPI * _azim);
            sa = sinf (TWOPI * _azim);
            ce = cosf (TWOPI * _elev);
            se = sinf (TWOPI * _elev);
            cv = cosf (TWOPI * _angle);
            sv = sinf (TWOPI * _angle);

	    w = _csw;
	    x = _csx;
	    y = _csy;
	    z = _csz;
	    dw = diff (k, w, _csw = 0.707107f * (1 - _direc));
	    dx = diff (k, x, _csx = _direc * ca * ce * cv);
            dy = diff (k, y, _csy = _direc * sa * ce * cv);
            dz = diff (k, z, _csz = _direc * cv * se);
    	    for (i = 0; i < k; i++)
    	    {
		w += dw;
                x += dx;
                y += dy;
                z += dz;
		S [i] = w * W [i] + x * X [i] + y * Y [i] + z * Z [i]; 
    	    }

	    x = _cdx;
	    y = _cdy;
            dx = diff (k, x, _cdx = -_direc * sa * sv);
	    dy = diff (k, y, _cdy =  _direc * ca * sv);
   	    for (i = 0; i < k; i++)
   	    {
                x += dx;
                y += dy;
		D [i] = x * X [i] + y * Y [i];
            }
	}
        else
	{
   	    for (i = 0; i < k; i++)
	    {
                S [i] = _csw * W [i] + _csx * X [i] + _csy * Y [i] + _csz * Z [i]; 
                D [i] = _cdx * X [i] + _cdy * Y [i];
	    }
	}

        for (i = 0; i < k; i++)
	{
	    *L++ = S [i] + D [i]; 
	    *R++ = S [i] - D [i]; 
	}		

        W += k;
        X += k;
        Y += k;           
        Z += k;
        n -= k;
    }
}

