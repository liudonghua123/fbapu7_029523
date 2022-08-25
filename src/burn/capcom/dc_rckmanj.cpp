#include "cps.h"

/*================================
Rockman - The Power Battle (Japan)
==================================*/

static struct BurnInputInfo DrvInputList[] = {
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020 + 4, "p1 coin"   },
  {"P1 Start"      , BIT_DIGITAL, CpsInp020 + 0, "p1 start"  },
  {"P1 Up"         , BIT_DIGITAL, CpsInp001 + 3, "p1 up"     },
  {"P1 Down"       , BIT_DIGITAL, CpsInp001 + 2, "p1 down"   },
  {"P1 Left"       , BIT_DIGITAL, CpsInp001 + 1, "p1 left"   },
  {"P1 Right"      , BIT_DIGITAL, CpsInp001 + 0, "p1 right"  },
  {"P1 Attack"     , BIT_DIGITAL, CpsInp001 + 4, "p1 fire 1" },
  {"P1 Jump"       , BIT_DIGITAL, CpsInp001 + 5, "p1 fire 2" },
  {"P1 Select"     , BIT_DIGITAL, CpsInp001 + 6, "p1 fire 3" },

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020 + 5, "p2 coin"   },
  {"P2 Start"      , BIT_DIGITAL, CpsInp020 + 1, "p2 start"  },
  {"P2 Up"         , BIT_DIGITAL, CpsInp000 + 3, "p2 up"     },
  {"P2 Down"       , BIT_DIGITAL, CpsInp000 + 2, "p2 down"   },
  {"P2 Left"       , BIT_DIGITAL, CpsInp000 + 1, "p2 left"   },
  {"P2 Right"      , BIT_DIGITAL, CpsInp000 + 0, "p2 right"  },
  {"P2 Attack"     , BIT_DIGITAL, CpsInp000 + 4, "p2 fire 1" },
  {"P2 Jump"       , BIT_DIGITAL, CpsInp000 + 5, "p2 fire 2" },
  {"P2 Select"     , BIT_DIGITAL, CpsInp000 + 6, "p2 fire 3" },

  {"Reset"         , BIT_DIGITAL, &CpsReset    , "reset"     },
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021 + 1, "diag"      },
  {"Service"       , BIT_DIGITAL, CpsInp021 + 2, "service"   },
};

STDINPUTINFO(Drv);

/*=================================
 Rockman - The Power Battle (Japan)
==================================*/


static struct BurnRomInfo RckmanjRomDesc[] = {
	{ "rcmjx.03a"  , 0x080000, 0x00000000, 2 | BRF_ESS },
	{ "rcmjx.04a"  , 0x080000, 0x00000000, 2 | BRF_ESS },

	{ "rcmj.03a"   , 0x080000, 0x30559f60, 1 | BRF_ESS | BRF_PRG },
	{ "rcmj.04a"   , 0x080000, 0x5efc9366, 1 | BRF_ESS | BRF_PRG },
	{ "rcmj.05a"   , 0x080000, 0x517ccde2, 1 | BRF_ESS | BRF_PRG },

	{ "rcm.63m"    , 0x080000, 0xacad7c62, 3 | BRF_GRA },
	{ "rcm.64m"    , 0x080000, 0x65c0464e, 3 | BRF_GRA },
	{ "rcm.65m"    , 0x080000, 0xecedad3d, 3 | BRF_GRA },
	{ "rcm.66m"    , 0x080000, 0x1300eb7b, 3 | BRF_GRA },
	{ "rcm.73m"    , 0x080000, 0x774c6e04, 3 | BRF_GRA },
	{ "rcm.74m"    , 0x080000, 0x004ec725, 3 | BRF_GRA },
	{ "rcm.75m"    , 0x080000, 0x70a73f99, 3 | BRF_GRA },
	{ "rcm.76m"    , 0x080000, 0x89a889ad, 3 | BRF_GRA },
	{ "rcm.83m"    , 0x080000, 0x6af30499, 3 | BRF_GRA },
	{ "rcm.84m"    , 0x080000, 0xfb3097cc, 3 | BRF_GRA },
	{ "rcm.85m"    , 0x080000, 0x3d6186d8, 3 | BRF_GRA },
	{ "rcm.86m"    , 0x080000, 0x6d974ebd, 3 | BRF_GRA },
	{ "rcm.93m"    , 0x080000, 0x7a5a5166, 3 | BRF_GRA },
	{ "rcm.94m"    , 0x080000, 0x2e16557a, 3 | BRF_GRA },
	{ "rcm.95m"    , 0x080000, 0x8c7700f1, 3 | BRF_GRA },
	{ "rcm.96m"    , 0x080000, 0x7da4cd24, 3 | BRF_GRA },

	{ "rcm.01"     , 0x020000, 0xd60cf8a3, 4 | BRF_ESS | BRF_PRG },

	{ "rcm.51m"    , 0x080000, 0xb6d07080, 5 | BRF_SND },
	{ "rcm.52m"    , 0x080000, 0xdfddc493, 5 | BRF_SND },
	{ "rcm.53m"    , 0x080000, 0x6062ae3a, 5 | BRF_SND },
	{ "rcm.54m"    , 0x080000, 0x08c6f3bf, 5 | BRF_SND },
	{ "rcm.55m"    , 0x080000, 0xf97dfccc, 5 | BRF_SND },
	{ "rcm.56m"    , 0x080000, 0xade475bc, 5 | BRF_SND },
	{ "rcm.57m"    , 0x080000, 0x075effb3, 5 | BRF_SND },
	{ "rcm.58m"    , 0x080000, 0xf6c1f87b, 5 | BRF_SND },
};

STD_ROM_PICK(Rckmanj) STD_ROM_FN(Rckmanj)

struct BurnDriver BurnDrvCpsRckmanj = {
	"rckmanj", NULL, NULL, "1995",
	"Rockman - the power battle (950922 Japan)\0", "Encrypted", "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_CAPCOM_CPS2,
	NULL, RckmanjRomInfo, RckmanjRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame, CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
