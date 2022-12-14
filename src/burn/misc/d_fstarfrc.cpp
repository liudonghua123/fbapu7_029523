#include "tiles_generic.h"
#include "msm6295.h"
#include "burn_ym2151.h"

static unsigned char  FstarfrcInputPort0[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char  FstarfrcDip[2]         = {0, 0};
static unsigned short FstarfrcInput[1]       = {0x00};
static unsigned char  FstarfrcReset          = 0;

static unsigned char  *Mem                   = NULL;
static unsigned char  *MemEnd                = NULL;
static unsigned char  *RamStart              = NULL;
static unsigned char  *RamEnd                = NULL;
static unsigned char  *FstarfrcRom           = NULL;
static unsigned char  *FstarfrcZ80Rom        = NULL;
static unsigned char  *FstarfrcRam           = NULL;
static unsigned char  *FstarfrcCharRam       = NULL;
static unsigned char  *FstarfrcVideoRam      = NULL;
static unsigned char  *FstarfrcColourRam     = NULL;
static unsigned char  *FstarfrcVideo2Ram     = NULL;
static unsigned char  *FstarfrcColour2Ram    = NULL;
static unsigned char  *FstarfrcSpriteRam     = NULL;
static unsigned char  *FstarfrcPaletteRam    = NULL;
static unsigned char  *FstarfrcZ80Ram        = NULL;
static unsigned int   *FstarfrcPalette       = NULL;
static unsigned char  *FstarfrcCharTiles     = NULL;
static unsigned char  *FstarfrcLayerTiles    = NULL;
static unsigned char  *FstarfrcSpriteTiles   = NULL;
static unsigned char  *FstarfrcTempGfx       = NULL;

static int CharScrollX;
static int Scroll1X;
static int Scroll1Y;
static int Scroll2X;
static int Scroll2Y;

static int FstarfrcSoundLatch;

static int nCyclesDone[2], nCyclesTotal[2];
static int nCyclesSegment;

static struct BurnInputInfo FstarfrcInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , FstarfrcInputPort0 + 14, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , FstarfrcInputPort0 +  6, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , FstarfrcInputPort0 + 15, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , FstarfrcInputPort0 +  7, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , FstarfrcInputPort0 +  3, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , FstarfrcInputPort0 +  2, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , FstarfrcInputPort0 +  1, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , FstarfrcInputPort0 +  0, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , FstarfrcInputPort0 +  4, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , FstarfrcInputPort0 +  5, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , FstarfrcInputPort0 + 11, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , FstarfrcInputPort0 + 10, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , FstarfrcInputPort0 +  9, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , FstarfrcInputPort0 +  8, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , FstarfrcInputPort0 + 12, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , FstarfrcInputPort0 + 13, "p2 fire 2" },

	{"Reset"             , BIT_DIGITAL  , &FstarfrcReset         , "reset"     },
	{"Dip 1"             , BIT_DIPSWITCH, FstarfrcDip + 0        , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, FstarfrcDip + 1        , "dip"       },
};

STDINPUTINFO(Fstarfrc);

inline void FstarfrcMakeInputs()
{
	// Reset Inputs
	FstarfrcInput[0] = 0x3fff;

	// Compile Digital Inputs
	for (int i = 0; i < 14; i++) {
		FstarfrcInput[0] -= (FstarfrcInputPort0[i] & 1) << i;
	}

	for (int i = 14; i < 16; i++) {
		FstarfrcInput[0] |= (FstarfrcInputPort0[i] & 1) << i;
	}
}

static struct BurnDIPInfo FstarfrcDIPList[]=
{
	// Default Values
	{0x11, 0xff, 0xff, 0xff, NULL                     },
	{0x12, 0xff, 0xff, 0xff, NULL                     },

	// Dip 1
	{0   , 0xfe, 0   , 4   , "Coin SW 1"              },
	{0x11, 0x01, 0x03, 0x03, "1 Coin 1 Credit"        },
	{0x11, 0x01, 0x03, 0x02, "1 Coin 2 Credits"       },
	{0x11, 0x01, 0x03, 0x01, "1 Coin 3 Credits"       },
	{0x11, 0x01, 0x03, 0x00, "1 Coin 4 Credits"       },

	{0   , 0xfe, 0   , 4   , "Coin SW 2"              },
	{0x11, 0x01, 0x0c, 0x00, "4 Coins 1 Credit"       },
	{0x11, 0x01, 0x0c, 0x04, "3 Coins 1 Credit"       },
	{0x11, 0x01, 0x0c, 0x08, "2 Coins 1 Credit"       },
	{0x11, 0x01, 0x0c, 0x0c, "1 Coin  1 Credit"       },

	{0   , 0xfe, 0   , 2   , "Screen Reverse"         },
	{0x11, 0x01, 0x10, 0x10, "Off"                    },
	{0x11, 0x01, 0x10, 0x00, "On"                     },

	{0   , 0xfe, 0   , 2   , "Demonstration Sound"    },
	{0x11, 0x01, 0x20, 0x00, "Off"                    },
	{0x11, 0x01, 0x20, 0x20, "On"                     },

	{0   , 0xfe, 0   , 2   , "Continue Play"          },
	{0x11, 0x01, 0x40, 0x00, "Off"                    },
	{0x11, 0x01, 0x40, 0x40, "On"                     },

	{0   , 0xfe, 0   , 2   , "Free Play"              },
	{0x11, 0x01, 0x80, 0x80, "Off"                    },
	{0x11, 0x01, 0x80, 0x00, "On"                     },

	// Dip 2
	{0   , 0xfe, 0   , 4   , "The Number of Player"   },
	{0x12, 0x01, 0x03, 0x00, "2"                      },
	{0x12, 0x01, 0x03, 0x03, "3"                      },
	{0x12, 0x01, 0x03, 0x02, "4"                      },
	{0x12, 0x01, 0x03, 0x01, "5"                      },

	{0   , 0xfe, 0   , 4   , "Difficulty"             },
	{0x12, 0x01, 0x0c, 0x08, "Easy"                   },
	{0x12, 0x01, 0x0c, 0x0c, "Medium"                 },
	{0x12, 0x01, 0x0c, 0x04, "Hard"                   },
	{0x12, 0x01, 0x0c, 0x00, "Hardest"                },

	{0   , 0xfe, 0   , 4   , "Level Up Speed"         },
	{0x12, 0x01, 0x30, 0x00, "Slowest"                },
	{0x12, 0x01, 0x30, 0x10, "Slow"                   },
	{0x12, 0x01, 0x30, 0x30, "Fast"                   },
	{0x12, 0x01, 0x30, 0x20, "Fastest"                },

	{0   , 0xfe, 0   , 4   , "Bonus Life"             },
	{0x12, 0x01, 0xc0, 0xc0, "200,000, 1,000,000"     },
	{0x12, 0x01, 0xc0, 0x80, "220,000, 1,200,000"     },
	{0x12, 0x01, 0xc0, 0x40, "240,000, 1,400,000"     },
	{0x12, 0x01, 0xc0, 0x00, "Every 500,000, Once at Highest Score"},
};

STDDIPINFO(Fstarfrc);

static struct BurnRomInfo FstarfrcRomDesc[] = {
	{ "fstarf01.rom",  0x40000, 0x94c71de6, BRF_ESS | BRF_PRG }, //  0	68000 Program Code
	{ "fstarf02.rom",  0x40000, 0xb1a07761, BRF_ESS | BRF_PRG }, //  1	68000 Program Code

	{ "fstarf03.rom",  0x20000, 0x54375335, BRF_GRA },			 //  2
	{ "fstarf05.rom",  0x80000, 0x77a281e7, BRF_GRA },			 //  3
	{ "fstarf04.rom",  0x80000, 0x398a920d, BRF_GRA },			 //  4
	{ "fstarf09.rom",  0x80000, 0xd51341d2, BRF_GRA },			 //  5
	{ "fstarf06.rom",  0x80000, 0x07e40e87, BRF_GRA },			 //  6

	{ "fstarf07.rom",  0x10000, 0xe0ad5de1, BRF_SND },			 //  7	Z80 Program Code

	{ "fstarf08.rom",  0x20000, 0xf0ad5693, BRF_SND },			 //  8	Samples
};


STD_ROM_PICK(Fstarfrc);
STD_ROM_FN(Fstarfrc);

void FstarfrcDecode8x8Tiles(unsigned char *pTile, int Num)
{
	int c, y;

	for (c = 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			pTile[(c * 64) + (y * 8) + 0] = FstarfrcTempGfx[0x00000 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 1] = FstarfrcTempGfx[0x00000 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 2] = FstarfrcTempGfx[0x00001 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 3] = FstarfrcTempGfx[0x00001 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 4] = FstarfrcTempGfx[0x00002 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 5] = FstarfrcTempGfx[0x00002 + (y * 4) + (c * 32)] & 0x0f;
			pTile[(c * 64) + (y * 8) + 6] = FstarfrcTempGfx[0x00003 + (y * 4) + (c * 32)] >> 4;
			pTile[(c * 64) + (y * 8) + 7] = FstarfrcTempGfx[0x00003 + (y * 4) + (c * 32)] & 0x0f;
		}
	}
}

void FstarfrcDecode16x16Tiles(unsigned char *pTile, int Num)
{
	int c, y;

	for (c = 0; c < Num; c++) {
		for (y = 0; y < 8; y++) {
			pTile[(c * 256) + (y * 16) +  0] = FstarfrcTempGfx[0x00000 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = FstarfrcTempGfx[0x00000 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = FstarfrcTempGfx[0x00001 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = FstarfrcTempGfx[0x00001 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = FstarfrcTempGfx[0x00002 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = FstarfrcTempGfx[0x00002 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = FstarfrcTempGfx[0x00003 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = FstarfrcTempGfx[0x00003 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = FstarfrcTempGfx[0x00020 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = FstarfrcTempGfx[0x00020 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = FstarfrcTempGfx[0x00021 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = FstarfrcTempGfx[0x00021 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = FstarfrcTempGfx[0x00022 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = FstarfrcTempGfx[0x00022 + (y * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = FstarfrcTempGfx[0x00023 + (y * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = FstarfrcTempGfx[0x00023 + (y * 4) + (c * 128)] & 0x0f;
		}

		for (y = 8; y < 16; y++) {
			pTile[(c * 256) + (y * 16) +  0] = FstarfrcTempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  1] = FstarfrcTempGfx[0x00000 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  2] = FstarfrcTempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  3] = FstarfrcTempGfx[0x00001 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  4] = FstarfrcTempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  5] = FstarfrcTempGfx[0x00002 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  6] = FstarfrcTempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  7] = FstarfrcTempGfx[0x00003 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) +  8] = FstarfrcTempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) +  9] = FstarfrcTempGfx[0x00020 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 10] = FstarfrcTempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 11] = FstarfrcTempGfx[0x00021 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 12] = FstarfrcTempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 13] = FstarfrcTempGfx[0x00022 + ((y + 8) * 4) + (c * 128)] & 0x0f;
			pTile[(c * 256) + (y * 16) + 14] = FstarfrcTempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] >> 4;
			pTile[(c * 256) + (y * 16) + 15] = FstarfrcTempGfx[0x00023 + ((y + 8) * 4) + (c * 128)] & 0x0f;
		}
	}
}

int FstarfrcDoReset()
{
	CharScrollX = Scroll1X = Scroll1Y = Scroll2X = Scroll2Y = 0;

	FstarfrcSoundLatch = 0;

	SekOpen(0);
	SekReset();
	SekClose();

	ZetReset();

	MSM6295Reset(0);
	BurnYM2151Reset();

	return 0;
}

void FstarfrcYM2151IrqHandler(int Irq)
{
	if (Irq) {
		ZetRaiseIrq(1);
	} else {
		ZetLowerIrq();
	}
}

unsigned short __fastcall FstarfrcReadWord(unsigned int a)
{
	switch (a) {
		case 0x150030: {
			SEK_DEF_READ_WORD(0, a);
		}

		case 0x150040: {
			SEK_DEF_READ_WORD(0, a);
		}

		case 0x150050: {
			return FstarfrcInput[0];
		}
	}

	return 0;
}

unsigned char __fastcall FstarfrcReadByte(unsigned int a)
{
	switch (a) {
		case 0x150031: {
			return FstarfrcDip[1];
		}
		case 0x150041: {
			return FstarfrcDip[0];
		}
	}

	return 0;
}

void __fastcall FstarfrcWriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x150010: {
			SEK_DEF_WRITE_WORD(0, a, d);
			return;
		}

		case 0x160000: {
			CharScrollX = d;
			return;
		}

		case 0x16000c: {
			Scroll1X = d;
			return;
		}

		case 0x160012: {
			Scroll1Y = d;
			return;
		}

		case 0x160018: {
			Scroll2X = d;
			return;
		}

		case 0x16001e: {
			Scroll2Y = d;
			return;
		}
	}
}

void __fastcall FstarfrcWriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x150011: {
			FstarfrcSoundLatch = d & 0xff;
			ZetNmi();
			return;
		}
	}
}

unsigned char __fastcall FstarfrcZ80Read(unsigned short a)
{
	switch (a) {
		case 0xfc00: {
			return MSM6295ReadStatus(0);
		}

		case 0xfc05: {
			return BurnYM2151ReadStatus();
		}

		case 0xfc08: {
			return FstarfrcSoundLatch;
		}
	}

	return 0;
}

void __fastcall FstarfrcZ80Write(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xfc00: {
			MSM6295Command(0, d);
			return;
		}

		case 0xfc04: {
			BurnYM2151SelectRegister(d);
			return;
		}

		case 0xfc05: {
			BurnYM2151WriteRegister(d);
			return;
		}
	}
}

static int FstarfrcMemIndex()
{
	unsigned char *Next; Next = Mem;

	FstarfrcRom          = Next; Next += 0x80000;
	FstarfrcZ80Rom       = Next; Next += 0x10000;
	MSM6295ROM           = Next; Next += 0x20000;

	RamStart = Next;

	FstarfrcRam          = Next; Next += 0x0a000;
	FstarfrcCharRam      = Next; Next += 0x01000;
	FstarfrcVideoRam     = Next; Next += 0x00800;
	FstarfrcColourRam    = Next; Next += 0x00800;
	FstarfrcVideo2Ram    = Next; Next += 0x00800;
	FstarfrcColour2Ram   = Next; Next += 0x00800;
	FstarfrcSpriteRam    = Next; Next += 0x01000;
	FstarfrcPaletteRam   = Next; Next += 0x00800;
	FstarfrcZ80Ram       = Next; Next += 0x0c002;

	RamEnd = Next;

	FstarfrcCharTiles    = Next; Next += (4096 * 8 * 8);
	FstarfrcLayerTiles   = Next; Next += (8192 * 16 * 16);
	FstarfrcSpriteTiles  = Next; Next += (32768 * 8 * 8);
	FstarfrcPalette      = (unsigned int*)Next; Next += 0x00800 * sizeof(unsigned int);
	MemEnd = Next;

	return 0;
}

int FstarfrcInit()
{
	int nRet = 0, nLen;

	// Allocate and Blank all required memory
	Mem = NULL;
	FstarfrcMemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	FstarfrcMemIndex();

	FstarfrcTempGfx = (unsigned char*)malloc(0x100000);

	// Load and byte-swap 68000 Program roms
	nRet = BurnLoadRom(FstarfrcRom + 0x00001, 0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(FstarfrcRom + 0x00000, 1, 2); if (nRet != 0) return 1;

	// Load and decode Char Tiles rom
	memset(FstarfrcTempGfx, 0, 0x100000);
	nRet = BurnLoadRom(FstarfrcTempGfx, 2, 1); if (nRet != 0) return 1;
	FstarfrcDecode8x8Tiles(FstarfrcCharTiles, 4096);

	// Load, byteswap and decode Bg and Fg Layer roms
	memset(FstarfrcTempGfx, 0, 0x100000);
	nRet = BurnLoadRom(FstarfrcTempGfx + 0x000000, 3, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(FstarfrcTempGfx + 0x000001, 4, 2); if (nRet != 0) return 1;
	FstarfrcDecode16x16Tiles(FstarfrcLayerTiles, 8192);

	// Load, byteswap and decode Sprite Tile roms
	memset(FstarfrcTempGfx, 0, 0x100000);
	nRet = BurnLoadRom(FstarfrcTempGfx + 0x000000, 5, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(FstarfrcTempGfx + 0x000001, 6, 2); if (nRet != 0) return 1;
	FstarfrcDecode8x8Tiles(FstarfrcSpriteTiles, 32768);

	free(FstarfrcTempGfx);

	// Load Z80 Program rom
	nRet = BurnLoadRom(FstarfrcZ80Rom, 7, 1); if (nRet != 0) return 1;

	// Load Sample Rom
	nRet = BurnLoadRom(MSM6295ROM, 8, 1); if (nRet != 0) return 1;

	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(FstarfrcRom         , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(FstarfrcRam         , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(FstarfrcCharRam     , 0x110000, 0x110fff, SM_RAM);
	SekMapMemory(FstarfrcVideoRam    , 0x120000, 0x1207ff, SM_RAM);
	SekMapMemory(FstarfrcColourRam   , 0x120800, 0x120fff, SM_RAM);
	SekMapMemory(FstarfrcVideo2Ram   , 0x121000, 0x1217ff, SM_RAM);
	SekMapMemory(FstarfrcColour2Ram  , 0x121800, 0x121fff, SM_RAM);
	SekMapMemory(FstarfrcRam + 0x4000, 0x122000, 0x127fff, SM_RAM);
	SekMapMemory(FstarfrcSpriteRam   , 0x130000, 0x130fff, SM_RAM);
	SekMapMemory(FstarfrcPaletteRam  , 0x140000, 0x1407ff, SM_RAM);
	SekSetReadWordHandler(0, FstarfrcReadWord);
	SekSetWriteWordHandler(0, FstarfrcWriteWord);
	SekSetReadByteHandler(0, FstarfrcReadByte);
	SekSetWriteByteHandler(0, FstarfrcWriteByte);
	SekClose();

	// Setup the Z80 emulation
	ZetInit(1);
	ZetMapArea(0x0000, 0xefff, 0, FstarfrcZ80Rom         );
	ZetMapArea(0x0000, 0xefff, 2, FstarfrcZ80Rom         );
	ZetMapArea(0xf000, 0xfbff, 0, FstarfrcZ80Ram         );
	ZetMapArea(0xf000, 0xfbff, 1, FstarfrcZ80Ram         );
	ZetMapArea(0xf000, 0xfbff, 2, FstarfrcZ80Ram         );
	ZetMapArea(0xfffe, 0xffff, 0, FstarfrcZ80Ram + 0xc000);
	ZetMapArea(0xfffe, 0xffff, 1, FstarfrcZ80Ram + 0xc000);
	ZetMapArea(0xfffe, 0xffff, 2, FstarfrcZ80Ram + 0xc000);
	ZetMemEnd();
	ZetSetReadHandler(FstarfrcZ80Read);
	ZetSetWriteHandler(FstarfrcZ80Write);

	// Setup the YM2151 emulation
	BurnYM2151Init(8000000 / 2, nBurnSoundRate);
	BurnYM2151SetIrqHandler(&FstarfrcYM2151IrqHandler);

	// Setup the OKIM6295 emulation
	MSM6295Init(0, 7575, 40, 1);

	GenericTilesInit();

	// Reset the driver
	FstarfrcDoReset();

	return 0;
}

int FstarfrcExit()
{
	BurnYM2151Exit();
	MSM6295Exit(0);

	SekExit();
	ZetExit();

	GenericTilesExit();

	free(Mem);
	Mem = NULL;

	return 0;
}

void FstarfrcRenderBgLayer()
{
	int mx, my, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 32; mx++) {
			Code = ((FstarfrcVideo2Ram[TileIndex + 1] << 8) | FstarfrcVideo2Ram[TileIndex + 0]) & 0x1fff;
			Colour = (((FstarfrcColour2Ram[TileIndex + 1] << 8) | FstarfrcColour2Ram[TileIndex + 0]) & 0x0f);

			x = 16 * mx;
			y = 16 * my;

			x -= Scroll2X;
			y -= Scroll2Y;

			x &= 0x1ff;
			y &= 0x1ff;

			if (x >= 496) x -= 512;
			if (y >= 496) y -= 512;

			y -= 16;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile_Mask(Code, x, y, Colour, 4, 0, 512 + (0x10 << 4), FstarfrcLayerTiles);
			} else {
				Render16x16Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 512 + (0x10 << 4), FstarfrcLayerTiles);
			}

			TileIndex += 2;
		}
	}
}

void FstarfrcRenderFgLayer()
{
	int mx, my, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 32; mx++) {
			Code = ((FstarfrcVideoRam[TileIndex + 1] << 8) | FstarfrcVideoRam[TileIndex + 0]) & 0x1fff;
			Colour = ((FstarfrcColourRam[TileIndex + 1] << 8) | FstarfrcColourRam[TileIndex + 0]) & 0x0f;

			x = 16 * mx;
			y = 16 * my;

			x -= Scroll1X;
			y -= Scroll1Y;

			x &= 0x1ff;
			y &= 0x1ff;

			if (x >= 496) x -= 512;
			if (y >= 496) y -= 512;

			y -= 16;

			if (x > 15 && x < 240 && y > 15 && y < 208) {
				Render16x16Tile_Mask(Code, x, y, Colour, 4, 0, 512, FstarfrcLayerTiles);
			} else {
				Render16x16Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 512, FstarfrcLayerTiles);
			}

			TileIndex += 2 ;
		}
	}
}

void FstarfrcRenderTextLayer()
{
	int mx, my, Code, Colour, x, y, TileIndex = 0;

	for (my = 0; my < 32; my++) {
		for (mx = 0; mx < 64; mx++) {
			Code = (FstarfrcCharRam[TileIndex + 1] << 8) | FstarfrcCharRam[TileIndex + 0];
			Colour = Code >> 12;
			Code &= 0x0fff;

			x = 8 * mx;
			y = 8 * my;

			x -= CharScrollX;

			x &= 0x1ff;
			y &= 0x0ff;

			if (x > 7 && x < 248 && y > 7 && y < 216) {
				Render8x8Tile_Mask(Code, x, y, Colour, 4, 0, 256, FstarfrcCharTiles);
			} else {
				Render8x8Tile_Mask_Clip(Code, x, y, Colour, 4, 0, 256, FstarfrcCharTiles);
			}

			TileIndex += 2 ;
		}
	}
}

static void draw_sprites(int layerpriority)
{
	unsigned short* pFstarfrcSpriteRam = ((unsigned short*)FstarfrcSpriteRam);


	int offs;
	const UINT8 layout[8][8] =
	{
		{0,1,4,5,16,17,20,21},
		{2,3,6,7,18,19,22,23},
		{8,9,12,13,24,25,28,29},
		{10,11,14,15,26,27,30,31},
		{32,33,36,37,48,49,52,53},
		{34,35,38,39,50,51,54,55},
		{40,41,44,45,56,57,60,61},
		{42,43,46,47,58,59,62,63}
	};

	for (offs = 0; offs < 0x1000 / 2; offs += 8)
	{
		if (pFstarfrcSpriteRam[offs] & 0x04)	/* enable */
		{
			int code,color,sizex,sizey,flipx,flipy,xpos,ypos;
			int x,y,priority;

			code = pFstarfrcSpriteRam[offs+1];
			color = (pFstarfrcSpriteRam[offs+2] & 0xf0) >> 4;
			sizex = 1 << ((pFstarfrcSpriteRam[offs+2] & 0x03) >> 0);
			sizey = 1 << ((pFstarfrcSpriteRam[offs+2] & 0x0c) >> 2);
			if (sizex >= 2) code &= ~0x01;
			if (sizey >= 2) code &= ~0x02;
			if (sizex >= 4) code &= ~0x04;
			if (sizey >= 4) code &= ~0x08;
			if (sizex >= 8) code &= ~0x10;
			if (sizey >= 8) code &= ~0x20;
			flipx = pFstarfrcSpriteRam[offs] & 0x01;
			flipy = pFstarfrcSpriteRam[offs] & 0x02;
			xpos = pFstarfrcSpriteRam[offs+4];
			if (xpos >= 0x8000) xpos -= 0x10000;
			ypos = pFstarfrcSpriteRam[offs+3];
			if (ypos >= 0x8000) ypos -= 0x10000;
			priority = (pFstarfrcSpriteRam[offs] & 0xc0) >> 6;

			if (priority != layerpriority) continue;

			for (y = 0;y < sizey;y++)
			{
				for (x = 0;x < sizex;x++)
				{
					int sx = xpos + 8*(flipx?(sizex-1-x):x);
					int sy = ypos + 8*(flipy?(sizey-1-y):y);

					if ((code + layout[y][x]) > 32767) break;

					sy -= 16;

					if (sx > 7 && sx < 248 && sy > 7 && sy < 216) {
						if (!flipx) {
							if (!flipy) {
								Render8x8Tile_Mask(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							} else {
								Render8x8Tile_Mask_FlipY(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							}
						} else {
							if (!flipy) {
								Render8x8Tile_Mask_FlipX(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							} else {
								Render8x8Tile_Mask_FlipXY(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							}
						}
					} else {
						if (!flipx) {
							if (!flipy) {
								Render8x8Tile_Mask_Clip(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							} else {
								Render8x8Tile_Mask_FlipY_Clip(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							}
						} else {
							if (!flipy) {
								Render8x8Tile_Mask_FlipX_Clip(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							} else {
								Render8x8Tile_Mask_FlipXY_Clip(code + layout[y][x], sx, sy, color, 4, 0, 0, FstarfrcSpriteTiles);
							}
						}
					}
				}
			}
		}
	}
}

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = (nColour >> 0) & 0x0f;
	g = (nColour >> 4) & 0x0f;
	b = (nColour >> 8) & 0x0f;

	r = (r << 4) | r;
	g = (g << 4) | g;
	b = (b << 4) | b;

	return BurnHighCol(r, g, b, 0);
}

int FstarfrcCalcPalette()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)FstarfrcPaletteRam, pd = FstarfrcPalette; i < 0x800; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}

	return 0;
}

void FstarfrcRender()
{
	BurnTransferClear();
	FstarfrcCalcPalette();
	draw_sprites(3);
	FstarfrcRenderBgLayer();
	draw_sprites(2);
	FstarfrcRenderFgLayer();
	draw_sprites(1);
	FstarfrcRenderTextLayer();
	draw_sprites(0);
	BurnTransferCopy(FstarfrcPalette);
}

int FstarfrcFrame()
{
	int nInterleave = 10;

	if (FstarfrcReset) FstarfrcDoReset();

	FstarfrcMakeInputs();

	nCyclesTotal[0] = (24000000 / 2) / 60;
	nCyclesTotal[1] = (8000000 / 2) / 60;
	nCyclesDone[0] = nCyclesDone[1] = 0;

	int nSoundBufferPos = 0;

	SekNewFrame();

	SekOpen(0);
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000
		nCurrentCPU = 0;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);

		// Run Z80
		nCurrentCPU = 1;
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;

		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen / nInterleave;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

			BurnYM2151Render(pSoundBuf, nSegmentLength);
			MSM6295Render(0, pSoundBuf, nSegmentLength);
			nSoundBufferPos += nSegmentLength;
		}
	}

	SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
	SekClose();

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);

		if (nSegmentLength) {
			BurnYM2151Render(pSoundBuf, nSegmentLength);
			MSM6295Render(0, pSoundBuf, nSegmentLength);
		}
	}

	if (pBurnDraw) FstarfrcRender();

	return 0;
}

static int FstarfrcScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin != NULL) {					// Return minimum compatible version
		*pnMin = 0x02944;
	}

	if (nAction & 4) {						// Scan volatile ram
		memset(&ba, 0, sizeof(ba));
    		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);

		SekScan(nAction & 3);					// Scan 68000
		ZetScan(nAction);					// Scan Z80

		MSM6295Scan(0, nAction);			// Scan OKIM6295
		BurnYM2151Scan(nAction);

		// Scan critical driver variables
		SCAN_VAR(FstarfrcSoundLatch);
		SCAN_VAR(FstarfrcInput);
		SCAN_VAR(FstarfrcDip);
		SCAN_VAR(CharScrollX);
		SCAN_VAR(Scroll1X);
		SCAN_VAR(Scroll1Y);
		SCAN_VAR(Scroll2X);
		SCAN_VAR(Scroll2Y);
	}

	return 0;
}

struct BurnDriver BurnDrvFstarfrc = {
	"fstarfrc", NULL, NULL, "1992",
	"Final Star Force (US)\0", NULL, "Tecmo", "Miscellaneous",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL | BDF_ORIENTATION_FLIPPED, 2, HARDWARE_MISC_MISC,
	NULL, FstarfrcRomInfo, FstarfrcRomName, FstarfrcInputInfo, FstarfrcDIPInfo,
	FstarfrcInit, FstarfrcExit, FstarfrcFrame, NULL, FstarfrcScan,
	NULL, 224, 256, 3, 4
};
