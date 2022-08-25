#include "cps.h"

/*=====================================================
 Cyberbots - fullmetal madness
=====================================================*/

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Low Attack" , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 High Attack", BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Boost"      , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},
  {"P1 Weapon"     , BIT_DIGITAL, CpsInp001+7, "p1 fire 4"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Low Attack" , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 High Attack", BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Boost"      , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},
  {"P2 Weapon"     , BIT_DIGITAL, CpsInp000+7, "p2 fire 4"},

  {"Reset"         , BIT_DIGITAL, &CpsReset   , "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

/*===================================
 Cyberbots - fullmetal madness (Euro)
===================================*/


static struct BurnRomInfo CybotsRomDesc[] = {
	{ "cybex.03",      0x80000, 0x00000000, 2 | BRF_ESS },			 // xor decryption tables
	{ "cybex.04",      0x80000, 0x00000000, 2 | BRF_ESS },

	{ "cybe.03",       0x80000, 0x234381cd, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "cybe.04",       0x80000, 0x80691061, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.05",        0x80000, 0xec40408e, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.06",        0x80000, 0x1ad0bed2, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.07",        0x80000, 0x6245a39a, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.08",        0x80000, 0x4b48e223, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.09",        0x80000, 0xe15238f6, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.10",        0x80000, 0x75f4003b, 1 | BRF_ESS | BRF_PRG },

	// graphics:
	{ "cyb.13m",      0x400000, 0xf0dce192, 3 | BRF_GRA },			 // 10
	{ "cyb.15m",      0x400000, 0x187aa39c, 3 | BRF_GRA },
	{ "cyb.17m",      0x400000, 0x8a0e4b12, 3 | BRF_GRA },
	{ "cyb.19m",      0x400000, 0x34b62612, 3 | BRF_GRA },
	{ "cyb.14m",      0x400000, 0xc1537957, 3 | BRF_GRA },
	{ "cyb.16m",      0x400000, 0x15349e86, 3 | BRF_GRA },
	{ "cyb.18m",      0x400000, 0xd83e977d, 3 | BRF_GRA },
	{ "cyb.20m",      0x400000, 0x77cdad5c, 3 | BRF_GRA },

	// sound - z80 roms
	{ "cyb.01",       0x020000, 0x9c0fb079, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "cyb.02",       0x020000, 0x51cb0c4e, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "cyb.11m",      0x200000, 0x362ccab2, 5 | BRF_SND },
	{ "cyb.12m",      0x200000, 0x7066e9cc, 5 | BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cybots) STD_ROM_FN(Cybots)

struct BurnDriver BurnDrvCpsCybots = {
	"cybots", NULL, NULL, "1995",
	"Cyberbots - fullmetal madness (950424 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	0,2,HARDWARE_CAPCOM_CPS2,
	NULL, CybotsRomInfo, CybotsRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*==================================
 Cyberbots - fullmetal madness (USA)
==================================*/


static struct BurnRomInfo CybotsuRomDesc[] = {
	{ "cybux.03",      0x80000, 0x4b4f5b32, 2 | BRF_ESS },			 // xor decryption tables
	{ "cybux.04",      0x80000, 0x6615a7e9, 2 | BRF_ESS },

	{ "cybu.03",       0x80000, 0xdb4da8f4, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "cybu.04",       0x80000, 0x1eec68ac, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.05",        0x80000, 0xec40408e, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.06",        0x80000, 0x1ad0bed2, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.07",        0x80000, 0x6245a39a, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.08",        0x80000, 0x4b48e223, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.09",        0x80000, 0xe15238f6, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.10",        0x80000, 0x75f4003b, 1 | BRF_ESS | BRF_PRG },

	// graphics:
	{ "cyb.13m",      0x400000, 0xf0dce192, 3 | BRF_GRA },			 // 10
	{ "cyb.15m",      0x400000, 0x187aa39c, 3 | BRF_GRA },
	{ "cyb.17m",      0x400000, 0x8a0e4b12, 3 | BRF_GRA },
	{ "cyb.19m",      0x400000, 0x34b62612, 3 | BRF_GRA },
	{ "cyb.14m",      0x400000, 0xc1537957, 3 | BRF_GRA },
	{ "cyb.16m",      0x400000, 0x15349e86, 3 | BRF_GRA },
	{ "cyb.18m",      0x400000, 0xd83e977d, 3 | BRF_GRA },
	{ "cyb.20m",      0x400000, 0x77cdad5c, 3 | BRF_GRA },

	// sound - z80 roms
	{ "cyb.01",       0x020000, 0x9c0fb079, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "cyb.02",       0x020000, 0x51cb0c4e, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "cyb.11m",      0x200000, 0x362ccab2, 5 | BRF_SND },
	{ "cyb.12m",      0x200000, 0x7066e9cc, 5 | BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cybotsu) STD_ROM_FN(Cybotsu)

struct BurnDriver BurnDrvCpsCybotsu = {
	"cybotsu", "cybots", NULL, "1995",
	"Cyberbots - fullmetal madness (950424 US)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, CybotsuRomInfo, CybotsuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*====================================
 Cyberbots - fullmetal madness (Japan)
====================================*/


static struct BurnRomInfo CybotsjRomDesc[] = {
	{ "cybjx.03",      0x80000, 0x867c9acd, 2 | BRF_ESS },			 // xor decryption tables
	{ "cybjx.04",      0x80000, 0x57ed677f, 2 | BRF_ESS },

	{ "cybj.03",       0x80000, 0x6096eada, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "cybj.04",       0x80000, 0x7b0ffaa9, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.05",        0x80000, 0xec40408e, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.06",        0x80000, 0x1ad0bed2, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.07",        0x80000, 0x6245a39a, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.08",        0x80000, 0x4b48e223, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.09",        0x80000, 0xe15238f6, 1 | BRF_ESS | BRF_PRG },
	{ "cyb.10",        0x80000, 0x75f4003b, 1 | BRF_ESS | BRF_PRG },

	// graphics:
	{ "cyb.13m",      0x400000, 0xf0dce192, 3 | BRF_GRA },			 // 10
	{ "cyb.15m",      0x400000, 0x187aa39c, 3 | BRF_GRA },
	{ "cyb.17m",      0x400000, 0x8a0e4b12, 3 | BRF_GRA },
	{ "cyb.19m",      0x400000, 0x34b62612, 3 | BRF_GRA },
	{ "cyb.14m",      0x400000, 0xc1537957, 3 | BRF_GRA },
	{ "cyb.16m",      0x400000, 0x15349e86, 3 | BRF_GRA },
	{ "cyb.18m",      0x400000, 0xd83e977d, 3 | BRF_GRA },
	{ "cyb.20m",      0x400000, 0x77cdad5c, 3 | BRF_GRA },

	// sound - z80 roms
	{ "cyb.01",       0x020000, 0x9c0fb079, 4 | BRF_ESS | BRF_PRG }, // 18
	{ "cyb.02",       0x020000, 0x51cb0c4e, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "cyb.11m",      0x200000, 0x362ccab2, 5 | BRF_SND },
	{ "cyb.12m",      0x200000, 0x7066e9cc, 5 | BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Cybotsj) STD_ROM_FN(Cybotsj)

struct BurnDriver BurnDrvCpsCybotsj = {
	"cybotsj", "cybots", NULL, "1995",
	"Cyberbots - fullmetal madness (950420 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, CybotsjRomInfo, CybotsjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
