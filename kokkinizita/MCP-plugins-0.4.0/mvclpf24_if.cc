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


#include "mvclpf24.h"

#define NMODS 4
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


static const char* name1 = "Mvclpf-1   Digital implementation of the VC filter invented by R.A.Moog";
static const char* label1  = "Mvclpf-1";

static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Moogvcf1 (rate);
}
 
static const char* name2 = "Mvclpf-2   Digital implementation of the VC filter invented by R.A.Moog";
static const char* label2  = "Mvclpf-2";

static LADSPA_Handle instant2 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Moogvcf2 (rate);
}

static const char* name3 = "Mvclpf-3   Digital implementation of the VC filter invented by R.A.Moog";
static const char* label3  = "Mvclpf-3";

static LADSPA_Handle instant3 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Moogvcf3 (rate);
}

static const char* name4 = "Mvclpf-4   Digital implementation of the VC filter invented by R.A.Moog";
static const char* label4  = "Mvclpf-4";

static LADSPA_Handle instant4 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Moogvcf4 (rate);
}


static const char * const pname1  [Ladspa_Moogvcf1::NPORT] = 
{
    "Input",
    "Output",
    "Frequency",
    "Exp FM",
    "Resonance",
    "Input gain (dB)",
    "Frequency",
    "Exp FM gain",
    "Resonance",
    "Resonance gain",
    "Output gain (dB)"
};

static const LADSPA_PortDescriptor pdesc1 [Ladspa_Moogvcf1::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const LADSPA_PortRangeHint phint1 [Ladspa_Moogvcf1::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -60, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -6, 6 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 1 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 1 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -15, 15 },
};


static const char * const pname4  [Ladspa_Moogvcf4::NPORT + Ladspa_Moogvcf4::NLABEL] = 
{
    "Input",
    "Output",
    "Frequency",
    "Exp FM",
    "Resonance",
    "Input gain (dB)",
    "Frequency",
    "Exp FM gain",
    "Resonance",
    "Resonance gain",
    "Filter poles",
    "Output gain (dB)",
    "No lowpass",
    " 6 dB/oct",
    "12 dB/oct",
    "18 dB/oct",
    "24 dB/oct"
};

static const LADSPA_PortDescriptor pdesc4 [Ladspa_Moogvcf4::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
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

static const LADSPA_PortRangeHint phint4 [Ladspa_Moogvcf4::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -60, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -6, 6 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 10 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 1 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, 0, 1 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_INTEGER /*| LADSPA_HINT_SWITCHED*/, 0, 4 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -15, 15 },
};


static const LADSPA_Descriptor moddescr [NMODS] =
{
    {
	1941,
	label1,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name1,
	maker,
	copyr,
	Ladspa_Moogvcf1::NPORT,
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
    },  
    {
	1942,
	label2,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name2,
	maker,
	copyr,
	Ladspa_Moogvcf2::NPORT,
	pdesc1,
	pname1,
	phint1,
	0,
	instant2,
	pconnect,
	activate,
	runplugin,
	runadding,
	setadding,
	deactivate,
	cleanup
    },  
    {
	1943,
	label3,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name3,
	maker,
	copyr,
	Ladspa_Moogvcf3::NPORT,
	pdesc1,
	pname1,
	phint1,
	0,
	instant3,
	pconnect,
	activate,
	runplugin,
	runadding,
	setadding,
	deactivate,
	cleanup
    },  
    {
	1948,
	label4,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name4,
	maker,
	copyr,
	Ladspa_Moogvcf4::NPORT,
	pdesc4,
	pname4,
	phint4,
	0,
	instant4,
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
