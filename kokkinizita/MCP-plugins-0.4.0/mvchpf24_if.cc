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

//-----------------------------------------------------------------------------------
// Common definitions


#include "mvchpf24.h"

#define NMODS 1
#define VERSION "0.4.0"


static const char* maker = "Fons Adriaensen <fons@kokkinizita.net>";
static const char* copyr = "(C) 2003-2008 Fons Adriaensen - License: GPL2";


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

static void runadding (LADSPA_Handle H, unsigned long k)
{
    ((LadspaPlugin *)H)->runproc (k, true);
}

static void setadding (LADSPA_Handle H, LADSPA_Data gain)
{
    ((LadspaPlugin *)H)->setgain (gain);
}

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


static const char* name1 = "Mvchpf-1   Digital implementation of the VC HP filter invented by R.A. Moog";
static const char* label1  = "Mvchpf-1";


static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Mvchpf1 (rate);
}
 

static const char * const pname1  [Ladspa_Mvchpf1::NPORT] = 
{
    "Input",
    "Output",
    "Frequency",
    "Exp FM",
    "Input gain (dB)",
    "Frequency",
    "Exp FM gain",
    "Output gain (dB)"
};

static const LADSPA_PortDescriptor pdesc1 [Ladspa_Mvchpf1::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const LADSPA_PortRangeHint phint1 [Ladspa_Mvchpf1::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -60, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -6, 6 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -15, 15 },
};


static const LADSPA_Descriptor moddescr [NMODS] =
{
    {
	1960,
	label1,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name1,
	maker,
	copyr,
	Ladspa_Mvchpf1::NPORT,
	pdesc1,
	pname1,
	phint1,
	0,
	instant1,
	pconnect,
	activate,
	runplugin,
	runadding,
	setadding,
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
