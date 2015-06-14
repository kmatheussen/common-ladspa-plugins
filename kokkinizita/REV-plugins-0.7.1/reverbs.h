// -----------------------------------------------------------------------
//
//  Copyright (C) 2003-2014 Fons Adriaensen <fons@linuxaudio.org>
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


#ifndef __REVERBS_H
#define __REVERBS_H

#include "ladspaplugin.h"
#include "zreverb.h"


// -----------------------------------------------------------------------


class Ladspa_zita_reverb : public LadspaPlugin
{
public:

  enum
  {
      A_INPL,
      A_INPR,
      A_OUTL,
      A_OUTR,
      C_DELAY,
      C_XOVER,
      C_RTLOW,
      C_RTMID,
      C_FDAMP,
      C_FREQ1,
      C_GAIN1,
      C_FREQ2,
      C_GAIN2,
      C_OPMIX,
      NPORT
  };

  Ladspa_zita_reverb (unsigned long fsam) : LadspaPlugin (fsam)
  {
      _zreverb = new Zreverb ();
      _zreverb->init (fsam, false);
      _nprep = 0;
  }
  virtual void setport (unsigned long port, LADSPA_Data *data);  
  virtual void active  (bool act);  
  virtual void runproc (unsigned long len, bool add);
  virtual ~Ladspa_zita_reverb (void)
  {
      delete _zreverb;
  }  

private:

  enum { FRAGM = 2048 };

  float          *_port [NPORT];
  Zreverb        *_zreverb;
  unsigned long   _nprep;
};


// -----------------------------------------------------------------------


class Ladspa_zita_reverb_amb : public LadspaPlugin
{
public:

  enum
  {
      A_INPL,
      A_INPR,
      A_OUTW,
      A_OUTX,
      A_OUTY,
      A_OUTZ,
      C_DELAY,
      C_XOVER,
      C_RTLOW,
      C_RTMID,
      C_FDAMP,
      C_FREQ1,
      C_GAIN1,
      C_FREQ2,
      C_GAIN2,
      C_RGXYZ,
      NPORT
  };

  Ladspa_zita_reverb_amb (unsigned long fsam) : LadspaPlugin (fsam)
  {
      _zreverb = new Zreverb ();
      _zreverb->init (fsam, true);
      _nprep = 0;
  }
  virtual void setport (unsigned long port, LADSPA_Data *data);  
  virtual void active  (bool act);  
  virtual void runproc (unsigned long len, bool add);
  virtual ~Ladspa_zita_reverb_amb (void)
  {
      delete _zreverb;
  }  

private:

  enum { FRAGM = 2048 };

  float          *_port [NPORT];
  Zreverb        *_zreverb;
  unsigned long   _nprep;
};


// -----------------------------------------------------------------------


#endif
