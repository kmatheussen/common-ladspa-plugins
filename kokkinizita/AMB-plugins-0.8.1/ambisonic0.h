/*
    Copyright (C) 2009-2010 Fons Adriaensen <fons@kokkinizita.net>
    
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


#ifndef __AMBISONIC0_H
#define __AMBISONIC0_H


#include "ladspaplugin.h"
#include "virtmic.h"
#include "allpass.h"



class Ladspa_Tricard2amb : public LadspaPlugin
{
public:

    enum { INP_L, INP_R, INP_B, OUT_W, OUT_X, OUT_Y, OUT_Z, NPORT  };

    Ladspa_Tricard2amb (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Tricard2amb (void) {}  

private:

    float     *_port [NPORT];
};



class Ladspa_Virtualmic : public LadspaPlugin
{
public:

    enum { INP_W, INP_X, INP_Y, INP_Z, OUT_L, OUT_R,
           CTL_ELEV, CTL_AZIM, CTL_ANGLE, CTL_POLAR, NPORT };

    Ladspa_Virtualmic (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Virtualmic (void) {}  

private:

    float     *_port [NPORT];
    Virtmic    _vmic;
};



class Ladspa_UHJ_encoder : public LadspaPlugin
{
public:

    enum { INP_W, INP_X, INP_Y, INP_Z, OUT_L, OUT_R, NPORT  };

    Ladspa_UHJ_encoder (unsigned long fsam);
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_UHJ_encoder (void) {}  

private:

    float     *_port [NPORT];
    bool       _err;
    Allpass22  _Wfilt_r, _Wfilt_i;
    Allpass22  _Xfilt_r, _Xfilt_i;
    Allpass22  _Yfilt_r;
};



class Ladspa_UHJ_decoder : public LadspaPlugin
{
public:

    enum { INP_L, INP_R, OUT_W, OUT_X, OUT_Y, OUT_Z, NPORT  };

    Ladspa_UHJ_decoder (unsigned long fsam);
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_UHJ_decoder (void) {}  

private:

    float     *_port [NPORT];
    bool       _err;
    Allpass22  _Lfilt_r, _Lfilt_i;
    Allpass22  _Rfilt_r, _Rfilt_i;
};


#endif
