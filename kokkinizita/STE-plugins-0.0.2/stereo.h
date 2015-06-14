// -----------------------------------------------------------------------
//
//  Copyright (C) 2010-2014 Fons Adriaensen <fons@linuxaudio.org>
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


#ifndef __STEREO_H
#define __STEREO_H

#include "ladspaplugin.h"


// -----------------------------------------------------------------------


class Ladspa_Stwidth : public LadspaPlugin
{
public:

  enum
  {
      A_INPL,
      A_INPR,
      A_OUTL,
      A_OUTR,
      C_IPBAL,
      C_WIDTH,
      NPORT
  };

  Ladspa_Stwidth (unsigned long fsam) :
  LadspaPlugin (fsam),
  _gL (1.0f),
  _gR (1.0f),
  _w (1.0f)
  {
  }
  virtual void setport (unsigned long port, LADSPA_Data *data);  
  virtual void active  (bool act);  
  virtual void runproc (unsigned long len, bool add);
  virtual ~Ladspa_Stwidth (void)
  {
  }  

private:

  float     *_port [NPORT];
  float      _gL, _gR, _w;
};


class Ladspa_Stpanner : public LadspaPlugin
{
public:

  enum
  {
      A_INPL,
      A_INPR,
      A_OUTL,
      A_OUTR,
      C_IPBAL,
      C_LPAN,
      C_RPAN,
      NPORT
  };

  Ladspa_Stpanner (unsigned long fsam) :
  LadspaPlugin (fsam),
  _gLL (1.0f),
  _gLR (0.0f),
  _gRL (0.0f),
  _gRR (1.0f)
  {
  }
  virtual void setport (unsigned long port, LADSPA_Data *data);  
  virtual void active  (bool act);  
  virtual void runproc (unsigned long len, bool add);
  virtual ~Ladspa_Stpanner (void)
  {
  }  

private:

  float     *_port [NPORT];
  float      _gLL, _gLR, _gRL, _gRR;
};


// -----------------------------------------------------------------------


#endif
