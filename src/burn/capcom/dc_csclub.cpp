#include "cps.h"

/*====================================================================================
 Capcom Sports Club
====================================================================================*/

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"    ,BIT_DIGITAL, CpsInp020+4, "p1 coin"  },
	{"P1 Start"   ,BIT_DIGITAL, CpsInp020+0, "p1 start" },
	{"P1 Up"      ,BIT_DIGITAL, CpsInp001+3, "p1 up"    },
	{"P1 Down"    ,BIT_DIGITAL, CpsInp001+2, "p1 down"  },
	{"P1 Left"    ,BIT_DIGITAL, CpsInp001+1, "p1 left"  },
	{"P1 Right"   ,BIT_DIGITAL, CpsInp001+0, "p1 right" },
	{"P1 Button 1",BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Button 2",BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
	{"P1 Button 3",BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

	{"P2 Coin"    ,BIT_DIGITAL, CpsInp020+5, "p2 coin"  },
	{"P2 Start"   ,BIT_DIGITAL, CpsInp020+1, "p2 start" },
	{"P2 Up"      ,BIT_DIGITAL, CpsInp000+3, "p2 up"    },
	{"P2 Down"    ,BIT_DIGITAL, CpsInp000+2, "p2 down"  },
	{"P2 Left"    ,BIT_DIGITAL, CpsInp000+1, "p2 left"  },
	{"P2 Right"   ,BIT_DIGITAL, CpsInp000+0, "p2 right" },
	{"P2 Button 1",BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Button 2",BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
	{"P2 Button 3",BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

	{"Reset"      ,BIT_DIGITAL, &CpsReset, "reset"      },
	{"Diagnostic" ,BIT_DIGITAL, CpsInp021+1, "diag"     },
	{"Service"    ,BIT_DIGITAL, CpsInp021+2, "service"  },
};

STDINPUTINFO(Drv);

/*=====================
Capcom Sports Club Euro
=====================*/


static struct BurnRomInfo CsclubRomDesc[] = {
	{ "cscex.03",      0x80000, 0x305fce70, 2 | BRF_ESS },
	{ "cscex.04",      0x80000, 0xd11da066, 2 | BRF_ESS },
	{ "cscex.05",      0x80000, 0x410c6220, 2 | BRF_ESS },
	{ "cscex.06",      0x80000, 0xeaf70123, 2 | BRF_ESS },

	{ "csce.03",       0x80000, 0xf2c852ef, 1 | BRF_ESS | BRF_PRG },
	{ "csce.04",       0x80000, 0x1184530f, 1 | BRF_ESS | BRF_PRG },
	{ "csce.05",       0x80000, 0x804e2b6b, 1 | BRF_ESS | BRF_PRG },
	{ "csce.06",       0x80000, 0x09277cb9, 1 | BRF_ESS | BRF_PRG },
	{ "csc.07",        0x80000, 0x01b05caa, 1 | BRF_ESS | BRF_PRG },

	{ "csc.14m",      0x200000, 0xe8904afa, 3 | BRF_GRA },
	{ "csc.16m",      0x200000, 0xc98c8079, 3 | BRF_GRA },
	{ "csc.18m",      0x200000, 0xc030df5a, 3 | BRF_GRA },
	{ "csc.20m",      0x200000, 0xb4e55863, 3 | BRF_GRA },

	{ "csc.01",       0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG },

	{ "csc.11m",      0x200000, 0xa027b827, 5 | BRF_SND },
	{ "csc.12m",      0x200000, 0xcb7f6e55, 5 | BRF_SND },
};


STD_ROM_PICK(Csclub) STD_ROM_FN(Csclub)

struct BurnDriver BurnDrvCpsCsclub = {
	"csclub", NULL, NULL, "1997",
	"Capcom Sports Club (970722 Euro)\0", "", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, CsclubRomInfo, CsclubRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*=====================
Capcom Sports Club Asia
=====================*/


static struct BurnRomInfo CsclubaRomDesc[] = {
	{ "cscax.03",      0x80000, 0x9f95b1e1, 2 | BRF_ESS },
	{ "cscax.04",      0x80000, 0x08e85ab2, 2 | BRF_ESS },
	{ "cscax.05",      0x80000, 0x1b2fae1d, 2 | BRF_ESS },
	{ "cscax.06",      0x80000, 0x9e548ba8, 2 | BRF_ESS },

	{ "csca.03",       0x80000, 0xb6acd708, 1 | BRF_ESS | BRF_PRG },
	{ "csca.04",       0x80000, 0xd44ae35f, 1 | BRF_ESS | BRF_PRG },
	{ "csca.05",       0x80000, 0x8da76aec, 1 | BRF_ESS | BRF_PRG },
	{ "csca.06",       0x80000, 0xa1b7b1ee, 1 | BRF_ESS | BRF_PRG },
	{ "csc.07",        0x80000, 0x01b05caa, 1 | BRF_ESS | BRF_PRG },

	{ "csc.14m",      0x200000, 0xe8904afa, 3 | BRF_GRA },
	{ "csc.16m",      0x200000, 0xc98c8079, 3 | BRF_GRA },
	{ "csc.18m",      0x200000, 0xc030df5a, 3 | BRF_GRA },
	{ "csc.20m",      0x200000, 0xb4e55863, 3 | BRF_GRA },

	{ "csc.01",       0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG },

	{ "csc.11m",      0x200000, 0xa027b827, 5 | BRF_SND },
	{ "csc.12m",      0x200000, 0xcb7f6e55, 5 | BRF_SND },
};


STD_ROM_PICK(Cscluba) STD_ROM_FN(Cscluba)

struct BurnDriver BurnDrvCpsCscluba = {
	"cscluba", "csclub", NULL, "1997",
	"Capcom Sports Club (970722 Asia)\0", "", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, CsclubaRomInfo, CsclubaRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*======================
Capcom Sports Club Japan
======================*/


static struct BurnRomInfo DrvRomDesc[] = {
	{ "cscjx.03",      0x80000, 0x2de1d45d, 2 | BRF_ESS },
	{ "cscjx.04",      0x80000, 0x81b25d76, 2 | BRF_ESS },
	{ "cscjx.05",      0x80000, 0x5adb1c93, 2 | BRF_ESS },
	{ "cscjx.06",      0x80000, 0xf5558f79, 2 | BRF_ESS },

	{ "cscj.03",       0x80000, 0xec4ddaa2, 1 | BRF_ESS | BRF_PRG },
	{ "cscj.04",       0x80000, 0x60c632bb, 1 | BRF_ESS | BRF_PRG },
	{ "cscj.05",       0x80000, 0xad042003, 1 | BRF_ESS | BRF_PRG },
	{ "cscj.06",       0x80000, 0x169e4d40, 1 | BRF_ESS | BRF_PRG },
	{ "csc.07",        0x80000, 0x01b05caa, 1 | BRF_ESS | BRF_PRG },

	{ "csc.14m",      0x200000, 0xe8904afa, 3 | BRF_GRA },
	{ "csc.16m",      0x200000, 0xc98c8079, 3 | BRF_GRA },
	{ "csc.18m",      0x200000, 0xc030df5a, 3 | BRF_GRA },
	{ "csc.20m",      0x200000, 0xb4e55863, 3 | BRF_GRA },

	{ "csc.01",       0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG },

	{ "csc.11m",      0x200000, 0xa027b827, 5 | BRF_SND },
	{ "csc.12m",      0x200000, 0xcb7f6e55, 5 | BRF_SND },
};


STD_ROM_PICK(Drv) STD_ROM_FN(Drv)

struct BurnDriver BurnDrvCpsCsclubj = {
	"csclubj", "csclub", NULL, "1997",
	"Capcom Sports Club (970722 Japan)\0", "", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, DrvRomInfo, DrvRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*======================
Capcom Sports Club (Hispanic)
======================*/

static struct BurnRomInfo csclubhRomDesc[] = {
	{ "cschx.03",      0x80000, 0x00000000, 2 | BRF_ESS },
	{ "cschx.04",      0x80000, 0x00000000, 2 | BRF_ESS },
	{ "cschx.05",      0x80000, 0x00000000, 2 | BRF_ESS },
	{ "cschx.06",      0x80000, 0x00000000, 2 | BRF_ESS },

	{ "csch.03",       0x80000, 0x0dd7e46d, 1 | BRF_ESS | BRF_PRG },
	{ "csch.04",       0x80000, 0x486e8143, 1 | BRF_ESS | BRF_PRG },
	{ "csch.05",       0x80000, 0x9e509dfb, 1 | BRF_ESS | BRF_PRG },
	{ "csch.06",       0x80000, 0x817ba313, 1 | BRF_ESS | BRF_PRG },
	{ "csc.07",        0x80000, 0x01b05caa, 1 | BRF_ESS | BRF_PRG },

	{ "csc.14m",      0x200000, 0xe8904afa, 3 | BRF_GRA },
	{ "csc.16m",      0x200000, 0xc98c8079, 3 | BRF_GRA },
	{ "csc.18m",      0x200000, 0xc030df5a, 3 | BRF_GRA },
	{ "csc.20m",      0x200000, 0xb4e55863, 3 | BRF_GRA },

	{ "csc.01",       0x020000, 0xee162111, 4 | BRF_ESS | BRF_PRG },

	{ "csc.11m",      0x200000, 0xa027b827, 5 | BRF_SND },
	{ "csc.12m",      0x200000, 0xcb7f6e55, 5 | BRF_SND },
};


STD_ROM_PICK(csclubh) STD_ROM_FN(csclubh)

struct BurnDriver BurnDrvCpscsclubh = {
	"csclubh", "csclub", NULL, "1997",
	"Capcom Sports Club (970722 Hispanic)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, csclubhRomInfo,csclubhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
