#include "cps.h"

/*=====================================
 Marvel Super Heroes vs Street Fighter
 All-in-One Driver 1.30 by LoopMaster
=====================================*/

STDINPUTINFOSPEC(Drv, CpsFsi);

/*============================================
Marvel Super Heroes  vs Street Fighter (Euro)
============================================*/

static struct BurnRomInfo MshvsfRomDesc[] = {
	{ "mvsex.03f",     0x80000, 0         , 2 | BRF_ESS },
	{ "mvsex.04f",     0x80000, 0         , 2 | BRF_ESS },

	{ "mvse.03f",      0x80000, 0xb72dc199, 1 | BRF_ESS | BRF_PRG },
	{ "mvse.04f",      0x80000, 0x6ef799f9, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsf) STD_ROM_FN(Mshvsf)

struct BurnDriver BurnDrvCpsMshvsf = {
	"mshvsf", NULL, NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Euro)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	0,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfRomInfo, MshvsfRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*============================================
Marvel Super Heroes  vs Street Fighter (USA)
============================================*/

static struct BurnRomInfo MshvsfuRomDesc[] = {
	{ "mvsux.03g",     0x80000, 0x17b12a95, 2 | BRF_ESS },
	{ "mvsux.04g",     0x80000, 0xf98200cf, 2 | BRF_ESS },

	{ "mvsu.03g",      0x80000, 0x0664ab15, 1 | BRF_ESS | BRF_PRG },
	{ "mvsu.04g",      0x80000, 0x97e060ee, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05d",       0x80000, 0x921fc542, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfu) STD_ROM_FN(Mshvsfu)

struct BurnDriver BurnDrvCpsMshvsfu = {
	"mshvsfu", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970827 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfuRomInfo, MshvsfuRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*============================================
Marvel Super Heroes  vs Street Fighter (USA r1)
============================================*/

static struct BurnRomInfo Mshvsfu1RomDesc[] = {
	{ "mvsux.03d",     0x80000, 0x281bcb48, 2 | BRF_ESS },
	{ "mvsux.04d",     0x80000, 0xa2d68628, 2 | BRF_ESS },

	{ "mvsu.03d",      0x80000, 0xae60a66a, 1 | BRF_ESS | BRF_PRG },
	{ "mvsu.04d",      0x80000, 0x91f67d8a, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfu1) STD_ROM_FN(Mshvsfu1)

struct BurnDriver BurnDrvCpsMshvsfu1 = {
	"mshvsfu1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfu1RomInfo, Mshvsfu1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*==============================================
Marvel Super Heroes  vs Street Fighter (Japan)
==============================================*/

static struct BurnRomInfo MshvsfjRomDesc[] = {
	{ "mvsjx.03i",     0x80000, 0x55170c4c, 2 | BRF_ESS },
	{ "mvsjx.04i",     0x80000, 0xe7883768, 2 | BRF_ESS },

	{ "mvsj.03i",      0x80000, 0xd8cbb691, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04i",      0x80000, 0x32741ace, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05h",       0x80000, 0x77870dc3, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj) STD_ROM_FN(Mshvsfj)

struct BurnDriver BurnDrvCpsMshvsfj = {
	"mshvsfj", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970707 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfjRomInfo, MshvsfjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*=================================================
Marvel Super Heroes  vs Street Fighter (Japan r1)
=================================================*/

static struct BurnRomInfo Mshvsfj1RomDesc[] = {
	{ "mvsjx.03h",     0x80000, 0x6b4201c1, 2 | BRF_ESS },
	{ "mvsjx.04h",     0x80000, 0xab1b04cc, 2 | BRF_ESS },

	{ "mvsj.03h",      0x80000, 0xfbe2115f, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04h",      0x80000, 0xb528a367, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05g",       0x80000, 0x9515a245, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj1) STD_ROM_FN(Mshvsfj1)

struct BurnDriver BurnDrvCpsMshvsfj1 = {
	"mshvsfj1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970702 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfj1RomInfo, Mshvsfj1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*=================================================
Marvel Super Heroes  vs Street Fighter (Japan r2) Encrypted
=================================================*/

static struct BurnRomInfo Mshvsfj2RomDesc[] = {
	{ "mvsjx.03g",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvsjx.04g",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvsj.03g",      0x80000, 0xfdfa7e26, 1 | BRF_ESS | BRF_PRG },
	{ "mvsj.04g",      0x80000, 0xc921825f, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfj2) STD_ROM_FN(Mshvsfj2)

struct BurnDriver BurnDrvCpsMshvsfj2 = {
	"mshvsfj2", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Japan)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfj2RomInfo, Mshvsfj2RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*===========================================================
Marvel Super Heroes  vs Street Fighter (Hispanic) Encrypted
===========================================================*/

static struct BurnRomInfo MshvsfhRomDesc[] = {
	{ "mvshx.03f",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvshx.04f",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvsh.03f",      0x80000, 0x4f60f41e, 1 | BRF_ESS | BRF_PRG },
	{ "mvsh.04f",      0x80000, 0xdc08ec12, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfh) STD_ROM_FN(Mshvsfh)

struct BurnDriver BurnDrvCpsMshvsfh = {
	"mshvsfh", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Hispanic)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfhRomInfo, MshvsfhRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*=======================================================
Marvel Super Heroes  vs Street Fighter (Asia) Encrypted
=======================================================*/

static struct BurnRomInfo MshvsfaRomDesc[] = {
	{ "mvsax.03d",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvsax.04d",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvsa.03d",      0x80000, 0x5b863716, 1 | BRF_ESS | BRF_PRG },
	{ "mvsa.04d",      0x80000, 0x4886e65f, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05a",       0x80000, 0x1a5de0cb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfa) STD_ROM_FN(Mshvsfa)

struct BurnDriver BurnDrvCpsMshvsfa = {
	"mshvsfa", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Asia)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfaRomInfo, MshvsfaRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*==========================================================
Marvel Super Heroes  vs Street Fighter (Asia r1) Encrypted
==========================================================*/

static struct BurnRomInfo Mshvsfa1RomDesc[] = {
	{ "mvsax.03",      0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvsax.04",      0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvsa.03",       0x80000, 0x92ef1933, 1 | BRF_ESS | BRF_PRG },
	{ "mvsa.04",       0x80000, 0x4b24373c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05",        0x80000, 0xac180c1c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfa1) STD_ROM_FN(Mshvsfa1)

struct BurnDriver BurnDrvCpsMshvsfa1 = {
	"mshvsfa1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970620 Asia)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfa1RomInfo, Mshvsfa1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};


/*===========================================================
Marvel Super Heroes  vs Street Fighter (Brazil) Encrypted
===========================================================*/

static struct BurnRomInfo MshvsfbRomDesc[] = {
	{ "mvsbx.03g",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "mvsbx.04g",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "mvsb.03g",      0x80000, 0x143895ef, 1 | BRF_ESS | BRF_PRG },
	{ "mvsb.04g",      0x80000, 0xdd8a886c, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.05d",       0x80000, 0x921fc542, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.06a",       0x80000, 0x959f3030, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.07b",       0x80000, 0x7f915bdb, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.08a",       0x80000, 0xc2813884, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.09b",       0x80000, 0x3ba08818, 1 | BRF_ESS | BRF_PRG },
	{ "mvs.10b",       0x80000, 0xcf0dba98, 1 | BRF_ESS | BRF_PRG },

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};


STD_ROM_PICK(Mshvsfb) STD_ROM_FN(Mshvsfb)

struct BurnDriver BurnDrvCpsMshvsfb = {
	"mshvsfb", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970827 Brazil)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, MshvsfbRomInfo, MshvsfbRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

/*===========================================================
Marvel Super Heroes  Vs. Street Fighter (Brazil r1) Encrypted
===========================================================*/

static struct BurnRomInfo Mshvsfb1RomDesc[] = {
	{"mvsbx.03f",	  0x80000,  0x00000000, 2 | BRF_ESS},
	{"mvsbx.04f",	  0x80000,  0x00000000, 2 | BRF_ESS},

	{"mvsb.03f" ,	  0x80000,  0x9c4bb950, 1 | BRF_ESS | BRF_PRG},
	{"mvsb.04f" ,	  0x80000,  0xd3320d13, 1 | BRF_ESS | BRF_PRG},
	{"mvs.05a"  ,	  0x80000,  0x1a5de0cb, 1 | BRF_ESS | BRF_PRG},
	{"mvs.06a"  ,	  0x80000,  0x959f3030, 1 | BRF_ESS | BRF_PRG},
	{"mvs.07b"  ,	  0x80000,  0x7f915bdb, 1 | BRF_ESS | BRF_PRG},
	{"mvs.08a"  ,	  0x80000,  0xc2813884, 1 | BRF_ESS | BRF_PRG},
	{"mvs.09b"  ,	  0x80000,  0x3ba08818, 1 | BRF_ESS | BRF_PRG},
	{"mvs.10b"  ,	  0x80000,  0xcf0dba98, 1 | BRF_ESS | BRF_PRG},

	{ "mvs.13m",      0x400000, 0x29b05fd9, 3 | BRF_GRA },
	{ "mvs.15m",      0x400000, 0xfaddccf1, 3 | BRF_GRA },
	{ "mvs.17m",      0x400000, 0x97aaf4c7, 3 | BRF_GRA },
	{ "mvs.19m",      0x400000, 0xcb70e915, 3 | BRF_GRA },
	{ "mvs.14m",      0x400000, 0xb3b1972d, 3 | BRF_GRA },
	{ "mvs.16m",      0x400000, 0x08aadb5d, 3 | BRF_GRA },
	{ "mvs.18m",      0x400000, 0xc1228b35, 3 | BRF_GRA },
	{ "mvs.20m",      0x400000, 0x366cc6c2, 3 | BRF_GRA },

	{ "mvs.01",       0x020000, 0x68252324, 4 | BRF_ESS | BRF_PRG },
	{ "mvs.02",       0x020000, 0xb34e773d, 4 | BRF_ESS | BRF_PRG },

	{ "mvs.11m",      0x400000, 0x86219770, 5 | BRF_SND },
	{ "mvs.12m",      0x400000, 0xf2fd7f68, 5 | BRF_SND },
};

STD_ROM_PICK(Mshvsfb1) STD_ROM_FN(Mshvsfb1)

struct BurnDriver BurnDrvCpsMshvsfb1 = {
	"mshvsfb1", "mshvsf", NULL, "1997",
	"Marvel Super Heroes vs Street Fighter (970625 Brazil)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Mshvsfb1RomInfo, Mshvsfb1RomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
