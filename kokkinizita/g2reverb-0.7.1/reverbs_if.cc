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


#include "reverbs.h"

#define NMODS 1
#define VERSION "0.7.1"


//-----------------------------------------------------------------------------------


static const char* maker = "Fons Adriaensen <fons@linuxaudio.org>";
static const char* copyr = "GPL";


static void pconnect (LADSPA_Handle H, unsigned long port, LADSPA_Data *data)
{
    ((LadspaPlugin *)H)->setport (port, data);
}

static void activate (LADSPA_Handle H)
{
    ((LadspaPlugin *)H)->active (true);
}

static void runplugin (LADSPA_Handle H, unsigned long k)
{
    ((LadspaPlugin *)H)->runproc (k, false);
}
/*
static void runadding (LADSPA_Handle H, unsigned long k)
{
    ((LadspaPlugin *)H)->runproc (k, true);
}

static void setadding (LADSPA_Handle H, LADSPA_Data gain)
{
    ((LadspaPlugin *)H)->setgain (gain);
}
*/
static void deactivate (LADSPA_Handle H)
{
    ((LadspaPlugin *)H)->active (false);
}

static void cleanup (LADSPA_Handle H)
{
    delete (LadspaPlugin *) H;
}


//-----------------------------------------------------------------------------------


static const char* label0 = "G2reverb";
static const char* name0  = "Stereo reverb";


static LADSPA_Handle instant0 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_G2reverb (rate);
}


static const LADSPA_PortDescriptor pdesc0 [Ladspa_G2reverb::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname0  [Ladspa_G2reverb::NPORT] = 
{
  "In L",
  "In R",
  "Out L",
  "Out R",
  "Room size",
  "Reverb time",
  "Input BW",
  "Damping",
  "Dry sound",
  "Reflections",
  "Reverb tail"
};

static const LADSPA_PortRangeHint phint0 [Ladspa_G2reverb::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_LOW,     10, 150 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_LOW,      1,  20 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE,   0,   1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE,   0,   1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE, -80,   0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_HIGH,   -80,   0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_HIGH,   -80,   0 }
};


//-----------------------------------------------------------------------------------


static const LADSPA_Descriptor moddescr [NMODS] =
{
  {
    1950,
    label0,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name0,
    maker,
    copyr,
    Ladspa_G2reverb::NPORT,
    pdesc0,
    pname0,
    phint0,
    0,
    instant0,
    pconnect,
    activate,
    runplugin,
    0,
    0,
    deactivate,
    cleanup
  }
};

extern "C" const LADSPA_Descriptor *ladspa_descriptor (unsigned long i)
{
  if (i >= NMODS) return 0;
  return moddescr + i;
}

//-----------------------------------------------------------------------------------
