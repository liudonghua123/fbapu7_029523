// Super Street Fighter II

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

//============================
//Super Street Fighter II (World)
//============================


static struct BurnRomInfo Ssf2RomDesc[] = {
// 0
	{ "ssfex.03",      0x80000, 0x29690c24, 2 | BRF_ESS },			 // xor decryption tables
	{ "ssfex.04",      0x80000, 0xd001e53a, 2 | BRF_ESS },
	{ "ssfex.05",      0x80000, 0xa45602e4, 2 | BRF_ESS },
	{ "ssfex.06",      0x80000, 0xae3c8a14, 2 | BRF_ESS },
	{ "ssfex.07",      0x80000, 0xf88f584e, 2 | BRF_ESS },
// 5
	{ "ssfe.03",       0x80000, 0xa597745d, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "ssfe.04",       0x80000, 0xb082aa67, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.05",       0x80000, 0x02b9c137, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.06",       0x80000, 0x70d470c5, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.07",       0x80000, 0x2409001d, 1 | BRF_ESS | BRF_PRG },
// 10
	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
// 18
	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },
// 19
	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2) STD_ROM_FN(Ssf2)

struct BurnDriver BurnDrvCpsSsf2 = {
	"ssf2", NULL, NULL, "1993",
	"Super Street Fighter II - the new challengers (930911 World)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2RomInfo, Ssf2RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============================
//Super Street Fighter II (USA)
//============================


static struct BurnRomInfo Ssf2uRomDesc[] = {
// 0
	{ "ssfux.03a",     0x80000, 0xec278279, 2 | BRF_ESS },			 // xor decryption tables
	{ "ssfux.04a",     0x80000, 0x6194d896, 2 | BRF_ESS },
	{ "ssfux.05",      0x80000, 0xaa846b9f, 2 | BRF_ESS },
	{ "ssfux.06",      0x80000, 0x235268c4, 2 | BRF_ESS },
	{ "ssfux.07",      0x80000, 0xe46e033c, 2 | BRF_ESS },
// 5
	{ "ssfu.03a",      0x80000, 0x72f29c33, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "ssfu.04a",      0x80000, 0x935cea44, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.05",       0x80000, 0xa0acb28a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.06",       0x80000, 0x47413dcf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfu.07",       0x80000, 0xe6066077, 1 | BRF_ESS | BRF_PRG },
// 10
	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },
// 18
	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },
// 19
	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2u) STD_ROM_FN(Ssf2u)

struct BurnDriver BurnDrvCpsSsf2u = {
	"ssf2u", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (930911 USA)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2uRomInfo, Ssf2uRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================
//Super Street Fighter II (Japan)
//==============================


static struct BurnRomInfo Ssf2jRomDesc[] = {
	{ "ssfjx.03b",     0x80000, 0x693985dd, 2 | BRF_ESS },
	{ "ssfjx.04a",     0x80000, 0xf866d34a, 2 | BRF_ESS },
	{ "ssfjx.05",      0x80000, 0x7282bb56, 2 | BRF_ESS },
	{ "ssfjx.06b",     0x80000, 0xc597bc4a, 2 | BRF_ESS },
	{ "ssfjx.07",      0x80000, 0x2af7cab2, 2 | BRF_ESS },

	{ "ssfj.03b",      0x80000, 0x5c2e356d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04a",      0x80000, 0x013bd55c, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06b",      0x80000, 0x014e0c6d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2j) STD_ROM_FN(Ssf2j)

struct BurnDriver BurnDrvCpsSsf2j = {
	"ssf2j", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (931005 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jRomInfo, Ssf2jRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================================
//Super Street Fighter II (Japan r1)
//=================================


static struct BurnRomInfo Ssf2jr1RomDesc[] = {
	{ "ssfjx.03a",     0x80000, 0xc1b1d0c1, 2 | BRF_ESS },
	{ "ssfjx.04a",     0x80000, 0xf866d34a, 2 | BRF_ESS },
	{ "ssfjx.05",      0x80000, 0x7282bb56, 2 | BRF_ESS },
	{ "ssfjx.06",      0x80000, 0xcc027506, 2 | BRF_ESS },
	{ "ssfjx.07",      0x80000, 0x2af7cab2, 2 | BRF_ESS },

	{ "ssfj.03a",      0x80000, 0x0bbf1304, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04a",      0x80000, 0x013bd55c, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06",       0x80000, 0xd808a6cd, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2jr1) STD_ROM_FN(Ssf2jr1)

struct BurnDriver BurnDrvCpsSsf2jr1 = {
	"ssf2jr1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (930911 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jr1RomInfo, Ssf2jr1RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=================================
//Super Street Fighter II (Japan r2)
//=================================


static struct BurnRomInfo Ssf2jr2RomDesc[] = {
	{ "ssfjx.03",      0x80000, 0xc3eca34c, 2 | BRF_ESS },
	{ "ssfjx.04",      0x80000, 0x4e1080c2, 2 | BRF_ESS },
	{ "ssfjx.05",      0x80000, 0x7282bb56, 2 | BRF_ESS },
	{ "ssfjx.06",      0x80000, 0xcc027506, 2 | BRF_ESS },
	{ "ssfjx.07",      0x80000, 0x2af7cab2, 2 | BRF_ESS },

	{ "ssfj.03",       0x80000, 0x7eb0efed, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.04",       0x80000, 0xd7322164, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.05",       0x80000, 0x0918d19a, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.06",       0x80000, 0xd808a6cd, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.07",       0x80000, 0xeb6a9b1b, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2jr2) STD_ROM_FN(Ssf2jr2)

struct BurnDriver BurnDrvCpsSsf2jr2 = {
	"ssf2jr2", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (930910 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2jr2RomInfo, Ssf2jr2RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//================================
//Super Street Fighter II (Asia r1)
//================================


static struct BurnRomInfo Ssf2ar1RomDesc[] = {
	{ "ssfax.03a",     0x80000, 0xd628422c, 2 | BRF_ESS },
	{ "ssfax.04a",     0x80000, 0x99d5e67f, 2 | BRF_ESS },
	{ "ssfax.05",      0x80000, 0xd104f415, 2 | BRF_ESS },
	{ "ssfax.06",      0x80000, 0x210e787c, 2 | BRF_ESS },
	{ "ssfax.07",      0x80000, 0xca49b7f6, 2 | BRF_ESS },

	{ "ssfa.03a",      0x80000, 0xd2a3c520, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.04a",      0x80000, 0x5d873642, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.05",       0x80000, 0xf8fb4de2, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.06",       0x80000, 0xaa8acee7, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.07",       0x80000, 0x36e29217, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2ar1) STD_ROM_FN(Ssf2ar1)

struct BurnDriver BurnDrvCpsSsf2ar1 = {
	"ssf2ar1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (930914 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2ar1RomInfo, Ssf2ar1RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=============================
//Super Street Fighter II (Asia)
//=============================


static struct BurnRomInfo Ssf2aRomDesc[] = {
	{ "ssfax.03b",     0x80000, 0x903b997e, 2 | BRF_ESS },
	{ "ssfax.04a",     0x80000, 0x99d5e67f, 2 | BRF_ESS },
	{ "ssfax.05",      0x80000, 0xd104f415, 2 | BRF_ESS },
	{ "ssfax.06b",     0x80000, 0x16516200, 2 | BRF_ESS },
	{ "ssfax.07",      0x80000, 0xca49b7f6, 2 | BRF_ESS },

	{ "ssfa.03b",      0x80000, 0x83a059bf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.04a",      0x80000, 0x5d873642, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.05",       0x80000, 0xf8fb4de2, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.06b",      0x80000, 0x3185d19d, 1 | BRF_ESS | BRF_PRG },
	{ "ssfa.07",       0x80000, 0x36e29217, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2a) STD_ROM_FN(Ssf2a)

struct BurnDriver BurnDrvCpsSsf2a = {
	"ssf2a", "ssf2", NULL, "1993",
	"Super Street Fighter II - the new challengers (931005 Asia)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2aRomInfo, Ssf2aRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================
//Super Street Fighter II - T.B. (World)
//====================================


static struct BurnRomInfo Ssf2tbRomDesc[] = {
	{ "ssfex.3tc",     0x80000, 0x9b2cda8c, 2 | BRF_ESS },
	{ "ssfex.4tc",     0x80000, 0x62d26dc2, 2 | BRF_ESS },
	{ "ssfex.5t",      0x80000, 0x3ae42ff3, 2 | BRF_ESS },
	{ "ssfex.6tb",     0x80000, 0xf12e7228, 2 | BRF_ESS },
	{ "ssfex.7t",      0x80000, 0x4d51f760, 2 | BRF_ESS },

	{ "ssfe.3tc",      0x80000, 0x496a8409, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.4tc",      0x80000, 0x4b45c18b, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.5t",       0x80000, 0x6a9c6444, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.6tb",      0x80000, 0xe4944fc3, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.7t",       0x80000, 0x2c9f4782, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tb) STD_ROM_FN(Ssf2tb)

struct BurnDriver BurnDrvCpsSsf2tb = {
	"ssf2tb", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (931119 World)\0", "Linkup feature not implemented", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tbRomInfo, Ssf2tbRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=========================================
//Super Street Fighter II - T.B. (World r1)
//=========================================


static struct BurnRomInfo ssf2tbr1RomDesc[] = {
	{ "ssfex.3t",      0x80000, 0         , 2 | BRF_ESS },
	{ "ssfex.4t",      0x80000, 0         , 2 | BRF_ESS },
	{ "ssfex.5t",      0x80000, 0         , 2 | BRF_ESS },
	{ "ssfex.6t",      0x80000, 0         , 2 | BRF_ESS },
	{ "ssfex.7t",      0x80000, 0         , 2 | BRF_ESS },

	{ "ssfe.3t",       0x80000, 0x1e018e34, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.4t",       0x80000, 0xac92efaf, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.5t",       0x80000, 0x6a9c6444, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.6t",       0x80000, 0xf442562b, 1 | BRF_ESS | BRF_PRG },
	{ "ssfe.7t",       0x80000, 0x2c9f4782, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(ssf2tbr1) STD_ROM_FN(ssf2tbr1)

struct BurnDriver BurnDrvCpsssf2tbr1 = {
	"ssf2tbr1", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (930911 World)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, ssf2tbr1RomInfo, ssf2tbr1RomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//====================================
//Super Street Fighter II - T.B. (Japan)
//====================================


static struct BurnRomInfo Ssf2tbjRomDesc[] = {
	{ "ssfjx.03t",     0x80000, 0x00000000, 2 | BRF_ESS },			 // xor decryption tables
	{ "ssfjx.04t",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "ssfjx.05t",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "ssfjx.06t",     0x80000, 0x00000000, 2 | BRF_ESS },
	{ "ssfjx.07t",     0x80000, 0x00000000, 2 | BRF_ESS },

	{ "ssfj.3t",       0x80000, 0x980d4450, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.4t",       0x80000, 0xb4dc1906, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.5t",       0x80000, 0xa7e35fbc, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.6t",       0x80000, 0xcb592b30, 1 | BRF_ESS | BRF_PRG },
	{ "ssfj.7t",       0x80000, 0x1f239515, 1 | BRF_ESS | BRF_PRG },

	{ "ssf.13m",      0x200000, 0xcf94d275, 3 | BRF_GRA },
	{ "ssf.15m",      0x200000, 0x5eb703af, 3 | BRF_GRA },
	{ "ssf.17m",      0x200000, 0xffa60e0f, 3 | BRF_GRA },
	{ "ssf.19m",      0x200000, 0x34e825c5, 3 | BRF_GRA },
	{ "ssf.14m",      0x100000, 0xb7cc32e7, 3 | BRF_GRA },
	{ "ssf.16m",      0x100000, 0x8376ad18, 3 | BRF_GRA },
	{ "ssf.18m",      0x100000, 0xf5b1b336, 3 | BRF_GRA },
	{ "ssf.20m",      0x100000, 0x459d5c6b, 3 | BRF_GRA },

	{ "ssf.01",       0x020000, 0xeb247e8c, 4 | BRF_ESS | BRF_PRG },

	{ "ssf.q01",      0x080000, 0xa6f9da5c, 5 | BRF_SND },
	{ "ssf.q02",      0x080000, 0x8c66ae26, 5 | BRF_SND },
	{ "ssf.q03",      0x080000, 0x695cc2ca, 5 | BRF_SND },
	{ "ssf.q04",      0x080000, 0x9d9ebe32, 5 | BRF_SND },
	{ "ssf.q05",      0x080000, 0x4770e7b7, 5 | BRF_SND },
	{ "ssf.q06",      0x080000, 0x4e79c951, 5 | BRF_SND },
	{ "ssf.q07",      0x080000, 0xcdd14313, 5 | BRF_SND },
	{ "ssf.q08",      0x080000, 0x6f5a088c, 5 | BRF_SND },
};


STD_ROM_PICK(Ssf2tbj) STD_ROM_FN(Ssf2tbj)

struct BurnDriver BurnDrvCpsSsf2tbj = {
	"ssf2tbj", "ssf2", NULL, "1993",
	"Super Street Fighter II - the tournament battle (930910 Japan)\0", "Encrypted, Linkup feature not implemented", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Ssf2tbjRomInfo, Ssf2tbjRomName, DrvInputInfo, NULL,
	DrvInit, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
