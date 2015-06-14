/*
    Copyright (C) 2004-2009 Fons Adriaensen <fons@kokkinizita.net>
    
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
//-----------------------------------------------------------------------------------


#include "ambisonic2.h"


#define NMODS 4
#define VERSION "0.6.1"


static const char* maker = "Fons Adriaensen <fons@kokkinizita.net>";
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
// Plugin definitions
//-----------------------------------------------------------------------------------


static const char* label0 = "Ambisonics-21-panner";
static const char* name0  = "AMB order 2,1 panner";


static LADSPA_Handle instant0 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Monopan21 (rate);
}


static const LADSPA_PortDescriptor pdesc0 [Ladspa_Monopan21::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname0 [Ladspa_Monopan21::NPORT] = 
{
    "In",
    "Out-W",
    "Out-X",
    "Out-Y",
    "Out-U",
    "Out-V",
    "Out-Z",
    "Elevation",
    "Azimuth"
};

static const LADSPA_PortRangeHint phint0 [Ladspa_Monopan21::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -90, 90 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -180, 180 }
};


//-----------------------------------------------------------------------------------


static const char* label1 = "Ambisonics-21-rotator";
static const char* name1  = "AMB order 2,1 rotator";


static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Rotator21 (rate);
}


static const LADSPA_PortDescriptor pdesc1 [Ladspa_Rotator21::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname1 [Ladspa_Rotator21::NPORT] = 
{
    "In-W",
    "In-X",
    "In-Y",
    "In-U",
    "In-V",
    "In-Z",
    "Out-W",
    "Out-X",
    "Out-Y",
    "Out-U",
    "Out-V",
    "Out-Z",
    "Angle"
};

static const LADSPA_PortRangeHint phint1 [Ladspa_Rotator21::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -180, 180 }
};


//-----------------------------------------------------------------------------------


static const char* label2 = "Ambisonics-22-panner";
static const char* name2  = "AMB order 2,2 panner";


static LADSPA_Handle instant2 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Monopan22 (rate);
}


static const LADSPA_PortDescriptor pdesc2 [Ladspa_Monopan22::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname2 [Ladspa_Monopan22::NPORT] = 
{
    "In",
    "Out-W",
    "Out-X",
    "Out-Y",
    "Out-Z",
    "Out-R",
    "Out-S",
    "Out-T",
    "Out-U",
    "Out-V",
    "Elevation",
    "Azimuth"
};

static const LADSPA_PortRangeHint phint2 [Ladspa_Monopan22::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -90, 90 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -180, 180 }
};


//-----------------------------------------------------------------------------------


static const char* label3 = "Ambisonics-22-rotator";
static const char* name3  = "AMB order 2,2 rotator";


static LADSPA_Handle instant3 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Rotator22 (rate);
}


static const LADSPA_PortDescriptor pdesc3 [Ladspa_Rotator22::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname3 [Ladspa_Rotator22::NPORT] = 
{
    "In-W",
    "In-X",
    "In-Y",
    "In-Z",
    "In-R",
    "In-S",
    "In-T",
    "In-U",
    "In-V",
    "Out-W",
    "Out-X",
    "Out-Y",
    "Out-Z",
    "Out-R",
    "Out-S",
    "Out-T",
    "Out-U",
    "Out-V",
    "Angle"
};

static const LADSPA_PortRangeHint phint3 [Ladspa_Rotator22::NPORT] = 
{
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -180, 180 }
};


//-----------------------------------------------------------------------------------
//  LADSPA dlsym interface
//-----------------------------------------------------------------------------------


static const LADSPA_Descriptor moddescr [NMODS] =
{
    {
	1979,
	label0,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name0,
	maker,
	copyr,
	Ladspa_Monopan21::NPORT,
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
	1980,
	label1,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name1,
	maker,
	copyr,
	Ladspa_Rotator21::NPORT,
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
	1967,
	label2,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name2,
	maker,
	copyr,
	Ladspa_Monopan22::NPORT,
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
	1968,
	label3,
	LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
	name3,
	maker,
	copyr,
	Ladspa_Rotator22::NPORT,
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
