// Hyper Street Fighter II The Anniversary Edition

#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static int DrvInit()
{
	if (Cps2Init()) {
		return 1;
	}

	nCpsGfxScroll[3] = 0;

	return 0;
}

static int DrvExit()
{
	return CpsExit();
}

//======================================================
//Hyper Street Fighter II The Anniversary Edition (Asia)
//======================================================

static struct BurnRomInfo hsf2aRomDesc[] = {
	{ "hs2ax.03",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },  // 0, xor decryption table
	{ "hs2ax.04",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.05",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.06",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2ax.07",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.08",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.09",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.10",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },

	{ "hs2a.03",       0x80000, 0xd50a17e0, 1 | BRF_ESS | BRF_PRG },  // 8, 68000 code (encrypted)
	{ "hs2a.04",       0x80000, 0xa27f42de, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.05",        0x80000, 0xdde34a35, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.06",        0x80000, 0xf4e56dda, 1 | BRF_ESS | BRF_PRG },
	{ "hs2a.07",       0x80000, 0xee4420fc, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.08",        0x80000, 0xc9441533, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.09",        0x80000, 0x3fc638a8, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.10",        0x80000, 0x20d0f9e4, 1 | BRF_ESS | BRF_PRG },

	// graphics:
	{ "hs2.13m",       0x800000, 0xa6ecab17, 3 | BRF_GRA },		  // 16
	{ "hs2.15m",       0x800000, 0x10a0ae4d, 3 | BRF_GRA },
	{ "hs2.17m",       0x800000, 0xadfa7726, 3 | BRF_GRA },
	{ "hs2.19m",       0x800000, 0xbb3ae322, 3 | BRF_GRA },

	// sound - z80 roms
	{ "hs2.01",        0x020000, 0xc1a13786, 4 | BRF_ESS | BRF_PRG }, // 20
	{ "hs2.02",        0x020000, 0x2d8794aa, 4 | BRF_ESS | BRF_PRG },

	// sound - samples
	{ "hs2.11m",       0x800000, 0x0e15c359, 5 | BRF_SND },		  // 22
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(hsf2a) STD_ROM_FN(hsf2a)

struct BurnDriver BurnDrvCpshsf2a = {
	"hsf2a", NULL, NULL, "2004",
	"Hyper Street Fighter II - the anniversary edition (040202 Asia)\0", "No XOR", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_LOCKED, 2, HARDWARE_CAPCOM_CPS2,
	NULL, hsf2aRomInfo, hsf2aRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal, 384, 224, 4, 3
};

//======================================================
//Hyper Street Fighter II The Anniversary Edition (Asia)
//======================================================

static struct BurnRomInfo hsf2jRomDesc[] = {
	{ "hs2jx.03",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },  // 0, xor decryption table
	{ "hs2jx.04",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.05",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.06",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2jx.07",      0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.08",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.09",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },
	{ "hs2x.10",       0x80000, 0, 		1 | BRF_ESS | BRF_PRG },

	{ "hs2j.03",       0x80000, 0x00738f73, 1 | BRF_ESS | BRF_PRG },  // 8, 68000 code (encrypted)
	{ "hs2j.04",       0x80000, 0x40072c4a, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.05",        0x80000, 0xdde34a35, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.06",        0x80000, 0xf4e56dda, 1 | BRF_ESS | BRF_PRG },
	{ "hs2j.07",       0x80000, 0x09fe85b4, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.08",        0x80000, 0xc9441533, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.09",        0x80000, 0x3fc638a8, 1 | BRF_ESS | BRF_PRG },
	{ "hs2.10",        0x80000, 0x20d0f9e4, 1 | BRF_ESS | BRF_PRG },

	// graphics:
	{ "hs2.13m",       0x800000, 0xa6ecab17, 3 | BRF_GRA },		  // 16
	{ "hs2.15m",       0x800000, 0x10a0ae4d, 3 | BRF_GRA },
	{ "hs2.17m",       0x800000, 0xadfa7726, 3 | BRF_GRA },
	{ "hs2.19m",       0x800000, 0xbb3ae322, 3 | BRF_GRA },

	// sound - z80 roms
	{ "hs2.01",        0x020000, 0xc1a13786, 4 | BRF_ESS | BRF_PRG }, // 20
	{ "hs2.02",        0x020000, 0x2d8794aa, 4 | BRF_ESS | BRF_PRG },

	// sound - samples
	{ "hs2.11m",       0x800000, 0x0e15c359, 5 | BRF_SND },		  // 22
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(hsf2j) STD_ROM_FN(hsf2j)

struct BurnDriver BurnDrvCpshsf2j = {
	"hsf2j", "hsf2a", NULL, "2003",
	"Hyper Street Fighter II - the anniversary edition (031222 Japan)\0", "No XOR", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE | BDF_LOCKED, 2, HARDWARE_CAPCOM_CPS2,
	NULL, hsf2jRomInfo, hsf2jRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit, Cps2Frame, CpsRedraw, CpsAreaScan,
	&CpsRecalcPal, 384, 224, 4, 3
};
