/*
    Copyright (C) 2003 Fons Adriaensen
    
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

//-----------------------------------------------------------------------------------
// Common definitions


#include "blvco.h"

#define NMODS 3
#define VERSION "0.3.0"


static const char* maker = "Fons Adriaensen <fons.adriaensen@alcatel.be>";
static const char* copyr = "(C) 2003 Fons Adriaensen, GNU General Public License Version 2 applies";


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

//static void runadding (LADSPA_Handle H, unsigned long k)
//{
//  ((LadspaPlugin *)H)->runproc (k, true);
//}

//static void setadding (LADSPA_Handle H, LADSPA_Data gain)
//{
//  ((LadspaPlugin *)H)->setgain (gain);
//}

static void deactivate (LADSPA_Handle H)
{
  ((LadspaPlugin *)H)->active (false);
}

static void cleanup (LADSPA_Handle H)
{
  delete (LadspaPlugin *) H;
}


//-----------------------------------------------------------------------------------
// Plugin definitions


static const char* name1 = "Pulse-VCO  --  Anti-aliased oscillator";
static const char* label1  = "Pulse-VCO";

static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
  return new Ladspa_VCO_pulse1 (rate);
}
 
static const char * const pname1  [Ladspa_VCO_pulse1::NPORT] = 
{
  "Output",
  "Frequency",
  "Exp FM",
  "Lin FM", 
  "Octave",
  "Tune",
  "Exp FM gain",
  "Lin FM gain",
  "LP filter"
};

static const LADSPA_PortDescriptor pdesc1 [Ladspa_VCO_pulse1::NPORT] = 
{
  LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const LADSPA_PortRangeHint phint1 [Ladspa_VCO_pulse1::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0 | LADSPA_HINT_INTEGER, -4, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_1, 0, 1 }
};



static const char* name2 = "Saw-VCO  --  Anti-aliased oscillator";
static const char* label2  = "Saw-VCO";

static LADSPA_Handle instant2 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
  return new Ladspa_VCO_saw1 (rate);
}
 
static const char * const pname2  [Ladspa_VCO_saw1::NPORT] = 
{
  "Output",
  "Frequency",
  "Exp FM",
  "Lin FM", 
  "Sync",
  "Octave",
  "Tune",
  "Exp FM gain",
  "Lin FM gain",
  "LP filter"
};

static const LADSPA_PortDescriptor pdesc2 [Ladspa_VCO_saw1::NPORT] = 
{
  LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const LADSPA_PortRangeHint phint2 [Ladspa_VCO_saw1::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0 | LADSPA_HINT_INTEGER, -4, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_1, 0, 1 }
};


static const char* name3 = "Rec-VCO  --  Anti-aliased oscillator";
static const char* label3  = "Rec-VCO";

static LADSPA_Handle instant3 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
  return new Ladspa_VCO_rec1 (rate);
}
 
static const char * const pname3  [Ladspa_VCO_rec1::NPORT] = 
{
  "Output",
  "Frequency",
  "Exp FM",
  "Lin FM", 
  "Mod",
  "Sync",
  "Octave",
  "Tune",
  "Exp FM gain",
  "Lin FM gain",
  "Waveform",
  "Form mod",
  "LP filter"
};

static const LADSPA_PortDescriptor pdesc3 [Ladspa_VCO_rec1::NPORT] = 
{
  LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
  LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const LADSPA_PortRangeHint phint3 [Ladspa_VCO_rec1::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0 | LADSPA_HINT_INTEGER, -4, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -1, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, 0, 4 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_1, 0, 1 }
};




static const LADSPA_Descriptor moddescr [NMODS] =
{
  {
    1952,
    label1,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name1,
    maker,
    copyr,
    Ladspa_VCO_pulse1::NPORT,
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
  },  
  {
    1953,
    label2,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name2,
    maker,
    copyr,
    Ladspa_VCO_saw1::NPORT,
    pdesc2,
    pname2,
    phint2,
    0,
    instant2,
    pconnect,
    activate,
    runplugin,
    0,
    0,
    deactivate,
    cleanup
  },  
  {
    1954,
    label3,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name3,
    maker,
    copyr,
    Ladspa_VCO_rec1::NPORT,
    pdesc3,
    pname3,
    phint3,
    0,
    instant3,
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
