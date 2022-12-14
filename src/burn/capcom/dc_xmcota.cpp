// X-Men - children of the atom

#include "cps.h"

STDINPUTINFOSPEC(Drv, CpsFsi);

static int DrvInit()
{
	Xmcota = 1;

	return Cps2Init();
}

static int DrvExit()
{
	Xmcota = 0;

	return CpsExit();
}

//========================================
//X-Men - children of the atom (Euro v3.00)
//========================================


static struct BurnRomInfo XmcotaRomDesc[] = {
	{ "xmnex.03e",     0x80000, 0x2f5daa9f, 2 | BRF_ESS },			 // xor decryption table
	{ "xmnex.04e",     0x80000, 0xf0e24605, 2 | BRF_ESS },

	{ "xmne.03e",      0x80000, 0xa9a09b09, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xmne.04e",      0x80000, 0x52fa2106, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.05a",       0x80000, 0xac0d7759, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06a",       0x80000, 0x1b86a328, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07a",       0x80000, 0x2c142a44, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08a",       0x80000, 0xf712d44f, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09a",       0x80000, 0x9241cae8, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.10a",       0x80000, 0x53c0eab9, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


STD_ROM_PICK(Xmcota) STD_ROM_FN(Xmcota)

struct BurnDriver BurnDrvCpsXmcota = {
	"xmcota", NULL, NULL, "1995",
	"X-Men - children of the atom (950105 Euro)\0", "ver 3.00", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotaRomInfo, XmcotaRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=======================================
//X-Men - children of the atom (USA v3.00)
//=======================================


static struct BurnRomInfo XmcotauRomDesc[] = {
	{ "xmnux.03e",     0x80000, 0x27636ac7, 2 | BRF_ESS },			 // xor decryption table
	{ "xmnux.04e",     0x80000, 0x0aed300c, 2 | BRF_ESS },

	{ "xmnu.03e",      0x80000, 0x0bafeb0e, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xmnu.04e",      0x80000, 0xc29bdae3, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.05a",       0x80000, 0xac0d7759, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06a",       0x80000, 0x1b86a328, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07a",       0x80000, 0x2c142a44, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08a",       0x80000, 0xf712d44f, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09a",       0x80000, 0x9241cae8, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.10a",       0x80000, 0x53c0eab9, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


STD_ROM_PICK(Xmcotau) STD_ROM_FN(Xmcotau)

struct BurnDriver BurnDrvCpsXmcotau = {
	"xmcotau", "xmcota", NULL, "1995",
	"X-Men - children of the atom (US 950105)\0", "ver 3.00", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotauRomInfo, XmcotauRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=========================================
//X-Men - children of the atom (Japan v2.10)
//=========================================


static struct BurnRomInfo XmcotajRomDesc[] = {
	{ "xmnjx.03b",     0x80000, 0x523c9589, 2 | BRF_ESS },
	{ "xmnjx.04b",     0x80000, 0x673765ba, 2 | BRF_ESS },

	{ "xmnj.03b",      0x80000, 0xc8175fb3, 1 | BRF_ESS | BRF_PRG },
	{ "xmnj.04b",      0x80000, 0x54b3fba3, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.05",        0x80000, 0xc3ed62a2, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06",        0x80000, 0xf03c52e1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07",        0x80000, 0x325626b1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08",        0x80000, 0x7194ea10, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09",        0x80000, 0xae946df3, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.10",        0x80000, 0x32a6be1d, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


STD_ROM_PICK(Xmcotaj) STD_ROM_FN(Xmcotaj)

struct BurnDriver BurnDrvCpsXmcotaj = {
	"xmcotaj", "xmcota", NULL, "1994",
	"X-Men - children of the atom (941219 Japan)\0", "ver. 2.10", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotajRomInfo, XmcotajRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//============================================
//X-Men - children of the atom (Japan r1 v2.00)
//============================================


static struct BurnRomInfo Xmcotaj1RomDesc[] = {
	{ "xmnjx.03a",     0x80000, 0x515b9bf9, 2 | BRF_ESS },
	{ "xmnjx.04a",     0x80000, 0x5419572b, 2 | BRF_ESS },

	{ "xmnj.03a",      0x80000, 0x00761611, 1 | BRF_ESS | BRF_PRG },
	{ "xmnj.04a",      0x80000, 0x614d3f60, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.05",        0x80000, 0xc3ed62a2, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06",        0x80000, 0xf03c52e1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07",        0x80000, 0x325626b1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08",        0x80000, 0x7194ea10, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09",        0x80000, 0xae946df3, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.10",        0x80000, 0x32a6be1d, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Xmcotaj1) STD_ROM_FN(Xmcotaj1)

struct BurnDriver BurnDrvCpsXmcotaj1 = {
	"xmcotaj1", "xmcota", NULL, "1994",
	"X-Men - children of the atom (941217 Japan)\0", "ver. 2.00", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, Xmcotaj1RomInfo, Xmcotaj1RomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//==============================================
//X-Men - children of the atom (Japan rent v1.00)
//==============================================


static struct BurnRomInfo XmcotajrRomDesc[] = {
	{ "xmnox.03a",     0x80000, 0xc2d26e40, 2 | BRF_ESS },			 // xor decryption table
	{ "xmnox.04a",     0x80000, 0x9fb6b396, 2 | BRF_ESS },

	{ "xmno.03a",      0x80000, 0x7ab19acf, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.04a",      0x80000, 0x7615dd21, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.05a",      0x80000, 0x0303d672, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.06a",      0x80000, 0x332839a5, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.07",       0x80000, 0x6255e8d5, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.08",       0x80000, 0xb8ebe77c, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.09",       0x80000, 0x5440d950, 1 | BRF_ESS | BRF_PRG },
	{ "xmno.10a",      0x80000, 0xb8296966, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01",       0x020000, 0x7178336e, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02",       0x020000, 0x0ec58501, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


// Make The RomInfo/Name functions for the game
STD_ROM_PICK(Xmcotajr) STD_ROM_FN(Xmcotajr)

struct BurnDriver BurnDrvCpsXmcotajr = {
	"xmcotajr", "xmcota", NULL, "1994",
	"X-Men - children of the atom (941208 Japan)\0", "Rent version", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotajrRomInfo, XmcotajrRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//===========================================
//X-Men - children of the atom (Hispanic v???)
//===========================================


static struct BurnRomInfo XmcotahRomDesc[] = {
	{ "xmnhx.03",      0x80000, 0x00000000, 2 | BRF_ESS },			 // xor decryption table
	{ "xmnhx.04",      0x80000, 0x00000000, 2 | BRF_ESS },

	{ "xmnh.03",       0x80000, 0xe4b85a90, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xmnh.04",       0x80000, 0x7dfe1406, 1 | BRF_ESS | BRF_PRG },
	{ "xmnh.05",       0x80000, 0x87b0ed0f, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06a",       0x80000, 0x1b86a328, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07a",       0x80000, 0x2c142a44, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08a",       0x80000, 0xf712d44f, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09a",       0x80000, 0x9241cae8, 1 | BRF_ESS | BRF_PRG },
	{ "xmnh.10",       0x80000, 0xcb36b0a4, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


STD_ROM_PICK(Xmcotah) STD_ROM_FN(Xmcotah)

struct BurnDriver BurnDrvCpsXmcotah = {
	"xmcotah", "xmcota", NULL, "1995",
	"X-Men - children of the atom (950331 Hispanic)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotahRomInfo, XmcotahRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

//=======================================
//X-Men - children of the atom (Asia v???)
//=======================================


static struct BurnRomInfo XmcotaaRomDesc[] = {
	{ "xmnax.03a",     0x80000, 0x978a0de4, 2 | BRF_ESS },			 // xor decryption table
	{ "xmnax.04a",     0x80000, 0x07cb0839, 2 | BRF_ESS },

	{ "xmna.03a",      0x80000, 0x7df8b27e, 1 | BRF_ESS | BRF_PRG }, // 68000 code (encrypted)
	{ "xmna.04a",      0x80000, 0xb44e30a7, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.05",        0x80000, 0xc3ed62a2, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.06",        0x80000, 0xf03c52e1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.07",        0x80000, 0x325626b1, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.08",        0x80000, 0x7194ea10, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.09",        0x80000, 0xae946df3, 1 | BRF_ESS | BRF_PRG },
	{ "xmn.10",        0x80000, 0x32a6be1d, 1 | BRF_ESS | BRF_PRG },
	// 10
	{ "xmn.13m",      0x400000, 0xbf4df073, 3 | BRF_GRA },			 // Graphics
	{ "xmn.15m",      0x400000, 0x4d7e4cef, 3 | BRF_GRA },
	{ "xmn.17m",      0x400000, 0x513eea17, 3 | BRF_GRA },
	{ "xmn.19m",      0x400000, 0xd23897fc, 3 | BRF_GRA },
	{ "xmn.14m",      0x400000, 0x778237b7, 3 | BRF_GRA },
	{ "xmn.16m",      0x400000, 0x67b36948, 3 | BRF_GRA },
	{ "xmn.18m",      0x400000, 0x015a7c4c, 3 | BRF_GRA },
	{ "xmn.20m",      0x400000, 0x9dde2758, 3 | BRF_GRA },
	// 18
	{ "xmn.01a",      0x020000, 0x40f479ea, 4 | BRF_ESS | BRF_PRG }, // Z80 code
	{ "xmn.02a",      0x020000, 0x39d9b5ad, 4 | BRF_ESS | BRF_PRG },
	// sound - samples
	{ "xmn.11m",      0x200000, 0xc848a6bc, 5 | BRF_SND },			 // QSound data
	{ "xmn.12m",      0x200000, 0x729c188f, 5 | BRF_SND },
};


STD_ROM_PICK(Xmcotaa) STD_ROM_FN(Xmcotaa)

struct BurnDriver BurnDrvCpsXmcotaa = {
	"xmcotaa", "xmcota", NULL, "1995",
	"X-Men - children of the atom (941217 Asia)\0", "ver. 2.00", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_CAPCOM_CPS2,
	NULL, XmcotaaRomInfo, XmcotaaRomName, DrvInputInfo, NULL,
	DrvInit, DrvExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
