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


#ifndef __GREVERB_H
#define __GREVERB_H


class Diffuser
{
private:
    
    friend class Greverb;

    void init (unsigned long size, float c);
    void reset (void);
    void fini (void);

    float process (float x)
    {
        float w;
 
        w = x - _c * _data [_i];
        x = _data [_i] + _c * w;
        _data [_i] = w;
        if (++_i == _size) _i = 0;
        return x;
    }

    float          *_data;
    unsigned long   _size;
    unsigned long   _i;      // sample index
    float           _c;      // feedback
};


class QuadFDN
{
private:
    
    friend class Greverb;

    void init (unsigned long size);
    void reset (void);
    void fini (void);

    void process (float *x0, float *x1)
    {	
	int   j;
        long  k;

        for (j = 0; j < 4; j++)
	{
            k = _i - _d [j];
            if (k < 0) k += _size;
            _y [j] += _c * (_g [j] * _data [j][k] - _y [j]);
        }         
        _data [0][_i] = x0 [0] + x1 [0] + 0.5 * ( _y [0] + _y [1] - _y [2] - _y [3]);        
        _data [1][_i] = x0 [1] + x1 [1] + 0.5 * ( _y [0] - _y [1] - _y [2] + _y [3]);        
        _data [2][_i] = x0 [2] + x1 [2] + 0.5 * (-_y [0] + _y [1] - _y [2] + _y [3]);        
        _data [3][_i] = x0 [3] + x1 [3] + 0.5 * ( _y [0] + _y [1] + _y [2] + _y [3]);        
        if (++_i == _size) _i = 0;
    }          

    float          *_data [4];
    unsigned long   _size;
    float           _g [4];  // gain
    float           _y [4];  // filtered output
    unsigned long   _d [4];  // delay
    unsigned long   _i;      // input index
    float           _c;      // damping
};


class MTDelay
{
private:
    
    friend class Greverb;

    void init (unsigned long size);
    void reset (void);
    void fini (void);

    void process (float x)
    { 
        int  j;
        long k;

        for (j = 0; j < 4; j++)
	{
            k = _i - _d [j];
            if (k < 0) k += _size;
            _y [j] = _data [k];
	}
        _z += _c * (x - _z);
        _data [_i] = _z;
        if (++_i == _size) _i = 0;
    }

    float          *_data;
    unsigned long   _size;
    float           _y [4];  // output
    unsigned long   _d [4];  // delay
    unsigned long   _i;      // input index 
    float           _c;      // damping;
    float           _z;      // filter state
} ;
   


class Greverb
{
public:

    enum 
    {
        MIN_ROOMSIZE = 5,
        MAX_ROOMSIZE = 150, 
        MIN_REVBTIME = 1,
        MAX_REVBTIME = 20
    };

    Greverb (unsigned long rate);
    ~Greverb (void);

    void reset (void);
    void set_roomsize (float roomsize);
    void set_revbtime (float revbtime);
    void set_ipbandw (float ipbandw);
    void set_damping (float damping);
    void set_dryslev (float refllev) { _dryslev = refllev; }
    void set_refllev (float refllev) { _refllev = refllev; }
    void set_taillev (float taillev) { _taillev = taillev; }
    void process (unsigned long n, float *x0, float *x1, float *y0, float *y1);

private:

    void set_params (void);

    unsigned long  _rate;

    float          _roomsize;
    float          _revbtime;
    float          _ipbandw;
    float          _damping;
    float          _dryslev;
    float          _refllev;    
    float          _taillev;    

    Diffuser       _dif0;
    Diffuser       _dif1;
    MTDelay        _del0;
    MTDelay        _del1;
    QuadFDN        _qfdn;
    Diffuser       _dif1L;    
    Diffuser       _dif2L;    
    Diffuser       _dif3L;    
    Diffuser       _dif1R;    
    Diffuser       _dif2R;    
    Diffuser       _dif3R;    
};


#endif
