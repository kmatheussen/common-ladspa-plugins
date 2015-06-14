/*
    Copyright (C) 2010 Fons Adriaensen <fons@kokkinizita.net>
    
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


#ifndef __ALLPASS22_H
#define __ALLPASS22_H


// Two second order allpass sections in series.
//
class Allpass22
{
public:

    Allpass22 (void) { reset (); }
    void reset (void) { _z1 = _z2 = _z3 = _z4 = 0; }
    void prepare (float f1, float b1, float f2, float b2);
    void process (int n, float *inp, float *out);

    static int initquad (Allpass22 *A, Allpass22 *B, float fsam);

private:

    float _c1, _c2, _c3, _c4;
    float _z1, _z2, _z3, _z4;

    static float quad44real [4];
    static float quad44imag [4];
    static float quad48real [4];
    static float quad48imag [4];
    static float quad96real [4];
    static float quad96imag [4];
};


#endif
