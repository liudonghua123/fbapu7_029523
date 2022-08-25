#include "cps.h"

/* ====================================
 	Choko (Japan 010820) Driver
===================================== */

STDINPUTINFOSPEC(Drv, CpsFsi);

/* ===================
  Choko (Japan 010820)
==================== */

static struct BurnRomInfo chokoRomDesc[] = {
	{ "tkojx.03",     0x080000, 0,		 2 | BRF_ESS },
	{ "tkojx.04",     0x080000, 0,		 2 | BRF_ESS },

	{ "tkoj.03",      0x080000, 0x11f5452f,  1 | BRF_ESS | BRF_PRG },
	{ "tkoj.04",      0x080000, 0x68655378,  1 | BRF_ESS | BRF_PRG },

	{ "tko-simm.01c", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.01d", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.01a", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.01b", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.03c", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.03d", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.03a", 0x200000, 0, 		11 | BRF_GRA },
	{ "tko-simm.03b", 0x200000, 0, 		11 | BRF_GRA },

	{ "tko.01",       0x020000, 0x6eda50c2,  4 | BRF_ESS | BRF_PRG },

	{ "tko-simm.05a", 0x200000, 0, 		13 | BRF_SND },
	{ "tko-simm.05b", 0x200000, 0, 		13 | BRF_SND },
};


STD_ROM_PICK(choko) STD_ROM_FN(choko)

struct BurnDriver BurnDrvCpschoko = {
	"choko", NULL, NULL, "2001",
	"Choko (010820 Japan)\0", "Just z80 and Program available", "Mitchell", "CPS2",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_CAPCOM_CPS2 | HARDWARE_CAPCOM_CPS2_SIMM,
	NULL, chokoRomInfo, chokoRomName, DrvInputInfo, NULL,
	Cps2Init,CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
