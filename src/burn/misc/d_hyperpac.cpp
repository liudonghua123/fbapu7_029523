#include "tiles_generic.h"
#include "timer.h"
#include "msm6295.h"
#include "burn_ym2151.h"
#include "burn_ym3812.h"

static unsigned char HyperpacInputPort0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char HyperpacInputPort1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char HyperpacInputPort2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char HyperpacDip[2]        = {0, 0};
static unsigned char HyperpacInput[3]      = {0x00, 0x00, 0x00};
static unsigned char HyperpacReset         = 0;

static unsigned char *Mem                  = NULL;
static unsigned char *MemEnd               = NULL;
static unsigned char *RamStart             = NULL;
static unsigned char *RamEnd               = NULL;
static unsigned char *HyperpacRom          = NULL;
static unsigned char *HyperpacZ80Rom       = NULL;
static unsigned char *HyperpacRam          = NULL;
static unsigned char *HyperpacPaletteRam   = NULL;
static unsigned char *HyperpacSpriteRam    = NULL;
static unsigned char *HyperpacZ80Ram       = NULL;
static unsigned int  *HyperpacPalette      = NULL;
static unsigned char *HyperpacSprites      = NULL;
static unsigned char *HyperpacTempGfx      = NULL;

static int HyperpacSoundLatch;

static int nCyclesDone[2], nCyclesTotal[2];
static int nCyclesSegment;

static short* pFMBuffer;

static struct BurnInputInfo HyperpacInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , HyperpacInputPort2 + 2, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , HyperpacInputPort2 + 0, "p1 start"  },

	{"P1 Up"             , BIT_DIGITAL  , HyperpacInputPort0 + 0, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , HyperpacInputPort0 + 1, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , HyperpacInputPort0 + 2, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , HyperpacInputPort0 + 3, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , HyperpacInputPort0 + 4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , HyperpacInputPort0 + 5, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , HyperpacInputPort0 + 6, "p1 fire 3" },

	{"Coin 2"            , BIT_DIGITAL  , HyperpacInputPort2 + 3, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , HyperpacInputPort2 + 1, "p2 start"  },

	{"P2 Up"             , BIT_DIGITAL  , HyperpacInputPort1 + 0, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , HyperpacInputPort1 + 1, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , HyperpacInputPort1 + 2, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , HyperpacInputPort1 + 3, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , HyperpacInputPort1 + 4, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , HyperpacInputPort1 + 5, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , HyperpacInputPort1 + 6, "p2 fire 3" },

	{"Reset"             , BIT_DIGITAL  , &HyperpacReset        , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, HyperpacDip + 0       , "dip"       },
};

STDINPUTINFO(Hyperpac);

static struct BurnInputInfo SnowbrosInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , HyperpacInputPort2 + 2, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , HyperpacInputPort2 + 0, "p1 start"  },

	{"P1 Up"             , BIT_DIGITAL  , HyperpacInputPort0 + 0, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , HyperpacInputPort0 + 1, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , HyperpacInputPort0 + 2, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , HyperpacInputPort0 + 3, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , HyperpacInputPort0 + 4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , HyperpacInputPort0 + 5, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , HyperpacInputPort0 + 6, "p1 fire 3" },

	{"Coin 2"            , BIT_DIGITAL  , HyperpacInputPort2 + 3, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , HyperpacInputPort2 + 1, "p2 start"  },

	{"P2 Up"             , BIT_DIGITAL  , HyperpacInputPort1 + 0, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , HyperpacInputPort1 + 1, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , HyperpacInputPort1 + 2, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , HyperpacInputPort1 + 3, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , HyperpacInputPort1 + 4, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , HyperpacInputPort1 + 5, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , HyperpacInputPort1 + 6, "p2 fire 3" },

	{"Reset"             , BIT_DIGITAL  , &HyperpacReset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , HyperpacInputPort2 + 6, "service"   },
	{"Tilt"              , BIT_DIGITAL  , HyperpacInputPort2 + 5, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH, HyperpacDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, HyperpacDip + 1       , "dip"       },
};

STDINPUTINFO(Snowbros);

inline void HyperpacClearOpposites(unsigned char* nJoystickInputs)
{
	if ((*nJoystickInputs & 0x03) == 0x03) {
		*nJoystickInputs &= ~0x03;
	}
	if ((*nJoystickInputs & 0x0c) == 0x0c) {
		*nJoystickInputs &= ~0x0c;
	}
}

inline void HyperpacMakeInputs()
{
	// Reset Inputs
	HyperpacInput[0] = HyperpacInput[1] = HyperpacInput[2] = 0x00;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		HyperpacInput[0] |= (HyperpacInputPort0[i] & 1) << i;
		HyperpacInput[1] |= (HyperpacInputPort1[i] & 1) << i;
		HyperpacInput[2] |= (HyperpacInputPort2[i] & 1) << i;
	}

	// Clear Opposites
	HyperpacClearOpposites(&HyperpacInput[0]);
	HyperpacClearOpposites(&HyperpacInput[1]);
}

static struct BurnDIPInfo HyperpacDIPList[]=
{
	// Default Values
	{0x13, 0xff, 0xff, 0xfc, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x13, 0x01, 0x01, 0x01, "Off"                    },
	{0x13, 0x01, 0x01, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Lives"                  },
	{0x13, 0x01, 0x02, 0x02, "3"                      },
	{0x13, 0x01, 0x02, 0x00, "5"                      },

	{0   , 0xfe, 0   , 8   , "Coin : Credit"          },
	{0x13, 0x01, 0x1c, 0x00, "5 : 1"                  },
	{0x13, 0x01, 0x1c, 0x04, "4 : 1"                  },
	{0x13, 0x01, 0x1c, 0x08, "3 : 1"                  },
	{0x13, 0x01, 0x1c, 0x0c, "2 : 1"                  },
	{0x13, 0x01, 0x1c, 0x1c, "1 : 1"                  },
	{0x13, 0x01, 0x1c, 0x14, "2 : 3"                  },
	{0x13, 0x01, 0x1c, 0x18, "1 : 2"                  },
	{0x13, 0x01, 0x1c, 0x10, "1 : 3"                  },

	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x13, 0x01, 0x60, 0x00, "Easy"                   },
	{0x13, 0x01, 0x60, 0x60, "Normal"                 },
	{0x13, 0x01, 0x60, 0x40, "Hard"                   },
	{0x13, 0x01, 0x60, 0x20, "Very Hard"              },

	{0   , 0xfe, 0   , 2   , "Mode"                   },
	{0x13, 0x01, 0x80, 0x80, "Game"                   },
	{0x13, 0x01, 0x80, 0x00, "Test"                   },
};

STDDIPINFO(Hyperpac);

static struct BurnDIPInfo SnowbrosDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0x01, NULL                     },
	{0x16, 0xff, 0xff, 0x00, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Country"                },
	{0x15, 0x01, 0x01, 0x01, "Europ Type"             },
	{0x15, 0x01, 0x01, 0x00, "America Type"           },

	{0   , 0xfe, 0   , 2   , "Flip Screen"            },
	{0x15, 0x01, 0x02, 0x02, "Invert Screen"          },
	{0x15, 0x01, 0x02, 0x00, "Normal Screen"          },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x15, 0x01, 0x04, 0x00, "Off"                    },
	{0x15, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x15, 0x01, 0x08, 0x08, "Advertise Sound Off"    },
	{0x15, 0x01, 0x08, 0x00, "Advertise Sound On"     },

	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x15, 0x01, 0x30, 0x30, "4 Coin 1 Play"          },
	{0x15, 0x01, 0x30, 0x20, "3 Coin 1 Play"          },
	{0x15, 0x01, 0x30, 0x10, "2 Coin 1 Play"          },
	{0x15, 0x01, 0x30, 0x00, "1 Coin 1 Play"          },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x15, 0x01, 0xc0, 0x00, "1 Coin 2 Play"          },
	{0x15, 0x01, 0xc0, 0x40, "1 Coin 3 Play"          },
	{0x15, 0x01, 0xc0, 0x80, "1 Coin 4 Play"          },
	{0x15, 0x01, 0xc0, 0xc0, "1 Coin 6 Play"          },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x16, 0x01, 0x03, 0x01, "Game Difficulty A"      },
	{0x16, 0x01, 0x03, 0x00, "Game Difficulty B"      },
	{0x16, 0x01, 0x03, 0x02, "Game Difficulty C"      },
	{0x16, 0x01, 0x03, 0x03, "Game Difficulty D"      },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x16, 0x01, 0x0c, 0x0c, "Extend No Extend"       },
	{0x16, 0x01, 0x0c, 0x00, "Extend 100000 Only"     },
	{0x16, 0x01, 0x0c, 0x08, "Extend 100000, 200000"  },
	{0x16, 0x01, 0x0c, 0x04, "Extend 200000 Only"     },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x16, 0x01, 0x30, 0x10, "Hero Counts 1"          },
	{0x16, 0x01, 0x30, 0x30, "Hero Counts 2"          },
	{0x16, 0x01, 0x30, 0x00, "Hero Counts 3"          },
	{0x16, 0x01, 0x30, 0x20, "Hero Counts 4"          },

	{0   , 0xfe, 0   , 2   , "Invulnerability"        },
	{0x16, 0x01, 0x40, 0x40, "No Death, Stop Mode"    },
	{0x16, 0x01, 0x40, 0x00, "Normal Game"            },

	{0   , 0xfe, 0   , 2   , "Allow Continue"         },
	{0x16, 0x01, 0x80, 0x00, "Continue Play On"       },
	{0x16, 0x01, 0x80, 0x80, "Continue Play Off"      },
};

STDDIPINFO(Snowbros);

static struct BurnDIPInfo SnowbrojDIPList[]=
{
	// Default Values
	{0x15, 0xff, 0xff, 0x00, NULL                     },
	{0x16, 0xff, 0xff, 0x00, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet Type"           },
	{0x15, 0x01, 0x01, 0x01, "Up-Right Type"          },
	{0x15, 0x01, 0x01, 0x00, "Table Type"             },

	{0   , 0xfe, 0   , 2   , "Flip Screen"            },
	{0x15, 0x01, 0x02, 0x02, "Invert Screen"          },
	{0x15, 0x01, 0x02, 0x00, "Normal Screen"          },

	{0   , 0xfe, 0   , 2   , "Test Mode"              },
	{0x15, 0x01, 0x04, 0x00, "Off"                    },
	{0x15, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sounds"            },
	{0x15, 0x01, 0x08, 0x08, "Advertise Sound Off"    },
	{0x15, 0x01, 0x08, 0x00, "Advertise Sound On"     },

	{0   , 0xfe, 0   , 4   , "Coin A"                 },
	{0x15, 0x01, 0x30, 0x30, "2 Coin 3 Play"          },
	{0x15, 0x01, 0x30, 0x20, "2 Coin 1 Play"          },
	{0x15, 0x01, 0x30, 0x10, "1 Coin 2 Play"          },
	{0x15, 0x01, 0x30, 0x00, "1 Coin 1 Play"          },

	{0   , 0xfe, 0   , 4   , "Coin B"                 },
	{0x15, 0x01, 0xc0, 0xc0, "2 Coin 3 Play"          },
	{0x15, 0x01, 0xc0, 0x80, "2 Coin 1 Play"          },
	{0x15, 0x01, 0xc0, 0x40, "1 Coin 2 Play"          },
	{0x15, 0x01, 0xc0, 0x00, "1 Coin 1 Play"          },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x16, 0x01, 0x03, 0x01, "Game Difficulty A"      },
	{0x16, 0x01, 0x03, 0x00, "Game Difficulty B"      },
	{0x16, 0x01, 0x03, 0x02, "Game Difficulty C"      },
	{0x16, 0x01, 0x03, 0x03, "Game Difficulty D"      },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x16, 0x01, 0x0c, 0x0c, "Extend No Extend"       },
	{0x16, 0x01, 0x0c, 0x00, "Extend 100000 Only"     },
	{0x16, 0x01, 0x0c, 0x08, "Extend 100000, 200000"  },
	{0x16, 0x01, 0x0c, 0x04, "Extend 200000 Only"     },

	{0   , 0xfe, 0   , 4   , "Lives"                  },
	{0x16, 0x01, 0x30, 0x10, "Hero Counts 1"          },
	{0x16, 0x01, 0x30, 0x30, "Hero Counts 2"          },
	{0x16, 0x01, 0x30, 0x00, "Hero Counts 3"          },
	{0x16, 0x01, 0x30, 0x20, "Hero Counts 4"          },

	{0   , 0xfe, 0   , 2   , "Invulnerability"        },
	{0x16, 0x01, 0x40, 0x40, "No Death, Stop Mode"    },
	{0x16, 0x01, 0x40, 0x00, "Normal Game"            },

	{0   , 0xfe, 0   , 2   , "Allow Continue"         },
	{0x16, 0x01, 0x80, 0x00, "Continue Play On"       },
	{0x16, 0x01, 0x80, 0x80, "Continue Play Off"      },
};

STDDIPINFO(Snowbroj);

static struct BurnRomInfo HyperpacRomDesc[] = {
	{ "hyperpac.h12",  0x20000, 0x2cf0531a, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "hyperpac.i12",  0x20000, 0x9c7d85b8, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "hyperpac.a4",   0x40000, 0xbd8673da, BRF_GRA },			 //  2	Sprites
	{ "hyperpac.a5",   0x40000, 0x5d90cd82, BRF_GRA },			 //  3	Sprites
	{ "hyperpac.a6",   0x40000, 0x61d86e63, BRF_GRA },			 //  4	Sprites

	{ "hyperpac.u1",   0x10000, 0x03faf88e, BRF_SND },			 //  5	Z80 Program Code

	{ "hyperpac.j15",  0x40000, 0xfb9f468d, BRF_SND },			 //  6	Samples
};


STD_ROM_PICK(Hyperpac);
STD_ROM_FN(Hyperpac);

static struct BurnRomInfo HyperpcbRomDesc[] = {
	{ "hpacuh12.bin",  0x20000, 0x633ab2c6, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "hpacui12.bin",  0x20000, 0x23dc00d1, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "hyperpac.a4",   0x40000, 0xbd8673da, BRF_GRA },			 //  2	Sprites
	{ "hyperpac.a5",   0x40000, 0x5d90cd82, BRF_GRA },			 //  3	Sprites
	{ "hyperpac.a6",   0x40000, 0x61d86e63, BRF_GRA },			 //  4	Sprites

	{ "hyperpac.u1",   0x10000, 0x03faf88e, BRF_SND },			 //  5	Z80 Program Code

	{ "hyperpac.j15",  0x40000, 0xfb9f468d, BRF_SND },			 //  6	Samples
};


STD_ROM_PICK(Hyperpcb);
STD_ROM_FN(Hyperpcb);

static struct BurnRomInfo SnowbrosRomDesc[] = {
	{ "sn6.bin",       0x20000, 0x4899ddcf, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "sn5.bin",       0x20000, 0xad310d3f, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "sbros-1.41",    0x80000, 0x16f06b3a, BRF_GRA },			 //  2	Sprites

	{ "sbros-4.29",    0x08000, 0xe6eab4e4, BRF_SND },			 //  3	Z80 Program Code
};


STD_ROM_PICK(Snowbros);
STD_ROM_FN(Snowbros);

static struct BurnRomInfo SnowbroaRomDesc[] = {
	{ "sbros-3a.5",    0x20000, 0x10cb37e1, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "sbros-2a.6",    0x20000, 0xab91cc1e, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "sbros-1.41",    0x80000, 0x16f06b3a, BRF_GRA },			 //  2	Sprites

	{ "sbros-4.29",    0x08000, 0xe6eab4e4, BRF_SND },			 //  3	Z80 Program Code
};


STD_ROM_PICK(Snowbroa);
STD_ROM_FN(Snowbroa);

static struct BurnRomInfo SnowbrobRomDesc[] = {
	{ "sbros3-a",      0x20000, 0x301627d6, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "sbros2-a",      0x20000, 0xf6689f41, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "sbros-1.41",    0x80000, 0x16f06b3a, BRF_GRA },			 //  2	Sprites

	{ "sbros-4.29",    0x08000, 0xe6eab4e4, BRF_SND },			 //  3	Z80 Program Code
};


STD_ROM_PICK(Snowbrob);
STD_ROM_FN(Snowbrob);

static struct BurnRomInfo SnowbrojRomDesc[] = {
	{ "snowbros.3",    0x20000, 0x3f504f9e, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "snowbros.2",    0x20000, 0x854b02bc, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "sbros-1.41",    0x80000, 0x16f06b3a, BRF_GRA },			 //  2	Sprites

	{ "sbros-4.29",    0x08000, 0xe6eab4e4, BRF_SND },			 //  3	Z80 Program Code
};


STD_ROM_PICK(Snowbroj);
STD_ROM_FN(Snowbroj);

static struct BurnRomInfo SnowbrocRomDesc[] =
{
	{"3-a.ic5"   , 	   0x20000, 0xe1bc346b, BRF_ESS | BRF_PRG}, //  0   68000 Program Code
	{"2-a.ic6"   ,     0x20000, 0x1be27f9d, BRF_ESS | BRF_PRG}, //  1   68000 Program Code

	{"sbros-1.41",     0x80000, 0x16f06b3a, BRF_GRA}, 	    		//  2   Sprites

	{"sbros-4.29",     0x08000, 0xe6eab4e4, BRF_SND}, 	    		//  3   Z80 Program Code
};

STD_ROM_PICK(Snowbroc);
STD_ROM_FN(Snowbroc);

int HyperpacDoReset()
{
	HyperpacSoundLatch = 0;

	SekOpen(0);
	SekReset();
	SekClose();

	ZetReset();

	MSM6295Reset(0);
	BurnYM2151Reset();

	return 0;
}

int SnowbrosDoReset()
{
	HyperpacSoundLatch = 0;

	SekOpen(0);
	SekReset();
	SekClose();

	ZetOpen(0);
	ZetReset();
	ZetClose();

	BurnYM3812Reset();

	return 0;
}

void HyperpacYM2151IrqHandler(int Irq)
{
	if (Irq) {
		ZetRaiseIrq(1);
	} else {
		ZetLowerIrq();
	}
}

// ----------------------------------------------------------------------------
// CPU synchronisation

static int nCycles68KSync;

static inline void snowbrosSynchroniseZ80(int nExtraCycles)
{
	int nCycles = ((long long)SekTotalCycles() * nCyclesTotal[1] / nCyclesTotal[0]) + nExtraCycles;

	if (nCycles <= ZetTotalCycles()) {
		return;
	}

	nCycles68KSync = nCycles - nExtraCycles;

	BurnTimerUpdate(nCycles);
}

// Callbacks for the FM chip

static void snowbrosFMIRQHandler(int, int nStatus)
{
	if (nStatus) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

static int snowbrosSynchroniseStream(int nSoundRate)
{
	return (long long)ZetTotalCycles() * nSoundRate / 6000000;
}

// ----------------------------------------------------------------------------

unsigned char __fastcall HyperpacReadByte(unsigned int a)
{
	switch (a) {
		case 0x500000: {
			return HyperpacInput[0];
		}

		case 0x500001: {
			return HyperpacDip[0];
		}

		case 0x500002: {
			return HyperpacInput[1];
		}

		case 0x500004: {
			return HyperpacInput[2];
		}
	}

	return 0;
}

void __fastcall HyperpacWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x300001: {
			HyperpacSoundLatch = d & 0xff;
			return;
		}
	}
}

unsigned char __fastcall HyperpacZ80Read(unsigned short a)
{
	switch (a) {
		case 0xf001: {
			return BurnYM2151ReadStatus();
		}

		case 0xf008: {
			return HyperpacSoundLatch;
		}
	}

	return 0;
}

void __fastcall HyperpacZ80Write(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xf000: {
			BurnYM2151SelectRegister(d);
			return;
		}

		case 0xf001: {
			BurnYM2151WriteRegister(d);
			return;
		}

		case 0xf002: {
			MSM6295Command(0, d);
			return;
		}
	}
}

unsigned short __fastcall SnowbrosReadWord(unsigned int a)
{
	switch (a) {
		case 0x300000:
		case 0x500000:
		case 0x500002:
		case 0x500004: {
			SEK_DEF_READ_WORD(0, a);
		}
	}

	return 0;
}

unsigned char __fastcall SnowbrosReadByte(unsigned int a)
{
	switch (a) {
		case 0x300001: {
			snowbrosSynchroniseZ80(0x0100);
			return HyperpacSoundLatch;
		}

		case 0x500000: {
			return 0x7f - HyperpacInput[0];
		}

		case 0x500001: {
			return 0xff - HyperpacDip[0];
		}

		case 0x500002: {
			return 0xff - HyperpacInput[1];
		}

		case 0x500003: {
			return 0xff - HyperpacDip[1];
		}

		case 0x500004: {
			return 0xff - HyperpacInput[2];
		}
	}

	return 0;
}

void __fastcall SnowbrosWriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x300000: {
			SEK_DEF_WRITE_WORD(0, a, d);
			return;
		}
	}
}

void __fastcall SnowbrosWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x300001: {
			HyperpacSoundLatch = d;
			snowbrosSynchroniseZ80(0);
			ZetNmi();
			return;
		}
	}
}

unsigned char __fastcall SnowbrosZ80PortRead(unsigned short a)
{
	a &= 0xff;

	switch (a) {
		case 0x02:
			return BurnYM3812Read(0);
		case 0x04: {
			if (ZetTotalCycles() > nCycles68KSync) {
				BurnTimerUpdateEnd();
			}
			return HyperpacSoundLatch;
		}
	}

	return 0;
}

void __fastcall SnowbrosZ80PortWrite(unsigned short a, unsigned char d)
{
	a &= 0xff;

	switch (a) {
		case 0x02: {
			BurnYM3812Write(0, d);
			return;
		}

		case 0x03: {
			BurnYM3812Write(1, d);
			return;
		}

		case 0x04: {
			HyperpacSoundLatch = d;
			return;
		}
	}
}

static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	HyperpacRom          = Next; Next += 0x80000;
	HyperpacZ80Rom       = Next; Next += 0x10000;
	MSM6295ROM           = Next; Next += 0x40000;

	RamStart = Next;

	HyperpacRam          = Next; Next += 0x10000;
	HyperpacPaletteRam   = Next; Next += 0x00200;
	HyperpacSpriteRam    = Next; Next += 0x02000;
	HyperpacZ80Ram       = Next; Next += 0x00800;

	RamEnd = Next;

	HyperpacSprites      = Next; Next += (6144 * 16 * 16);
	HyperpacPalette      = (unsigned int*)Next; Next += 0x00200 * sizeof(unsigned int);
	MemEnd = Next;

	return 0;
}

static int SnowbrosMemIndex()
{
	unsigned char *Next; Next = Mem;

	HyperpacRom          = Next; Next += 0x40000;
	HyperpacZ80Rom       = Next; Next += 0x08000;

	RamStart = Next;

	HyperpacRam          = Next; Next += 0x04000;
	HyperpacPaletteRam   = Next; Next += 0x00200;
	HyperpacSpriteRam    = Next; Next += 0x02000;
	HyperpacZ80Ram       = Next; Next += 0x00800;

	RamEnd = Next;

	HyperpacSprites      = Next; Next += (4096 * 16 * 16);
	HyperpacPalette      = (unsigned int*)Next; Next += 0x00200 * sizeof(unsigned int);
	pFMBuffer = (short*)Next; Next += nBurnSoundLen * sizeof(short);
	MemEnd = Next;

	return 0;
}

int HyperpacInit()
{
	int nRet = 0, nLen;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();

	HyperpacTempGfx = (unsigned char*)malloc(0xc0000);

	// Load and byte-swap 68000 Program roms
	nRet = BurnLoadRom(HyperpacRom + 0x00000, 0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(HyperpacRom + 0x00001, 1, 2); if (nRet != 0) return 1;

	// Load Z80 Program Rom
	nRet = BurnLoadRom(HyperpacZ80Rom, 5, 1); if (nRet != 0) return 1;

	// Simulate RAM initialisation done by the protection MCU (not needed for bootleg)
	if (!strcmp(BurnDrvGetTextA(DRV_NAME), "hyperpac")) {
		HyperpacRam[0xe000 + 0] = 0xf9;
		HyperpacRam[0xe000 + 1] = 0x4e;
		HyperpacRam[0xe002 + 0] = 0x00;
		HyperpacRam[0xe002 + 1] = 0x00;
		HyperpacRam[0xe004 + 0] = 0x2c;
		HyperpacRam[0xe004 + 1] = 0x06;
		HyperpacRam[0xe080 + 0] = 0xdc;
		HyperpacRam[0xe080 + 1] = 0xfe;
		HyperpacRam[0xe082 + 0] = 0x98;
		HyperpacRam[0xe082 + 1] = 0xba;
		HyperpacRam[0xe084 + 0] = 0x54;
		HyperpacRam[0xe084 + 1] = 0x76;
		HyperpacRam[0xe086 + 0] = 0x10;
		HyperpacRam[0xe086 + 1] = 0x32;
	}

	// Load and Decode Sprite Roms
	nRet = BurnLoadRom(HyperpacTempGfx + 0x00000, 2, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(HyperpacTempGfx + 0x40000, 3, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(HyperpacTempGfx + 0x80000, 4, 1); if (nRet != 0) return 1;
	for (int c = 0; c < 6144; c++) {
		for (int y = 0; y < 16; y++) {
			int yOff = 0;

			if (y ==  0) yOff = 0;
			if (y ==  1) yOff = 2;
			if (y ==  2) yOff = 1;
			if (y ==  3) yOff = 3;
			if (y ==  4) yOff = 16;
			if (y ==  5) yOff = 18;
			if (y ==  6) yOff = 17;
			if (y ==  7) yOff = 19;
			if (y ==  8) yOff = 4;
			if (y ==  9) yOff = 6;
			if (y == 10) yOff = 5;
			if (y == 11) yOff = 7;
			if (y == 12) yOff = 20;
			if (y == 13) yOff = 22;
			if (y == 14) yOff = 21;
			if (y == 15) yOff = 23;

			HyperpacSprites[(c * 256) + (y * 16) +  0] = HyperpacTempGfx[0x00000 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  1] = HyperpacTempGfx[0x00000 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  2] = HyperpacTempGfx[0x00020 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  3] = HyperpacTempGfx[0x00020 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  4] = HyperpacTempGfx[0x00002 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  5] = HyperpacTempGfx[0x00002 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  6] = HyperpacTempGfx[0x00022 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  7] = HyperpacTempGfx[0x00022 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  8] = HyperpacTempGfx[0x00001 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  9] = HyperpacTempGfx[0x00001 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 10] = HyperpacTempGfx[0x00021 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 11] = HyperpacTempGfx[0x00021 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 12] = HyperpacTempGfx[0x00003 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 13] = HyperpacTempGfx[0x00003 + (yOff * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 14] = HyperpacTempGfx[0x00023 + (yOff * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 15] = HyperpacTempGfx[0x00023 + (yOff * 4) + (c * 128)] >> 4;
		}
	}

	free(HyperpacTempGfx);

	// Load Sample Rom
	nRet = BurnLoadRom(MSM6295ROM, 6, 1); if (nRet != 0) return 1;

	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(HyperpacRom       , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(HyperpacRam       , 0x100000, 0x10ffff, SM_RAM);
	SekMapMemory(HyperpacPaletteRam, 0x600000, 0x6001ff, SM_RAM);
	SekMapMemory(HyperpacSpriteRam , 0x700000, 0x701fff, SM_RAM);
	SekSetReadByteHandler(0, HyperpacReadByte);
	SekSetWriteByteHandler(0, HyperpacWriteByte);
	SekClose();

	// Setup the Z80 emulation
	ZetInit(1);
	ZetMapArea(0x0000, 0xcfff, 0, HyperpacZ80Rom);
	ZetMapArea(0x0000, 0xcfff, 2, HyperpacZ80Rom);
	ZetMapArea(0xd000, 0xd7ff, 0, HyperpacZ80Ram);
	ZetMapArea(0xd000, 0xd7ff, 1, HyperpacZ80Ram);
	ZetMapArea(0xd000, 0xd7ff, 2, HyperpacZ80Ram);
	ZetMemEnd();
	ZetSetReadHandler(HyperpacZ80Read);
	ZetSetWriteHandler(HyperpacZ80Write);

	// Setup the YM2151 emulation
	BurnYM2151Init(4000000, 25.0);
	BurnYM2151SetIrqHandler(&HyperpacYM2151IrqHandler);

	// Setup the OKIM6295 emulation
	MSM6295Init(0, 7575, 100.0, 1);

	GenericTilesInit();

	// Reset the driver
	HyperpacDoReset();

	return 0;
}

int SnowbrosInit()
{
	int nRet = 0, nLen, y;

	BurnSetRefreshRate(57.5);

	// Allocate and Blank all required memory
	Mem = NULL;
	SnowbrosMemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	SnowbrosMemIndex();

	HyperpacTempGfx = (unsigned char*)malloc(0x80000);

	// Load and byte-swap 68000 Program roms
	nRet = BurnLoadRom(HyperpacRom + 0x00001, 0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(HyperpacRom + 0x00000, 1, 2); if (nRet != 0) return 1;

	// Load Z80 Program Rom
	nRet = BurnLoadRom(HyperpacZ80Rom, 3, 1); if (nRet != 0) return 1;

	// Load and Decode Sprite Roms
	nRet = BurnLoadRom(HyperpacTempGfx + 0x00000, 2, 1); if (nRet != 0) return 1;
	for (int c = 0; c < 4096; c++) {
		for (y = 0; y < 8; y++) {
			HyperpacSprites[(c * 256) + (y * 16) +  0] = HyperpacTempGfx[0x00000 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  1] = HyperpacTempGfx[0x00000 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  2] = HyperpacTempGfx[0x00001 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  3] = HyperpacTempGfx[0x00001 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  4] = HyperpacTempGfx[0x00002 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  5] = HyperpacTempGfx[0x00002 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  6] = HyperpacTempGfx[0x00003 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  7] = HyperpacTempGfx[0x00003 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  8] = HyperpacTempGfx[0x00020 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  9] = HyperpacTempGfx[0x00020 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 10] = HyperpacTempGfx[0x00021 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 11] = HyperpacTempGfx[0x00021 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 12] = HyperpacTempGfx[0x00022 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 13] = HyperpacTempGfx[0x00022 + (y * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 14] = HyperpacTempGfx[0x00023 + (y * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 15] = HyperpacTempGfx[0x00023 + (y * 4) + (c * 128)] & 0x0f;
		}

		for (y = 8; y < 16; y++) {
			HyperpacSprites[(c * 256) + (y * 16) +  0] = HyperpacTempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  1] = HyperpacTempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  2] = HyperpacTempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  3] = HyperpacTempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  4] = HyperpacTempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  5] = HyperpacTempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  6] = HyperpacTempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  7] = HyperpacTempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) +  8] = HyperpacTempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) +  9] = HyperpacTempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 10] = HyperpacTempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 11] = HyperpacTempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 12] = HyperpacTempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 13] = HyperpacTempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			HyperpacSprites[(c * 256) + (y * 16) + 14] = HyperpacTempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] >> 4;
			HyperpacSprites[(c * 256) + (y * 16) + 15] = HyperpacTempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] & 0x0f;
		}
	}

	free(HyperpacTempGfx);

	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(HyperpacRom       , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(HyperpacRam       , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(HyperpacPaletteRam, 0x600000, 0x6001ff, SM_RAM);
	SekMapMemory(HyperpacSpriteRam , 0x700000, 0x701fff, SM_RAM);
	SekSetReadWordHandler(0, SnowbrosReadWord);
	SekSetWriteWordHandler(0, SnowbrosWriteWord);
	SekSetReadByteHandler(0, SnowbrosReadByte);
	SekSetWriteByteHandler(0, SnowbrosWriteByte);
	SekClose();

	// Setup the Z80 emulation
	ZetInit(1);
	ZetOpen(0);
	ZetMapArea(0x0000, 0x7fff, 0, HyperpacZ80Rom);
	ZetMapArea(0x0000, 0x7fff, 2, HyperpacZ80Rom);
	ZetMapArea(0x8000, 0x87ff, 0, HyperpacZ80Ram);
	ZetMapArea(0x8000, 0x87ff, 1, HyperpacZ80Ram);
	ZetMapArea(0x8000, 0x87ff, 2, HyperpacZ80Ram);
	ZetMemEnd();
	ZetSetInHandler(SnowbrosZ80PortRead);
	ZetSetOutHandler(SnowbrosZ80PortWrite);
	ZetClose();

	BurnYM3812Init(3000000, &snowbrosFMIRQHandler, &snowbrosSynchroniseStream);
	BurnTimerAttachZet(6000000);

	GenericTilesInit();

	// Reset the driver
	SnowbrosDoReset();

	return 0;
}

int HyperpacExit()
{
	BurnYM2151Exit();
	MSM6295Exit(0);

	SekExit();
	ZetExit();

	GenericTilesExit();

	free(Mem);
	Mem = NULL;

	return 0;
}

int SnowbrosExit()
{
	BurnYM3812Exit();

	SekExit();
	ZetExit();

	GenericTilesExit();

	free(Mem);
	Mem = NULL;

	return 0;
}

void HyperpacRenderSpriteLayer()
{
	int x = 0, y = 0, Offs;

	for (Offs = 0; Offs < 0x2000; Offs += 16) {
		int dx         = ((HyperpacSpriteRam[Offs +  9]  << 8) + HyperpacSpriteRam[Offs +  8]) & 0xff;
		int dy         = ((HyperpacSpriteRam[Offs + 11]  << 8) + HyperpacSpriteRam[Offs + 10]) & 0xff;
		int TileColour = (HyperpacSpriteRam[Offs +  7]  << 8) + HyperpacSpriteRam[Offs +  6];
		int Attr       = (HyperpacSpriteRam[Offs + 15]  << 8) + HyperpacSpriteRam[Offs + 14];
		int Attr2      = (HyperpacSpriteRam[Offs + 13]  << 8) + HyperpacSpriteRam[Offs + 12];
		int FlipX      = Attr & 0x80;
		int FlipY      = (Attr & 0x40) << 1;
		int Tile       = ((Attr & 0x1f) << 8) + (Attr2 & 0xff);
		int Colour     = (TileColour & 0xf0) >> 4;

		if (TileColour & 1) dx = -1 - (dx ^ 0xff);
		if (TileColour & 2) dy = -1 - (dy ^ 0xff);
		if (TileColour & 4) {
			x += dx;
			y += dy;
		} else {
			x = dx;
			y = dy;
		}

		if (x > 511) x &= 0x1ff;
		if (y > 511) y &= 0x1ff;

		if (x > 15 && x <= 240 && (y - 16) > 15 && (y - 16) <= 208) {
			if (!FlipY) {
				if (!FlipX) {
					Render16x16Tile_Mask(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);

				} else {
					Render16x16Tile_Mask_FlipX(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				}
			} else {
				if (!FlipX) {
					Render16x16Tile_Mask_FlipY(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				} else {
					Render16x16Tile_Mask_FlipXY(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				}
			}
		} else {
			if (!FlipY) {
				if (!FlipX) {
					Render16x16Tile_Mask_Clip(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				} else {
					Render16x16Tile_Mask_FlipX_Clip(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				}
			} else {
				if (!FlipX) {
					Render16x16Tile_Mask_FlipY_Clip(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				} else {
					Render16x16Tile_Mask_FlipXY_Clip(Tile, x, y - 16, Colour, 4, 0, 0, HyperpacSprites);
				}
			}
		}
	}
}

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = (nColour >>  0) & 0x1f;
	g = (nColour >>  5) & 0x1f;
	b = (nColour >> 10) & 0x1f;

	r = (r << 3) | (r >> 2);
	g = (g << 3) | (g >> 2);
	b = (b << 3) | (b >> 2);

	return BurnHighCol(r, g, b, 0);
}

int HyperpacCalcPalette()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)HyperpacPaletteRam, pd = HyperpacPalette; i < 0x200; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}

	return 0;
}

void HyperpacRender()
{
	BurnTransferClear();
	HyperpacCalcPalette();
	HyperpacRenderSpriteLayer();
	BurnTransferCopy(HyperpacPalette);
}

int HyperpacFrame()
{
	int nInterleave = 4;

	if (HyperpacReset) HyperpacDoReset();

	HyperpacMakeInputs();

	nCyclesTotal[0] = 16000000 / 60;
	nCyclesTotal[1] = 4000000 / 60;
	nCyclesDone[0] = nCyclesDone[1] = 0;

	int nSoundBufferPos = 0;

	SekNewFrame();

	SekOpen(0);
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);

		// Run Z80
		nCurrentCPU = 1;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			MSM6295Render(0, pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}

		if (i == 1) SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		if (i == 2) SekSetIRQLine(3, SEK_IRQSTATUS_AUTO);
		if (i == 3) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
	}

	SekClose();

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			MSM6295Render(0, pSoundBuf, nSegmentLength);
		}
	}

	if (pBurnDraw) HyperpacRender();

	return 0;
}

int SnowbrosFrame()
{
	int nInterleave = 4;

	if (HyperpacReset) SnowbrosDoReset();

	HyperpacMakeInputs();

	SekOpen(0);
	ZetOpen(0);

	SekNewFrame();
	ZetNewFrame();

	SekIdle(nCyclesDone[0]);
	ZetIdle(nCyclesDone[1]);

	nCyclesTotal[0] = 8000000 / 60;
	nCyclesTotal[1] = 6000000 / 60;

	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - SekTotalCycles();
		SekRun(nCyclesSegment);

		if (i == 1) SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);
		if (i == 2) SekSetIRQLine(3, SEK_IRQSTATUS_AUTO);
		if (i == 3) SekSetIRQLine(2, SEK_IRQSTATUS_AUTO);
	}

	SekClose();

	nCycles68KSync = SekTotalCycles();
	BurnTimerEndFrame(nCyclesTotal[1]);
	BurnYM3812Update(nBurnSoundLen);

	nCyclesDone[0] = SekTotalCycles() - nCyclesTotal[0];
	nCyclesDone[1] = ZetTotalCycles() - nCyclesTotal[1];

//	bprintf(PRINT_NORMAL, _T("%i\n"), nCyclesDone[0]);

	ZetClose();
	SekClose();

	if (pBurnDraw) HyperpacRender();

	return 0;
}

static int HyperpacScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin = 0x02944;
	}

	if (nAction & 4) {						// Scan volatile ram
		memset(&ba, 0, sizeof(ba));
    		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);

		SekScan(nAction & 3);				// Scan 68000
		ZetScan(nAction);					// Scan Z80

		MSM6295Scan(0, nAction);			// Scan OKIM6295
		BurnYM2151Scan(nAction);

		// Scan critical driver variables
		SCAN_VAR(HyperpacSoundLatch);
		SCAN_VAR(HyperpacInput);
		SCAN_VAR(HyperpacDip);
	}

	return 0;
}

static int SnowbrosScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (nAction & 4) {						// Scan volatile ram
		if (pnMin != NULL) {				// Return minimum compatible version
			*pnMin = 0x029519;
		}

		memset(&ba, 0, sizeof(ba));
	    	ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);

		SekScan(nAction & 3);					// Scan 68000
		ZetScan(nAction);					// Scan Z80

		SCAN_VAR(nCyclesDone);

		BurnYM3812Scan(nAction, pnMin);

		// Scan critical driver variables
		SCAN_VAR(HyperpacSoundLatch);
		SCAN_VAR(HyperpacInput);
		SCAN_VAR(HyperpacDip);
	}

	return 0;
}

struct BurnDriver BurnDrvHyperpac = {
	"hyperpac", NULL, NULL, "1995",
	"Hyper Pacman\0", NULL, "SemiCom", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_MISC,
	NULL, HyperpacRomInfo, HyperpacRomName, HyperpacInputInfo, HyperpacDIPInfo,
	HyperpacInit, HyperpacExit, HyperpacFrame, NULL, HyperpacScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvHyperpcb = {
	"hyperpcb", "hyperpac", NULL, "1995",
	"Hyper Pacman (bootleg)\0", "Alternate version", "SemiCom", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_MISC_MISC,
	NULL, HyperpcbRomInfo, HyperpcbRomName, HyperpacInputInfo, HyperpacDIPInfo,
	HyperpacInit, HyperpacExit, HyperpacFrame, NULL, HyperpacScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvSnowbros = {
	"snowbros", NULL, NULL, "1990",
	"Snow Bros. - Nick & Tom (set 1)\0", NULL, "Toaplan", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_MISC,
	NULL, SnowbrosRomInfo, SnowbrosRomName, SnowbrosInputInfo, SnowbrosDIPInfo,
	SnowbrosInit, SnowbrosExit, SnowbrosFrame, NULL, SnowbrosScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvSnowbroa = {
	"snowbroa", "snowbros", NULL, "1990",
	"Snow Bros. - Nick & Tom (set 2)\0", "Alternate version 1", "Toaplan", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, SnowbroaRomInfo, SnowbroaRomName, SnowbrosInputInfo, SnowbrosDIPInfo,
	SnowbrosInit, SnowbrosExit, SnowbrosFrame, NULL, SnowbrosScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvSnowbrob = {
	"snowbrob", "snowbros", NULL, "1990",
	"Snow Bros. - Nick & Tom (set 3)\0", "Alternate version 2", "Toaplan", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, SnowbrobRomInfo, SnowbrobRomName, SnowbrosInputInfo, SnowbrosDIPInfo,
	SnowbrosInit, SnowbrosExit, SnowbrosFrame, NULL, SnowbrosScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvSnowbroj = {
	"snowbroj", "snowbros", NULL, "1990",
	"Snow Bros. - Nick & Tom (Japan)\0", "Japan version", "Toaplan", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, SnowbrojRomInfo, SnowbrojRomName, SnowbrosInputInfo, SnowbrojDIPInfo,
	SnowbrosInit, SnowbrosExit, SnowbrosFrame, NULL, SnowbrosScan,
	NULL, 256, 224, 4, 3
};

struct BurnDriver BurnDrvSnowbroc = {
	"snowbroc", "snowbros", NULL, "1990",
	"Snow Bros. - Nick & Tom (set 4)\0", "Alternate version 3", "Toaplan", "Kaneko Pandora based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_MISC,
	NULL, SnowbrocRomInfo, SnowbrocRomName, SnowbrosInputInfo, SnowbrosDIPInfo,
	SnowbrosInit, SnowbrosExit, SnowbrosFrame, NULL, SnowbrosScan,
	NULL, 256, 224, 4, 3
};
