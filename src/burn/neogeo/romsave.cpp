// FB Alpha Plus! Neo-Geo ROMs saving driver module
// Module version: v0.4a
// Whole driver module written by IQ_132 - http://neosource.1emulation.com/.
// ===============================================================
// Revision History:
// - Version 0.4a
//   Trimmed C-Saving routine and optimized it (Thanks to IQ_132).
// ---------------------------------------------------------------
// - Version 0.4
//   Renamed some kludges and added routines for some new games.
// ---------------------------------------------------------------
// - Version 0.3
//   Fixed svcchaos c1 and c2 code (again, thanks to Jimmy_Page)
//   Added a code to save a 16mb V1-ROM for kof2003 (thanks to Jimmy_page)
// ---------------------------------------------------------------
// - Version 0.2
//   Fixed C-Decryption for svcchaos.
//   Added the hability for naming the files from the cartridge ID.
//   Fixed interleaving for using less RAM.
//   Changed V-ROM saving routine.
// ---------------------------------------------------------------
// - Version 0.1
//   First version.
//   Added some tweaks for C-Decryption saving.
// ===============================================================

#include "neogeo.h"

// ----------------------

int bsavedecryptedcs = 0;
int bsavedecryptedps = 0;
int bsavedecrypteds1 = 0;
int bsavedecryptedvs = 0;
extern unsigned int nCodeSize;
extern unsigned int nSpriteSize;

// ----------------------

// 8 C-ROMs for standard ROMsets, number will vary
void savedecCROMs()
{
	TCHAR szNames[50];
	int size = nSpriteSize;
	int divby = 0x1000000;

	BurnUpdateProgress(0.0, _T("Initializing save routine..."), 0);
	if (NeoSpriteROM) {
		if (!(nSpriteSize & 0xFFFFFF)) {
			if (!strcmp(BurnDrvGetTextA(DRV_NAME), "svcpcb")) divby = 0x4000000;
			if (!strcmp(BurnDrvGetTextA(DRV_NAME), "kf2k3pcb")) divby = 0x2000000;

			for (int i = 0; i < (size / divby); i++) {
				_stprintf(szNames, _T("Saving decrypted C%d and C%d ROMs..."), ((i*2)+1), ((i*2)+2));
				BurnUpdateProgress(0.0, szNames, 0);
				_stprintf(szNames, _T("%X%2.2X-c%d_decrypted.bin"), Neo68KROM[0x109], Neo68KROM[0x108], ((i*2)+1));
				FILE* C1 = _tfopen(szNames, _T("wb"));
				_stprintf(szNames, _T("%X%2.2X-c%d_decrypted.bin"), Neo68KROM[0x109], Neo68KROM[0x108], ((i*2)+2));
				FILE* C2 = _tfopen(szNames, _T("wb"));
				for (int j = 0; j < divby; j+=2) {
					fwrite(NeoSpriteROM + i * divby + j + 0, 1, 1, C1);
					fwrite(NeoSpriteROM + i * divby + j + 1, 1, 1, C2);
				}
				fclose(C1);
				fclose(C2);
			}
			return;
		}
	}
}

// For compatibility issues, only 1 P-ROM will be saved
void savedecPROMs()
{
	char name[50];

	BurnUpdateProgress(0.0, _T("Saving decrypted P-ROM..."), 0);
	sprintf (name, "%X%2.2X-p1_decrypted.bin", Neo68KROM[0x109], Neo68KROM[0x108]);
	FILE* PROM = fopen(name, "wb");
	if (PROM) {
		fwrite(Neo68KROM, 1, nCodeSize, PROM);
		fclose(PROM);
	}
}

// Either extracted from C Data or descrambled text roms
void savedecSROM()
{
	char name[50];

	BurnUpdateProgress(0.0, _T("Saving decrypted S1-ROM..."), 0);
	sprintf (name, "%X%2.2X-s1_decrypted.bin", Neo68KROM[0x109], Neo68KROM[0x108]);
	FILE* fp = fopen(name, "wb");
	if (fp) {
		fwrite(NeoTextROM + 0x020000, 1, nNeoTextROMSize, fp);
		fclose(fp);
	}
}

// Standard decrypted samples are saved with this
void savedecVROMs(int nNumber)
{
	char name[50];

	// Special handler for unique V-ROM
	if (nNumber == 1) {
		sprintf (name, "%X%2.2X-v1_decrypted.bin", Neo68KROM[0x109], Neo68KROM[0x108]);
		BurnUpdateProgress(0.0, _T("Saving decrypted V1 ROM..."), 0);
		FILE* V1ROM = fopen(name, "wb");
		if (V1ROM) {
			fwrite(YM2610ADPCMAROM, 1, nYM2610ADPCMASize, V1ROM);
			fclose(V1ROM);
		}
	} else {
		BurnUpdateProgress(0.0, _T("Saving decrypted V1 and V2 ROMs..."), 0);
		sprintf (name, "%X%2.2X-v1_decrypted.bin", Neo68KROM[0x109], Neo68KROM[0x108]);
		FILE* V1ROM = fopen(name, "wb");
		if (V1ROM) {
			fwrite(YM2610ADPCMAROM, 1, 0x800000, V1ROM);
			fclose(V1ROM);
		}
		sprintf (name, "%X%2.2X-v2_decrypted.bin", Neo68KROM[0x109], Neo68KROM[0x108]);
		FILE* V2ROM = fopen(name, "wb");
		if (V2ROM) {
			fwrite(YM2610ADPCMAROM + 0x800000, 1, 0x800000, V2ROM);
			fclose(V2ROM);
		}
	}
}
