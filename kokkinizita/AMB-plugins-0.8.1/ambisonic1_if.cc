/*
    Copyright (C) 2004-2008 Fons Adriaensen  <fons@kokkinizita.net>
    
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


#include "ambisonic1.h"


#define NMODS 6
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


static const char* label0 = "Ambisonics-11-mono-panner";
static const char* name0  = "AMB order 1,1 mono panner";


static LADSPA_Handle instant0 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Monopan11 (rate);
}


static const LADSPA_PortDescriptor pdesc0 [Ladspa_Monopan11::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname0 [Ladspa_Monopan11::NPORT] = 
{
  "In",
  "Out-W",
  "Out-X",
  "Out-Y",
  "Out-Z",
  "Elevation",
  "Azimuth"
};

static const LADSPA_PortRangeHint phint0 [Ladspa_Monopan11::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -90, 90 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0, -180, 180 }
};


//-----------------------------------------------------------------------------------


static const char* label1 = "Ambisonics-11-stereo-panner";
static const char* name1  = "AMB order 1,1 stereo panner";


static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Stereopan11 (rate);
}


static const LADSPA_PortDescriptor pdesc1 [Ladspa_Stereopan11::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname1 [Ladspa_Stereopan11::NPORT] = 
{
  "In-L",
  "In-R",
  "Out-W",
  "Out-X",
  "Out-Y",
  "Out-Z",
  "Elevation",
  "Width",
  "Azimuth"
};

static const LADSPA_PortRangeHint phint1 [Ladspa_Stereopan11::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0,        -90,  90 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM,  -90,  90 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0,       -180, 180 }
};


//-----------------------------------------------------------------------------------


static const char* label2 = "Ambisonics-11-rotator";
static const char* name2  = "AMB order 1,1 rotator";


static LADSPA_Handle instant2 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_Rotator11 (rate);
}


static const LADSPA_PortDescriptor pdesc2 [Ladspa_Rotator11::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname2 [Ladspa_Rotator11::NPORT] = 
{
  "In-W",
  "In-X",
  "In-Y",
  "In-Z",
  "Out-W",
  "Out-X",
  "Out-Y",
  "Out-Z",
  "Angle"
};

static const LADSPA_PortRangeHint phint2 [Ladspa_Rotator11::NPORT] = 
{
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


static const char* label3 = "Ambisonics-11-square-decoder";
static const char* name3  = "AMB order 1,1 square decoder";


static LADSPA_Handle instant3 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_SquareDec11 (rate);
}


static const LADSPA_PortDescriptor pdesc3 [Ladspa_SquareDec11::NPORT] = 
{
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname3 [Ladspa_SquareDec11::NPORT] = 
{
  "In-W",
  "In-X",
  "In-Y",
  "In-Z",
  "Out-LF/F",
  "Out-RF/R",
  "Out-RB/B",
  "Out-LB/L",
  "Front spkr",
  "Shelf filt",
  "HF XY gain",
  "LF XY gain",
  "Shelf freq",
  "Distance"
};

static const LADSPA_PortRangeHint phint3 [Ladspa_SquareDec11::NPORT] = 
{
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 2 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 2 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE, 200, 800 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM | LADSPA_HINT_LOGARITHMIC, 1, 30 }
};


//-----------------------------------------------------------------------------------


static const char* label4 = "Ambisonics-11-hexagon-decoder";
static const char* name4  = "AMB order 1,1 hexagon decoder";


static LADSPA_Handle instant4 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_HexaDec11 (rate);
}


static const LADSPA_PortDescriptor pdesc4 [Ladspa_HexaDec11::NPORT] = 
{
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
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname4 [Ladspa_HexaDec11::NPORT] = 
{
  "In-W",
  "In-X",
  "In-Y",
  "In-Z",
  "Out-LF/F",
  "Out-RF/RF",
  "Out-R/RB",
  "Out-RB/B",
  "Out-LB/LB",
  "Out-L/LF",
  "Front spkr",
  "Shelf filt",
  "HF XY gain",
  "LF XY gain",
  "Shelf freq",
  "Distance"
};

static const LADSPA_PortRangeHint phint4 [Ladspa_HexaDec11::NPORT] = 
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
  { LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 2 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 2 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE, 200, 800 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM | LADSPA_HINT_LOGARITHMIC, 1, 30 }
};


//-----------------------------------------------------------------------------------


static const char* label5 = "Ambisonics-11-cube-decoder";
static const char* name5  = "AMB order 1,1 cube decoder";


static LADSPA_Handle instant5 (const struct _LADSPA_Descriptor *desc, unsigned long rate)
{
    return new Ladspa_CubeDec11 (rate);
}


static const LADSPA_PortDescriptor pdesc5 [Ladspa_CubeDec11::NPORT] = 
{
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
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL,
    LADSPA_PORT_INPUT  | LADSPA_PORT_CONTROL
};

static const char * const pname5 [Ladspa_CubeDec11::NPORT] = 
{
  "In-W",
  "In-X",
  "In-Y",
  "In-Z",
  "Out-DLF",
  "Out-DRF",
  "Out-DRB",
  "Out-DLB",
  "Out-ULF",
  "Out-URF",
  "Out-URB",
  "Out-ULB",
  "Shelf filt",
  "HF XYZ gain",
  "LF XYZ gain",
  "Shelf freq",
  "Distance"
};

static const LADSPA_PortRangeHint phint5 [Ladspa_CubeDec11::NPORT] = 
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
  { LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0, 0, 1 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 3 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM | LADSPA_HINT_LOGARITHMIC,  1, 3 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE, 200, 800 },
  { LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM | LADSPA_HINT_LOGARITHMIC, 1, 30 }
};


//-----------------------------------------------------------------------------------
//  LADSPA dlsym interface
//-----------------------------------------------------------------------------------


static const LADSPA_Descriptor moddescr [NMODS] =
{
  {
    1973,
    label0,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name0,
    maker,
    copyr,
    Ladspa_Monopan11::NPORT,
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
    1974,
    label1,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name1,
    maker,
    copyr,
    Ladspa_Stereopan11::NPORT,
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
    1975,
    label2,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name2,
    maker,
    copyr,
    Ladspa_Rotator11::NPORT,
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
    1976,
    label3,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name3,
    maker,
    copyr,
    Ladspa_SquareDec11::NPORT,
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
  },  
  {
    1977,
    label4,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name4,
    maker,
    copyr,
    Ladspa_HexaDec11::NPORT,
    pdesc4,
    pname4,
    phint4,
    0,
    instant4,
    pconnect,
    activate,
    runplugin,
    0,
    0,
    deactivate,
    cleanup
  },  
  {
    1978,
    label5,
    LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
    name5,
    maker,
    copyr,
    Ladspa_CubeDec11::NPORT,
    pdesc5,
    pname5,
    phint5,
    0,
    instant5,
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
