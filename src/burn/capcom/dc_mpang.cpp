#include "cps.h"

/*==============================================
 Mighty! Pang
==============================================*/

static struct BurnInputInfo DrvInputList[] =
{
	{"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
	{"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
	{"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
	{"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
	{"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
	{"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
	{"P1 Shot1"      , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
	{"P1 Shot2"      , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},

	{"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
	{"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
	{"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
	{"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
	{"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
	{"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
	{"P2 Shot1"      , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
	{"P2 Shot2"      , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},

	{"Reset"         , BIT_DIGITAL, &CpsReset  , "reset"},
	{"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
	{"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

/*===================
 Mighty! Pang (Japan)
===================*/

static struct BurnRomInfo mpangjRomDesc[] = {
	{ "mpnjx.03a",    0x080000, 0xECCAF0CC,  2 | BRF_ESS },
	{ "mpnjx.04a",    0x080000, 0x34AC83F8,  2 | BRF_ESS },

	{ "mpnj.03a",     0x080000, 0xBF597b1C,  1 | BRF_ESS | BRF_PRG },
	{ "mpnj.04a",     0x080000, 0xF4A3AB0F,  1 | BRF_ESS | BRF_PRG },

	{ "mpn-simm.01c", 0x200000, 0x388DB66B, 11 | BRF_GRA },
	{ "mpn-simm.01d", 0x200000, 0xAFF1B494, 11 | BRF_GRA },
	{ "mpn-simm.01a", 0x200000, 0xA9C4857B, 11 | BRF_GRA },
	{ "mpn-simm.01b", 0x200000, 0xF759DF22, 11 | BRF_GRA },
	{ "mpn-simm.03c", 0x200000, 0xDEC6B720, 11 | BRF_GRA },
	{ "mpn-simm.03d", 0x200000, 0xF8774C18, 11 | BRF_GRA },
	{ "mpn-simm.03a", 0x200000, 0xC2AEA4EC, 11 | BRF_GRA },
	{ "mpn-simm.03b", 0x200000, 0x84D6DC33, 11 | BRF_GRA },

	{ "mpn.01",       0x020000, 0x90C7ADB6,  4 | BRF_ESS | BRF_PRG },

	{ "mpn-simm.05a", 0x200000, 0x318A2E21, 13 | BRF_SND },
	{ "mpn-simm.05b", 0x200000, 0x5462F4E8, 13 | BRF_SND },
};


STD_ROM_PICK(mpangj) STD_ROM_FN(mpangj)

struct BurnDriver BurnDrvCpsMPangj = {
	"mpangj", NULL, NULL, "2000",
	"Mighty! Pang (001011 Japan)\0", NULL, "Mitchell", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, mpangjRomInfo, mpangjRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

