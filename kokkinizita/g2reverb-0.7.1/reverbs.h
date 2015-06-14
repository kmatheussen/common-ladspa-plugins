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
#include "greverb.h"


// -----------------------------------------------------------------------


class Ladspa_G2reverb : public LadspaPlugin
{
public:

  enum
  {
      A_INPL,
      A_INPR,
      A_OUTL,
      A_OUTR,
      C_SIZE,
      C_RT60,
      C_IPBW,
      C_DAMP,
      C_DRYS,
      C_REFL,
      C_TAIL,
      NPORT
  };

  Ladspa_G2reverb (unsigned long fsam) : LadspaPlugin (fsam)
  {
      _greverb = new Greverb (fsam);
  }
  virtual void setport (unsigned long port, LADSPA_Data *data);  
  virtual void active  (bool act);  
  virtual void runproc (unsigned long len, bool add);
  virtual ~Ladspa_G2reverb (void)
  {
      delete _greverb;
  }  

private:

  float     *_port [NPORT];
  Greverb   *_greverb;

};


// -----------------------------------------------------------------------


#endif
