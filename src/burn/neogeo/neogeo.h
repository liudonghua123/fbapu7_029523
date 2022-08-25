#include "burnint.h"
#include "bitswap.h"

// Uncomment the following line to mnake the display the full 320 pixels wide
// #define NEO_DISPLAY_OVERSCAN

#ifdef NEO_DISPLAY_OVERSCAN
 const int nNeoScreenWidth = 320;
#else
 const int nNeoScreenWidth = 304;
#endif

struct NeoGameInfo {
	int nCodeOffset; int nCodeNum;
	int nTextOffset;
	int nSpriteOffset; int nSpriteNum;
	int nSoundOffset;
	int nADPCMOffset; int nADPCMANum; int nADPCMBNum;
};

// neogeo.cpp
// ---------------------------------------------------------------------------------------
void NeoClearScreen();
int NeoLoadCode(int nOffset, int nNum, unsigned char* pDest);
void NeoInterleaveCode32WORDSWAP(unsigned char* pDest);
int NeoLoadSprites(int nOffset, int nNum, unsigned char* pDest, unsigned int nSpriteSize);
int NeoLoadADPCM(int nOffset, int nNum, unsigned char* pDest);

void NeoDecodeSprites(unsigned char* pDest, int nSize);
void NeoDecodeText(unsigned char* pDest, int nSize);


// romsave.cpp
// ---------------------------------------------------------------------------------------
extern int bsavedecryptedcs;
extern int bsavedecryptedps;
extern int bsavedecrypteds1;
extern int bsavedecryptedvs;

extern void savedecCROMs();
extern void savedecPROMs();
extern void savedecSROM();
extern void savedecVROMs(int nNumber);


// neo_run.cpp
// ---------------------------------------------------------------------------------------
extern int nNeoSMASNKProtection;
extern int nNeoPCM2SNKProtection;
extern int nNeoPCM2PLAYMOREProtection;
extern int nNeoPVCPLAYMOREProtection;
extern int nNeoTextROMFixType;
extern int nNeoBootlegSoundProtection;

extern unsigned char* NeoGraphicsRAM;

extern unsigned char nNeoNumSlots;

extern unsigned char NeoButton1[];
extern unsigned char NeoButton2[];
extern unsigned char NeoButton3[];
extern unsigned char NeoButton4[];
extern unsigned char NeoJoy1[];
extern unsigned char NeoJoy2[];
extern unsigned char NeoJoy3[];
extern unsigned char NeoJoy4[];
extern unsigned short NeoAxis[];
extern unsigned char NeoInput[];
extern unsigned char NeoDiag[];
extern unsigned char NeoDebugDip[];
extern unsigned char NeoReset, NeoSystem;

extern unsigned char *Neo68KROM, *YM2610ADPCMAROM;
extern unsigned int nNeo68KROMBank;
extern int nYM2610ADPCMASize;

extern void (*pNeoInitCallback)();
extern void (*pNeoBankswitchCallback)();
extern int (*pNeoScanCallback)(int, int*);
extern void (*pNeoBIOSCallback)();
extern void (*pNeoProtectionCallback)();

extern bool bNeoEnableGraphics;

int NeoInit();
int NeoExit();
int NeoScan(int nAction, int* pnMin);
int NeoRender();
int NeoFrame();


// neo_palette.cpp
// ---------------------------------------------------------------------------------------
extern unsigned char* NeoPalSrc[2];
extern int nNeoPaletteBank;
extern unsigned int* NeoPalette;

extern unsigned char NeoRecalcPalette;

int NeoInitPalette();
void NeoExitPalette();
int NeoUpdatePalette();
void NeoSetPalette();

void __fastcall NeoPalWriteByte(unsigned int nAddress, unsigned char byteValue);
void __fastcall NeoPalWriteWord(unsigned int nAddress, unsigned short wordValue);


// neo_text.cpp
// ---------------------------------------------------------------------------------------
extern unsigned char* NeoTextROM;
extern int nNeoTextROMSize;
extern bool bBIOSTextROMEnabled;

int NeoInitText();
void NeoExitText();
int NeoRenderText();

// for kof10th text handling
void NeoUpdateTextOne(int nOffset, const unsigned char byteValue);


// neo_sprite.cpp
// ---------------------------------------------------------------------------------------
extern unsigned char* NeoSpriteROM;
extern unsigned char* NeoZoomROM;

extern int nNeoSpriteFrame;
extern unsigned int nNeoTileMask;
extern int nNeoMaxTile;

extern int nSliceStart, nSliceEnd, nSliceSize;

int NeoInitSprites();
void NeoExitSprites();
int NeoRenderSprites();


// neo_decrypt.cpp
// ---------------------------------------------------------------------------------------
extern unsigned char nNeoProtectionXor;

void NeoGfxDecryptCMC42Init();
void NeoGfxDecryptCMC50Init();
void NeoGfxDecryptDoBlock(int extra_xor, unsigned char* buf, int offset, int block_size, int rom_size);
void NeoExtractSData(unsigned char* rom, unsigned char* sdata, int rom_size, int sdata_size);

// Extra handling for PCB encrypted C-ROMs
void ms5pcb_cx_decrypt(unsigned char* rom);
void kf2k3pcb_cx_decrypt(unsigned char* rom);

// Decryption routines for 68K ROMs
extern void kof98Decrypt();
extern void Neo_SMA_SNK_1999(int nValue);
extern void kof2002Decrypt();
extern void samsho5Decrypt();
extern void samsh5spDecrypt();
extern void Neo_PVC_PLAYMORE_2003(int nValue);

// Decryption for kf2k3pcb BIOS
void kf2k3pcbBIOSDecrypt();

// Decryption for Sound ROMs
void Neo_PCM2_SNK_1999(int nValue);
void Neo_PCM2_PLAYMORE_2002(int nValue);


// neo_prot.cpp
// ---------------------------------------------------------------------------------------
// Unknown protection devices
extern void fatfury2ProtectionInstall();
extern void kof98ProtectionInstall();
extern void mslugxProtectionInstall();

// SMA Protection
void __fastcall kof99WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue);
void __fastcall garouWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue);
void __fastcall garouoWriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue);
void __fastcall mslug3WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue);
void __fastcall kof2000WriteWordBankswitch(unsigned int sekAddress, unsigned short wordValue);
int NeoSMAInit(int nSMADecrypt, pSekWriteWordHandler pBankswitchHandler, unsigned int nRNGAddress0, unsigned int nRNGAddress1);
int NeoSMAExit();

// PVC Protection
extern unsigned short CartRAM[0x1000];
extern void PVCProtectionInstall();
extern void NeoPVCBankswitch();
int NeoPVCInit(int nGameInit, void(*pBIOSCallBack)(),int nPCM2Value, int nTextDecValue);


// neo_boot.cpp
// ---------------------------------------------------------------------------------------
// General bootleg decryption routines
extern void DoPerm(int nGame);
extern void neo_boot_text_decrypt(int nGame);
extern void neo_boot_sound_decrypt(int nGame);

// KOF 96 Plus
extern void kof96plsDecrypt();

// KOG
extern void kogDecrypt();
extern void kogProtectionInstall();

// Lansquenet 2004
extern void lans2004Decrypt();

// CTHD 2003 + clones
extern void cthd2003Decrypt();
extern void cthd2003ProtectionInstall();
extern void cthd2003MapBank();
extern void cthd2k3aDecrypt();

// KOF 2002 Plus + clones
extern void kof2k2blDecrypt();
extern void PLUSDecryptP();
extern void kf2k2plsDecrypt();
extern void kf2k2mpDecrypt();
extern void kf2k2mp2Decrypt();
extern void kf2k4speDecrypt();
extern void kf2k4splDecrypt();

// KOF 10th + clones
extern void kof10thDecrypt();
extern void kof10thProtectionInstall();
int kof10thScan(int nAction, int* /*pnMin*/);
extern void kof10thMapBank();
extern void kf10thepDecrypt();
extern void kof10thuDecrypt();
extern void kf2k5uniDecrypt();

// Matrimbl
extern void matrimblDecrypt();

// ms5boot + clones
extern void ms5bootProtectionInstall();
extern void ms5plusProtectionInstall();

// ms6boot
extern void ms6bootDecrypt();

// svcboot + clones
extern void svcbootDecrypt();
extern void svcplusDecrypt();
extern void svcplusaDecrypt();
extern void svcsplusDecrypt();

// samsh5bl
extern void samsh5blDecrypt();

// kf2k3bl + clones
extern void kf2k3blDecrypt();
extern void kf2k3blProtectionInstall();
extern void kf2k3blaDecrypt();
extern void kf2k3blaBankswitch();
extern void kf2k3blaProtectionInstall();
extern void kf2k4uplDecrypt();

// fr2ch
extern void fr2chCallback();


// neo_upd4990a.cpp
// ---------------------------------------------------------------------------------------
void uPD4990AExit();
void uPD499ASetTicks(unsigned int nTicksPerSecond);
int uPD4990AInit(unsigned int nTicksPerSecond);
void uPD4990AScan(int nAction, int* pnMin);
void uPD4990AUpdate(unsigned int nTicks);
void uPD4990AWrite(unsigned char CLK, unsigned char STB, unsigned char DATA);
unsigned char uPD4990ARead(unsigned int nTicks);
