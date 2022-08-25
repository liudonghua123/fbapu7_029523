#include "cps.h"

/*==============================================
 19XX
==============================================*/

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start" },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"    },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"  },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"  },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right" },
  {"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start" },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"    },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"  },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"  },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right" },
  {"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

  {"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"    },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"     },
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

/*==========
 19XX (USA)
==========*/

static struct BurnRomInfo NinexxRomDesc[] = {
	{ "19xux.03",      0x80000, 0x239a08ae, 2 | BRF_ESS },
	{ "19xux.04",      0x80000, 0xc13a1072, 2 | BRF_ESS },
	{ "19xux.05",      0x80000, 0x8c066ec3, 2 | BRF_ESS },
	{ "19xux.06",      0x80000, 0x4b1caeb9, 2 | BRF_ESS },

	{ "19xu.03",       0x80000, 0x05955268, 1 | BRF_ESS | BRF_PRG },
	{ "19xu.04",       0x80000, 0x3111ab7f, 1 | BRF_ESS | BRF_PRG },
	{ "19xu.05",       0x80000, 0x38df4a63, 1 | BRF_ESS | BRF_PRG },
	{ "19xu.06",       0x80000, 0x5c7e60d3, 1 | BRF_ESS | BRF_PRG },
	{ "19x.07",        0x80000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG },

	{ "19x.13m",      0x080000, 0x427aeb18, 3 | BRF_GRA },
	{ "19x.15m",      0x080000, 0x63bdbf54, 3 | BRF_GRA },
	{ "19x.17m",      0x080000, 0x2dfe18b5, 3 | BRF_GRA },
	{ "19x.19m",      0x080000, 0xcbef9579, 3 | BRF_GRA },
	{ "19x.14m",      0x200000, 0xe916967c, 3 | BRF_GRA },
	{ "19x.16m",      0x200000, 0x6e75f3db, 3 | BRF_GRA },
	{ "19x.18m",      0x200000, 0x2213e798, 3 | BRF_GRA },
	{ "19x.20m",      0x200000, 0xab9d5b96, 3 | BRF_GRA },

	{ "19x.01",       0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG },

	{ "19x.11m",      0x200000, 0xd38beef3, 5 | BRF_SND },
	{ "19x.12m",      0x200000, 0xd47c96e2, 5 | BRF_SND },
};


STD_ROM_PICK(Ninexx) STD_ROM_FN(Ninexx)

struct BurnDriver BurnDrvCps19xx = {
	"19xx", NULL, NULL, "1995",
	"19XX - the war against destiny (951207 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, NinexxRomInfo, NinexxRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};


/*==========
 19XX (Asia)
==========*/


static struct BurnRomInfo NinexxaRomDesc[] = {
	{ "19xax.03",      0x80000, 0xa4424f2c, 2 | BRF_ESS },
	{ "19xax.04",      0x80000, 0x7b808db4, 2 | BRF_ESS },
	{ "19xax.05",      0x80000, 0xd6535dcf, 2 | BRF_ESS },
	{ "19xax.06",      0x80000, 0xdd39511c, 2 | BRF_ESS },

	{ "19xa.03",       0x80000, 0x0c20fd50, 1 | BRF_ESS | BRF_PRG },
	{ "19xa.04",       0x80000, 0x1fc37508, 1 | BRF_ESS | BRF_PRG },
	{ "19xa.05",       0x80000, 0x6c9cc4ed, 1 | BRF_ESS | BRF_PRG },
	{ "19xa.06",       0x80000, 0xca5b9f76, 1 | BRF_ESS | BRF_PRG },
	{ "19x.07",        0x80000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG },

	{ "19x.13m",      0x080000, 0x427aeb18, 3 | BRF_GRA },
	{ "19x.15m",      0x080000, 0x63bdbf54, 3 | BRF_GRA },
	{ "19x.17m",      0x080000, 0x2dfe18b5, 3 | BRF_GRA },
	{ "19x.19m",      0x080000, 0xcbef9579, 3 | BRF_GRA },
	{ "19x.14m",      0x200000, 0xe916967c, 3 | BRF_GRA },
	{ "19x.16m",      0x200000, 0x6e75f3db, 3 | BRF_GRA },
	{ "19x.18m",      0x200000, 0x2213e798, 3 | BRF_GRA },
	{ "19x.20m",      0x200000, 0xab9d5b96, 3 | BRF_GRA },

	{ "19x.01",       0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG },

	{ "19x.11m",      0x200000, 0xd38beef3, 5 | BRF_SND },
	{ "19x.12m",      0x200000, 0xd47c96e2, 5 | BRF_SND },
};


STD_ROM_PICK(Ninexxa) STD_ROM_FN(Ninexxa)

struct BurnDriver BurnDrvCps19xxa = {
	"19xxa", "19xx", NULL, "1995",
	"19XX - the war against destiny (951207 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, NinexxaRomInfo, NinexxaRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

/*===============
 19XX (Hispanic)
===============*/


static struct BurnRomInfo NinexxhRomDesc[] = {
	{ "19xhx.03a",     0x80000, 0x374ce871, 2 | BRF_ESS },
	{ "19xhx.04a",     0x80000, 0xebd16e33, 2 | BRF_ESS },
	{ "19xhx.05a",     0x80000, 0x0bb5ad27, 2 | BRF_ESS },
	{ "19xhx.06a",     0x80000, 0x3663c8d2, 2 | BRF_ESS },

	{ "19xh.03a",      0x80000, 0x357be2ac, 1 | BRF_ESS | BRF_PRG },
	{ "19xh.04a",      0x80000, 0xbb13ea3b, 1 | BRF_ESS | BRF_PRG },
	{ "19xh.05a",      0x80000, 0xcbd76601, 1 | BRF_ESS | BRF_PRG },
	{ "19xh.06a",      0x80000, 0xb362de8b, 1 | BRF_ESS | BRF_PRG },
	{ "19x.07",        0x80000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG },

	{ "19x.13m",      0x080000, 0x427aeb18, 3 | BRF_GRA },
	{ "19x.15m",      0x080000, 0x63bdbf54, 3 | BRF_GRA },
	{ "19x.17m",      0x080000, 0x2dfe18b5, 3 | BRF_GRA },
	{ "19x.19m",      0x080000, 0xcbef9579, 3 | BRF_GRA },
	{ "19x.14m",      0x200000, 0xe916967c, 3 | BRF_GRA },
	{ "19x.16m",      0x200000, 0x6e75f3db, 3 | BRF_GRA },
	{ "19x.18m",      0x200000, 0x2213e798, 3 | BRF_GRA },
	{ "19x.20m",      0x200000, 0xab9d5b96, 3 | BRF_GRA },

	{ "19x.01",       0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG },

	{ "19x.11m",      0x200000, 0xd38beef3, 5 | BRF_SND },
	{ "19x.12m",      0x200000, 0xd47c96e2, 5 | BRF_SND },
};


STD_ROM_PICK(Ninexxh) STD_ROM_FN(Ninexxh)

struct BurnDriver BurnDrvCps19xxh = {
	"19xxh", "19xx", NULL, "1995",
	"19XX - the war against destiny (951218 Hispanic)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, NinexxhRomInfo, NinexxhRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};


/*======================
 19XX (Japan) Encrypted
======================*/


static struct BurnRomInfo NinexxjRomDesc[] = {
	{ "19xjx.03a",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "19xjx.04a",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "19xjx.05a",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "19xjx.06a",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "19xj.03a",      0x80000, 0xed08bdd1, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.04a",      0x80000, 0xfb8e3f29, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.05a",      0x80000, 0xaa508ac4, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.06a",      0x80000, 0xff2d785b, 1 | BRF_ESS | BRF_PRG },
	{ "19x.07",        0x80000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG },

	{ "19x.13m",      0x080000, 0x427aeb18, 3 | BRF_GRA },
	{ "19x.15m",      0x080000, 0x63bdbf54, 3 | BRF_GRA },
	{ "19x.17m",      0x080000, 0x2dfe18b5, 3 | BRF_GRA },
	{ "19x.19m",      0x080000, 0xcbef9579, 3 | BRF_GRA },
	{ "19x.14m",      0x200000, 0xe916967c, 3 | BRF_GRA },
	{ "19x.16m",      0x200000, 0x6e75f3db, 3 | BRF_GRA },
	{ "19x.18m",      0x200000, 0x2213e798, 3 | BRF_GRA },
	{ "19x.20m",      0x200000, 0xab9d5b96, 3 | BRF_GRA },

	{ "19x.01",       0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG },

	{ "19x.11m",      0x200000, 0xd38beef3, 5 | BRF_SND },
	{ "19x.12m",      0x200000, 0xd47c96e2, 5 | BRF_SND },
};


STD_ROM_PICK(Ninexxj) STD_ROM_FN(Ninexxj)

struct BurnDriver BurnDrvCps19xxj = {
	"19xxj", "19xx", NULL, "1995",
	"19XX - the war against destiny (951225 Japan)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, NinexxjRomInfo, NinexxjRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};

/*=========================
 19XX (Japan r1) Encrypted
=========================*/


static struct BurnRomInfo Ninexxjr1RomDesc[] = {
	{ "19xjx.03",      0x80000, 0x782b4258, 2 | BRF_ESS },
	{ "19xjx.04",      0x80000, 0x11125b05, 2 | BRF_ESS },
	{ "19xjx.05",      0x80000, 0xd4478468, 2 | BRF_ESS },
	{ "19xjx.06",      0x80000, 0x2e9b6a63, 2 | BRF_ESS },

	{ "19xj.03",       0x80000, 0x26a381ed, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.04",       0x80000, 0x30100cca, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.05",       0x80000, 0xde67e938, 1 | BRF_ESS | BRF_PRG },
	{ "19xj.06",       0x80000, 0x39f9a409, 1 | BRF_ESS | BRF_PRG },
	{ "19x.07",        0x80000, 0x61c0296c, 1 | BRF_ESS | BRF_PRG },

	{ "19x.13m",      0x080000, 0x427aeb18, 3 | BRF_GRA },
	{ "19x.15m",      0x080000, 0x63bdbf54, 3 | BRF_GRA },
	{ "19x.17m",      0x080000, 0x2dfe18b5, 3 | BRF_GRA },
	{ "19x.19m",      0x080000, 0xcbef9579, 3 | BRF_GRA },
	{ "19x.14m",      0x200000, 0xe916967c, 3 | BRF_GRA },
	{ "19x.16m",      0x200000, 0x6e75f3db, 3 | BRF_GRA },
	{ "19x.18m",      0x200000, 0x2213e798, 3 | BRF_GRA },
	{ "19x.20m",      0x200000, 0xab9d5b96, 3 | BRF_GRA },

	{ "19x.01",       0x020000, 0xef55195e, 4 | BRF_ESS | BRF_PRG },

	{ "19x.11m",      0x200000, 0xd38beef3, 5 | BRF_SND },
	{ "19x.12m",      0x200000, 0xd47c96e2, 5 | BRF_SND },
};


STD_ROM_PICK(Ninexxjr1) STD_ROM_FN(Ninexxjr1)

struct BurnDriver BurnDrvCps19xxjr1 = {
	"19xxjr1", "19xx", NULL, "1995",
	"19XX - the war against destiny (951207 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Ninexxjr1RomInfo, Ninexxjr1RomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,224,384,3,4
};
