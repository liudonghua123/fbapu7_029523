#include "burnint.h"
#include "msm6295.h"
#include "burn_ym2151.h"

// Uncomment to have the driver perform the screen rotation (faster unless 3D hardware is used for blitting).
// #undef DRIVER_ROTATION
// #define DRIVER_ROTATION

const int TOA_68K_SPEED = 16000000;
const int TOA_Z80_SPEED = 4000000;
const int TOA_VBLANK_LINES = 22;

// toaplan.cpp
extern int nToaCyclesScanline;
extern int nToaCyclesDisplayStart;
extern int nToaCyclesVBlankStart;

int ToaLoadCode(unsigned char *Rom, int nStart, int nCount);
int ToaLoadGP9001Tiles(unsigned char* pDest, int nStart, int nNumFiles, int nROMSize, bool bSwap = false);

void ToaClearScreen();

void ToaZExit();

extern unsigned char* RomZ80;
extern unsigned char* RamZ80;

extern int nCyclesDone[2], nCyclesTotal[2];
extern int nCyclesSegment;

#ifdef DRIVER_ROTATION
 extern bool bToaRotateScreen;
 #define TOA_ROTATE_GRAPHICS_CCW 0
#else
 const bool bToaRotateScreen = false;
 #define TOA_ROTATE_GRAPHICS_CCW BDF_ORIENTATION_VERTICAL
#endif

extern unsigned char* pBurnBitmap;
extern int nBurnColumn;
extern int nBurnRow;

inline void ToaGetBitmap()
{
	if (bToaRotateScreen) {
		pBurnBitmap = pBurnDraw + 319 * nBurnPitch;
		nBurnColumn = -nBurnPitch;
		nBurnRow = nBurnBpp;
	} else {
		pBurnBitmap = pBurnDraw;
		nBurnColumn = nBurnBpp;
		nBurnRow = nBurnPitch;
	}
}

inline void ToaClearOpposites(unsigned char* nJoystickInputs)
{
	if ((*nJoystickInputs & 0x03) == 0x03) {
		*nJoystickInputs &= ~0x03;
	}
	if ((*nJoystickInputs & 0x0C) == 0x0C) {
		*nJoystickInputs &= ~0x0C;
	}
}

// toa_pal.cpp
extern unsigned char *ToaPalSrc;
extern unsigned int* ToaPalette;
extern unsigned char ToaRecalcPalette;
extern int nToaPalLen;

int ToaPalInit();
int ToaPalExit();
int ToaPalUpdate();

// toa_gp9001.cpp
extern unsigned char* GP9001ROM[2];
extern unsigned int nGP9001ROMSize[2];

extern unsigned int GP9001TileBank[8];

extern unsigned char* GP9001RAM[2];
extern unsigned short* GP9001Reg[2];

extern int nSpriteXOffset, nSpriteYOffset, nSpritePriority;

extern int nLayer0XOffset, nLayer0YOffset, nLayer0Priority;
extern int nLayer1XOffset, nLayer1YOffset, nLayer1Priority;
extern int nLayer2XOffset, nLayer2YOffset, nLayer2Priority;
extern int nLayer3XOffset, nLayer3YOffset;

int ToaBufferGP9001Sprites();
int ToaRenderGP9001();
int ToaInitGP9001(int n = 1);
int ToaExitGP9001();
int ToaScanGP9001(int nAction, int* pnMin);

inline static void ToaGP9001SetRAMPointer(unsigned int wordValue, const int nController = 0)
{
	extern unsigned char* GP9001Pointer[2];

	wordValue &= 0x1FFF;
	GP9001Pointer[nController] = GP9001RAM[nController] + (wordValue << 1);
}

inline static void ToaGP9001WriteRAM(const unsigned short wordValue, const int nController)
{
	extern unsigned char* GP9001Pointer[2];

	*((unsigned short*)(GP9001Pointer[nController])) = wordValue;
	GP9001Pointer[nController] += 2;
}

inline static unsigned short ToaGP9001ReadRAM_Hi(const int nController)
{
	extern unsigned char* GP9001Pointer[2];

	return *((unsigned short*)(GP9001Pointer[nController]));
}

inline static unsigned short ToaGP9001ReadRAM_Lo(const int nController)
{
	extern unsigned char* GP9001Pointer[2];

	return *((unsigned short*)(GP9001Pointer[nController] + 2));
}

inline static void ToaGP9001SelectRegister(const unsigned short wordValue, const int nController = 0)
{
	extern int GP9001Regnum[2];

	GP9001Regnum[nController] = wordValue & 0xFF;
}

inline static void ToaGP9001WriteRegister(const unsigned short wordValue, const int nController = 0)
{
	extern int GP9001Regnum[2];

	GP9001Reg[nController][GP9001Regnum[nController]] = wordValue;
}

inline static unsigned short ToaVBlankRegister()
{
	int nCycles = SekTotalCycles();

	if (nCycles >= nToaCyclesVBlankStart) {
		return 1;
	} else {
		if (nCycles < nToaCyclesDisplayStart) {
			return 1;
		}
	}
	return 0;
}

inline static unsigned short ToaScanlineRegister()
{
	static int nPreviousScanline;
	unsigned short nFlags = 0xFE00;
	int nCurrentScanline = SekCurrentScanline();

#if 0
	// None of the games actually use this
	int nCurrentBeamPosition = SekTotalCycles() % nToaCyclesScanline;
	if (nCurrentBeamPosition < 64) {
		nFlags &= ~0x4000;
	}
#endif

	if (nCurrentScanline != nPreviousScanline) {
		nPreviousScanline = nCurrentScanline;
		nFlags &= ~0x8000;

//		bprintf(PRINT_NORMAL, _T("  - line %3i, PC 0x%08X\n"), nCurrentScanline, SekGetPC(-1));

	}

	return nFlags | nCurrentScanline;
}

// toa_extratext.cpp
extern unsigned char* ExtraTROM;
extern unsigned char* ExtraTRAM;
extern unsigned char* ExtraTScroll;
extern unsigned char* ExtraTSelect;
extern int nExtraTXOffset;

int ToaExtraTextLayer();
int ToaExtraTextInit();
void ToaExtraTextExit();
