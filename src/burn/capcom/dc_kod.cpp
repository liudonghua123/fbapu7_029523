// The King of Dragons

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp018+0, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp018+4, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp018+1, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp018+5, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"P3 Coin"       , BIT_DIGITAL, CpsInp177+6, "p3 coin"  },
  {"P3 Start"      , BIT_DIGITAL, CpsInp177+7, "p3 start" },
  {"P3 Up"         , BIT_DIGITAL, CpsInp177+3, "p3 up"    },
  {"P3 Down"       , BIT_DIGITAL, CpsInp177+2, "p3 down"  },
  {"P3 Left"       , BIT_DIGITAL, CpsInp177+1, "p3 left"  },
  {"P3 Right"      , BIT_DIGITAL, CpsInp177+0, "p3 right" },
  {"P3 Attack"     , BIT_DIGITAL, CpsInp177+4, "p3 fire 1"},
  {"P3 Jump"       , BIT_DIGITAL, CpsInp177+5, "p3 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset,   "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp018+6, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp018+2, "service"},
  {"Dip A"         , BIT_DIPSWITCH, &Cpi01A    , "dip"},
  {"Dip B"         , BIT_DIPSWITCH, &Cpi01C    , "dip"},
  {"Dip C"         , BIT_DIPSWITCH, &Cpi01E    , "dip"},
};

STDINPUTINFO(Drv);

static struct BurnDIPInfo kodDIPList[]=
{
	// Defaults
	{0x1b, 0xff, 0xff, 0x00, NULL                },
	{0x1c, 0xff, 0xff, 0x00, NULL                },
	{0x1d, 0xff, 0xff, 0x00, NULL                },

	// Dip A
	{0   , 0xfe, 0   , 8   , "Coinage"                },
	{0x1b, 0x01, 0x07, 0x07, "4 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x06, "3 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x05, "2 Coins 1 Credit"       },
	{0x1b, 0x01, 0x07, 0x00, "1 Coin 1 Credit"        },
	{0x1b, 0x01, 0x07, 0x01, "1 Coin 2 Credits"       },
	{0x1b, 0x01, 0x07, 0x02, "1 Coin 3 Credits"       },
	{0x1b, 0x01, 0x07, 0x03, "1 Coin 4 Credits"       },
	{0x1b, 0x01, 0x07, 0x04, "1 Coin 6 Credits"       },

	{0   , 0xfe, 0   , 2   , "Shooter"                },
	{0x1b, 0x01, 0x08, 0x08, "1"                      },
	{0x1b, 0x01, 0x08, 0x00, "3"                      },

	{0   , 0xfe, 0   , 2   , "Max Players"            },
	{0x1b, 0x01, 0x10, 0x10, "2"                      },
	{0x1b, 0x01, 0x10, 0x00, "3"                      },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x20, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "2C to Start, 1 to Cont" },
	{0x1b, 0x01, 0x40, 0x00, "Off"                    },
	{0x1b, 0x01, 0x40, 0x40, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1b, 0x01, 0x80, 0x00, "Off"                    },
//	{0x1b, 0x01, 0x80, 0x80, "On"                     },

	// Dip B
	{0   , 0xfe, 0   , 8   , "Difficulty"             },
	{0x1c, 0x01, 0x07, 0x00, "Easiest"                },
	{0x1c, 0x01, 0x07, 0x01, "Very Easy"              },
	{0x1c, 0x01, 0x07, 0x02, "Easy"                   },
	{0x1c, 0x01, 0x07, 0x03, "Normal"                 },
	{0x1c, 0x01, 0x07, 0x04, "Medium"                 },
	{0x1c, 0x01, 0x07, 0x05, "Hard"                   },
	{0x1c, 0x01, 0x07, 0x06, "Very Hard"              },
	{0x1c, 0x01, 0x07, 0x07, "Hardest"                },

	{0   , 0xfe, 0   , 8   , "Lives"                  },
	{0x1c, 0x01, 0x38, 0x08, "1"                      },
	{0x1c, 0x01, 0x38, 0x00, "2"                      },
	{0x1c, 0x01, 0x38, 0x10, "3"                      },
	{0x1c, 0x01, 0x38, 0x18, "4"                      },
	{0x1c, 0x01, 0x38, 0x20, "5"                      },
	{0x1c, 0x01, 0x38, 0x28, "6"                      },
	{0x1c, 0x01, 0x38, 0x30, "7"                      },
	{0x1c, 0x01, 0x38, 0x38, "8"                      },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x1c, 0x01, 0xc0, 0x40, "80k and every 400k"     },
	{0x1c, 0x01, 0xc0, 0x80, "160k and every 450k"    },
	{0x1c, 0x01, 0xc0, 0x00, "200k and every 450k"    },
	{0x1c, 0x01, 0xc0, 0xc0, "None"                   },

	// Dip C
//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1d, 0x01, 0x01, 0x00, "Off"                    },
//	{0x1d, 0x01, 0x01, 0x01, "On"                     },

//	{0   , 0xfe, 0   , 2   , "Unknown"                },
//	{0x1d, 0x01, 0x02, 0x00, "Off"                    },
//	{0x1d, 0x01, 0x02, 0x02, "On"                     },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x1d, 0x01, 0x04, 0x00, "Off"                    },
	{0x1d, 0x01, 0x04, 0x04, "On"                     },

	{0   , 0xfe, 0   , 2   , "Freeze"                 },
	{0x1d, 0x01, 0x08, 0x00, "Off"                    },
	{0x1d, 0x01, 0x08, 0x08, "On"                     },

	{0   , 0xfe, 0   , 2   , "Flip"                   },
	{0x1d, 0x01, 0x10, 0x00, "Off"                    },
	{0x1d, 0x01, 0x10, 0x10, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demo Sound"             },
	{0x1d, 0x01, 0x20, 0x00, "Off"                    },
	{0x1d, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue"               },
	{0x1d, 0x01, 0x40, 0x00, "Off"                    },
	{0x1d, 0x01, 0x40, 0x40, "On"                     },
};

STDDIPINFO(kod);


static int DrvExit()
{


  CpsRunExit();

  CpsExit();
  nCpsAdLen=0; nCpsZRomLen=0; nCpsGfxLen=0; nCpsRomLen=0;
  Cps = 0;
  Kodb = 0;
  return 0;
}

//========================
//The King of Dragons Init
//========================

static int DrvInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x080001,4,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x080000,5,2); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x0c0001,6,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x0c0000,7,2); if (nRet!=0) return 1; // Already byteswapped

  // Load graphics roms
  CpsLoadTiles(CpsGfx+0x000000,8+0*4);
  CpsLoadTiles(CpsGfx+0x200000,8+1*4);

  //Layer enable code by KEV
  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x30;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x30;

  // Protection enable code by KEV
  CpsMProt[0]=0x5e;
  CpsMProt[1]=0x5c;
  CpsMProt[2]=0x5a;
  CpsMProt[3]=0x58;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,16,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,17,1);
  nRet=BurnLoadRom(CpsAd+0x20000,18,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//================================
//The King of Dragons (Japan) Init
//================================

static int KodjInit()
{
  int nRet=0;
  Cps=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x040001,2,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x040000,3,2); if (nRet!=0) return 1; // Already byteswapped
  nRet=BurnLoadRom(CpsRom+0x080000,4,1); if (nRet!=0) return 1;

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,5);
  CpsLoadTiles(CpsGfx+0x200000,9);

  //Layer enable code by KEV
  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x30;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x30;

  // Protection enable code by KEV
  CpsMProt[0]=0x5e;
  CpsMProt[1]=0x5c;
  CpsMProt[2]=0x5a;
  CpsMProt[3]=0x58;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,13,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,14,1);
  nRet=BurnLoadRom(CpsAd+0x20000,15,1);

  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//==================================
//The King of Dragons (Bootleg) Init
//==================================

static int KodbInit()
{
  int nRet=0;
  Cps=1; Kodb=1;
  nCpsRomLen=   0x100000;
  nCpsCodeLen=0; // not encrypted
  nCpsGfxLen= 8*0x080000;
  nCpsZRomLen=  0x010000;
  nCpsAdLen  =2*0x020000;
  nRet=CpsInit(); if (nRet!=0) return 1;

  // Load program roms
  nRet=BurnLoadRom(CpsRom+0x000001,0,2); if (nRet!=0) return 1;
  nRet=BurnLoadRom(CpsRom+0x000000,1,2); if (nRet!=0) return 1; // Already byteswapped

// ----------------------------------------------------------------------------
// Patches...

// Patch protection? check
  CpsRom[0x412] = 0x6;
  CpsRom[0x414] = 0x64;
  CpsRom[0x415] = 0x71;
  CpsRom[0xC44] = 0x1C;
  CpsRom[0xC45] = 0x10;
  CpsRom[0xC46] = 0x88;
  CpsRom[0xC47] = 0xEF;
  CpsRom[0xC48] = 0x1C;
  CpsRom[0xC49] = 0x12;
  CpsRom[0x34FE] = 0x7C;
  CpsRom[0x34FF] = 0x22;
  CpsRom[0x3500] = 0x90;
  CpsRom[0x3502] = 0x0;
  CpsRom[0x3503] = 0x0;
  CpsRom[0x36AA] = 0xFA;
  CpsRom[0x36AB] = 0x45;
  CpsRom[0x36AC] = 0x2E;
  CpsRom[0x36AE] = 0x1A;
  CpsRom[0x36AF] = 0x30;
  CpsRom[0x4999] = 0x49;
  CpsRom[0x499A] = 0x90;
  CpsRom[0x499C] = 0x0;
  CpsRom[0x499D] = 0x0;
  CpsRom[0x5E64] = 0x0;
  CpsRom[0x5E65] = 0x61;
  CpsRom[0x5E66] = 0x3E;
  CpsRom[0x5E68] = 0x6D;
  CpsRom[0x5E69] = 0x8;
  CpsRom[0x5E92] = 0x0;
  CpsRom[0x5E93] = 0x0;
  CpsRom[0x5EA0] = 0x0;
  CpsRom[0x5EA1] = 0x40;
  CpsRom[0x610A] = 0xC2;
  CpsRom[0x610B] = 0x38;
  CpsRom[0x610C] = 0xC3;
  CpsRom[0x610D] = 0x38;
  CpsRom[0x610E] = 0xE9;
  CpsRom[0x610F] = 0x38;
  CpsRom[0x6168] = 0xC2;
  CpsRom[0x6169] = 0x38;
  CpsRom[0x616A] = 0xC3;
  CpsRom[0x616B] = 0x38;
  CpsRom[0x616C] = 0xC0;
  CpsRom[0x616D] = 0x38;
  CpsRom[0x616E] = 0xC4;
  CpsRom[0x616F] = 0x38;
  CpsRom[0x6188] = 0xC2;
  CpsRom[0x6189] = 0x38;
  CpsRom[0x618A] = 0xC3;
  CpsRom[0x618B] = 0x38;
  CpsRom[0x618C] = 0xC0;
  CpsRom[0x618D] = 0x38;
  CpsRom[0x618E] = 0xC4;
  CpsRom[0x618F] = 0x38;
  CpsRom[0x61A0] = 0xC2;
  CpsRom[0x61A1] = 0x38;
  CpsRom[0x61A2] = 0xC3;
  CpsRom[0x61A3] = 0x38;
  CpsRom[0x61A4] = 0xC0;
  CpsRom[0x61A5] = 0x38;
  CpsRom[0x61A6] = 0xC4;
  CpsRom[0x61A7] = 0x38;
  CpsRom[0x61B8] = 0xC2;
  CpsRom[0x61B9] = 0x38;
  CpsRom[0x61BA] = 0xC3;
  CpsRom[0x61BB] = 0x38;
  CpsRom[0x61BC] = 0xC0;
  CpsRom[0x61BD] = 0x38;
  CpsRom[0x61BE] = 0xC4;
  CpsRom[0x61BF] = 0x38;
  CpsRom[0x6232] = 0xC0;
  CpsRom[0x6233] = 0x38;
  CpsRom[0x6234] = 0xC3;
  CpsRom[0x6235] = 0x38;
  CpsRom[0x6236] = 0xC1;
  CpsRom[0x6237] = 0x38;
  CpsRom[0x6238] = 0xC4;
  CpsRom[0x6239] = 0x38;
  CpsRom[0x623A] = 0x6C;
  CpsRom[0x623B] = 0x2;
  CpsRom[0x623C] = 0xFF;
  CpsRom[0x623E] = 0xFE;
  CpsRom[0x623F] = 0xFF;
  CpsRom[0x6284] = 0xC0;
  CpsRom[0x6285] = 0x38;
  CpsRom[0x6286] = 0xC3;
  CpsRom[0x6287] = 0x38;
  CpsRom[0x6288] = 0xC1;
  CpsRom[0x6289] = 0x38;
  CpsRom[0x628A] = 0xC4;
  CpsRom[0x628B] = 0x38;
  CpsRom[0x62CE] = 0xC0;
  CpsRom[0x62CF] = 0x38;
  CpsRom[0x62D0] = 0xC3;
  CpsRom[0x62D1] = 0x38;
  CpsRom[0x62D2] = 0xC1;
  CpsRom[0x62D3] = 0x38;
  CpsRom[0x62D4] = 0xC4;
  CpsRom[0x62D5] = 0x38;
  CpsRom[0x6318] = 0xC0;
  CpsRom[0x6319] = 0x38;
  CpsRom[0x631A] = 0xC3;
  CpsRom[0x631B] = 0x38;
  CpsRom[0x631C] = 0xC1;
  CpsRom[0x631D] = 0x38;
  CpsRom[0x631E] = 0xC4;
  CpsRom[0x631F] = 0x38;
  CpsRom[0x63B0] = 0xC0;
  CpsRom[0x63B1] = 0x38;
  CpsRom[0x63B2] = 0xC3;
  CpsRom[0x63B3] = 0x38;
  CpsRom[0x63B4] = 0xC1;
  CpsRom[0x63B5] = 0x38;
  CpsRom[0x63B6] = 0xD9;
  CpsRom[0x63B7] = 0x38;
  CpsRom[0x640A] = 0xC0;
  CpsRom[0x640B] = 0x38;
  CpsRom[0x640C] = 0xC3;
  CpsRom[0x640D] = 0x38;
  CpsRom[0x640E] = 0xC1;
  CpsRom[0x640F] = 0x38;
  CpsRom[0x6410] = 0xD9;
  CpsRom[0x6411] = 0x38;
  CpsRom[0x645C] = 0xC0;
  CpsRom[0x645D] = 0x38;
  CpsRom[0x645E] = 0xC3;
  CpsRom[0x645F] = 0x38;
  CpsRom[0x6460] = 0xC1;
  CpsRom[0x6461] = 0x38;
  CpsRom[0x6462] = 0xD9;
  CpsRom[0x6463] = 0x38;
  CpsRom[0x64AE] = 0xC0;
  CpsRom[0x64AF] = 0x38;
  CpsRom[0x64B0] = 0xC3;
  CpsRom[0x64B1] = 0x38;
  CpsRom[0x64B2] = 0xC1;
  CpsRom[0x64B3] = 0x38;
  CpsRom[0x64B4] = 0xD9;
  CpsRom[0x64B5] = 0x38;
  CpsRom[0x657E] = 0xC0;
  CpsRom[0x657F] = 0x38;
  CpsRom[0x6580] = 0xC3;
  CpsRom[0x6581] = 0x38;
  CpsRom[0x6582] = 0xC1;
  CpsRom[0x6583] = 0x38;
  CpsRom[0x6584] = 0xC4;
  CpsRom[0x6585] = 0x38;
  CpsRom[0x65D4] = 0xC0;
  CpsRom[0x65D5] = 0x38;
  CpsRom[0x65D6] = 0xC3;
  CpsRom[0x65D7] = 0x38;
  CpsRom[0x65D8] = 0xC1;
  CpsRom[0x65D9] = 0x38;
  CpsRom[0x65DA] = 0xC4;
  CpsRom[0x65DB] = 0x38;
  CpsRom[0x6622] = 0xC0;
  CpsRom[0x6623] = 0x38;
  CpsRom[0x6624] = 0xC3;
  CpsRom[0x6625] = 0x38;
  CpsRom[0x6626] = 0xC1;
  CpsRom[0x6627] = 0x38;
  CpsRom[0x6628] = 0xC4;
  CpsRom[0x6629] = 0x38;
  CpsRom[0x6670] = 0xC0;
  CpsRom[0x6671] = 0x38;
  CpsRom[0x6672] = 0xC3;
  CpsRom[0x6673] = 0x38;
  CpsRom[0x6674] = 0xC1;
  CpsRom[0x6675] = 0x38;
  CpsRom[0x6676] = 0xC4;
  CpsRom[0x6677] = 0x38;
  CpsRom[0x6708] = 0xC1;
  CpsRom[0x6709] = 0x38;
  CpsRom[0x670A] = 0xC2;
  CpsRom[0x670B] = 0x38;
  CpsRom[0x670C] = 0xC3;
  CpsRom[0x670D] = 0x38;
  CpsRom[0x6870] = 0xC2;
  CpsRom[0x6871] = 0x38;
  CpsRom[0x6872] = 0xC3;
  CpsRom[0x6873] = 0x38;
  CpsRom[0x6874] = 0xFC;
  CpsRom[0x6875] = 0x38;
  CpsRom[0x9D96] = 0x69;
  CpsRom[0x9D97] = 0x42;
  CpsRom[0x9D98] = 0x4;
  CpsRom[0x9D9A] = 0x69;
  CpsRom[0x9D9B] = 0x42;
  CpsRom[0xE1A6] = 0x0;
  CpsRom[0xE1A7] = 0x7A;
  CpsRom[0xE1A8] = 0x2D;
  CpsRom[0xE1A9] = 0x1A;
  CpsRom[0xE1AA] = 0x49;
  CpsRom[0xE1AB] = 0x8E;
  CpsRom[0x69958] = 0x91;
  CpsRom[0x69959] = 0x42;
  CpsRom[0x6995A] = 0xE9;
  CpsRom[0x6995B] = 0x43;
  CpsRom[0x6995C] = 0x80;
  CpsRom[0x6995D] = 0x0;
  CpsRom[0x7A12E] = 0x80;
  CpsRom[0x7A130] = 0x6C;
  CpsRom[0x7A131] = 0x1;
  CpsRom[0x7A134] = 0x80;
  CpsRom[0x7A136] = 0x6A;
  CpsRom[0x7A137] = 0x1;

// ----------------------------------------------------------------------------

  // Load graphics roms
  CpsLoadTiles(CpsGfx         ,2);
  CpsLoadTiles(CpsGfx+0x200000,6);

  //Layer enable code by KEV
  nCpsLcReg=0x60; // Layer control register is at 0x60
  CpsLayEn[1]=0x30;
  CpsLayEn[2]=0x08;
  CpsLayEn[3]=0x30;

  // Protection enable code by KEV
  CpsMProt[0]=0x5e;
  CpsMProt[1]=0x5c;
  CpsMProt[2]=0x5a;
  CpsMProt[3]=0x58;

  MaskAddr[0]=0x6e;
  MaskAddr[1]=0x6c;
  MaskAddr[2]=0x6a;
  MaskAddr[3]=0x68;

  // Load Z80 Rom
  nRet=BurnLoadRom(CpsZRom,10,1);

  // Load ADPCM data
  nRet=BurnLoadRom(CpsAd        ,11,1);
  nRet=BurnLoadRom(CpsAd+0x20000,12,1);


  nRet=CpsRunInit(); if (nRet!=0) return 1;
  // Ready to go
  return 0;
}

//===========================
//The King of Dragons (World)
//===========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo KodRomDesc[] = {
	{ "kod30.rom",     0x20000, 0xc7414fd4, BRF_ESS | BRF_PRG }, // 0 even
	{ "kod37.rom",     0x20000, 0xa5bf40d2, BRF_ESS | BRF_PRG }, // 1 odd
	{ "kod31.rom",     0x20000, 0x1fffc7bd, BRF_ESS | BRF_PRG }, // 2 even
	{ "kod38.rom",     0x20000, 0x89e57a82, BRF_ESS | BRF_PRG }, // 3 odd
	{ "kod28.rom",     0x20000, 0x9367bcd9, BRF_ESS | BRF_PRG }, // 4 even
	{ "kod35.rom",     0x20000, 0x4ca6a48a, BRF_ESS | BRF_PRG }, // 5 odd
	{ "kod29.rom",     0x20000, 0x6a0ba878, BRF_ESS | BRF_PRG }, // 6 even
	{ "kod36.rom",     0x20000, 0xb509b39d, BRF_ESS | BRF_PRG }, // 7 odd

  // graphics:
	{ "kod02.rom",     0x80000, 0xe45b8701, BRF_GRA },			 // 8
	{ "kod04.rom",     0x80000, 0xa7750322, BRF_GRA },
	{ "kod01.rom",     0x80000, 0x5f74bf78, BRF_GRA },
	{ "kod03.rom",     0x80000, 0x5e5303bf, BRF_GRA },
	{ "kod11.rom",     0x80000, 0x113358f3, BRF_GRA },			 // 12
	{ "kod13.rom",     0x80000, 0x38853c44, BRF_GRA },
	{ "kod10.rom",     0x80000, 0x9ef36604, BRF_GRA },
	{ "kod12.rom",     0x80000, 0x402b9b4f, BRF_GRA },

  // z80 rom
	{ "kod09.rom",     0x10000, 0xf5514510, BRF_GRA },			 // 16
  // samples
	{ "kod18.rom",     0x20000, 0x69ecb2c8, BRF_GRA },
	{ "kod19.rom",     0x20000, 0x02d851c1, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Kod) STD_ROM_FN(Kod)

struct BurnDriver BurnDrvCpsKod = {
	"kod", NULL, NULL, "1991",
	"The King of Dragons (910711 World)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,3,HARDWARE_CAPCOM_CPS1,
	NULL,KodRomInfo,KodRomName,DrvInputInfo, kodDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=========================
//The King of Dragons (USA)
//=========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo KoduRomDesc[] = {
	{ "kdu-30b.bin",   0x20000, 0x825817f9, BRF_ESS | BRF_PRG }, // 0
	{ "kdu-37b.bin",   0x20000, 0xd2422dfb, BRF_ESS | BRF_PRG }, // 1
	{ "kdu-31b.bin",   0x20000, 0x9af36039, BRF_ESS | BRF_PRG }, // 2
	{ "kdu-38b.bin",   0x20000, 0xbe8405a1, BRF_ESS | BRF_PRG }, // 3
	{ "kod28.rom",     0x20000, 0x9367bcd9, BRF_ESS | BRF_PRG }, // 4
	{ "kod35.rom",     0x20000, 0x4ca6a48a, BRF_ESS | BRF_PRG }, // 5
	{ "kd-29.bin",     0x20000, 0x0360fa72, BRF_ESS | BRF_PRG }, // 6
	{ "kd-36a.bin",    0x20000, 0x95a3cef8, BRF_ESS | BRF_PRG }, // 7

  // graphics:
	{ "kod02.rom",     0x80000, 0xe45b8701, BRF_GRA },			 // 8
	{ "kod04.rom",     0x80000, 0xa7750322, BRF_GRA },
	{ "kod01.rom",     0x80000, 0x5f74bf78, BRF_GRA },
	{ "kod03.rom",     0x80000, 0x5e5303bf, BRF_GRA },
	{ "kod11.rom",     0x80000, 0x113358f3, BRF_GRA },			 // 12
	{ "kod13.rom",     0x80000, 0x38853c44, BRF_GRA },
	{ "kod10.rom",     0x80000, 0x9ef36604, BRF_GRA },
	{ "kod12.rom",     0x80000, 0x402b9b4f, BRF_GRA },

  // z80 rom
	{ "kd09.bin",      0x10000, 0xbac6ec26, BRF_GRA },			 // 16
  // samples
	{ "kd18.bin",      0x20000, 0x4c63181d, BRF_GRA },
	{ "kd19.bin",      0x20000, 0x92941b80, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Kodu) STD_ROM_FN(Kodu)

struct BurnDriver BurnDrvCpsKodu = {
	"kodu", "kod", NULL, "1991",
	"The King of Dragons (910910 USA)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1,
	NULL,KoduRomInfo,KoduRomName,DrvInputInfo, kodDIPInfo,
	DrvInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===========================
//The King of Dragons (Japan)
//===========================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo KodjRomDesc[] = {
	{ "kd30.bin",      0x20000, 0xebc788ad, BRF_ESS | BRF_PRG }, // 0 even
	{ "kd37.bin",      0x20000, 0xe55c3529, BRF_ESS | BRF_PRG }, // 1 odd
	{ "kd31.bin",      0x20000, 0xc710d722, BRF_ESS | BRF_PRG }, // 2 even
	{ "kd38.bin",      0x20000, 0x57d6ed3a, BRF_ESS | BRF_PRG }, // 3 odd
	{ "kd33.bin",      0x80000, 0x9bd7ad4b, BRF_ESS | BRF_PRG }, // 4 both

  // graphics:
	{ "kod02.rom",     0x80000, 0xe45b8701, BRF_GRA },			 // 8
	{ "kod04.rom",     0x80000, 0xa7750322, BRF_GRA },
	{ "kod01.rom",     0x80000, 0x5f74bf78, BRF_GRA },
	{ "kod03.rom",     0x80000, 0x5e5303bf, BRF_GRA },
	{ "kod11.rom",     0x80000, 0x113358f3, BRF_GRA },			 // 12
	{ "kod13.rom",     0x80000, 0x38853c44, BRF_GRA },
	{ "kod10.rom",     0x80000, 0x9ef36604, BRF_GRA },
	{ "kod12.rom",     0x80000, 0x402b9b4f, BRF_GRA },

  // z80 rom
	{ "kd09.bin",      0x10000, 0xbac6ec26, BRF_GRA },			 // 16
  // samples
	{ "kd18.bin",      0x20000, 0x4c63181d, BRF_GRA },
	{ "kd19.bin",      0x20000, 0x92941b80, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Kodj) STD_ROM_FN(Kodj)

struct BurnDriver BurnDrvCpsKodj = {
	"kodj", "kod", NULL, "1991",
	"The King of Dragons (910805 Japan)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,3,HARDWARE_CAPCOM_CPS1,
	NULL,KodjRomInfo,KodjRomName,DrvInputInfo, kodDIPInfo,
	KodjInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================
//The King of Dragons (Bootleg)
//=============================

// Count possible zip names and (if pszName!=NULL) return them

// Rom information
static struct BurnRomInfo KodbRomDesc[] = {
	{ "kod.17",        0x80000, 0x036dd74c, BRF_ESS | BRF_PRG }, // 0
	{ "kod.18",        0x80000, 0x3e4b7295, BRF_ESS | BRF_PRG }, // 1

  // graphics:
	{ "kod02.rom",     0x80000, 0xe45b8701, BRF_GRA },			 // 2
	{ "kod04.rom",     0x80000, 0xa7750322, BRF_GRA },
	{ "kod01.rom",     0x80000, 0x5f74bf78, BRF_GRA },
	{ "kod03.rom",     0x80000, 0x5e5303bf, BRF_GRA },
	{ "kod11.rom",     0x80000, 0x113358f3, BRF_GRA },			 // 6
	{ "kod13.rom",     0x80000, 0x38853c44, BRF_GRA },
	{ "kod10.rom",     0x80000, 0x9ef36604, BRF_GRA },
	{ "kod12.rom",     0x80000, 0x402b9b4f, BRF_GRA },

  // z80 rom
	{ "kod.15",        0x10000, 0x01cae60c, BRF_GRA },			 // 10
  // samples
	{ "kd18.bin",      0x20000, 0x4c63181d, BRF_GRA },
	{ "kd19.bin",      0x20000, 0x92941b80, BRF_GRA },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Kodb) STD_ROM_FN(Kodb)

struct BurnDriver BurnDrvCpsKodb = {
	"kodb", "kod", NULL, "1991",
	"The King of Dragons (bootleg)\0", NULL, "Capcom", "CPS1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,3,HARDWARE_CAPCOM_CPS1,
	NULL,KodbRomInfo,KodbRomName,DrvInputInfo, kodDIPInfo,
	KodbInit,DrvExit,Cps1Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
