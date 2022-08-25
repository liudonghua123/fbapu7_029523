#include "cps.h"

/*=======================================================
Marvel vs Capcom All-in-One Driver 1.50 by Treble Winner
=======================================================*/

STDINPUTINFOSPEC(Drv, CpsFsi);


/*=====================
Marvel vs Capcom (Euro)
=====================*/


static struct BurnRomInfo MvscRomDesc[] = {
	{ "mvcex.03",      0x80000, 0         , 2 | BRF_ESS },
	{ "mvcex.04",      0x80000, 0         , 2 | BRF_ESS },

	{ "mvce.03",       0x80000, 0xe0633fc0, 1 | BRF_ESS | BRF_PRG },
	{ "mvce.04",       0x80000, 0xa450a251, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05",        0x80000, 0x7db71ce9, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06",        0x80000, 0x4b0b6d3e, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvsc) STD_ROM_FN(Mvsc)

struct BurnDriver BurnDrvCpsMvsc = {
	"mvsc", NULL, NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980112 Euro)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	0,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvscRomInfo, MvscRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*=====================
Marvel vs Capcom (USA)
=====================*/


static struct BurnRomInfo MvscuRomDesc[] = {
	{ "mvcux.03d",     0x80000, 0x86685cbf, 2 | BRF_ESS },
	{ "mvcux.04d",     0x80000, 0x438ba92b, 2 | BRF_ESS },

	{ "mvcu.03d",      0x80000, 0xc6007557, 1 | BRF_ESS | BRF_PRG },
	{ "mvcu.04d",      0x80000, 0x724b2b20, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05a",       0x80000, 0x2d8c8e86, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06a",       0x80000, 0x8528e1f5, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvscu) STD_ROM_FN(Mvscu)

struct BurnDriver BurnDrvCpsMvscu = {
	"mvscu", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980123 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvscuRomInfo, MvscuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*=======================
Marvel vs Capcom (Japan)
=======================*/


static struct BurnRomInfo MvscjRomDesc[] = {
	{ "mvcjx.03a",     0x80000, 0xe696a098, 2 | BRF_ESS },
	{ "mvcjx.04a",     0x80000, 0x7faeee82, 2 | BRF_ESS },

	{ "mvcj.03a",      0x80000, 0x3df18879, 1 | BRF_ESS | BRF_PRG },
	{ "mvcj.04a",      0x80000, 0x07d212e8, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05a",       0x80000, 0x2d8c8e86, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06a",       0x80000, 0x8528e1f5, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvscj) STD_ROM_FN(Mvscj)

struct BurnDriver BurnDrvCpsMvscj = {
	"mvscj", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980123 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvscjRomInfo, MvscjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*==========================
Marvel vs Capcom (Japan r1)
==========================*/


static struct BurnRomInfo Mvscjr1RomDesc[] = {
	{ "mvcjx.03",      0x80000, 0xcc94ab89, 2 | BRF_ESS },
	{ "mvcjx.04",      0x80000, 0xc5a83202, 2 | BRF_ESS },

	{ "mvcj.03",       0x80000, 0x2164213f, 1 | BRF_ESS | BRF_PRG },
	{ "mvcj.04",       0x80000, 0xc905c86f, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05",        0x80000, 0x7db71ce9, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06",        0x80000, 0x4b0b6d3e, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvscjr1) STD_ROM_FN(Mvscjr1)

struct BurnDriver BurnDrvCpsMvscjr1 = {
	"mvscjr1", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980112 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mvscjr1RomInfo, Mvscjr1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*======================
Marvel vs Capcom (Asia)
======================*/


static struct BurnRomInfo Mvscar1RomDesc[] = {
	{ "mvcax.03",      0x80000, 0x4512a6af, 2 | BRF_ESS },
	{ "mvcax.04",      0x80000, 0xe6f537d2, 2 | BRF_ESS },

	{ "mvca.03",       0x80000, 0xfe5fa7b9, 1 | BRF_ESS | BRF_PRG },
	{ "mvca.04",       0x80000, 0x082b701c, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05",        0x80000, 0x7db71ce9, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06",        0x80000, 0x4b0b6d3e, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvscar1) STD_ROM_FN(Mvscar1)

struct BurnDriver BurnDrvCpsMvscar1 = {
	"mvscar1", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980112 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mvscar1RomInfo, Mvscar1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*==========================
Marvel vs Capcom (Hispanic)
==========================*/


static struct BurnRomInfo MvschRomDesc[] = {
	{ "mvchx.03",      0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvchx.04",      0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvch.03",       0x80000, 0x6a0ec9f7, 1 | BRF_ESS | BRF_PRG },
	{ "mvch.04",       0x80000, 0x00f03fa4, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05a",       0x80000, 0x2d8c8e86, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06a",       0x80000, 0x8528e1f5, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",        0x80000, 0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",        0x80000, 0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",        0x80000, 0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",        0x80000, 0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};


STD_ROM_PICK(Mvsch) STD_ROM_FN(Mvsch)

struct BurnDriver BurnDrvCpsMvsch = {
	"mvsch", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980123 Hispanic)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvschRomInfo, MvschRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*=========================
Marvel Vs. Capcom (Brazil)
==========================*/


static struct BurnRomInfo MvscbRomDesc[] = {
	{ "mvcbx.03a",	  0x80000,  0x00000000, 2 | BRF_ESS },
	{ "mvcbx.04a",	  0x80000,  0x00000000, 2 | BRF_ESS },

	{ "mvcb.03a",	  0x80000,  0x7155953b, 1 | BRF_ESS | BRF_PRG },
	{ "mvcb.04a",	  0x80000,  0xfb117d0e, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.05a",	  0x80000,  0x2d8c8e86, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.06a",	  0x80000,  0x8528e1f5, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.07",	  0x80000,  0xc3baa32b, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.08",	  0x80000,  0xbc002fcd, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.09",	  0x80000,  0xc67b26df, 1 | BRF_ESS | BRF_PRG },
	{ "mvc.10",	  0x80000,  0x0fdd1e26, 1 | BRF_ESS | BRF_PRG },

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};

STD_ROM_PICK(Mvscb) STD_ROM_FN(Mvscb)

struct BurnDriver BurnDrvCpsMvscb = {
	"mvscb", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980123 Brazil)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvscbRomInfo, MvscbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*======================
Marvel Vs. Capcom (Asia)
======================*/


static struct BurnRomInfo MvscaRomDesc[] = {
	{ "mvcax.03a",	  0x80000,  0x00000000, 2 | BRF_ESS},
	{ "mvcax.04a",	  0x80000,  0x00000000, 2 | BRF_ESS},

	{ "mvca.03a",	  0x80000,  0xfe5fa7b9, 1 | BRF_ESS | BRF_PRG},
	{ "mvca.04a",	  0x80000,  0x082b701c, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.05a",	  0x80000,  0x2d8c8e86, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.06a",	  0x80000,  0x8528e1f5, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.07",	  0x80000,  0xc3baa32b, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.08",	  0x80000,  0xbc002fcd, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.09",	  0x80000,  0xc67b26df, 1 | BRF_ESS | BRF_PRG},
	{ "mvc.10",	  0x80000,  0x0fdd1e26, 1 | BRF_ESS | BRF_PRG},

	{ "mvc.13m",      0x400000, 0xfa5f74bc, 3 | BRF_GRA },
	{ "mvc.15m",      0x400000, 0x71938a8f, 3 | BRF_GRA },
	{ "mvc.17m",      0x400000, 0x92741d07, 3 | BRF_GRA },
	{ "mvc.19m",      0x400000, 0xbcb72fc6, 3 | BRF_GRA },
	{ "mvc.14m",      0x400000, 0x7f1df4e4, 3 | BRF_GRA },
	{ "mvc.16m",      0x400000, 0x90bd3203, 3 | BRF_GRA },
	{ "mvc.18m",      0x400000, 0x67aaf727, 3 | BRF_GRA },
	{ "mvc.20m",      0x400000, 0x8b0bade8, 3 | BRF_GRA },

	{ "mvc.01",       0x020000, 0x41629e95, 4 | BRF_ESS | BRF_PRG },
	{ "mvc.02",       0x020000, 0x963abf6b, 4 | BRF_ESS | BRF_PRG },

	{ "mvc.11m",      0x400000, 0x850fe663, 5 | BRF_SND },
	{ "mvc.12m",      0x400000, 0x7ccb1896, 5 | BRF_SND },
};

STD_ROM_PICK(Mvsca) STD_ROM_FN(Mvsca)

struct BurnDriver BurnDrvCpsMvsca = {
	"mvsca", "mvsc", NULL, "1998",
	"Marvel vs Capcom - clash of super heroes (980123 Asia)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MvscaRomInfo, MvscaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
