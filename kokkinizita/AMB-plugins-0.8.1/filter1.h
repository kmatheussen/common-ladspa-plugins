/*
    Copyright (C) 2004-2006 Fons Adriaensen <fons@kokkinizita.net>
    
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


#ifndef __FILTER1_H
#define __FILTER1_H


/* --------------------------------------------------------------- 

Lowpass1

First order lowpass, -3dB at f3dB.

--------------------------------------------------------------- */

class Lowpass1
{
public:

    Lowpass1 (void) : _a (0), _z (0) {}
    ~Lowpass1 (void) {}

    void init (float fsam, float f3db);
    void reset (void) { _z = 0; }
    float process (float x)
    {
        float d;
        d = _a * (x - _z);
        x  = _z + d;
        _z =  x + d + 1e-20f;      
        return x;    
    }

    float    _a;
    float    _z;
};


/* --------------------------------------------------------------- 

Allpass1

First order allpass having 0, 90, 180 degrees phase shift at
resp. LF, fmid, HF.

--------------------------------------------------------------- */

class Allpass1
{
public:

    Allpass1 (void) : _d (0), _z (0) {}
    ~Allpass1 (void) {}

    void init (float fsam, float fmid);
    void reset (void) { _z = 0; }
    float process (float x)
    {
        float y;
        x =  x - _d * _z;
        y = _z + _d *  x;
        _z = x + 1e-20f;        
        return y;
    }

    float    _d;
    float    _z;
};


/* --------------------------------------------------------------- 

Pcshelf1

First order shelf filter having the same phase response as a
first order allpass set for 90 degrees at fmid.
Useful for phase aligned shelfs for Ambisonics decoders etc.
See shelf1-plot.cc for tests.

--------------------------------------------------------------- */

class Pcshelf1
{
public:

    Pcshelf1 (void) : _d1 (0), _d2 (0), _g (0), _z (0) {}
    ~Pcshelf1 (void) {}

    void init (float fsam, float fmid, float glf, float ghf);
    void reset (void) { _z = 0; }
    float process (float x)
    {
 	float y;
        x =  x - _d2 * _z;
        y = _z + _d1 *  x;
        _z = x + 1e-20f;        
        return _g * y;
    }

    float    _d1;
    float    _d2;
    float    _g;
    float    _z;
};



#endif

