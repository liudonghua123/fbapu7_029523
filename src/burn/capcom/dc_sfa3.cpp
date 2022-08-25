// Street Fighter Alpha 3

#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

// announcer codes are between 100 and 13a if anyone wants to disable them

//============================
//Street Fighter Alpha 3 (USA)
//============================


static struct BurnRomInfo Sfa3RomDesc[] = {
	{ "sz3ux.03c",     0x80000, 0x7091276b, 2 | BRF_ESS },
	{ "sz3ux.04c",     0x80000, 0x83b213b1, 2 | BRF_ESS },

	{ "sz3u.03c",      0x80000, 0xe007da2e, 1 | BRF_ESS | BRF_PRG },
	{ "sz3u.04c",      0x80000, 0x5f78f0e7, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05c",       0x80000, 0x57fd0a40, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06c",       0x80000, 0xf6305f8b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07c",       0x80000, 0x6eab0f6f, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08c",       0x80000, 0x910c4a3b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09c",       0x80000, 0xb29e5199, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10b",       0x80000, 0xdeb2ff52, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(Sfa3) STD_ROM_FN(Sfa3)

struct BurnDriver BurnDrvCpsSfa3 = {
	"sfa3", NULL, NULL, "1998",
	"Street Fighter Alpha 3 (980904 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfa3RomInfo, Sfa3RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===============================
//Street Fighter Alpha 3 (USA r1)
//===============================


static struct BurnRomInfo Sfa3r1RomDesc[] = {
	{ "sz3ux.03",      0x80000, 0x42994875, 2 | BRF_ESS },
	{ "sz3ux.04",      0x80000, 0x86ee79e3, 2 | BRF_ESS },

	{ "sz3u.03",       0x80000, 0xb5984a19, 1 | BRF_ESS | BRF_PRG },
	{ "sz3u.04",       0x80000, 0x7e8158ba, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05",        0x80000, 0x9b21518a, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06",        0x80000, 0xe7a6c3a7, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07",        0x80000, 0xec4c0cfd, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08",        0x80000, 0x5c7e7240, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09",        0x80000, 0xc5589553, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10",        0x80000, 0xa9717252, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(Sfa3r1) STD_ROM_FN(Sfa3r1)

struct BurnDriver BurnDrvCpsSfa3r1 = {
	"sfa3r1", "sfa3", NULL, "1998",
	"Street Fighter Alpha 3 (980629 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfa3r1RomInfo, Sfa3r1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================
//Street Fighter Zero 3 (Japan)
//=============================


static struct BurnRomInfo Sfz3jRomDesc[] = {
	{ "sz3jx.03c",     0x80000, 0xf46c83d9, 2 | BRF_ESS },
	{ "sz3jx.04c",     0x80000, 0x66fc9322, 2 | BRF_ESS },

	{ "sz3j.03c",      0x80000, 0xcadf4a51, 1 | BRF_ESS | BRF_PRG },
	{ "sz3j.04c",      0x80000, 0xfcb31228, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05c",       0x80000, 0x57fd0a40, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06c",       0x80000, 0xf6305f8b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07c",       0x80000, 0x6eab0f6f, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08c",       0x80000, 0x910c4a3b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09c",       0x80000, 0xb29e5199, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10b",       0x80000, 0xdeb2ff52, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz3j) STD_ROM_FN(Sfz3j)

struct BurnDriver BurnDrvCpsSfz3j = {
	"sfz3j", "sfa3", NULL, "1998",
	"Street Fighter Zero 3 (980904 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz3jRomInfo, Sfz3jRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================
//Street Fighter Zero 3 (Japan r1)
//================================


static struct BurnRomInfo Sfz3jr1RomDesc[] = {
	{ "sz3jx.03a",     0x80000, 0xb2f4046d, 2 | BRF_ESS },
	{ "sz3jx.04a",     0x80000, 0x85c38642, 2 | BRF_ESS },

	{ "sz3j.03a",      0x80000, 0x6ee0beae, 1 | BRF_ESS | BRF_PRG },
	{ "sz3j.04a",      0x80000, 0xa6e2978d, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05a",       0x80000, 0x05964b7d, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06a",       0x80000, 0x78ce2179, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07a",       0x80000, 0x398bf52f, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08a",       0x80000, 0x866d0588, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09a",       0x80000, 0x2180892c, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10",        0x80000, 0xa9717252, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz3jr1) STD_ROM_FN(Sfz3jr1)

struct BurnDriver BurnDrvCpsSfz3jr1 = {
	"sfz3jr1", "sfa3", NULL, "1998",
	"Street Fighter Zero 3 (980727 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz3jr1RomInfo, Sfz3jr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================
//Street Fighter Zero 3 (Japan r2)
//================================


static struct BurnRomInfo Sfz3jr2RomDesc[] = {
	{ "sz3jx.03",      0x80000, 0xacd88307, 2 | BRF_ESS },
	{ "sz3jx.04",      0x80000, 0x2c15655b, 2 | BRF_ESS },

	{ "sz3j.03",       0x80000, 0xf7cb4b13, 1 | BRF_ESS | BRF_PRG },
	{ "sz3j.04",       0x80000, 0x0846c29d, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05",        0x80000, 0x9b21518a, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06",        0x80000, 0xe7a6c3a7, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07",        0x80000, 0xec4c0cfd, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08",        0x80000, 0x5c7e7240, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09",        0x80000, 0xc5589553, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10",        0x80000, 0xa9717252, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(Sfz3jr2) STD_ROM_FN(Sfz3jr2)

struct BurnDriver BurnDrvCpsSfz3jr2 = {
	"sfz3jr2", "sfa3", NULL, "1998",
	"Street Fighter Zero 3 (980629 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfz3jr2RomInfo, Sfz3jr2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================
//Street Fighter Zero 3 (Asia)
//================================


static struct BurnRomInfo sfz3ar1RomDesc[] = {
	{ "sz3ax.03a",     0x80000, 0xf3ad39ac, 2 | BRF_ESS },
	{ "sz3ax.04",      0x80000, 0x792527ca, 2 | BRF_ESS },

	{ "sz3a.03a",      0x80000, 0x29c681fd, 1 | BRF_ESS | BRF_PRG },
	{ "sz3a.04",       0x80000, 0x9ddd1484, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05",        0x80000, 0x9b21518a, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06",        0x80000, 0xe7a6c3a7, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07",        0x80000, 0xec4c0cfd, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08",        0x80000, 0x5c7e7240, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09",        0x80000, 0xc5589553, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10",        0x80000, 0xa9717252, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};


STD_ROM_PICK(sfz3ar1) STD_ROM_FN(sfz3ar1)

struct BurnDriver BurnDrvCpssfz3ar1 = {
	"sfz3ar1", "sfa3", NULL, "1998",
	"Street Fighter Zero 3 (980701 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, sfz3ar1RomInfo, sfz3ar1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===============================
//Street Fighter Alpha 3 (Brazil)
//===============================


static struct BurnRomInfo Sfa3bRomDesc[] = {
	{ "sz3bx.03",	  0x80000,  0x00000000, 2 | BRF_ESS },
	{ "sz3bx.04",	  0x80000,  0x00000000, 2 | BRF_ESS },

	{ "sz3b.03",	  0x80000,  0x046c9b4d, 1 | BRF_ESS | BRF_PRG },
	{ "sz3b.04",	  0x80000,  0xda211919, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05",	  0x80000,  0x9b21518a, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06",	  0x80000,  0xe7a6c3a7, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07",	  0x80000,  0xec4c0cfd, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08",	  0x80000,  0x5c7e7240, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09",	  0x80000,  0xc5589553, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10",	  0x80000,  0xa9717252, 1 | BRF_ESS | BRF_PRG },

	{ "sz3.13m",      0x400000, 0x0f7a60d9, 3 | BRF_GRA },
	{ "sz3.15m",      0x400000, 0x8e933741, 3 | BRF_GRA },
	{ "sz3.17m",      0x400000, 0xd6e98147, 3 | BRF_GRA },
	{ "sz3.19m",      0x400000, 0xf31a728a, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};

STD_ROM_PICK(Sfa3b) STD_ROM_FN(Sfa3b)

struct BurnDriver BurnDrvCpsSfa3b = {
	"sfa3b", "sfa3", NULL, "1998",
	"Street Fighter Alpha 3 (980629 Brazil)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfa3bRomInfo, Sfa3bRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================
//Street Fighter Alpha 3 (Brasil)
//================================


static struct BurnRomInfo Sfa3brRomDesc[] = {
	{ "sz3ux.03c"    ,0x80000,  0x7091276b, 2 | BRF_ESS },
	{ "sz3ux.04c"    ,0x80000,  0x83b213b1, 2 | BRF_ESS },

	{ "sz3br.03c"    ,0x80000,  0xcf889cdc, 1 | BRF_ESS | BRF_PRG },
	{ "sz3br.04c"    ,0x80000,  0xa47733c4, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.05c"      ,0x80000,  0x57fd0a40, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.06c"      ,0x80000,  0xf6305f8b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.07c"      ,0x80000,  0x6eab0f6f, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.08c"      ,0x80000,  0x910c4a3b, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.09c"      ,0x80000,  0xb29e5199, 1 | BRF_ESS | BRF_PRG },
	{ "sz3.10b"      ,0x80000,  0xdeb2ff52, 1 | BRF_ESS | BRF_PRG },

	{ "sz3br.13",	  0x400000, 0xf18ffe2d, 3 | BRF_GRA },
	{ "sz3br.15",	  0x400000, 0x3283878c, 3 | BRF_GRA },
	{ "sz3br.17",	  0x400000, 0x869e0ae2, 3 | BRF_GRA },
	{ "sz3br.19",	  0x400000, 0x81e0ebfa, 3 | BRF_GRA },
	{ "sz3.14m",      0x400000, 0x5ff98297, 3 | BRF_GRA },
	{ "sz3.16m",      0x400000, 0x52b5bdee, 3 | BRF_GRA },
	{ "sz3.18m",      0x400000, 0x40631ed5, 3 | BRF_GRA },
	{ "sz3.20m",      0x400000, 0x763409b4, 3 | BRF_GRA },

	{ "sz3.01",       0x020000, 0xde810084, 4 | BRF_ESS | BRF_PRG },
	{ "sz3.02",       0x020000, 0x72445dc4, 4 | BRF_ESS | BRF_PRG },

	{ "sz3.11m",      0x400000, 0x1c89eed1, 5 | BRF_SND },
	{ "sz3.12m",      0x400000, 0xf392b13a, 5 | BRF_SND },
};

STD_ROM_PICK(Sfa3br) STD_ROM_FN(Sfa3br)

struct BurnDriver BurnDrvCpsSfa3br = {
	"sfa3br", "sfa3", NULL, "2004",
	"Street Fighter Alpha 3 (040716 Brazil)\0", "Translation ROM - Portuguese BRA", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG,2,HARDWARE_CAPCOM_CPS2,
	NULL, Sfa3brRomInfo, Sfa3brRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
