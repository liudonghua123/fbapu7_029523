#include "neogeo.h"
// Neo Geo -- misc. support functions

unsigned char nNeoProtectionXor;

// This function loads the 68K ROMs
int NeoLoadCode(int nOffset, int nNum, unsigned char* pDest)
{
	struct BurnRomInfo ri;

	for (int i = 0; i < nNum; i++) {
		ri.nLen = 0;
		BurnDrvGetRomInfo(&ri, nOffset + i);

		if (BurnLoadRom(pDest, nOffset + i, 1)) {
			return 1;
		}

		if ((BurnDrvGetHardwareCode() & HARDWARE_SNK_SWAPP) && (i == 0)) {
			for (unsigned int j = 0; j < (ri.nLen / 2); j++) {
				int k = pDest[j];
				pDest[j] = pDest[j + (ri.nLen / 2)];
				pDest[j + (ri.nLen / 2)] = k;
			}
		}

		pDest += ri.nLen;
	}

	return 0;
}

// ----------------------------------------------------------------------------
// Needed for PVC Protected games
/* ----------------------------------------------------------------------------

  The P roms of mslug5(pcb & mvs), kof2003(pcb & mvs), and svc(mvs) are unusual
  in the fact that every other dWord (2 bytes) comes from the p1 or the p2.
  Normally, data is stored in a linear fashion in the roms.

---------------------------------------------------------------------------- */
void NeoInterleaveCode32WORDSWAP(unsigned char* pDest)
{
	// Interleave data in the 68K code

	unsigned char* pTemp = (unsigned char*)malloc(0x800000);

	for (int i = 0; i < 0x800000; i+=4) {
		memcpy(pTemp + i + 0, pDest + i / 2 + 0x000000, 2);
		memcpy(pTemp + i + 2, pDest + i / 2 + 0x400000, 2);
	}

	memcpy(pDest, pTemp, 0x800000);
	free(pTemp);
}

// This function loads and pre-processes the sprite data
int NeoLoadSprites(int nOffset, int nNum, unsigned char* pDest, unsigned int nSpriteSize)
{
	struct BurnRomInfo ri;
	ri.nType = 0;
	ri.nLen = 0;

	unsigned int nRomSize = 0;

	// Hack for svcpcb's non-standard 32mb Cx roms
	int svcpcb = 0;

	if ((BurnDrvGetHardwareCode() & (HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_ENCRYPTED_B)) && (nSpriteSize != 0x6000000)) {
		if (BurnDrvGetHardwareCode() & HARDWARE_SNK_ENCRYPTED_A) {
			NeoGfxDecryptCMC42Init();
		} else {
			if (BurnDrvGetHardwareCode() & HARDWARE_SNK_ENCRYPTED_B) {
				NeoGfxDecryptCMC50Init();
			}
		}

		unsigned char* pBuf = (unsigned char*)malloc(0x800000 * 2);
		if (pBuf == NULL) {
			return 1;
		}

		for (int i = 0; i < (nNum + svcpcb >> 1); i++) {
			int k = 4, n = i;
			// ms5pcb, svcpcba
			if ((nSpriteSize == 0x4000000) && (nNum == 4)) {
				pBuf = (unsigned char*)malloc(0x2000000);
				BurnLoadRom(pBuf + 0, nOffset + 0 + (i << 1), 2);
				BurnLoadRom(pBuf + 1, nOffset + 1 + (i << 1), 2);
				k = 8, n = i * 2;

				for (int j = 0; j < 0x2000000; j+=4) {
					BurnByteswap(pBuf + j + 1, 2);
				}

				ms5pcb_cx_decrypt(pBuf);
			// svcpcb
			} else if ((nSpriteSize == 0x4000000) && (nNum == 2)) {
				pBuf = (unsigned char*)malloc(0x2000000);
				BurnLoadRom(pBuf, nOffset + i, 1);
				k = 8, n = i * 2, svcpcb = 2;

				ms5pcb_cx_decrypt(pBuf);
			} else {
				BurnLoadRom(pBuf + 0, nOffset + (i << 1), 2);
				BurnLoadRom(pBuf + 1, nOffset + 1 + (i << 1), 2);
			}

			for (int j = 0; j < k; j++) {
				BurnUpdateProgress(1.0 / ((double)(nSpriteSize/0x800000) * 8.0 / 3.0), j ? NULL : _T("Decrypting graphics..."), 0);
				NeoGfxDecryptDoBlock(nNeoProtectionXor, pBuf + j * 0x400000, n * 0x800000 * 2 + j * 0x400000, 0x400000, nSpriteSize);
			}
		}

		free(pBuf);

	} else {
		nSpriteSize = 0;

		// Compute correct size to gaps into account (Kizuna)
		for (int i = 0; i < nNum - 2; i++) {
			BurnDrvGetRomInfo(&ri, nOffset + i);
			if (ri.nLen > nRomSize) {
				nRomSize = ri.nLen;
			}
		}

		for (int i = 0; i < (nNum >> 1); i++) {
			BurnLoadRom(pDest + nSpriteSize + 0, nOffset + (i << 1), 2);
			BurnLoadRom(pDest + nSpriteSize + 1, nOffset + 1 + (i << 1), 2);

			BurnDrvGetRomInfo(&ri, nOffset + (i << 1));

			if (i < (nNum >> 1) - 1) {
				nSpriteSize += nRomSize << 1;
			} else {
				nSpriteSize += ri.nLen << 1;
			}
		}
	}

	// Swap data for viewpoin, aof, ssideki, kotm2, more
	if (BurnDrvGetHardwareCode() & HARDWARE_SNK_SWAPC) {
		for (int i = 0; i < 0x200000; i++) {
			unsigned char n = pDest[i + 0x400000];
			pDest[i + 0x400000] = pDest[i + 0x200000];
			pDest[i + 0x200000] = n;
		}
	}

	if ((BurnDrvGetHardwareCode() & HARDWARE_SNK_ENCRYPTED_B) && (nSpriteSize == 0x6000000)) {
		BurnUpdateProgress(0, _T("Decrypting graphics..."), 0);
		kf2k3pcb_cx_decrypt(NeoSpriteROM);
		BurnUpdateProgress(1.0, NULL, 0);
	}

	return 0;
}

void NeoDecodeSprites(unsigned char* pDest, int nSize)
{
	for (int i = 0; i < 8; i++) {

		unsigned char* pStart = pDest + i * (nSize >> 3);
		unsigned char* pEnd = pStart + (nSize >> 3);

		{
			int nStep = 8;
			if (BurnDrvGetHardwareCode() & (HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_ENCRYPTED_B)) {
				nStep *= 4;
			}
			BurnUpdateProgress(1.0 / nStep, i ? NULL : _T("Preprocessing graphics..."), 0);
		}

		// Pre-process the sprite graphics
		for (unsigned char* pTile = pStart; pTile < pEnd; pTile += 128) {
			unsigned int data[32];

			for (int y = 0; y < 16; y++) {
				unsigned int n = 0;
				for (int x = 0; x < 8; x++) {
					unsigned int m = ((pTile[67 + (y << 2)] >> x) & 1) << 3;
					m |= ((pTile[65 + (y << 2)] >> x) & 1) << 2;
					m |= ((pTile[66 + (y << 2)] >> x) & 1) << 1;
					m |= ((pTile[64 + (y << 2)] >> x) & 1) << 0;

					n |= m << (x << 2);
				}
				data[(y << 1) + 0] = n;

				n = 0;
				for (int x = 0; x < 8; x++) {
					unsigned int m = ((pTile[3 + (y << 2)] >> x) & 1) << 3;
					m |= ((pTile[1 + (y << 2)] >> x) & 1) << 2;
					m |= ((pTile[2 + (y << 2)] >> x) & 1) << 1;
					m |= ((pTile[0 + (y << 2)] >> x) & 1) << 0;

					n |= m << (x << 2);
				}
				data[(y << 1) + 1] = n;
			}
			for (int n = 0; n < 32; n++) {
				((unsigned int*)pTile)[n] = data[n];
			}
		}
	}
}

void NeoDecodeText(unsigned char* pDest, int nSize)
{
	// Pre-process the text layer graphics
	for (unsigned char* pTile = pDest; pTile < (pDest + 0x20000 + nSize); pTile += 32) {
		unsigned char data[32];
		for (int n = 0; n < 8; n++) {
			data[0 + n * 4] = pTile[16 + n];
			data[1 + n * 4] = pTile[24 + n];
			data[2 + n * 4] = pTile[ 0 + n];
			data[3 + n * 4] = pTile[ 8 + n];
		}

		for (int n = 0; n < 32; n++) {
			pTile[n] = data[n] << 4;
			pTile[n] |= data[n] >> 4;
		}
	}
}

int NeoLoadADPCM(int nOffset, int nNum, unsigned char* pDest)
{
	struct BurnRomInfo ri;
	ri.nType = 0;
	ri.nLen = 0;

	BurnDrvGetRomInfo(&ri, nOffset);

	for (int i = 0; i < nNum; i++) {
		BurnLoadRom(pDest + ri.nLen * i, nOffset + i, 1);
	}

	return 0;
}

// This function fills the screen with the first palette entry
void NeoClearScreen()
{
	unsigned int nColour = NeoPalette[0x0FFF];

	if (nColour) {
		switch (nBurnBpp) {
			case 4: {
				unsigned int* pClear = (unsigned int*)pBurnDraw;
				for (int i = 0; i < nNeoScreenWidth * 224 / 8; i++) {
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
				}
				break;
			}

			case 3: {
				unsigned char* pClear = pBurnDraw;
				unsigned char r = nColour;
				unsigned char g = (r >> 8) & 0xFF;
				unsigned char b = (r >> 16) & 0xFF;
				r &= 0xFF;
				for (int i = 0; i < nNeoScreenWidth * 224; i++) {
					*pClear++ = r;
					*pClear++ = g;
					*pClear++ = b;
				}
				break;
			}

			case 2: {
				unsigned int* pClear = (unsigned int*)pBurnDraw;
				nColour |= nColour << 16;
				for (int i = 0; i < nNeoScreenWidth * 224 / 16; i++) {
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
					*pClear++ = nColour;
				}
				break;
			}
		}
	} else {
		memset(pBurnDraw, 0, nNeoScreenWidth * 224 * nBurnBpp);
	}
}
