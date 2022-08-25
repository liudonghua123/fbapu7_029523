#include "burnint.h"
#include "driver.h"
extern "C" {
 #include "ay8910.h"
}
unsigned char DrvJoy1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char DrvReset = 0;
static int latch;

static int nCyclesDone[2], nCyclesTotal[2];
static int nCyclesSegment;

static unsigned char *Mem    = NULL;
static unsigned char *MemEnd = NULL;
static unsigned char *RamStart= NULL;
static unsigned char *RamEnd = NULL;
static unsigned char *BjGfx =NULL;
static unsigned char *BjMap =NULL;
static unsigned char *BjRom =NULL;
static unsigned char *BjRam =NULL;
static unsigned char *BjColRam =NULL;
static unsigned char *BjVidRam =NULL;
static unsigned char *BjSprRam =NULL;
// sound cpu
static unsigned char *SndRom =NULL;
static unsigned char *SndRam =NULL;

//graphics tiles
static unsigned char *text=NULL;
static unsigned char *sprites=NULL;
static unsigned char *tiles=NULL;
//pallete
static unsigned char *BjPalSrc=NULL;
static unsigned int *BjPalReal=NULL;

static unsigned char* pTileData;


static short* pFMBuffer;
static short* pAY8910Buffer[9];
// Dip Switch and Input Definitions
static struct BurnInputInfo DrvInputList[] = {
	{"P1 Coin",		0, DrvJoy1 + 0,	"p1 coin"},
	{"P1 Start",	0, DrvJoy1 + 1,	"p1 start"},


	{"P1 Up",		0, DrvJoy1 + 2, 	"p1 up"},
	{"P1 Down",		0, DrvJoy1 + 3, 	"p1 down"},
	{"P1 Left",		0, DrvJoy1 + 4, 	"p1 left"},
	{"P1 Right",	0, DrvJoy1 + 5, 	"p1 right"},
	{"P1 Button 1",	0, DrvJoy1 + 6,		"p1 fire 1"},


	{"Reset",		0, &DrvReset,		"reset"},
/*	{"Diagnostic",	0, DrvButton + 2,	"diag"},
	{"Dip A",		2, DrvInput + 3,	"dip"},
	{"Dip B",		2, DrvInput + 4,	"dip"},
	{"Dip C",		2, DrvInput + 5,	"dip"},
*/};


STDINPUTINFO(Drv);

// Rom information
static struct BurnRomInfo DrvRomDesc[] = {
	{ "09_j01b.bin",    0x2000, 0xc668dc30, BRF_SND },			 //  0 Z80 code
	{ "10_l01b.bin",    0x2000, 0x52a1e5fb, BRF_SND },			 //  1
	{ "11_m01b.bin",    0x2000, 0xb68a062a, BRF_SND },			 //  2
	{ "12_n01b.bin",    0x2000, 0x1d3ecee5, BRF_SND },			 //  3
	{ "13.1r",          0x2000, 0x70e0244d, BRF_SND },			 //  4

  // graphics 3 bit planes:
	{ "03_e08t.bin",    0x1000, 0x9f0470d5, BRF_GRA },			 // chars
	{ "04_h08t.bin",    0x1000, 0x81ec12e6, BRF_GRA },
	{ "05_k08t.bin",    0x1000, 0xe87ec8b1, BRF_GRA },

	{ "14_j07b.bin",    0x2000, 0x101c858d, BRF_GRA },			 // sprites
	{ "15_l07b.bin",    0x2000, 0x013f58f2, BRF_GRA },
	{ "16_m07b.bin",    0x2000, 0x94694097, BRF_GRA },

	{ "06_l08t.bin",    0x2000, 0x51eebd89, BRF_GRA },			 // background tiles
	{ "07_n08t.bin",    0x2000, 0x9dd98e9d, BRF_GRA },
	{ "08_r08t.bin",    0x2000, 0x3155ee7d, BRF_GRA },

	{ "02_p04t.bin",    0x1000, 0x398d4a02, BRF_GRA },			 // background tilemaps

	{ "01_h03t.bin",    0x2000, 0x8407917d, BRF_GRA },			 //Sound CPU
};

STD_ROM_PICK(Drv);
STD_ROM_FN(Drv);


// Rom information
static struct BurnRomInfo Drv1RomDesc[] = {
	{ "09_j01b.bin",    0x2000, 0xc668dc30, BRF_SND },			 //  0 Z80 code
	{ "10_l01b.bin",    0x2000, 0x52a1e5fb, BRF_SND },			 //  1
	{ "11_m01b.bin",    0x2000, 0xb68a062a, BRF_SND },			 //  2
	{ "12_n01b.bin",    0x2000, 0x1d3ecee5, BRF_SND },			 //  3
	{ "13_r01b.bin",    0x2000, 0xbcafdd29, BRF_SND },			 //  4

  // graphics 3 bit planes:
	{ "03_e08t.bin",    0x1000, 0x9f0470d5, BRF_GRA },			 // chars
	{ "04_h08t.bin",    0x1000, 0x81ec12e6, BRF_GRA },
	{ "05_k08t.bin",    0x1000, 0xe87ec8b1, BRF_GRA },

	{ "14_j07b.bin",    0x2000, 0x101c858d, BRF_GRA },			 // sprites
	{ "15_l07b.bin",    0x2000, 0x013f58f2, BRF_GRA },
	{ "16_m07b.bin",    0x2000, 0x94694097, BRF_GRA },

	{ "06_l08t.bin",    0x2000, 0x51eebd89, BRF_GRA },			 // background tiles
	{ "07_n08t.bin",    0x2000, 0x9dd98e9d, BRF_GRA },
	{ "08_r08t.bin",    0x2000, 0x3155ee7d, BRF_GRA },

	{ "02_p04t.bin",    0x1000, 0x398d4a02, BRF_GRA },			 // background tilemaps

	{ "01_h03t.bin",    0x2000, 0x8407917d, BRF_GRA },			 //Sound CPU
};

STD_ROM_PICK(Drv1);
STD_ROM_FN(Drv1);


unsigned char __fastcall BjMemRead(unsigned short addr)
{
	unsigned char inputs=0;

	if (addr==0xb000) {
 		if (DrvJoy1[5])
 			inputs|=0x01;
 		if (DrvJoy1[4])
 			inputs|=0x02;
 		if (DrvJoy1[2])
 			inputs|=0x04;
 		if (DrvJoy1[3])
 			inputs|=0x08;
 		if (DrvJoy1[6])
 			inputs|=0x10;
 		return inputs;
 	}
 	if (addr==0xb002) {
         if (DrvJoy1[0])
 			inputs|=0x01;
         if (DrvJoy1[1])
 			inputs|=0x04;
 		return inputs;
 	}
	return 0;
}

void __fastcall BjMemWrite(unsigned short addr,unsigned char val)
{
	if(addr==0xb800)
	{
		latch=val;
		return;
	}
	BjRam[addr]=val;
}

unsigned char __fastcall SndMemRead(unsigned short a)
{
	if(a==0x6000)
	{
	int res;
	res = latch;
	latch = 0;
	return res;
	}
	return 0;
}



void __fastcall SndPortWrite(unsigned short a, unsigned char d)
{
	a &= 0xff;
	switch (a) {
		case 0x00: {
			AY8910Write(0, 0, d);
			return;
		}
		case 0x01: {
			AY8910Write(0, 1, d);
			return;
		}
		case 0x10: {
			AY8910Write(1, 0, d);
			return;
		}
		case 0x11: {
			AY8910Write(1, 1, d);
			return;
		}
		case 0x80: {
			AY8910Write(2, 0, d);
			return;
		}
		case 0x81: {
			AY8910Write(2, 1, d);
			return;
		}
	}
}

int BjZInit()
{
    // Init the z80
	ZetInit(2);
	// Main CPU setup
	ZetOpen(0);

	ZetMapArea    (0x0000,0x7fff,0,BjRom+0x0000); // Direct Read from ROM
	ZetMapArea    (0x0000,0x7fff,2,BjRom+0x0000); // Direct Fetch from ROM
	ZetMapArea    (0xc000,0xdfff,0,BjRom+0x8000); // Direct Read from ROM
	ZetMapArea    (0xc000,0xdfff,2,BjRom+0x8000); // Direct Fetch from ROM

	ZetMapArea    (0x8000,0x8fff,0,BjRam+0x8000);
	ZetMapArea    (0x8000,0x8fff,1,BjRam+0x8000);

	ZetMapArea    (0x9000,0x93ff,0,BjVidRam);
	ZetMapArea    (0x9000,0x93ff,1,BjVidRam);

	ZetMapArea    (0x9400,0x97ff,0,BjColRam);
	ZetMapArea    (0x9400,0x97ff,1,BjColRam);

	ZetMapArea    (0x9820,0x987f,0,BjSprRam);
	ZetMapArea    (0x9820,0x987f,1,BjSprRam);

	ZetMapArea    (0x9c00,0x9cff,0,BjPalSrc);
	ZetMapArea    (0x9c00,0x9cff,1,BjPalSrc);

	ZetMapArea    (0x9e00,0x9e00,0,BjRam+0x9e00);
	ZetMapArea    (0x9e00,0x9e00,1,BjRam+0x9e00);

	ZetMapArea    (0xb000,0xb000,0,BjRam+0xb000);
	ZetMapArea    (0xb000,0xb000,1,BjRam+0xb000);

//	ZetMapArea    (0xb800,0xb800,0,BjRam+0xb800);
//	ZetMapArea    (0xb800,0xb800,1,BjRam+0xb800);

	ZetSetReadHandler(BjMemRead);
	ZetSetWriteHandler(BjMemWrite);
	ZetMemEnd();
	ZetClose();

	ZetOpen(1);
	ZetMapArea    (0x0000,0x1fff,0,SndRom); // Direct Read from ROM
	ZetMapArea    (0x0000,0x1fff,2,SndRom); // Direct Fetch from ROM
	ZetMapArea    (0x4000,0x43ff,0,SndRam);
	ZetMapArea    (0x4000,0x43ff,1,SndRam);
	ZetMapArea    (0x4000,0x43ff,2,SndRam); // fetch from ram?
//	ZetMapArea    (0x6000,0x6000,0,BjRam+0xb800);
//	ZetMapArea    (0x6000,0x6000,1,BjRam+0xb800);
	ZetSetReadHandler(SndMemRead);
	ZetSetOutHandler(SndPortWrite);
	ZetMemEnd();
	ZetClose();

	pAY8910Buffer[0] = pFMBuffer + nBurnSoundLen * 0;
	pAY8910Buffer[1] = pFMBuffer + nBurnSoundLen * 1;
	pAY8910Buffer[2] = pFMBuffer + nBurnSoundLen * 2;
	pAY8910Buffer[3] = pFMBuffer + nBurnSoundLen * 3;
	pAY8910Buffer[4] = pFMBuffer + nBurnSoundLen * 4;
	pAY8910Buffer[5] = pFMBuffer + nBurnSoundLen * 5;
	pAY8910Buffer[6] = pFMBuffer + nBurnSoundLen * 6;
	pAY8910Buffer[7] = pFMBuffer + nBurnSoundLen * 7;
	pAY8910Buffer[8] = pFMBuffer + nBurnSoundLen * 8;

	AY8910Init(0, 1500000, nBurnSoundRate, NULL, NULL, NULL, NULL);
	AY8910Init(1, 1500000, nBurnSoundRate, NULL, NULL, NULL, NULL);
	AY8910Init(2, 1500000, nBurnSoundRate, NULL, NULL, NULL, NULL);

    // remember to do ZetReset() in main driver
     return 0;
}

int BjZExit()
{
	ZetExit();
	return 0;
}


static int DrvDoReset()
{
	ZetOpen(0);
	ZetReset();
	ZetClose();
	ZetOpen(1);
	ZetReset();
	ZetClose();
	return 0;
}

void DecodeTiles(unsigned char *TilePointer, int num,int off1,int off2, int off3)
{
      int c,y,x,dat1,dat2,dat3,col;
      for (c=0;c<num;c++)
      {
            for (y=0;y<8;y++)
            {
            dat1=BjGfx[off1 + (c * 8) + y];
            dat2=BjGfx[off2 + (c * 8) + y];
            dat3=BjGfx[off3 + (c * 8) + y];
			for (x=0;x<8;x++)
                  {
 				  col=0;
				  if (dat1&1){ col |= 4;}
                  if (dat2&1){ col |= 2;}
                  if (dat3&1){ col |= 1;}
                  TilePointer[(c * 64) + ((7-x) * 8) + (7 - y)]=col;
                  dat1>>=1;
                  dat2>>=1;
                  dat3>>=1;
                  }
            }
      }
}


static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	BjRom		= Next; Next += (0x2000*5);
	SndRom		= Next; Next += 0x2000;
	RamStart	= Next;
	BjRam		= Next; Next += 0xffff;
	SndRam		= Next; Next += 0x400;
	BjMap		= Next; Next += 0x1000;
	BjGfx		= Next; Next += 0x15000;
	BjPalSrc	= Next; Next += 0x00200;
	BjVidRam =Next; Next +=0x400;
	BjColRam =Next;Next += 0x400;
	BjSprRam =Next;Next +=0x100;
	pFMBuffer	= (short*)Next; Next += nBurnSoundLen * 9 * sizeof(short);
	RamEnd		= Next;
	BjPalReal	= (unsigned int*)Next; Next += 0x00100 * sizeof(unsigned int);
	text		=Next; Next+=0x8000;
	sprites		=Next; Next+=0x10000;
	tiles		=Next; Next+=0x10000;
	MemEnd		= Next;

	return 0;
}


int BjInit()
{
	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	int nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();

	for (int i =0; i<5 ; i++)
	{
		BurnLoadRom(BjRom+(0x2000*i),i,1); // load code roms
	}

	for (int i=0;i<3;i++)
	{
		BurnLoadRom(BjGfx+(0x1000*i),i+5,1);
	}

//	for (int i=0;i<5;i++)
//	{
//		BurnLoadRom(BjGfx+0x3000+(0x2000*i),i+8,1);
//	}

	BurnLoadRom(BjGfx+0x3000,8,1);
	BurnLoadRom(BjGfx+0x5000,9,1);
	BurnLoadRom(BjGfx+0x7000,10,1);

	BurnLoadRom(BjGfx+0x9000,11,1);
	BurnLoadRom(BjGfx+0xB000,12,1);
	BurnLoadRom(BjGfx+0xD000,13,1);

	BurnLoadRom(BjMap,14,1); // load Background tile maps
	BurnLoadRom(SndRom,15,1); // load Background tile maps

// Set memory access & Init
    BjZInit();
	DrvDoReset();
    DecodeTiles(text,512,0,0x1000,0x2000);
    DecodeTiles(sprites,1024,0x7000,0x5000,0x3000);
    DecodeTiles(tiles,1024,0x9000,0xB000,0xD000);
// done
	BurnTransferInit();
	return 0;
}

int BjExit()
{
	for (int i = 0; i < 3; i++) {
		AY8910Exit(i);
	}
	free(Mem);
	BurnTransferExit();
	BjZExit();
	return 0;
}

static unsigned int CalcCol(unsigned short nColour)
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

int CalcAll()
{
	for (int i = 0; i < 0x100; i++) {
		BjPalReal[i / 2] = CalcCol(BjPalSrc[i & ~1] | (BjPalSrc[i | 1] << 8));
	}

	return 0;
}

#define PLOTPIXEL(x) if (pTileData[x]) {pPixel[x] = nPalette | pTileData[x];}
void BombJackDrawItem(int nTileNumber, int startx, int starty,int nTilePalette,unsigned char *TilePointer)
{
	unsigned char nPalette = nTilePalette << 3;
	pTileData = TilePointer + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (starty<<8)+startx;

	for (int y = 0; y < 8; y++, pPixel += 256, pTileData += 8) {
		PLOTPIXEL(0);
		PLOTPIXEL(1);
		PLOTPIXEL(2);
		PLOTPIXEL(3);
		PLOTPIXEL(4);
		PLOTPIXEL(5);
		PLOTPIXEL(6);
		PLOTPIXEL(7);
	}
}
#define PLOTPIXEL_fx(a,x) if (pTileData[x]) {pPixel[a] = nPalette | pTileData[x];}

void BombJackDrawItem_flipx(int nTileNumber, int startx, int starty,int nTilePalette,unsigned char *TilePointer)
{
	unsigned char nPalette = nTilePalette << 3;
	pTileData = TilePointer + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + (starty<<8)+startx;

	for (int y = 0; y < 8; y++, pPixel += 256, pTileData += 8) {
		PLOTPIXEL_fx(7,0);
		PLOTPIXEL_fx(6,1);
		PLOTPIXEL_fx(5,2);
		PLOTPIXEL_fx(4,3);
		PLOTPIXEL_fx(3,4);
		PLOTPIXEL_fx(2,5);
		PLOTPIXEL_fx(1,6);
		PLOTPIXEL_fx(0,7);
	}
}

void BombJackDrawItem_flipy(int nTileNumber, int startx, int starty,int nTilePalette,unsigned char *TilePointer)
{
	unsigned char nPalette = nTilePalette << 3;
	pTileData = TilePointer + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((starty+8)<<8)+startx;

	for (int y = 8; y > 0; y--, pPixel -= 256, pTileData += 8) {
		PLOTPIXEL(0);
		PLOTPIXEL(1);
		PLOTPIXEL(2);
		PLOTPIXEL(3);
		PLOTPIXEL(4);
		PLOTPIXEL(5);
		PLOTPIXEL(6);
		PLOTPIXEL(7);
	}
}


void BombJackDrawItem_flipxy(int nTileNumber, int startx, int starty,int nTilePalette,unsigned char *TilePointer)
{
	unsigned char nPalette = nTilePalette << 3;
	TilePointer = TilePointer + (nTileNumber << 6);

	unsigned short* pPixel = pTransDraw + ((starty+8)<<8)+startx;

	for (int y = 8; y > 0; y--, pPixel -= 256, pTileData += 8) {
		PLOTPIXEL_fx(7,0);
		PLOTPIXEL_fx(6,1);
		PLOTPIXEL_fx(5,2);
		PLOTPIXEL_fx(4,3);
		PLOTPIXEL_fx(3,4);
		PLOTPIXEL_fx(2,5);
		PLOTPIXEL_fx(1,6);
		PLOTPIXEL_fx(0,7);
	}
}

static int BjDraw()
{
	int x,y;
	int c;
	int tile;
	int colour;
	int BgSel=BjRam[0x9e00];
	int pos=0,pos2=0,pos3=0x200*(BgSel&7),pos4;
	pos4=pos3+0x100;
	int attrib;
	if (BgSel&0x10)
	{
		for (x=15;x>-1;x--)
		{
			for (y=0;y<16;y++)
			{
				attrib=BjMap[pos4];
				if (attrib&0x80)
				{
					BombJackDrawItem_flipx((BjMap[pos3]<<2),(x<<4)+8,(y<<4),attrib,tiles);
					BombJackDrawItem_flipx((BjMap[pos3]<<2)+1,(x<<4)+8,(y<<4)+8,attrib,tiles);
					BombJackDrawItem_flipx((BjMap[pos3]<<2)+2,(x<<4),(y<<4),attrib,tiles);
					BombJackDrawItem_flipx((BjMap[pos3]<<2)+3,(x<<4),(y<<4)+8,attrib,tiles);
				}
				else
				{
					BombJackDrawItem((BjMap[pos3]<<2),(x<<4)+8,(y<<4),attrib,tiles);
					BombJackDrawItem((BjMap[pos3]<<2)+1,(x<<4)+8,(y<<4)+8,attrib,tiles);
					BombJackDrawItem((BjMap[pos3]<<2)+2,(x<<4),(y<<4),attrib,tiles);
					BombJackDrawItem((BjMap[pos3]<<2)+3,(x<<4),(y<<4)+8,attrib,tiles);
				}
				pos3++;
				pos4++;
			}
		}
	}
	for (x=0;x<32;x++)
	{
		for (y=0;y<32;y++)
		{
			if (BgSel&0x10)
			{
				if (BjColRam[pos2]&0x10)
				BombJackDrawItem(BjVidRam[pos++]+256,(31-x)<<3,y<<3,BjColRam[pos2++]&15,text);
				else
				BombJackDrawItem(BjVidRam[pos++],(31-x)<<3,y<<3,BjColRam[pos2++]&15,text);
			}
			else
			{
				if (BjColRam[pos2]&0x10)
				BombJackDrawItem(BjVidRam[pos++]+256,(31-x)<<3,y<<3,BjColRam[pos2++]&15,text);
				else
				BombJackDrawItem(BjVidRam[pos++],(31-x)<<3,y<<3,BjColRam[pos2++]&15,text);
			}
		}
	}
	pos=0;
	for (c=0;c<24;c++)
	{
	//	flipx = spriteram[offs+1] & 0x40;
	//	flipy =	spriteram[offs+1] & 0x80;
		x=BjSprRam[pos+2]-1;
		y=BjSprRam[pos+3];
		if (x>8&&y>8)
		{
			tile=BjSprRam[pos]&0x7F;
			colour=BjSprRam[pos+1]&0x0F;
			attrib=BjSprRam[pos+1]&0xc0;

			switch (attrib){
			case 0:
				if (!(BjSprRam[pos]&0x80))
				{
					BombJackDrawItem((tile<<2), x+8,y,colour,sprites);
					BombJackDrawItem((tile<<2)+1, x+8,y+8,colour,sprites);
					BombJackDrawItem((tile<<2)+2, x,y,colour,sprites);
					BombJackDrawItem((tile<<2)+3, x,y+8,colour,sprites);

				}
				else
				{
					tile&=31;
					BombJackDrawItem((tile<<4)+512,x+8+16,y,colour,sprites);
					BombJackDrawItem((tile<<4)+513,x+8+16,y+8,colour,sprites);
					BombJackDrawItem((tile<<4)+514,x+16,y,colour,sprites);
					BombJackDrawItem((tile<<4)+515,x+16,y+8,colour,sprites);
					BombJackDrawItem((tile<<4)+516,x+8+16,y+16,colour,sprites);
					BombJackDrawItem((tile<<4)+517,x+8+16,y+8+16,colour,sprites);
					BombJackDrawItem((tile<<4)+518,x+16,y+16,colour,sprites);
					BombJackDrawItem((tile<<4)+519,x+16,y+8+16,colour,sprites);
					BombJackDrawItem((tile<<4)+520,x+8,y,colour,sprites);
					BombJackDrawItem((tile<<4)+521,x+8,y+8,colour,sprites);
					BombJackDrawItem((tile<<4)+522,x,y,colour,sprites);
					BombJackDrawItem((tile<<4)+523,x,y+8,colour,sprites);
					BombJackDrawItem((tile<<4)+524,x+8,y+16,colour,sprites);
					BombJackDrawItem((tile<<4)+525,x+8,y+8+16,colour,sprites);
					BombJackDrawItem((tile<<4)+526,x,y+16,colour,sprites);
					BombJackDrawItem((tile<<4)+527,x,y+8+16,colour,sprites);
				}
			 break;
			case 0x80:
				if (!(BjSprRam[pos]&0x80))
				{
					BombJackDrawItem_flipx((tile<<2)+2, x+8,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<2)+3, x+8,y+8,colour,sprites);
					BombJackDrawItem_flipx((tile<<2), x,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<2)+1, x,y+8,colour,sprites);

				}
				else
				{
					tile&=31;
					BombJackDrawItem_flipx((tile<<4)+512,x+8+16,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+513,x+8+16,y+8,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+514,x+16,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+515,x+16,y+8,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+516,x+8+16,y+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+517,x+8+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+518,x+16,y+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+519,x+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+520,x+8,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+521,x+8,y+8,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+522,x,y,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+523,x,y+8,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+524,x+8,y+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+525,x+8,y+8+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+526,x,y+16,colour,sprites);
					BombJackDrawItem_flipx((tile<<4)+527,x,y+8+16,colour,sprites);
				}
				break;
	case 0x40:
				if (!(BjSprRam[pos]&0x80))
				{
					BombJackDrawItem_flipy((tile<<2)+1, x+8,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<2), x+8,y+8,colour,sprites);
					BombJackDrawItem_flipy((tile<<2)+3, x,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<2)+2, x,y+8,colour,sprites);
				}
				else
				{
					tile&=31;
					BombJackDrawItem_flipy((tile<<4)+512,x+8+16,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+513,x+8+16,y+8,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+514,x+16,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+515,x+16,y+8,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+516,x+8+16,y+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+517,x+8+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+518,x+16,y+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+519,x+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+520,x+8,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+521,x+8,y+8,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+522,x,y,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+523,x,y+8,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+524,x+8,y+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+525,x+8,y+8+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+526,x,y+16,colour,sprites);
					BombJackDrawItem_flipy((tile<<4)+527,x,y+8+16,colour,sprites);
				}
				break;
			case 0xc0:
				if (!(BjSprRam[pos]&0x80))
				{
					BombJackDrawItem_flipxy((tile<<2)+3, x+8,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<2)+2, x+8,y+8,colour,sprites);
					BombJackDrawItem_flipxy((tile<<2)+1, x,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<2), x,y+8,colour,sprites);
				}
				else
				{
					tile&=31;
					BombJackDrawItem_flipxy((tile<<4)+512,x+8+16,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+513,x+8+16,y+8,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+514,x+16,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+515,x+16,y+8,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+516,x+8+16,y+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+517,x+8+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+518,x+16,y+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+519,x+16,y+8+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+520,x+8,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+521,x+8,y+8,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+522,x,y,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+523,x,y+8,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+524,x+8,y+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+525,x+8,y+8+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+526,x,y+16,colour,sprites);
					BombJackDrawItem_flipxy((tile<<4)+527,x,y+8+16,colour,sprites);
				}
				break;
			default:
				bprintf(PRINT_NORMAL, PRINT_NORMAL, PRINT_NORMAL, "attrib %x\n",attrib);
				break;
			}
		}
		pos+=4;
	}
	return 0;
}
// end

int BjFrame()
{
	int nInterleave = 10;
	int nSoundBufferPos = 0;

	nCyclesTotal[0] = 4000000 / 60;
	nCyclesTotal[1] = 3072000 / 60;
	nCyclesDone[0] = nCyclesDone[1] = 0;

	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run Z80 #1
		nCurrentCPU = 0;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesDone[nCurrentCPU] += ZetRun(nCyclesSegment);
		ZetClose();

		// Run Z80 #2
		nCurrentCPU = 1;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;
		ZetClose();

		// Render Sound Segment
		if (pBurnSoundOut) {
			int nSample;
			int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
			short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
			AY8910Update(0, &pAY8910Buffer[0], nSegmentLength);
			AY8910Update(1, &pAY8910Buffer[3], nSegmentLength);
			AY8910Update(2, &pAY8910Buffer[6], nSegmentLength);
			for (int n = 0; n < nSegmentLength; n++) {
				nSample  = pAY8910Buffer[0][n];
				nSample += pAY8910Buffer[1][n];
				nSample += pAY8910Buffer[2][n];
				nSample += pAY8910Buffer[3][n];
				nSample += pAY8910Buffer[4][n];
				nSample += pAY8910Buffer[5][n];
				nSample += pAY8910Buffer[6][n];
				nSample += pAY8910Buffer[7][n];
				nSample += pAY8910Buffer[8][n];

				nSample /= 4;

				if (nSample < -32768) {
					nSample = -32768;
				} else {
					if (nSample > 32767) {
						nSample = 32767;
					}
				}

				pSoundBuf[(n << 1) + 0] = nSample;
				pSoundBuf[(n << 1) + 1] = nSample;
    			}
				nSoundBufferPos += nSegmentLength;
		}
	}

	// Make sure the buffer is entirely filled.
	if (pBurnSoundOut) {
		int nSample;
		int nSegmentLength = nBurnSoundLen - nSoundBufferPos;
		short* pSoundBuf = pBurnSoundOut + (nSoundBufferPos << 1);
		if (nSegmentLength) {
			AY8910Update(0, &pAY8910Buffer[0], nSegmentLength);
			AY8910Update(1, &pAY8910Buffer[3], nSegmentLength);
			AY8910Update(2, &pAY8910Buffer[6], nSegmentLength);
			for (int n = 0; n < nSegmentLength; n++) {
				nSample  = pAY8910Buffer[0][n];
				nSample += pAY8910Buffer[1][n];
				nSample += pAY8910Buffer[2][n];
				nSample += pAY8910Buffer[3][n];
				nSample += pAY8910Buffer[4][n];
				nSample += pAY8910Buffer[5][n];
				nSample += pAY8910Buffer[6][n];
				nSample += pAY8910Buffer[7][n];
				nSample += pAY8910Buffer[8][n];

				nSample /= 4;

				if (nSample < -32768) {
					nSample = -32768;
				} else {
					if (nSample > 32767) {
						nSample = 32767;
					}
				}

				pSoundBuf[(n << 1) + 0] = nSample;
				pSoundBuf[(n << 1) + 1] = nSample;
 			}
		}
	}
	ZetOpen(0);
	if (BjRam[0xb000])
   		ZetNmi();
	ZetClose();
	ZetOpen(1);
	ZetNmi();
	ZetClose();


	if (pBurnDraw != NULL)
	{
		BurnTransferClear();
		CalcAll();
		BjDraw();	// Draw screen if needed
		BurnTransferCopy(BjPalReal);
	}
	return 0;
}

int BjScan(int /*nAction*/,int * /*pnMin*/)
{
	return 0;
}

struct BurnDriver BurnDrvBombjack = {
	"bombjack", NULL, NULL, "1984",
	"Bomb Jack (set 1)\0", NULL, "Tehkan", "Bomb Jack Hardware",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_MISC,
	NULL,DrvRomInfo,DrvRomName,DrvInputInfo,NULL,
	BjInit,BjExit,BjFrame,NULL,BjScan,
	NULL,256,256,3,4
};

struct BurnDriver BurnDrvbombjac2 = {
	"bombjac2", "bombjack", NULL, "1984",
	"Bomb Jack (set 2)\0", NULL, "Tehkan", "Bomb Jack Hardware",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE,2,HARDWARE_MISC_MISC,
	NULL,Drv1RomInfo,Drv1RomName,DrvInputInfo,NULL,
	BjInit,BjExit,BjFrame,NULL,BjScan,
	NULL,256,256,3,4
};
