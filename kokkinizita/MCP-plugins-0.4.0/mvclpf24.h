/*
  Copyright (C) 2003-2008 Fons Adriaensen <fons@kokkinizita.net>
   
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


#ifndef __MOOGVCF_H
#define __MOOGVCF_H

#include "ladspaplugin.h"


class Ladspa_Moogvcf1 : public LadspaPlugin
{
public:

    enum { A_INPUT, A_OUTPUT, A_FREQ, A_FMOD, A_RESO,
           C_IPGAIN, C_FREQ, C_FMODG, C_RESO, C_RESOG, C_OPGAIN, NPORT };

    Ladspa_Moogvcf1 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Moogvcf1 (void) {}  

private:

    float *_port [NPORT];
    float _c1, _c2, _c3, _c4, _c5, _w, _r;

};


class Ladspa_Moogvcf2 : public LadspaPlugin
{
public:

    enum { A_INPUT, A_OUTPUT, A_FREQ, A_FMOD, A_RESO,
           C_IPGAIN, C_FREQ, C_FMODG, C_RESO, C_RESOG, C_OPGAIN, NPORT };

    Ladspa_Moogvcf2 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Moogvcf2 (void) {}  

private:

    float *_port [NPORT];
    float _c1, _c2, _c3, _c4, _c5, _w, _r;

};


class Ladspa_Moogvcf3 : public LadspaPlugin
{
public:

    enum { A_INPUT, A_OUTPUT, A_FREQ, A_FMOD, A_RESO,
           C_IPGAIN, C_FREQ, C_FMODG, C_RESO, C_RESOG, C_OPGAIN, NPORT };

    Ladspa_Moogvcf3 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Moogvcf3 (void) {}  

private:

    float *_port [NPORT];
    float _c1, _c2, _c3, _c4, _c5, _w, _r;

};


class Ladspa_Moogvcf4 : public LadspaPlugin
{
public:

    enum { A_INPUT, A_OUTPUT, A_FREQ, A_FMOD, A_RESO,
           C_IPGAIN, C_FREQ, C_FMODG, C_RESO, C_RESOG,
           C_LPFILT, C_OPGAIN, NPORT, NLABEL = 5 };

    Ladspa_Moogvcf4 (unsigned long fsam) : LadspaPlugin (fsam) {}
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~Ladspa_Moogvcf4 (void) {}  

private:

    float *_port [NPORT];
    float _c1, _c2, _c3, _c4, _c5, _w, _r;

};

#endif
