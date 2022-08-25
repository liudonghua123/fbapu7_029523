#include "cps.h"

/*===================================
 Jyangokushi - Haoh no Saihai (Japan)
=====================================*/

static struct BurnInputInfo DrvInputList[] = {
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot"       , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Bomb"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
	{"P1 Auto"       , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot"       , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Bomb"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
	{"P2 Auto"       , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

/*====================================
 Jyangokushi - Haoh no Saihai (Japan)
======================================*/

static struct BurnRomInfo jgokushiRomDesc[] = {
	{ "majjx.03",     0x080000, 0,  	 2 | BRF_ESS },

	{ "majj.03",      0x080000, 0x4614a3b2,  1 | BRF_ESS | BRF_PRG },

	{ "maj-simm.01c", 0x200000, 0xba0fe27b, 11 | BRF_GRA },
	{ "maj-simm.01d", 0x200000, 0x2cd141bf, 11 | BRF_GRA },
	{ "maj-simm.01a", 0x200000, 0xe29e4c26, 11 | BRF_GRA },
	{ "maj-simm.01b", 0x200000, 0x7f68b88a, 11 | BRF_GRA },
	{ "maj-simm.03c", 0x200000, 0x3aaeb90b, 11 | BRF_GRA },
	{ "maj-simm.03d", 0x200000, 0x97894cea, 11 | BRF_GRA },
	{ "maj-simm.03a", 0x200000, 0xec737d9d, 11 | BRF_GRA },
	{ "maj-simm.03b", 0x200000, 0xc23b6f22, 11 | BRF_GRA },

	{ "maj.01",       0x020000, 0x1fe8c213,  4 | BRF_ESS | BRF_PRG },

	{ "maj-simm.05a", 0x200000, 0x4cb79672, 13 | BRF_SND },
	{ "maj-simm.05b", 0x200000, 0xe5f2e14a, 13 | BRF_SND },
};


STD_ROM_PICK(jgokushi) STD_ROM_FN(jgokushi)

struct BurnDriver BurnDrvCpsjgokushi = {
	"jgokushi", NULL, NULL, "1999",
	"Jyangokushi - Haoh no Saihai (990527 Japan)\0", "No XOR", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, jgokushiRomInfo, jgokushiRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
