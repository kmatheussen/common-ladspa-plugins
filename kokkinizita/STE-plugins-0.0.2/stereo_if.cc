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


#include "stereo.h"

#define NMODS 2
#define VERSION "0.0.2"


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


static const char* label0 = "stereowidth";
static const char* name0  = "Stereo width";


static LADSPA_Handle instant0 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Stwidth (rate);
}


static const LADSPA_PortDescriptor pdesc0 [Ladspa_Stwidth::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname0  [Ladspa_Stwidth::NPORT] = 
{
  "In L",
  "In R",
  "Out L",
  "Out R",
  "Balance",
  "Width"
};

static const LADSPA_PortRangeHint phint0 [Ladspa_Stwidth::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0,  -6,   6 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_1,  -3,   3 }
};


//-----------------------------------------------------------------------------------


static const char* label1 = "stpanner";
static const char* name1  = "Stereo balance and panner";


static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Stpanner (rate);
}


static const LADSPA_PortDescriptor pdesc1 [Ladspa_Stpanner::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname1  [Ladspa_Stpanner::NPORT] = 
{
  "In L",
  "In R",
  "Out L",
  "Out R",
  "Balance",
  "L Pan",
  "R Pan"
};

static const LADSPA_PortRangeHint phint1 [Ladspa_Stpanner::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0,  -1,   1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM,  -1,   1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM,  -1,   1 }
};


//-----------------------------------------------------------------------------------


static const LADSPA_Descriptor moddescr [NMODS] =
{
  {
    1955,
    label0,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name0,
    maker,
    copyr,
    Ladspa_Stwidth::NPORT,
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
  },
  {
    1956,
    label1,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name1,
    maker,
    copyr,
    Ladspa_Stpanner::NPORT,
    pdesc1,
    pname1,
    phint1,
    0,
    instant1,
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
