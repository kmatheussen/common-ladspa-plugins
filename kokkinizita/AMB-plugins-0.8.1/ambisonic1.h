/*
    Copyright (C) 2004-2008 Fons Adriaensen <fons@kokkinizita.net>
    
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


#ifndef __AMBISONIC1_H
#define __AMBISONIC1_H


#include "ladspaplugin.h"
#include "filter1.h"


class Ladspa_Monopan11 : public LadspaPlugin
{
public:

    enum { INP, OUT_W, OUT_X, OUT_Y, OUT_Z, CTL_ELEV, CTL_AZIM, NPORT  };

    Ladspa_Monopan11 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Monopan11 (void) {}  

private:

    void calcpar (float az, float el);

    float     *_port [NPORT];
    float      _xx, _yy, _zz;
};



class Ladspa_Stereopan11 : public LadspaPlugin
{
public:

    enum { INP_L, INP_R, OUT_W, OUT_X, OUT_Y, OUT_Z, CTL_ELEV, CTL_WIDTH, CTL_AZIM, NPORT };

    Ladspa_Stereopan11 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Stereopan11 (void) {}  

private:

    void calcpar (float az, float el, float wd);

    float     *_port [NPORT];
    float      _xl, _xr, _yl, _yr, _zz;
};



class Ladspa_Rotator11 : public LadspaPlugin
{
public:

    enum { INP_W, INP_X, INP_Y, INP_Z, OUT_W, OUT_X, OUT_Y, OUT_Z, CTL_AZIM, NPORT  };

    Ladspa_Rotator11 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Rotator11 (void) {}  

private:

    void calcpar (float az);

    float     *_port [NPORT];
    float      _c, _s;
};



class Ladspa_SquareDec11 : public LadspaPlugin
{
public:

    enum 
    {
        INP_W, INP_X, INP_Y, INP_Z,
        OUT_1, OUT_2, OUT_3, OUT_4,
        CTL_FRONT, CTL_SHELF, CTL_HFG1, CTL_LFG1, CTL_FREQ, CTL_DIST,
        NPORT
    };

    Ladspa_SquareDec11 (unsigned long fsam) :
        LadspaPlugin (fsam),
        _mode (0),
        _hfg1 (0),
        _lfg1 (0),
        _freq (0),
        _dist (0)
    {}

    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_SquareDec11 (void) {}  

private:

    enum { SHELF = 1 };

    float     *_port [NPORT];
    int        _mode;
    float      _hfg1;
    float      _lfg1;
    float      _freq;
    float      _dist;
    Pcshelf1   _wsh;
    Pcshelf1   _xsh;
    Pcshelf1   _ysh;
    Lowpass1   _xlp;
    Lowpass1   _ylp;
};



class Ladspa_HexaDec11 : public LadspaPlugin
{
public:

    enum
    {
        INP_W, INP_X, INP_Y, INP_Z,
        OUT_1, OUT_2, OUT_3, OUT_4, OUT_5, OUT_6,
        CTL_FRONT, CTL_SHELF, CTL_HFG1, CTL_LFG1, CTL_FREQ, CTL_DIST,
        NPORT
    };

    Ladspa_HexaDec11 (unsigned long fsam) : 
        LadspaPlugin (fsam),
        _mode (0),
        _hfg1 (0),
        _lfg1 (0),
        _freq (0),
        _dist (0)
    {}

    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_HexaDec11 (void) {}  

private:

    enum { SHELF = 1 };

    float     *_port [NPORT];
    int        _mode;
    float      _hfg1;
    float      _lfg1;
    float      _freq;
    float      _dist;
    Pcshelf1   _wsh;
    Pcshelf1   _xsh;
    Pcshelf1   _ysh;
    Lowpass1   _xlp;
    Lowpass1   _ylp;
};


class Ladspa_CubeDec11 : public LadspaPlugin
{
public:

    enum
    {
        INP_W, INP_X, INP_Y, INP_Z,
        OUT_1, OUT_2, OUT_3, OUT_4, OUT_5, OUT_6, OUT_7, OUT_8,
        CTL_SHELF, CTL_HFG1, CTL_LFG1, CTL_FREQ, CTL_DIST,
        NPORT
    };

    Ladspa_CubeDec11 (unsigned long fsam) :
        LadspaPlugin (fsam),
        _mode (0),
        _hfg1 (0),
        _lfg1 (0),
        _freq (0),
        _dist (0)
        {}

    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_CubeDec11 (void) {}  

private:

    enum { SHELF = 1 };

    float     *_port [NPORT];
    int        _mode;
    float      _hfg1;
    float      _lfg1;
    float      _freq;
    float      _dist;
    Pcshelf1   _wsh;
    Pcshelf1   _xsh;
    Pcshelf1   _ysh;
    Pcshelf1   _zsh;
    Lowpass1   _xlp;
    Lowpass1   _ylp;
    Lowpass1   _zlp;
};


#endif
