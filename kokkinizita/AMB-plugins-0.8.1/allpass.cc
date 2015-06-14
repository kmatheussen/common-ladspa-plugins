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


#include <math.h>
#include "allpass.h"


void Allpass22::prepare (float f1, float b1, float f2, float b2)
{
    f1 *= float (M_PI);
    b1 *= f1;
    _c1 = -cosf (2 * f1);
    _c2 = (1 - b1) / (1 + b1);
    f2 *= float (M_PI);
    b2 *= f2;
    _c3 = -cosf (2 * f2);
    _c4 = (1 - b2) / (1 + b2);
}


void Allpass22::process (int n, float *inp, float *out)
{
    float x, y, z1, z2, z3, z4;

    z1 = _z1;
    z2 = _z2;
    z3 = _z3;
    z4 = _z4;
    while (n--)
    {
	x = *inp++;
	y = x - _c2 * z2;
	x = z2 + _c2 * y;
	y -= _c1 * z1;
	z2 = z1 + _c1 * y;
	z1 = y + 1e-20f;
	y = x - _c4 * z4;
	x = z4 + _c4 * y;
	y -= _c3 * z3;
	z4 = z3 + _c3 * y;
	z3 = y + 1e-20f;
	*out++ = x;
    }
    _z1 = z1;
    _z2 = z2;
    _z3 = z3;
    _z4 = z4;
}


float Allpass22::quad44real [4] = {  41.0f, 4.00f,  5.10e3f, 3.35f };
float Allpass22::quad44imag [4] = { 153.0f, 3.50f, 13.80e3f, 2.00f };
float Allpass22::quad48real [4] = {  41.0f, 4.00f,  5.05e3f, 3.40f };
float Allpass22::quad48imag [4] = { 153.0f, 3.50f, 14.20e3f, 2.20f };
float Allpass22::quad96real [4] = {  41.0f, 4.00f,  5.50e3f, 3.40f };
float Allpass22::quad96imag [4] = { 155.0f, 3.65f, 18.00e3f, 3.00f };


int Allpass22::initquad (Allpass22 *A, Allpass22 *B, float fsam)
{
    float *a = 0;
    float *b = 0;

    if ((fsam >= 43.1e3f) && (fsam < 45.1e3f))
    {
	a = quad44real;
	b = quad44imag;
    }
    else if ((fsam >= 47e3f) && (fsam < 49e3f))
    {
	a = quad48real;
	b = quad48imag;
    }
    else if ((fsam >= 86e3f) && (fsam < 98e3f))
    {
	a = quad96real;
	b = quad96imag;
    }
    
    if (!a) return 1;
    if (A) A->prepare (a [0] / fsam, a [1], a [2] / fsam, a [3]); 
    if (B) B->prepare (b [0] / fsam, b [1], b [2] / fsam, b [3]); 
    return 0;
}

