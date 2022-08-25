#include "cps.h"

/*==========================
 	Puzz Loop 2
==========================*/

static struct BurnInputInfo DrvInputList[] = {
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

/*===================
 Puzz Loop 2  (Japan)
====================*/

static struct BurnRomInfo pzloop2jRomDesc[] = {
	{ "pl2jx.03a",    0x080000, 0x3c9bdc30,  2 | BRF_ESS },
	{ "pl2jx.04a",    0x080000, 0xaa1b28f4,  2 | BRF_ESS },
	{ "pl2jx.05a",    0x080000, 0xcd27c17d,  2 | BRF_ESS },
	{ "pl2jx.06a",    0x080000, 0x48f3ac5f,  2 | BRF_ESS },

	{ "pl2j.03a",     0x080000, 0x0a751bd0,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.04a",     0x080000, 0xc3f72afe,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.05a",     0x080000, 0x6ea9dbfc,  1 | BRF_ESS | BRF_PRG },
	{ "pl2j.06a",     0x080000, 0x0f14848d,  1 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.01c", 0x200000, 0x137b13a7, 11 | BRF_GRA },
	{ "pl2-simm.01d", 0x200000, 0xa2db1507, 11 | BRF_GRA },
	{ "pl2-simm.01a", 0x200000, 0x7e80ff8e, 11 | BRF_GRA },
	{ "pl2-simm.01b", 0x200000, 0xcd93e6ed, 11 | BRF_GRA },
	{ "pl2-simm.03c", 0x200000, 0x0f52bbca, 11 | BRF_GRA },
	{ "pl2-simm.03d", 0x200000, 0xa62712c3, 11 | BRF_GRA },
	{ "pl2-simm.03a", 0x200000, 0xb60c9f8e, 11 | BRF_GRA },
	{ "pl2-simm.03b", 0x200000, 0x83fef284, 11 | BRF_GRA },

	{ "pl2.01",       0x020000, 0x35697569,  4 | BRF_ESS | BRF_PRG },

	{ "pl2-simm.05a", 0x200000, 0x85d8fbe8, 13 | BRF_SND },
	{ "pl2-simm.05b", 0x200000, 0x1ed62584, 13 | BRF_SND },
};


STD_ROM_PICK(pzloop2j) STD_ROM_FN(pzloop2j)

struct BurnDriver BurnDrvCpspzloop2j = {
	"pzloop2j", NULL, NULL, "2001",
	"Puzz Loop 2 (010205 Japan)\0", NULL, "Mitchell", "CPS2",
	L"Puzz Loop 2 (Japan 010205)\0\u30D1\u30BA\u30EB\u30FC\u30D7 \u30C4\u30FC (\u65E5\u672C\u7248 010205)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, pzloop2jRomInfo, pzloop2jRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
