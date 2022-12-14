#include "toaplan.h"
// Battle Garegga

static unsigned char DrvButton[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char DrvJoy1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char DrvJoy2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char DrvInput[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static unsigned char DrvReset = 0;
static unsigned char bDrawScreen;
static bool bVBlank;

static unsigned char nIRQPending;

static int nSoundCommand;

// Z80 ROM bank
static int nCurrentBank;

static int nSpeedHackOffset;

// Rom information
static struct BurnRomInfo battlegRomDesc[] = {
	{ "u123",         0x080000, 0x88A4E66A, BRF_ESS | BRF_PRG }, //  0 CPU #0 code (even)
	{ "u65",          0x080000, 0x5DEA32A3, BRF_ESS | BRF_PRG }, //  1				(odd)

	{ "rom4.bin",     0x200000, 0xB333D81F, BRF_GRA },			 //  2 GP9001 Tile data
	{ "rom3.bin",     0x200000, 0x51B9EBFB, BRF_GRA },			 //  3
	{ "rom2.bin",     0x200000, 0xB330E5E2, BRF_GRA },			 //  4
	{ "rom1.bin",     0x200000, 0x7EAFDD70, BRF_GRA },			 //  5

	{ "text.u81",     0x008000, 0xE67FD534, BRF_GRA },			 //  6 Extra text layer tile data

	{ "snd.bin",      0x020000, 0x68632952, BRF_ESS | BRF_PRG }, //  7 Z80 program

	{ "rom5.bin",     0x100000, 0xF6D49863, BRF_SND },			 //  8 MSM6295 ADPCM data
};


STD_ROM_PICK(battleg);
STD_ROM_FN(battleg);

static struct BurnRomInfo battlegaRomDesc[] = {
	{ "prg0.bin",     0x080000, 0xF80C2FC2, BRF_ESS | BRF_PRG }, //  0 CPU #0 code (even)
	{ "prg1.bin",     0x080000, 0x2CCFDD1E, BRF_ESS | BRF_PRG }, //  1				(odd)

	{ "rom4.bin",     0x200000, 0xB333D81F, BRF_GRA },			 //  2 GP9001 Tile data
	{ "rom3.bin",     0x200000, 0x51B9EBFB, BRF_GRA },			 //  3
	{ "rom2.bin",     0x200000, 0xB330E5E2, BRF_GRA },			 //  4
	{ "rom1.bin",     0x200000, 0x7EAFDD70, BRF_GRA },			 //  5

	{ "text.u81",     0x008000, 0xE67FD534, BRF_GRA },			 //  6 Extra text layer tile data

	{ "snd.bin",      0x020000, 0x68632952, BRF_ESS | BRF_PRG }, //  7 Z80 program

	{ "rom5.bin",     0x100000, 0xF6D49863, BRF_SND },			 //  8 MSM6295 ADPCM data
};


STD_ROM_PICK(battlega);
STD_ROM_FN(battlega);

static struct BurnRomInfo battlegbRomDesc[] = {
	{ "prg_0.bin",    0x080000, 0x951ECC07, BRF_ESS | BRF_PRG }, //  0 CPU #0 code (even)
	{ "prg_1.bin",    0x080000, 0x729A60C6, BRF_ESS | BRF_PRG }, //  1				(odd)

	{ "rom4.bin",     0x200000, 0xB333D81F, BRF_GRA },			 //  2 GP9001 Tile data
	{ "rom3.bin",     0x200000, 0x51B9EBFB, BRF_GRA },			 //  3
	{ "rom2.bin",     0x200000, 0xB330E5E2, BRF_GRA },			 //  4
	{ "rom1.bin",     0x200000, 0x7EAFDD70, BRF_GRA },			 //  5

	{ "text.u81",     0x008000, 0xE67FD534, BRF_GRA },			 //  6 Extra text layer tile data

	{ "snd.bin",      0x020000, 0x68632952, BRF_ESS | BRF_PRG }, //  7 Z80 program

	{ "rom5.bin",     0x100000, 0xF6D49863, BRF_SND },			 //  8 MSM6295 ADPCM data
};


STD_ROM_PICK(battlegb);
STD_ROM_FN(battlegb);

static struct BurnRomInfo battlegcRomDesc[] = {
	{ "prg_0.rom",    0x080000, 0x26E0019E, BRF_ESS | BRF_PRG }, //  0 CPU #0 code (even)
	{ "prg_1.rom",    0x080000, 0x2CCFDD1E, BRF_ESS | BRF_PRG }, //  1				(odd)

	{ "rom4.bin",     0x200000, 0xB333D81F, BRF_GRA },			 //  2 GP9001 Tile data
	{ "rom3.bin",     0x200000, 0x51B9EBFB, BRF_GRA },			 //  3
	{ "rom2.bin",     0x200000, 0xB330E5E2, BRF_GRA },			 //  4
	{ "rom1.bin",     0x200000, 0x7EAFDD70, BRF_GRA },			 //  5

	{ "text.u81",     0x008000, 0xE67FD534, BRF_GRA },			 //  6 Extra text layer tile data

	{ "snd.bin",      0x020000, 0x68632952, BRF_ESS | BRF_PRG }, //  7 Z80 program

	{ "rom5.bin",     0x100000, 0xF6D49863, BRF_SND },			 //  8 MSM6295 ADPCM data
};


STD_ROM_PICK(battlegc);
STD_ROM_FN(battlegc);

static struct BurnInputInfo battlegInputList[] = {
	{"P1 Coin",		BIT_DIGITAL,	DrvButton + 3,	"p1 coin"},
	{"P1 Start",	BIT_DIGITAL,	DrvButton + 5,	"p1 start"},

	{"P1 Up",		BIT_DIGITAL,	DrvJoy1 + 0,	"p1 up"},
	{"P1 Down",		BIT_DIGITAL,	DrvJoy1 + 1,	"p1 down"},
	{"P1 Left",		BIT_DIGITAL,	DrvJoy1 + 2,	"p1 left"},
	{"P1 Right",	BIT_DIGITAL,	DrvJoy1 + 3,	"p1 right"},
	{"P1 Button 1",	BIT_DIGITAL,	DrvJoy1 + 4,	"p1 fire 1"},
	{"P1 Button 2",	BIT_DIGITAL,	DrvJoy1 + 5,	"p1 fire 2"},
	{"P1 Button 3",	BIT_DIGITAL,	DrvJoy1 + 6,	"p1 fire 3"},

	{"P2 Coin",		BIT_DIGITAL,	DrvButton + 4,	"p2 coin"},
	{"P2 Start",	BIT_DIGITAL,	DrvButton + 6,	"p2 start"},

	{"P2 Up",		BIT_DIGITAL,	DrvJoy2 + 0,	"p2 up"},
	{"P2 Down",		BIT_DIGITAL,	DrvJoy2 + 1,	"p2 down"},
	{"P2 Left",		BIT_DIGITAL,	DrvJoy2 + 2,	"p2 left"},
	{"P2 Right",	BIT_DIGITAL,	DrvJoy2 + 3,	"p2 right"},
	{"P2 Button 1",	BIT_DIGITAL,	DrvJoy2 + 4,	"p2 fire 1"},
	{"P2 Button 2",	BIT_DIGITAL,	DrvJoy2 + 5,	"p2 fire 2"},
	{"P2 Button 3",	BIT_DIGITAL,	DrvJoy2 + 6,	"p2 fire 3"},

	{"Reset",		BIT_DIGITAL,	&DrvReset,		"reset"},
	{"Diagnostics",	BIT_DIGITAL,	DrvButton + 0,	"diag"},
	{"Dip A",		BIT_DIPSWITCH,	DrvInput + 3,	"dip"},
	{"Dip B",		BIT_DIPSWITCH,	DrvInput + 4,	"dip"},
	{"Dip C",		BIT_DIPSWITCH,	DrvInput + 5,	"dip"},
};

STDINPUTINFO(battleg);

static struct BurnDIPInfo battlegDIPList[] = {

	// Defaults
	{0x14,	0xFF, 0xFF,	0x00, NULL},
	{0x15,	0xFF, 0xFF,	0x00, NULL},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Test mode"},
	{0x14,	0x01, 0x01,	0x00, "Normal"},
	{0x14,	0x01, 0x01,	0x01, "Test"},
	{0,		0xFE, 0,	2,	  "Starting coin"},
	{0x14,	0x01, 0x02,	0x00, "1 credit"},
	{0x14,	0x01, 0x02,	0x02, "2 credits"},
	{0,		0xFE, 0,	8,	  "Coin 1"},
	{0x14,	0x01, 0x1C, 0x00, "1 coin 1 credit"},
	{0x14,	0x01, 0x1C, 0x04, "1 coin 2 credits"},
	{0x14,	0x01, 0x1C, 0x08, "1 coin 3 credits"},
	{0x14,	0x01, 0x1C, 0x0C, "1 coin 3 credits"},
	{0x14,	0x01, 0x1C, 0x10, "2 coins 1 credit"},
	{0x14,	0x01, 0x1C, 0x14, "3 coins 1 credit"},
	{0x14,	0x01, 0x1C, 0x18, "4 coins 1 credit"},
	{0x14,	0x01, 0x1C, 0x1C, "Free Play"},
	// 0x1C: Free play settings active
	// Normal
	{0,		0xFE, 0,	7,	  "Coin 2"},
	{0x14,	0x82, 0xE0,	0x00, "1 coin 1 credit"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0x20, "1 coin 2 credits"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0x40, "1 coin 3 credits"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0x60, "1 coin 3 credits"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0x80, "2 coins 1 credit"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0xA0, "3 coins 1 credit"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0xC0, "4 coins 1 credit"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x82, 0xE0,	0x04, "1 coin 1 credit"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	// Free play
	{0,		0xFE, 0,	2,	  "Stick mode"},
	{0x14,	0x02, 0x20,	0x00, "Special"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x02, 0x20,	0x20, "Normal"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0,		0xFE, 0,	2,	  "Effect"},
	{0x14,	0x02, 0x40,	0x00, "Off"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x02, 0x40,	0x40, "On"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0,		0xFE, 0,	2,	  "Music"},
	{0x14,	0x02, 0x80,	0x00, "Off"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},
	{0x14,	0x02, 0x80,	0x80, "On"},
	{0x14,	0x00, 0x1C, 0x1C, NULL},

	// DIP 2
	{0,		0xFE, 0,	4,	  "Difficulty"},
	{0x15,	0x01, 0x03, 0x00, "Normal"},
	{0x15,	0x01, 0x03, 0x01, "Easy"},
	{0x15,	0x01, 0x03, 0x02, "Hard"},
	{0x15,	0x01, 0x03, 0x03, "Very hard"},
	{0,		0xFE, 0,	2,	  "Screen flip"},
	{0x15,	0x01, 0x04, 0x00, "Off"},
	{0x15,	0x01, 0x04, 0x04, "On"},
	{0,		0xFE, 0,	2,	  "Demo sound"},
	{0x15,	0x01, 0x08, 0x00, "On"},
	{0x15,	0x01, 0x08, 0x08, "Off"},
	{0,		0xFE, 0,	8,	  "Player counts"},
	{0x15,	0x01, 0x70, 0x00, "3"},
	{0x15,	0x01, 0x70, 0x10, "4"},
	{0x15,	0x01, 0x70, 0x20, "2"},
	{0x15,	0x01, 0x70, 0x30, "1"},
	{0x15,	0x01, 0x70, 0x40, "5"},
	{0x15,	0x01, 0x70, 0x50, "6"},
	{0x15,	0x01, 0x70, 0x60, "Multiple"},
	{0x15,	0x01, 0x70, 0x70, "Invincible"},
    // Nippon and U.S.A. regions
	{0,		0xFE, 0,	2,	  "Extra player"},
    {0x15,	0x02, 0x80, 0x00, "1000000 each"},
	{0x16,	0x00, 0x01, 0x00, NULL},
	{0x15,	0x02, 0x80, 0x80, "1000000 2000000"},
	{0x16,	0x00, 0x01, 0x00, NULL},
    // Europe/Denmark and Asia regions
	{0,		0xFE, 0,	2,	  "Extra player"},
	{0x15,	0x02, 0x80, 0x80, "2000000 each"},
	{0x16,	0x00, 0x01, 0x01, NULL},
	{0x15,	0x02, 0x80, 0x00, "No extra"},
	{0x16,	0x00, 0x01, 0x01, NULL},

	// DIP 3
	{0,		0xFE, 0,	2,	  "Continue play"},
	{0x16,	0x01, 0x04, 0x00, "On"},
	{0x16,	0x01, 0x04, 0x04, "Off"},
};

static struct BurnDIPInfo battlegRegionDIPList[] = {
	// Region
	{0x16,	0xFF, 0x0F,	0x01, NULL},
	{0,		0xFE, 0,	2,	  "Region"},
	{0x16,	0x01, 0x03, 0x01, "Denmark"},
	{0x16,	0x01, 0x03, 0x03, "China"},
	{0x16,	0x01, 0x03, 0x00, "Nippon [illegal setting]"},
	{0x16,	0x01, 0x03, 0x02, "U.S.A. [illegal setting]"},
};

static struct BurnDIPInfo battlegaRegionDIPList[] = {
	// DIP 3
	{0,		0xFE, 0,	2,	  "Stage edit"},
	{0x16,	0x01, 0x08, 0x00, "Disable"},
	{0x16,	0x01, 0x08, 0x08, "Enable"},

	// Region
	{0x16,	0xFF, 0x0F,	0x00, NULL},
	{0,		0xFE, 0,	4,	  "Region"},
	{0x16,	0x01, 0x03, 0x00, "Nippon"},
	{0x16,	0x01, 0x03, 0x01, "Europe"},
	{0x16,	0x01, 0x03, 0x02, "U.S.A."},
	{0x16,	0x01, 0x03, 0x03, "Asia"},
};

static struct BurnDIPInfo battlegbRegionDIPList[] = {
	// Region
	{0x16,	0xFF, 0x0F,	0x01, NULL},
	{0,		0xFE, 0,	2,	  "Region"},
	{0x16,	0x01, 0x03, 0x01, "Austria"},
	{0x16,	0x01, 0x03, 0x03, "Hongkong"},
	{0x16,	0x01, 0x03, 0x00, "Nippon [illegal setting]"},
	{0x16,	0x01, 0x03, 0x02, "U.S.A. [illegal setting]"},
};

STDDIPINFOEXT(battleg, battleg, battlegRegion);
STDDIPINFOEXT(battlega, battleg, battlegaRegion);
STDDIPINFOEXT(battlegb, battleg, battlegbRegion);

static unsigned char *Mem = NULL, *MemEnd = NULL;
static unsigned char *RamStart, *RamEnd;
static unsigned char *Rom01;
static unsigned char *Ram01, *Ram02, *RamPal;

static int nColCount = 0x0800;
static int nMSM6295ROMSize = 0x100000;

// This routine is called first to determine how much memory is needed (MemEnd-(unsigned char *)0),
// and then afterwards to set up all the pointers
static int MemIndex()
{
	unsigned char *Next; Next = Mem;
	Rom01		= Next; Next += 0x100000;			//
	RomZ80		= Next; Next += 0x020000;			// Z80 ROM
	GP9001ROM[0]= Next; Next += nGP9001ROMSize[0];	// GP9001 tile data
	ExtraTROM	= Next; Next += 0x010000;			// Extra Text layer tile data
	MSM6295ROM	= Next; Next += nMSM6295ROMSize;	// ADPCM data
	RamStart	= Next;
	Ram01		= Next; Next += 0x010000;			// CPU #0 work RAM
	Ram02		= Next; Next += 0x000800;			//
	ExtraTRAM	= Next; Next += 0x002000;			// Extra tile layer
	ExtraTScroll= Next; Next += 0x001000;			//
	ExtraTSelect= Next; Next += 0x001000;			//
	RamPal		= Next; Next += 0x001000;			// palette
	RamZ80		= Next; Next += 0x004000;			// Z80 RAM
	GP9001RAM[0]= Next; Next += 0x004000;
	GP9001Reg[0]= (unsigned short*)Next; Next += 0x0100 * sizeof(short);
	RamEnd		= Next;
	ToaPalette	= (unsigned int *)Next; Next += nColCount * sizeof(unsigned int);
	MemEnd		= Next;

	return 0;
}

static void drvZ80Bankswitch(int nBank)
{
	nBank &= 0x07;
	if (nBank != nCurrentBank) {
		unsigned char* nStartAddress = RomZ80 + (nBank << 14);
		ZetMapArea(0x8000, 0xBFFF, 0, nStartAddress);
		ZetMapArea(0x8000, 0xBFFF, 2, nStartAddress);

		nCurrentBank = nBank;
	}
}

// Scan ram
static int DrvScan(int nAction,int *pnMin)
{
	struct BurnArea ba;

	if (pnMin) {						// Return minimum compatible version
		*pnMin = 0x029497;
	}
	if (nAction & ACB_VOLATILE) {		// Scan volatile data

		memset(&ba, 0, sizeof(ba));
    	ba.Data		= RamStart;
		ba.nLen		= RamEnd-RamStart;
		ba.szName	= "All Ram";
		BurnAcb(&ba);

		SekScan(nAction);				// scan 68000 states
		ZetScan(nAction);				// Scan Z80
		SCAN_VAR(nCurrentBank);

		MSM6295Scan(0, nAction);
		BurnYM2151Scan(nAction);

		ToaScanGP9001(nAction, pnMin);

		SCAN_VAR(DrvInput);
		SCAN_VAR(nSoundCommand);
		SCAN_VAR(nIRQPending);

		if (nAction & ACB_WRITE) {
			int nBank = nCurrentBank;
			nCurrentBank = -1;
			drvZ80Bankswitch(nBank);
		}
	}

	return 0;
}

static int LoadRoms()
{
	// Load 68000 ROM
	if (ToaLoadCode(Rom01, 0, 2)) {
		return 1;
	}

	// Load GP9001 tile data
	ToaLoadGP9001Tiles(GP9001ROM[0], 2, 4, nGP9001ROMSize[0]);

	// Load Extra text layer tile data
	BurnLoadRom(ExtraTROM, 6, 1);

	// Load the Z80 ROM
	BurnLoadRom(RomZ80, 7, 1);

	// Load ADPCM data
	BurnLoadRom(MSM6295ROM, 8, 1);

	return 0;
}

unsigned char __fastcall battlegZ80Read(unsigned short nAddress)
{
//	printf("z80 read %4X\n", nAddress);
	switch (nAddress) {
		case 0xE001:
			return BurnYM2151ReadStatus();

		case 0xE004:
			return MSM6295ReadStatus(0);

		case 0xE01C:
			return nSoundCommand;

		case 0xE01D:
			// Bit 0 enables/disables interrupt processing (0 = enabled)
			return 0;
	}
	return 0;
}

void __fastcall battlegZ80Write(unsigned short nAddress, unsigned char nValue)
{
//	printf("z80 wrote %4X with %2X\n", nAddress, nValue);
	switch (nAddress) {
		case 0xE000:
			BurnYM2151SelectRegister(nValue);
			break;
		case 0xE001:
			BurnYM2151WriteRegister(nValue);
			break;

		case 0xE004:
			MSM6295Command(0, nValue);
			break;

		case 0xE006:
			MSM6295SampleInfo[0][0] = MSM6295ROM + ((nValue & 0x0F) << 16);
			MSM6295SampleData[0][0] = MSM6295ROM + ((nValue & 0x0F) << 16);
			MSM6295SampleInfo[0][1] = MSM6295ROM + ((nValue & 0xF0) << 12) + 0x0100;
			MSM6295SampleData[0][1] = MSM6295ROM + ((nValue & 0xF0) << 12);
			break;
		case 0xE008:
			MSM6295SampleInfo[0][2] = MSM6295ROM + ((nValue & 0x0F) << 16) + 0x0200;
			MSM6295SampleData[0][2] = MSM6295ROM + ((nValue & 0x0F) << 16);
			MSM6295SampleInfo[0][3] = MSM6295ROM + ((nValue & 0xF0) << 12) + 0x0300;
			MSM6295SampleData[0][3] = MSM6295ROM + ((nValue & 0xF0) << 12);
			break;

		case 0xE00A: {
			drvZ80Bankswitch(nValue);
			break;
  		}

		case 0xE00C:
			// Once a sound command is processed, it is written to this address
			// printf("z80 wrote %4X -> %2X\n", nAddress, nValue);
			break;

	}
}

static int DrvZ80Init()
{
	ZetInit(1);

	ZetSetReadHandler(battlegZ80Read);
	ZetSetWriteHandler(battlegZ80Write);

	// ROM bank 1
	ZetMapArea    (0x0000, 0x7FFF, 0, RomZ80 + 0x0000); // Direct Read from ROM
	ZetMapArea    (0x0000, 0x7FFF, 2, RomZ80 + 0x0000); // Direct Fetch from ROM
	// ROM bank 2
	ZetMapArea    (0x8000, 0xBFFF, 0, RomZ80 + 0x8000); // Direct Read from ROM
	ZetMapArea    (0x8000, 0xBFFF, 2, RomZ80 + 0x8000); // Direct Fetch from ROM
	// RAM
	ZetMapArea    (0xC000, 0xDFFF, 0, RamZ80);			// Direct Read from RAM
	ZetMapArea    (0xC000, 0xDFFF, 1, RamZ80);			// Direct Write to RAM
	ZetMapArea    (0xC000, 0xDFFF, 2, RamZ80);			//
	// Ports
	ZetMemCallback(0xE000, 0xE0FF, 0);					// Read
	ZetMemCallback(0xE000, 0xE0FF, 1);					// Write

	ZetMemEnd();

	nCurrentBank = 2;

	return 0;
}

unsigned char __fastcall battlegReadByte(unsigned int sekAddress)
{
	switch (sekAddress) {

		case 0x218021:								// The 68K has access to the Z80 RAM
			return RamZ80[0x10];					// Only these addresses are used, however
		case 0x218023:								//
			return RamZ80[0x11];					//

		case 0x21C021:								// Player 1 inputs
			return DrvInput[0];
		case 0x21C025:								// Player 2 inputs
			return DrvInput[1];
		case 0x21C029:								// Other inputs
			return DrvInput[2];
		case 0x21C02D:								// Dipswitch A
			return DrvInput[3];
		case 0x21C031:			   					// Dipswitch B
			return DrvInput[4];
		case 0x21C035:								// Dipswitch C - Territory
			return DrvInput[5];

//		default:
//			printf("Attempt to read byte value of location %x\n", sekAddress);
	}
	return 0;
}

unsigned short __fastcall battlegReadWord(unsigned int sekAddress)
{
	switch (sekAddress) {

		case 0x21C03C:
			return ToaScanlineRegister();

		case 0x300004:
			return ToaGP9001ReadRAM_Hi(0);
		case 0x300006:
			return ToaGP9001ReadRAM_Lo(0);

//		default:
//			printf("Attempt to read word value of location %x\n", sekAddress);
	}
	return 0;
}

void __fastcall battlegWriteByte(unsigned int sekAddress, unsigned char byteValue)
{
	switch (sekAddress) {

		case 0x218021:								// The 68K has access to the Z80 RAM
			RamZ80[0x10] = byteValue;				// Only these addresses are used, however
			break;

		case 0x21C01D:								// Coin control
			break;

		case 0x600001:
			nSoundCommand = byteValue;

			// Trigger Z80 interrupt, and allow the Z80 to process it
			ZetRaiseIrq(255);
			nCyclesDone[1] += ZetRun(0x0200);
			break;

//		default:
//			printf("Attempt to write byte value %x to location %x\n", byteValue, sekAddress);
	}
}

void __fastcall battlegWriteWord(unsigned int sekAddress, unsigned short wordValue)
{
	switch (sekAddress) {

//		static int p;

		case 0x300000:								// Set GP9001 VRAM address-pointer
			ToaGP9001SetRAMPointer(wordValue);
//			p = wordValue & 0x1FFF;
			break;

		case 0x300004:
//			if (p++ >= 0x1800) {
//				static int s;
//				if (s != SekCurrentScanline()) {
//					s = SekCurrentScanline();
//					bprintf(PRINT_NORMAL, _T("  - sprite (%3i).\n"), s);
//				}
//			}
		case 0x300006:
//			p++;
			ToaGP9001WriteRAM(wordValue, 0);
			break;

		case 0x300008:
			ToaGP9001SelectRegister(wordValue);
			break;

		case 0x30000C: {
			ToaGP9001WriteRegister(wordValue);
			break;
		}

//		default:
//			printf("Attempt to write word value %x to location %x\n", wordValue, sekAddress);
	}
}

static int DrvDoReset()
{
	SekOpen(0);
	nIRQPending = 0;
    SekSetIRQLine(0, SEK_IRQSTATUS_NONE);
	SekReset();
	SekClose();

	ZetReset();

	MSM6295Reset(0);
	BurnYM2151Reset();

	return 0;
}

static int battlegInit()
{
	int nLen;

#ifdef DRIVER_ROTATION
	bToaRotateScreen = true;
#endif

	nGP9001ROMSize[0] = 0x800000;

	// Find out how much memory is needed
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) {
		return 1;
	}
	memset(Mem, 0, nLen);										// blank all memory
	MemIndex();													// Index the allocated memory

	// Load the roms into memory
	if (LoadRoms()) {
		return 1;
	}

	{
		SekInit(0, 0x68000);										// Allocate 68000
	    SekOpen(0);

		// Map 68000 memory:
		SekMapMemory(Rom01,			0x000000, 0x0FFFFF, SM_ROM);	// CPU 0 ROM
		SekMapMemory(Ram01,			0x100000, 0x10FFFF, SM_RAM);
		SekMapMemory(RamPal,		0x400000, 0x400FFF, SM_RAM);	// Palette RAM
		SekMapMemory(Ram02,			0x401000, 0x4017FF, SM_RAM);	// Unused
		SekMapMemory(ExtraTRAM,		0x500000, 0x501FFF, SM_RAM);
		SekMapMemory(ExtraTSelect,	0x502000, 0x502FFF, SM_RAM);	// 0x502000 - Scroll; 0x502200 - RAM
		SekMapMemory(ExtraTScroll,	0x503000, 0x503FFF, SM_RAM);	// 0x203000 - Offset; 0x503200 - RAM

		SekSetReadWordHandler(0, battlegReadWord);
		SekSetReadByteHandler(0, battlegReadByte);
		SekSetWriteWordHandler(0, battlegWriteWord);
		SekSetWriteByteHandler(0, battlegWriteByte);

		SekClose();
	}

	nSpriteXOffset = 0x0024;
	nSpriteYOffset = 0x0001;

	nLayer0XOffset = -0x01D6;
	nLayer1XOffset = -0x01D8;
	nLayer2XOffset = -0x01DA;

	ToaInitGP9001();

	nExtraTXOffset = 0x2C;
	ToaExtraTextInit();

	DrvZ80Init();												// Initialize Z80

	BurnYM2151Init(32000000 / 8, 50.0);
	MSM6295Init(0, 32000000 / 16 / 132, 50.0, 1);

	nToaPalLen = nColCount;
	ToaPalSrc = RamPal;
	ToaPalInit();

	bDrawScreen = true;

	// mar 2 1996 & apr 2 1996 ver:	0x0009AC - 0x0009B8 & 0x001F5E - 0x001F64 & 0x003A1C - 0x003A22
	// feb 2 1996 ver:				0x0009AC - 0x0009B8 & 0x001F2E - 0x001F34 & 0x0039EC - 0x0039F2

	nSpeedHackOffset = 0;
	if (strcmp(BurnDrvGetTextA(DRV_NAME), "battlega") == 0) {
		nSpeedHackOffset = 0x30;
	}

#if defined FBA_DEBUG && defined USE_SPEEDHACKS
	bprintf(PRINT_IMPORTANT, _T("  * Using speed-hacks (detecting idle loops).\n"));
#endif

	DrvDoReset();												// Reset machine
	return 0;
}

static int DrvExit()
{
	MSM6295Exit(0);
	BurnYM2151Exit();

	ToaPalExit();
	ToaExitGP9001();
	ToaExtraTextExit();
	ToaZExit();				// Z80 exit
	SekExit();				// Deallocate 68000s

	// Deallocate all used memory
	free(Mem);
	Mem = NULL;

	return 0;
}

static int DrvDraw()
{
	ToaClearScreen();

	if (bDrawScreen) {
		ToaGetBitmap();
		ToaRenderGP9001();					// Render GP9001 graphics
		ToaExtraTextLayer();				// Render extra text layer
	}

	ToaPalUpdate();							// Update the palette

	return 0;
}

inline static int CheckSleep(int)
{
#if 1 && defined USE_SPEEDHACKS
	int nCurrentPC = SekGetPC(-1);

	if (!nIRQPending && nCurrentPC >= 0x0009AC && nCurrentPC <= 0x0009B8) {
		return 1;
	}

	nCurrentPC += nSpeedHackOffset;

	if (!nIRQPending &&
		((nCurrentPC >= 0x001F5E && nCurrentPC <= 0x001F64) ||
		 (nCurrentPC >= 0x003A1C && nCurrentPC <= 0x003A22)))
	{
		return 1;
	}
#endif

	return 0;
}

static int DrvFrame()
{
	int nInterleave = 8;

	if (DrvReset) {														// Reset machine
		DrvDoReset();
	}

	// Compile digital inputs
	DrvInput[0] = 0x00;													// Buttons
	DrvInput[1] = 0x00;													// Player 1
	DrvInput[2] = 0x00;													// Player 2
	for (int i = 0; i < 8; i++) {
		DrvInput[0] |= (DrvJoy1[i] & 1) << i;
		DrvInput[1] |= (DrvJoy2[i] & 1) << i;
		DrvInput[2] |= (DrvButton[i] & 1) << i;
	}
	ToaClearOpposites(&DrvInput[0]);
	ToaClearOpposites(&DrvInput[1]);

	SekNewFrame();

	nCyclesTotal[0] = (int)((long long)16000000 * nBurnCPUSpeedAdjust / (0x0100 * 60));
	nCyclesTotal[1] = TOA_Z80_SPEED / 60;
	nCyclesDone[0] = nCyclesDone[1] = 0;

	SekSetCyclesScanline(nCyclesTotal[0] / 262);
	nToaCyclesDisplayStart = nCyclesTotal[0] - ((nCyclesTotal[0] * (TOA_VBLANK_LINES + 240)) / 262);
	nToaCyclesVBlankStart = nCyclesTotal[0] - ((nCyclesTotal[0] * TOA_VBLANK_LINES) / 262);
	bVBlank = false;

	int nSoundBufferPos = 0;

	SekOpen(0);
	for (int i = 1; i <= nInterleave; i++) {
    	int nCurrentCPU;
		int nNext;

		// Run 68000

		nCurrentCPU = 0;
		nNext = i * nCyclesTotal[nCurrentCPU] / nInterleave;

		// Trigger VBlank interrupt
		if (!bVBlank && nNext > nToaCyclesVBlankStart) {
			if (nCyclesDone[nCurrentCPU] < nToaCyclesVBlankStart) {
				nCyclesSegment = nToaCyclesVBlankStart - nCyclesDone[nCurrentCPU];
				if (!CheckSleep(nCurrentCPU)) {
					nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
				} else {
					nCyclesDone[nCurrentCPU] += SekIdle(nCyclesSegment);
				}
			}

			nIRQPending = 1;
			SekSetIRQLine(4, SEK_IRQSTATUS_AUTO);

			ToaBufferGP9001Sprites();

			if (pBurnDraw) {
				DrvDraw();												// Draw screen if needed
			}

			bVBlank = true;
		}

		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		if (!CheckSleep(nCurrentCPU)) {									// See if this CPU is busywaiting
			nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
			nIRQPending = 0;
		} else {
			nCyclesDone[nCurrentCPU] += SekIdle(nCyclesSegment);
		}

		if ((i & 1) == 0) {
			// Run Z80
			nCurrentCPU = 1;
			nNext = i * nCyclesTotal[nCurrentCPU] / nInterleave;
			nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
			nCyclesDone[nCurrentCPU] += ZetRun(nCyclesSegment);

			// Render sound segment
			if (pBurnSoundOut) {
				int nSegmentLength = (nBurnSoundLen * i / nInterleave) - nSoundBufferPos;
				short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
				BurnYM2151Render(pSoundBuf, nSegmentLength);
				MSM6295Render(0, pSoundBuf, nSegmentLength);
				nSoundBufferPos += nSegmentLength;
			}
		}
	}

	SekClose();

	{
		// Make sure the buffer is entirely filled.
		if (pBurnSoundOut) {
			int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			if (nSegmentLength) {
				BurnYM2151Render(pSoundBuf, nSegmentLength);
				MSM6295Render(0, pSoundBuf, nSegmentLength);
			}
		}
	}

	return 0;
}

struct BurnDriver BurnDrvBattleG = {
	"battleg", NULL, NULL, "1996",
	"Battle Garegga (ver. Tue Apr 2 1996)\0", "Type 2 (China/Denmark region only, round bullets only)", "Raizing / 8ing", "Toaplan GP9001 based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | TOA_ROTATE_GRAPHICS_CCW, 2, HARDWARE_TOAPLAN_RAIZING,
	NULL, battlegRomInfo, battlegRomName, battlegInputInfo, battlegDIPInfo,
	battlegInit, DrvExit, DrvFrame, DrvDraw, DrvScan, &ToaRecalcPalette,
	240, 320, 3, 4
};

struct BurnDriver BurnDrvBattleGA = {
	"battlega", "battleg", NULL, "1996",
	"Battle Garegga (ver. Sat Feb 3 1996)\0", NULL, "Raizing / 8ing", "Toaplan GP9001 based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | TOA_ROTATE_GRAPHICS_CCW, 2, HARDWARE_TOAPLAN_RAIZING,
	NULL, battlegaRomInfo, battlegaRomName, battlegInputInfo, battlegaDIPInfo,
	battlegInit, DrvExit, DrvFrame, DrvDraw, DrvScan, &ToaRecalcPalette,
	240, 320, 3, 4
};

struct BurnDriver BurnDrvBattleGB = {
	"battlegb", "battleg", NULL, "1996",
	"Battle Garegga (ver. Sat Mar 2 1996)\0", "New version (Austria/Hong Kong region only, round bullets only)", "Raizing / 8ing", "Toaplan GP9001 based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | TOA_ROTATE_GRAPHICS_CCW, 2, HARDWARE_TOAPLAN_RAIZING,
	NULL, battlegbRomInfo, battlegbRomName, battlegInputInfo, battlegbDIPInfo,
	battlegInit, DrvExit, DrvFrame, DrvDraw, DrvScan, &ToaRecalcPalette,
	240, 320, 3, 4
};

struct BurnDriver BurnDrvBattleGC = {
	"battlegc", "battleg", NULL, "1996",
	"Battle Garegga (ver. Sat Feb 3 1996)\0", "Austria/Hong Kong region only", "Raizing / 8ing", "Toaplan GP9001 based",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | TOA_ROTATE_GRAPHICS_CCW, 2, HARDWARE_TOAPLAN_RAIZING,
	NULL, battlegcRomInfo, battlegcRomName, battlegInputInfo, battlegbDIPInfo,
	battlegInit, DrvExit, DrvFrame, DrvDraw, DrvScan, &ToaRecalcPalette,
	240, 320, 3, 4
};
