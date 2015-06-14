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


#ifndef __AMBISONIC3_H
#define __AMBISONIC3_H


#include "ladspaplugin.h"


class Ladspa_Monopan31 : public LadspaPlugin
{
public:

    enum { INP,
           OUT_W,
           OUT_X, OUT_Y, 
           OUT_U, OUT_V, 
           OUT_P, OUT_Q, 
           OUT_Z,
           CTL_ELEV, CTL_AZIM, NPORT  };

    Ladspa_Monopan31 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Monopan31 (void) {}  

private:

    void calcpar (float az, float el);

    float     *_port [NPORT];
    float      _xx, _yy, _uu, _vv, _pp, _qq, _zz;
};


class Ladspa_Rotator31 : public LadspaPlugin
{
public:

    enum { INP_W,
           INP_X, INP_Y, 
           INP_U, INP_V, 
           INP_P, INP_Q, 
           INP_Z,
           OUT_W, 
           OUT_X, OUT_Y, 
           OUT_U, OUT_V, 
           OUT_P, OUT_Q, 
           OUT_Z,
           CTL_AZIM, NPORT  };

    Ladspa_Rotator31 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Rotator31 (void) {}  

private:

    void calcpar (float az);

    float *_port [NPORT];
    float   _c1, _s1, _c2, _s2, _c3, _s3;
};


class Ladspa_Monopan33 : public LadspaPlugin
{
public:

    enum { INP,
           OUT_W, 
           OUT_X, OUT_Y, OUT_Z, 
           OUT_R, OUT_S, OUT_T, OUT_U, OUT_V, 
           OUT_K, OUT_L, OUT_M, OUT_N, OUT_O, OUT_P, OUT_Q,
           CTL_ELEV, CTL_AZIM, NPORT  };

    Ladspa_Monopan33 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Monopan33 (void) {}  

private:

    void calcpar (float az, float el);

    float *_port [NPORT];
    float  _xx, _yy, _zz, 
           _rr, _ss, _tt, _uu, _vv,
           _kk, _ll, _mm, _nn, _oo, _pp, _qq;
};


class Ladspa_Rotator33 : public LadspaPlugin
{
public:

    enum { INP_W, 
           INP_X, INP_Y, INP_Z, 
           INP_R, INP_S, INP_T, INP_U, INP_V,
           INP_K, INP_L, INP_M, INP_N, INP_O, INP_P, INP_Q,
           OUT_W, 
           OUT_X, OUT_Y, OUT_Z,
           OUT_R, OUT_S, OUT_T, OUT_U, OUT_V,
           OUT_K, OUT_L, OUT_M, OUT_N, OUT_O, OUT_P, OUT_Q,
           CTL_AZIM, NPORT  };

    Ladspa_Rotator33 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Rotator33 (void) {}  

private:

    void calcpar (float az);

    float  *_port [NPORT];
    float   _c1, _s1, _c2, _s2, _c3, _s3;
};


#endif
