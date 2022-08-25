// Street Fighter Alpha

#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

//===========================
//Street Fighter Alpha (Euro)
//===========================


static struct BurnRomInfo SfaRomDesc[] = {
	{ "sfzex.03b",     0x80000, 0x505a1b4a, 2 | BRF_ESS },

	{ "sfze.03b",      0x80000, 0xebf2054d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04b",       0x80000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfa) STD_ROM_FN(Sfa)

struct BurnDriver BurnDrvCpsSfa = {
	"sfa", NULL, NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950727 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfaRomInfo, SfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Alpha (Euro r3)
//==============================


static struct BurnRomInfo Sfar3RomDesc[] = {
	{ "sfzex.03a",     0x80000, 0xb50d87c7, 2 | BRF_ESS },

	{ "sfze.03a",      0x80000, 0xfdbcd434, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04",        0x80000, 0x0c436d30, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05",        0x80000, 0x1f363612, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar3) STD_ROM_FN(Sfar3)

struct BurnDriver BurnDrvCpsSfar3 = {
	"sfar3", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950605 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar3RomInfo, Sfar3RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Alpha (Euro r2)
//==============================


static struct BurnRomInfo Sfar2RomDesc[] = {
	{ "sfzex.03b",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "sfze.03b",      0x80000, 0x2bf5708e, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar2) STD_ROM_FN(Sfar2)

struct BurnDriver BurnDrvCpsSfar2 = {
	"sfar2", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950627 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar2RomInfo, Sfar2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Alpha (Euro r1)
//==============================


static struct BurnRomInfo Sfar1RomDesc[] = {
	{ "sfzex.03c",     0x80000, 0x818f6bde, 2 | BRF_ESS },

	{ "sfze.03c",      0x80000, 0xa1b69dd7, 1 | BRF_ESS | BRF_PRG },
	{ "sfze.04b",      0x80000, 0xbb90acd5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfar1) STD_ROM_FN(Sfar1)

struct BurnDriver BurnDrvCpsSfar1 = {
	"sfar1", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950718 Euro)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfar1RomInfo, Sfar1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===========================================
//Street Fighter Alpha - Warriors Dreams (USA)
//===========================================


static struct BurnRomInfo SfauRomDesc[] = {
	{ "sfzux.03a",     0x80000, 0x1a3160ed, 2 | BRF_ESS },

	{ "sfzu.03a",      0x80000, 0x49fc7db9, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfau) STD_ROM_FN(Sfau)

struct BurnDriver BurnDrvCpsSfau = {
	"sfau", "sfa", NULL, "1995",
	"Street Fighter Alpha - warriors' dreams (950627 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfauRomInfo, SfauRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===========================
//Street Fighter Zero (Japan)
//===========================


static struct BurnRomInfo SfzjRomDesc[] = {
	{ "sfzjx.03c",     0x80000, 0xd6b17a9b, 2 | BRF_ESS },

	{ "sfzj.03c",      0x80000, 0xf5444120, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04b",       0x80000, 0x8b73b0e5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzj) STD_ROM_FN(Sfzj)

struct BurnDriver BurnDrvCpsSfzj = {
	"sfzj", "sfa", NULL, "1995",
	"Street Fighter Zero (950727 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzjRomInfo, SfzjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Zero (Japan r1)
//==============================


static struct BurnRomInfo Sfzjr1RomDesc[] = {
	{ "sfzjx.03b",     0x80000, 0xb501f03c, 2 | BRF_ESS },

	{ "sfzj.03b",      0x80000, 0x844220c2, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",       0x80000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",       0x80000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzjr1) STD_ROM_FN(Sfzjr1)

struct BurnDriver BurnDrvCpsSfzjr1 = {
	"sfzjr1", "sfa", NULL, "1995",
	"Street Fighter Zero (950627 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfzjr1RomInfo, Sfzjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Zero (Japan r2)
//==============================


static struct BurnRomInfo Sfzjr2RomDesc[] = {
	{ "sfzjx.03a",     0x80000, 0x3cc138b5, 2 | BRF_ESS },

	{ "sfzj.03a",      0x80000, 0x3cfce93c, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04",        0x80000, 0x0c436d30, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05",        0x80000, 0x1f363612, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",        0x80000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzjr2) STD_ROM_FN(Sfzjr2)

struct BurnDriver BurnDrvCpsSfzjr2 = {
	"sfzjr2", "sfa", NULL, "1995",
	"Street Fighter Zero (950605 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfzjr2RomInfo, Sfzjr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Zero (Hispanic)
//==============================


static struct BurnRomInfo SfzhRomDesc[] = {
	{ "sfzhx.03c",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "sfzh.03c",     0x080000, 0xbce635aa, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.04a",      0x080000, 0x5f99e9a5, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",      0x080000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",       0x080000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzh) STD_ROM_FN(Sfzh)

struct BurnDriver BurnDrvCpsSfzh = {
	"sfzh", "sfa", NULL, "1995",
	"Street Fighter Zero (950627 Hispanic)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzhRomInfo, SfzhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Street Fighter Zero (Brazil)
//==============================


static struct BurnRomInfo SfzbRomDesc[] = {
	{ "sfzbx.03g",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "sfzb.03g",     0x080000, 0x348862d4, 1 | BRF_ESS | BRF_PRG },
	{ "sfzb.04e",     0x080000, 0x8d9b2480, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.05a",      0x080000, 0x0810544d, 1 | BRF_ESS | BRF_PRG },
	{ "sfz.06",       0x080000, 0x806e8f38, 1 | BRF_ESS | BRF_PRG },

	{ "sfz.14m",      0x200000, 0x90fefdb3, 3 | BRF_GRA },
	{ "sfz.16m",      0x200000, 0x5354c948, 3 | BRF_GRA },
	{ "sfz.18m",      0x200000, 0x41a1e790, 3 | BRF_GRA },
	{ "sfz.20m",      0x200000, 0xa549df98, 3 | BRF_GRA },

	{ "sfz.01",       0x020000, 0xffffec7d, 4 | BRF_ESS | BRF_PRG },
	{ "sfz.02",       0x020000, 0x45f46a08, 4 | BRF_ESS | BRF_PRG },

	{ "sfz.11m",      0x200000, 0xc4b093cd, 5 | BRF_SND },
	{ "sfz.12m",      0x200000, 0x8bdbc4b4, 5 | BRF_SND },
};


STD_ROM_PICK(Sfzb) STD_ROM_FN(Sfzb)

struct BurnDriver BurnDrvCpsSfzb = {
	"sfzb", "sfa", NULL, "1995",
	"Street Fighter Zero (951109 Brazil)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, SfzbRomInfo, SfzbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
