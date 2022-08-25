// FB Alpha Plus! Neo-Geo bootleg Driver module

/* =======================================================================================

   Special thanks to IQ_132 for the info about the bootleg carts and their
   protections, the comments can be seen in the "Per game handlers" section
   and all around the file.

==========================================================================================
   Neo-Geo Bootleg custom encryption & protections
   (info taked from MAME -- http://www.mame.net/)
  
      Many of the NeoGeo bootlegs use their own form of encryption and
      protection, presumably to make them harder for other bootleggser to
      copy.  This encryption often involves non-trivial scrambling of the
      program roms and the games are protected using an Altera chip which
      provides some kind of rom overlay, patching parts of the code.
      The graphics roms are usually scrambled in a different way to the
      official SNK cartridges too.
  
      In addition to this info, text layers, z80 and samples are protected
      by using bankswaps and some sort of adress scrambling. Some 68K ROMs
      shows a custom bankswitch, or the same that is originaly in the real
      game, but with some small modifications.

==========================================================================================

   Neo-Geo CD Hacks:
   (info from IQ_132 -- http://neosource.1emulation.com/)
      Zintrick is one of two Neo-Geo CD games that was:
       A. Not available in MVS format.
       B. Small enough and easy enough to hack to make it run as a stand-alone Neo-Geo
          rom.

      Here are some simple instructions to convert from Neo-Geo CD to MVS:

      - Take the program rom L.PRG, byteswap it, and swap the bytes at offset:
      0x68&0x69 with the bytes at 0x6A&0x6B respectively.  This is vitally imporatant.
      - There was a small error when loading the rom, it complains about the Z80 rom,
      the hackers simply changed the text in the rom.
      - The next step is to simply rename the FIX.FIX to whatever you want. (this is the s1)
      - Then rename the SW.Z80 to whatever you want (this is the m1)
      - Next, copy the first 8 .PCM roms tegether and rename them.  (This is the V1)
      - Last, you must convert the Cx roms.  SW.SPR is the Cx rom.  You must first byteswap
      the rom, then dissect it wordwise (two bytes at a time).  The first file is the C1
      and the second is the C2.

      It's as simple as that :)

==========================================================================================

   About some layouts and unconfirmed bootlegs:

      Some bootleg sets are unconfirmed, either because they aren't redumped or because
      they are fakes, by now the list of confirmed, unconfirmed and fake bootlegs is
      shown below. Maybe a redump should confirm the rest of the bootlegs.

      Confirmed Bootleg sets:
-----------------------------      
      - The King of Fighters '96 Plus (Maybe Extra Plus?)
      - The King of Fighters '97 Plus (sets 1 and 2)
      - King of Gladiator
      - Lansquenet 2004
      - The King of Fighters 2001 (bootleg)
      - The King of Fighters 2001 Plus (sets 1 and 2)
      - Crouching Tiger Hidden Dragon 2003 (sets 1 and 2)
      - Crouching Tiger Hidden Dragon 2003 Super Plus
      - Metal Slug 4 Plus
      - The King of Fighters 2002 (bootleg)
      - The King of Fighters 2002 Plus (sets 1, 2 and 3)
      - The King of Fighters 2002 Super
      - The King of Fighters 2002 Magic Plus
      - The King of Fighters 2002 Magic Plus II
      - The King of Fighters Special Edition 2004
      - The King of Fighters Special Edition 2004 Plus
      - The King of Fighters 10th Anniversary
      - The King of Fighters 10th Anniversary Extra Plus
      - The King of Fighters 10th Anniversary 2005 Unique (sets 1 and 2)
      - Matrimelee (bootleg)
      - Metal Slug 5 (bootleg)
      - Metal Slug 5 Plus
      - Metal Slug 6 (bootleg)
      - SNK vs CAPCOM (bootleg)
      - SNK vs CAPCOM Plus (sets 1 and 2)
      - SNK vs CAPCOM Super Plus
      - Samurai Shodown V (bootleg)
      - The King of Fighters 2003 (Bootleg, sets 1 and 2)
      - The King of Fighters 2004 EX Hero
      - The King of Fighters 2004 EX Ultra Plus

      Unconfirmed Bootleg sets:
-------------------------------
      - The King of Fighters Special Edition 2004 Plus (set 2? blue english "EXTRA PLUS")
      - SNK vs CAPCOM Super Plus (set 2?, not added, no info available yet, blue english "PLUS")
      - SNK vs CAPCOM Super Plus X (not added, no info available yet)

      Fake Bootleg sets:
------------------------
      - Metal Slug 4 (bootleg, just watermarked decrypted C-ROMs and V-ROMs)
      - The King of Fighters Special Edition 2004 Magic Plus (handmade-PC hack)
      - SNK vs CAPCOM Super Plus (set 2, chinesse orange letters "PLUS")


      About the unconfirmed sets, no one was able to confirm if they are real or not
      I saw most of them running on MVS system but if there is not a redump this
      cannot be confirmed. Anyway they are supported until is confirmed if they are
      fakes or not.
      The fake bootlegs are just watermarked ROMs or even handmade-Hex-Hacked ROMs
      just to show something different or add something new to them, but not made
      directly by the bootlegger and then "burned" the info in a real chip.

      Some bootlegs seems that are made by the same bootleggers, for example kog,
      lans2004 and samsh5bl, or ms4plus and kf2k2spr... because the layouts and
      porotections are similar compaing them, some new bootlegs use protection
      for sprites and even z80 and samples, but some sets older that 2002 don't.
      Svcboot and ms5boot seems to come from the same bootlegger too, so maybe
      uses encrypted (scrambled) sprite and sample data. Not confirmed if the
      68K had an extra encryption in adittion to the bankswitch.

      About some layouts:
         - Is not confirmed that kf2k1pla uses the bootleg ROMs...
           Is confirmed that it uses the AES second program ROM, so maybe sprite
           data should come from a decrypted AES cart, in short, the decrypted
           C-ROMs from kof2001 (that uses the same set as kof2001h).
         - The z80 ROMs in some games like kf2k2pls or svcplus/a is correct, the
           lack of some data in them is present too in the real carts.
         - Kf2k3bl and clones have some similar names, that are the real chip
           labels anyway the sprite data and sound doesn't seem to be 100% correct,
           and yes as the MAME team says, they DO have zoom effect problems, they
           are spected to use the PCB BIOS data, not the standard Neo-Geo BIOS set.
         - Some ROM names were changed according to real chip labels, if there is
           something incorrect, I should fix it as soon as I get the real data.
         - kof2k2bl uses decrypted (watermarked?) samples, not PCM2 encrypted ROMs, due
           the lack of the PCM2 chip in the bootleg cart.
         - Ms6boot is supposed to be protected only with the header at the end of the
           P2 ROM?... someone told me that it had at least a bitswap or something...
           This thing is also supposed to have 14 sprite chips... and the cart shows
           3 altera chips on it, maybe for sprite, text and 68K decryption? Nothing
           is confirmed by now.
           Just for those that are wondering, this is a hack / bootleg from mslug3,
           mslug6 will only be released for Sammy hardware (Atomiswave) which is
           currently unknown how it works.

======================================================================================= */

#include "neogeo.h"

// =======================================================================================
// Common handlers for custom encryption or protections
// =======================================================================================

// ---------------------------------------------------------------------------------------
// Neo-Geo Bootleg Sprite data encryption handlers
// Original code by IQ_132 - http://neosource.1emulation.com/
void DoPerm(int nGame) // 0 - cthd2003 / matrimbl, 1 - svcboot
{
	unsigned int idx[2][0x10] = {
		{ 0, 1, 2, 3, 3, 4, 4, 5, 0, 1, 2, 3, 3, 4, 4, 5 }, // cthd2003 / matrimbl
		{ 0, 1, 0, 1, 2, 3, 2, 3, 3, 4, 3, 4, 4, 5, 4, 5 }, // svcboot
	};

	unsigned int tbl[6][4] = {
		{ 3, 0, 1, 2 },
		{ 2, 3, 0, 1 },
		{ 1, 2, 3, 0 },
		{ 0, 1, 2, 3 },
		{ 3, 2, 1, 0 },
		{ 3, 0, 2, 1 },
	};

	unsigned char tmp[0x800];

	BurnUpdateProgress(0.0, _T("Decrypting bootleg graphics..."), 0);
	for(int i = 0; i < 0x8000; i++) {
		for(int j = 0; j < 16; j++)	{
			unsigned int *b = tbl[idx[nGame][(i>>(5-nGame))&0xF]];
			int ofst = BITSWAP08(j, 7, 6, 5, 4, b[3], b[2], b[1], b[0]);
			memcpy(tmp + j * 0x80, NeoSpriteROM + (i * 0x800) + ofst * 0x80, 0x80);
		}
		memcpy(NeoSpriteROM + i * 0x800, tmp, 0x800);
	}
}

// Decryption code by IQ_132 -- http;//neosource.1emulation.com/
static void kof2k2bl_gfx_decrypt(unsigned char* rom, int size)
{
	int t[8][10] = {
		{ 0, 8, 7, 3, 4, 5, 6, 2, 1 },
		{ 1, 0, 8, 4, 5, 3, 7, 6, 2 },
		{ 2, 1, 0, 3, 4, 5, 8, 7, 6 },
		{ 6, 2, 1, 5, 3, 4, 0, 8, 7 },
		{ 7, 6, 2, 5, 3, 4, 1, 0, 8 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8 },
		{ 2, 1, 0, 4, 5, 3, 6, 7, 8 },
		{ 8, 0, 7, 3, 4, 5, 6, 2, 1 },
	};

	unsigned char* tmp = (unsigned char*)malloc(0x10000);

	BurnUpdateProgress(0.0, _T("Decrypting bootleg graphics..."), 0);
	for (int i = 0; i < size; i += 0x10000) {
		memcpy(tmp, rom + i, 0x10000);

		for (int j = 0; j < 0x200; j++) {
			int *n = t[(j % 0x40) /8];
			int ofst = BITSWAP16(j, 15, 14, 13, 12, 11, 10, 9, n[0], n[1], n[2], n[3], n[4], n[5], n[6], n[7], n[8]);
			memcpy(rom + i + ofst * 128, tmp + j * 128, 128);
		}
	}
	free(tmp);
}

// Thanks to:
// Halrin -- http://www52.tok2.com/home/foge/
// IQ_132 -- http;//neosource.1emulation.com/
static void neo_boot_gfx_decrypt(int nSize)
{
	BurnUpdateProgress(0.0, _T("Decrypting bootleg graphics..."), 0);
	unsigned char *cso = (unsigned char*)malloc(64);
	for (int i = 0; i < nSize; i += 128) {
		memcpy (cso, NeoSpriteROM + i + 64, 64);
		memcpy (NeoSpriteROM + i + 64, NeoSpriteROM + i, 64);
		memcpy (NeoSpriteROM + i, cso, 64);
	}
	free(cso);
}

// ---------------------------------------------------------------------------------------
// Neo-Geo Bootleg Text Data decryption
void neo_boot_text_decrypt(int nGame)
{
	unsigned char* tmp = (unsigned char*)malloc(nNeoTextROMSize);

	BurnUpdateProgress(0.0, _T("Decrypting bootleg text layer graphics..."), 0);
	switch (nGame) {
		// Original code for MAME by fataku
		// for kf2k1pla
		case 1: {
			for (int i = 0; i < nNeoTextROMSize; i++) {
				(NeoTextROM + 0x20000)[i] = BITSWAP08((NeoTextROM + 0x20000)[i], 3, 2, 4, 5, 1, 6, 0, 7);
			}
		  break;
		}
		// Original code from mame traduced by FerchogtX
		// for ms5boot, svcboot, svcplusa, more
		case 2: {
			memcpy(tmp + 0x000000, NeoTextROM + 0x020000 + 0x010000, 0x010000);
			memcpy(tmp + 0x010000, NeoTextROM + 0x020000 + 0x000000, 0x010000);
			memcpy(NeoTextROM + 0x20000, tmp, nNeoTextROMSize);
			break;
		}
		// Thanks also to HappyASR for the info
		// for ms5plus, svcplus, kf2k3bl, more
		case 3: {
			for (int i = 0; i < nNeoTextROMSize; i+= 0x10) {
				memcpy (tmp + i + 0, NeoTextROM + 0x020000 + i + 8, 8);
				memcpy (tmp + i + 8, NeoTextROM + 0x020000 + i + 0, 8);
			}
			memcpy (NeoTextROM + 0x020000, tmp, nNeoTextROMSize);
			break;
		}
		// Original code from MAME -- http://www.mame.net
		// for cthd2003
		case 4: {
			memcpy(tmp + 0 * 0x8000, NeoTextROM + 0x020000 + 0 * 0x8000, 0x8000);
			memcpy(tmp + 1 * 0x8000, NeoTextROM + 0x020000 + 2 * 0x8000, 0x8000);
			memcpy(tmp + 2 * 0x8000, NeoTextROM + 0x020000 + 1 * 0x8000, 0x8000);
			memcpy(tmp + 3 * 0x8000, NeoTextROM + 0x020000 + 3 * 0x8000, 0x8000);
			memcpy(NeoTextROM + 0x020000, tmp, nNeoTextROMSize);
			break;
		}
		// Original code by HalRIN
		// for ct2003sp
		case 5: {
			for (int i = 0; i < nNeoTextROMSize; i++) {
				int j = BITSWAP24(i, 23, 22, 21, 20, 19, 18, 17, 3, 0, 1, 4, 2, 13, 14, 16, 15, 5, 6, 11, 10, 9, 8, 7, 12);
				int k = ((i &~ 0x18000) | ((i >> 1) & 0x8000) | ((i & 0x8000) << 1));
				tmp[k] = (NeoTextROM + 0x020000)[j];
			}
			memcpy (NeoTextROM + 0x020000, tmp, nNeoTextROMSize);
			break;
		}
		// Converted by Jimmy_Page (www.neofighters.com)
		// for svcsplus, kof10thu, kf2k2spr, more
		case 6: {
			for (int i = 0; i < nNeoTextROMSize; i++) {
				(NeoTextROM + 0x20000)[i] = BITSWAP08((NeoTextROM + 0x20000)[i], 7, 6, 0, 4, 3, 2, 1, 5);
			}
			break;
		}
		// Thanks to IQ_132 -- http://neoource.1emulation.com/
		// for kof2k2bl
		case 8: {
			kof2k2bl_gfx_decrypt(NeoTextROM + 0x20000, 0x20000);
			break;
		}
		// for kf2k5uni
		case 9: {
			for (int i = 0; i < nNeoTextROMSize; i++) {
				NeoTextROM[0x20000 + i] = BITSWAP08(NeoTextROM[0x20000 + i], 4, 5, 6, 7, 0, 1, 2, 3);
			}
			break;
		}
	}
	free(tmp);
}

// ---------------------------------------------------------------------------------------
// Neo-Geo Bootleg z80 Decryption
// Thanks to IQ_132 and fataku for the info and drivers
static void neo_boot_z80_decrypt(int nGame)
{
	extern unsigned char* NeoZ80ROM;
	unsigned char* tmp = (unsigned char*)malloc(0x020000);

	BurnUpdateProgress(0.0, _T("Decrypting bootleg z80 data..."), 0);
	switch (nGame) {
		// cthd2003
		case 0: {
			memcpy(tmp + 0 * 0x8000, NeoZ80ROM + 0 * 0x8000, 0x8000);
			memcpy(tmp + 1 * 0x8000, NeoZ80ROM + 2 * 0x8000, 0x8000);
			memcpy(tmp + 2 * 0x8000, NeoZ80ROM + 1 * 0x8000, 0x8000);
			memcpy(tmp + 3 * 0x8000, NeoZ80ROM + 3 * 0x8000, 0x8000);
			memcpy(NeoZ80ROM, tmp, 0x20000);
			break;
		}
		// svcboot
		case 1: {
			memcpy(tmp + 0x00000, NeoZ80ROM + 0x10000, 0x10000);
			memcpy(tmp + 0x10000, NeoZ80ROM + 0x00000, 0x10000);
			memcpy(NeoZ80ROM, tmp, 0x20000);
			break;
		}
		// matrimbl
		case 2: {
			if (tmp){
				memcpy(tmp, NeoZ80ROM, 0x20000);
				for(int i = 0; i < 0x20000; i++) {
					int j = i;
					if (i & 0x00001) j ^= 0x00800;
					if (i & 0x00002) j ^= 0x02000;
					if (i & 0x00800) j ^= 0x10800;
					if (i & 0x10000) j ^= 0x00800;
					NeoZ80ROM[j] = tmp[i];
				}
			}
			break;
		}
		// kf10thua
		case 3: {
			for (int i = 0; i < 0x20000; i++) {
				NeoZ80ROM[i] = BITSWAP08(NeoZ80ROM[i], 4, 5, 6, 7, 0, 1, 2, 3);
			}
			break;
		}
	}
	free(tmp);
}

// ---------------------------------------------------------------------------------------
// Neo-Geo Bootleg Sound Emulation
// Thanks to IQ_132 and fataku for the info and drivers
void neo_boot_sound_decrypt(int nGame)
{
	BurnUpdateProgress(0.0, _T("Decrypting bootleg sound..."), 0);
	switch (nGame) {
		// Matrimelee (bootleg)
		case 1: {
			// Only V2 and V4 are byteswapped
			BurnByteswap(YM2610ADPCMAROM + 0x400000, 0x400000); // V2
			BurnByteswap(YM2610ADPCMAROM + 0xc00000, 0x400000); // V4
			break;
		}
		// SNK vs. CAPCOM (bootleg) and similar sets
		case 2: {
			// Byteswaps the whole sound ROMs
			BurnByteswap(YM2610ADPCMAROM, 0x1000000);
			break;
		}
		// Samurai Shodown 5 (bootleg)
		// Lansquenet 2004
		case 3: {
			// Variable byteswap
			for(int i = 0; i < nYM2610ADPCMASize; i++) {
				YM2610ADPCMAROM[i] = BITSWAP08(YM2610ADPCMAROM[i], 0, 1, 5, 4, 3, 2, 6, 7);
			}
			break;
		}
	}
}



// =======================================================================================
// Per game protections and handlers
// =======================================================================================

// -----------------------------------------------------------
// The King of Fighters '96 Plus

/* -----------------------------------------------------------

  This game is a very small modification of an actual kof96
  board. The boolegger simply put another chip in the board
  and mapped the first 0x80000 of the game to it. Also, they
  hooked the original chip and this together using a small
  piece of hardware. This was somewhat of a protection method.
  The game gets 1 bit (bit 3) out of every byte from the
  original p1 chip.

----------------------------------------------------------- */

// Code by Robbert
void kof96plsDecrypt()
{
	for (int i = 0; i < 0x80000; i++) {
		if ((Neo68KROM[0x300000 + i]^0x08) == Neo68KROM[i]) {
			Neo68KROM[0x300000 + i] ^= 0x08;
		}
	}
	memcpy(Neo68KROM, Neo68KROM + 0x300000, 0x80000);
}

// -----------------------------------------------------------
// King of Gladiator
// IQ_132 - http://neosource.1emulation.com/
// Thanks to Razoola for the info
void kogDecrypt()
{
	// Decrypt Sprite data
	neo_boot_gfx_decrypt(0x2800000);

	unsigned char *pTemp = (unsigned char*)malloc(0x600000);
	unsigned int nBank[] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };

	if (pTemp) {
		for (int i = 0; i < 8; i++)
			memcpy (pTemp + i * 0x20000, Neo68KROM + nBank[i] * 0x20000, 0x20000);

		memcpy (pTemp + 0x0007A6, Neo68KROM + 0x0407A6, 0x000006);
		memcpy (pTemp + 0x0007C6, Neo68KROM + 0x0407C6, 0x000006);
		memcpy (pTemp + 0x0007E6, Neo68KROM + 0x0407E6, 0x000006);
		memcpy (pTemp + 0x090000, Neo68KROM + 0x040000, 0x004000);
		memcpy (pTemp + 0x100000, Neo68KROM + 0x200000, 0x400000);
		memcpy (Neo68KROM, pTemp, 0x600000);
		free (pTemp);
	}

	for (int i = 0x90000; i < 0x94000; i++) {
		if (((*((unsigned short*)(Neo68KROM + i))&0xFFBF) == 0x4EB9 || *((unsigned short*)(Neo68KROM + i)) == 0x43F9) && !*((unsigned short*)(Neo68KROM + i + 2)))
			*((unsigned short*)(Neo68KROM + i + 2)) = 0x0009;

		if (*((unsigned short*)(Neo68KROM + i)) == 0x4EB8)
			*((unsigned short*)(Neo68KROM + i)) = 0x6100;
	}

	*((unsigned short*)(Neo68KROM + 0x007A8)) = 0x0009;
	*((unsigned short*)(Neo68KROM + 0x007C8)) = 0x0009;
	*((unsigned short*)(Neo68KROM + 0x007E8)) = 0x0009;
	*((unsigned short*)(Neo68KROM + 0x93408)) = 0xF168;
	*((unsigned short*)(Neo68KROM + 0x9340C)) = 0xFB7A;
	*((unsigned short*)(Neo68KROM + 0x924AC)) = 0x0009;
	*((unsigned short*)(Neo68KROM + 0x9251C)) = 0x0009;
	*((unsigned short*)(Neo68KROM + 0x93966)) = 0xFFDA;
	*((unsigned short*)(Neo68KROM + 0x93974)) = 0xFFCC;
	*((unsigned short*)(Neo68KROM + 0x93982)) = 0xFFBE;
	*((unsigned short*)(Neo68KROM + 0x93990)) = 0xFFB0;
	*((unsigned short*)(Neo68KROM + 0x9399E)) = 0xFFA2;
	*((unsigned short*)(Neo68KROM + 0x939AC)) = 0xFF94;
	*((unsigned short*)(Neo68KROM + 0x939BA)) = 0xFF86;
	*((unsigned short*)(Neo68KROM + 0x939C8)) = 0xFF78;
	*((unsigned short*)(Neo68KROM + 0x939D4)) = 0xFA5C;
	*((unsigned short*)(Neo68KROM + 0x939E0)) = 0xFA50;
	*((unsigned short*)(Neo68KROM + 0x939EC)) = 0xFA44;
	*((unsigned short*)(Neo68KROM + 0x939F8)) = 0xFA38;
	*((unsigned short*)(Neo68KROM + 0x93A04)) = 0xFA2C;
	*((unsigned short*)(Neo68KROM + 0x93A10)) = 0xFA20;
	*((unsigned short*)(Neo68KROM + 0x93A1C)) = 0xFA14;
	*((unsigned short*)(Neo68KROM + 0x93A28)) = 0xFA08;
	*((unsigned short*)(Neo68KROM + 0x93A34)) = 0xF9FC;
	*((unsigned short*)(Neo68KROM + 0x93A40)) = 0xF9F0;
	*((unsigned short*)(Neo68KROM + 0x93A4C)) = 0xFD14;
	*((unsigned short*)(Neo68KROM + 0x93A58)) = 0xFD08;
	*((unsigned short*)(Neo68KROM + 0x93A66)) = 0xF9CA;
	*((unsigned short*)(Neo68KROM + 0x93A72)) = 0xF9BE;
}

// Thanks to Razoola for the info!
unsigned char __fastcall kog_enable_title(unsigned int sekAddress)
{
	extern unsigned char *Neo68KRAM; // Main 68K RAM
	if (sekAddress == 0xFFFFF) return (Neo68KRAM[0x0FD82]+1)>>1;
	return 0xFF;
}

void kogProtectionInstall()
{
	SekMapHandler(5, 0x0FFFFE, 0x0FFFFF, SM_READ);
	SekSetReadByteHandler(5,    kog_enable_title);
}

// -----------------------------------------------------------
// Lansquenet 2004

/* -----------------------------------------------------------

  Lansquenet (derived from the German landsknecht ('servant of
  the land or country'), applied to a mercenary soldier) is a
  card game.

  Lansquenet 2004 is a bootleg/hack of Shock Troopers - 2nd
  squad.
  This seems to come from the same bootlegger as kog and
  samsho5b.  The similarities are in the protections of the P,
  Cx, S, and V roms.

  The p1 of this game, as well as that of kog and kf10thep are
  scrambled in the exact same order, the p1 is double the normal
  size, and the junk data is random bytes.  There is extra 68k
  data hidden in the junk bits, and needs to be copied out and
  patched into place in order for the games to work 100%
  correctly.

  { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD }; // P1 Order

  The s1 is scrambled per tile, which is 8 bytes, and easy to
  figure out.

  The Cx are scrambled in a similar way, each 128 byte tile
  is swapped 1>2, 2<1, etc.  This again is quite easy.

  Lastly, the Vx roms are encrypted using a bitswap.  This is
  the same bitswap that samsho5b uses for its Vx roms.

  BITSWAP08(src[i], 0, 1, 5, 4, 3, 2, 6, 7) // Vx bitswap

----------------------------------------------------------- */

void lans2004Decrypt()
{
	// Decrypt Sprite data
	neo_boot_gfx_decrypt(0x3000000);

	unsigned char *pTemp = (unsigned char*)malloc(0x600000);

	if (pTemp) {
		int sec[8] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };

		for (int i = 0; i < 8; i++)
			memcpy (pTemp + i * 0x20000, Neo68KROM + sec[i] * 0x20000, 0x20000);

		memcpy (pTemp + 0x0BBB00, Neo68KROM + 0x045B00, 0x001710);
		memcpy (pTemp + 0x02FFF0, Neo68KROM + 0x1A92BE, 0x000010);
		memcpy (pTemp + 0x100000, Neo68KROM + 0x200000, 0x400000);
		memcpy (Neo68KROM, pTemp, 0x600000);
		free(pTemp);
	}

	for (int i = 0xBBB00/2; i < 0xBE000/2; i++) {
		if ((((((unsigned short*)Neo68KROM)[i] & 0xFFBF) == 0x4EB9) || ((((unsigned short*)Neo68KROM)[i] & 0xFFBF) == 0x43B9)) &&	(((unsigned short*)Neo68KROM)[i + 1] == 0x0000)) {
			((unsigned short*)Neo68KROM)[i + 1] = 0x000B;
			((unsigned short*)Neo68KROM)[i + 2] += 0x6000;
		}
	}

	for (int i = 0; i < 0x100000/2; i++) {
		if ((((unsigned short*)Neo68KROM)[i] == 0xBE79) && (((unsigned short*)Neo68KROM)[i + 1] == 0x0010)) {
			((unsigned short*)Neo68KROM)[i + 3] = 0x6002;
		}
	}

	((unsigned short*)Neo68KROM)[0x2D15C/2] = 0x000B;
	((unsigned short*)Neo68KROM)[0x2D15E/2] = 0xBB00;
}

// -----------------------------------------------------------
// Crouching Tiger Hidden Dragon 2003 (set 1)

/* -----------------------------------------------------------

  Crouching Tiger Hidden Dragon 2003 is a fairly well-done
  hack.  It offers different backgrounds, edited characters,
  and quite a variety of protections.  King of Fighters 2001,
  the parent rom of cthd2003 had no bankswitch protections and
  just used the	standard CMC50 Cx encryptions.  CTHD2003 uses
  very scrambled Cx roms, P roms with a bankswitch and 
  on-the-fly patching, and S1 and M1 roms with Swapped chunks.

  The most interesting part of this game is probably the
  scrambled Cx roms.  They are scrambled in 128 byte (1 tile)
  pieces and the pattern repeats every 2KB. The last 4 bits of
  the tile address is scrambled seemingly according to a 16
  digit table.

  Crouching Tiger Hidden Dragon 2003 Super Plus is just a
  minor hack of cthd2003. It uses a 256kb S1 rom (which is
  unusual for a bootleg). And the s1 is protected with a
  24bit bitswap. Again unusual for an S rom.
  Other than that, there is very little different about this
  game worth mentioning.

----------------------------------------------------------- */

void cthd2003Bankswitch(unsigned int nBank)
{
	static unsigned int cthd2003_banks[8] =	{
		0x200000, 0x100000, 0x200000, 0x100000, 0x200000, 0x100000, 0x400000, 0x300000,
	};

	nBank = cthd2003_banks[nBank & 7];

	if (nBank != nNeo68KROMBank) {
		nNeo68KROMBank = nBank;
		SekMapMemory(Neo68KROM + nNeo68KROMBank, 0x200000, 0x2FFFFF, SM_ROM);
	}
}

void __fastcall cthd2003WriteByteBankswitch(unsigned int sekAddress, unsigned char byteValue)
{
	if (sekAddress == 0x2FFFF0) {
		cthd2003Bankswitch(byteValue);
	}
}

void __fastcall cthd2003WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2FFFF0) {
		cthd2003Bankswitch(wordValue);
	}
}

static void cthd2003_patches()
{
	// Patches, thanks to Razoola
	// fix garbage on s1 layer over everything
	((unsigned short*)Neo68KROM)[0xF415A / 2] = 0x4EF9;
	((unsigned short*)Neo68KROM)[0xF415C / 2] = 0x000F;
	((unsigned short*)Neo68KROM)[0xF415E / 2] = 0x4CF2;

	// Fix corruption in attract mode before title screen
	for (int i = 0x1AE290 / 2; i < 0x1AE8D0/2; i++) {
		((unsigned short*)Neo68KROM)[i] = 0x0000;
	}

	// Fix for title page
	for (int i = 0x1F8EF0 / 2; i < 0x1FA1F0 / 2; i = i + 2) {
		((unsigned short*)Neo68KROM)[i + 0] -= 0x7000;
		((unsigned short*)Neo68KROM)[i + 1] -= 0x0010;
	}

	// Fix for green dots on title page
	for (int i = 0xAC500 / 2; i < 0xAC520 / 2; i++)	{
		((unsigned short*)Neo68KROM)[i] = 0xFFFF;
	}

	// Fix for blanks as screen change level end clear
	((unsigned short*)Neo68KROM)[0x991D0 / 2] = 0xDD03;
	((unsigned short*)Neo68KROM)[0x99306 / 2] = 0xDD03;
	((unsigned short*)Neo68KROM)[0x99354 / 2] = 0xDD03;
	((unsigned short*)Neo68KROM)[0x9943E / 2] = 0xDD03;

	// Fix for AES mode (stop loop that triggers Watchdog)
	((unsigned short*)Neo68KROM)[0xA2B7E / 2] = 0x4E71;
}

void cthd2003Decrypt()
{
	neo_boot_z80_decrypt(0);
	cthd2003_patches();
	DoPerm(0);
}

// Install bankswitch handler
void cthd2003ProtectionInstall()
{
	SekOpen(0);

	SekMapHandler(4,	0x200000, 0x2FFFFF, SM_WRITE);
	SekSetWriteWordHandler(4, cthd2003WriteWordBankswitch);
	SekSetWriteByteHandler(4, cthd2003WriteByteBankswitch);
	cthd2003Bankswitch(0);

	SekClose();
}

void cthd2003MapBank()
{
	SekMapMemory(Neo68KROM + nNeo68KROMBank, 0x200000, 0x2FFFFF, SM_ROM);
}

// -----------------------------------------------------------
// Crouching Tiger Hidden Dragon 2003 (set 2)

/* -----------------------------------------------------------

  The only difference between the set 1 and this one should
  be that this seems to be the "final" revision of the hack,
  this means that it doesn't need patches for all corrupted
  stuff seen on cthd2003, and the game name in BIOS settings
  is correct labeled (C.T.H.D. 2003 instead of C.T.H.D. 2002)
  Maybe cthd2003 is a bootleg prototype?

----------------------------------------------------------- */

void cthd2k3aDecrypt()
{
	neo_boot_z80_decrypt(0);
	DoPerm(0);
}

// -----------------------------------------------------------
// The King of Fighters 2002 (bootleg)
void kof2k2blDecrypt()
{
	kof2002Decrypt();	// Program is scrambled same as original code...
	kof2k2bl_gfx_decrypt(NeoSpriteROM, 0x4000000);	// Sprite and Text are scrambled/encrypted in the same way every 64kb
}

// -----------------------------------------------------------
// The King of Fighters 2002 Plus (set 1)
// Is confirmed that this game and ms4plus use an encrypted 68K ROM
// Thanks to IQ_132 -- http://neosource.1emulation.com/
// Thanks to robber804 -- http://??
void PLUSDecryptP()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x100000);

	if (pTemp) {
		unsigned int nBank[16] = { 0x08, 0x06, 0x04, 0x0c, 0x0a, 0x01, 0x0e, 0x02, 0x0d, 0x05, 0x09, 0x0f, 0x0b, 0x03, 0x07, 0x00 };

		memcpy(pTemp, Neo68KROM, 0x100000);
		for (int i = 0; i < 16; i++) {
 			memcpy(Neo68KROM + i * 0x10000, pTemp + nBank[i] * 0x10000, 0x10000);
		}

	free(pTemp);
	}
}

void kf2k2plsDecrypt()
{
	kof2k2blDecrypt(); // GFX and P2 ROM are encrypted the same way as kof2k2bl
	PLUSDecryptP(); // Extra encryption for P1
}

// -----------------------------------------------------------
// The King of Fighters 2002 Magic Plus
void kf2k2mpDecrypt()
{
	kof2k2bl_gfx_decrypt(NeoSpriteROM,0x4000000);

	unsigned char *pTemp = (unsigned char*)malloc(0x80);

	memcpy(Neo68KROM, Neo68KROM + 0x300000, 0x500000);

	if (pTemp) {
		for (int i = 0; i < 0x800000; i+=0x80) {
			for (int j = 0; j < 0x80 / 2; j++) {
				int ofst = BITSWAP08( j, 6, 7, 2, 3, 4, 5, 0, 1 );
				memcpy(pTemp + j * 2, Neo68KROM + i + ofst * 2, 2);
			}
			memcpy(Neo68KROM + i, pTemp, 0x80);
		}
	}
	free(pTemp);
}

// -----------------------------------------------------------
// The King of Fighters 2002 Magic Plus II
void kf2k2mp2Decrypt()
{
	kof2k2bl_gfx_decrypt(NeoSpriteROM,0x4000000);

	memcpy(Neo68KROM + 0x000000, Neo68KROM + 0x1C0000, 0x040000);
	memcpy(Neo68KROM + 0x040000, Neo68KROM + 0x140000, 0x080000);
	memcpy(Neo68KROM + 0x0C0000, Neo68KROM + 0x100000, 0x040000);
	memcpy(Neo68KROM + 0x100000, Neo68KROM + 0x200000, 0x400000);
}

// -----------------------------------------------------------
// The King of Fighters Special Edition 2004

/* -----------------------------------------------------------

  There's not much special about this game other than that the 
  chunks of the P rom are mapped backwards.  the last 1mb
  should be the first and the first should be the last ;)

----------------------------------------------------------- */

void kf2k4speDecrypt()
{
	// Original code by IQ_132 (http://neosource.1emulation.com/)
	unsigned char* pTemp = (unsigned char*)malloc(0x500000);
	if (pTemp) {
		memcpy(pTemp, Neo68KROM, 0x500000);

		for (int i = 0; i < 5; i++) {
			memcpy(Neo68KROM + i * 0x100000, pTemp + 0x400000 - i * 0x100000, 0x100000);
		}
		free(pTemp);
	}
}

// -----------------------------------------------------------
// The King of Fighters Special Edition 2004 Plus
void kf2k4splDecrypt()
{
	// Thanks to KanyEr0 for the info, init by IQ_132
	// P1-ROM is scrambled in 128 chunks, so we load them
	// in the correct places, the second MB isn't loaded
	// because has only repeated data
	unsigned char *pTemp = (unsigned char*)malloc(0x600000);
	if (pTemp) {
		int nBank[8] = {0xD, 0x4, 0xA, 0x0, 0xC, 0x5, 0x8, 0x2};

		for (int i = 0; i < 8; i++) {
			memcpy (pTemp + 0x400000 + i * 0x20000, Neo68KROM + nBank[i] * 0x20000, 0x20000);
		}

		memcpy (pTemp, Neo68KROM + 0x200000, 0x400000);
		memcpy (Neo68KROM, pTemp, 0x600000);
	}
	free(pTemp);

	kf2k4speDecrypt();
}

// -----------------------------------------------------------
// The King of Fighters 10th Anniversary

/*------------------------------------------------------------

  The King of Fighters 10th Anniversary is probably the most
  interesting bootleg of a NEO-GEO game. It has tons of extra
  characters, new backgrounds, changed moves for clone
  characters, and an entirely new character select screen.

  The more interesting part of the game are the protections.
  The program rom has a bitswap on the addressing, so it is
  quite scrambled and has an Altera chip that puts patches on
  the program. Also, it has two new ram banks that hold code
  and text data, which is written on-the-fly. Also, the last
  and most interesting thing is that it has a bankswitch on
  the first rom bank. Switching this bank allows the clone
  characters to have extra moves.

----------------------------------------------------------- */

// Thanks to BDiamond for the whole driver
// Thanks to IQ_132 for helping me with this also

// RAM modules
static unsigned char *kof10thExtraRAMA = NULL; // Text RAM
static unsigned char *kof10thExtraRAMB = NULL; // 68K RAM

// 68K Bankswitch
void kof10thBankswitch(unsigned int nBank)
{
	nBank = 0x100000 + ((nBank & 7) << 20);
	if (nBank >= 0x700000) {
		nBank = 0x100000;
	}

	if (nBank != nNeo68KROMBank) {
		nNeo68KROMBank = nBank;
		SekMapMemory(Neo68KROM + nNeo68KROMBank, 0x200000, 0x2FDFFF, SM_ROM);
	}
}

// Text data extraction, game does this on the fly!
void __fastcall kof10thWriteWordCustom(unsigned int sekAddress, unsigned short wordValue)
{
	if (kof10thExtraRAMB[0x1FFC]) {
		NeoUpdateTextOne(0x20000 + ((sekAddress >> 1) & 0x1FFFF), BITSWAP08(wordValue, 7, 6, 0, 4, 3, 2, 1, 5));
	} else {
		*(unsigned short*)(kof10thExtraRAMA + (sekAddress & 0x01FFFF)) = wordValue;
	}
}

// 68K Bankswitch and RAM Handlers
void __fastcall kof10thWriteByteBankswitch(unsigned int sekAddress, unsigned char byteValue)
{
	if (sekAddress >= 0x2FE000) {
		sekAddress ^= 1;
		if (sekAddress == 0x2FFFF0)
			kof10thBankswitch(byteValue);
		else if (sekAddress == 0x2FFFF8 && kof10thExtraRAMB[sekAddress & 0x1FFE] != byteValue) {
			SekMapMemory(Neo68KROM + ((byteValue & 1) ? 0x700400 : 0x000400) , 0x000400, 0x0DFFFF, SM_ROM);
		}
		kof10thExtraRAMB[sekAddress & 0x1FFF] = byteValue;
	}
}

void __fastcall kof10thWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress >= 0x2FE000) {
		if (sekAddress == 0x2FFFF0)
			kof10thBankswitch(wordValue);
		else if (sekAddress == 0x2FFFF8 && *(unsigned short*)(kof10thExtraRAMB + (sekAddress & 0x1FFE)) != wordValue) {
			SekMapMemory(Neo68KROM + ((wordValue & 1) ? 0x700400 : 0x000400) , 0x000400, 0x0DFFFF, SM_ROM);
		}
		*(unsigned short*)(kof10thExtraRAMB + (sekAddress & 0x01FFE)) = wordValue;
	}
}

// Normal Decryption
void kof10thDecrypt()
{
	unsigned char* pTemp = (unsigned char*)malloc(0x800000);

	if (pTemp) {
		memcpy(pTemp, Neo68KROM, 0x800000);
		memcpy(Neo68KROM + 0x000000, pTemp + 0x700000, 0x100000); // correct in Uni-Bios
		memcpy(Neo68KROM + 0x100000, pTemp + 0x000000, 0x600000);

		memcpy(pTemp, Neo68KROM, 0x800000);
		for (int i = 0; i < 0x800000; i++) {
			int j = BITSWAP24(i, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 2, 9, 8, 7, 1, 5, 4, 3, 10, 6, 0);
			Neo68KROM[j] = pTemp[i];
		}
		free(pTemp);
	}

	// Run code that gives XOR for RAM moves and forces SoftDIPs
	*((unsigned short*)(Neo68KROM + 0x000124)) = 0x000D;
	*((unsigned short*)(Neo68KROM + 0x000126)) = 0xF7A8;

	// Run code to change 8x8 tiles (needed for neogeo logo tiles)
	*((unsigned short*)(Neo68KROM + 0x008BF4)) = 0x4EF9;
	*((unsigned short*)(Neo68KROM + 0x008BF6)) = 0x000D;
	*((unsigned short*)(Neo68KROM + 0x008BF8)) = 0xF980;
}

// Install Protection
void kof10thProtectionInstall()
{
	// set RAM modules
	kof10thExtraRAMA = Neo68KROM + 0x7E0000;
	kof10thExtraRAMB = Neo68KROM + 0x1FE000;
	memset(kof10thExtraRAMA, 0, 0x20000);
	memset(kof10thExtraRAMB, 0, 0x2000);

	SekOpen(0);

	// Install RAM handlers
	SekMapMemory(kof10thExtraRAMA, 0x0E0000, 0x0FFFFF, SM_ROM); // Text RAM on range 0x0e0000 - 0x0fffff
	SekMapMemory(kof10thExtraRAMB, 0x2FE000, 0x2FFFFF, SM_ROM); // Extra 68K RAM

	// Install bankswitch and text handlers
	SekMapHandler(4,	0x240000, 0x2FFFFF, SM_WRITE);
	SekSetWriteWordHandler(4, kof10thWriteWordBankswitch);
	SekSetWriteByteHandler(4, kof10thWriteByteBankswitch);

	SekMapHandler(5,	0x200000, 0x23FFFF, SM_WRITE);
	SekSetWriteWordHandler(5, kof10thWriteWordCustom);

	// Set bank
	nNeo68KROMBank = 1;
	kof10thBankswitch(0);

	SekClose();
}

// For savestates
int kof10thScan(int nAction, int* /*pnMin*/)
{
	struct BurnArea ba;

	if (nAction & ACB_MEMORY_RAM) {
		ba.Data		= kof10thExtraRAMA;
		ba.nLen		= 0x00020000;
		ba.nAddress	= 0;
		ba.szName	= "Extra RAM A";
		BurnAcb(&ba);

		ba.Data		= kof10thExtraRAMB;
		ba.nLen		= 0x00002000;
		ba.nAddress	= 0;
		ba.szName	= "Extra RAM B";
		BurnAcb(&ba);

		ba.Data		= NeoTextROM + 0x00020000;
		ba.nLen		= nNeoTextROMSize;
		ba.nAddress	= 0;
		ba.szName	= "8x8 Text Tile RAM";
		BurnAcb(&ba);
	}
	return 0;
}

// Blank 68K on the 0x200000 - 0x2fdfff range
void kof10thMapBank()
{
	SekMapMemory(Neo68KROM + nNeo68KROMBank, 0x200000, 0x2FDFFF, SM_ROM);
}

// -----------------------------------------------------------
// The King of Fighters 10th Anniversary Extra Plus

/* -----------------------------------------------------------

  King of Fighters 10th Anniversary Extra Plus introduced a
  new kind of protection for program roms. The p1 rom was twice
  the size it	needed to be, and contained about 1mb of junk,
  random data. Some	needed P data was hidden in the junk and
  had to be patched into place. This type of protection can
  also be seen in King of Gladiator and Lansquenet 2004

----------------------------------------------------------- */

// Code by IQ_132 -- http://neosource.1emulation.com/
// Thanks to JotaCE, Jimmy_page, and Robber804 for some info
void kf10thepDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x800000);

	unsigned int nBank[] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };

	for (int i = 0; i < 8; i++) {
		memcpy (pTemp + i * 0x20000, Neo68KROM + nBank[i] * 0x20000, 0x20000);
	}

	memcpy(pTemp + 0x0002e0, Neo68KROM + 0x0402e0, 0x06a);
	memcpy(pTemp + 0x0f92bc, Neo68KROM + 0x0492bc, 0xb9e);

	for (int i = 0xf92bc; i < 0xf9e58; i += 2) {
		if (*((unsigned short*)(pTemp + i + 0)) == 0x4eb9 || *((unsigned short*)(pTemp + i + 0)) == 0x4ef9) {
			if (*((unsigned short*)(pTemp + i + 2)) == 0x0000) {
				*((unsigned short*)(pTemp + i + 2)) = 0x000F;
			}
		}
	}
	pTemp[0x00342] = 0x0f;

	memcpy (pTemp + 0x100000, Neo68KROM + 0x200000, 0x600000);
	memcpy (Neo68KROM, pTemp, 0x800000);

	free(pTemp);
}

// -----------------------------------------------------------
// The King of Fighters 10th Anniversary 2005 Unique (set 1)
// Decryption for UNIQUE version
// Code by IQ_132 - http://neosource.1emulation.com
void kof10thuDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x80);
	if (pTemp) {
		for (int i = 0; i < 0x800000; i+=0x80) {
			for (int j = 0; j < 0x80; j+=2) {
				int ofst = BITSWAP08(j, 0, 3, 4, 5, 6, 1, 2, 7);
				memcpy(pTemp + j, Neo68KROM + i + ofst, 2);
			}
			memcpy(Neo68KROM + i, pTemp, 0x80);
		}
	}
	free(pTemp);

	memcpy(Neo68KROM, Neo68KROM + 0x600000, 0x100000);
}

// -----------------------------------------------------------
// The King of Fighters 10th Anniversary 2005 Unique (set 2)
void kf2k5uniDecrypt()
{
	kof10thuDecrypt(); // Same decryption as kof10thu
	neo_boot_z80_decrypt(3);
}

// -----------------------------------------------------------
// Matrimelee (bootleg)
void matrimblDecrypt()
{
	// Uses same descrambling as matrim
	kof2002Decrypt();
	neo_boot_z80_decrypt(2);
}

// -----------------------------------------------------------
// Metal Slug 5 (bootleg)
// Based on code provided by bms888 and Neoaethyr, ported by IQ_132
void __fastcall ms5bootWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2ffff2) {
		wordValue = (wordValue >> 12);

		if (wordValue == 2) wordValue = 3;
		else if (wordValue == 3) wordValue = 2;

		SekMapMemory(Neo68KROM + wordValue * 0x100000, 0x200000, 0x2fdfff, SM_ROM);
	}
}

// Install bankswitch handler
void ms5bootProtectionInstall()
{
	SekMapHandler(5,	0x2ffff0, 0x2fffff, SM_WRITE);
	SekSetWriteWordHandler(5, ms5bootWriteWordBankswitch);
}

// -----------------------------------------------------------
// Metal Slug 5 Plus

/* -----------------------------------------------------------

  Metal Slug 5 Plus is very simply protected.  The bankswitch
  for	game is relocated from 0x2FFFF2 to 0x2FFFF4. Also, the S
  rom	is very lightly scrambled, swapping every 8 bytes
  (1 tile).
  The game itself has a bug during AES mode; the flashing
  "PLUS" doesn't go away.

----------------------------------------------------------- */

// Thanks to bms888 for the handler
void __fastcall ms5plusWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	if (sekAddress == 0x2ffff4) {
		SekMapMemory(Neo68KROM + (wordValue << 0x10), 0x200000, 0x2fdfff, SM_ROM);
	};
}

// Install bankswitch handler
void ms5plusProtectionInstall()
{
	SekMapHandler(5,	0x2ffff0, 0x2fffff, SM_WRITE);
	SekSetWriteWordHandler(5, ms5plusWriteWordBankswitch);
}

// -----------------------------------------------------------
// Metal Slug 6 (bootleg)
// Does this is all protection used?
void ms6bootDecrypt()
{
	memcpy(Neo68KROM, Neo68KROM + 0x100000, 0x500000);
}


// -----------------------------------------------------------
// SNK vs CAPCOM (bootleg)

/*-------------------------------------------------------------

  This board is protected by 3 Actel A40MX04-F PL84 0323 FPGAs
  There are two on Board A (P & V) and 1 on Board B (C, S, M).
  Also, either the M or S (I'm not sure) has a small capacitor
  going from the VCC pin to the VPP pin.

  This game has the bankswitch of its parent in-tact, but the
  pallete write has been removed (code was hacked in the P for it),
  and the writes to the extra ram bank were moved to write in the
  normal 68K work ram at 0x100000-0x10FFFF.

  The data in the P roms is scrambled using a bitswap8 and a small
  scrambling on the banks.

  The Cx roms are scrambled in a very similar way to cthd2003 &
  matrimbl (every tile is moved).

  The Vx roms are protected in a somewhat humorous way, they labels
  on them were swapped, and the data was byteswapped.

------------------------------------------------------------- */

// FBA Conversion by JiMMy_PaGe (www.neofighters.com.br) original code by Halrin
void svcbootDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x800000);

	if (pTemp) {
		int nBank[] =  { 0x06, 0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00 };

		memcpy (pTemp, Neo68KROM, 0x800000);
		for(int i = 0; i < 0x800000 / 2; i++) {
			int j = (nBank[(i >> 19) & 7] << 19) | (i & 0x7ff00) | BITSWAP08((i & 0xff), 7, 6, 1, 0, 3, 2, 5, 4);
			memcpy(Neo68KROM + i * 2, pTemp + j * 2, 2);
		}
	
		free(pTemp);
	}

	neo_boot_z80_decrypt(1);
	DoPerm(1); // bitswap for C-ROMs
}

// -----------------------------------------------------------
// SNK vs CAPCOM Plus (set 1)
// Analyzed by HalRIN - http://www52.tok2.com/home/foge/
// FBA conversion by IQ_132 - http://neosource.1emulation.com/
void svcplusDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x600000);

	if (pTemp) {	
		memcpy(pTemp + 0x500000, Neo68KROM + 0x000000, 0x100000);
		memcpy(pTemp + 0x000000, Neo68KROM + 0x100000, 0x500000);

		for(int i = 0; i < 0x600000/2; i++) {
			int j = ((i & 1) << 18) | ((i & 2) << 16) | ((i & 4) << 14) | ((i >> 18) & 1) | ((i >> 16) & 2) | ((i >> 14) & 4);
			j ^= (i &~ 0x70007) | 0x70007;
			memcpy(Neo68KROM + i * 2, pTemp + j * 2, 2);
		}
	
		free(pTemp);
	}

	// Patched by Altera protection chip?
	*((unsigned short*)(Neo68KROM + 0xf8016)) = 0x33c1;

	neo_boot_z80_decrypt(1);
	DoPerm(1); // bitswap for C-ROMs
}

// -----------------------------------------------------------
// SNK vs CAPCOM Plus (set 2)
void svcplusaDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x600000);

	if (pTemp) {
		memcpy (pTemp, Neo68KROM + 0x100000, 0x500000);
		memcpy (pTemp + 0x500000, Neo68KROM, 0x100000);
		memcpy (Neo68KROM, pTemp, 0x600000);
		free(pTemp);
	}

	// Patched by Altera protection chip?
	*((unsigned short*)(Neo68KROM + 0xf8016)) = 0x33c1;

	neo_boot_z80_decrypt(1);
	DoPerm(1); // bitswap for C-ROMs
}

// -----------------------------------------------------------
// SNK vs CAPCOM Super Plus
// Analyzed by HalRIN - http://www52.tok2.com/home/foge/
// FBA conversion by IQ_132 - http://neosource.1emulation.com/
void svcsplusDecrypt()
{
	unsigned char *pTemp = (unsigned char*)malloc(0x800000);

	if (pTemp) {
		memcpy(pTemp + 0x000000, Neo68KROM + 0x000000, 0x800000);
		memcpy(pTemp + 0x000000, Neo68KROM + 0x600000, 0x200000);
		memcpy(pTemp + 0x200000, Neo68KROM + 0x100000, 0x500000);
		memcpy(pTemp + 0x700000, Neo68KROM + 0x000000, 0x100000);
	
		for(int i = 0; i < 0x800000 / 2; i++) {
			int j = (i & ~0x7fff) | BITSWAP16((i & 0x7fff), 15, 0, 8, 9, 11, 10, 12, 13, 4, 3, 1, 7, 6, 2, 5, 14);
	        	memcpy(Neo68KROM + i * 2, pTemp + j * 2, 2);
		}

		free(pTemp);
	}

	// Enable S. Plus
	*((unsigned short*)(Neo68KROM + 0x9E90)) = 0x000F;
	*((unsigned short*)(Neo68KROM + 0x9E92)) = 0xc9c0;

	// Enable boss icons
	*((unsigned short*)(Neo68KROM + 0xA10C)) = 0x4EB9;
	*((unsigned short*)(Neo68KROM + 0xA10E)) = 0x000E;
	*((unsigned short*)(Neo68KROM + 0xA110)) = 0x9750;

	neo_boot_z80_decrypt(1);
	DoPerm(1); // bitswap for C-ROMs
}

// -----------------------------------------------------------
// Samurai Shodown V (bootleg)
// FBA Conversion by JiMMy_PaGe (www.neofighters.com.br) original code by Halrin
// Small modification by IQ_132 -- http://neosource.1emulation.com/
void samsh5blDecrypt()
{
	// Decrypt Sprite data
	neo_boot_gfx_decrypt(0x4000000);

	unsigned char *pTemp = (unsigned char*)malloc(0x800000);

	if (pTemp) {
		memcpy(pTemp + 0x000000, Neo68KROM + 0x700000, 0x100000);
		memcpy(pTemp + 0x100000, Neo68KROM + 0x000000, 0x700000);
	
		for(int i = 0; i < 0x800000/2; i++) {
			int j = ((i & ~5) | ((i & 4) >> 2) | ((i & 1) << 2)) ^ 0x060005;
			memcpy(Neo68KROM + i * 2, pTemp + j * 2, 2);
		}

		free(pTemp);
	}
}

// -----------------------------------------------------------
// The King of Fighters 2003 (bootleg, set 1)
void kf2k3blDecrypt()
{
	// Thanks to IQ_132 -- http://neosource.1emulation.com/
	memcpy(Neo68KROM + 0x100000, Neo68KROM + 0x000000, 0x600000);
	memcpy(Neo68KROM + 0x000000, Neo68KROM + 0x700000, 0x100000);
}

// Speciall read handler for kof2003 (bootleg)
unsigned char __fastcall kf2k3blReadByteProtection(unsigned int /*sekAddress*/)
{
	return CartRAM[0xff9];
}

// Install bankswitch handler
void kf2k3blProtectionInstall()
{
	PVCProtectionInstall();

	SekMapHandler(6,    0x058196,    0x058197,  SM_READ);
	SekSetReadByteHandler(6,  kf2k3blReadByteProtection);
}

// -----------------------------------------------------------
// The King of Fighters 2003 (bootleg, set 2)

/*------------------------------------------------------------

  This KOF2003 bootleg has a few interesting features. One of
  them is that it uses a reduced version of the bankswitch.
  This version only requires a 4 byte (2 dword) buffer to store
  the bankswitch offset, and uses 3 bytes of the 4 that are
  written to choose which offset. The game also features a
  bitswap, but the bitswap is fairly easy in that bits 18-0 are
  backwards. Lastly, the game has an Altera (probably Max) chip
  that patches a single patch into the program data of the game.
  It seems to make no difference in gameplay, but I haven't
  thoroughly played the game to check if this is correct or not.

----------------------------------------------------------- */

void kf2k3blaDecrypt()
{
	unsigned short *tmp = (unsigned short*)malloc(0x100000);

	for (int i = 0; i < 0x700000 / 2; i += 0x100000 / 2) {
		memcpy(tmp, &((unsigned short*)Neo68KROM)[i], 0x100000);

		for (int j = 0; j < 0x100000/2; j++) {
			((unsigned short*)Neo68KROM)[i + j] = tmp[BITSWAP24(j, 23, 22, 21, 20, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18)];
		}
	}

	free(tmp);

	// patched by Altera protection chip on PCB
	((unsigned short*)Neo68KROM)[0xf38ac / 2] = 0x4e75;
}

// Second bankswitch for kof2003 bootleg (set 2)
// Heavily modified by IQ_132 - http://neosource.1emulation.com
void kf2k3blaBankswitch()
{
	int nBank = (CartRAM[1] << 8) | (CartRAM[0] & 0xff);
	SekMapMemory(Neo68KROM + nBank + 0x100000, 0x200000, 0x2fdfff, SM_ROM);
}

void __fastcall kf2k3blaWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue)
{
	CartRAM[(sekAddress - 0x2ffff0) / 2] = wordValue;
	if (sekAddress == 0x2ffff2) kf2k3blaBankswitch();
}

unsigned short __fastcall kf2k3blaReadWordBankswitch(unsigned int sekAddress)
{
	return CartRAM[(sekAddress - 0x2ffff0) / 2];
}

// Install BankSwitch handler
void kf2k3blaProtectionInstall()
{
	SekMapHandler(5,          0x2ffff0, 0x2fffff, SM_READ);
	SekSetReadWordHandler(5,   kf2k3blaReadWordBankswitch);

	SekMapHandler(5,         0x2ffff0, 0x2fffff, SM_WRITE);
	SekSetWriteWordHandler(5, kf2k3blaWriteWordBankswitch);
}

// -----------------------------------------------------------
// The King of Fighters 2004 EX Ultra Plus
// original code by bms1221
void kf2k4uplDecrypt()
{
	// Using same descrambling as kf2k3bl
	kf2k3blDecrypt();

	for(int i = 0; i < 0x2000; i++) {
		int j = (i & 0xff00) + BITSWAP08((i & 0x00ff), 7, 1, 5, 4, 3, 2, 6, 0); 
		Neo68KROM[0xfe000 + i] = Neo68KROM[0xd0610 + j];
	}
}

// -----------------------------------------------------------
// Final Romance 2 (CD Hack)
// Thanks to IQ_132 -- http://neosource.1emulation.com/
void fr2chCallback()
{
	// Patch out bios call.. 0xC0056A
	*((unsigned short*)(Neo68KROM + 0x1BF2)) = 0x4E71;
	*((unsigned short*)(Neo68KROM + 0x1BF4)) = 0x4E71;
	*((unsigned short*)(Neo68KROM + 0x1BF6)) = 0x4E71;
}
