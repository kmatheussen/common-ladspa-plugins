// -----------------------------------------------------------------------
//
//  Copyright (C) 2003-2013 Fons Adriaensen <fons@linuxaudio.org>
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
#include "greverb.h"


void Diffuser::init (unsigned long size, float c)
{
    _size = size;
    _data = new float [size];
    _c = c;
    reset ();
}


void Diffuser::reset (void)
{
    memset (_data, 0, _size * sizeof (float));
    _i = 0;
}


void Diffuser::fini (void)
{
    delete[] _data;
}


void QuadFDN::init (unsigned long size)
{
    _size = size;
    for (int j = 0; j < 4; j++)
    {
        _data [j] = new float [size]; 
        _g [j] = 0;
        _d [j] = 0; 
    }
    _c = 1;
    reset ();
}       


void QuadFDN::reset (void)
{
    for (int j = 0; j < 4; j++)
    {
        memset (_data [j], 0, _size * sizeof (float));
        _y [j] = 0;
    }  
    _i = 0;
}       


void QuadFDN::fini (void)
{
    for (int j = 0; j < 4; j++) delete[] _data [j]; 
}


void MTDelay::init (unsigned long size)
{
    _size = size;
    _data = new float [size];
    for (int j = 0; j < 4; j++) _d [j] = 0;  
    _c = 1;
    reset ();
}


void MTDelay::reset (void)
{
    memset (_data, 0, _size * sizeof (float));
    for (int j = 0; j < 4; j++) _y [j] = 0;
    _z = 0;
    _i = 0; 
}


void MTDelay::fini (void)
{
    delete[] _data;
}


Greverb::Greverb (unsigned long rate) :
    _rate (rate),
    _roomsize (0.0f),
    _revbtime (0.0f),
    _ipbandw (0.8f),
    _damping (0.2f),
    _refllev (0.3f),
    _taillev (0.3f)
{
    unsigned long n;

    n = (unsigned long)(rate * 0.015f);
    _dif0.init (n, 0.450f);
    _dif1.init (n, 0.450f);
    _qfdn.init ((unsigned long)(rate * MAX_ROOMSIZE / 340.0f));
    n = (unsigned long)(_qfdn._size * 0.450f);
    _del0.init (n);
    _del1.init (n);
    n = (unsigned long)(rate * 0.124f);
    _dif1L.init ((unsigned long)(n * 0.2137f), 0.5f);
    _dif2L.init ((unsigned long)(n * 0.3753f), 0.5f);
    _dif3L.init (n - _dif1L._size - _dif2L._size, 0.5f);
    _dif1R.init ((unsigned long)(n * 0.1974f), 0.5f);
    _dif2R.init ((unsigned long)(n * 0.3526f), 0.5f);
    _dif3R.init (n - _dif1R._size - _dif2R._size, 0.5f);

    set_ipbandw (0.8f);
    set_damping (0.2f);
    set_roomsize (50.0f);
    set_revbtime (3.0f);
}


Greverb::~Greverb (void)
{
    _dif0.fini ();  
    _dif1.fini ();  
    _qfdn.fini ();
    _del0.fini ();;  
    _del1.fini ();;  
    _dif1L.fini ();  
    _dif2L.fini ();  
    _dif3L.fini ();  
    _dif1R.fini ();  
    _dif2R.fini ();  
    _dif3R.fini ();  
}


void Greverb::reset (void)
{
    // Clear all delay lines and filter states.
    // Current parameters are preserved.
    _dif0.reset ();  
    _dif1.reset ();  
    _qfdn.reset ();
    _del0.reset ();  
    _del1.reset ();  
    _dif1L.reset ();  
    _dif2L.reset ();  
    _dif3L.reset ();  
    _dif1R.reset ();  
    _dif2R.reset ();  
    _dif3R.reset ();  
}


void Greverb::set_roomsize (float R)
{
    if (R > MAX_ROOMSIZE) R = MAX_ROOMSIZE;   
    if (R < MIN_ROOMSIZE) R = MIN_ROOMSIZE;   
    if (fabsf (_roomsize - R) < 0.5f) return;
    _roomsize = R; 
    _qfdn._d [0] = (unsigned long)(_rate * R / 340.0f);
    _qfdn._d [1] = (unsigned long)(_qfdn._d [0] * 0.816490f);
    _qfdn._d [2] = (unsigned long)(_qfdn._d [0] * 0.707100f);
    _qfdn._d [3] = (unsigned long)(_qfdn._d [0] * 0.632450f);

    _del0._d [0] = (unsigned long)(_qfdn._d [0] * 0.100f);
    _del0._d [1] = (unsigned long)(_qfdn._d [0] * 0.164f);
    _del0._d [2] = (unsigned long)(_qfdn._d [0] * 0.270f);
    _del0._d [3] = (unsigned long)(_qfdn._d [0] * 0.443f);

    _del1._d [0] = (unsigned long)(_qfdn._d [0] * 0.087f);
    _del1._d [1] = (unsigned long)(_qfdn._d [0] * 0.149f);
    _del1._d [2] = (unsigned long)(_qfdn._d [0] * 0.256f);
    _del1._d [3] = (unsigned long)(_qfdn._d [0] * 0.440f);
    set_params ();    
}


void Greverb::set_revbtime (float T)
{
    if (T > MAX_REVBTIME) T = MAX_REVBTIME;   
    if (T < MIN_REVBTIME) T = MIN_REVBTIME;   
    if (fabsf (_revbtime - T) < 0.05f) return;
    _revbtime = T; 
    set_params ();
}


void Greverb::set_ipbandw (float B)
{
    if (B < 0.1f) B = 0.1f;
    if (B > 1.0f) B = 1.0f;
    _del1._c = _del0._c = _ipbandw = B;
}


void Greverb::set_damping (float D)
{
    if (D < 0.0f) D = 0.0f;
    if (D > 0.9f) D = 0.9f;
    _damping = D;
    _qfdn._c = 1.0f - _damping;
}


void Greverb::set_params (void)
{
    double a;

    a = powf (0.001f, 1.0f / (_rate * _revbtime));
    for (int j = 0; j < 4; j++)
    {
        _qfdn._g [j] = powf (a, (double)(_qfdn._d [j]));
    }        
}


void Greverb::process (unsigned long n, float *x0, float *x1, float *y0, float *y1)
{
    float z, z0, z1;

    while (n--)
    {
        _del0.process (_dif0.process (*x0 + 1e-20));
        _del1.process (_dif1.process (*x1 + 1e-20));
        _qfdn.process (_del0._y, _del1._y);
        z = _taillev * (_qfdn._y [0] + _qfdn._y [1] + _qfdn._y [2] + _qfdn._y [3]);     
        z0 = _refllev * (_del0._y [0] - _del0._y [1] + _del0._y [2] - _del0._y [3]);     
        z1 = _refllev * (_del1._y [0] - _del1._y [1] + _del1._y [2] - _del1._y [3]);     
        *y0++ = _dif3L.process (_dif2L.process (_dif1L.process (z + z0))) + _dryslev * *x0++;
        *y1++ = _dif3R.process (_dif2R.process (_dif1R.process (z + z1))) + _dryslev * *x1++;
    }
}
