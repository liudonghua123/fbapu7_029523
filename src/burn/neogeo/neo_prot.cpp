// FB Alpha Plus! Neo-Geo 68K Protection support file

/* =================================================================

PROTECTIONS INFO: (Info ripped and/or taked from MAME)
Thanks to IQ_132 for the major part of the comments and info.
NOTE: See neo_decrypt.cpp for chip decryption infos.

Unknown or earlier protections
------------------------------
- Fatal Fury 2:
  The game makes several ROM checks during the game, so the data
  changes all the time.
- Metal Slug X (Not emulated at all):
  The same as Fatal Fury 2 it seems maybe some sort of memory check,
  by now it's patched.
- The King of Fighters '98
  Uses a rom overlay feature, cheked at various points of the game.
  Also has a unique earlier encryption chip.

Neo-SMA SNK (c) 1999 Protection
-------------------------------
Thanks to:
Razoola -- http://cps2shock.retrogames.com/
- The King of Fighters '99
- Garou (sets 1 & 2)
- Metal Slug 3
- The King of Fighters 2000
  complex SMA chip which appears to contain part of the game rom
  internally and decrypts the 68k code on the board. Also has a
  random number generator and custom bankswitching.

Neo-PVC PLAYMORE (c) 2003 Protection
------------------------------------
Thanks to:
IQ_132 -- http://neosource.1emulation.com
bms888 -- http://bbs.jj.jx.cn
HalRIN -- http://www52.tok2.com/home/foge/
fataku -- http://?
- Metal Slug 5 (PCB & MVS)
- SvC Chaos: SNK vs. CAPCOM (PCB & MVS)
- The King of Fighters 2003 (PCB & MVS)
  consists in a byteswap + xor + adress scrambling, also needs to be
  interleaved (32 word swap instead of 16 byte swap like C-ROMs).
  Also this games have a bankswitch consisting in Pallete protections
  and extra RAM. (see d_neogeo.cpp for driver info)

Neo-Gambling (?) Protection
---------------------------
Thanks to:
IQ_132 -- http://neosource.1emulation.com
- Jockey Grand Prix
- V-Liner (sets 1 & 2)
  The gambling games are very interesting in that they both have extra
  banks of ram mapped at 0x200000 - 0x201FFF.
  This bank is used to store many variables including coin counters and
  setup information. (see neo_run.cpp for handler info)

==================================================================== */

#include "neogeo.h"

// ----------------------------------------------------------------------------
// Extra code for unknown protections
// ----------------------------------------------------------------------------

// Fatal Fury 2 Protection
// ====================================

/* ----------------------------------------------------------------------------

  fatfury2 uses a particularly evil protection scheme.  It writes
  data to particular offsets and then reads back the modified data.  The
  part that makes this protection bad is that it isn't noticable until
  after the first round.  After that, the game freaks out and it is
  impossible to hit your opponent.  The protection pops up again and again
  throughout the game doing particularly nasty things.

  Super Side Kicks also uses this protection method but not nearly as
  extensively as fatfury2

---------------------------------------------------------------------------- */

static int prot_data;

unsigned char __fastcall fatfury2ReadByteProtection(unsigned int sekAddress)
{
	unsigned short res = (prot_data >> 24) & 0xFF;

	switch (sekAddress) {
		case 0x255551:
		case 0x2FFFF1:
		case 0x200001:
		case 0x2FF001:

		case 0x236001:
		case 0x236009:
//			bprintf(PRINT_NORMAL, _T("  - prot read: 0x%02X (PC: 0x%06X)\n"), res, SekGetPC(-1));
			return res;

		case 0x236005:
		case 0x23600D:
//			bprintf(PRINT_NORMAL, _T("  - prot read: 0x%02X (PC: 0x%06X)\n"), ((res & 0xF0) >> 4) | ((res & 0x0F) << 4), SekGetPC(-1));
			return ((res & 0xF0) >> 4) | ((res & 0x0F) << 4);

//		default:
//			bprintf(PRINT_NORMAL, _T("  - prot 0x%06X read (PC: 0x%06X)\n"), sekAddress, SekGetPC(-1));
	}

	return 0;
}

void __fastcall fatfury2WriteByteProtection(unsigned int sekAddress, unsigned char /* byteValue */)
{
//	bprintf(PRINT_NORMAL, _T("  - prot 0x%06X -> 0x%02X (PC: 0x%06X)\n"), sekAddress, byteValue, SekGetPC(-1));

	switch (sekAddress) {
		case 0x255551:
		case 0x2FFFF1:
		case 0x2FF001:

		case 0x236001:
		case 0x236005:
		case 0x236009:
		case 0x23600D:
			prot_data <<= 8;
			break;

//		default:
//			bprintf(PRINT_NORMAL, _T("  - prot 0x%06X -> 0x%02X\n"), sekAddress, byteValue);
	}
}

void __fastcall fatfury2WriteWordProtection(unsigned int sekAddress, unsigned short /* wordValue */)
{
//	bprintf(PRINT_NORMAL, _T("  - prot 0x%06X -> 0x%04X (PC: 0x%06X)\n"), sekAddress, wordValue, SekGetPC(-1));

	switch (sekAddress) {
		case 0x211112:				// data = 0x1111, expects 0xFF000000 back
			prot_data = 0xFF000000;
/*
			prot_data  = (wordValue & 0x1000) << 19;
			prot_data |= (wordValue & 0x0100) << 22;
			prot_data |= (wordValue & 0x0010) << 25;
			prot_data |= (wordValue & 0x0001) << 28;

			prot_data |= prot_data >> 4;
*/
//			bprintf(PRINT_NORMAL, _T("    prot data -> 0x%08X\n"), prot_data);
			break;

		case 0x233332:				// data = 0x3333, expects 0x0000FFFF back
			prot_data = 0x0000FFFF;
/*
			prot_data  = wordValue << 0;
			prot_data |= wordValue << 2;
*/
//			bprintf(PRINT_NORMAL, _T("    prot data -> 0x%08X\n"), prot_data);
			break;

		case 0x244442:				// data = 0x4444, expects 0x00FF0000 back
			prot_data = 0x00FF0000;
/*
			prot_data  = (wordValue & 0x4000) <<  9;
			prot_data |= (wordValue & 0x0400) << 12;
			prot_data |= (wordValue & 0x0040) << 15;
			prot_data |= (wordValue & 0x0004) << 18;

			prot_data |= prot_data >> 4;
*/
//			bprintf(PRINT_NORMAL, _T("    prot data -> 0x%08X\n"), prot_data);
			break;

		case 0x255552:				// data == 0x5555; read back from 55550, ffff0, 00000, ff000
			prot_data = 0xFF00FF00;
			break;

		case 0x256782:				// data == 0x1234; read back from 36000 *or* 36004
			prot_data = 0xF05A3601;
			break;

		case 0x242812:				// data == 0x1824; read back from 36008 *or* 3600c
			prot_data = 0x81422418;
			break;

//		default:
//			bprintf(PRINT_NORMAL, _T("  - prot 0x%06X -> 0x%02X\n"), sekAddress, byteValue);
	}
}

// Install protection handler
void fatfury2ProtectionInstall()
{
	SekMapHandler(5,	 0x200000, 0x2FFFFF, SM_WRITE);
	SekMapHandler(5,	  0x200000, 0x2FFFFF, SM_READ);

	SekSetWriteWordHandler(5, fatfury2WriteWordProtection);
	SekSetWriteByteHandler(5, fatfury2WriteByteProtection);
	SekSetReadByteHandler(5,   fatfury2ReadByteProtection);
}


// The King of Fighters '98
// ====================================
static unsigned short nkof98Protection;

static void kof98Protection()
{
	// We need to writes because the BIOS vector block is actually 1024 bytes large
	switch (nkof98Protection) {
		case 0x0090:
			*((unsigned int*)Neo68KROM + 0x0100) = 0x00C200FD;
			SekWriteLongROM(0x000100, 0x00C200FD);
			break;
		case 0x00F0:
			*((unsigned int*)Neo68KROM + 0x0100) = 0x4E454F2D;
			SekWriteLongROM(0x000100, 0x4E454F2D);
			break;
	}
}

void __fastcall kof98WriteByteProtection(unsigned int sekAddress, unsigned char byteValue)
{
	switch (sekAddress) {
		case 0x20AAAA: {
			nkof98Protection &= 0x00FF;
			nkof98Protection |= byteValue << 8;
			kof98Protection();
		}
		case 0x20AAAB: {
			nkof98Protection &= 0xFF00;
			nkof98Protection |= byteValue;
			kof98Protection();
		}
	}
}

void __fastcall kof98WriteWordProtection(unsigned int sekAddress, unsigned short wordValue)
{
	switch (sekAddress) {
		case 0x20AAAA: {
			nkof98Protection = wordValue;
			kof98Protection();
		}
	}
}

// Install protection handler
void kof98ProtectionInstall()
{
	SekMapHandler(5,      0x200000, 0x2FFBFF, SM_WRITE);
	SekSetWriteWordHandler(5, kof98WriteWordProtection);
	SekSetWriteByteHandler(5, kof98WriteByteProtection);

	nkof98Protection = 0;
}


// Metal Slug X
// ====================================

/* ----------------------------------------------------------------------------

  Metal Slug X uses an Altera protection chip on its A board. It is not
  currently known what exactly this chip does, so if someone was to 
  send a mslugx cart to Razoola this game could finally be properly
  emulated.

----------------------------------------------------------------------------- */

void mslugxProtectionInstall()
{
	// most emulators use other patches, but I noticed that
	// you can simply patch one dWord and it seems to have the
	// same desired effect.

	// Protection seems to involve writing 0x2FFFE0-0x2FFFEA
	 *((unsigned short*)(Neo68KROM + 0x3C72)) = 0x4E75;
}


// ----------------------------------------------------------------------------
// Extra code for SMA protection
// ----------------------------------------------------------------------------
// General SMA & Random Number Generator bankswitch
// ================================================
int nSMARandomNumber;

static unsigned int nNeoSMARNGAddress[2] = { 0, 0 };

// Bank in an area of memory
void NeoSMABankswitch()
{
	SekMapMemory(Neo68KROM + nNeo68KROMBank, 0x200000, 0x2FE3FF, SM_ROM);
	if (nNeoSMARNGAddress[0] > 0 || nNeoSMARNGAddress[1] > 0) {
		SekMapMemory(Neo68KROM + nNeo68KROMBank + 0x0FE800, 0x2FE800, 0x2FFBFF, SM_ROM);
	} else {
		SekMapMemory(Neo68KROM + nNeo68KROMBank + 0x0FE800, 0x2FE800, 0x2FFFFF, SM_ROM);
	}
}

// Extra protection
unsigned short __fastcall neogeoReadWordSMA9A37(unsigned int sekAddress)
{
//	bprintf(PRINT_NORMAL, " -- SMA9A37 0x%08X (word)\n", sekAddress);

	if (sekAddress == 0x2FE446) {
		return 0x9A37;
	}

	return *((unsigned short*)(Neo68KROM + nNeo68KROMBank + sekAddress - 0x200000));
}

unsigned char __fastcall neogeoReadByteSMA9A37(unsigned int sekAddress)
{
//	bprintf(PRINT_NORMAL, " -- SMA9A37 0x%08X (byte)\n", sekAddress);

	if (sekAddress == 0x2FE446) {
		return 0x9A;
	}
	if (sekAddress == 0x2FE447) {
		return 0x37;
	}

	return Neo68KROM[(nNeo68KROMBank + sekAddress - 0x200000) ^ 1];
}

// Random number generator
unsigned short __fastcall neogeoReadWordSMARNG(unsigned int sekAddress)
{
	if (sekAddress == nNeoSMARNGAddress[0] || sekAddress == nNeoSMARNGAddress[1]) {
		int nRandomNubmer = nSMARandomNumber;

		int nNewbit = (
				(nSMARandomNumber >>  2) ^
				(nSMARandomNumber >>  3) ^
				(nSMARandomNumber >>  5) ^
				(nSMARandomNumber >>  6) ^
				(nSMARandomNumber >>  7) ^
				(nSMARandomNumber >> 11) ^
				(nSMARandomNumber >> 12) ^
				(nSMARandomNumber >> 15)) & 1;

		nSMARandomNumber = ((nSMARandomNumber << 1) | nNewbit) & 0x0FFFFF;

		return nRandomNubmer;
	}

	return *((unsigned short*)(Neo68KROM + nNeo68KROMBank + sekAddress - 0x200000));
}

unsigned char __fastcall neogeoReadByteSMARNG(unsigned int sekAddress)
{
	if ((sekAddress & ~1) == nNeoSMARNGAddress[0] || (sekAddress & ~1) == nNeoSMARNGAddress[1]) {
		int nRandomNubmer = nSMARandomNumber;

		int nNewbit = (
				(nSMARandomNumber >>  2) ^
				(nSMARandomNumber >>  3) ^
				(nSMARandomNumber >>  5) ^
				(nSMARandomNumber >>  6) ^
				(nSMARandomNumber >>  7) ^
				(nSMARandomNumber >> 11) ^
				(nSMARandomNumber >> 12) ^
				(nSMARandomNumber >> 15)) & 1;

		nSMARandomNumber = ((nSMARandomNumber << 1) | nNewbit) & 0x0FFFFF;

		if (sekAddress & 1) {
			return nRandomNubmer & 0xFF;
		} else {
			return nRandomNubmer >> 8;
		}
	}

	return Neo68KROM[(nNeo68KROMBank + sekAddress - 0x200000) ^ 1];
}

int NeoSMAScan(int nAction, int* /*pnMin*/)
{
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(nSMARandomNumber);
	}

	return 0;
}

// Per Game Bankswitch Handlers
// ================================================

// The King of Fighters '99
// ================================================
void __fastcall kof99WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFF0) {
		static unsigned int bankoffset[64] = {
			0x100000, 0x200000, 0x300000, 0x400000,
			0x4cc000, 0x5cc000, 0x4f2000, 0x5f2000,
			0x507800, 0x607800, 0x50d000, 0x60d000,
			0x517800, 0x617800, 0x520800, 0x620800,
			0x524800, 0x624800, 0x529000, 0x629000,
			0x52e800, 0x62e800, 0x531800, 0x631800,
			0x64d000, 0x651000, 0x667000, 0x692800,
			0x688800, 0x681800, 0x699800, 0x694800,
			0x598000,	// rest not used?
		};

		// Unscramble bank number
		int nBank = BITSWAP16(wordValue, 15, 0, 13, 4, 11, 3, 9, 2, 7, 1, 5, 12, 10, 8, 6, 14) & 0x3F;

		if (bankoffset[nBank] != nNeo68KROMBank) {
			nNeo68KROMBank = bankoffset[nBank];
			NeoSMABankswitch();
		}
	}
}

// Garou (set 1)
// ================================================
void __fastcall garouWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFC0) {
		static unsigned int bankoffset[64] = {
			0x100000, 0x200000, 0x300000, 0x400000, // 00
			0x380000, 0x480000, 0x3d0000, 0x4d0000, // 04
			0x3f0000, 0x4f0000, 0x500000, 0x600000, // 08
			0x520000, 0x620000, 0x540000, 0x640000, // 12
			0x598000, 0x698000, 0x5a0000, 0x6a0000, // 16
			0x5a8000, 0x6a8000, 0x5b0000, 0x6b0000, // 20
			0x5b8000, 0x6b8000, 0x5c0000, 0x6c0000, // 24
			0x5c8000, 0x6c8000, 0x5d0000, 0x6d0000, // 28
			0x558000, 0x658000, 0x560000, 0x660000, // 32
			0x568000, 0x668000, 0x570000, 0x670000, // 36
			0x578000, 0x678000, 0x580000, 0x680000, // 40
			0x588000, 0x688000, 0x590000, 0x690000, // 44
			0x6d0000, 0x6d8000, 0x6e0000, 0x6e8000, // 48
			0x6f0000, 0x6f8000, 0x700000, // rest not used?
		};

		// Unscramble bank number
		int nBank = BITSWAP16(wordValue, 15, 4, 13, 5, 11, 10, 1, 8, 2, 3, 12, 14, 6, 7, 9, 5) & 0x3F;

		if ((bankoffset[nBank]) != nNeo68KROMBank) {
			nNeo68KROMBank = bankoffset[nBank];
			NeoSMABankswitch();
		}
	}
}

// Garou (set 2)
// ================================================

void __fastcall garouoWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFC0) {
		static unsigned int bankoffset[64] = {
			0x100000, 0x200000, 0x300000, 0x400000, // 00
			0x380000, 0x480000, 0x3d0000, 0x4d0000, // 04
			0x3c8000, 0x4c8000, 0x500000, 0x600000, // 08
			0x520000, 0x620000, 0x540000, 0x640000, // 12
			0x698000, 0x798000, 0x6a0000, 0x7a0000, // 16
			0x6a8000, 0x7a8000, 0x6b0000, 0x7b0000, // 20
			0x6b8000, 0x7b8000, 0x6c0000, 0x7c0000, // 24
			0x6c8000, 0x7c8000, 0x6d0000, 0x7d0000, // 28
			0x558000, 0x658000, 0x560000, 0x660000, // 32
			0x568000, 0x668000, 0x570000, 0x670000, // 36
			0x578000, 0x678000, 0x580000, 0x680000, // 40
			0x588000, 0x688000, 0x590000, 0x690000, // 44
			0x6d8000, 0x7d8000, 0x6e0000, 0x7e0000, // 48
			0x6e8000, 0x7e8000, 0x7e8000, 0x100000, // 52
			0x100000, 0x100000, 0x100000, 0x100000, // 56
			0x100000, 0x100000, 0x100000, 0x100000, // 60
		};

		// Unscramble bank number
		int nBank = BITSWAP16(wordValue, 15, 3, 5, 12, 0, 10, 9, 1, 7, 6, 13, 11, 2, 14, 8, 4) & 0x3F;

		if ((bankoffset[nBank]) != nNeo68KROMBank) {
			nNeo68KROMBank = bankoffset[nBank];
			NeoSMABankswitch();
		}
	}
}

// Metal Slug 3
// ================================================
void __fastcall mslug3WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFE4) {
		static unsigned int bankoffset[64] = {
			0x100000, 0x120000, 0x140000, 0x160000, // 00
			0x170000, 0x190000, 0x1b0000, 0x1d0000, // 04
			0x1e0000, 0x1f0000, 0x220000, 0x230000, // 08
			0x240000, 0x250000, 0x280000, 0x290000, // 12
			0x2a0000, 0x2b0000, 0x2e0000, 0x2f0000, // 16
			0x300000, 0x310000, 0x340000, 0x350000, // 20
			0x360000, 0x370000, 0x3a0000, 0x3b0000, // 24
			0x3c0000, 0x3d0000, 0x400000, 0x410000, // 28
			0x420000, 0x430000, 0x460000, 0x470000, // 32
			0x480000, 0x490000, 0x4c0000, 0x4d0000, // 36
			0x500000, 0x510000, 0x540000, 0x550000, // 40
			0x560000, 0x570000, 0x5a0000, 0x5b0000, // 44
			0x5c0000, // rest not used?
		};

		// Unscramble bank number
		int nBank = BITSWAP16(wordValue, 2, 0, 13, 1, 11, 10, 5, 8, 7, 4, 9, 3, 6, 15, 12, 14) & 0x3F;

		if ((bankoffset[nBank]) != nNeo68KROMBank) {
			nNeo68KROMBank = bankoffset[nBank];
			NeoSMABankswitch();
		}
	}
}

// The King of Fighters 2000
// ================================================
void __fastcall kof2000WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFEC) {
		static unsigned int bankoffset[64] = {
			0x100000, 0x200000, 0x300000, 0x400000, // 00
			0x4f7800, 0x5f7800, 0x4ff800, 0x5ff800, // 04
			0x507800, 0x607800, 0x50f800, 0x60f800, // 08
			0x516800, 0x616800, 0x51d800, 0x61d800, // 12
			0x524000, 0x624000, 0x623800, 0x723800, // 16
			0x626000, 0x726000, 0x628000, 0x728000, // 20
			0x62a000, 0x72a000, 0x62b800, 0x72b800, // 24
			0x62d000, 0x72d000, 0x62e800, 0x72e800, // 28
			0x718000, 0x719000, 0x71a000, 0x71a800, // 32
		};

		// Unscramble bank number
		int nBank = BITSWAP16(wordValue, 0, 1, 13, 12, 11, 4, 9, 8, 2, 6, 5, 10, 3, 7, 14, 15) & 0x3F;

		if (bankoffset[nBank] != nNeo68KROMBank) {
			nNeo68KROMBank = bankoffset[nBank];
			NeoSMABankswitch();
		}
	}
}

// Install the memory handlers
// ================================================
int NeoSMAInit(int nSMADecrypt, pSekWriteWordHandler pBankswitchHandler, unsigned int nRNGAddress0, unsigned int nRNGAddress1)
{
	int nRet;

	nNeoSMASNKProtection = nSMADecrypt;
	pNeoBankswitchCallback = NeoSMABankswitch;
	pNeoScanCallback = NeoSMAScan;

	if ((nRet = NeoInit()) == 0) {
		SekMapHandler(4,	0x2FFC00, 0x2FFFFF, SM_WRITE);	// Bankswitch
		SekSetWriteWordHandler(4,   pBankswitchHandler);

		SekMapHandler(5,		0x2FE400, 0x2FE7FF, SM_ROM);	// Protection
		SekSetReadWordHandler(5, neogeoReadWordSMA9A37);
		SekSetReadByteHandler(5, neogeoReadByteSMA9A37);

		nNeoSMARNGAddress[0] = nRNGAddress0; nNeoSMARNGAddress[1] = nRNGAddress1;
		if (nNeoSMARNGAddress[0] > 0 || nNeoSMARNGAddress[1] > 0) {
			SekMapHandler(6,	0x2FFC00, 0x2FFFFF, SM_ROM);	// Randum number generator
			SekSetReadWordHandler(6, neogeoReadWordSMARNG);
			SekSetReadByteHandler(6, neogeoReadByteSMARNG);
		}
	}

	nSMARandomNumber = 0x2345;

	return nRet;
}

int NeoSMAExit()
{
	NeoExit();

	nNeoSMARNGAddress[0] = nNeoSMARNGAddress[1] = 0;

	return 0;
}


// ----------------------------------------------------------------------------
// Extra code for Neo-PVC Protection
// ----------------------------------------------------------------------------
// General Bankswitch & Protections for PVC Protected games
// ========================================================
unsigned short CartRAM[0x1000];

unsigned char pvc_r8(unsigned int sekAddress)
{
	return *(((unsigned char*)CartRAM) + ((sekAddress ^ 1) - 0x2fe000));
}

void pvc_w8(unsigned int sekAddress, unsigned char byteValue)
{
	*(((unsigned char*)CartRAM) + ((sekAddress ^ 1) - 0x2fe000)) = byteValue;
}

// These perform some palette calculations
// Unpack palette word to RGB dword, thanks to bms888
void NeoPVCPallette01() // on writes to e0/e1
{
	unsigned char b1, b2;
	b1 = pvc_r8(0x2fffe0);
	b2 = pvc_r8(0x2fffe1);

	pvc_w8(0x2fffe3,(((b2 >> 0) & 0xf) << 1) | ((b1 >> 4) & 1));
	pvc_w8(0x2fffe2,(((b2 >> 4) & 0xf) << 1) | ((b1 >> 5) & 1));
	pvc_w8(0x2fffe5,(((b1 >> 0) & 0xf) << 1) | ((b1 >> 6) & 1));
	pvc_w8(0x2fffe4, (b1 >> 7));
}

// pack RGB dword to palette word
void NeoPVCPallette02() // on writes to e8/e9/ea/eb
{
	unsigned char b1, b2, b3, b4;
	b1 = pvc_r8(0x2fffe8);
	b2 = pvc_r8(0x2fffe9);
	b3 = pvc_r8(0x2fffea);
	b4 = pvc_r8(0x2fffeb);

	pvc_w8(0x2fffed,(b2 >> 1) | ((b1 >> 1) << 4));
	pvc_w8(0x2fffec,(b4 >> 1) | ((b2 & 1) << 4) | ((b1 & 1) << 5) | ((b4 & 1) << 6) | ((b3 & 1) << 7));
}

void NeoPVCBankswitch() // on writes to f0-f3
{
	unsigned int nBank = (pvc_r8(0x2ffff2) << 16) | (pvc_r8(0x2ffff3) << 8) | (pvc_r8(0x2ffff0) << 0);
	*(((unsigned char*)CartRAM) + (0x2ffff0 - 0x2fe000)) = 0xA0; // Modified
	*(((unsigned char*)CartRAM) + (0x2ffff1 - 0x2fe000)) &= 0xFE;
	*(((unsigned char*)CartRAM) + (0x2ffff3 - 0x2fe000)) &= 0x7F;
	SekMapMemory(Neo68KROM + nBank + 0x100000, 0x200000, 0x2fdfff, SM_ROM);
}

unsigned char __fastcall PVCReadByteBankSwitch(unsigned int sekAddress)
{
	return pvc_r8(sekAddress);
}

unsigned short __fastcall PVCReadWordBankSwitch(unsigned int sekAddress)
{
	return CartRAM[(sekAddress - 0x2fe000) / 2];
}

void __fastcall PVCWriteByteBankSwitch(unsigned int sekAddress, unsigned char byteValue)
{
	pvc_w8(sekAddress, byteValue); // Write 1 byte
	if (sekAddress >= 0x2fffe0 && sekAddress <= 0x2fffe1) NeoPVCPallette01(); // pallete operation
	else if(sekAddress >= 0x2fffe8 && sekAddress <= 0x2fffeb) NeoPVCPallette02(); // pallete operation 2
	else if(sekAddress >= 0x2ffff0 && sekAddress <= 0x2ffff3) NeoPVCBankswitch(); // bankswitch
}

void __fastcall PVCWriteWordBankSwitch(unsigned int sekAddress, unsigned short wordValue)
{
	CartRAM[(sekAddress - 0x2fe000) / 2] = wordValue; // Write 1 word (2 bytes)
	if (sekAddress >= 0x2fffe0 && sekAddress <= 0x2fffe1) NeoPVCPallette01(); // pallete operation
	else if(sekAddress >= 0x2fffe8 && sekAddress <= 0x2fffeb) NeoPVCPallette02(); // pallete operation 2
	else if(sekAddress >= 0x2ffff0 && sekAddress <= 0x2ffff3) NeoPVCBankswitch(); // bankswitch
}

// This is needed for the scan function and savestates
int NeoPVCScan(int nAction, int* /*pnMin*/)
{
	struct BurnArea ba;

	if (nAction & ACB_MEMORY_RAM) {
		ba.Data		= (unsigned char*)CartRAM;
		ba.nLen		= 0x00002000;
		ba.nAddress	= 0;
		ba.szName	= "Neo-PVC 68K RAM";
		BurnAcb(&ba);
	}

	return 0;
}

// Install Normal BankSwitch handler
void PVCProtectionInstall()
{
	SekMapHandler(5,  0x2fe000,  0x2fffff,   SM_READ);
	SekSetReadWordHandler(5,   PVCReadWordBankSwitch);
	SekSetReadByteHandler(5,   PVCReadByteBankSwitch);

	SekMapHandler(5,  0x2fe000,  0x2fffff,  SM_WRITE);
	SekSetWriteWordHandler(5, PVCWriteWordBankSwitch);
	SekSetWriteByteHandler(5, PVCWriteByteBankSwitch);
}

// Install handlers
int NeoPVCInit(int nGameInit, void(*pBIOSCallBack)(),int nPCM2Value, int nTextDecValue)
{
	int nRet;
	extern unsigned char *Neo68KBIOS;

	// Reset Extra RAM for PVC games
	memset(CartRAM, 0, sizeof(CartRAM));

	nNeoPVCPLAYMOREProtection = nGameInit;
	pNeoBIOSCallback = pBIOSCallBack; // Does kf2k3pcb only use this?
	pNeoBankswitchCallback = NeoPVCBankswitch;
	pNeoScanCallback = NeoPVCScan;
	pNeoProtectionCallback = PVCProtectionInstall;

	// Special handlers for sound and text if necesary
	nNeoPCM2PLAYMOREProtection = nPCM2Value; // Neo-PCM2 PLAYMORE (c) type
	nNeoTextROMFixType = nTextDecValue; // Text encryption handler

	if ((nRet = NeoInit()) == 0) {
		if (nGameInit == 3) {
			// Handler for kof2003 BIOS
			SekMapMemory(Neo68KBIOS + 0x20000, 0xC20000, 0xC3FFFF, SM_ROM);
		}
	}

	return nRet;
}
