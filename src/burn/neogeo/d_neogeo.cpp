// FB Alpha Neo Geo driver module

#include "neogeo.h"

// To do:
//	King of Fighters 10th Anniversary
//		- P1 bankswitch is still not 100% correct.
//		  a. The moves do not change as you lose.
//	V-liner 
//		- Sound
//		  a. How does FBA handles the timer_16_r function
//	Metal Slug X
//		- P1 protection
//		  a. What exactly does the Altera chip do?

static struct BurnRomInfo emptyRomDesc[] = {
	{ "", 0, 0, 0 },
};

// -----------------------------------------------------------------------------
// Common data

static struct BurnInputInfo neogeoInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
//	{"P1 Coin 2",	BIT_DIGITAL,	NeoButton2 + 3,	"p1 coin 2"},
	{"P1 Start",	BIT_DIGITAL,	NeoButton1 + 0,	"p1 start"},		//  1
	{"P1 Select",	BIT_DIGITAL,	NeoButton1 + 1,	"p1 select"},		//  2

	{"P1 Up",	BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"P1 Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"P1 Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"P1 Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"P1 Button A",	BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"P1 Button C",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"P1 Button D",	BIT_DIGITAL,	NeoJoy1 + 7,	"p1 fire 4"},		//  A

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		//  B
//	{"P2 Coin 2",	BIT_DIGITAL,	NeoButton2 + 4,	"p2 coin 2"},
	{"P2 Start",	BIT_DIGITAL,	NeoButton1 + 2,	"p2 start"},		//  C
	{"P2 Select",	BIT_DIGITAL,	NeoButton1 + 3,	"p2 select"},		//  D

	{"P2 Up",	BIT_DIGITAL,	NeoJoy2 + 0,	"p2 up"},		//  E
	{"P2 Down",	BIT_DIGITAL,	NeoJoy2 + 1,	"p2 down"},		//  F
	{"P2 Left",	BIT_DIGITAL,	NeoJoy2 + 2,	"p2 left"},		// 10
	{"P2 Right",	BIT_DIGITAL,	NeoJoy2 + 3,	"p2 right"},		// 11
	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"p2 fire 1"},		// 12
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"p2 fire 2"},		// 13
	{"P2 Button C",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 3"},		// 14
	{"P2 Button D",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 4"},		// 15

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 16
	{"Test",	BIT_DIGITAL,	NeoDiag + 0,	"diag"},		// 17
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 18
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 19
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 1A

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 1B
	{"Slots",	BIT_DIPSWITCH,	&nNeoNumSlots,	"dip"},			// 1C

	{"Debug Dip 1",	BIT_DIPSWITCH,	NeoDebugDip + 0,"dip"},			// 1D
	{"Debug Dip 2",	BIT_DIPSWITCH,	NeoDebugDip + 1,"dip"},			// 1E
};

STDINPUTINFO(neogeo);

#define A(a, b, c, d) { a, b, (unsigned char*)(c), d }

static struct BurnInputInfo neopaddleInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
	{"P1 Start",	BIT_DIGITAL,	NeoButton1 + 0,	"p1 start"},		//  1
	{"P1 Select",	BIT_DIGITAL,	NeoButton1 + 1,	"p1 select"},		//  2

	{"P1 Up",	BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"P1 Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"P1 Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"P1 Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"P1 Button A",	BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"P1 Button C",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"P1 Button D",	BIT_DIGITAL,	NeoJoy1 + 7,	"mouse button 1"},	//  A
	A("P1 Paddle",	BIT_ANALOG_REL, NeoAxis + 0,	"mouse x-axis"),	//  B

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		//  C
	{"P2 Start",	BIT_DIGITAL,	NeoButton1 + 2,	"p2 start"},		//  D
	{"P2 Select",	BIT_DIGITAL,	NeoButton1 + 3,	"p2 select"},		//  E

	{"P2 Up",	BIT_DIGITAL,	NeoJoy2 + 0,	"p2 up"},		//  F
	{"P2 Down",	BIT_DIGITAL,	NeoJoy2 + 1,	"p2 down"},		// 10
	{"P2 Left",	BIT_DIGITAL,	NeoJoy2 + 2,	"p2 left"},		// 11
	{"P2 Right",	BIT_DIGITAL,	NeoJoy2 + 3,	"p2 right"},		// 12
	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"p2 fire 1"},		// 13
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"p2 fire 2"},		// 14
	{"P2 Button C",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 3"},		// 15
	{"P2 Button D",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 4"},		// 16
	A("P2 Paddle",	BIT_ANALOG_REL, NeoAxis + 1,	"p2 x-axis"),		// 17

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 18
	{"Test",	BIT_DIGITAL,	NeoDiag + 0,	"diag"},		// 19
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 1A
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 1B
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 1C

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 1D
	{"Slots",	BIT_DIPSWITCH,	&nNeoNumSlots,	"dip"},			// 1E

	{"Debug Dip 1",	BIT_DIPSWITCH,	NeoDebugDip + 0,"dip"},			// 1F
	{"Debug Dip 2",	BIT_DIPSWITCH,	NeoDebugDip + 1,"dip"},			// 1G
};

STDINPUTINFO(neopaddle);

static struct BurnInputInfo neotrackballInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
	{"P1 Start",	BIT_DIGITAL,	NeoButton1 + 0,	"p1 start"},		//  1

   	A("P1 X Axis",	BIT_ANALOG_REL,	NeoAxis + 0,	"mouse x-axis"),	//  2
   	A("P1 Y Axis",	BIT_ANALOG_REL,	NeoAxis + 1,	"mouse y-axis"),	//  3

	{"P1 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"mouse button 1"},	//  4
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"mouse button 2"},	//  5

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		//  6
	{"P2 Start",	BIT_DIGITAL,	NeoButton1 + 2,	"p2 start"},		//  7

	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 1"},		//  8
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 2"},		//  9

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		//  A
	{"Test",	BIT_DIGITAL,	NeoDiag + 0,	"diag"},		//  B
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		//  C
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			//  D
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			//  E

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			//  F
	{"Slots",	BIT_DIPSWITCH,	&nNeoNumSlots,	"dip"},			// 10

	{"Debug Dip 1",	BIT_DIPSWITCH,	NeoDebugDip + 0,"dip"},			// 11
	{"Debug Dip 2",	BIT_DIPSWITCH,	NeoDebugDip + 1,"dip"},			// 12
};

STDINPUTINFO(neotrackball);

#undef A

static struct BurnInputInfo neodualInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
	{"P1 Start",	BIT_DIGITAL,	NeoButton1 + 0,	"p1 start"},		//  1
	{"P1 Select",	BIT_DIGITAL,	NeoButton1 + 1,	"p1 select"},		//  2

	{"P1 Up",	BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"P1 Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"P1 Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"P1 Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"P1 Button A",	BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"P1 Button C",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"P1 Button D",	BIT_DIGITAL,	NeoJoy1 + 7,	"p1 fire 4"},		//  A

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		//  B
	{"P2 Start",	BIT_DIGITAL,	NeoButton1 + 2,	"p2 start"},		//  C
	{"P2 Select",	BIT_DIGITAL,	NeoButton1 + 3,	"p2 select"},		//  D

	{"P2 Up",	BIT_DIGITAL,	NeoJoy2 + 0,	"p2 up"},		//  E
	{"P2 Down",	BIT_DIGITAL,	NeoJoy2 + 1,	"p2 down"},		//  F
	{"P2 Left",	BIT_DIGITAL,	NeoJoy2 + 2,	"p2 left"},		// 10
	{"P2 Right",	BIT_DIGITAL,	NeoJoy2 + 3,	"p2 right"},		// 11
	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"p2 fire 1"},		// 12
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"p2 fire 2"},		// 13
	{"P2 Button C",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 3"},		// 14
	{"P2 Button D",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 4"},		// 15

	{"P3 Coin",	BIT_DIGITAL,	NeoButton4 + 0,	"p3 coin"},		// 16
	{"P3 Start",	BIT_DIGITAL,	NeoButton3 + 0,	"p3 start"},		// 17
	{"P3 Select",	BIT_DIGITAL,	NeoButton3 + 1,	"p3 select"},		// 18

	{"P3 Up",	BIT_DIGITAL,	NeoJoy3 + 0,	"p3 up"},		// 19
	{"P3 Down",	BIT_DIGITAL,	NeoJoy3 + 1,	"p3 down"},		// 1A
	{"P3 Left",	BIT_DIGITAL,	NeoJoy3 + 2,	"p3 left"},		// 1B
	{"P3 Right",	BIT_DIGITAL,	NeoJoy3 + 3,	"p3 right"},		// 1C
	{"P3 Button A",	BIT_DIGITAL,	NeoJoy3 + 4,	"p3 fire 1"},		// 1D
	{"P3 Button B",	BIT_DIGITAL,	NeoJoy3 + 5,	"p3 fire 2"},		// 1E
	{"P3 Button C",	BIT_DIGITAL,	NeoJoy3 + 6,	"p3 fire 3"},		// 1F
	{"P3 Button D",	BIT_DIGITAL,	NeoJoy3 + 7,	"p3 fire 4"},		// 20

	{"P4 Coin",	BIT_DIGITAL,	NeoButton4 + 1,	"p4 coin"},		// 21
	{"P4 Start",	BIT_DIGITAL,	NeoButton3 + 2,	"p4 start"},		// 22
	{"P4 Select",	BIT_DIGITAL,	NeoButton3 + 3,	"p4 select"},		// 23

	{"P4 Up",	BIT_DIGITAL,	NeoJoy4 + 0,	"p4 up"},		// 24
	{"P4 Down",	BIT_DIGITAL,	NeoJoy4 + 1,	"p4 down"},		// 25
	{"P4 Left",	BIT_DIGITAL,	NeoJoy4 + 2,	"p4 left"},		// 26
	{"P4 Right",	BIT_DIGITAL,	NeoJoy4 + 3,	"p4 right"},		// 27
	{"P4 Button A",	BIT_DIGITAL,	NeoJoy4 + 4,	"p4 fire 1"},		// 28
	{"P4 Button B",	BIT_DIGITAL,	NeoJoy4 + 5,	"p4 fire 2"},		// 29
	{"P4 Button C",	BIT_DIGITAL,	NeoJoy4 + 6,	"p4 fire 3"},		// 2A
	{"P4 Button D",	BIT_DIGITAL,	NeoJoy4 + 7,	"p4 fire 4"},		// 2B

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 2C
	{"Test 1",	BIT_DIGITAL,	NeoDiag + 0,	"diag"},		// 2D
	{"Service 1",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 2E
	{"Test 2",	BIT_DIGITAL,	NeoDiag + 1,	""},			// 2F
	{"Service 2",	BIT_DIGITAL,	NeoButton4 + 2,	""},			// 30

	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 31
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 32

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 33
	{"Slots",	BIT_DIPSWITCH,	&nNeoNumSlots,	"dip"},			// 34

	{"Debug Dip 1",	BIT_DIPSWITCH,	NeoDebugDip + 0,"dip"},			// 35
	{"Debug Dip 2",	BIT_DIPSWITCH,	NeoDebugDip + 1,"dip"},			// 36
};

STDINPUTINFO(neodual);

static struct BurnInputInfo neomahjongInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
	{"P1 Start",	BIT_DIGITAL,	NeoButton1 + 0,	"p1 start"},		//  1
	{"P1 Select",	BIT_DIGITAL,	NeoButton1 + 1,	"p1 select"},		//  2

	{"P1 Up",	BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"P1 Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"P1 Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"P1 Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"P1 Button A",	BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"P1 Button C",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"P1 Button D",	BIT_DIGITAL,	NeoJoy1 + 7,	"p1 fire 4"},		//  A

	{"A",		BIT_DIGITAL,	NeoButton1 +  8, "key tab"},		//  B
	{"B",		BIT_DIGITAL,	NeoButton1 +  9, "key q"},		//  C
	{"C",		BIT_DIGITAL,	NeoButton1 + 10, "key w"},		//  D
	{"D",		BIT_DIGITAL,	NeoButton1 + 11, "key e"},		//  E
	{"E",		BIT_DIGITAL,	NeoButton1 + 12, "key r"},		//  F
	{"F",		BIT_DIGITAL,	NeoButton1 + 13, "key t"},		// 10
	{"G",		BIT_DIGITAL,	NeoButton1 + 14, "key y"},		// 11
	{"H",		BIT_DIGITAL,	NeoButton1 + 16, "key u"},		// 12
	{"I",		BIT_DIGITAL,	NeoButton1 + 17, "key i"},		// 13
	{"J",		BIT_DIGITAL,	NeoButton1 + 18, "key o"},		// 14
	{"K",		BIT_DIGITAL,	NeoButton1 + 19, "key p"},		// 15
	{"L",		BIT_DIGITAL,	NeoButton1 + 20, "key ["},		// 16
	{"M",		BIT_DIGITAL,	NeoButton1 + 21, "key ]"},		// 17
	{"N",		BIT_DIGITAL,	NeoButton1 + 22, "key backslash"},	// 18
	{"Pon",		BIT_DIGITAL,	NeoButton1 + 24, "key a"},		// 19
	{"Chi",		BIT_DIGITAL,	NeoButton1 + 25, "key s"},		// 1A
	{"Kan",		BIT_DIGITAL,	NeoButton1 + 26, "key d"},		// 1B
	{"Ron",		BIT_DIGITAL,	NeoButton1 + 27, "key f"},		// 1C
	{"Reach",	BIT_DIGITAL,	NeoButton1 + 28, "key g"},		// 1D

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		// 1E
	{"P2 Start",	BIT_DIGITAL,	NeoButton1 + 2,	"p2 start"},		// 1F
	{"P2 Select",	BIT_DIGITAL,	NeoButton1 + 3,	"p2 select"},		// 20

	{"P2 Up",	BIT_DIGITAL,	NeoJoy2 + 0,	"p2 up"},		// 21
	{"P2 Down",	BIT_DIGITAL,	NeoJoy2 + 1,	"p2 down"},		// 22
	{"P2 Left",	BIT_DIGITAL,	NeoJoy2 + 2,	"p2 left"},		// 23
	{"P2 Right",	BIT_DIGITAL,	NeoJoy2 + 3,	"p2 right"},		// 24
	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"p2 fire 1"},		// 25
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"p2 fire 2"},		// 26
	{"P2 Button C",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 3"},		// 27
	{"P2 Button D",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 4"},		// 28

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 29
	{"Test",	BIT_DIGITAL,	NeoDiag + 0,	"diag"},		// 2A
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 2B
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 2C
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 2D

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 2E
	{"Slots",	BIT_DIPSWITCH,	&nNeoNumSlots,	"dip"},			// 2F

	{"Debug Dip 1",	BIT_DIPSWITCH,	NeoDebugDip + 0,"dip"},			// 30
	{"Debug Dip 2",	BIT_DIPSWITCH,	NeoDebugDip + 1,"dip"},			// 31
};

STDINPUTINFO(neomahjong);

// ------------------------------------------------------------------------
// Additional inputs for gambling games

static struct BurnInputInfo jockeygpInputList[] = {
	{"P1 Coin",	BIT_DIGITAL,	NeoButton2 + 4,	"p1 coin"},		// 18

	{"P1 Up",	BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"P1 Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"P1 Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"P1 Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"P1 Button A",	BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"P1 Button B",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"P1 Button C",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"P1 Button D",	BIT_DIGITAL,	NeoJoy1 + 7,	"p1 fire 4"},		//  A

	{"P2 Coin",	BIT_DIGITAL,	NeoButton2 + 7,	"p2 coin"},		//  0
	{"P2 Up",	BIT_DIGITAL,	NeoJoy2 + 0,	"p2 up"},		//  E
	{"P2 Down",	BIT_DIGITAL,	NeoJoy2 + 1,	"p2 down"},		//  F
	{"P2 Left",	BIT_DIGITAL,	NeoJoy2 + 2,	"p2 left"},		// 10
	{"P2 Right",	BIT_DIGITAL,	NeoJoy2 + 3,	"p2 right"},		// 11
	{"P2 Button A",	BIT_DIGITAL,	NeoJoy2 + 4,	"p2 fire 1"},		// 12
	{"P2 Button B",	BIT_DIGITAL,	NeoJoy2 + 5,	"p2 fire 2"},		// 13
	{"P2 Button C",	BIT_DIGITAL,	NeoJoy2 + 6,	"p2 fire 3"},		// 14
	{"P2 Button D",	BIT_DIGITAL,	NeoJoy2 + 7,	"p2 fire 4"},		// 15

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 16
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 18
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 19
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 1A

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 1B
};

STDINPUTINFO(jockeygp);

static struct BurnInputInfo vlinerInputList[] = {
	{"Coin 0 IN",	BIT_DIGITAL,	NeoButton2 + 0,	"p1 coin"},		//  0
	{"Coin 1 IN",	BIT_DIGITAL,	NeoButton2 + 1,	"p2 coin"},		//  B
	{"Hopper out",	BIT_DIGITAL,	NeoButton2 + 7,	"p1 start"},		// 28

	{"Up",		BIT_DIGITAL,	NeoJoy1 + 0,	"p1 up"},		//  3
	{"Down",	BIT_DIGITAL,	NeoJoy1 + 1,	"p1 down"},		//  4
	{"Left",	BIT_DIGITAL,	NeoJoy1 + 2,	"p1 left"},		//  5
	{"Right",	BIT_DIGITAL,	NeoJoy1 + 3,	"p1 right"},		//  6
	{"Big",		BIT_DIGITAL,	NeoJoy1 + 4,	"p1 fire 1"},		//  7
	{"Small",	BIT_DIGITAL,	NeoJoy1 + 5,	"p1 fire 2"},		//  8
	{"D-up",	BIT_DIGITAL,	NeoJoy1 + 6,	"p1 fire 3"},		//  9
	{"Start",	BIT_DIGITAL,	NeoJoy1 + 7,	"p1 fire 4"},		//  A

	{"Reset",	BIT_DIGITAL,	&NeoReset,	"reset"},		// 16
	{"Test",	BIT_DIGITAL,	NeoButton2 + 4,	"diag"},		// 17
	{"Service",	BIT_DIGITAL,	NeoButton2 + 2,	"service"},		// 18
	{"Dip 1",	BIT_DIPSWITCH,	NeoInput + 4,	"dip"},			// 19
	{"Dip 2",	BIT_DIPSWITCH,	NeoInput + 5,	"dip"},			// 1A

	{"System",	BIT_DIPSWITCH,	&NeoSystem,	"dip"},			// 1B
};

STDINPUTINFO(vliner);

static struct BurnDIPInfo neodefaultDIPList[] = {
	// Offset
	{0x19,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},
	{0x03,	0xFF, 0xFF,	0x02, NULL},

	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x00,	0x01, 0x04,	0x00, "Off"},
	{0x00,	0x01, 0x04,	0x04, "On"},
};

static struct BurnDIPInfo neopaddleDIPList[] = {
	// Offset
	{0x1B,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},
	{0x03,	0xFF, 0xFF,	0x02, NULL},
};

static struct BurnDIPInfo neodualDIPList[] = {
	// Offset
	{0x31,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},
	{0x03,	0xFF, 0xFF,	0x02, NULL},

	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x00,	0x01, 0x04,	0x00, "Off"},
	{0x00,	0x01, 0x04,	0x04, "On"},
};

static struct BurnDIPInfo neomahjongDIPList[] = {
	// Offset
	{0x2C,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x84, NULL},
	{0x03,	0xFF, 0xFF,	0x02, NULL},

	{0,		0xFE, 0,	2,	  "Mahjong control panel"},
	{0x00,	0x01, 0x04,	0x00, "Off"},
	{0x00,	0x01, 0x04,	0x04, "On"},
};

static struct BurnDIPInfo neogeoDIPList[] = {
	// DIP 1
	{0,		0xFE, 0,	2,	  "Setting mode"},
	{0x00,	0x01, 0x01,	0x00, "Off"},
	{0x00,	0x01, 0x01,	0x01, "On"},

	// 1 or 2 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x02, 0x02,	0x00, "1"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x02, 0x02,	0x02, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	// 2 or 4 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x82, 0x02,	0x00, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x82, 0x02,	0x02, "4"},
	{0x02,	0x00, 0x3F,	0x06, NULL},

	{0,		0xFE, 0,	5,	  "Commmunicaton"},
	{0x00,	0x01, 0x38,	0x00, "Disabled"},
	{0x00,	0x01, 0x38,	0x08, "Setting 1"},
	{0x00,	0x01, 0x38,	0x10, "Setting 2"},
	{0x00,	0x01, 0x38,	0x18, "Setting 3"},
	{0x00,	0x01, 0x38,	0x20, "Setting 4"},
	{0x00,	0x01, 0x38,	0x28, "Setting 5"},
	{0x00,	0x01, 0x38,	0x30, "Setting 6"},
	{0x00,	0x01, 0x38,	0x38, "Setting 7"},
	{0,		0xFE, 0,	2,	  "Free play"},
	{0x00,	0x01, 0x40,	0x00, "Off"},
	{0x00,	0x01, 0x40,	0x40, "On"},
	{0,		0xFE, 0,	2,	  "Stop mode"},
	{0x00,	0x01, 0x80,	0x00, "Off"},
	{0x00,	0x01, 0x80,	0x80, "On"},

	// Fake DIPs

	// MVS/AES system
	{0,		0xFD, 0,	2,	  NULL},
	{0x02,	0x82, 0x04,	0x04, "MVS system"},
	{0x02,	0x00, 0x30,	0x30, NULL},
	{0x02,	0x82, 0x04,	0x00, "AES system"},
	{0x02,	0x00, 0x30,	0x30, NULL},
	// Region
	{0,		0xFD, 0,	3,	  "Region"},
	{0x02,	0x02, 0x03,	0x00, "Japan"},
	{0x02,	0x00, 0x30,	0x00, NULL},
	{0x02,	0x02, 0x03,	0x01, "USA"},
	{0x02,	0x00, 0x30,	0x00, NULL},
	{0x02,	0x02, 0x03,	0x02, "Asia / Europe"},
	{0x02,	0x00, 0x30,	0x00, NULL},
	{0x02,	0x02, 0x03,	0x03, "Japan"},
	{0x02,	0x00, 0x30,	0x00, NULL},
	// BIOS selection
	{0,		0xFD, 0,	3,	  NULL},
	{0x02,	0x01, 0x30,	0x00, "Normal BIOS"},
	{0x02,	0x01, 0x30,	0x10, "Debug BIOS"},
	{0x02,	0x01, 0x30,	0x20, "Universe BIOS"},
	// Number of cartridge slots
	{0,		0xFD, 0,	3,	  "Cartridge Slots"},
	{0x03,	0x01, 0xFF,	0x02, "1 / 2"},
	{0x03,	0x01, 0xFF,	0x04, "4"},
	{0x03,	0x01, 0xFF,	0x06, "6"},
	{0x03,	0x01, 0xFF,	0x01, "1 / 2"},

	// Memory card
	{0,		0xFD, 0,	2,	  "Memory card"},
	{0x02,	0x01, 0x80,	0x80, "Writable"},
	{0x02,	0x01, 0x80,	0x00, "Write-protected"},
	{0,		0xFD, 0,	2,	  "Default card type"},
	{0x02,	0x01, 0x40,	0x40, "1 Megabit"},
	{0x02,	0x01, 0x40,	0x00, "Normal"},
};

STDDIPINFOEXT(neogeo, neodefault, neogeo);
STDDIPINFOEXT(neopaddle, neopaddle, neogeo);
STDDIPINFOEXT(neodual, neodual, neogeo);
STDDIPINFOEXT(neomahjong, neomahjong, neogeo);

static struct BurnDIPInfo neotrackballDIPList[] = {
	// Defaults
	{0x0D,	0xFF, 0xFF,	0x00, NULL},
	{0x0E,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x0F,	0xFF, 0xFF,	0x86, NULL},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Setting mode"},
	{0x0D,	0x01, 0x01,	0x00, "Off"},
	{0x0D,	0x01, 0x01,	0x01, "On"},
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x0D,	0x01, 0x02,	0x00, "1"},
	{0x0D,	0x01, 0x02,	0x02, "2"},
	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x0D,	0x01, 0x04,	0x00, "Off"},
	{0x0D,	0x01, 0x04,	0x04, "On"},
	{0,		0xFE, 0,	5,	  "Commmunicaton"},
	{0x0D,	0x01, 0x38,	0x00, "Disabled"},
	{0x0D,	0x01, 0x38,	0x08, "Setting 1"},
	{0x0D,	0x01, 0x38,	0x10, "Setting 2"},
	{0x0D,	0x01, 0x38,	0x18, "Setting 3"},
	{0x0D,	0x01, 0x38,	0x20, "Setting 4"},
	{0x0D,	0x01, 0x38,	0x28, "Setting 5"},
	{0x0D,	0x01, 0x38,	0x30, "Setting 6"},
	{0x0D,	0x01, 0x38,	0x38, "Setting 7"},
	{0,		0xFE, 0,	2,	  "Free play"},
	{0x0D,	0x01, 0x40,	0x00, "Off"},
	{0x0D,	0x01, 0x40,	0x40, "On"},
	{0,		0xFE, 0,	2,	  "Stop mode"},
	{0x0D,	0x01, 0x80,	0x00, "Off"},
	{0x0D,	0x01, 0x80,	0x80, "On"},

	// MVS/AES system
	{0,		0xFD, 0,	2,	  NULL},
	{0x0F,	0x02, 0x04,	0x04, "MVS system"},
	{0x0F,	0x00, 0x30,	0x00, NULL},
	{0x0F,	0x02, 0x04,	0x00, "AES system"},
	{0x0F,	0x00, 0x30,	0x00, NULL},
	// Region
	{0,		0xFD, 0,	3,	  "Region"},
	{0x0F,	0x01, 0x03,	0x00, "Japan"},
	{0x0F,	0x01, 0x03,	0x01, "USA"},
	{0x0F,	0x01, 0x03,	0x02, "Asia / Europe"},
	{0x0F,	0x01, 0x03,	0x03, "Japan"},

	// Memory card
	{0,		0xFD, 0,	2,	  "Memory card"},
	{0x0F,	0x01, 0x80,	0x80, "Writable"},
	{0x0F,	0x01, 0x80,	0x00, "Write-protected"},
	{0,		0xFD, 0,	2,	  "Default card type"},
	{0x0F,	0x01, 0x40,	0x40, "1 Megabit"},
	{0x0F,	0x01, 0x40,	0x00, "Normal"},
};

static struct BurnDIPInfo PCB268DIPList[] = {
	// Offset
	{0x19,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},

	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x0D,	0x01, 0x04,	0x00, "Off"},
	{0x0D,	0x01, 0x04,	0x04, "On"},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Setting mode"},
	{0x00,	0x01, 0x01,	0x00, "Off"},
	{0x00,	0x01, 0x01,	0x01, "On"},

	// 1 or 2 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x02, 0x02,	0x00, "1"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x02, 0x02,	0x02, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	// 2 or 4 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x82, 0x02,	0x00, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x82, 0x02,	0x02, "4"},
	{0x02,	0x00, 0x3F,	0x06, NULL},

	{0,		0xFE, 0,	5,	  "Commmunicaton"},
	{0x00,	0x01, 0x38,	0x00, "Disabled"},
	{0x00,	0x01, 0x38,	0x08, "Setting 1"},
	{0x00,	0x01, 0x38,	0x10, "Setting 2"},
	{0x00,	0x01, 0x38,	0x18, "Setting 3"},
	{0x00,	0x01, 0x38,	0x20, "Setting 4"},
	{0x00,	0x01, 0x38,	0x28, "Setting 5"},
	{0x00,	0x01, 0x38,	0x30, "Setting 6"},
	{0x00,	0x01, 0x38,	0x38, "Setting 7"},
	{0,		0xFE, 0,	2,	  "Free play"},
	{0x00,	0x01, 0x40,	0x00, "Off"},
	{0x00,	0x01, 0x40,	0x40, "On"},
	{0,		0xFE, 0,	2,	  "Stop mode"},
	{0x00,	0x01, 0x80,	0x00, "Off"},
	{0x00,	0x01, 0x80,	0x80, "On"},

	// Memory card
	{0,		0xFD, 0,	2,	  "Memory card"},
	{0x0F,	0x01, 0x80,	0x80, "Writable"},
	{0x0F,	0x01, 0x80,	0x00, "Write-protected"},
	{0,		0xFD, 0,	2,	  "Default card type"},
	{0x0F,	0x01, 0x40,	0x40, "1 Megabit"},
	{0x0F,	0x01, 0x40,	0x00, "Normal"},
};

static struct BurnDIPInfo PCB269DIPList[] = {
	// Offset
	{0x19,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},

	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x0D,	0x01, 0x04,	0x00, "Off"},
	{0x0D,	0x01, 0x04,	0x04, "On"},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Setting mode"},
	{0x00,	0x01, 0x01,	0x00, "Off"},
	{0x00,	0x01, 0x01,	0x01, "On"},

	// 1 or 2 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x02, 0x02,	0x00, "1"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x02, 0x02,	0x02, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	// 2 or 4 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x82, 0x02,	0x00, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x82, 0x02,	0x02, "4"},
	{0x02,	0x00, 0x3F,	0x06, NULL},

	{0,		0xFE, 0,	5,	  "Commmunicaton"},
	{0x00,	0x01, 0x38,	0x00, "Disabled"},
	{0x00,	0x01, 0x38,	0x08, "Setting 1"},
	{0x00,	0x01, 0x38,	0x10, "Setting 2"},
	{0x00,	0x01, 0x38,	0x18, "Setting 3"},
	{0x00,	0x01, 0x38,	0x20, "Setting 4"},
	{0x00,	0x01, 0x38,	0x28, "Setting 5"},
	{0x00,	0x01, 0x38,	0x30, "Setting 6"},
	{0x00,	0x01, 0x38,	0x38, "Setting 7"},
	{0,		0xFE, 0,	2,	  "Free play"},
	{0x00,	0x01, 0x40,	0x00, "Off"},
	{0x00,	0x01, 0x40,	0x40, "On"},
	{0,		0xFE, 0,	2,	  "Stop mode"},
	{0x00,	0x01, 0x80,	0x00, "Off"},
	{0x00,	0x01, 0x80,	0x80, "On"},

	// Region
	{0,		0xFD, 0,	2,	  "Region"},
	{0x02,	0x02, 0x03,	0x02, "Asia / Europe"},
	{0x02,	0x00, 0x30,	0x00, NULL},
	{0x02,	0x02, 0x03,	0x03, "Japan"},
	{0x02,	0x00, 0x30,	0x00, NULL},
};

static struct BurnDIPInfo PCB271DIPList[] = {
	// Offset
	{0x19,	0xF0, 0x00,	0x00, NULL},

	// Defaults
	{0x00,	0xFF, 0xFF,	0x00, NULL},
	{0x01,	0xFF, 0x7F,	0x00, NULL},
	// Fake DIPs
	{0x02,	0xFF, 0xFF,	0x86, NULL},

	{0,		0xFE, 0,	2,	  "Autofire"},
	{0x0D,	0x01, 0x04,	0x00, "Off"},
	{0x0D,	0x01, 0x04,	0x04, "On"},

	// DIP 1
	{0,		0xFE, 0,	2,	  "Setting mode"},
	{0x00,	0x01, 0x01,	0x00, "Off"},
	{0x00,	0x01, 0x01,	0x01, "On"},

	// 1 or 2 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x02, 0x02,	0x00, "1"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x02, 0x02,	0x02, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	// 2 or 4 coin slots
	{0,		0xFE, 0,	2,	  "Coin chutes"},
	{0x00,	0x82, 0x02,	0x00, "2"},
	{0x02,	0x00, 0x3F,	0x06, NULL},
	{0x00,	0x82, 0x02,	0x02, "4"},
	{0x02,	0x00, 0x3F,	0x06, NULL},

	{0,		0xFE, 0,	5,	  "Commmunicaton"},
	{0x00,	0x01, 0x38,	0x00, "Disabled"},
	{0x00,	0x01, 0x38,	0x08, "Setting 1"},
	{0x00,	0x01, 0x38,	0x10, "Setting 2"},
	{0x00,	0x01, 0x38,	0x18, "Setting 3"},
	{0x00,	0x01, 0x38,	0x20, "Setting 4"},
	{0x00,	0x01, 0x38,	0x28, "Setting 5"},
	{0x00,	0x01, 0x38,	0x30, "Setting 6"},
	{0x00,	0x01, 0x38,	0x38, "Setting 7"},
	{0,		0xFE, 0,	2,	  "Free play"},
	{0x00,	0x01, 0x40,	0x00, "Off"},
	{0x00,	0x01, 0x40,	0x40, "On"},
	{0,		0xFE, 0,	2,	  "Stop mode"},
	{0x00,	0x01, 0x80,	0x00, "Off"},
	{0x00,	0x01, 0x80,	0x80, "On"},
};

STDDIPINFO(neotrackball);
STDDIPINFO(PCB268);
STDDIPINFO(PCB269);
STDDIPINFO(PCB271);

// Rom information
static struct BurnRomInfo neogeoRomDesc[] = {
	{ "vs-bios.rom",    0x020000, 0xF0E8F27D, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  0 68K BIOS (JP, MVS, ? slot, version 5)
//	{ "sp-j2.rom",      0x020000, 0xACEDE59C, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  0 68K BIOS (JP, MVS, ? slot, version 5)
//	{ "sp1.jipan.1024", 0x020000, 0x9FB0ABE4, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  0 68K BIOS (JP, MVS, 4 slot, version 3)
	{ "usa_2slt.bin",   0x020000, 0xE72943DE, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  1 68K BIOS (US, MVS, 2 slot, version 5)
//	{ "sp-e.sp1",       0x020000, 0x2723A5B5, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  1 68K BIOS (US, MVS, 6 slot, version 5)
	{ "asia-s3.rom",    0x020000, 0x91B64BE3, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT },		 //  2 68K BIOS (AS, MVS, 1 slot, version 6, no Z80 BIOS)
//	{ "sp-s2.sp1",      0x020000, 0x9036D879, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT },		 //  2 68K BIOS (AS, MVS, 1 slot, version 5)
//	{ "sp-s.sp1",       0x020000, 0xC7F2FA45, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT },		 //  2 68K BIOS (AS, MVS, 4 slot, version 3)
	{ "",                      0,          0, 0 },

	{ "neo-po.bin",     0x020000, 0x16D0C132, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  4 68K BIOS (JP, AES)
	{ "",                      0,          0, 0 },							 //  5 68K BIOS (US, AES)
	{ "neo-epo.bin",    0x020000, 0xD27A71F1, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  6 68K BIOS (AS, AES)
	{ "",                      0,          0, 0 },

	{ "neodebug.bin",   0x020000, 0x698EBB7D, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  8 68K BIOS (JP, devkit)
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "uni-bios.22",    0x020000, 0x2d50996a, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v2.2)
//	{ "uni-bios.21",    0x020000, 0x8DABF76B, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v2.1)
//	{ "uni-bios.20",    0x020000, 0x0C12C2AD, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v2.0)
//	{ "uni-bios.13a",   0x020000, 0x02BF155E, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v1.3 Revision A?)
//	{ "uni-bios.13",    0x020000, 0xB24B44A0, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v1.3)
//	{ "uni-bios.12",    0x020000, 0x4FA698E9, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v1.2)
//	{ "uni-bios.11",    0x020000, 0x5DDA0D84, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v1.1)
//	{ "uni-bios.10",    0x020000, 0x0CE453A0, BRF_ESS | BRF_PRG | BRF_BIOS | BRF_SELECT | BRF_OPT }, //  C Universe BIOS (v1.0)
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sm1.sm1",        0x020000, 0x97Cf998B, BRF_ESS | BRF_PRG | BRF_BIOS },			 // 10 Z80 program
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sfix.sfx",       0x020000, 0x354029FC, BRF_GRA | BRF_BIOS },					 // 14 Text layer tiles
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "000-lo.lo",      0x010000, 0xE09E253C, BRF_ESS | BRF_BIOS },					 // 18 Zoom table
};

STD_ROM_PICK(neogeo);
STD_ROM_FN(neogeo);

static struct BurnRomInfo neotrackballRomDesc[] = {
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "",                      0,          0, 0 },
	{ "236-bios.bin",   0x020000, 0x853E6B96, BRF_BIOS },											 //  9 68K BIOS (EU/AS, MVS, supports analog controls)
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sm1.sm1",        0x020000, 0x97Cf998B, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 10 Z80 program
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sfix.sfx",       0x020000, 0x354029FC, BRF_GRA | BRF_BIOS },									 // 14 Text layer tiles
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "000-lo.lo",      0x010000, 0xE09E253C, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 18 Zoom table
};


STD_ROM_PICK(neotrackball);
STD_ROM_FN(neotrackball);

static struct BurnRomInfo PCB268RomDesc[] = {
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "268-bios.bin",   0x080000, 0         , BRF_BIOS },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sm1.sm1",        0x020000, 0x97Cf998B, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 10 Z80 program
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sfix.sfx",       0x020000, 0x354029FC, BRF_GRA | BRF_BIOS },									 // 14 Text layer tiles
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "000-lo.lo",      0x010000, 0xE09E253C, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 18 Zoom table
};


STD_ROM_PICK(PCB268);
STD_ROM_FN(PCB268);

static struct BurnRomInfo PCB269RomDesc[] = {
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "269-bios.bin",   0x080000, 0xb4590283, BRF_BIOS }, // real name is sp-4x.sp1
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sm1.sm1",        0x020000, 0x97Cf998B, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 10 Z80 program
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sfix.sfx",       0x020000, 0x354029FC, BRF_GRA | BRF_BIOS },									 // 14 Text layer tiles
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "000-lo.lo",      0x010000, 0xE09E253C, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 18 Zoom table
};


STD_ROM_PICK(PCB269);
STD_ROM_FN(PCB269);

static struct BurnRomInfo PCB271RomDesc[] = {
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "271-bios.bin",   0x080000, 0x148dd727, BRF_BIOS },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sm1.sm1",        0x020000, 0x97Cf998B, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 10 Z80 program
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "sfix.sfx",       0x020000, 0x354029FC, BRF_GRA | BRF_BIOS },									 // 14 Text layer tiles
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },
	{ "",                      0,          0, 0 },

	{ "000-lo.lo",      0x010000, 0xE09E253C, BRF_ESS | BRF_PRG | BRF_BIOS },						 // 18 Zoom table
};


STD_ROM_PICK(PCB271);
STD_ROM_FN(PCB271);

struct BurnDriver BurnDrvNeoGeo = {
	"neogeo", NULL, NULL, "1990",
	"Neo Geo\0", "BIOS only", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_BOARDROM, 0, HARDWARE_SNK_NEOGEO,
	NULL, neogeoRomInfo, neogeoRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// ----------------------------------------------------------------------------
// Neo Geo 4 player test cartridge

static struct BurnRomInfo fourplayRomDesc[] = {
	{ "4play_p1.rom", 0x100000, 0x3C3D741B, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "4play_s1.rom", 0x020000, 0xDE828076, 2 | BRF_GRA },		 //  1 Text data

	{ "4play_c1.rom", 0x020000, 0x7EE8CDCD, 3 | BRF_GRA },		 //  2 Sprite data
	{ "4play_c2.rom", 0x020000, 0x7EE8CDCD, 3 | BRF_GRA },		 //  3

	{ "4play_m1.rom", 0x020000, 0x5132580E, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "4play_v1.rom", 0x020000, 0x7EE8CDCD, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(fourplay, fourplay, neogeo);
STD_ROM_FN(fourplay);

struct BurnDriverX BurnDrv4play = {
	"4play", NULL, "neogeo", "???",
	"* 4 player input test\0", "4 player  input test cartridge", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 4, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_4_JOYSTICKS,
	NULL, fourplayRomInfo, fourplayRomName, neodualInputInfo, neodualDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// ----------------------------------------------------------------------------
// Normal Games

// Nam - 1975

static struct BurnRomInfo nam1975RomDesc[] = {
	{ "001-p1.bin",   0x080000, 0xcc9fc951, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "001-s1.bin",   0x010000, 0x8ded55a5, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "001-c1.bin",   0x080000, 0x32ea98e1, 3 | BRF_GRA },		 //  2 Sprite data
	{ "001-c2.bin",   0x080000, 0xcbc4064c, 3 | BRF_GRA },		 //  3
	{ "001-c3.bin",   0x080000, 0x0151054c, 3 | BRF_GRA },		 //  4
	{ "001-c4.bin",   0x080000, 0x0a32570d, 3 | BRF_GRA },		 //  5
	{ "001-c5.bin",   0x080000, 0x90b74cc2, 3 | BRF_GRA },		 //  6
	{ "001-c6.bin",   0x080000, 0xe62bed58, 3 | BRF_GRA },		 //  7

	{ "001-m1.bin",   0x010000, 0xcd088502, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "001-v11.bin",  0x080000, 0xa7c3d5e5, 5 | BRF_SND },		 //  9 Sound data
	{ "001-v21.bin",  0x080000, 0x55e670b3, 6 | BRF_SND },		 // 10
	{ "001-v22.bin",  0x080000, 0xab0d8368, 6 | BRF_SND },		 // 11
	{ "001-v23.bin",  0x080000, 0xdf468e28, 6 | BRF_SND },		 // 12
};

STDROMPICKEXT(nam1975, nam1975, neogeo);
STD_ROM_FN(nam1975);

struct BurnDriver BurnDrvNam1975 = {
	"nam1975", NULL, "neogeo", "1990",
	"NAM - 1975\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, nam1975RomInfo, nam1975RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Baseball Stars Professional

static struct BurnRomInfo bstarsRomDesc[] = {
	{ "002-p1.bin",   0x080000, 0x3bc7790e, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "002-s1.bin",   0x020000, 0x1a7fd0c6, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "002-c1.bin",   0x080000, 0xaaff2a45, 3 | BRF_GRA },		 //  2 Sprite data
	{ "002-c2.bin",   0x080000, 0x3ba0f7e4, 3 | BRF_GRA },		 //  3
	{ "002-c3.bin",   0x080000, 0x96f0fdfa, 3 | BRF_GRA },		 //  4
	{ "002-c4.bin",   0x080000, 0x5fd87f2f, 3 | BRF_GRA },		 //  5
	{ "002-c5.bin",   0x080000, 0x807ed83b, 3 | BRF_GRA },		 //  6
	{ "002-c6.bin",   0x080000, 0x5a3cad41, 3 | BRF_GRA },		 //  7

	{ "002-m1.bin",   0x010000, 0x79a8f4c2, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "002-v11.bin",  0x080000, 0xb7b925bd, 5 | BRF_SND },		 //  9 Sound data
	{ "002-v12.bin",  0x080000, 0x329f26fc, 5 | BRF_SND },		 // 10
	{ "002-v13.bin",  0x080000, 0x0c39f3c8, 5 | BRF_SND },		 // 11
	{ "002-v14.bin",  0x080000, 0xc7e11c38, 5 | BRF_SND },		 // 12
	{ "002-v21.bin",  0x080000, 0x04a733d1, 6 | BRF_SND },		 // 13
};

STDROMPICKEXT(bstars, bstars, neogeo);
STD_ROM_FN(bstars);

struct BurnDriver BurnDrvBstars = {
	"bstars", NULL, "neogeo", "1990",
	"Baseball Stars Professional\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, bstarsRomInfo, bstarsRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Top Player's Golf

static struct BurnRomInfo tpgolfRomDesc[] = {
	{ "003-p1.bin",   0x080000, 0xf75549ba, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "003-p2.bin",   0x080000, 0xb7809a8f, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "003-s1.bin",   0x020000, 0x7b3eb9b1, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "003-c1.bin",   0x080000, 0x0315fbaf, 3 | BRF_GRA },		 //  3 Sprite data
	{ "003-c2.bin",   0x080000, 0xb4c15d59, 3 | BRF_GRA },		 //  4
	{ "003-c3.bin",   0x080000, 0xb09f1612, 3 | BRF_GRA },		 //  5
	{ "003-c4.bin",   0x080000, 0x150ea7a1, 3 | BRF_GRA },		 //  6
	{ "003-c5.bin",   0x080000, 0x9a7146da, 3 | BRF_GRA },		 //  7
	{ "003-c6.bin",   0x080000, 0x1e63411a, 3 | BRF_GRA },		 //  8
	{ "003-c7.bin",   0x080000, 0x2886710c, 3 | BRF_GRA },		 //  9
	{ "003-c8.bin",   0x080000, 0x422af22d, 3 | BRF_GRA },		 // 10

	{ "003-m1.bin",   0x010000, 0x7851d0d9, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "003-v11.bin",  0x080000, 0xff97f1cb, 5 | BRF_SND },		 // 12 Sound data
	{ "003-v21.bin",  0x080000, 0xd34960c6, 6 | BRF_SND },		 // 13
	{ "003-v22.bin",  0x080000, 0x9a5f58d4, 6 | BRF_SND },		 // 14
	{ "003-v23.bin",  0x080000, 0x30f53e54, 6 | BRF_SND },		 // 15
	{ "003-v24.bin",  0x080000, 0x5ba0f501, 6 | BRF_SND },		 // 16
};

STDROMPICKEXT(tpgolf, tpgolf, neogeo);
STD_ROM_FN(tpgolf);

struct BurnDriver BurnDrvTpgolf = {
	"tpgolf", NULL, "neogeo", "1990",
	"Top Player's Golf\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, tpgolfRomInfo, tpgolfRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Mahjong Kyoretsuden

static struct BurnRomInfo mahretsuRomDesc[] = {
	{ "004-p1.bin",   0x080000, 0xfc6f53db, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "004-s1.bin",   0x010000, 0xb0d16529, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "004-c1.bin",   0x080000, 0xf1ae16bc, 3 | BRF_GRA },		 //  2 Sprite data
	{ "004-c2.bin",   0x080000, 0xbdc13520, 3 | BRF_GRA },		 //  3
	{ "004-c3.bin",   0x080000, 0x9c571a37, 3 | BRF_GRA },		 //  4
	{ "004-c4.bin",   0x080000, 0x7e81cb29, 3 | BRF_GRA },		 //  5

	{ "004-m1.bin",   0x010000, 0x37965a73, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "004-v1.bin",   0x080000, 0xb2fb2153, 5 | BRF_SND },		 //  7 Sound data
	{ "004-v2.bin",   0x080000, 0x8503317b, 5 | BRF_SND },		 //  8
	{ "004-v3.bin",   0x080000, 0x4999fb27, 5 | BRF_SND },		 //  9
	{ "004-v4.bin",   0x080000, 0x776fa2a2, 5 | BRF_SND },		 // 10
	{ "004-v5.bin",   0x080000, 0xb3e7eeea, 5 | BRF_SND },		 // 11
};

STDROMPICKEXT(mahretsu, mahretsu, neogeo);
STD_ROM_FN(mahretsu);

struct BurnDriver BurnDrvMahretsu = {
	"mahretsu", NULL, "neogeo", "1990",
	"Mahjong Kyoretsuden - real mah-jong game\0", NULL, "SNK", "Neo Geo",
	L"\u9EBB\u96C0\u72C2\u5217\u4F1D - real mah-jong game\0Mahjong Kyoretsuden\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_MAHJONG,
	NULL, mahretsuRomInfo, mahretsuRomName, neomahjongInputInfo, neomahjongDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Magician Lord

static struct BurnRomInfo maglordRomDesc[] = {
	{ "005-p1.bin",   0x080000, 0xBD0A492D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "005-s1.bin",   0x020000, 0x1C5369A2, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "005-c1.bin",   0x080000, 0x806AEE34, 3 | BRF_GRA },		 //  2 Sprite data
	{ "005-c2.bin",   0x080000, 0x34AA9A86, 3 | BRF_GRA },		 //  3
	{ "005-c3.bin",   0x080000, 0xC4C2B926, 3 | BRF_GRA },		 //  4
	{ "005-c4.bin",   0x080000, 0x9C46DCF4, 3 | BRF_GRA },		 //  5
	{ "005-c5.bin",   0x080000, 0x69086DEC, 3 | BRF_GRA },		 //  6
	{ "005-c6.bin",   0x080000, 0xAB7AC142, 3 | BRF_GRA },		 //  7

	{ "005-m1.bin",   0x010000, 0x91EE1F73, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "005-v11.bin",  0x080000, 0xCC0455FD, 5 | BRF_SND },		 //  9 Sound data
	{ "005-v21.bin",  0x080000, 0xF94AB5B7, 6 | BRF_SND },		 // 10
	{ "005-v22.bin",  0x080000, 0x232CFD04, 6 | BRF_SND },		 // 11
};

STDROMPICKEXT(maglord, maglord, neogeo);
STD_ROM_FN(maglord);

struct BurnDriver BurnDrvMagLord = {
	"maglord", NULL, "neogeo", "1990",
	"Magician Lord (set 1)\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, maglordRomInfo, maglordRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Magician Lord (aes version)

static struct BurnRomInfo maglordhRomDesc[] = {
	{ "005-p1h.bin",  0x080000, 0x599043C5, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "005-s1.bin",   0x020000, 0x1C5369A2, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "005-c1.bin",   0x080000, 0x806AEE34, 3 | BRF_GRA },		 //  2 Sprite data
	{ "005-c2.bin",   0x080000, 0x34AA9A86, 3 | BRF_GRA },		 //  3
	{ "005-c3.bin",   0x080000, 0xC4C2B926, 3 | BRF_GRA },		 //  4
	{ "005-c4.bin",   0x080000, 0x9C46DCF4, 3 | BRF_GRA },		 //  5
	{ "005-c5.bin",   0x080000, 0x69086DEC, 3 | BRF_GRA },		 //  6
	{ "005-c6.bin",   0x080000, 0xAB7AC142, 3 | BRF_GRA },		 //  7

	{ "005-m1.bin",   0x010000, 0x91EE1F73, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "005-v11.bin",  0x080000, 0xCC0455FD, 5 | BRF_SND },		 //  9 Sound data
	{ "005-v21.bin",  0x080000, 0xF94AB5B7, 6 | BRF_SND },		 // 10
	{ "005-v22.bin",  0x080000, 0x232CFD04, 6 | BRF_SND },		 // 11
};

STDROMPICKEXT(maglordh, maglordh, neogeo);
STD_ROM_FN(maglordh);

struct BurnDriver BurnDrvMagLordh = {
	"maglordh", "maglord", "neogeo", "1990",
	"Magician Lord (set 2)\0", "AES version", "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, maglordhRomInfo, maglordhRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Riding Hero

static struct BurnRomInfo ridheroRomDesc[] = {
	{ "006-p1.bin",   0x080000, 0xd4aaf597, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "006-s1.bin",   0x010000, 0x197d1a28, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "006-c1.bin",   0x080000, 0x4a5c7f78, 3 | BRF_GRA },		 //  2 Sprite data
	{ "006-c2.bin",   0x080000, 0xe0b70ece, 3 | BRF_GRA },		 //  3
	{ "006-c3.bin",   0x080000, 0x8acff765, 3 | BRF_GRA },		 //  4
	{ "006-c4.bin",   0x080000, 0x205e3208, 3 | BRF_GRA },		 //  5

	{ "006-m1.bin",   0x020000, 0xf0b6425d, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "006-v11.bin",  0x080000, 0xcdf74a42, 5 | BRF_SND },		 //  7 Sound data
	{ "006-v12.bin",  0x080000, 0xe2fd2371, 5 | BRF_SND },		 //  8
	{ "006-v21.bin",  0x080000, 0x94092bce, 6 | BRF_SND },		 //  9
	{ "006-v22.bin",  0x080000, 0x4e2cd7c3, 6 | BRF_SND },		 // 10
	{ "006-v23.bin",  0x080000, 0x069c71ed, 6 | BRF_SND },		 // 11
	{ "006-v24.bin",  0x080000, 0x89fbb825, 6 | BRF_SND },		 // 12
};

STDROMPICKEXT(ridhero, ridhero, neogeo);
STD_ROM_FN(ridhero);

struct BurnDriver BurnDrvRidhero = {
	"ridhero", NULL, "neogeo", "1990",
	"Riding Hero (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, ridheroRomInfo, ridheroRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Riding Hero (aes version)

static struct BurnRomInfo ridherohRomDesc[] = {
	{ "006-p1h.bin",  0x080000, 0x52445646, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "006-s1.bin",   0x010000, 0x197d1a28, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "006-c1.bin",   0x080000, 0x4a5c7f78, 3 | BRF_GRA },		 //  2 Sprite data
	{ "006-c2.bin",   0x080000, 0xe0b70ece, 3 | BRF_GRA },		 //  3
	{ "006-c3.bin",   0x080000, 0x8acff765, 3 | BRF_GRA },		 //  4
	{ "006-c4.bin",   0x080000, 0x205e3208, 3 | BRF_GRA },		 //  5

	{ "006-m1.bin",   0x020000, 0xf0b6425d, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "006-v11.bin",  0x080000, 0xcdf74a42, 5 | BRF_SND },		 //  7 Sound data
	{ "006-v12.bin",  0x080000, 0xe2fd2371, 5 | BRF_SND },		 //  8
	{ "006-v21.bin",  0x080000, 0x94092bce, 6 | BRF_SND },		 //  9
	{ "006-v22.bin",  0x080000, 0x4e2cd7c3, 6 | BRF_SND },		 // 10
	{ "006-v23.bin",  0x080000, 0x069c71ed, 6 | BRF_SND },		 // 11
	{ "006-v24.bin",  0x080000, 0x89fbb825, 6 | BRF_SND },		 // 12
};

STDROMPICKEXT(ridheroh, ridheroh, neogeo);
STD_ROM_FN(ridheroh);

struct BurnDriver BurnDrvRidheroh = {
	"ridheroh", "ridhero", "neogeo", "1990",
	"Riding Hero (set 2)\0", "AES version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, ridherohRomInfo, ridherohRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Alpha Mission II

static struct BurnRomInfo alpham2RomDesc[] = {
	{ "007-p1.bin",   0x080000, 0x5b266f47, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "007-p2.bin",   0x020000, 0xeb9c1044, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "007-s1.bin",   0x020000, 0x85ec9acf, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "007-c1.bin",   0x100000, 0x8fba8ff3, 3 | BRF_GRA },		 //  3 Sprite data
	{ "007-c2.bin",   0x100000, 0x4dad2945, 3 | BRF_GRA },		 //  4
	{ "007-c3.bin",   0x080000, 0x68c2994e, 3 | BRF_GRA },		 //  5
	{ "007-c4.bin",   0x080000, 0x7d588349, 3 | BRF_GRA },		 //  6

	{ "007-m1.bin",   0x020000, 0x28dfe2cd, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "007-v1.bin",   0x100000, 0xcd5db931, 5 | BRF_SND },		 //  8 Sound data
	{ "007-v2.bin",   0x100000, 0x63e9b574, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(alpham2, alpham2, neogeo);
STD_ROM_FN(alpham2);

struct BurnDriver BurnDrvAlpham2 = {
	"alpham2", NULL, "neogeo", "1991",
	"Alpha Mission II\0ASO II - last guardian\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, alpham2RomInfo, alpham2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0008 Sunshine (prototype) 1990 SNK


// Ninja Combat

static struct BurnRomInfo ncombatRomDesc[] = {
	{ "009-p1.bin",   0x080000, 0xB45FCFBF, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "009-s1.bin",   0x020000, 0xD49AFEE8, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "009-c1.bin",   0x080000, 0x33CC838E, 3 | BRF_GRA },		 //  2 Sprite data
	{ "009-c2.bin",   0x080000, 0x26877FEB, 3 | BRF_GRA },		 //  3
	{ "009-c3.bin",   0x080000, 0x3B60A05D, 3 | BRF_GRA },		 //  4
	{ "009-c4.bin",   0x080000, 0x39C2D039, 3 | BRF_GRA },		 //  5
	{ "009-c5.bin",   0x080000, 0x67A4344E, 3 | BRF_GRA },		 //  6
	{ "009-c6.bin",   0x080000, 0x2ECA8B19, 3 | BRF_GRA },		 //  7

	{ "009-m1.bin",   0x020000, 0xB5819863, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "009-v11.bin",  0x080000, 0xCF32A59C, 5 | BRF_SND },		 //  9 Sound data
	{ "009-v12.bin",  0x080000, 0x7B3588B7, 5 | BRF_SND },		 // 10
	{ "009-v13.bin",  0x080000, 0x505A01B5, 5 | BRF_SND },		 // 11
	{ "009-v21.bin",  0x080000, 0x365F9011, 6 | BRF_SND },		 // 12
};

STDROMPICKEXT(ncombat, ncombat, neogeo);
STD_ROM_FN(ncombat);

struct BurnDriver BurnDrvNCombat = {
	"ncombat", NULL, "neogeo", "1990",
	"Ninja Combat (set 1)\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ncombatRomInfo, ncombatRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ninja Combat (alternate version)

static struct BurnRomInfo ncombataRomDesc[] = {
	{ "009-pg1.bin",  0x080000, 0x8E9F0ADD, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "009-s1.bin",   0x020000, 0xD49AFEE8, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "009-c1.bin",   0x080000, 0x33CC838E, 3 | BRF_GRA },		 //  2 Sprite data
	{ "009-c2.bin",   0x080000, 0x26877FEB, 3 | BRF_GRA },		 //  3
	{ "009-c3.bin",   0x080000, 0x3B60A05D, 3 | BRF_GRA },		 //  4
	{ "009-c4.bin",   0x080000, 0x39C2D039, 3 | BRF_GRA },		 //  5
	{ "009-c5.bin",   0x080000, 0x67A4344E, 3 | BRF_GRA },		 //  6
	{ "009-c6.bin",   0x080000, 0x2ECA8B19, 3 | BRF_GRA },		 //  7

	{ "009-m1.bin",   0x020000, 0xB5819863, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "009-v11.bin",  0x080000, 0xCF32A59C, 5 | BRF_SND },		 //  9 Sound data
	{ "009-v12.bin",  0x080000, 0x7B3588B7, 5 | BRF_SND },		 // 10
	{ "009-v13.bin",  0x080000, 0x505A01B5, 5 | BRF_SND },		 // 11
	{ "009-v21.bin",  0x080000, 0x365F9011, 6 | BRF_SND },		 // 12
};

STDROMPICKEXT(ncombata, ncombata, neogeo);
STD_ROM_FN(ncombata);

struct BurnDriver BurnDrvNCombata = {
	"ncombata", "ncombat", "neogeo", "1990",
	"Ninja Combat (set 2)\0", "Alternate version", "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ncombataRomInfo, ncombataRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Cyber-Lip

static struct BurnRomInfo cyberlipRomDesc[] = {
	{ "010-p1.bin",   0x080000, 0x69a6b42d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "010-s1.bin",   0x020000, 0x79a35264, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "010-c1.bin",   0x080000, 0x8bba5113, 3 | BRF_GRA },		 //  2 Sprite data
	{ "010-c2.bin",   0x080000, 0xcbf66432, 3 | BRF_GRA },		 //  3
	{ "010-c3.bin",   0x080000, 0xe4f86efc, 3 | BRF_GRA },		 //  4
	{ "010-c4.bin",   0x080000, 0xf7be4674, 3 | BRF_GRA },		 //  5
	{ "010-c5.bin",   0x080000, 0xe8076da0, 3 | BRF_GRA },		 //  6
	{ "010-c6.bin",   0x080000, 0xc495c567, 3 | BRF_GRA },		 //  7

	{ "010-m1.bin",   0x010000, 0x47980d3a, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "010-v11.bin",  0x080000, 0x90224d22, 5 | BRF_SND },		 //  9 Sound data
	{ "010-v12.bin",  0x080000, 0xa0cf1834, 5 | BRF_SND },		 // 10
	{ "010-v13.bin",  0x080000, 0xae38bc84, 5 | BRF_SND },		 // 11
	{ "010-v14.bin",  0x080000, 0x70899bd2, 5 | BRF_SND },		 // 12
	{ "010-v21.bin",  0x080000, 0x586f4cb2, 6 | BRF_SND },		 // 13
};

STDROMPICKEXT(cyberlip, cyberlip, neogeo);
STD_ROM_FN(cyberlip);

struct BurnDriver BurnDrvCyberlip = {
	"cyberlip", NULL, "neogeo", "1990",
	"Cyber-Lip\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, cyberlipRomInfo, cyberlipRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The Super Spy

static struct BurnRomInfo superspyRomDesc[] = {
	{ "011-p1.bin",   0x080000, 0xc7f944b5, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "011-p2.bin",   0x020000, 0x811a4faf, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "011-s1.bin",   0x020000, 0xec5fdb96, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "011-c1.bin",   0x100000, 0xcae7be57, 3 | BRF_GRA },		 //  3 Sprite data
	{ "011-c2.bin",   0x100000, 0x9e29d986, 3 | BRF_GRA },		 //  4
	{ "011-c3.bin",   0x100000, 0x14832ff2, 3 | BRF_GRA },		 //  5
	{ "011-c4.bin",   0x100000, 0xb7f63162, 3 | BRF_GRA },		 //  6

	{ "011-m1.bin",   0x020000, 0xd59d5d12, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "011-v11.bin",  0x100000, 0x5c674d5c, 5 | BRF_SND },		 //  8 Sound data
	{ "011-v12.bin",  0x100000, 0x7df8898b, 5 | BRF_SND },		 //  9
	{ "011-v21.bin",  0x100000, 0x1ebe94c7, 6 | BRF_SND },		 // 10
};

STDROMPICKEXT(superspy, superspy, neogeo);
STD_ROM_FN(superspy);

struct BurnDriver BurnDrvSuperspy = {
	"superspy", NULL, "neogeo", "1990",
	"The Super Spy\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, superspyRomInfo, superspyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0012?
// 0013?


// Mutation Nation

static struct BurnRomInfo mutnatRomDesc[] = {
	{ "014-p1.bin",   0x080000, 0x6f1699c8, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "014-s1.bin",   0x020000, 0x99419733, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "014-c1.bin",   0x100000, 0x5e4381bf, 3 | BRF_GRA },		 //  2 Sprite data
	{ "014-c2.bin",   0x100000, 0x69ba4e18, 3 | BRF_GRA },		 //  3
	{ "014-c3.bin",   0x100000, 0x890327d5, 3 | BRF_GRA },		 //  4
	{ "014-c4.bin",   0x100000, 0xe4002651, 3 | BRF_GRA },		 //  5

	{ "014-m1.bin",   0x020000, 0xb6683092, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "014-v1.bin",   0x100000, 0x25419296, 5 | BRF_SND },		 //  7 Sound data
	{ "014-v2.bin",   0x100000, 0x0de53d5e, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(mutnat, mutnat, neogeo);
STD_ROM_FN(mutnat);

struct BurnDriver BurnDrvMutnat = {
	"mutnat", NULL, "neogeo", "1992",
	"Mutation Nation\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, mutnatRomInfo, mutnatRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0015


// King of the Monsters

static struct BurnRomInfo kotmRomDesc[] = {
	{ "016-p1.bin",   0x080000, 0x1B818731, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "016-p2.bin",   0x020000, 0x12AFDC2B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "016-s1.bin",   0x020000, 0x1A2EEEB3, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "016-c1.bin",   0x100000, 0x71471C25, 3 | BRF_GRA },		 //  3 Sprite data
	{ "016-c2.bin",   0x100000, 0x320DB048, 3 | BRF_GRA },		 //  4
	{ "016-c3.bin",   0x100000, 0x98DE7995, 3 | BRF_GRA },		 //  5
	{ "016-c4.bin",   0x100000, 0x070506E2, 3 | BRF_GRA },		 //  6

	{ "016-m1.bin",   0x020000, 0x0296ABCB, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "016-v1.bin",   0x100000, 0x86C0A502, 5 | BRF_SND },		 //  8 Sound data
	{ "016-v2.bin",   0x100000, 0x5BC23EC5, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(kotm, kotm, neogeo);
STD_ROM_FN(kotm);

struct BurnDriver BurnDrvKotm = {
	"kotm", NULL, "neogeo", "1991",
	"King of the Monsters (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, kotmRomInfo, kotmRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// King of the Monsters (aes version)

static struct BurnRomInfo kotmhRomDesc[] = {
	{ "016-hp1.bin",  0x080000, 0xB774621E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "016-p2.bin",   0x020000, 0x12AFDC2B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "016-s1.bin",   0x020000, 0x1A2EEEB3, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "016-c1.bin",   0x100000, 0x71471C25, 3 | BRF_GRA },		 //  3 Sprite data
	{ "016-c2.bin",   0x100000, 0x320DB048, 3 | BRF_GRA },		 //  4
	{ "016-c3.bin",   0x100000, 0x98DE7995, 3 | BRF_GRA },		 //  5
	{ "016-c4.bin",   0x100000, 0x070506E2, 3 | BRF_GRA },		 //  6

	{ "016-m1.bin",   0x020000, 0x0296ABCB, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "016-v1.bin",   0x100000, 0x86C0A502, 5 | BRF_SND },		 //  8 Sound data
	{ "016-v2.bin",   0x100000, 0x5BC23EC5, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(kotmh, kotmh, neogeo);
STD_ROM_FN(kotmh);

struct BurnDriver BurnDrvKotmh = {
	"kotmh", "kotm", "neogeo", "1991",
	"King of the Monsters (set 2)\0", "AES version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kotmhRomInfo, kotmhRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sengoku

static struct BurnRomInfo sengokuRomDesc[] = {
	{ "017-p1.bin",   0x080000, 0xf8a63983, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "017-p2.bin",   0x020000, 0x3024bbb3, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "017-s1.bin",   0x020000, 0xb246204d, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "017-c1.bin",   0x100000, 0xb4eb82a1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "017-c2.bin",   0x100000, 0xd55c550d, 3 | BRF_GRA },		 //  4
	{ "017-c3.bin",   0x100000, 0xed51ef65, 3 | BRF_GRA },		 //  5
	{ "017-c4.bin",   0x100000, 0xf4f3c9cb, 3 | BRF_GRA },		 //  6

	{ "017-m1.bin",   0x020000, 0x9b4f34c6, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "017-v1.bin",   0x100000, 0x23663295, 5 | BRF_SND },		 //  8 Sound data
	{ "017-v2.bin",   0x100000, 0xf61e6765, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(sengoku, sengoku, neogeo);
STD_ROM_FN(sengoku);

struct BurnDriver BurnDrvSengoku = {
	"sengoku", NULL, "neogeo", "1991",
	"Sengoku\0Sengoku Denshou (set 1)\0", NULL, "SNK", "Neo Geo",
	L"Sengoku\0\u6226\u56FD\u4F1D\u627F\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, sengokuRomInfo, sengokuRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sengoku (aes version)

static struct BurnRomInfo sengokhRomDesc[] = {
	{ "017-p1h.bin",  0x080000, 0x33eccae0, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "017-p2.bin",   0x020000, 0x3024bbb3, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "017-s1.bin",   0x020000, 0xb246204d, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "017-c1.bin",   0x100000, 0xb4eb82a1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "017-c2.bin",   0x100000, 0xd55c550d, 3 | BRF_GRA },		 //  4
	{ "017-c3.bin",   0x100000, 0xed51ef65, 3 | BRF_GRA },		 //  5
	{ "017-c4.bin",   0x100000, 0xf4f3c9cb, 3 | BRF_GRA },		 //  6

	{ "017-m1.bin",   0x020000, 0x9b4f34c6, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "017-v1.bin",   0x100000, 0x23663295, 5 | BRF_SND },		 //  8 Sound data
	{ "017-v2.bin",   0x100000, 0xf61e6765, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(sengokh, sengokh, neogeo);
STD_ROM_FN(sengokh);

struct BurnDriver BurnDrvSengokh = {
	"sengokh", "sengoku", "neogeo", "1991",
	"Sengoku\0Sengoku Denshou (set 2)\0", "AES version", "SNK", "Neo Geo",
	L"Sengoku\0\u6226\u56FD\u4F1D\u627F\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, sengokhRomInfo, sengokhRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Burning Fight

static struct BurnRomInfo burningfRomDesc[] = {
	{ "018-p1.bin",   0x080000, 0x4092c8db, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "018-s1.bin",   0x020000, 0x6799ea0d, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "018-c1.bin",   0x100000, 0x25a25e9b, 3 | BRF_GRA },		 //  2 Sprite data
	{ "018-c2.bin",   0x100000, 0xd4378876, 3 | BRF_GRA },		 //  3
	{ "018-c3.bin",   0x100000, 0x862b60da, 3 | BRF_GRA },		 //  4
	{ "018-c4.bin",   0x100000, 0xe2e0aff7, 3 | BRF_GRA },		 //  5

	{ "018-m1.bin",   0x020000, 0x0c939ee2, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "018-v1.bin",   0x100000, 0x508c9ffc, 5 | BRF_SND },		 //  7 Sound data
	{ "018-v2.bin",   0x100000, 0x854ef277, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(burningf, burningf, neogeo);
STD_ROM_FN(burningf);

struct BurnDriver BurnDrvBurningf = {
	"burningf", NULL, "neogeo", "1991",
	"Burning Fight (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, burningfRomInfo, burningfRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Burning Fight (aes version)

static struct BurnRomInfo burninghRomDesc[] = {
	{ "018-p1h.bin",  0x080000, 0xddffcbf4, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "018-s1.bin",   0x020000, 0x6799ea0d, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "018-c1.bin",   0x100000, 0x25a25e9b, 3 | BRF_GRA },		 //  2 Sprite data
	{ "018-c2.bin",   0x100000, 0xd4378876, 3 | BRF_GRA },		 //  3
	{ "018-c3.bin",   0x100000, 0x862b60da, 3 | BRF_GRA },		 //  4
	{ "018-c4.bin",   0x100000, 0xe2e0aff7, 3 | BRF_GRA },		 //  5

	{ "018-m1.bin",   0x020000, 0x0c939ee2, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "018-v1.bin",   0x100000, 0x508c9ffc, 5 | BRF_SND },		 //  7 Sound data
	{ "018-v2.bin",   0x100000, 0x854ef277, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(burningh, burningh, neogeo);
STD_ROM_FN(burningh);

struct BurnDriver BurnDrvBurningh = {
	"burningh", "burningf", "neogeo", "1991",
	"Burning Fight (set 2)\0", "AES version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, burninghRomInfo, burninghRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// League Bowling

static struct BurnRomInfo lbowlingRomDesc[] = {
	{ "019-p1.bin",   0x080000, 0xa2de8445, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "019-s1.bin",   0x020000, 0x5fcdc0ed, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "019-c1.bin",   0x080000, 0x4ccdef18, 3 | BRF_GRA },		 //  2 Sprite data
	{ "019-c2.bin",   0x080000, 0xd4dd0802, 3 | BRF_GRA },		 //  3

	{ "019-m1.bin",   0x020000, 0x589d7f25, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "019-v11.bin",  0x080000, 0x0fb74872, 5 | BRF_SND },		 //  5 Sound data
	{ "019-v12.bin",  0x080000, 0x029faa57, 5 | BRF_SND },		 //  6
	{ "019-v21.bin",  0x080000, 0x2efd5ada, 6 | BRF_SND },		 //  7
};

STDROMPICKEXT(lbowling, lbowling, neogeo);
STD_ROM_FN(lbowling);

struct BurnDriver BurnDrvLbowling = {
	"lbowling", NULL, "neogeo", "1990",
	"League Bowling\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, lbowlingRomInfo, lbowlingRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ghost Pilots

static struct BurnRomInfo gpilotsRomDesc[] = {
	{ "020-p1.bin",   0x080000, 0xe6f2fe64, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "020-p2.bin",   0x020000, 0xedcb22ac, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "020-s1.bin",   0x020000, 0xa6d83d53, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "020-c1.bin",   0x100000, 0xbd6fe78e, 3 | BRF_GRA },		 //  3 Sprite data
	{ "020-c2.bin",   0x100000, 0x5f4a925c, 3 | BRF_GRA },		 //  4
	{ "020-c3.bin",   0x100000, 0xd1e42fd0, 3 | BRF_GRA },		 //  5
	{ "020-c4.bin",   0x100000, 0xedde439b, 3 | BRF_GRA },		 //  6

	{ "020-m1.bin",   0x020000, 0x48409377, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "020-v11.bin",  0x100000, 0x1b526c8b, 5 | BRF_SND },		 //  8 Sound data
	{ "020-v12.bin",  0x080000, 0x4a9e6f03, 5 | BRF_SND },		 //  9
	{ "020-v21.bin",  0x080000, 0x7abf113d, 6 | BRF_SND },		 // 10
};

STDROMPICKEXT(gpilots, gpilots, neogeo);
STD_ROM_FN(gpilots);

struct BurnDriver BurnDrvGpilots = {
	"gpilots", NULL, "neogeo", "1991",
	"Ghost Pilots\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, gpilotsRomInfo, gpilotsRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzled \ Joy Joy Kid

static struct BurnRomInfo joyjoyRomDesc[] = {
	{ "021-p1.bin",   0x080000, 0x39c3478f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "021-s1.bin",   0x020000, 0x6956d778, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "021-c1.bin",   0x080000, 0x509250ec, 3 | BRF_GRA },		 //  2 Sprite data
	{ "021-c2.bin",   0x080000, 0x09ed5258, 3 | BRF_GRA },		 //  3

	{ "021-m1.bin",   0x010000, 0x058683ec, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "021-v1.bin",   0x080000, 0x66c1e5c4, 5 | BRF_SND },		 //  5 Sound data
	{ "021-v2.bin",   0x080000, 0x8ed20a86, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(joyjoy, joyjoy, neogeo);
STD_ROM_FN(joyjoy);

struct BurnDriver BurnDrvJoyjoy = {
	"joyjoy", NULL, "neogeo", "1990",
	"Puzzled\0Joy Joy Kid\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, joyjoyRomInfo, joyjoyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Blue's Journey \ Raguy

static struct BurnRomInfo bjourneyRomDesc[] = {
	{ "022-p1.bin",   0x100000, 0x6A2F6D4A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "022-s1.bin",   0x020000, 0x843C3624, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "022-c1.bin",   0x100000, 0x4D47A48C, 3 | BRF_GRA },		 //  2 Sprite data
	{ "022-c2.bin",   0x100000, 0xE8C1491A, 3 | BRF_GRA },		 //  3
	{ "022-c3.bin",   0x080000, 0x66E69753, 3 | BRF_GRA },		 //  4
	{ "022-c4.bin",   0x080000, 0x71BFD48A, 3 | BRF_GRA },		 //  5

	{ "022-m1.bin",   0x010000, 0xA9E30496, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "022-v11.bin",  0x100000, 0x2CB4AD91, 5 | BRF_SND },		 //  7 Sound data
	{ "022-v22.bin",  0x100000, 0x65A54D13, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(bjourney, bjourney, neogeo);
STD_ROM_FN(bjourney);

struct BurnDriver BurnDrvBJourney = {
	"bjourney", NULL, "neogeo", "1990",
	"Blue's Journey\0Raguy\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, bjourneyRomInfo, bjourneyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Quiz Daisousa Sen

static struct BurnRomInfo quizdaisRomDesc[] = {
	{ "023-p1.bin",   0x100000, 0xc488fda3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "023-s1.bin",   0x020000, 0xac31818a, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "023-c1.bin",   0x100000, 0x2999535a, 3 | BRF_GRA },		 //  2 Sprite data
	{ "023-c2.bin",   0x100000, 0x876a99e6, 3 | BRF_GRA },		 //  3

	{ "023-m1.bin",   0x020000, 0x2a2105e0, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "023-v1.bin",   0x100000, 0xa53e5bd3, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(quizdais, quizdais, neogeo);
STD_ROM_FN(quizdais);

struct BurnDriver BurnDrvQuizdais = {
	"quizdais", NULL, "neogeo", "1991",
	"Quiz Daisousa Sen - the last count down\0", NULL, "SNK", "Neo Geo",
	L"\u30AF\u30A4\u30BA\u5927\u635C\u67FB\u7DDA - the last count down\0Quiz Daisousa Sen\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, quizdaisRomInfo, quizdaisRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Last Resort

static struct BurnRomInfo lresortRomDesc[] = {
	{ "024-p1.bin",   0x080000, 0x89c4ab97, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "024-s1.bin",   0x020000, 0x5cef5cc6, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "024-c1.bin",   0x100000, 0x3617c2dc, 3 | BRF_GRA },		 //  2 Sprite data
	{ "024-c2.bin",   0x100000, 0x3f0a7fd8, 3 | BRF_GRA },		 //  3
	{ "024-c3.bin",   0x080000, 0xe9f745f8, 3 | BRF_GRA },		 //  4
	{ "024-c4.bin",   0x080000, 0x7382fefb, 3 | BRF_GRA },		 //  5

	{ "024-m1.bin",   0x020000, 0xcec19742, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "024-v1.bin",   0x100000, 0xefdfa063, 5 | BRF_SND },		 //  7 Sound data
	{ "024-v2.bin",   0x100000, 0x3c7997c0, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(lresort, lresort, neogeo);
STD_ROM_FN(lresort);

struct BurnDriver BurnDrvLresort = {
	"lresort", NULL, "neogeo", "1992",
	"Last Resort\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, lresortRomInfo, lresortRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Eight Man

static struct BurnRomInfo eightmanRomDesc[] = {
	{ "025-p1.bin",   0x080000, 0x43344cb0, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "025-s1.bin",   0x020000, 0xa402202b, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "025-c1.bin",   0x100000, 0x555e16a4, 3 | BRF_GRA },		 //  2 Sprite data
	{ "025-c2.bin",   0x100000, 0xe1ee51c3, 3 | BRF_GRA },		 //  3
	{ "025-c3.bin",   0x080000, 0x0923d5b0, 3 | BRF_GRA },		 //  4
	{ "025-c4.bin",   0x080000, 0xe3eca67b, 3 | BRF_GRA },		 //  5

	{ "025-m1.bin",   0x020000, 0x9927034c, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "025-v1.bin",   0x100000, 0x4558558a, 5 | BRF_SND },		 //  7 Sound data
	{ "025-v2.bin",   0x100000, 0xc5e052e9, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(eightman, eightman, neogeo);
STD_ROM_FN(eightman);

struct BurnDriver BurnDrvEightman = {
	"eightman", NULL, "neogeo", "1991",
	"Eight Man\0", NULL, "SNK / Pallas", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, eightmanRomInfo, eightmanRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0026 Fun Fun Brothers (prototype) 1991 Alpha


// Minnasanno Okagesamadesu

static struct BurnRomInfo minasanRomDesc[] = {
	{ "027-p1.bin",   0x080000, 0xC8381327, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "027-s1.bin",   0x020000, 0xE5824BAA, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "027-c1.bin",   0x100000, 0xD0086F94, 3 | BRF_GRA },		 //  2 Sprite data
	{ "027-c2.bin",   0x100000, 0xDA61F5A6, 3 | BRF_GRA },		 //  3
	{ "027-c3.bin",   0x100000, 0x08DF1228, 3 | BRF_GRA },		 //  4
	{ "027-c4.bin",   0x100000, 0x54E87696, 3 | BRF_GRA },		 //  5

	{ "027-m1.bin",   0x020000, 0xADD5A226, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "027-v11.bin",  0x100000, 0x59AD4459, 5 | BRF_SND },		 //  7 Sound data
	{ "027-v21.bin",  0x100000, 0xDF5B4EEB, 6 | BRF_SND },		 //  8
};

STDROMPICKEXT(minasan, minasan, neogeo);
STD_ROM_FN(minasan);

struct BurnDriver BurnDrvMinasan = {
	"minasan", NULL, "neogeo", "1990",
	"Minnasanno Okagesamadesu\0", NULL, "Monolith Corp.", "Neo Geo",
	L"\u307F\u306A\u3055\u3093\u306E\u304A\u304B\u3052\u3055\u307E\u3067\u3059\uFF01\0Minnasanno Okagesamadesu\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_MAHJONG,
	NULL, minasanRomInfo, minasanRomName, neomahjongInputInfo, neomahjongDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0028 Dunk Star (prototype) Sammy


// Legend of Success Joe

static struct BurnRomInfo legendosRomDesc[] = {
	{ "029-p1.bin",   0x080000, 0x9d563f19, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "029-s1.bin",   0x020000, 0xbcd502f0, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "029-c1.bin",   0x100000, 0x2f5ab875, 3 | BRF_GRA },		 //  2 Sprite data
	{ "029-c2.bin",   0x100000, 0x318b2711, 3 | BRF_GRA },		 //  3
	{ "029-c3.bin",   0x100000, 0x6bc52cb2, 3 | BRF_GRA },		 //  4
	{ "029-c4.bin",   0x100000, 0x37ef298c, 3 | BRF_GRA },		 //  5

	{ "029-m1.bin",   0x010000, 0x909d4ed9, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "029-v1.bin",   0x100000, 0x85065452, 5 | BRF_SND },		 //  7 Sound data
};

STDROMPICKEXT(legendos, legendos, neogeo);
STD_ROM_FN(legendos);

struct BurnDriver BurnDrvLegendos = {
	"legendos", NULL, "neogeo", "1991",
	"Legend of Success Joe\0Ashitano Joe Densetsu\0", NULL, "SNK", "Neo Geo",
	L"Legend of Success Joe\0\u3042\u3057\u305F\u306E\u30B8\u30E7\u30FC\u4F1D\u8AAC\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, legendosRomInfo, legendosRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// 2020 Super Baseball

static struct BurnRomInfo bb2020RomDesc[] = {
	{ "030-p1.bin",   0x080000, 0xD396C9CB, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "030-s1.bin",   0x020000, 0x7015B8FC, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "030-c1.bin",   0x100000, 0x4f5E19BD, 3 | BRF_GRA },		 //  2 Sprite data
	{ "030-c2.bin",   0x100000, 0xD6314BF0, 3 | BRF_GRA },		 //  3
	{ "030-c3.bin",   0x100000, 0x47FDDFEE, 3 | BRF_GRA },		 //  4
	{ "030-c4.bin",   0x100000, 0x780D1C4E, 3 | BRF_GRA },		 //  5

	{ "030-m1.bin",   0x020000, 0x4CF466EC, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "030-v1.bin",   0x100000, 0xD4CA364E, 5 | BRF_SND },		 //  7 Sound data
	{ "030-v2.bin",   0x100000, 0x54994455, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(bb2020, bb2020, neogeo);
STD_ROM_FN(bb2020);

struct BurnDriver BurnDrvbb2020 = {
	"2020bb", NULL, "neogeo", "1991",
	"2020 Super Baseball (set 1)\0", NULL, "SNK / Pallas", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, bb2020RomInfo, bb2020RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// 2020 Super Baseball (alternate version)

static struct BurnRomInfo bba2020RomDesc[] = {
	{ "030-p1.rom",   0x080000, 0xC59BE3DD, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "030-s1.bin",   0x020000, 0x7015B8FC, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "030-c1.bin",   0x100000, 0x4f5E19BD, 3 | BRF_GRA },		 //  2 Sprite data
	{ "030-c2.bin",   0x100000, 0xD6314BF0, 3 | BRF_GRA },		 //  3
	{ "030-c3.bin",   0x100000, 0x47FDDFEE, 3 | BRF_GRA },		 //  4
	{ "030-c4.bin",   0x100000, 0x780D1C4E, 3 | BRF_GRA },		 //  5

	{ "030-m1.bin",   0x020000, 0x4CF466EC, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "030-v1.bin",   0x100000, 0xD4CA364E, 5 | BRF_SND },		 //  7 Sound data
	{ "030-v2.bin",   0x100000, 0x54994455, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(bba2020, bba2020, neogeo);
STD_ROM_FN(bba2020);

struct BurnDriver BurnDrvbba2020 = {
	"2020bba", "2020bb", "neogeo", "1991",
	"2020 Super Baseball (set 2)\0", "Alternate version", "SNK / Pallas", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, bba2020RomInfo, bba2020RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// 2020 Super Baseball (aes version)

static struct BurnRomInfo bbh2020RomDesc[] = {
	{ "030-p1h.bin",  0x080000, 0x12d048d7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "030-s1.bin",   0x020000, 0x7015B8FC, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "030-c1.bin",   0x100000, 0x4f5E19BD, 3 | BRF_GRA },		 //  2 Sprite data
	{ "030-c2.bin",   0x100000, 0xD6314BF0, 3 | BRF_GRA },		 //  3
	{ "030-c3.bin",   0x100000, 0x47FDDFEE, 3 | BRF_GRA },		 //  4
	{ "030-c4.bin",   0x100000, 0x780D1C4E, 3 | BRF_GRA },		 //  5

	{ "030-m1.bin",   0x020000, 0x4CF466EC, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "030-v1.bin",   0x100000, 0xD4CA364E, 5 | BRF_SND },		 //  7 Sound data
	{ "030-v2.bin",   0x100000, 0x54994455, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(bbh2020, bbh2020, neogeo);
STD_ROM_FN(bbh2020);

struct BurnDriver BurnDrvbbh2020 = {
	"2020bbh", "2020bb", "neogeo", "1991",
	"2020 Super Baseball (set 3)\0", "AES version", "SNK / Pallas", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, bbh2020RomInfo, bbh2020RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Soccer Brawl

static struct BurnRomInfo socbrawlRomDesc[] = {
	{ "031-p1.bin",   0x080000, 0xa2801c24, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "031-s1.bin",   0x010000, 0x2db38c3b, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "031-c1.bin",   0x100000, 0xbd0a4eb8, 3 | BRF_GRA },		 //  2 Sprite data
	{ "031-c2.bin",   0x100000, 0xefde5382, 3 | BRF_GRA },		 //  3
	{ "031-c3.bin",   0x080000, 0x580f7f33, 3 | BRF_GRA },		 //  4
	{ "031-c4.bin",   0x080000, 0xed297de8, 3 | BRF_GRA },		 //  5

	{ "031-m1.bin",   0x010000, 0x2f38d5d3, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "031-v1.bin",   0x100000, 0xcc78497e, 5 | BRF_SND },		 //  7 Sound data
	{ "031-v2.bin",   0x100000, 0xdda043c6, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(socbrawl, socbrawl, neogeo);
STD_ROM_FN(socbrawl);

struct BurnDriver BurnDrvSocbrawl = {
	"socbrawl", NULL, "neogeo", "1991",
	"Soccer Brawl\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, socbrawlRomInfo, socbrawlRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Robo Army

static struct BurnRomInfo roboarmyRomDesc[] = {
	{ "032-p1.bin",   0x080000, 0xcd11cbd4, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "032-s1.bin",   0x020000, 0xac0daa1b, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "032-c1.bin",   0x100000, 0x97984c6c, 3 | BRF_GRA },		 //  2 Sprite data
	{ "032-c2.bin",   0x100000, 0x65773122, 3 | BRF_GRA },		 //  3
	{ "032-c3.bin",   0x080000, 0x40adfccd, 3 | BRF_GRA },		 //  4
	{ "032-c4.bin",   0x080000, 0x462571de, 3 | BRF_GRA },		 //  5

	{ "032-m1.bin",   0x020000, 0x98edc671, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "032-v1.bin",   0x100000, 0x63791533, 5 | BRF_SND },		 //  7 Sound data
	{ "032-v2.bin",   0x100000, 0xeb95de70, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(roboarmy, roboarmy, neogeo);
STD_ROM_FN(roboarmy);

struct BurnDriver BurnDrvRoboarmy = {
	"roboarmy", NULL, "neogeo", "1991",
	"Robo Army (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, roboarmyRomInfo, roboarmyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Robo Army (aes version)

static struct BurnRomInfo roboarmaRomDesc[] = {
	{ "032-p1h.bin",  0x080000, 0x27c773cb, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "032-s1.bin",   0x020000, 0xac0daa1b, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "032-c1.bin",   0x100000, 0x97984c6c, 3 | BRF_GRA },		 //  2 Sprite data
	{ "032-c2.bin",   0x100000, 0x65773122, 3 | BRF_GRA },		 //  3
	{ "032-c3.bin",   0x080000, 0x40adfccd, 3 | BRF_GRA },		 //  4
	{ "032-c4.bin",   0x080000, 0x462571de, 3 | BRF_GRA },		 //  5

	{ "032-m1h.bin",  0x020000, 0x35ec952d, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "032-v1.bin",   0x100000, 0x63791533, 5 | BRF_SND },		 //  7 Sound data
	{ "032-v2.bin",   0x100000, 0xeb95de70, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(roboarma, roboarma, neogeo);
STD_ROM_FN(roboarma);

struct BurnDriver BurnDrvroboarma = {
	"roboarma", "roboarmy", "neogeo", "1991",
	"Robo Army (set 2)\0", "AES version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, roboarmaRomInfo, roboarmaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fatal Fury

static struct BurnRomInfo fatfury1RomDesc[] = {
	{ "033-p1.bin",   0x080000, 0x47EBDC2F, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "033-p2.bin",   0x020000, 0xC473AF1C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "033-s1.bin",   0x020000, 0x3C3BDF8C, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "033-c1.bin",   0x100000, 0x74317E54, 3 | BRF_GRA },		 //  3 Sprite data
	{ "033-c2.bin",   0x100000, 0x5BB952F3, 3 | BRF_GRA },		 //  4
	{ "033-c3.bin",   0x100000, 0x9B714A7C, 3 | BRF_GRA },		 //  5
	{ "033-c4.bin",   0x100000, 0x9397476A, 3 | BRF_GRA },		 //  6

	{ "033-m1.bin",   0x020000, 0xA8603979, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "033-v1.bin",   0x100000, 0x212FD20D, 5 | BRF_SND },		 //  8	Sound data
	{ "033-v2.bin",   0x100000, 0xFA2AE47F, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(fatfury1, fatfury1, neogeo);
STD_ROM_FN(fatfury1);

struct BurnDriver BurnDrvFatFury1 = {
	"fatfury1", NULL, "neogeo", "1992",
	"Fatal Fury - king of fighters\0Garou Denetsu - shukumei no tatakai\0", NULL, "SNK", "Neo Geo",
	L"Fatal Fury - king of fighters\0\u9913\u72FC\u4F1D\u8AAC - \u5BBF\u547D\u306E\u95D8\u3044\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, fatfury1RomInfo, fatfury1RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Football Frenzy

static struct BurnRomInfo fbfrenzyRomDesc[] = {
	{ "034-p1.bin",   0x080000, 0xcdef6b19, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "034-s1.bin",   0x020000, 0x8472ed44, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "034-c1.bin",   0x100000, 0x91c56e78, 3 | BRF_GRA },		 //  2 Sprite data
	{ "034-c2.bin",   0x100000, 0x9743ea2f, 3 | BRF_GRA },		 //  3
	{ "034-c3.bin",   0x080000, 0xe5aa65f5, 3 | BRF_GRA },		 //  4
	{ "034-c4.bin",   0x080000, 0x0eb138cc, 3 | BRF_GRA },		 //  5

	{ "034-m1.bin",   0x020000, 0xf41b16b8, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "034-v1.bin",   0x100000, 0x50c9d0dd, 5 | BRF_SND },		 //  7 Sound data
	{ "034-v2.bin",   0x100000, 0x5aa15686, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(fbfrenzy, fbfrenzy, neogeo);
STD_ROM_FN(fbfrenzy);

struct BurnDriver BurnDrvFbfrenzy = {
	"fbfrenzy", NULL, "neogeo", "1992",
	"Football Frenzy\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, fbfrenzyRomInfo, fbfrenzyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0035 Mystic Wand (prototype) 1991 Alpha


// Bakatonosama Mahjong Manyuki

static struct BurnRomInfo bakatonoRomDesc[] = {
	{ "036-p1.bin",   0x080000, 0x1c66b6fa, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "036-s1.bin",   0x020000, 0xf3ef4485, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "036-c1.bin",   0x100000, 0xfe7f1010, 3 | BRF_GRA },		 //  2 Sprite data
	{ "036-c2.bin",   0x100000, 0xbbf003f5, 3 | BRF_GRA },		 //  3
	{ "036-c3.bin",   0x100000, 0x9ac0708e, 3 | BRF_GRA },		 //  4
	{ "036-c4.bin",   0x100000, 0xf2577d22, 3 | BRF_GRA },		 //  5

	{ "036-m1.bin",   0x020000, 0xf1385b96, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "036-v1.bin",   0x100000, 0x1c335dce, 5 | BRF_SND },		 //  7 Sound data
	{ "036-v2.bin",   0x100000, 0xbbf79342, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(bakatono, bakatono, neogeo);
STD_ROM_FN(bakatono);

struct BurnDriver BurnDrvBakatono = {
	"bakatono", NULL, "neogeo", "1991",
	"Bakatonosama Mahjong Manyuki\0", NULL, "Monolith Corp.", "Neo Geo",
	L"\u30D0\u30AB\u6BBF\u69D8 \u9EBB\u96C0\u6F2B\u904A\u8A18\0Bakatonosama Mahjong Manyuki\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_MAHJONG,
	NULL, bakatonoRomInfo, bakatonoRomName, neomahjongInputInfo, neomahjongDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Crossed Swords

static struct BurnRomInfo crswordRomDesc[] = {
	{ "037-p1.bin",   0x080000, 0xE7F2553C, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "037-s1.bin",   0x020000, 0x74651F27, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "037-c1.bin",   0x100000, 0x09DF6892, 3 | BRF_GRA },		 //  2 Sprite data
	{ "037-c2.bin",   0x100000, 0xAC122A78, 3 | BRF_GRA },		 //  3
	{ "037-c3.bin",   0x100000, 0x9D7ED1CA, 3 | BRF_GRA },		 //  4
	{ "037-c4.bin",   0x100000, 0x4A24395D, 3 | BRF_GRA },		 //  5

	{ "037-m1.bin",   0x020000, 0x9C384263, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "037-v1.bin",   0x100000, 0x61FEDF65, 5 | BRF_SND },		 //  7 Sound data
};

STDROMPICKEXT(crsword, crsword, neogeo);
STD_ROM_FN(crsword);

struct BurnDriver BurnDrvCrSword = {
	"crsword", NULL, "neogeo", "1991",
	"Crossed Swords\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, crswordRomInfo, crswordRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Thrash Rally

static struct BurnRomInfo trallyRomDesc[] = {
	{ "038-p1.bin",   0x080000, 0x1E52A576, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "038-p2.bin",   0x080000, 0xA5193E2F, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "038-s1.bin",   0x020000, 0xFFF62AE3, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "038-c1.bin",   0x100000, 0xC58323D4, 3 | BRF_GRA },		 //  3 Sprite data
	{ "038-c2.bin",   0x100000, 0xBBA9C29E, 3 | BRF_GRA },		 //  4
	{ "038-c3.bin",   0x080000, 0x3BB7B9D6, 3 | BRF_GRA },		 //  5
	{ "038-c4.bin",   0x080000, 0xA4513ECF, 3 | BRF_GRA },		 //  6

	{ "038-m1.bin",   0x020000, 0x0908707E, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "038-v1.bin",   0x100000, 0x5CCD9FD5, 5 | BRF_SND },		 //  8 Sound data
	{ "038-v2.bin",   0x080000, 0xDDD8D1E6, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(trally, trally, neogeo);
STD_ROM_FN(trally);

struct BurnDriver BurnDrvTRally = {
	"trally", NULL, "neogeo", "1991",
	"Thrash Rally\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, trallyRomInfo, trallyRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// King of the Monsters 2

static struct BurnRomInfo kotm2RomDesc[] = {
	{ "039-p1.bin",   0x080000, 0xb372d54c, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "039-p2.bin",   0x080000, 0x28661afe, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "039-s1.bin",   0x020000, 0x63ee053a, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "039-c1.bin",   0x200000, 0x6d1c4aa9, 3 | BRF_GRA },		 //  3 Sprite data
	{ "039-c2.bin",   0x200000, 0xf7b75337, 3 | BRF_GRA },		 //  4
	{ "039-c3.bin",   0x080000, 0xbfc4f0b2, 3 | BRF_GRA },		 //  5
	{ "039-c4.bin",   0x080000, 0x81c9c250, 3 | BRF_GRA },		 //  6

	{ "039-m1.bin",   0x020000, 0x0c5b2ad5, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "039-v2.bin",   0x200000, 0x86d34b25, 5 | BRF_SND },		 //  8 Sound data
	{ "039-v4.bin",   0x100000, 0x8fa62a0b, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(kotm2, kotm2, neogeo);
STD_ROM_FN(kotm2);

struct BurnDriver BurnDrvKotm2 = {
	"kotm2", NULL, "neogeo", "1992",
	"King of the Monsters 2 - the next thing\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, kotm2RomInfo, kotm2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sengoku 2

static struct BurnRomInfo sengoku2RomDesc[] = {
	{ "040-p1.bin",   0x100000, 0x6dde02c2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "040-s1.bin",   0x020000, 0xcd9802a3, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "040-c1.bin",   0x200000, 0xfaa8ea99, 3 | BRF_GRA },		 //  3 Sprite data
	{ "040-c2.bin",   0x200000, 0x87d0ec65, 3 | BRF_GRA },		 //  4
	{ "040-c3.bin",   0x080000, 0x24b5ba80, 3 | BRF_GRA },		 //  5
	{ "040-c4.bin",   0x080000, 0x1c9e9930, 3 | BRF_GRA },		 //  6

	{ "040-m1.bin",   0x020000, 0xd4de4bca, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "040-v1.bin",   0x200000, 0x71cb4b5d, 5 | BRF_SND },		 //  8 Sound data
	{ "040-v2.bin",   0x100000, 0xc5cece01, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(sengoku2, sengoku2, neogeo);
STD_ROM_FN(sengoku2);

struct BurnDriver BurnDrvSengoku2 = {
	"sengoku2", NULL, "neogeo", "1993",
	"Sengoku 2\0Sengoku Denshou 2\0", NULL, "SNK", "Neo Geo",
	L"Sengoku 2\0\u6226\u56FD\u4F1D\u627F\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, sengoku2RomInfo, sengoku2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Baseball Stars 2

static struct BurnRomInfo bstars2RomDesc[] = {
	{ "041-p1.bin",   0x080000, 0x523567fd, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "041-s1.bin",   0x020000, 0x015c5c94, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "041-c1.bin",   0x100000, 0xb39a12e1, 3 | BRF_GRA },		 //  2 Sprite data
	{ "041-c2.bin",   0x100000, 0x766cfc2f, 3 | BRF_GRA },		 //  3
	{ "041-c3.bin",   0x100000, 0xfb31339d, 3 | BRF_GRA },		 //  4
	{ "041-c4.bin",   0x100000, 0x70457a0c, 3 | BRF_GRA },		 //  5

	{ "041-m1.bin",   0x010000, 0xb2611c03, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "041-v1.bin",   0x100000, 0xcb1da093, 5 | BRF_SND },		 //  7 Sound data
	{ "041-v2.bin",   0x100000, 0x1c954a9d, 5 | BRF_SND },		 //  8
	{ "041-v3.bin",   0x080000, 0xafaa0180, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(bstars2, bstars2, neogeo);
STD_ROM_FN(bstars2);

struct BurnDriver BurnDrvBstars2 = {
	"bstars2", NULL, "neogeo", "1992",
	"Baseball Stars 2\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_NEOGEO,
	NULL, bstars2RomInfo, bstars2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Quiz Meintantei Neo Geo

static struct BurnRomInfo quizdai2RomDesc[] = {
	{ "042-p1.bin",   0x100000, 0xed719dcf, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "042-s1.bin",   0x020000, 0x164fd6e6, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "042-c1.bin",   0x100000, 0xcb5809a1, 3 | BRF_GRA },		 //  2 Sprite data
	{ "042-c2.bin",   0x100000, 0x1436dfeb, 3 | BRF_GRA },		 //  3
	{ "042-c3.bin",   0x080000, 0xbcd4a518, 3 | BRF_GRA },		 //  4
	{ "042-c4.bin",   0x080000, 0xd602219b, 3 | BRF_GRA },		 //  5

	{ "042-m1.bin",   0x020000, 0xbb19995d, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "042-v1.bin",   0x100000, 0xaf7f8247, 5 | BRF_SND },		 //  7 Sound data
	{ "042-v2.bin",   0x100000, 0xc6474b59, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(quizdai2, quizdai2, neogeo);
STD_ROM_FN(quizdai2);

struct BurnDriver BurnDrvQuizdai2 = {
	"quizdai2", NULL, "neogeo", "1992",
	"Quiz Meintantei Neo Geo - quiz daisousa sen part 2\0", NULL, "SNK", "Neo Geo",
	L"\u30AF\u30A4\u30BA\u8FF7\u63A2\u5075\u30CD\u30AA\uFF06\u30B8\u30AA - quiz daisousa sen part 2\0Quiz Meintantei Neo Geo\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, quizdai2RomInfo, quizdai2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// 3 Count Bout

static struct BurnRomInfo countb3RomDesc[] = {
	{ "043-p1.bin",   0x080000, 0xeb2714c4, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "043-p2.bin",   0x080000, 0x5e764567, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "043-s1.bin",   0x020000, 0xc362d484, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "043-c1.bin",   0x200000, 0xbad2d67f, 3 | BRF_GRA },		 //  3 Sprite data
	{ "043-c2.bin",   0x200000, 0xa7fbda95, 3 | BRF_GRA },		 //  4
	{ "043-c3.bin",   0x200000, 0xf00be011, 3 | BRF_GRA },		 //  5
	{ "043-c4.bin",   0x200000, 0x1887e5c0, 3 | BRF_GRA },		 //  6

	{ "043-m1.bin",   0x020000, 0x3377cda3, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "043-v1.bin",   0x200000, 0x63688ce8, 5 | BRF_SND },		 //  8 Sound data
	{ "043-v2.bin",   0x200000, 0xc69a827b, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(countb3, countb3, neogeo);
STD_ROM_FN(countb3);

struct BurnDriver BurnDrv3Countb = {
	"3countb", NULL, "neogeo", "1993",
	"3 Count Bout\0Fire Suplex\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, countb3RomInfo, countb3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Art of Fighting

static struct BurnRomInfo aofRomDesc[] = {
	{ "044-p1.bin",   0x080000, 0xca9f7a6d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "044-s1.bin",   0x020000, 0x89903f39, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "044-c1.bin",   0x200000, 0xddab98a7, 3 | BRF_GRA },		 //  2 Sprite data
	{ "044-c2.bin",   0x200000, 0xd8ccd575, 3 | BRF_GRA },		 //  3
	{ "044-c3.bin",   0x200000, 0x403e898a, 3 | BRF_GRA },		 //  4
	{ "044-c4.bin",   0x200000, 0x6235fbaa, 3 | BRF_GRA },		 //  5

	{ "044-m1.bin",   0x020000, 0x981345f8, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "044-v2.bin",   0x200000, 0x3ec632ea, 5 | BRF_SND },		 //  7 Sound data
	{ "044-v4.bin",   0x200000, 0x4b0f8e23, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(aof, aof, neogeo);
STD_ROM_FN(aof);

struct BurnDriver BurnDrvAof = {
	"aof", NULL, "neogeo", "1992",
	"Art of Fighting\0Ryuuko no Ken\0", NULL, "SNK", "Neo Geo",
	L"Art of Fighting\0\u9F8D\u864E\u306E\u62F3\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, aofRomInfo, aofRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown

static struct BurnRomInfo samshoRomDesc[] = {
	{ "045-p1.bin",   0x080000, 0x80AA6C97, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "045-p2.bin",   0x080000, 0x71768728, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "045-p3.bin",   0x080000, 0x38EE9bA9, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "045-s1.bin",   0x020000, 0x9142A4D3, 2 | BRF_GRA },		 //  3 Text layer tiles

	{ "045-c1.bin",   0x200000, 0x2E5873A4, 3 | BRF_GRA },		 //  4 Sprite data
	{ "045-c2.bin",   0x200000, 0x04FEBB10, 3 | BRF_GRA },		 //  5
	{ "045-c3.bin",   0x200000, 0xF3DABD1E, 3 | BRF_GRA },		 //  6
	{ "045-c4.bin",   0x200000, 0x935C62F0, 3 | BRF_GRA },		 //  7
	{ "045-c5.bin",   0x080000, 0xA2BB8284, 3 | BRF_GRA },		 //  8
	{ "045-c6.bin",   0x080000, 0x4FA71252, 3 | BRF_GRA },		 //  9

	{ "045-m1.bin",   0x020000, 0x95170640, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "045-v1.bin",   0x200000, 0x37F78A9B, 5 | BRF_SND },		 // 11	Sound data
	{ "045-v2.bin",   0x200000, 0x568B20CF, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(samsho, samsho, neogeo);
STD_ROM_FN(samsho);

struct BurnDriver BurnDrvSamSho = {
	"samsho", NULL, "neogeo", "1993",
	"Samurai Shodown\0Samurai Spirits\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, samshoRomInfo, samshoRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Top Hunter

static struct BurnRomInfo tophuntrRomDesc[] = {
	{ "046-p1.bin",   0x100000, 0x69FA9E29, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "046-p2.sp2",   0x100000, 0xF182CB3E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "046-s1.bin",   0x020000, 0x14B01D7B, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "046-c1.bin",   0x100000, 0xFA720A4A, 3 | BRF_GRA },		 //  3 Sprite data
	{ "046-c2.bin",   0x100000, 0xC900C205, 3 | BRF_GRA },		 //  4
	{ "046-c3.bin",   0x100000, 0x880E3C25, 3 | BRF_GRA },		 //  5
	{ "046-c4.bin",   0x100000, 0x7A2248AA, 3 | BRF_GRA },		 //  6
	{ "046-c5.bin",   0x100000, 0x4B735E45, 3 | BRF_GRA },		 //  7
	{ "046-c6.bin",   0x100000, 0x273171DF, 3 | BRF_GRA },		 //  8
	{ "046-c7.bin",   0x100000, 0x12829C4C, 3 | BRF_GRA },		 //  9
	{ "046-c8.bin",   0x100000, 0xC944E03D, 3 | BRF_GRA },		 // 10

	{ "046-m1.bin",   0x020000, 0x3F84BB9f, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "046-v1.bin",   0x100000, 0xC1F9C2DB, 5 | BRF_SND },		 // 12 Sound data
	{ "046-v2.bin",   0x100000, 0x56254A64, 5 | BRF_SND },		 // 13
	{ "046-v3.bin",   0x100000, 0x58113FB1, 5 | BRF_SND },		 // 14
	{ "046-v4.bin",   0x100000, 0x4F54C187, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(tophuntr, tophuntr, neogeo);
STD_ROM_FN(tophuntr);

struct BurnDriver BurnDrvtophntr = {
	"tophuntr", NULL, "neogeo", "1994",
	"Top Hunter - Roddy & Cathy (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, tophuntrRomInfo, tophuntrRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Top Hunter (alternate version)

static struct BurnRomInfo tophuntaRomDesc[] = {
	{ "046-pg1.bin",  0x100000, 0x771E39BC, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "046-p2.sp2",   0x100000, 0xF182CB3E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "046-s1.bin",   0x020000, 0x14B01D7B, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "046-c1.bin",   0x100000, 0xFA720A4A, 3 | BRF_GRA },		 //  3 Sprite data
	{ "046-c2.bin",   0x100000, 0xC900C205, 3 | BRF_GRA },		 //  4
	{ "046-c3.bin",   0x100000, 0x880E3C25, 3 | BRF_GRA },		 //  5
	{ "046-c4.bin",   0x100000, 0x7A2248AA, 3 | BRF_GRA },		 //  6
	{ "046-c5.bin",   0x100000, 0x4B735E45, 3 | BRF_GRA },		 //  7
	{ "046-c6.bin",   0x100000, 0x273171DF, 3 | BRF_GRA },		 //  8
	{ "046-c7.bin",   0x100000, 0x12829C4C, 3 | BRF_GRA },		 //  9
	{ "046-c8.bin",   0x100000, 0xC944E03D, 3 | BRF_GRA },		 // 10

	{ "046-m1.bin",   0x020000, 0x3F84BB9f, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "046-v1.bin",   0x100000, 0xC1F9C2DB, 5 | BRF_SND },		 // 12 Sound data
	{ "046-v2.bin",   0x100000, 0x56254A64, 5 | BRF_SND },		 // 13
	{ "046-v3.bin",   0x100000, 0x58113FB1, 5 | BRF_SND },		 // 14
	{ "046-v4.bin",   0x100000, 0x4F54C187, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(tophunta, tophunta, neogeo);
STD_ROM_FN(tophunta);

struct BurnDriver BurnDrvtophunta = {
	"tophunta", "tophuntr", "neogeo", "1994",
	"Top Hunter - Roddy & Cathy (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, tophuntaRomInfo, tophuntaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fatal Fury 2

static struct BurnRomInfo fatfury2RomDesc[] = {
	{ "047-p1.bin",   0x080000, 0xbe40ea92, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "047-p2.bin",   0x080000, 0x2a9beac5, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "047-s1.bin",   0x020000, 0xd7dbbf39, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "047-c1.bin",   0x200000, 0xf72a939e, 3 | BRF_GRA },		 //  3 Sprite data
	{ "047-c2.bin",   0x200000, 0x05119a0d, 3 | BRF_GRA },		 //  4
	{ "047-c3.bin",   0x200000, 0x01e00738, 3 | BRF_GRA },		 //  5
	{ "047-c4.bin",   0x200000, 0x9fe27432, 3 | BRF_GRA },		 //  6

	{ "047-m1.bin",   0x020000, 0x820b0ba7, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "047-v1.bin",   0x200000, 0xd9d00784, 5 | BRF_SND },		 //  8 Sound data
	{ "047-v2.bin",   0x200000, 0x2c9a4b33, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(fatfury2, fatfury2, neogeo);
STD_ROM_FN(fatfury2);

static int fatfury2Init()
{
	pNeoProtectionCallback = fatfury2ProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvFatfury2 = {
	"fatfury2", NULL, "neogeo", "1992",
	"Fatal Fury 2\0Garou Densetsu 2 - arata-naru tatakai\0", NULL, "SNK", "Neo Geo",
	L"Fatal Fury 2\0\u9913\u72FC\u4F1D\u8AAC\uFF12 - \u65B0\u305F\u306A\u308B\u95D8\u3044\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, fatfury2RomInfo, fatfury2RomName, neogeoInputInfo, neogeoDIPInfo,
	fatfury2Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Jyanshin Densetsu - quest of jongmaster

static struct BurnRomInfo janshinRomDesc[] = {
	{ "048-p1.bin",   0x100000, 0x7514cb7a, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "048-s1.bin",   0x020000, 0x8285b25a, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "048-c1.bin",   0x200000, 0x3fa890e9, 3 | BRF_GRA },		 //  2 Sprite data
	{ "048-c2.bin",   0x200000, 0x59c48ad8, 3 | BRF_GRA },		 //  3

	{ "048-m1.bin",   0x010000, 0xe191f955, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "048-v1.bin",   0x200000, 0xf1947d2b, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(janshin, janshin, neogeo);
STD_ROM_FN(janshin);

struct BurnDriver BurnDrvJanshin = {
	"janshin", NULL, "neogeo", "1994",
	"Jyanshin Densetsu - quest of jongmaster\0", NULL, "Aicom", "Neo Geo",
	L"\u96C0\u795E\u4F1D\u8AAC - quest of jongmaster\0Jyanshin Densetsu\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_MAHJONG,
	NULL, janshinRomInfo, janshinRomName, neomahjongInputInfo, neomahjongDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Andro Dunos

static struct BurnRomInfo androdunRomDesc[] = {
	{ "049-p1.bin",   0x080000, 0x3B857DA2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "049-p2.bin",   0x080000, 0x2F062209, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "049-s1.bin",   0x020000, 0x6349DE5D, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "049-c1.bin",   0x100000, 0x7ACE6DB3, 3 | BRF_GRA },		 //  3 Sprite data
	{ "049-c2.bin",   0x100000, 0xB17024F7, 3 | BRF_GRA },		 //  4

	{ "049-m1.bin",   0x020000, 0x1A009F8C, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "049-v1.bin",   0x080000, 0x577C85B3, 5 | BRF_SND },		 //  8 Sound data
	{ "049-v2.bin",   0x080000, 0xE14551C4, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(androdun, androdun, neogeo);
STD_ROM_FN(androdun);

struct BurnDriver BurnDrvandrodun = {
	"androdun", NULL, "neogeo", "1992",
	"Andro Dunos\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, androdunRomInfo, androdunRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ninja Commando

static struct BurnRomInfo ncommandRomDesc[] = {
	{ "050-p1.bin",   0x100000, 0x4E097C40, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "050-s1.bin",   0x020000, 0xDB8F9C8E, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "050-c1.bin",   0x100000, 0x87421A0A, 3 | BRF_GRA },		 //  2 Sprite data
	{ "050-c2.bin",   0x100000, 0xC4CF5548, 3 | BRF_GRA },		 //  3
	{ "050-c3.bin",   0x100000, 0x03422C1E, 3 | BRF_GRA },		 //  4
	{ "050-c4.bin",   0x100000, 0x0845EADB, 3 | BRF_GRA },		 //  5

	{ "050-m1.bin",   0x020000, 0x6FCF07D3, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "050-v1.bin",   0x100000, 0x23C3AB42, 5 | BRF_SND },		 //  7 Sound data
	{ "050-v2.bin",   0x080000, 0x80B8A984, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(ncommand, ncommand, neogeo);
STD_ROM_FN(ncommand);

struct BurnDriver BurnDrvNCommand = {
	"ncommand", NULL, "neogeo", "1992",
	"Ninja Commando\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ncommandRomInfo, ncommandRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Viewpoint

static struct BurnRomInfo viewpoinRomDesc[] = {
	{ "051-p1.bin",   0x100000, 0x17aa899d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "051-s1.bin",   0x010000, 0x6d0f146a, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "051-c1.bin",   0x200000, 0xd624c132, 3 | BRF_GRA },		 //  2 Sprite data
	{ "051-c2.bin",   0x200000, 0x40d69f1e, 3 | BRF_GRA },		 //  3

	{ "051-m1.bin",   0x010000, 0xd57bd7af, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "051-v1.bin",   0x200000, 0x019978b6, 5 | BRF_SND },		 //  5 Sound data
	{ "051-v2.bin",   0x200000, 0x5758f38c, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(viewpoin, viewpoin, neogeo);
STD_ROM_FN(viewpoin);

struct BurnDriver BurnDrvViewpoin = {
	"viewpoin", NULL, "neogeo", "1992",
	"Viewpoint\0", NULL, "Sammy", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, viewpoinRomInfo, viewpoinRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Super Sidekicks

static struct BurnRomInfo ssidekiRomDesc[] = {
	{ "052-p1.bin",   0x080000, 0x9cd97256, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "052-s1.bin",   0x020000, 0x97689804, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "052-c1.bin",   0x200000, 0x53e1c002, 3 | BRF_GRA },		 //  2 Sprite data
	{ "052-c2.bin",   0x200000, 0x776a2d1f, 3 | BRF_GRA },		 //  3

	{ "052-m1.bin",   0x020000, 0x49f17d2d, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "052-v1.bin",   0x200000, 0x22c097a5, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(ssideki, ssideki, neogeo);
STD_ROM_FN(ssideki);

// Uses same protection as Fatal Fury 2

struct BurnDriver BurnDrvSsideki = {
	"ssideki", NULL, "neogeo", "1992",
	"Super Sidekicks\0Tokuten Ou\0", NULL, "SNK", "Neo Geo",
	L"Super Sidekicks\0\u5F97\u70B9\u738B\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, ssidekiRomInfo, ssidekiRomName, neogeoInputInfo, neogeoDIPInfo,
	fatfury2Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// World Heroes

static struct BurnRomInfo wh1RomDesc[] = {
	{ "053-p1.bin",   0x080000, 0x95B574CB, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "053-p2.bin",   0x080000, 0xF198ED45, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "053-s1.bin",   0x020000, 0x8C2C2D6B, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "053-c1.bin",   0x200000, 0x85EB5BCE, 3 | BRF_GRA },		 //  3 Sprite data
	{ "053-c2.bin",   0x200000, 0xEC93B048, 3 | BRF_GRA },		 //  4
	{ "053-c3.bin",   0x100000, 0x0DD64965, 3 | BRF_GRA },		 //  5
	{ "053-c4.bin",   0x100000, 0x9270D954, 3 | BRF_GRA },		 //  6

	{ "053-m1.bin",   0x020000, 0x1BD9D04B, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "053-v2.bin",   0x200000, 0xA68DF485, 5 | BRF_SND },		 //  8 Sound data
	{ "053-v4.bin",   0x100000, 0x7BEA8F66, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(wh1, wh1, neogeo);
STD_ROM_FN(wh1);

struct BurnDriver BurnDrvWH1 = {
	"wh1", NULL, "neogeo", "1992",
	"World Heroes (set 1)\0", NULL, "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, wh1RomInfo, wh1RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// World Heroes (aes version)

static struct BurnRomInfo wh1hRomDesc[] = {
	{ "053-p1.rom",   0x080000, 0xED29FDE2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "053-p2.rom",   0x080000, 0x98F2B158, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "053-s1.bin",   0x020000, 0x8C2C2D6B, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "053-c1.bin",   0x200000, 0x85EB5BCE, 3 | BRF_GRA },		 //  3 Sprite data
	{ "053-c2.bin",   0x200000, 0xEC93B048, 3 | BRF_GRA },		 //  4
	{ "053-c3.bin",   0x100000, 0x0DD64965, 3 | BRF_GRA },		 //  5
	{ "053-c4.bin",   0x100000, 0x9270D954, 3 | BRF_GRA },		 //  6

	{ "053-m1.bin",   0x020000, 0x1BD9D04B, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "053-v2.bin",   0x200000, 0xA68DF485, 5 | BRF_SND },		 //  8 Sound data
	{ "053-v4.bin",   0x100000, 0x7BEA8F66, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(wh1h, wh1h, neogeo);
STD_ROM_FN(wh1h);

struct BurnDriver BurnDrvWH1h = {
	"wh1h", "wh1", "neogeo", "1992",
	"World Heroes (set 2)\0", "AES version", "Alpha Denshi Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPC,
	NULL, wh1hRomInfo, wh1hRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0054 Crossed Swords 2  (CD only? not confirmed, MVS might exist)


// The King of Fighters '94

static struct BurnRomInfo kof94RomDesc[] = {
	{ "055-p1.bin",   0x200000, 0xf10a2042, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "055-s1.bin",   0x020000, 0x825976c1, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "055-c1.bin",   0x200000, 0xb96ef460, 3 | BRF_GRA },		 //  2 Sprite data
	{ "055-c2.bin",   0x200000, 0x15e096a7, 3 | BRF_GRA },		 //  3
	{ "055-c3.bin",   0x200000, 0x54f66254, 3 | BRF_GRA },		 //  4
	{ "055-c4.bin",   0x200000, 0x0b01765f, 3 | BRF_GRA },		 //  5
	{ "055-c5.bin",   0x200000, 0xee759363, 3 | BRF_GRA },		 //  6
	{ "055-c6.bin",   0x200000, 0x498da52c, 3 | BRF_GRA },		 //  7
	{ "055-c7.bin",   0x200000, 0x62f66888, 3 | BRF_GRA },		 //  8
	{ "055-c8.bin",   0x200000, 0xfe0a235d, 3 | BRF_GRA },		 //  9

	{ "055-m1.bin",   0x020000, 0xf6e77cf5, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "055-v1.bin",   0x200000, 0x8889596d, 5 | BRF_SND },		 // 11 Sound data
	{ "055-v2.bin",   0x200000, 0x25022b27, 5 | BRF_SND },		 // 12
	{ "055-v3.bin",   0x200000, 0x83cf32c0, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(kof94, kof94, neogeo);
STD_ROM_FN(kof94);

struct BurnDriver BurnDrvKof94 = {
	"kof94", NULL, "neogeo", "1994",
	"The King of Fighters '94\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, kof94RomInfo, kof94RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Art of Fighting 2

static struct BurnRomInfo aof2RomDesc[] = {
	{ "056-p1.bin",   0x100000, 0xa3b1d021, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "056-s1.bin",   0x020000, 0x8b02638e, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "056-c1.bin",   0x200000, 0x17b9cbd2, 3 | BRF_GRA },		 //  2 Sprite data
	{ "056-c2.bin",   0x200000, 0x5fd76b67, 3 | BRF_GRA },		 //  3
	{ "056-c3.bin",   0x200000, 0xd2c88768, 3 | BRF_GRA },		 //  4
	{ "056-c4.bin",   0x200000, 0xdb39b883, 3 | BRF_GRA },		 //  5
	{ "056-c5.bin",   0x200000, 0xc3074137, 3 | BRF_GRA },		 //  6
	{ "056-c6.bin",   0x200000, 0x31de68d3, 3 | BRF_GRA },		 //  7
	{ "056-c7.bin",   0x200000, 0x3f36df57, 3 | BRF_GRA },		 //  8
	{ "056-c8.bin",   0x200000, 0xe546d7a8, 3 | BRF_GRA },		 //  9

	{ "056-m1.bin",   0x020000, 0xf27e9d52, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "056-v1.bin",   0x200000, 0x4628fde0, 5 | BRF_SND },		 // 11 Sound data
	{ "056-v2.bin",   0x200000, 0xb710e2f2, 5 | BRF_SND },		 // 12
	{ "056-v3.bin",   0x100000, 0xd168c301, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(aof2, aof2, neogeo);
STD_ROM_FN(aof2);

struct BurnDriver BurnDrvAof2 = {
	"aof2", NULL, "neogeo", "1994",
	"Art of Fighting 2\0Ryuuko no Ken 2 (set 1)\0", NULL, "SNK", "Neo Geo",
	L"Art of Fighting 2\0\u9F8D\u864E\u306E\u62F3\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, aof2RomInfo, aof2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*------------------------------------------------------------------------------------

		This game was modified by simply adding another Program chip and 
	mapping it to the region that the old P1 was mapped to.  This means
	that 0-0x7FFFF of the P is from the ep1.bin, and the last 0x80000-0xFFFFF
	is from the original P.

------------------------------------------------------------------------------------*/

// Art of Fighting 2 (alternate version)

static struct BurnRomInfo aof2aRomDesc[] = {
	{ "056-p1.bin",   0x100000, 0xa3b1d021, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "056-s1.bin",   0x020000, 0x8b02638e, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "056-c1.bin",   0x200000, 0x17b9cbd2, 3 | BRF_GRA },		 //  2 Sprite data
	{ "056-c2.bin",   0x200000, 0x5fd76b67, 3 | BRF_GRA },		 //  3
	{ "056-c3.bin",   0x200000, 0xd2c88768, 3 | BRF_GRA },		 //  4
	{ "056-c4.bin",   0x200000, 0xdb39b883, 3 | BRF_GRA },		 //  5
	{ "056-c5.bin",   0x200000, 0xc3074137, 3 | BRF_GRA },		 //  6
	{ "056-c6.bin",   0x200000, 0x31de68d3, 3 | BRF_GRA },		 //  7
	{ "056-c7.bin",   0x200000, 0x3f36df57, 3 | BRF_GRA },		 //  8
	{ "056-c8.bin",   0x200000, 0xe546d7a8, 3 | BRF_GRA },		 //  9

	{ "056-m1.bin",   0x020000, 0xf27e9d52, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "056-v1.bin",   0x200000, 0x4628fde0, 5 | BRF_SND },		 // 11 Sound data
	{ "056-v2.bin",   0x200000, 0xb710e2f2, 5 | BRF_SND },		 // 12
	{ "056-v3.bin",   0x100000, 0xd168c301, 5 | BRF_SND },		 // 13

	{ "056-ep1.bin",  0x080000, 0x75d6301c, 0 | BRF_ESS | BRF_PRG }, // 14 68K code patch
};

STDROMPICKEXT(aof2a, aof2a, neogeo);
STD_ROM_FN(aof2a);

static void aof2aCallback()
{
	BurnLoadRom(Neo68KROM, 14, 1);
}

static int aof2aInit()
{
	pNeoInitCallback = aof2aCallback;
 	return NeoInit();
}

struct BurnDriver BurnDrvAof2a = {
	"aof2a", "aof2", "neogeo", "1994",
	"Art of Fighting 2\0Ryuuko no Ken 2 (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"Art of Fighting 2\0\u9F8D\u864E\u306E\u62F3\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, aof2aRomInfo, aof2aRomName, neogeoInputInfo, neogeoDIPInfo,
	aof2aInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// World Heroes 2

static struct BurnRomInfo wh2RomDesc[] = {
	{ "057-p1.bin",   0x200000, 0x65A891D9, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "057-s1.bin",   0x020000, 0xFCAEB3A4, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "057-c1.bin",   0x200000, 0x21C6BB91, 3 | BRF_GRA },		 //  2 Sprite data
	{ "057-c2.bin",   0x200000, 0xA3999925, 3 | BRF_GRA },		 //  3
	{ "057-c3.bin",   0x200000, 0xB725A219, 3 | BRF_GRA },		 //  4
	{ "057-c4.bin",   0x200000, 0x8D96425E, 3 | BRF_GRA },		 //  5
	{ "057-c5.bin",   0x200000, 0xB20354AF, 3 | BRF_GRA },		 //  6
	{ "057-c6.bin",   0x200000, 0xB13D1DE3, 3 | BRF_GRA },		 //  7

	{ "057-m1.bin",   0x020000, 0x8FA3BC77, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "057-v1.bin",   0x200000, 0x8877E301, 5 | BRF_SND },		 //  9 Sound data
	{ "057-v2.bin",   0x200000, 0xC1317FF4, 5 | BRF_SND },		 // 10
};

STDROMPICKEXT(wh2, wh2, neogeo);
STD_ROM_FN(wh2);

struct BurnDriver BurnDrvWH2 = {
	"wh2", NULL, "neogeo", "1993",
	"World Heroes 2\0", NULL, "ADK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, wh2RomInfo, wh2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fatal Fury Special

static struct BurnRomInfo fatfurspRomDesc[] = {
	{ "058-p1.bin",   0x100000, 0x2f585ba2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "058-p2.bin",   0x080000, 0xd7c71a6b, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "058-s1.bin",   0x020000, 0x2df03197, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "058-c1.bin",   0x200000, 0x044ab13c, 3 | BRF_GRA },		 //  3 Sprite data
	{ "058-c2.bin",   0x200000, 0x11e6bf96, 3 | BRF_GRA },		 //  4
	{ "058-c3.bin",   0x200000, 0x6f7938d5, 3 | BRF_GRA },		 //  5
	{ "058-c4.bin",   0x200000, 0x4ad066ff, 3 | BRF_GRA },		 //  6
	{ "058-c5.bin",   0x200000, 0x49c5e0bf, 3 | BRF_GRA },		 //  7
	{ "058-c6.bin",   0x200000, 0x8ff1f43d, 3 | BRF_GRA },		 //  8

	{ "058-m1.bin",   0x020000, 0xccc5186e, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "058-v1.bin",   0x200000, 0x55d7ce84, 5 | BRF_SND },		 // 10 Sound data
	{ "058-v2.bin",   0x200000, 0xee080b10, 5 | BRF_SND },		 // 11
	{ "058-v3.bin",   0x100000, 0xf9eb3d4a, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(fatfursp, fatfursp, neogeo);
STD_ROM_FN(fatfursp);

struct BurnDriver BurnDrvFatfursp = {
	"fatfursp", NULL, "neogeo", "1993",
	"Fatal Fury Special\0Garou Densetsu Special (set 1)\0", NULL, "SNK", "Neo Geo",
	L"Fatal Fury Special\0\u9913\u72FC\u4F1D\u8AAC Special\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, fatfurspRomInfo, fatfurspRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fatal Fury Special (alternate version)

static struct BurnRomInfo fatfursaRomDesc[] = {
	{ "058-p1.bin",   0x100000, 0x2f585ba2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "058-p2.bin",   0x080000, 0xd7c71a6b, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "058-s1.bin",   0x020000, 0x2df03197, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "058-c1.bin",   0x200000, 0x044ab13c, 3 | BRF_GRA },		 //  3 Sprite data
	{ "058-c2.bin",   0x200000, 0x11e6bf96, 3 | BRF_GRA },		 //  4
	{ "058-c3.bin",   0x200000, 0x6f7938d5, 3 | BRF_GRA },		 //  5
	{ "058-c4.bin",   0x200000, 0x4ad066ff, 3 | BRF_GRA },		 //  6
	{ "058-c5.bin",   0x200000, 0x49c5e0bf, 3 | BRF_GRA },		 //  7
	{ "058-c6.bin",   0x200000, 0x8ff1f43d, 3 | BRF_GRA },		 //  8

	{ "058-m1.bin",   0x020000, 0xccc5186e, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "058-v1.bin",   0x200000, 0x55d7ce84, 5 | BRF_SND },		 // 10 Sound data
	{ "058-v2.bin",   0x200000, 0xee080b10, 5 | BRF_SND },		 // 11
	{ "058-v3.bin",   0x100000, 0xf9eb3d4a, 5 | BRF_SND },		 // 12

	{ "058-ep1.bin",  0x080000, 0x9f0c1e1a, 0 | BRF_ESS | BRF_PRG }, // 13 68K code
};

STDROMPICKEXT(fatfursa, fatfursa, neogeo);
STD_ROM_FN(fatfursa);

// See the notes for aof2a for an explanation on this

static void fatfursaCallback()
{
	BurnLoadRom(Neo68KROM, 13, 1);
}

static int fatfursaInit()
{
	pNeoInitCallback = fatfursaCallback;
 	return NeoInit();
}

struct BurnDriver BurnDrvFatfursa = {
	"fatfursa", "fatfursp", "neogeo", "1993",
	"Fatal Fury Special\0Garou Densetsu Special (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"Fatal Fury Special\0\u9913\u72FC\u4F1D\u8AAC Special\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, fatfursaRomInfo, fatfursaRomName, neogeoInputInfo, neogeoDIPInfo,
	fatfursaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Savage Reign

static struct BurnRomInfo savagereRomDesc[] = {
	{ "059-p1.bin",   0x200000, 0x01d4e9c0, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "059-s1.bin",   0x020000, 0xe08978ca, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "059-c1.bin",   0x200000, 0x763ba611, 3 | BRF_GRA },		 //  2 Sprite data
	{ "059-c2.bin",   0x200000, 0xe05e8ca6, 3 | BRF_GRA },		 //  3
	{ "059-c3.bin",   0x200000, 0x3e4eba4b, 3 | BRF_GRA },		 //  4
	{ "059-c4.bin",   0x200000, 0x3c2a3808, 3 | BRF_GRA },		 //  5
	{ "059-c5.bin",   0x200000, 0x59013f9e, 3 | BRF_GRA },		 //  6
	{ "059-c6.bin",   0x200000, 0x1c8d5def, 3 | BRF_GRA },		 //  7
	{ "059-c7.bin",   0x200000, 0xc88f7035, 3 | BRF_GRA },		 //  8
	{ "059-c8.bin",   0x200000, 0x484ce3ba, 3 | BRF_GRA },		 //  9

	{ "059-m1.bin",   0x020000, 0x29992eba, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "059-v1.bin",   0x200000, 0x530c50fd, 5 | BRF_SND },		 // 11 Sound data
	{ "059-v2.bin",   0x200000, 0xeb6f1cdb, 5 | BRF_SND },		 // 12
	{ "059-v3.bin",   0x200000, 0x7038c2f9, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(savagere, savagere, neogeo);
STD_ROM_FN(savagere);

struct BurnDriver BurnDrvSavagere = {
	"savagere", NULL, "neogeo", "1995",
	"Savage Reign\0Fu'un Mokushiroku - kakutou sousei\0", NULL, "SNK", "Neo Geo",
	L"Savage Reign\0\u98A8\u96F2\u9ED9\u793A\u9332 - \u683C\u95D8\u5275\u4E16\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, savagereRomInfo, savagereRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fight Fever

static struct BurnRomInfo fightfevRomDesc[] = {
	{ "060-p1.bin",   0x080000, 0x3032041b, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "060-p2.bin",   0x080000, 0xb0801d5f, 1 | BRF_ESS | BRF_PRG }, //  1 68K code

	{ "060-s1.bin",   0x020000, 0x70727a1e, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "060-c1.bin",   0x200000, 0x8908fff9, 3 | BRF_GRA },		 //  3 Sprite data
	{ "060-c2.bin",   0x200000, 0xc6649492, 3 | BRF_GRA },		 //  4
	{ "060-c3.bin",   0x200000, 0x0956b437, 3 | BRF_GRA },		 //  5
	{ "060-c4.bin",   0x200000, 0x026f3b62, 3 | BRF_GRA },		 //  6

	{ "060-m1.bin",   0x020000, 0x0b7c4e65, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "060-v1.bin",   0x200000, 0xf417c215, 5 | BRF_SND },		 //  8 Sound data
	{ "060-v2.bin",   0x100000, 0x64470036, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(fightfev, fightfev, neogeo);
STD_ROM_FN(fightfev);

struct BurnDriver BurnDrvFightfev = {
	"fightfev", NULL, "neogeo", "1994",
	"Fight Fever\0Wang Jung Wang (set 1)\0", NULL, "Viccom", "Neo Geo",
	L"Fight Fever\0\uC655\uC911\uC655\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, fightfevRomInfo, fightfevRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fight Fever (alternate version)

static struct BurnRomInfo fightfvaRomDesc[] = {
	{ "060-p1a.bin",  0x100000, 0x2a104b50, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "060-s1.bin",   0x020000, 0x70727a1e, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "060-c1.bin",   0x200000, 0x8908fff9, 3 | BRF_GRA },		 //  3 Sprite data
	{ "060-c2.bin",   0x200000, 0xc6649492, 3 | BRF_GRA },		 //  4
	{ "060-c3.bin",   0x200000, 0x0956b437, 3 | BRF_GRA },		 //  5
	{ "060-c4.bin",   0x200000, 0x026f3b62, 3 | BRF_GRA },		 //  6

	{ "060-m1.bin",   0x020000, 0x0b7c4e65, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "060-v1.bin",   0x200000, 0xf417c215, 5 | BRF_SND },		 //  8 Sound data
	{ "060-v2.bin",   0x100000, 0x64470036, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(fightfva, fightfva, neogeo);
STD_ROM_FN(fightfva);

struct BurnDriver BurnDrvFightfeva = {
	"fightfva", "fightfev", "neogeo", "1994",
	"Fight Fever\0Wang Jung Wang (set 2)\0", "Alternate version", "Viccom", "Neo Geo",
	L"Fight Fever\0\uC655\uC911\uC655\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, fightfvaRomInfo, fightfvaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Super Sidekicks 2

static struct BurnRomInfo ssideki2RomDesc[] = {
	{ "061-p1.bin",   0x100000, 0x5969e0dc, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "061-s1.bin",   0x020000, 0x226d1b68, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "061-c1.bin",   0x200000, 0xa626474f, 3 | BRF_GRA },		 //  2 Sprite data
	{ "061-c2.bin",   0x200000, 0xc3be42ae, 3 | BRF_GRA },		 //  3
	{ "061-c3.bin",   0x200000, 0x2a7b98b9, 3 | BRF_GRA },		 //  4
	{ "061-c4.bin",   0x200000, 0xc0be9a1f, 3 | BRF_GRA },		 //  5

	{ "061-m1.bin",   0x020000, 0x156f6951, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "061-v1.bin",   0x200000, 0xf081c8d3, 5 | BRF_SND },		 //  7 Sound data
	{ "061-v2.bin",   0x200000, 0x7cd63302, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(ssideki2, ssideki2, neogeo);
STD_ROM_FN(ssideki2);

struct BurnDriver BurnDrvSsideki2 = {
	"ssideki2", NULL, "neogeo", "1994",
	"Super Sidekicks 2 - the world championship\0Tokuten Ou 2 - real fight football\0", NULL, "SNK", "Neo Geo",
	L"Super Sidekicks 2 - the world championship\0\u5F97\u70B9\u738B\uFF12 - \u30EA\u30A2\u30EB\u30D5\u30A1\u30A4\u30C8\u30D5\u30C3\u30C8\u30DC\u30FC\u30EB\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, ssideki2RomInfo, ssideki2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Spin Master

static struct BurnRomInfo spinmastRomDesc[] = {
	{ "062-p1.bin",   0x100000, 0x37ABA1AA, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "062-p2.bin",   0x080000, 0x43763AD2, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "062-s1.bin",   0x020000, 0x289E2BBE, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "062-c1.bin",   0x100000, 0xA9375AA2, 3 | BRF_GRA },		 //  3 Sprite data
	{ "062-c2.bin",   0x100000, 0x0E73B758, 3 | BRF_GRA },		 //  4
	{ "062-c3.bin",   0x100000, 0xDF51E465, 3 | BRF_GRA },		 //  5
	{ "062-c4.bin",   0x100000, 0x38517E90, 3 | BRF_GRA },		 //  6
	{ "062-c5.bin",   0x100000, 0x7BABD692, 3 | BRF_GRA },		 //  7
	{ "062-c6.bin",   0x100000, 0xCDE5ADE5, 3 | BRF_GRA },		 //  8
	{ "062-c7.bin",   0x100000, 0xBB2FD7C0, 3 | BRF_GRA },		 //  9
	{ "062-c8.bin",   0x100000, 0x8D7BE933, 3 | BRF_GRA },		 // 10

	{ "062-m1.bin",   0x020000, 0x76108B2F, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "062-v1.bin",   0x100000, 0xCC281AEF, 5 | BRF_SND },		 // 12 Sound data
};

STDROMPICKEXT(spinmast, spinmast, neogeo);
STD_ROM_FN(spinmast);

struct BurnDriver BurnDrvspinmast = {
	"spinmast", NULL, "neogeo", "1993",
	"Spin Master\0Miracle Adventure\0", NULL, "Data East Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, spinmastRomInfo, spinmastRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown 2

static struct BurnRomInfo samsho2RomDesc[] = {
	{ "063-p1.bin",   0x200000, 0x22368892, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "063-s1.bin",   0x020000, 0x64A5CD66, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "063-c1.bin",   0x200000, 0x86CD307C, 3 | BRF_GRA },		 //  2 Sprite data
	{ "063-c2.bin",   0x200000, 0xCDFCC4CA, 3 | BRF_GRA },		 //  3
	{ "063-c3.bin",   0x200000, 0x7A63CCC7, 3 | BRF_GRA },		 //  4
	{ "063-c4.bin",   0x200000, 0x751025CE, 3 | BRF_GRA },		 //  5
	{ "063-c5.bin",   0x200000, 0x20D3A475, 3 | BRF_GRA },		 //  6
	{ "063-c6.bin",   0x200000, 0xAE4C0A88, 3 | BRF_GRA },		 //  7
	{ "063-c7.bin",   0x200000, 0x2DF3CBCF, 3 | BRF_GRA },		 //  8
	{ "063-c8.bin",   0x200000, 0x1FFC6DFA, 3 | BRF_GRA },		 //  9

	{ "063-m1.bin",   0x020000, 0x56675098, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "063-v1.bin",   0x200000, 0x37703F91, 5 | BRF_SND },		 // 11	Sound data
	{ "063-v2.bin",   0x200000, 0x0142BDE8, 5 | BRF_SND },		 // 12
	{ "063-v3.bin",   0x200000, 0xD07FA5CA, 5 | BRF_SND },		 // 13
	{ "063-v4.bin",   0x100000, 0x24AAB4BB, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(samsho2, samsho2, neogeo);
STD_ROM_FN(samsho2);

struct BurnDriver BurnDrvSamSho2 = {
	"samsho2", NULL, "neogeo", "1994",
	"Samurai Shodown II\0Shin Samurai Spirits - Haohmaru jigokuhen\0", NULL, "SNK", "Neo Geo",
	L"Samurai Shodown II\0\u771F Samurai Spirits - \u8987\u738B\u4E38\u5730\u7344\u5909\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, samsho2RomInfo, samsho2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// World Heroes 2 Jet

static struct BurnRomInfo wh2jRomDesc[] = {
	{ "064-p1.bin",   0x200000, 0x385A2E86, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "064-s1.bin",   0x020000, 0x2A03998A, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "064-c1.bin",   0x200000, 0x2EC87CEA, 3 | BRF_GRA },		 //  2 Sprite data
	{ "064-c2.bin",   0x200000, 0x526B81AB, 3 | BRF_GRA },		 //  3
	{ "064-c3.bin",   0x200000, 0x436D1B31, 3 | BRF_GRA },		 //  4
	{ "064-c4.bin",   0x200000, 0xF9C8DD26, 3 | BRF_GRA },		 //  5
	{ "064-c5.bin",   0x200000, 0x8E34A9F4, 3 | BRF_GRA },		 //  6
	{ "064-c6.bin",   0x200000, 0xA43E4766, 3 | BRF_GRA },		 //  7
	{ "064-c7.bin",   0x200000, 0x59D97215, 3 | BRF_GRA },		 //  8
	{ "064-c8.bin",   0x200000, 0xFC092367, 3 | BRF_GRA },		 //  9

	{ "064-m1.bin",   0x020000, 0xD2EEC9D3, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "064-v1.bin",   0x200000, 0xAA277109, 5 | BRF_SND },		 // 11 Sound data
	{ "064-v2.bin",   0x200000, 0xB6527EDD, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(wh2j, wh2j, neogeo);
STD_ROM_FN(wh2j);

struct BurnDriver BurnDrvWH2J = {
	"wh2j", NULL, "neogeo", "1994",
	"World Heroes 2 Jet\0", NULL, "ADK / SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, wh2jRomInfo, wh2jRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Windjammers

static struct BurnRomInfo wjammersRomDesc[] = {
	{ "065-p1.bin",   0x100000, 0x6692C140, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "065-s1.bin",   0x020000, 0x074B5723, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "065-c1.bin",   0x100000, 0xC7650204, 3 | BRF_GRA },		 //  2 Sprite data
	{ "065-c2.bin",   0x100000, 0xD9F3E71D, 3 | BRF_GRA },		 //  3
	{ "065-c3.bin",   0x100000, 0x40986386, 3 | BRF_GRA },		 //  4
	{ "065-c4.bin",   0x100000, 0x715E15FF, 3 | BRF_GRA },		 //  5

	{ "065-m1.bin",   0x020000, 0x52C23CFC, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "065-v1.bin",   0x100000, 0xCE8B3698, 5 | BRF_SND },		 //  7 Sound data
	{ "065-v2.bin",   0x100000, 0x659F9B96, 5 | BRF_SND },		 //  8
	{ "065-v3.bin",   0x100000, 0x39F73061, 5 | BRF_SND },		 //  8
	{ "065-v4.bin",   0x100000, 0x5DEE7963, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(wjammers, wjammers, neogeo);
STD_ROM_FN(wjammers);

struct BurnDriver BurnDrvWJammers = {
	"wjammers", NULL, "neogeo", "1994",
	"Windjammers - flying disc game\0Flying Power Disc\0", NULL, "Data East Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, wjammersRomInfo, wjammersRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Karnov's Revenge

static struct BurnRomInfo karnovrRomDesc[] = {
	{ "066-p1.bin",   0x100000, 0x8C86FD22, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "066-s1.bin",   0x020000, 0xBAE5D5E5, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "066-c1.bin",   0x200000, 0x09DFE061, 3 | BRF_GRA },		 //  2 Sprite data
	{ "066-c2.bin",   0x200000, 0xE0F6682A, 3 | BRF_GRA },		 //  3
	{ "066-c3.bin",   0x200000, 0xA673B4F7, 3 | BRF_GRA },		 //  4
	{ "066-c4.bin",   0x200000, 0xCB3DC5F4, 3 | BRF_GRA },		 //  5
	{ "066-c5.bin",   0x200000, 0x9A28785D, 3 | BRF_GRA },		 //  6
	{ "066-c6.bin",   0x200000, 0xC15C01ED, 3 | BRF_GRA },		 //  7

	{ "066-m1.bin",   0x020000, 0x030BEAE4, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "066-v1.bin",   0x200000, 0x0B7EA37A, 5 | BRF_SND },		 //  9 Sound data
};

STDROMPICKEXT(karnovr, karnovr, neogeo);
STD_ROM_FN(karnovr);

struct BurnDriver BurnDrvKarnovR = {
	"karnovr", NULL, "neogeo", "1994",
	"Karnov's Revenge\0Fighter's History Dynamite\0", NULL, "Data East Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, karnovrRomInfo, karnovrRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Gururin

static struct BurnRomInfo gururinRomDesc[] = {
	{ "067-p1.bin",   0x080000, 0x4cea8a49, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "067-s1.bin",   0x020000, 0x4f0cbd58, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "067-c1.bin",   0x200000, 0x35866126, 3 | BRF_GRA },		 //  2 Sprite data
	{ "067-c2.bin",   0x200000, 0x9db64084, 3 | BRF_GRA },		 //  3

	{ "067-m1.bin",   0x010000, 0x833cdf1b, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "067-v1.bin",   0x080000, 0xcf23afd0, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(gururin, gururin, neogeo);
STD_ROM_FN(gururin);

struct BurnDriver BurnDrvGururin = {
	"gururin", NULL, "neogeo", "1994",
	"Gururin\0", NULL, "Face", "Neo Geo",
	L"\u3050\u308B\u308A\u3093\0Gururin\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, gururinRomInfo, gururinRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Power Spikes II

static struct BurnRomInfo pspikes2RomDesc[] = {
	{ "068-pg1.bin",  0x100000, 0x105a408f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "068-sg1.bin",  0x020000, 0x18082299, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "068-c1.bin",   0x100000, 0x7f250f76, 3 | BRF_GRA },		 //  2 Sprite data
	{ "068-c2.bin",   0x100000, 0x20912873, 3 | BRF_GRA },		 //  3
	{ "068-c3.bin",   0x100000, 0x4b641ba1, 3 | BRF_GRA },		 //  4
	{ "068-c4.bin",   0x100000, 0x35072596, 3 | BRF_GRA },		 //  5
	{ "068-c5.bin",   0x100000, 0x151dd624, 3 | BRF_GRA },		 //  6
	{ "068-c6.bin",   0x100000, 0xa6722604, 3 | BRF_GRA },		 //  7

	{ "068-mg1.bin",  0x020000, 0xb1c7911e, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "068-v1.bin",   0x100000, 0x2ced86df, 5 | BRF_SND },		 //  9 Sound data
	{ "068-v2.bin",   0x100000, 0x970851ab, 5 | BRF_SND },		 // 10
	{ "068-v3.bin",   0x100000, 0x81ff05aa, 5 | BRF_SND },		 // 11
};

STDROMPICKEXT(pspikes2, pspikes2, neogeo);
STD_ROM_FN(pspikes2);

struct BurnDriver BurnDrvPspikes2 = {
	"pspikes2", NULL, "neogeo", "1994",
	"Power Spikes II\0", NULL, "Video System Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, pspikes2RomInfo, pspikes2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fatal Fury 3

static struct BurnRomInfo fatfury3RomDesc[] = {
	{ "069-p1.bin",   0x100000, 0xa8bcfbbc, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "069-p2.bin",   0x200000, 0xdbe963ed, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "069-s1.bin",   0x020000, 0x0b33a800, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "069-c1.bin",   0x400000, 0xe302f93c, 3 | BRF_GRA },		 //  3 Sprite data
	{ "069-c2.bin",   0x400000, 0x1053a455, 3 | BRF_GRA },		 //  4
	{ "069-c3.bin",   0x400000, 0x1c0fde2f, 3 | BRF_GRA },		 //  5
	{ "069-c4.bin",   0x400000, 0xa25fc3d0, 3 | BRF_GRA },		 //  6
	{ "069-c5.bin",   0x200000, 0xb3ec6fa6, 3 | BRF_GRA },		 //  7
	{ "069-c6.bin",   0x200000, 0x69210441, 3 | BRF_GRA },		 //  8

	{ "069-m1.bin",   0x020000, 0xfce72926, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "069-v1.bin",   0x400000, 0x2bdbd4db, 5 | BRF_SND },		 // 10 Sound data
	{ "069-v2.bin",   0x400000, 0xa698a487, 5 | BRF_SND },		 // 11
	{ "069-v3.bin",   0x200000, 0x581c5304, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(fatfury3, fatfury3, neogeo);
STD_ROM_FN(fatfury3);

struct BurnDriver BurnDrvFatfury3 = {
	"fatfury3", NULL, "neogeo", "1995",
	"Fatal Fury 3 - road to the final victory\0Garou Densetsu 3\0", NULL, "SNK", "Neo Geo",
	L"Fatal Fury 3 - road to the final victory\0\u9913\u72FC\u4F1D\u8AAC\uFF13\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, fatfury3RomInfo, fatfury3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


/* ---------------------------------------------------------------------------------------

	Info from Billy Pitt's Neo-Geo proto page:
		  http://www.neobitz.com/protos/games/zupapa.htm

		A NEO-GEO action game designed by Face Corporation. It was shown at the 
	AOU Exposition in Japan on February 22nd, 1994 right alongside Gururin. However, 
	for some odd reason only Gururin was released back then. The game has cute 
	comical characters and colorful playfields. It plays very similar to Capcom's 
	Snow Brothers. It was dusted-off and picked up by SNK for release on MVS 
	format in 2001. So far, this is the only Neo-Geo un-released proto game that 
	finally saw an actual official release.

--------------------------------------------------------------------------------------- */

// Zupapa!

static struct BurnRomInfo zupapaRomDesc[] = {
	{ "070-p1.bin",   0x100000, 0x5A96203E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "070-c1.bin",   0x800000, 0xF8AD02D8, 3 | BRF_GRA },		 //  1 Sprite data
	{ "070-c2.bin",   0x800000, 0x70156DDE, 3 | BRF_GRA },		 //  2

	{ "070-m1.bin",   0x020000, 0x5A3B3191, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "070-v1.bin",   0x200000, 0xD3A7E1FF, 5 | BRF_SND },		 //  4 Sound data
};

STDROMPICKEXT(zupapa, zupapa, neogeo);
STD_ROM_FN(zupapa);

static int zupapaInit()
{
	nNeoProtectionXor = 0xBD;
	return NeoInit();
}

struct BurnDriver BurnDrvZupapa = {
	"zupapa", NULL, "neogeo", "2001",
	"Zupapa!\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, zupapaRomInfo, zupapaRomName, neogeoInputInfo, neogeoDIPInfo,
	zupapaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0071 Bang Bang Busters (prototype) 1994 Visco
// 0072 Last Odyssey Pinball Fantasia (prototype) 1995 Monolith


// Panic Bomber

static struct BurnRomInfo panicbomRomDesc[] = {
	{ "073-p1.bin",   0x040000, 0x0b21130d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "073-s1.bin",   0x020000, 0xb876de7e, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "073-c1.bin",   0x100000, 0x8582e1b5, 3 | BRF_GRA },		 //  2 Sprite data
	{ "073-c2.bin",   0x100000, 0xe15a093b, 3 | BRF_GRA },		 //  3

	{ "073-m1.bin",   0x020000, 0x3cdf5d88, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "073-v1.bin",   0x200000, 0x7fc86d2f, 5 | BRF_SND },		 //  5 Sound data
	{ "073-v2.bin",   0x100000, 0x082adfc7, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(panicbom, panicbom, neogeo);
STD_ROM_FN(panicbom);

struct BurnDriver BurnDrvPanicbom = {
	"panicbom", NULL, "neogeo", "1994",
	"Panic Bomber\0", NULL, "Hudson Soft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, panicbomRomInfo, panicbomRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Aggressors of Dark Kombat / Tsuukai GANGAN Koushinkyoku

static struct BurnRomInfo aodkRomDesc[] = {
	{ "074-p1.bin",   0x200000, 0x62369553, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "074-s1.bin",   0x020000, 0x96148D2B, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "074-c1.bin",   0x200000, 0xA0B39344, 3 | BRF_GRA },		 //  2 Sprite data
	{ "074-c2.bin",   0x200000, 0x203F6074, 3 | BRF_GRA },		 //  3
	{ "074-c3.bin",   0x200000, 0x7FFF4D41, 3 | BRF_GRA },		 //  4
	{ "074-c4.bin",   0x200000, 0x48DB3E0A, 3 | BRF_GRA },		 //  5
	{ "074-c5.bin",   0x200000, 0xC74C5E51, 3 | BRF_GRA },		 //  6
	{ "074-c6.bin",   0x200000, 0x73E8E7E0, 3 | BRF_GRA },		 //  7
	{ "074-c7.bin",   0x200000, 0xAC7DAA01, 3 | BRF_GRA },		 //  8
	{ "074-c8.bin",   0x200000, 0x14E7AD71, 3 | BRF_GRA },		 //  9

	{ "074-m1.bin",   0x020000, 0x5A52A9D1, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "074-v1.bin",   0x200000, 0x7675B8FA, 5 | BRF_SND },		 // 11 Sound data
	{ "074-v2.bin",   0x200000, 0xA9DA86E9, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(aodk, aodk, neogeo);
STD_ROM_FN(aodk);

struct BurnDriver BurnDrvAODK = {
	"aodk", NULL, "neogeo", "1994",
	"Aggressors of Dark Kombat\0Tsuukai GANGAN Koushinkyoku\0", NULL, "ADK / SNK", "Neo Geo",
	L"Aggressors of Dark Kombat\0\u75DB\u5FEB\uFF27\uFF41\uFF4E\uFF47\uFF41\uFF4E\u884C\u9032\u66F2\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, aodkRomInfo, aodkRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sonic Wings 2

static struct BurnRomInfo sonicwi2RomDesc[] = {
	{ "075-p1.bin",   0x200000, 0x92871738, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "075-s1.bin",   0x020000, 0xc9eec367, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "075-c1.bin",   0x200000, 0x3278e73e, 3 | BRF_GRA },		 //  2 Sprite data
	{ "075-c2.bin",   0x200000, 0xfe6355d6, 3 | BRF_GRA },		 //  3
	{ "075-c3.bin",   0x200000, 0xc1b438f1, 3 | BRF_GRA },		 //  4
	{ "075-c4.bin",   0x200000, 0x1f777206, 3 | BRF_GRA },		 //  5

	{ "075-m1.bin",   0x020000, 0xbb828df1, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "075-v1.bin",   0x200000, 0x7577e949, 5 | BRF_SND },		 //  7 Sound data
	{ "075-v2.bin",   0x080000, 0x6d0a728e, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(sonicwi2, sonicwi2, neogeo);
STD_ROM_FN(sonicwi2);

struct BurnDriver BurnDrvSonicwi2 = {
	"sonicwi2", NULL, "neogeo", "1994",
	"Aero Fighters 2\0Sonic Wings 2\0", NULL, "Video System Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, sonicwi2RomInfo, sonicwi2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Zed Blade

static struct BurnRomInfo zedbladeRomDesc[] = {
	{ "076-p1.bin",   0x080000, 0xd7c1effd, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "076-s1.bin",   0x020000, 0xf4c25dd5, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "076-c1.bin",   0x200000, 0x4d9cb038, 3 | BRF_GRA },		 //  2 Sprite data
	{ "076-c2.bin",   0x200000, 0x09233884, 3 | BRF_GRA },		 //  3
	{ "076-c3.bin",   0x200000, 0xd06431e3, 3 | BRF_GRA },		 //  4
	{ "076-c4.bin",   0x200000, 0x4b1c089b, 3 | BRF_GRA },		 //  5

	{ "076-m1.bin",   0x020000, 0x7b5f3d0a, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "076-v1.bin",   0x200000, 0x1a21d90c, 5 | BRF_SND },		 //  7	Sound data
	{ "076-v2.bin",   0x200000, 0xb61686c3, 5 | BRF_SND },		 //  8
	{ "076-v3.bin",   0x100000, 0xb90658fa, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(zedblade, zedblade, neogeo);
STD_ROM_FN(zedblade);

struct BurnDriver BurnDrvZedblade = {
	"zedblade", NULL, "neogeo", "1994",
	"Zed Blade\0Operation Ragnarok\0", NULL, "NMK", "Neo Geo",
	L"Zed Blade\0Operation Ragnarok\0\u4F5C\u6226\u540D\uFF02\u30E9\u30B0\u30CA\u30ED\u30AF\uFF02\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, zedbladeRomInfo, zedbladeRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


//  0077 The Warlocks of the Fates (prototype) 1995 Astec


// Galaxy Fight

static struct BurnRomInfo galaxyfgRomDesc[] = {
	{ "078-p1.bin",   0x200000, 0x45906309, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "078-s1.bin",   0x020000, 0x72f8923e, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "078-c1.bin",   0x200000, 0xc890c7c0, 3 | BRF_GRA },		 //  2 Sprite data
	{ "078-c2.bin",   0x200000, 0xb6d25419, 3 | BRF_GRA },		 //  3
	{ "078-c3.bin",   0x200000, 0x9d87e761, 3 | BRF_GRA },		 //  4
	{ "078-c4.bin",   0x200000, 0x765d7cb8, 3 | BRF_GRA },		 //  5
	{ "078-c5.bin",   0x200000, 0xe6b77e6a, 3 | BRF_GRA },		 //  6
	{ "078-c6.bin",   0x200000, 0xd779a181, 3 | BRF_GRA },		 //  7
	{ "078-c7.bin",   0x100000, 0x4f27d580, 3 | BRF_GRA },		 //  8
	{ "078-c8.bin",   0x100000, 0x0a7cc0d8, 3 | BRF_GRA },		 //  9

	{ "078-m1.bin",   0x020000, 0x8e9e3b10, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "078-v1.bin",   0x200000, 0xe3b735ac, 5 | BRF_SND },		 // 11	Sound data
	{ "078-v2.bin",   0x200000, 0x6a8e78c2, 5 | BRF_SND },		 // 12
	{ "078-v3.bin",   0x100000, 0x70bca656, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(galaxyfg, galaxyfg, neogeo);
STD_ROM_FN(galaxyfg);

struct BurnDriver BurnDrvGalaxyfg = {
	"galaxyfg", NULL, "neogeo", "1995",
	"Galaxy Fight - universal warriors\0", NULL, "Sunsoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, galaxyfgRomInfo, galaxyfgRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Street Hoop / Street Slam / Dunk Dream

static struct BurnRomInfo strhoopRomDesc[] = {
	{ "079-p1.bin",   0x100000, 0x5E78328E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "079-s1.bin",   0x020000, 0x3AC06665, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "079-c1.bin",   0x200000, 0x0581C72A, 3 | BRF_GRA },		 //  2 Sprite data
	{ "079-c2.bin",   0x200000, 0x5B9B8FB6, 3 | BRF_GRA },		 //  3
	{ "079-c3.bin",   0x200000, 0xCD65BB62, 3 | BRF_GRA },		 //  4
	{ "079-c4.bin",   0x200000, 0xA4C90213, 3 | BRF_GRA },		 //  5

	{ "079-m1.bin",   0x010000, 0x1A5F08DB, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "079-v1.bin",   0x200000, 0x718A2400, 5 | BRF_SND },		 //  7 Sound data
	{ "079-v2.bin",   0x080000, 0xB19884F8, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(strhoop, strhoop, neogeo);
STD_ROM_FN(strhoop);

struct BurnDriver BurnDrvStrHoop = {
	"strhoop", NULL, "neogeo", "1994",
	"Street Hoop\0Street Slam\0Dunk Dream\0", NULL, "Data East Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, strhoopRomInfo, strhoopRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Quiz King of Fighters

static struct BurnRomInfo quizkofRomDesc[] = {
	{ "080-p1.bin",   0x100000, 0x4440315e, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "080-s1.bin",   0x020000, 0xd7b86102, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "080-c1.bin",   0x200000, 0xea1d764a, 3 | BRF_GRA },		 //  2 Sprite data
	{ "080-c2.bin",   0x200000, 0xc78c49da, 3 | BRF_GRA },		 //  3
	{ "080-c3.bin",   0x200000, 0xb4851bfe, 3 | BRF_GRA },		 //  4
	{ "080-c4.bin",   0x200000, 0xca6f5460, 3 | BRF_GRA },		 //  5

	{ "080-m1.bin",   0x020000, 0xf5f44172, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "080-v1.bin",   0x200000, 0x0be18f60, 5 | BRF_SND },		 //  7 Sound data
	{ "080-v2.bin",   0x200000, 0x4abde3ff, 5 | BRF_SND },		 //  8
	{ "080-v3.bin",   0x200000, 0xf02844e2, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(quizkof, quizkof, neogeo);
STD_ROM_FN(quizkof);

struct BurnDriver BurnDrvQuizkof = {
	"quizkof", NULL, "neogeo", "1995",
	"Quiz King of Fighters\0", NULL, "Saurus", "Neo Geo",
	L"\u30AF\u30A4\u30BA\u30AD\u30F3\u30B0\u30AA\u30D6\u30D5\u30A1\u30A4\u30BF\u30FC\u30BA\0Quiz King of Fighters\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, quizkofRomInfo, quizkofRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Super Sidekicks 3

static struct BurnRomInfo ssideki3RomDesc[] = {
	{ "081-p1.bin",   0x200000, 0x6bc27a3d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "081-s1.bin",   0x020000, 0x7626da34, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "081-c1.bin",   0x200000, 0x1fb68ebe, 3 | BRF_GRA },		 //  2 Sprite data
	{ "081-c2.bin",   0x200000, 0xb28d928f, 3 | BRF_GRA },		 //  3
	{ "081-c3.bin",   0x200000, 0x3b2572e8, 3 | BRF_GRA },		 //  4
	{ "081-c4.bin",   0x200000, 0x47d26a7c, 3 | BRF_GRA },		 //  5
	{ "081-c5.bin",   0x200000, 0x17d42f0d, 3 | BRF_GRA },		 //  6
	{ "081-c6.bin",   0x200000, 0x6b53fb75, 3 | BRF_GRA },		 //  7

	{ "081-m1.bin",   0x020000, 0x82fcd863, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "081-v1.bin",   0x200000, 0x201fa1e1, 5 | BRF_SND },		 //  9 Sound data
	{ "081-v2.bin",   0x200000, 0xacf29d96, 5 | BRF_SND },		 //  10
	{ "081-v3.bin",   0x200000, 0xe524e415, 5 | BRF_SND },		 //  11
};

STDROMPICKEXT(ssideki3, ssideki3, neogeo);
STD_ROM_FN(ssideki3);

struct BurnDriver BurnDrvSsideki3 = {
	"ssideki3", NULL, "neogeo", "1995",
	"Super Sidekicks 3 - the next glory\0Tokuten Ou 3 - eikoue no michi\0", NULL, "SNK", "Neo Geo",
	L"Super Sidekicks 3 - the next glory\0\u5F97\u70B9\u738B\uFF13 - \u6804\u5149\u3078\u306E\u6311\u6226\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ssideki3RomInfo, ssideki3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Double Dragon

static struct BurnRomInfo doubledrRomDesc[] = {
	{ "082-p1.bin",   0x200000, 0x34ab832a, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "082-s1.bin",   0x020000, 0xbef995c5, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "082-c1.bin",   0x200000, 0xb478c725, 3 | BRF_GRA },		 //  2 Sprite data
	{ "082-c2.bin",   0x200000, 0x2857da32, 3 | BRF_GRA },		 //  3
	{ "082-c3.bin",   0x200000, 0x8b0d378e, 3 | BRF_GRA },		 //  4
	{ "082-c4.bin",   0x200000, 0xc7d2f596, 3 | BRF_GRA },		 //  5
	{ "082-c5.bin",   0x200000, 0xec87bff6, 3 | BRF_GRA },		 //  6
	{ "082-c6.bin",   0x200000, 0x844a8a11, 3 | BRF_GRA },		 //  7
	{ "082-c7.bin",   0x100000, 0x727c4d02, 3 | BRF_GRA },		 //  8
	{ "082-c8.bin",   0x100000, 0x69a5fa37, 3 | BRF_GRA },		 //  9

	{ "082-m1.bin",   0x020000, 0x10b144de, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "082-v1.bin",   0x200000, 0xcc1128e4, 5 | BRF_SND },		 // 11 Sound data
	{ "082-v2.bin",   0x200000, 0xc3ff5554, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(doubledr, doubledr, neogeo);
STD_ROM_FN(doubledr);

struct BurnDriver BurnDrvDoubledr = {
	"doubledr", NULL, "neogeo", "1995",
	"Double Dragon\0", NULL, "Technos", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, doubledrRomInfo, doubledrRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzle Bobble

static struct BurnRomInfo pbobblenRomDesc[] = {
	{ "083-p1.bin",   0x040000, 0x7c3c34e1, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "083-s1.bin",   0x020000, 0x9caae538, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "083-c5.bin",   0x080000, 0xe89ad494, 3 | BRF_GRA },		 //  2 Sprite data
	{ "083-c6.bin",   0x080000, 0x4b42d7eb, 3 | BRF_GRA },		 //  3

	{ "083-m1.bin",   0x010000, 0x129e6054, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "083-v3.bin",   0x100000, 0x0840cbc4, 5 | BRF_SND },		 //  5	Sound data
	{ "083-v4.bin",   0x080000, 0x0a548948, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(pbobblen, pbobblen, neogeo);
STD_ROM_FN(pbobblen);

struct BurnDriver BurnDrvPbobblen = {
	"pbobblen", NULL, "neogeo", "1994",
	"Puzzle Bobble\0Bust-A-Move (set 1)\0", NULL, "Taito", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, pbobblenRomInfo, pbobblenRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzle Bobble (alternate version)

static struct BurnRomInfo pbobblnaRomDesc[] = {
	{ "083-p1.rom",   0x040000, 0xd6efe86f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "083-s1.bin",   0x020000, 0x9caae538, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "083-c5.bin",   0x080000, 0xe89ad494, 3 | BRF_GRA },		 //  2 Sprite data
	{ "083-c6.bin",   0x080000, 0x4b42d7eb, 3 | BRF_GRA },		 //  3

	{ "083-m1.bin",   0x010000, 0x129e6054, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "083-v3.bin",   0x100000, 0x0840cbc4, 5 | BRF_SND },		 //  5	Sound data
	{ "083-v4.bin",   0x080000, 0x0a548948, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(pbobblna, pbobblna, neogeo);
STD_ROM_FN(pbobblna);

struct BurnDriver BurnDrvPbobblna = {
	"pbobblna", "pbobblen", "neogeo", "1994",
	"Puzzle Bobble\0Bust-A-Move (set 2)\0", "Alternate version", "Taito", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, pbobblnaRomInfo, pbobblnaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '95

static struct BurnRomInfo kof95RomDesc[] = {
	{ "084-p1.bin",   0x200000, 0x5E54CF95, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "084-s1.bin",   0x020000, 0xDE716f8A, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "084-c1.bin",   0x400000, 0xFE087E32, 3 | BRF_GRA },		 //  2 Sprite data
	{ "084-c2.bin",   0x400000, 0x07864E09, 3 | BRF_GRA },		 //  3
	{ "084-c3.bin",   0x400000, 0xA4E65D1B, 3 | BRF_GRA },		 //  4
	{ "084-c4.bin",   0x400000, 0xC1ACE468, 3 | BRF_GRA },		 //  5
	{ "084-c5.bin",   0x200000, 0x8A2C1EDC, 3 | BRF_GRA },		 //  6
	{ "084-c6.bin",   0x200000, 0xF593AC35, 3 | BRF_GRA },		 //  7
	{ "084-c7.bin",   0x100000, 0x9904025F, 3 | BRF_GRA },		 //  8
	{ "084-c8.bin",   0x100000, 0x78EB0F9B, 3 | BRF_GRA },		 //  9

	{ "084-m1.bin",   0x020000, 0x6F2d7429, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "084-v1.bin",   0x400000, 0x84861B56, 5 | BRF_SND },		 // 11 Sound data
	{ "084-v2.bin",   0x200000, 0xB38a2803, 5 | BRF_SND },		 // 12
	{ "084-v3.bin",   0x100000, 0xD683A338, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(kof95, kof95, neogeo);
STD_ROM_FN(kof95);

struct BurnDriver BurnDrvKof95 = {
	"kof95", NULL, "neogeo", "1995",
	"The King of Fighters '95 (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, kof95RomInfo, kof95RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '95 (alternate version)

static struct BurnRomInfo kof95aRomDesc[] = {
	{ "084a-p1.bin",  0x200000, 0x2CBA2716, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "084-s1.bin",   0x020000, 0xDE716f8A, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "084-c1.bin",   0x400000, 0xFE087E32, 3 | BRF_GRA },		 //  2 Sprite data
	{ "084-c2.bin",   0x400000, 0x07864E09, 3 | BRF_GRA },		 //  3
	{ "084-c3.bin",   0x400000, 0xA4E65D1B, 3 | BRF_GRA },		 //  4
	{ "084-c4.bin",   0x400000, 0xC1ACE468, 3 | BRF_GRA },		 //  5
	{ "084-c5.bin",   0x200000, 0x8A2C1EDC, 3 | BRF_GRA },		 //  6
	{ "084-c6.bin",   0x200000, 0xF593AC35, 3 | BRF_GRA },		 //  7
	{ "084-c7.bin",   0x100000, 0x9904025F, 3 | BRF_GRA },		 //  8
	{ "084-c8.bin",   0x100000, 0x78EB0F9B, 3 | BRF_GRA },		 //  9

	{ "084-m1.bin",   0x020000, 0x6F2d7429, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "084-v1.bin",   0x400000, 0x84861B56, 5 | BRF_SND },		 // 11 Sound data
	{ "084-v2.bin",   0x200000, 0xB38a2803, 5 | BRF_SND },		 // 12
	{ "084-v3.bin",   0x100000, 0xD683A338, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(kof95a, kof95a, neogeo);
STD_ROM_FN(kof95a);

struct BurnDriver BurnDrvKof95a = {
	"kof95a", "kof95", "neogeo", "1995",
	"The King of Fighters '95 (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, kof95aRomInfo, kof95aRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0085 Shinsetsu Samurai Spirits Bushidoretsuden / Samurai Shodown RPG (CD only)


// Tecmo World Soccer 96

static struct BurnRomInfo tws96RomDesc[] = {
	{ "086-p1.bin",   0x100000, 0x03e20ab6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "086-s1.bin",   0x020000, 0x6f5e2b3a, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "086-c1.bin",   0x400000, 0x2611bc2a, 3 | BRF_GRA },		 //  2 Sprite data
	{ "086-c2.bin",   0x400000, 0x6b0d6827, 3 | BRF_GRA },		 //  3
	{ "086-c3.bin",   0x100000, 0x750ddc0c, 3 | BRF_GRA },		 //  4
	{ "086-c4.bin",   0x100000, 0x7a6e7d82, 3 | BRF_GRA },		 //  5

	{ "086-m1.bin",   0x010000, 0x860ba8c7, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "086-v1.bin",   0x200000, 0x97bf1986, 5 | BRF_SND },		 //  7 Sound data
	{ "086-v2.bin",   0x200000, 0xb7eb05df, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(tws96, tws96, neogeo);
STD_ROM_FN(tws96);

struct BurnDriver BurnDrvTws96 = {
	"tws96", NULL, "neogeo", "1996",
	"Tecmo World Soccer '96\0", NULL, "Tecmo", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, tws96RomInfo, tws96RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown 3

static struct BurnRomInfo samsho3RomDesc[] = {
	{ "087-p1.bin",   0x100000, 0x282A336E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "087-p2.bin",   0x200000, 0x9BBE27E0, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "087-s1.bin",   0x020000, 0x74EC7D9F, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "087-c1.bin",   0x400000, 0x07A233BC, 3 | BRF_GRA },		 //  3 Sprite data
	{ "087-c2.bin",   0x400000, 0x7a413592, 3 | BRF_GRA },		 //  4
	{ "087-c3.bin",   0x400000, 0x8b793796, 3 | BRF_GRA },		 //  5
	{ "087-c4.bin",   0x400000, 0x728fbf11, 3 | BRF_GRA },		 //  6
	{ "087-c5.bin",   0x400000, 0x172ab180, 3 | BRF_GRA },		 //  7
	{ "087-c6.bin",   0x400000, 0x002ff8f3, 3 | BRF_GRA },		 //  8
	{ "087-c7.bin",   0x100000, 0xAE450e3d, 3 | BRF_GRA },		 //  9
	{ "087-c8.bin",   0x100000, 0xA9E82717, 3 | BRF_GRA },		 // 10

	{ "087-m1.bin",   0x020000, 0x8E6440EB, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "087-v1.bin",   0x400000, 0x84BDD9A0, 5 | BRF_SND },		 // 12	Sound data
	{ "087-v2.bin",   0x200000, 0xAC0F261A, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(samsho3, samsho3, neogeo);
STD_ROM_FN(samsho3);

struct BurnDriver BurnDrvSamSho3 = {
	"samsho3", NULL, "neogeo", "1995",
	"Samurai Shodown III\0Samurai Spirits - Zankurou musouken (set 1)\0", NULL, "SNK", "Neo Geo",
	L"Samurai Shodown III\0\u30B5\u30E0\u30E9\u30A4\u30B9\u30D4\u30EA\u30C3\u30C4 - \u65AC\u7D05\u90CE\u7121\u53CC\u5263\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, samsho3RomInfo, samsho3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown 3 (alternate version)

static struct BurnRomInfo samsho3aRomDesc[] = {
	{ "087-ep1.bin",  0x080000, 0x23E09BB8, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "087-ep2.bin",  0x080000, 0x256F5302, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "087-ep3.bin",  0x080000, 0xBF2DB5DD, 1 | BRF_ESS | BRF_PRG }, //  2
	{ "087-ep4.bin",  0x080000, 0x53E60C58, 1 | BRF_ESS | BRF_PRG }, //  3
	{ "087-p5.bin",   0x100000, 0xE86CA4AF, 1 | BRF_ESS | BRF_PRG }, //  4

	{ "087-s1.bin",   0x020000, 0x74EC7D9F, 2 | BRF_GRA },		 //  5 Text layer tiles

	{ "087-c1.bin",   0x400000, 0x07A233BC, 3 | BRF_GRA },		 //  6 Sprite data
	{ "087-c2.bin",   0x400000, 0x7a413592, 3 | BRF_GRA },		 //  7
	{ "087-c3.bin",   0x400000, 0x8b793796, 3 | BRF_GRA },		 //  8
	{ "087-c4.bin",   0x400000, 0x728fbf11, 3 | BRF_GRA },		 //  9
	{ "087-c5.bin",   0x400000, 0x172ab180, 3 | BRF_GRA },		 // 10
	{ "087-c6.bin",   0x400000, 0x002ff8f3, 3 | BRF_GRA },		 // 11
	{ "087-c7.bin",   0x100000, 0xAE450e3d, 3 | BRF_GRA },		 // 12
	{ "087-c8.bin",   0x100000, 0xA9E82717, 3 | BRF_GRA },		 // 13

	{ "087-m1.bin",   0x020000, 0x8E6440EB, 4 | BRF_ESS | BRF_PRG }, // 14 Z80 code

	{ "087-v1.bin",   0x400000, 0x84BDD9A0, 5 | BRF_SND },		 // 15	Sound data
	{ "087-v2.bin",   0x200000, 0xAC0F261A, 5 | BRF_SND },		 // 16
};

STDROMPICKEXT(samsho3a, samsho3a, neogeo);
STD_ROM_FN(samsho3a);

struct BurnDriver BurnDrvSamSho3a = {
	"samsho3a", "samsho3", "neogeo", "1995",
	"Samurai Shodown III\0Samurai Spirits - Zankurou musouken\0Fighters Swords (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"Samurai Shodown III\0\u30B5\u30E0\u30E9\u30A4\u30B9\u30D4\u30EA\u30C3\u30C4 - \u65AC\u7D05\u90CE\u7121\u53CC\u5263\0Fighters Swords\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, samsho3aRomInfo, samsho3aRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Fighting Swords (Korean version)

static struct BurnRomInfo fswordsRomDesc[] = {
	{ "087-p1k.bin",  0x100000, 0xC8E7C075, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "087-p2.bin",   0x200000, 0x9BBE27E0, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "087-s1.bin",   0x020000, 0x74EC7D9F, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "087-c1.bin",   0x400000, 0x07A233BC, 3 | BRF_GRA },		 //  3 Sprite data
	{ "087-c2.bin",   0x400000, 0x7a413592, 3 | BRF_GRA },		 //  4
	{ "087-c3.bin",   0x400000, 0x8b793796, 3 | BRF_GRA },		 //  5
	{ "087-c4.bin",   0x400000, 0x728fbf11, 3 | BRF_GRA },		 //  6
	{ "087-c5.bin",   0x400000, 0x172ab180, 3 | BRF_GRA },		 //  7
	{ "087-c6.bin",   0x400000, 0x002ff8f3, 3 | BRF_GRA },		 //  8
	{ "087-c7.bin",   0x100000, 0xAE450e3d, 3 | BRF_GRA },		 //  9
	{ "087-c8.bin",   0x100000, 0xA9E82717, 3 | BRF_GRA },		 // 10

	{ "087-m1.bin",   0x020000, 0x8E6440EB, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "087-v1.bin",   0x400000, 0x84BDD9A0, 5 | BRF_SND },		 // 12	Sound data
	{ "087-v2.bin",   0x200000, 0xAC0F261A, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(fswords, fswords, neogeo);
STD_ROM_FN(fswords);

struct BurnDriver BurnDrvfswords = {
	"fswords", "samsho3", "neogeo", "1995",
	"Fighting Swords\0", "Korean version of \"Samurai Shodown III\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, fswordsRomInfo, fswordsRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Stakes Winner

static struct BurnRomInfo stakwinRomDesc[] = {
	{ "088-p1.bin",   0x200000, 0xbd5814f6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "088-s1.bin",   0x020000, 0x073cb208, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "088-c1.bin",   0x200000, 0x6e733421, 3 | BRF_GRA },		 //  2 Sprite data
	{ "088-c2.bin",   0x200000, 0x4d865347, 3 | BRF_GRA },		 //  3
	{ "088-c3.bin",   0x200000, 0x8fa5a9eb, 3 | BRF_GRA },		 //  4
	{ "088-c4.bin",   0x200000, 0x4604f0dc, 3 | BRF_GRA },		 //  5

	{ "088-m1.bin",   0x020000, 0x2fe1f499, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "088-v1.bin",   0x200000, 0xb7785023, 5 | BRF_SND },		 //  7 Sound data
};

STDROMPICKEXT(stakwin, stakwin, neogeo);
STD_ROM_FN(stakwin);

struct BurnDriver BurnDrvStakwin = {
	"stakwin", NULL, "neogeo", "1995",
	"Stakes Winner\0", NULL, "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, stakwinRomInfo, stakwinRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*-----------------------------------------------------------------------------

   The protection of this game involves locking write access to a
   particular byte in the Backup RAM on normal MVS hardware.  If the game
   can't write to the particular address, it doesn't have any problems.
   The Battery-Backed RAM is mapped to address 0xD00000 - 0xD0FFFF.

-----------------------------------------------------------------------------*/

// Pulstar

static struct BurnRomInfo pulstarRomDesc[] = {
	{ "089-p1.bin",   0x100000, 0x5E5847A2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "089-p2.bin",   0x200000, 0x028B774C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "089-s1.bin",   0x020000, 0xC79FC2C8, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "089-c1.bin",   0x400000, 0xF4E97332, 3 | BRF_GRA },		 //  3 Sprite data
	{ "089-c2.bin",   0x400000, 0x836D14DA, 3 | BRF_GRA },		 //  4
	{ "089-c3.bin",   0x400000, 0x913611C4, 3 | BRF_GRA },		 //  5
	{ "089-c4.bin",   0x400000, 0x44CEF0E3, 3 | BRF_GRA },		 //  6
	{ "089-c5.bin",   0x400000, 0x89BAA1d7, 3 | BRF_GRA },		 //  7
	{ "089-c6.bin",   0x400000, 0xB2594d56, 3 | BRF_GRA },		 //  8
	{ "089-c7.bin",   0x200000, 0x6A5618CA, 3 | BRF_GRA },		 //  9
	{ "089-c8.bin",   0x200000, 0xA223572D, 3 | BRF_GRA },		 // 10

	{ "089-m1.bin",   0x020000, 0xFF3DF7C7, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "089-v1.bin",   0x400000, 0xB458DED2, 5 | BRF_SND },		 // 12	Sound data
	{ "089-v2.bin",   0x400000, 0x9D2DB551, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(pulstar, pulstar, neogeo);
STD_ROM_FN(pulstar);

struct BurnDriver BurnDrvPulstar = {
	"pulstar", NULL, "neogeo", "1995",
	"Pulstar\0", NULL, "Aicom", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, pulstarRomInfo, pulstarRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// World Heroes Perfect

static struct BurnRomInfo whpRomDesc[] = {
	{ "090-p1.bin",   0x200000, 0xAFAA4702, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "090-s1.bin",   0x020000, 0x174A880F, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "090-c1.bin",   0x400000, 0xCD30ED9B, 3 | BRF_GRA },		 //  2 Sprite data
	{ "090-c2.bin",   0x400000, 0x10EED5EE, 3 | BRF_GRA },		 //  3
	{ "090-c3.bin",   0x200000, 0x436D1B31, 3 | BRF_GRA },		 //  4
	{ "090-c4.bin",   0x200000, 0xF9C8DD26, 3 | BRF_GRA },		 //  5
	{ "090-c5.bin",   0x200000, 0x8E34A9F4, 3 | BRF_GRA },		 //  6
	{ "090-c6.bin",   0x200000, 0xA43E4766, 3 | BRF_GRA },		 //  7
	{ "090-c7.bin",   0x200000, 0x59D97215, 3 | BRF_GRA },		 //  8
	{ "090-c8.bin",   0x200000, 0xFC092367, 3 | BRF_GRA },		 //  9

	{ "090-m1.bin",   0x020000, 0x28065668, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "090-v1.bin",   0x200000, 0x30CF2709, 5 | BRF_SND },		 // 11 Sound data
	{ "090-v2.bin",   0x200000, 0xB6527EDD, 5 | BRF_SND },		 // 12
	{ "090-v3.bin",   0x200000, 0x1908A7CE, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(whp, whp, neogeo);
STD_ROM_FN(whp);

struct BurnDriver BurnDrvWHP = {
	"whp", NULL, "neogeo", "1995",
	"World Heroes Perfect\0", NULL, "ADK / SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, whpRomInfo, whpRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0091


// Kabuki Klash - far east of eden

static struct BurnRomInfo kabukiklRomDesc[] = {
	{ "092-p1.bin",   0x200000, 0x28EC9B77, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "092-s1.bin",   0x020000, 0xA3D68EE2, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "092-c1.bin",   0x400000, 0x2A9FAB01, 3 | BRF_GRA },		 //  2 Sprite data
	{ "092-c2.bin",   0x400000, 0x6D2BAC02, 3 | BRF_GRA },		 //  3
	{ "092-c3.bin",   0x400000, 0x5DA735d6, 3 | BRF_GRA },		 //  4
	{ "092-c4.bin",   0x400000, 0xDE07F997, 3 | BRF_GRA },		 //  5

	{ "092-m1.bin",   0x020000, 0x91957EF6, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "092-v1.bin",   0x200000, 0x69E90596, 5 | BRF_SND },		 //  7 Sound data
	{ "092-v2.bin",   0x200000, 0x7ABDB75D, 5 | BRF_SND },		 //  8
	{ "092-v3.bin",   0x200000, 0xECCC98D3, 5 | BRF_SND },		 //  9
	{ "092-v4.bin",   0x100000, 0xA7C9C949, 5 | BRF_SND },		 // 10
};

STDROMPICKEXT(kabukikl, kabukikl, neogeo);
STD_ROM_FN(kabukikl);

struct BurnDriver BurnDrvKabukiKl = {
	"kabukikl", NULL, "neogeo", "1995",
	"Kabuki Klash - far east of eden\0tengai makyou - Shinden\0", NULL, "Hudson Soft", "Neo Geo",
	L"Kabuki Klash - far east of eden\0\u5929\u5916\u9B54\u5883 - \u771F\u4F1D\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, kabukiklRomInfo, kabukiklRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo Bomberman

static struct BurnRomInfo neobombeRomDesc[] = {
	{ "093-p1.bin",   0x100000, 0xa1a71d0d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "093-s1.bin",   0x020000, 0x4b3fa119, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "093-c1.bin",   0x400000, 0xd1f328f8, 3 | BRF_GRA },		 //  2 Sprite data
	{ "093-c2.bin",   0x400000, 0x82c49540, 3 | BRF_GRA },		 //  3
	{ "093-c3.bin",   0x080000, 0xe37578c5, 3 | BRF_GRA },		 //  4
	{ "093-c4.bin",   0x080000, 0x59826783, 3 | BRF_GRA },		 //  5

	{ "093-m1.bin",   0x020000, 0xe81e780b, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "093-v1.bin",   0x400000, 0x02abd4b0, 5 | BRF_SND },		 //  7 Sound data
	{ "093-v2.bin",   0x200000, 0xa92b8b3d, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(neobombe, neobombe, neogeo);
STD_ROM_FN(neobombe);

struct BurnDriver BurnDrvNeobombe = {
	"neobombe", NULL, "neogeo", "1997",
	"Neo Bomberman\0", NULL, "Hudson Soft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neobombeRomInfo, neobombeRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Voltage Fighter - Gowcaizer

static struct BurnRomInfo gowcaizrRomDesc[] = {
	{ "094-p1.bin",   0x200000, 0x33019545, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "094-s1.bin",   0x020000, 0x2F8748A2, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "094-c1.bin",   0x200000, 0x042F6AF5, 3 | BRF_GRA },		 //  2 Sprite data
	{ "094-c2.bin",   0x200000, 0x0FBCD046, 3 | BRF_GRA },		 //  3
	{ "094-c3.bin",   0x200000, 0x58BFBAA1, 3 | BRF_GRA },		 //  4
	{ "094-c4.bin",   0x200000, 0x9451EE73, 3 | BRF_GRA },		 //  5
	{ "094-c5.bin",   0x200000, 0xFF9CF48C, 3 | BRF_GRA },		 //  6
	{ "094-c6.bin",   0x200000, 0x31BBD918, 3 | BRF_GRA },		 //  7
	{ "094-c7.bin",   0x200000, 0x2091EC04, 3 | BRF_GRA },		 //  8
	{ "094-c8.bin",   0x200000, 0x0D31DEE6, 3 | BRF_GRA },		 //  9

	{ "094-m1.bin",   0x020000, 0x78C851CB, 4 | BRF_ESS | BRF_PRG }, //  10 Z80 code

	{ "094-v1.bin",   0x200000, 0x6C31223C, 5 | BRF_SND },		 //  11 Sound data
	{ "094-v2.bin",   0x200000, 0x8EDB776C, 5 | BRF_SND },		 //  12
	{ "094-v3.bin",   0x100000, 0xC63B9285, 5 | BRF_SND },		 //  13
};

STDROMPICKEXT(gowcaizr, gowcaizr, neogeo);
STD_ROM_FN(gowcaizr);

struct BurnDriver BurnDrvgowcaizr = {
	"gowcaizr", NULL, "neogeo", "1996",
	"Voltage Fighter - Gowcaizer\0Choujin Gakuen Gowcaizer\0", NULL, "Technos", "Neo Geo",
	L"Voltage Fighter - Gowcaizer\0\u8D85\u4EBA\u5B66\u5712\u30B4\u30A6\u30AB\u30A4\u30B6\u30FC\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, gowcaizrRomInfo, gowcaizrRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Real Bout Fatal Fury

static struct BurnRomInfo rbff1RomDesc[] = {
	{ "095-p1.bin",   0x100000, 0x63B4D8AE, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "095-p2.bin",   0x200000, 0xCC15826E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "095-s1.bin",   0x020000, 0xB6BF5E08, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "069-c1.bin",   0x400000, 0xE302F93C, 3 | BRF_GRA },		 //  3 Sprite data
	{ "069-c2.bin",   0x400000, 0x1053A455, 3 | BRF_GRA },		 //  4
	{ "069-c3.bin",   0x400000, 0x1C0FDE2F, 3 | BRF_GRA },		 //  5
	{ "069-c4.bin",   0x400000, 0xA25FC3D0, 3 | BRF_GRA },		 //  6
	{ "095-c5.bin",   0x400000, 0x8B9B65DF, 3 | BRF_GRA },		 //  7
	{ "095-c6.bin",   0x400000, 0x3E164718, 3 | BRF_GRA },		 //  8
	{ "095-c7.bin",   0x200000, 0xCA605E12, 3 | BRF_GRA },		 //  9
	{ "095-c8.bin",   0x200000, 0x4E6BEB6C, 3 | BRF_GRA },		 // 10

	{ "095-m1.bin",   0x020000, 0x653492A7, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "069-v1.bin",   0x400000, 0x2BDBD4DB, 5 | BRF_SND },		 // 10	Sound data
	{ "069-v2.bin",   0x400000, 0xA698A487, 5 | BRF_SND },		 // 11
	{ "095-v3.bin",   0x400000, 0x189D1C6C, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(rbff1, rbff1, neogeo);
STD_ROM_FN(rbff1);

struct BurnDriver BurnDrvrbff1 = {
	"rbff1", "fatfury3", "neogeo", "1995",
	"Real Bout Fatal Fury\0Real Bout Garou Densetsu\0", NULL, "SNK", "Neo Geo",
	L"Real Bout Fatal Fury\0Real Bout \u9913\u72FC\u4F1D\u8AAC\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, rbff1RomInfo, rbff1RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Art of Fighting 3 - the path of the warrior

static struct BurnRomInfo aof3RomDesc[] = {
	{ "096-p1.bin",   0x100000, 0x9edb420d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "096-p2.bin",   0x200000, 0x4d5a2602, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "096-s1.bin",   0x020000, 0xcc7fd344, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "096-c1.bin",   0x400000, 0xf17b8d89, 3 | BRF_GRA },		 //  3 Sprite data
	{ "096-c2.bin",   0x400000, 0x3840c508, 3 | BRF_GRA },		 //  4
	{ "096-c3.bin",   0x400000, 0x55f9ee1e, 3 | BRF_GRA },		 //  5
	{ "096-c4.bin",   0x400000, 0x585b7e47, 3 | BRF_GRA },		 //  6
	{ "096-c5.bin",   0x400000, 0xc75a753c, 3 | BRF_GRA },		 //  7
	{ "096-c6.bin",   0x400000, 0x9a9d2f7a, 3 | BRF_GRA },		 //  8
	{ "096-c7.bin",   0x200000, 0x51bd8ab2, 3 | BRF_GRA },		 //  9
	{ "096-c8.bin",   0x200000, 0x9a34f99c, 3 | BRF_GRA },		 // 10

	{ "096-m1.bin",   0x020000, 0xcb07b659, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "096-v1.bin",   0x200000, 0xe2c32074, 5 | BRF_SND },		 // 12 Sound data
	{ "096-v2.bin",   0x200000, 0xa290eee7, 5 | BRF_SND },		 // 13
	{ "096-v3.bin",   0x200000, 0x199d12ea, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(aof3, aof3, neogeo);
STD_ROM_FN(aof3);

struct BurnDriver BurnDrvAof3 = {
	"aof3", NULL, "neogeo", "1996",
	"Art of Fighting 3 - the path of the warrior\0Art of Fighting - ryuuko no ken gaiden\0", NULL, "SNK", "Neo Geo",
	L"Art of Fighting 3 - the path of the warrior\0Art of Fighting - \u9F8D\u864E\u306E\u62F3\u5916\u4F1D\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, aof3RomInfo, aof3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// Art of Fighting 3 - the path of the warrior (Korean)

static struct BurnRomInfo aof3kRomDesc[] = {
	{ "096-p1k.bin",  0x100000, 0xA0780789, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "096-p2.bin",   0x200000, 0x4d5a2602, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "096-s1.bin",   0x020000, 0xcc7fd344, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "096-c1.bin",   0x400000, 0xf17b8d89, 3 | BRF_GRA },		 //  3 Sprite data
	{ "096-c2.bin",   0x400000, 0x3840c508, 3 | BRF_GRA },		 //  4
	{ "096-c3.bin",   0x400000, 0x55f9ee1e, 3 | BRF_GRA },		 //  5
	{ "096-c4.bin",   0x400000, 0x585b7e47, 3 | BRF_GRA },		 //  6
	{ "096-c5.bin",   0x400000, 0xc75a753c, 3 | BRF_GRA },		 //  7
	{ "096-c6.bin",   0x400000, 0x9a9d2f7a, 3 | BRF_GRA },		 //  8
	{ "096-c7.bin",   0x200000, 0x51bd8ab2, 3 | BRF_GRA },		 //  9
	{ "096-c8.bin",   0x200000, 0x9a34f99c, 3 | BRF_GRA },		 // 10

	{ "096-m1.bin",   0x020000, 0xcb07b659, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "096-v1.bin",   0x200000, 0xe2c32074, 5 | BRF_SND },		 // 12 Sound data
	{ "096-v2.bin",   0x200000, 0xa290eee7, 5 | BRF_SND },		 // 13
	{ "096-v3.bin",   0x200000, 0x199d12ea, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(aof3k, aof3k, neogeo);
STD_ROM_FN(aof3k);

struct BurnDriver BurnDrvaof3k = {
	"aof3k", "aof3", "neogeo", "1996",
	"Art of Fighting 3 - the path of the warrior (Korean)\0", "Korean version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, aof3kRomInfo, aof3kRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sonic Wings 3

static struct BurnRomInfo sonicwi3RomDesc[] = {
	{ "097-p1.bin",   0x200000, 0x0547121d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "097-s1.bin",   0x020000, 0x8dd66743, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "097-c1.bin",   0x400000, 0x33d0d589, 3 | BRF_GRA },		 //  2 Sprite data
	{ "097-c2.bin",   0x400000, 0x186f8b43, 3 | BRF_GRA },		 //  3
	{ "097-c3.bin",   0x200000, 0xc339fff5, 3 | BRF_GRA },		 //  4
	{ "097-c4.bin",   0x200000, 0x84a40c6e, 3 | BRF_GRA },		 //  5

	{ "097-m1.bin",   0x020000, 0xb20e4291, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "097-v1.bin",   0x400000, 0x6f885152, 5 | BRF_SND },		 //  7 Sound data
	{ "097-v2.bin",   0x100000, 0x32187ccd, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(sonicwi3, sonicwi3, neogeo);
STD_ROM_FN(sonicwi3);

struct BurnDriver BurnDrvSonicwi3 = {
	"sonicwi3", NULL, "neogeo", "1995",
	"Aero Fighters 3\0Sonic Wings 3\0", NULL, "Video System Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, sonicwi3RomInfo, sonicwi3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0098 Idol Mahjong - final romance 2 (CD only? not confirmed, MVS might exist)
// 0099 Neo Pool Masters */


// Neo Turf Masters

static struct BurnRomInfo turfmastRomDesc[] = {
	{ "200-p1.bin",   0x200000, 0x28C83048, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "200-s1.bin",   0x020000, 0x9A5402B2, 2 | BRF_GRA },		 //  3 Text layer tiles

	{ "200-c1.bin",   0x400000, 0x8E7BF41A, 3 | BRF_GRA },		 //  4 Sprite data
	{ "200-c2.bin",   0x400000, 0x5A65A8CE, 3 | BRF_GRA },		 //  5

	{ "200-m1.bin",   0x020000, 0x9994AC00, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "200-v1.bin",   0x200000, 0x00FD48D2, 5 | BRF_SND },		 // 11	Sound data
	{ "200-v2.bin",   0x200000, 0x082ACB31, 5 | BRF_SND },		 // 12
	{ "200-v3.bin",   0x200000, 0x7ABCA053, 5 | BRF_SND },		 // 13
	{ "200-v4.bin",   0x200000, 0x6C7B4902, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(turfmast, turfmast, neogeo);
STD_ROM_FN(turfmast);

struct BurnDriver BurnDrvTurfmast = {
	"turfmast", NULL, "neogeo", "1996",
	"Neo Turf Masters\0Big Tournament Golf\0", NULL, "Nazca", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, turfmastRomInfo, turfmastRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug - Super Vehicle-001

static struct BurnRomInfo mslugRomDesc[] = {
	{ "201-p1.bin",   0x200000, 0x08D8DAA5, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "201-s1.bin",   0x020000, 0x2F55958D, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "201-c1.bin",   0x400000, 0x72813676, 3 | BRF_GRA },		 //  2 Sprite data
	{ "201-c2.bin",   0x400000, 0x96F62574, 3 | BRF_GRA },		 //  3
	{ "201-c3.bin",   0x400000, 0x5121456A, 3 | BRF_GRA },		 //  4
	{ "201-c4.bin",   0x400000, 0xF4AD59A3, 3 | BRF_GRA },		 //  5

	{ "201-m1.bin",   0x020000, 0xC28B3253, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "201-v1.bin",   0x400000, 0x23D22ED1, 5 | BRF_SND },		 //  7 Sound data
	{ "201-v2.bin",   0x400000, 0x472CF9DB, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(mslug, mslug, neogeo);
STD_ROM_FN(mslug);

struct BurnDriver BurnDrvMSlug = {
	"mslug", NULL, "neogeo", "1996",
	"Metal Slug - super vehicle-001\0", NULL, "Nazca", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, mslugRomInfo, mslugRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzle De Pon

static struct BurnRomInfo puzzledpRomDesc[] = {
	{ "202-p1.bin",   0x080000, 0x2b61415b, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "202-s1.bin",   0x010000, 0x4a421612, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "202-c1.bin",   0x100000, 0xcc0095ef, 3 | BRF_GRA },		 //  2 Sprite data
	{ "202-c2.bin",   0x100000, 0x42371307, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(puzzledp, puzzledp, neogeo);
STD_ROM_FN(puzzledp);

struct BurnDriver BurnDrvPuzzledp = {
	"puzzledp", NULL, "neogeo", "1995",
	"Puzzle De Pon\0", NULL, "Taito (Visco license)", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, puzzledpRomInfo, puzzledpRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Syougi No Tatsujin - master of syougi

static struct BurnRomInfo mosyougiRomDesc[] = {
	{ "203-p1.bin",   0x100000, 0x7BA70E2D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "203-s1.bin",   0x020000, 0x4E132FAC, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "203-c1.bin",   0x200000, 0xBBA9E8C0, 3 | BRF_GRA },		 //  2 Sprite data
	{ "203-c2.bin",   0x200000, 0x2574BE03, 3 | BRF_GRA },		 //  3

	{ "203-m1.bin",   0x020000, 0xA602C2C2, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "203-v1.bin",   0x200000, 0xBAA2B9A5, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(mosyougi, mosyougi, neogeo);
STD_ROM_FN(mosyougi);

struct BurnDriver BurnDrvMOSyougi = {
	"mosyougi", NULL, "neogeo", "1990",
	"Syougi No Tatsujin - master of syougi\0", NULL, "ADK / SNK", "Neo Geo",
	L"\u5C06\u68CB\u306E\u9054\u4EBA\0Master of Syougi\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, mosyougiRomInfo, mosyougiRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0204 QP (prototype)
// 0205 Neo-Geo CD Special (CD only)


// Chibi Marukochan Deluxe Quiz

static struct BurnRomInfo marukodqRomDesc[] = {
	{ "206-p1.bin",   0x100000, 0xc33ed21e, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "206-s1.bin",   0x008000, 0x3b52a219, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "206-c1.bin",   0x400000, 0x4bd5e70f, 3 | BRF_GRA },		 //  2 Sprite data
	{ "206-c2.bin",   0x400000, 0x67dbe24d, 3 | BRF_GRA },		 //  3
	{ "206-c3.bin",   0x100000, 0x79aa2b48, 3 | BRF_GRA },		 //  4
	{ "206-c4.bin",   0x100000, 0x55e1314d, 3 | BRF_GRA },		 //  5

	{ "206-m1.bin",   0x020000, 0x0e22902e, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "206-v1.bin",   0x200000, 0x5385eca8, 5 | BRF_SND },		 //  7 Sound data
	{ "206-v2.bin",   0x200000, 0xf8c55404, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(marukodq, marukodq, neogeo);
STD_ROM_FN(marukodq);

struct BurnDriver BurnDrvMarukodq = {
	"marukodq", NULL, "neogeo", "1995",
	"Chibi Marukochan Deluxe Quiz\0", NULL, "Takara", "Neo Geo",
	L"\u3061\u3073\u307E\u308B\u5B50\u3061\u3083\u3093 \u307E\u308B\u5B50\u30C7\u30E9\u30C3\u30AF\u30B9\u30AF\u30A4\u30BA\0Chibi Marukochan Deluxe Quiz\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, marukodqRomInfo, marukodqRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo Mr. Do!

static struct BurnRomInfo neomrdoRomDesc[] = {
	{ "207-p1.bin",   0x080000, 0x39efdb82, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "207-s1.bin",   0x010000, 0x6c4b09c4, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "207-c1.bin",   0x200000, 0xc7541b9d, 3 | BRF_GRA },		 //  2 Sprite data
	{ "207-c2.bin",   0x200000, 0xf57166d2, 3 | BRF_GRA },		 //  3

	{ "207-m1.bin",   0x020000, 0x81eade02, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "207-v1.bin",   0x200000, 0x4143c052, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neomrdo, neomrdo, neogeo);
STD_ROM_FN(neomrdo);

struct BurnDriver BurnDrvNeomrdo = {
	"neomrdo", NULL, "neogeo", "1996",
	"Neo Mr. Do!\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neomrdoRomInfo, neomrdoRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Super Dodge Ball

static struct BurnRomInfo sdodgebRomDesc[] = {
	{ "208-p1.bin",   0x200000, 0x127f3d32, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "208-s1.bin",   0x020000, 0x64abd6b3, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "208-c1.bin",   0x400000, 0x93d8619b, 3 | BRF_GRA },		 //  2 Sprite data
	{ "208-c2.bin",   0x400000, 0x1c737bb6, 3 | BRF_GRA },		 //  3
	{ "208-c3.bin",   0x200000, 0x14cb1703, 3 | BRF_GRA },		 //  4
	{ "208-c4.bin",   0x200000, 0xc7165f19, 3 | BRF_GRA },		 //  5

	{ "208-m1.bin",   0x020000, 0x0a5f3325, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "208-v1.bin",   0x200000, 0x8b53e945, 5 | BRF_SND },		 //  7 Sound data
	{ "208-v2.bin",   0x200000, 0xaf37ebf8, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(sdodgeb, sdodgeb, neogeo);
STD_ROM_FN(sdodgeb);

struct BurnDriver BurnDrvSdodgeb = {
	"sdodgeb", NULL, "neogeo", "1996",
	"Super Dodge Ball\0Kunio no Nekketsu Toukyuu Densetsu\0", NULL, "Technos", "Neo Geo",
	L"Super Dodge Ball\0\u304F\u306B\u304A\u306E\u71B1\u8840\u95D8\u7403\u4F1D\u8AAC\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, sdodgebRomInfo, sdodgebRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Goal! Goal! Goal!

static struct BurnRomInfo goalx3RomDesc[] = {
	{ "209-p1.bin",   0x200000, 0x2a019a79, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "209-s1.bin",   0x020000, 0xc0eaad86, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "209-c1.bin",   0x400000, 0xb49d980e, 3 | BRF_GRA },		 //  2 Sprite data
	{ "209-c2.bin",   0x400000, 0x5649b015, 3 | BRF_GRA },		 //  3
	{ "209-c3.bin",   0x100000, 0x5f91bace, 3 | BRF_GRA },		 //  4
	{ "209-c4.bin",   0x100000, 0x1e9f76f2, 3 | BRF_GRA },		 //  5

	{ "209-m1.bin",   0x010000, 0xdd945773, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "209-v1.bin",   0x200000, 0xef214212, 5 | BRF_SND },		 //  7	Sound data
};

STDROMPICKEXT(goalx3, goalx3, neogeo);
STD_ROM_FN(goalx3);

struct BurnDriver BurnDrvGoalx3 = {
	"goalx3", NULL, "neogeo", "1995",
	"Goal! Goal! Goal!\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, goalx3RomInfo, goalx3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0210 Karate Ninja Sho (prototype) 1995 Yumekobo
// 0211 Oshidashi Zintrick (CD only? not confirmed, MVS might exist) 1996 SNK/ADK


// OverTop

static struct BurnRomInfo overtopRomDesc[] = {
	{ "212-p1.bin",   0x200000, 0x16c063a9, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "212-s1.bin",   0x020000, 0x481d3ddc, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "212-c1.bin",   0x400000, 0x50f43087, 3 | BRF_GRA },		 //  2 Sprite data
	{ "212-c2.bin",   0x400000, 0xa5b39807, 3 | BRF_GRA },		 //  3
	{ "212-c3.bin",   0x400000, 0x9252ea02, 3 | BRF_GRA },		 //  4
	{ "212-c4.bin",   0x400000, 0x5f41a699, 3 | BRF_GRA },		 //  5
	{ "212-c5.bin",   0x200000, 0xfc858bef, 3 | BRF_GRA },		 //  6
	{ "212-c6.bin",   0x200000, 0x0589c15e, 3 | BRF_GRA },		 //  7

	{ "212-m1.bin",   0x020000, 0xfcab6191, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "212-v1.bin",   0x400000, 0x013d4ef9, 5 | BRF_SND },		 //  9 Sound data
};

STDROMPICKEXT(overtop, overtop, neogeo);
STD_ROM_FN(overtop);

struct BurnDriver BurnDrvOvertop = {
	"overtop", NULL, "neogeo", "1996",
	"OverTop\0", NULL, "ADK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, overtopRomInfo, overtopRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo Drift Out

static struct BurnRomInfo neodriftRomDesc[] = {
	{ "213-p1.bin",   0x200000, 0xe397d798, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "213-s1.bin",   0x020000, 0xb76b61bc, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "213-c1.bin",   0x400000, 0x3edc8bd3, 3 | BRF_GRA },		 //  2 Sprite data
	{ "213-c2.bin",   0x400000, 0x46ae5f16, 3 | BRF_GRA },		 //  3

	{ "213-m1.bin",   0x020000, 0x200045f1, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "213-v1.bin",   0x200000, 0xa421c076, 5 | BRF_SND },		 //  5	Sound data
	{ "213-v2.bin",   0x200000, 0x233c7dd9, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(neodrift, neodrift, neogeo);
STD_ROM_FN(neodrift);

struct BurnDriver BurnDrvNeodrift = {
	"neodrift", NULL, "neogeo", "1996",
	"Neo Drift Out - new technology\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, neodriftRomInfo, neodriftRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '96

static struct BurnRomInfo kof96RomDesc[] = {
	{ "214-p1.bin",   0x100000, 0x52755d74, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "214-p2.bin",   0x200000, 0x002ccb73, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "214-s1.bin",   0x020000, 0x1254cbdb, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "214-c1.bin",   0x400000, 0x7ecf4aa2, 3 | BRF_GRA },		 //  3 Sprite data
	{ "214-c2.bin",   0x400000, 0x05b54f37, 3 | BRF_GRA },		 //  4
	{ "214-c3.bin",   0x400000, 0x64989a65, 3 | BRF_GRA },		 //  5
	{ "214-c4.bin",   0x400000, 0xafbea515, 3 | BRF_GRA },		 //  6
	{ "214-c5.bin",   0x400000, 0x2a3bbd26, 3 | BRF_GRA },		 //  7
	{ "214-c6.bin",   0x400000, 0x44d30dc7, 3 | BRF_GRA },		 //  8
	{ "214-c7.bin",   0x400000, 0x3687331b, 3 | BRF_GRA },		 //  9
	{ "214-c8.bin",   0x400000, 0xfa1461ad, 3 | BRF_GRA },		 // 10

	{ "214-m1.bin",   0x020000, 0xdabc427c, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "214-v1.bin",   0x400000, 0x63f7b045, 5 | BRF_SND },		 // 12 Sound data
	{ "214-v2.bin",   0x400000, 0x25929059, 5 | BRF_SND },		 // 13
	{ "214-v3.bin",   0x200000, 0x92a2257d, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof96, kof96, neogeo);
STD_ROM_FN(kof96);

struct BurnDriver BurnDrvKof96 = {
	"kof96", NULL, "neogeo", "1996",
	"The King of Fighters '96 (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof96RomInfo, kof96RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '96 (aes version)

static struct BurnRomInfo kof96hRomDesc[] = {
	{ "214-pg1.bin",  0x100000, 0xbd3757c9, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "214-p2.bin",   0x200000, 0x002ccb73, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "214-s1.bin",   0x020000, 0x1254cbdb, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "214-c1.bin",   0x400000, 0x7ecf4aa2, 3 | BRF_GRA },		 //  3 Sprite data
	{ "214-c2.bin",   0x400000, 0x05b54f37, 3 | BRF_GRA },		 //  4
	{ "214-c3.bin",   0x400000, 0x64989a65, 3 | BRF_GRA },		 //  5
	{ "214-c4.bin",   0x400000, 0xafbea515, 3 | BRF_GRA },		 //  6
	{ "214-c5.bin",   0x400000, 0x2a3bbd26, 3 | BRF_GRA },		 //  7
	{ "214-c6.bin",   0x400000, 0x44d30dc7, 3 | BRF_GRA },		 //  8
	{ "214-c7.bin",   0x400000, 0x3687331b, 3 | BRF_GRA },		 //  9
	{ "214-c8.bin",   0x400000, 0xfa1461ad, 3 | BRF_GRA },		 // 10

	{ "214-m1.bin",   0x020000, 0xdabc427c, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "214-v1.bin",   0x400000, 0x63f7b045, 5 | BRF_SND },		 // 12 Sound data
	{ "214-v2.bin",   0x400000, 0x25929059, 5 | BRF_SND },		 // 13
	{ "214-v3.bin",   0x200000, 0x92a2257d, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof96h, kof96h, neogeo);
STD_ROM_FN(kof96h);

struct BurnDriver BurnDrvKof96h = {
	"kof96h", "kof96", "neogeo", "1996",
	"The King of Fighters '96 (set 2)\0", "AES version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof96hRomInfo, kof96hRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Super Sidekicks 4

static struct BurnRomInfo ssideki4RomDesc[] = {
	{ "215-p1.bin",   0x200000, 0x519b4ba3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "215-s1.bin",   0x020000, 0xf0fe5c36, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "215-c1.bin",   0x400000, 0x8ff444f5, 3 | BRF_GRA },		 //  2 Sprite data
	{ "215-c2.bin",   0x400000, 0x5b155037, 3 | BRF_GRA },		 //  3
	{ "215-c3.bin",   0x400000, 0x456a073a, 3 | BRF_GRA },		 //  4
	{ "215-c4.bin",   0x400000, 0x43c182e1, 3 | BRF_GRA },		 //  5
	{ "215-c5.bin",   0x200000, 0x0c6f97ec, 3 | BRF_GRA },		 //  6
	{ "215-c6.bin",   0x200000, 0x329c5e1b, 3 | BRF_GRA },		 //  7

	{ "215-m1.bin",   0x020000, 0xa932081d, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "215-v1.bin",   0x400000, 0x877d1409, 5 | BRF_SND },		 //  9 Sound data
	{ "215-v2.bin",   0x200000, 0x1bfa218b, 5 | BRF_SND },		 //  10
};

STDROMPICKEXT(ssideki4, ssideki4, neogeo);
STD_ROM_FN(ssideki4);

struct BurnDriver BurnDrvSsideki4 = {
	"ssideki4", NULL, "neogeo", "1996",
	"The Ultimate 11 - SNK football championship\0Tokuten Ou - honoo no libero\0", NULL, "SNK", "Neo Geo",
	L"The Ultimate 11 - SNK football championship\0\u5F97\u70B9\u738B - \u708E\u306E\u30EA\u30D9\u30ED\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ssideki4RomInfo, ssideki4RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*-------------------------------------------------------------------------------------

   Kizuna Encounter was suppose to be a true tag battle.  There was an
   adapter board that would make the game into a four player game.  Apparently
   using the debug bios can unlock the four-player game mode, but I'm not sure
   how to do this.  The board is labeled "NEO-FTC1B MAIN BOARD" (© SNK 1996) 
   and has a plug with four blue wires leading into the cart (I think).

-------------------------------------------------------------------------------------*/

// Kizuna Encounter

static struct BurnRomInfo kizunaRomDesc[] = {
	{ "216-p1.bin",   0x200000, 0x75d2b3de, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "216-s1.bin",   0x020000, 0xefdc72d7, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "059-c1.bin",   0x200000, 0x763ba611, 3 | BRF_GRA },		 //  2 Sprite data
	{ "059-c2.bin",   0x200000, 0xe05e8ca6, 3 | BRF_GRA },		 //  3
	{ "216-c3.bin",   0x400000, 0x665c9f16, 3 | BRF_GRA },		 //  4
	{ "216-c4.bin",   0x400000, 0x7f5d03db, 3 | BRF_GRA },		 //  5
	{ "059-c5.bin",   0x200000, 0x59013f9e, 3 | BRF_GRA },		 //  6
	{ "059-c6.bin",   0x200000, 0x1c8d5def, 3 | BRF_GRA },		 //  7
	{ "059-c7.bin",   0x200000, 0xc88f7035, 3 | BRF_GRA },		 //  8
	{ "059-c8.bin",   0x200000, 0x484ce3ba, 3 | BRF_GRA },		 //  9

	{ "216-m1.bin",   0x020000, 0x1b096820, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "216-v1.bin",   0x200000, 0x530c50fd, 5 | BRF_SND },		 // 11 Sound data
	{ "216-v2.bin",   0x200000, 0x03667a8d, 5 | BRF_SND },		 // 12
	{ "216-v3.bin",   0x200000, 0x7038c2f9, 5 | BRF_SND },		 // 13
	{ "216-v4.bin",   0x200000, 0x31b99bd6, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kizuna, kizuna, neogeo);
STD_ROM_FN(kizuna);

struct BurnDriver BurnDrvKizuna = {
	"kizuna", "savagere", "neogeo", "1996",
	"Kizuna Encounter - super tag battle\0Fu'un Super Tag Battle\0", NULL, "SNK", "Neo Geo",
	L"Kizuna Encounter - super tag battle\0\u98A8\u96F2 Super Tag Battle\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, kizunaRomInfo, kizunaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ninja Master's

static struct BurnRomInfo ninjamasRomDesc[] = {
	{ "217-p1.bin",   0x100000, 0x3E97ED69, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "217-p2.bin",   0x200000, 0x191FCA88, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "217-s1.bin",   0x020000, 0x8FF782F0, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "217-c1.bin",   0x400000, 0x5FE97BC4, 3 | BRF_GRA },		 //  3 Sprite data
	{ "217-c2.bin",   0x400000, 0x886E0d66, 3 | BRF_GRA },		 //  4
	{ "217-c3.bin",   0x400000, 0x59E8525F, 3 | BRF_GRA },		 //  5
	{ "217-c4.bin",   0x400000, 0x8521ADD2, 3 | BRF_GRA },		 //  6
	{ "217-c5.bin",   0x400000, 0xFB1896E5, 3 | BRF_GRA },		 //  7
	{ "217-c6.bin",   0x400000, 0x1C98C54B, 3 | BRF_GRA },		 //  8
	{ "217-c7.bin",   0x400000, 0x8B0EDE2E, 3 | BRF_GRA },		 //  9
	{ "217-c8.bin",   0x400000, 0xA085BB61, 3 | BRF_GRA },		 // 10

	{ "217-m1.bin",   0x020000, 0xD00FB2AF, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "217-v1.bin",   0x400000, 0x1C34E013, 5 | BRF_SND },		 // 12 Sound data
	{ "217-v2.bin",   0x200000, 0x22F1C681, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(ninjamas, ninjamas, neogeo);
STD_ROM_FN(ninjamas);

struct BurnDriver BurnDrvNinjaMas = {
	"ninjamas", NULL, "neogeo", "1996",
	"Ninja Master's haoh ninpo cho\0", NULL, "ADK / SNK", "Neo Geo",
	L"Ninja master's \u8987\u738B\u5FCD\u6CD5\u5E16\0Ninja Master's haoh ninpo cho\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, ninjamasRomInfo, ninjamasRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Operation Ragnagard

static struct BurnRomInfo ragnagrdRomDesc[] = {
	{ "218-p1.bin",   0x200000, 0xCA372303, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "218-s1.bin",   0x020000, 0x7D402F9A, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "218-c1.bin",   0x400000, 0xC31500A4, 3 | BRF_GRA },		 //  2 Sprite data
	{ "218-c2.bin",   0x400000, 0x98ABA1F9, 3 | BRF_GRA },		 //  3
	{ "218-c3.bin",   0x400000, 0x833C163A, 3 | BRF_GRA },		 //  4
	{ "218-c4.bin",   0x400000, 0xC1A30f69, 3 | BRF_GRA },		 //  5
	{ "218-c5.bin",   0x400000, 0x6B6DE0FF, 3 | BRF_GRA },		 //  6
	{ "218-c6.bin",   0x400000, 0x94BEEFCF, 3 | BRF_GRA },		 //  7
	{ "218-c7.bin",   0x400000, 0xDE6f9B28, 3 | BRF_GRA },		 //  8
	{ "218-c8.bin",   0x400000, 0xD9B311F6, 3 | BRF_GRA },		 //  9

	{ "218-m1.bin",   0x020000, 0x17028BCF, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "218-v1.bin",   0x400000, 0x61EEE7F4, 5 | BRF_SND },		 // 11 Sound data
	{ "218-v2.bin",   0x400000, 0x6104E20B, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(ragnagrd, ragnagrd, neogeo);
STD_ROM_FN(ragnagrd);

struct BurnDriver BurnDrvragnagrd = {
	"ragnagrd", NULL, "neogeo", "1996",
	"Operation Ragnagard\0Shin-Oh-Ken\0", NULL, "Saurus", "Neo Geo",
	L"Operation Ragnagard\0\u795E\u51F0\u62F3\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ragnagrdRomInfo, ragnagrdRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Pleasure Goal

static struct BurnRomInfo pgoalRomDesc[] = {
	{ "219-p1.bin",   0x200000, 0x6af0e574, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "219-s1.bin",   0x020000, 0x002f3c88, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "219-c1.bin",   0x200000, 0x2dc69faf, 3 | BRF_GRA },		 //  2 Sprite data
	{ "219-c2.bin",   0x200000, 0x5db81811, 3 | BRF_GRA },		 //  3
	{ "219-c3.bin",   0x200000, 0x9dbfece5, 3 | BRF_GRA },		 //  4
	{ "219-c4.bin",   0x200000, 0xc9f4324c, 3 | BRF_GRA },		 //  5
	{ "219-c5.bin",   0x200000, 0x5fdad0a5, 3 | BRF_GRA },		 //  6
	{ "219-c6.bin",   0x200000, 0xf57b4a1c, 3 | BRF_GRA },		 //  7

	{ "219-m1.bin",   0x020000, 0x958efdc8, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "219-v1.bin",   0x200000, 0x2cc1bd05, 5 | BRF_SND },		 //  9 Sound data
	{ "219-v2.bin",   0x200000, 0x06ac1d3f, 5 | BRF_SND },		 //  10
};

STDROMPICKEXT(pgoal, pgoal, neogeo);
STD_ROM_FN(pgoal);

struct BurnDriver BurnDrvPgoal = {
	"pgoal", NULL, "neogeo", "1996",
	"Pleasure Goal - 5 on 5 mini soccer\0Futsal\0", NULL, "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, pgoalRomInfo, pgoalRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0220 Choutetsu Brikin'ger - iron clad (MVS existance seems to have been confirmed)


// Magical Drop II

static struct BurnRomInfo magdrop2RomDesc[] = {
	{ "221-p1.bin",   0x080000, 0x7BE82353, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "221-s1.bin",   0x020000, 0x2A4063A3, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "221-c1.bin",   0x400000, 0x1F862A14, 3 | BRF_GRA },		 //  2 Sprite data
	{ "221-c2.bin",   0x400000, 0x14B90536, 3 | BRF_GRA },		 //  3

	{ "221-m1.bin",   0x020000, 0xBDDAE628, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "221-v1.bin",   0x200000, 0x7E5E53E4, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(magdrop2, magdrop2, neogeo);
STD_ROM_FN(magdrop2);

struct BurnDriver BurnDrvMagDrop2 = {
	"magdrop2", NULL, "neogeo", "1996",
	"Magical Drop II\0", NULL, "Data East Corporation", "Neo Geo",
	L"Magical Drop II\0\u30DE\u30B8\u30AB\u30EB\u30C9\u30ED\u30C3\u30D7\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, magdrop2RomInfo, magdrop2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// Samurai Shodown 4

static struct BurnRomInfo samsho4RomDesc[] = {
	{ "222-p1.bin",   0x100000, 0x1A5CB56D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "222-p2.bin",   0x400000, 0xB023CD8B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "222-s1.bin",   0x020000, 0x8D3D3BF9, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "222-c1.bin",   0x400000, 0x68F2ED95, 3 | BRF_GRA },		 //  3 Sprite data
	{ "222-c2.bin",   0x400000, 0xA6E9AFF0, 3 | BRF_GRA },		 //  4
	{ "222-c3.bin",   0x400000, 0xC91B40F4, 3 | BRF_GRA },		 //  5
	{ "222-c4.bin",   0x400000, 0x359510A4, 3 | BRF_GRA },		 //  6
	{ "222-c5.bin",   0x400000, 0x9cFBB22D, 3 | BRF_GRA },		 //  7
	{ "222-c6.bin",   0x400000, 0x685EFC32, 3 | BRF_GRA },		 //  8
	{ "222-c7.bin",   0x400000, 0xD0F86F0D, 3 | BRF_GRA },		 //  9
	{ "222-c8.bin",   0x400000, 0xADFC50E3, 3 | BRF_GRA },		 // 10

	{ "222-m1.bin",   0x020000, 0x7615BC1B, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "222-v1.bin",   0x400000, 0x7D6bA95F, 5 | BRF_SND },		 // 12	Sound data
	{ "222-v2.bin",   0x400000, 0x6C33BB5D, 5 | BRF_SND },		 // 13
	{ "222-v3.bin",   0x200000, 0x831EA8C0, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(samsho4, samsho4, neogeo);
STD_ROM_FN(samsho4);

struct BurnDriver BurnDrvSamSho4 = {
	"samsho4", NULL, "neogeo", "1996",
	"Samurai Shodown IV - Amakusa's revenge\0Samurai Spirits - Amakusa kourin\0", NULL, "SNK", "Neo Geo",
	L"Samurai Shodown IV - Amakusa's revenge\0\u30B5\u30E0\u30E9\u30A4\u30B9\u30D4\u30EA\u30C3\u30C4 - \u5929\u8349\u964D\u81E8\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, samsho4RomInfo, samsho4RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Real Bout Fatal Fury Special

static struct BurnRomInfo rbffspecRomDesc[] = {
	{ "223-p1.bin",   0x100000, 0xF84A2D1D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "223-p2.bin",   0x400000, 0xADDD8F08, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "223-s1.bin",   0x020000, 0x7ECD6E8C, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "223-c1.bin",   0x400000, 0xEBAB05E2, 3 | BRF_GRA },		 //  3 Sprite data
	{ "223-c2.bin",   0x400000, 0x641868C3, 3 | BRF_GRA },		 //  4
	{ "223-c3.bin",   0x400000, 0xCA00191F, 3 | BRF_GRA },		 //  5
	{ "223-c4.bin",   0x400000, 0x1F23d860, 3 | BRF_GRA },		 //  6
	{ "223-c5.bin",   0x400000, 0x321E362C, 3 | BRF_GRA },		 //  7
	{ "223-c6.bin",   0x400000, 0xd8FCEF90, 3 | BRF_GRA },		 //  8
	{ "223-c7.bin",   0x400000, 0xBC80DD2D, 3 | BRF_GRA },		 //  9
	{ "223-c8.bin",   0x400000, 0x5AD62102, 3 | BRF_GRA },		 // 10

	{ "223-m1.bin",   0x020000, 0x3FEE46BF, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "223-v1.bin",   0x400000, 0x76673869, 5 | BRF_SND },		 // 10	Sound data
	{ "223-v2.bin",   0x400000, 0x7A275ACD, 5 | BRF_SND },		 // 11
	{ "223-v3.bin",   0x400000, 0x5A797FD2, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(rbffspec, rbffspec, neogeo);
STD_ROM_FN(rbffspec);

struct BurnDriver BurnDrvrbffspec = {
	"rbffspec", NULL, "neogeo", "1996",
	"Real Bout Fatal Fury Special\0Real Bout Special\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, rbffspecRomInfo, rbffspecRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Twinklestar Sprites

static struct BurnRomInfo twinspriRomDesc[] = {
	{ "224-p1.bin",   0x200000, 0x7697E445, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "224-s1.bin",   0x020000, 0xEEED5758, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "224-c1.bin",   0x400000, 0xf7DA64AB, 3 | BRF_GRA },		 //  2 Sprite data
	{ "224-c2.bin",   0x400000, 0x4C09BBFB, 3 | BRF_GRA },		 //  3
	{ "224-c3.bin",   0x100000, 0xC59E4129, 3 | BRF_GRA },		 //  4
	{ "224-c4.bin",   0x100000, 0xB5532E53, 3 | BRF_GRA },		 //  5

	{ "224-m1.bin",   0x020000, 0x364D6F96, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "224-v1.bin",   0x400000, 0xFF57F088, 5 | BRF_SND },		 //  7 Sound data
	{ "224-v2.bin",   0x200000, 0x7AD26599, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(twinspri, twinspri, neogeo);
STD_ROM_FN(twinspri);

struct BurnDriver BurnDrvTwinSpri = {
	"twinspri", NULL, "neogeo", "1996",
	"Twinklestar Sprites\0", NULL, "ADK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, twinspriRomInfo, twinspriRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Waku Waku 7

static struct BurnRomInfo wakuwak7RomDesc[] = {
	{ "225-p1.bin",   0x100000, 0xb14da766, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "225-p2.bin",   0x200000, 0xfe190665, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "225-s1.bin",   0x020000, 0x71c4b4b5, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "225-c1.bin",   0x400000, 0xee4fea54, 3 | BRF_GRA },		 //  3 Sprite data
	{ "225-c2.bin",   0x400000, 0x0c549e2d, 3 | BRF_GRA },		 //  4
	{ "225-c3.bin",   0x400000, 0xaf0897c0, 3 | BRF_GRA },		 //  5
	{ "225-c4.bin",   0x400000, 0x4c66527a, 3 | BRF_GRA },		 //  6
	{ "225-c5.bin",   0x400000, 0x8ecea2b5, 3 | BRF_GRA },		 //  7
	{ "225-c6.bin",   0x400000, 0x0eb11a6d, 3 | BRF_GRA },		 //  8

	{ "225-m1.bin",   0x020000, 0x0634bba6, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "225-v1.bin",   0x400000, 0x6195c6b4, 5 | BRF_SND },		 // 10	Sound data
	{ "225-v2.bin",   0x400000, 0x6159c5fe, 5 | BRF_SND },		 // 11
};

STDROMPICKEXT(wakuwak7, wakuwak7, neogeo);
STD_ROM_FN(wakuwak7);

struct BurnDriver BurnDrvWakuwak7 = {
	"wakuwak7", NULL, "neogeo", "1996",
	"Waku Waku 7\0", NULL, "Sunsoft", "Neo Geo",
	L"Waku Waku 7\0\u308F\u304F\u308F\u304F\uFF17\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, wakuwak7RomInfo, wakuwak7RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0226 Pair Pair Wars (prototype) 1996 Sunsoft?


// Stakes Winner 2

static struct BurnRomInfo stakwin2RomDesc[] = {
	{ "227-p1.bin",   0x200000, 0xdaf101d2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "227-s1.bin",   0x020000, 0x2a8c4462, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "227-c1.bin",   0x400000, 0x7d6c2af4, 3 | BRF_GRA },		 //  2 Sprite data
	{ "227-c2.bin",   0x400000, 0x7e402d39, 3 | BRF_GRA },		 //  3
	{ "227-c3.bin",   0x200000, 0x93dfd660, 3 | BRF_GRA },		 //  4
	{ "227-c4.bin",   0x200000, 0x7efea43a, 3 | BRF_GRA },		 //  5

	{ "227-m1.bin",   0x020000, 0xc8e5e0f9, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "227-v1.bin",   0x400000, 0xb8f24181, 5 | BRF_SND },		 //  7 Sound data
	{ "227-v2.bin",   0x400000, 0xee39e260, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(stakwin2, stakwin2, neogeo);
STD_ROM_FN(stakwin2);

struct BurnDriver BurnDrvStakwin2 = {
	"stakwin2", NULL, "neogeo", "1996",
	"Stakes Winner 2\0", NULL, "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, stakwin2RomInfo, stakwin2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* -----------------------------------------------------------------------------

	Info from Billy Pitt's Neo-Geo proto page:
		  http://www.neobitz.com/protos/games/ghostlop.htm

		An excellent Ghostbusters themed puzzle game by Data East 
	from 1996. It combines the fast action of an Arkanoid style game, 
	with the quick thinking of a Bust-A-Move type game. The game was 
	re-considered for release in 2001, but SNK's untimely demise later 
	that same year may have ended that possibility. A personal email 
	from Data East of Japan states that the game is officially no 
	longer going to be released: "...We regret to tell you the plan 
	to publish Ghostlop on NEO-GEO is now abandoned/cancelled to date, 
	so we do not have any idea when the game is released." This is a 
	shame because it really is a great game...and believe me...I know...
	because I own the proto! :) 

------------------------------------------------------------------------------ */

// Ghostlop (prototype)

static struct BurnRomInfo ghostlopRomDesc[] = {
	{ "gl-p1.rom",    0x100000, 0x6033172E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "gl-s1.rom",    0x020000, 0x83C24E81, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "gl-c1.rom",    0x400000, 0xBFC99EFE, 3 | BRF_GRA },		 //  2 Sprite data
	{ "gl-c2.rom",    0x400000, 0x69788082, 3 | BRF_GRA },		 //  3

	{ "gl-m1.rom",    0x020000, 0xFD833B33, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "gl-v1.rom",    0x200000, 0xC603FCE6, 5 | BRF_SND },		 //  9 Sound data
};

STDROMPICKEXT(ghostlop, ghostlop, neogeo);
STD_ROM_FN(ghostlop);

struct BurnDriver BurnDrvghostlop = {
	"ghostlop", NULL, "neogeo", "1994",
	"Ghostlop (prototype)\0", NULL, "Data East Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_PROTOTYPE, 2, HARDWARE_SNK_NEOGEO,
	NULL, ghostlopRomInfo, ghostlopRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0229 King of Fighters '96 CD Collection (CD only)


// Breakers

static struct BurnRomInfo breakersRomDesc[] = {
	{ "230-p1.bin",   0x200000, 0xED24A6E6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "230-s1.bin",   0x020000, 0x076FB64C, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "230-c1.bin",   0x400000, 0x68D4AE76, 3 | BRF_GRA },		 //  2 Sprite data
	{ "230-c2.bin",   0x400000, 0xFDEE05CD, 3 | BRF_GRA },		 //  3
	{ "230-c3.bin",   0x400000, 0x645077F3, 3 | BRF_GRA },		 //  4
	{ "230-c4.bin",   0x400000, 0x63AEB74C, 3 | BRF_GRA },		 //  5

	{ "230-m1.bin",   0x020000, 0x3951A1C1, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "230-v1.bin",   0x400000, 0x7F9ED279, 5 | BRF_SND },		 //  7 Sound data
	{ "230-v2.bin",   0x400000, 0x1D43E420, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(breakers, breakers, neogeo);
STD_ROM_FN(breakers);

struct BurnDriver BurnDrvBreakers = {
	"breakers", NULL, "neogeo", "1996",
	"Breakers\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, breakersRomInfo, breakersRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Money Puzzle Exchanger

static struct BurnRomInfo miexchngRomDesc[] = {
	{ "231-p1.bin",   0x080000, 0x61be1810, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "231-s1.bin",   0x020000, 0xfe0c0c53, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "231-c1.bin",   0x200000, 0x6c403ba3, 3 | BRF_GRA },		 //  2 Sprite data
	{ "231-c2.bin",   0x200000, 0x554bcd9b, 3 | BRF_GRA },		 //  3
	{ "231-c3.bin",   0x080000, 0x14524eb5, 3 | BRF_GRA },		 //  4
	{ "231-c4.bin",   0x080000, 0x1694f171, 3 | BRF_GRA },		 //  5

	{ "231-m1.bin",   0x020000, 0xde41301b, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "231-v1.bin",   0x400000, 0x113fb898, 5 | BRF_SND },		 //  7 Sound data
};

STDROMPICKEXT(miexchng, miexchng, neogeo);
STD_ROM_FN(miexchng);

struct BurnDriver BurnDrvMiexchng = {
	"miexchng", NULL, "neogeo", "1997",
	"Money Puzzle Exchanger\0Money Idol Exchanger\0", NULL, "Face", "Neo Geo",
	L"Money Puzzle Exchanger\0\u30DE\u30CD\u30FC\u30A2\u30A4\u30C9\u30EB\u30A8\u30AF\u30B9\u30C1\u30A7\u30F3\u30B8\u30E3\u30FC\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, miexchngRomInfo, miexchngRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '97

static struct BurnRomInfo kof97RomDesc[] = {
	{ "232-p1.bin",   0x100000, 0x7DB81AD9, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "232-p2.bin",   0x400000, 0x158B23F6, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "232-s1.bin",   0x020000, 0x8514ECF5, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "232-c1.bin",   0x800000, 0x5F8BF0A1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "232-c2.bin",   0x800000, 0xE4D45C81, 3 | BRF_GRA },		 //  4
	{ "232-c3.bin",   0x800000, 0x581D6618, 3 | BRF_GRA },		 //  5
	{ "232-c4.bin",   0x800000, 0x49BB1E68, 3 | BRF_GRA },		 //  6
	{ "232-c5.bin",   0x400000, 0x34fC4E51, 3 | BRF_GRA },		 //  7
	{ "232-c6.bin",   0x400000, 0x4FF4D47B, 3 | BRF_GRA },		 //  8

	{ "232-m1.bin",   0x020000, 0x45348747, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "232-v1.bin",   0x400000, 0x22A2B5B5, 5 | BRF_SND },		 // 10 Sound data
	{ "232-v2.bin",   0x400000, 0x2304E744, 5 | BRF_SND },		 // 11
	{ "232-v3.bin",   0x400000, 0x759EB954, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(kof97, kof97, neogeo);
STD_ROM_FN(kof97);

struct BurnDriver BurnDrvKof97 = {
	"kof97", NULL, "neogeo", "1997",
	"The King of Fighters '97 (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof97RomInfo, kof97RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '97 (alternate version)

static struct BurnRomInfo kof97aRomDesc[] = {
	{ "232-pg1.bin",  0x100000, 0x5C2400B7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "232-p2.bin",   0x400000, 0x158B23F6, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "232-s1.bin",   0x020000, 0x8514ECF5, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "232-c1.bin",   0x800000, 0x5F8BF0A1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "232-c2.bin",   0x800000, 0xE4D45C81, 3 | BRF_GRA },		 //  4
	{ "232-c3.bin",   0x800000, 0x581D6618, 3 | BRF_GRA },		 //  5
	{ "232-c4.bin",   0x800000, 0x49BB1E68, 3 | BRF_GRA },		 //  6
	{ "232-c5.bin",   0x400000, 0x34fC4E51, 3 | BRF_GRA },		 //  7
	{ "232-c6.bin",   0x400000, 0x4FF4D47B, 3 | BRF_GRA },		 //  8

	{ "232-m1.bin",   0x020000, 0x45348747, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "232-v1.bin",   0x400000, 0x22A2B5B5, 5 | BRF_SND },		 // 10 Sound data
	{ "232-v2.bin",   0x400000, 0x2304E744, 5 | BRF_SND },		 // 11
	{ "232-v3.bin",   0x400000, 0x759EB954, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(kof97a, kof97a, neogeo);
STD_ROM_FN(kof97a);

struct BurnDriver BurnDrvKof97a = {
	"kof97a", "kof97", "neogeo", "1997",
	"The King of Fighters '97 (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof97aRomInfo, kof97aRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Magical Drop III

static struct BurnRomInfo magdrop3RomDesc[] = {
	{ "233-p1.bin",   0x100000, 0x931E17FA, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "233-s1.bin",   0x020000, 0x7399E68A, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "233-c1.bin",   0x400000, 0x65e3f4c4, 3 | BRF_GRA },		 //  2 Sprite data
	{ "233-c2.bin",   0x400000, 0x35dea6c9, 3 | BRF_GRA },		 //  3
	{ "233-c3.bin",   0x400000, 0x0ba2c502, 3 | BRF_GRA },		 //  4
	{ "233-c4.bin",   0x400000, 0x70dbbd6d, 3 | BRF_GRA },		 //  5

	{ "233-m1.bin",   0x020000, 0x5BEAF34E, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "233-v1.bin",   0x400000, 0x58839298, 5 | BRF_SND },		 //  7 Sound data
	{ "233-v2.bin",   0x080000, 0xD5E30DF4, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(magdrop3, magdrop3, neogeo);
STD_ROM_FN(magdrop3);

struct BurnDriver BurnDrvMagDrop3 = {
	"magdrop3", NULL, "neogeo", "1997",
	"Magical Drop III\0", NULL, "Data East Corporation", "Neo Geo",
	L"Magical Drop III\0\u30DE\u30B8\u30AB\u30EB\u30C9\u30ED\u30C3\u30D7III\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, magdrop3RomInfo, magdrop3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The Last Blade

static struct BurnRomInfo lastbladRomDesc[] = {
	{ "234-p1.bin",   0x100000, 0xCD01C06D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "234-p2.bin",   0x400000, 0x0FDC289E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "234-s1.bin",   0x020000, 0x95561412, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "234-c1.bin",   0x800000, 0x9F7E2BD3, 3 | BRF_GRA },		 //  3 Sprite data
	{ "234-c2.bin",   0x800000, 0x80623D3C, 3 | BRF_GRA },		 //  4
	{ "234-c3.bin",   0x800000, 0x91AB1A30, 3 | BRF_GRA },		 //  5
	{ "234-c4.bin",   0x800000, 0x3D60b037, 3 | BRF_GRA },		 //  6
	{ "234-c5.bin",   0x400000, 0x1BA80CEE, 3 | BRF_GRA },		 //  7
	{ "234-c6.bin",   0x400000, 0xBEAFD091, 3 | BRF_GRA },		 //  8

	{ "234-m1.bin",   0x020000, 0x087628EA, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "234-v1.bin",   0x400000, 0xED66B76F, 5 | BRF_SND },		 // 10 Sound data
	{ "234-v2.bin",   0x400000, 0xA0e7F6E2, 5 | BRF_SND },		 // 11
	{ "234-v3.bin",   0x400000, 0xA506E1E2, 5 | BRF_SND },		 // 12
	{ "234-v4.bin",   0x200000, 0x13583C4B, 5 | BRF_SND },		 // 13
	// V4 is 32Mbits, needs redump
};

STDROMPICKEXT(lastblad, lastblad, neogeo);
STD_ROM_FN(lastblad);

struct BurnDriver BurnDrvlastblad = {
	"lastblad", NULL, "neogeo", "1997",
	"The Last Blade\0Bakumatsu Roman Gekka No Kenshi (set 1)\0", NULL, "SNK", "Neo Geo",
	L"The Last Blade\0\u5E55\u672B\u6D6A\u6F2B \u6708\u83EF\u306E\u5263\u58EB\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, lastbladRomInfo, lastbladRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The Last Blade (alternate version)

static struct BurnRomInfo lastbldaRomDesc[] = {
	{ "234-p1.rom",            0x100000, 0xE123A5A3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "234-p2.bin",            0x400000, 0x0FDC289E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "234-s1.bin",            0x020000, 0x95561412, 2 | BRF_GRA },		  //  2 Text layer tiles

	{ "234-c1.bin",            0x800000, 0x9F7E2BD3, 3 | BRF_GRA },		  //  3 Sprite data
	{ "234-c2.bin",            0x800000, 0x80623D3C, 3 | BRF_GRA },		  //  4
	{ "234-c3.bin",            0x800000, 0x91AB1A30, 3 | BRF_GRA },		  //  5
	{ "234-c4.bin",            0x800000, 0x3D60b037, 3 | BRF_GRA },		  //  6
	{ "234-c5.bin",            0x400000, 0x1BA80CEE, 3 | BRF_GRA },		  //  7
	{ "234-c6.bin",            0x400000, 0xBEAFD091, 3 | BRF_GRA },		  //  8

	{ "234-m1.bin",            0x020000, 0x087628EA, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "234-v1.bin",            0x400000, 0xED66B76F, 5 | BRF_SND },		  // 10 Sound data
	{ "234-v2.bin",            0x400000, 0xA0e7F6E2, 5 | BRF_SND },		  // 11
	{ "234-v3.bin",            0x400000, 0xA506E1E2, 5 | BRF_SND },		  // 12
	{ "lastblda_234-v4.bin",   0x400000, 0x0E34157F, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(lastblda, lastblda, neogeo);
STD_ROM_FN(lastblda);

struct BurnDriver BurnDrvlastblda = {
	"lastblda", "lastblad", "neogeo", "1997",
	"The Last Blade\0Bakumatsu Roman Gekka No Kenshi (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"The Last Blade\0\u5E55\u672B\u6D6A\u6F2B \u6708\u83EF\u306E\u5263\u58EB\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, lastbldaRomInfo, lastbldaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The Last Soldier (Korean)

static struct BurnRomInfo lastsoldRomDesc[] = {
	{ "234-p1k.bin",  0x100000, 0x906F3065, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "234-p2.bin",   0x400000, 0x0FDC289E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "234-s1.bin",   0x020000, 0x95561412, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "234-c1.bin",   0x800000, 0x9F7E2BD3, 3 | BRF_GRA },		 //  3 Sprite data
	{ "234-c2.bin",   0x800000, 0x80623D3C, 3 | BRF_GRA },		 //  4
	{ "234-c3.bin",   0x800000, 0x91AB1A30, 3 | BRF_GRA },		 //  5
	{ "234-c4.bin",   0x800000, 0x3D60b037, 3 | BRF_GRA },		 //  6
	{ "234-c5.bin",   0x400000, 0x1BA80CEE, 3 | BRF_GRA },		 //  7
	{ "234-c6.bin",   0x400000, 0xBEAFD091, 3 | BRF_GRA },		 //  8

	{ "234-m1.bin",   0x020000, 0x087628EA, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "234-v1.bin",   0x400000, 0xED66B76F, 5 | BRF_SND },		 // 10 Sound data
	{ "234-v2.bin",   0x400000, 0xA0e7F6E2, 5 | BRF_SND },		 // 11
	{ "234-v3.bin",   0x400000, 0xA506E1E2, 5 | BRF_SND },		 // 12
	{ "234-v4.bin",   0x200000, 0x13583C4B, 5 | BRF_SND },		 // 13
	// V4 is 32Mbits, needs redump
};

STDROMPICKEXT(lastsold, lastsold, neogeo);
STD_ROM_FN(lastsold);

struct BurnDriver BurnDrvlastsold = {
	"lastsold", "lastblad", "neogeo", "1997",
	"The Last Soldier\0", "Korean Version of \"The Last Blade\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, lastsoldRomInfo, lastsoldRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzle De Pon R

static struct BurnRomInfo puzzldprRomDesc[] = {
	{ "235-p1.bin",   0x080000, 0xafed5de2, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "235-s1.bin",   0x010000, 0x5a68d91e, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "202-c1.bin",   0x100000, 0xcc0095ef, 3 | BRF_GRA },		 //  2 Sprite data
	{ "202-c2.bin",   0x100000, 0x42371307, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(puzzldpr, puzzldpr, neogeo);
STD_ROM_FN(puzzldpr);

struct BurnDriver BurnDrvPuzzldpr = {
	"puzzldpr", "puzzledp", "neogeo", "1997",
	"Puzzle De Pon R\0", NULL, "Taito (Visco license)", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, puzzldprRomInfo, puzzldprRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* ------------------------------------------------------------------------------------------

	Irritating Maze is the most unusual game on the Neo-Geo hardware.  It only came
	as a stand-alone pcb + cab, used a trackball to move around the maze (which 
	required a special bios), and had a fan that shot air on you >> Irritating.

------------------------------------------------------------------------------------------- */

// The Irritating Maze

static struct BurnRomInfo irrmazeRomDesc[] = {
	{ "236-p1.bin",   0x200000, 0x6d536c6e, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "236-s1.bin",   0x020000, 0x5d1ca640, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "236-c1.bin",   0x400000, 0xc1d47902, 3 | BRF_GRA },		 //  2 Sprite data
	{ "236-c2.bin",   0x400000, 0xe15f972e, 3 | BRF_GRA },		 //  3

	{ "236-m1.bin",   0x020000, 0x880a1abd, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "236-v1.bin",   0x200000, 0x5f89c3b4, 5 | BRF_SND },		 //  5 Sound data
	{ "236-v2.bin",   0x100000, 0x1e843567, 6 | BRF_SND },		 //  6
};

STDROMPICKEXT(irrmaze, irrmaze, neotrackball)
STD_ROM_FN(irrmaze);

struct BurnDriver BurnDrvIrrmaze = {
	"irrmaze", NULL, "neogeo", "1997",
	"The Irritating Maze\0Ultra Denryu Iraira Bou\0", NULL, "SNK / Saurus", "Neo Geo",
	L"The Irritating Maze\0\u30A6\u30EB\u30C8\u30E9\u96FB\u6D41\u30A4\u30E9\u30A4\u30E9\u68D2\0", NULL, NULL, NULL,
	1, 1, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_TRACKBALL,
	NULL, irrmazeRomInfo, irrmazeRomName, neotrackballInputInfo, neotrackballDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Pop 'n Bounce

static struct BurnRomInfo popbouncRomDesc[] = {
	{ "237-p1.bin",   0x100000, 0xbe96e44f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "237-s1.bin",   0x020000, 0xb61cf595, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "237-c1.bin",   0x200000, 0xeda42d66, 3 | BRF_GRA },		 //  2 Sprite data
	{ "237-c2.bin",   0x200000, 0x5e633c65, 3 | BRF_GRA },		 //  3

	{ "237-m1.bin",   0x020000, 0xd4c946dd, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "237-v1.bin",   0x200000, 0xedcb1beb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(popbounc, popbounc, neogeo);
STD_ROM_FN(popbounc);

struct BurnDriver BurnDrvPopbounc = {
	"popbounc", NULL, "neogeo", "1997",
	"Pop 'n Bounce\0Gapporin\0", NULL, "Video System Co.", "Neo Geo",
	L"Pop 'n Bounce\0\u30AC\u30C3\u30DD\u30EA\u30F3\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_PADDLE,
	NULL, popbouncRomInfo, popbouncRomName, neopaddleInputInfo, neopaddleDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Shock Troopers

static struct BurnRomInfo shocktroRomDesc[] = {
	{ "238-p1.bin",   0x100000, 0x5677456F, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "238-p2.bin",   0x400000, 0x5b4A09C5, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "238-s1.bin",   0x020000, 0x1F95CEDB, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "238-c1.bin",   0x400000, 0x90C6A181, 3 | BRF_GRA },		 //  3 Sprite data
	{ "238-c2.bin",   0x400000, 0x888720F0, 3 | BRF_GRA },		 //  4
	{ "238-c3.bin",   0x400000, 0x2C393AA3, 3 | BRF_GRA },		 //  5
	{ "238-c4.bin",   0x400000, 0xB9E909EB, 3 | BRF_GRA },		 //  6
	{ "238-c5.bin",   0x400000, 0xC22C68EB, 3 | BRF_GRA },		 //  7
	{ "238-c6.bin",   0x400000, 0x119323CD, 3 | BRF_GRA },		 //  8
	{ "238-c7.bin",   0x400000, 0xA72CE7ED, 3 | BRF_GRA },		 //  9
	{ "238-c8.bin",   0x400000, 0x1C7C2EFB, 3 | BRF_GRA },		 // 10

	{ "238-m1.bin",   0x020000, 0x075B9518, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "238-v1.bin",   0x400000, 0x260C0BEF, 5 | BRF_SND },		 // 12 Sound data
	{ "238-v2.bin",   0x200000, 0x4AD7D59E, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(shocktro, shocktro, neogeo);
STD_ROM_FN(shocktro);

struct BurnDriver BurnDrvshocktro = {
	"shocktro", NULL, "neogeo", "1997",
	"Shock Troopers (set 1)\0", NULL, "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, shocktroRomInfo, shocktroRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Shock Troopers (Alternate version)

static struct BurnRomInfo shocktraRomDesc[] = {
	{ "238-pg1.bin",  0x100000, 0xefedf8dc, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "238-p2.bin",   0x400000, 0x5b4A09C5, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "238-s1.bin",   0x020000, 0x1F95CEDB, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "238-c1.bin",   0x400000, 0x90C6A181, 3 | BRF_GRA },		 //  3 Sprite data
	{ "238-c2.bin",   0x400000, 0x888720F0, 3 | BRF_GRA },		 //  4
	{ "238-c3.bin",   0x400000, 0x2C393AA3, 3 | BRF_GRA },		 //  5
	{ "238-c4.bin",   0x400000, 0xB9E909EB, 3 | BRF_GRA },		 //  6
	{ "238-c5.bin",   0x400000, 0xC22C68EB, 3 | BRF_GRA },		 //  7
	{ "238-c6.bin",   0x400000, 0x119323CD, 3 | BRF_GRA },		 //  8
	{ "238-c7.bin",   0x400000, 0xA72CE7ED, 3 | BRF_GRA },		 //  9
	{ "238-c8.bin",   0x400000, 0x1C7C2EFB, 3 | BRF_GRA },		 // 10

	{ "238-m1.bin",   0x020000, 0x075B9518, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "238-v1.bin",   0x400000, 0x260C0BEF, 5 | BRF_SND },		 // 12 Sound data
	{ "238-v2.bin",   0x200000, 0x4AD7D59E, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(shocktra, shocktra, neogeo);
STD_ROM_FN(shocktra);

struct BurnDriver BurnDrvShocktra = {
	"shocktra", "shocktro", "neogeo", "1997",
	"Shock Troopers (set 2)\0", "Alternate version", "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, shocktraRomInfo, shocktraRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Blazing Star

static struct BurnRomInfo blazstarRomDesc[] = {
	{ "239-p1.bin",   0x100000, 0x183682F8, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "239-p2.bin",   0x200000, 0x9A9F4154, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "239-s1.bin",   0x020000, 0xD56CB498, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "239-c1.bin",   0x400000, 0x84F6D584, 3 | BRF_GRA },		 //  3 Sprite data
	{ "239-c2.bin",   0x400000, 0x05A0CB22, 3 | BRF_GRA },		 //  4
	{ "239-c3.bin",   0x400000, 0x5FB69C9E, 3 | BRF_GRA },		 //  5
	{ "239-c4.bin",   0x400000, 0x0BE028C4, 3 | BRF_GRA },		 //  6
	{ "239-c5.bin",   0x400000, 0x74BAE5f8, 3 | BRF_GRA },		 //  7
	{ "239-c6.bin",   0x400000, 0x4E0700d2, 3 | BRF_GRA },		 //  8
	{ "239-c7.bin",   0x400000, 0x010ff4FD, 3 | BRF_GRA },		 //  9
	{ "239-c8.bin",   0x400000, 0xDB60460E, 3 | BRF_GRA },		 // 10

	{ "239-m1.bin",   0x020000, 0xD31A3AEA, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "239-v1.bin",   0x400000, 0x1B8D5BF7, 5 | BRF_SND },		 // 12	Sound data
	{ "239-v2.bin",   0x400000, 0x74CF0A70, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(blazstar, blazstar, neogeo);
STD_ROM_FN(blazstar);

struct BurnDriver BurnDrvBlazStar = {
	"blazstar", NULL, "neogeo", "1998",
	"Blazing Star\0", NULL, "Yumekobo", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, blazstarRomInfo, blazstarRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Real Bout Fatal Fury 2

static struct BurnRomInfo rbff2RomDesc[] = {
	{ "240-p1.bin",   0x100000, 0xB6969780, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "240-p2.bin",   0x400000, 0x960AA88D, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "240-s1.bin",   0x020000, 0xDA3B40DE, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "240-c1.bin",   0x800000, 0xEFFAC504, 3 | BRF_GRA },		 //  3 Sprite data
	{ "240-c2.bin",   0x800000, 0xED182D44, 3 | BRF_GRA },		 //  4
	{ "240-c3.bin",   0x800000, 0x22E0330A, 3 | BRF_GRA },		 //  5
	{ "240-c4.bin",   0x800000, 0xC19A07EB, 3 | BRF_GRA },		 //  6
	{ "240-c5.bin",   0x800000, 0x244DFF5A, 3 | BRF_GRA },		 //  7
	{ "240-c6.bin",   0x800000, 0x4609E507, 3 | BRF_GRA },		 //  8

	{ "240-m1.bin",   0x040000, 0xED482791, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "240-v1.bin",   0x400000, 0xF796265A, 5 | BRF_SND },		 // 10	Sound data
	{ "240-v2.bin",   0x400000, 0x2CB3F3BB, 5 | BRF_SND },		 // 11
	{ "240-v3.bin",   0x400000, 0xDF77B7FA, 5 | BRF_SND },		 // 12
	{ "240-v4.bin",   0x400000, 0x33A356EE, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(rbff2, rbff2, neogeo);
STD_ROM_FN(rbff2);

struct BurnDriver BurnDrvrbff2 = {
	"rbff2", NULL, "neogeo", "1998",
	"Real Bout Fatal Fury 2 - the newcomers\0Real Bout Garou Densetsu - the newcomers (set 1)\0", NULL, "SNK", "Neo Geo",
	L"Real Bout Fatal Fury 2 - the newcomers\0Real Bout \u9913\u72FC\u4F1D\u8AAC\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, rbff2RomInfo, rbff2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Real Bout Fatal Fury 2 (alternate version)

static struct BurnRomInfo rbff2aRomDesc[] = {
	{ "240-p1.rom",   0x100000, 0x80E41205, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "240-p2.bin",   0x400000, 0x960AA88D, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "240-s1.bin",   0x020000, 0xDA3B40DE, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "240-c1.bin",   0x800000, 0xEFFAC504, 3 | BRF_GRA },		 //  3 Sprite data
	{ "240-c2.bin",   0x800000, 0xED182D44, 3 | BRF_GRA },		 //  4
	{ "240-c3.bin",   0x800000, 0x22E0330A, 3 | BRF_GRA },		 //  5
	{ "240-c4.bin",   0x800000, 0xC19A07EB, 3 | BRF_GRA },		 //  6
	{ "240-c5.bin",   0x800000, 0x244DFF5A, 3 | BRF_GRA },		 //  7
	{ "240-c6.bin",   0x800000, 0x4609E507, 3 | BRF_GRA },		 //  8

	{ "240-m1.bin",   0x040000, 0xED482791, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "240-v1.bin",   0x400000, 0xF796265A, 5 | BRF_SND },		 // 10	Sound data
	{ "240-v2.bin",   0x400000, 0x2CB3F3BB, 5 | BRF_SND },		 // 11
	{ "240-v3.bin",   0x400000, 0xDF77B7FA, 5 | BRF_SND },		 // 12
	{ "240-v4.bin",   0x400000, 0x33A356EE, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(rbff2a, rbff2a, neogeo);
STD_ROM_FN(rbff2a);

struct BurnDriver BurnDrvrbff2a = {
	"rbff2a", "rbff2", "neogeo", "1998",
	"Real Bout Fatal Fury 2 - the newcomers\0Real Bout Garou Densetsu - the newcomers (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"Real Bout Fatal Fury 2 - the newcomers\0Real Bout \u9913\u72FC\u4F1D\u8AAC\uFF12\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, rbff2aRomInfo, rbff2aRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Real Bout Fatal Fury 2 (Korean version)

static struct BurnRomInfo rbff2kRomDesc[] = {
	{ "240-p1k.bin",  0x100000, 0x965EDEE1, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "240-p2.bin",   0x400000, 0x960AA88D, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "240-s1.bin",   0x020000, 0xDA3B40DE, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "240-c1.bin",   0x800000, 0xEFFAC504, 3 | BRF_GRA },		 //  3 Sprite data
	{ "240-c2.bin",   0x800000, 0xED182D44, 3 | BRF_GRA },		 //  4
	{ "240-c3.bin",   0x800000, 0x22E0330A, 3 | BRF_GRA },		 //  5
	{ "240-c4.bin",   0x800000, 0xC19A07EB, 3 | BRF_GRA },		 //  6
	{ "240-c5.bin",   0x800000, 0x244DFF5A, 3 | BRF_GRA },		 //  7
	{ "240-c6.bin",   0x800000, 0x4609E507, 3 | BRF_GRA },		 //  8

	{ "240-m1.bin",   0x040000, 0xED482791, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "240-v1.bin",   0x400000, 0xF796265A, 5 | BRF_SND },		 // 10	Sound data
	{ "240-v2.bin",   0x400000, 0x2CB3F3BB, 5 | BRF_SND },		 // 11
	{ "240-v3.bin",   0x400000, 0xDF77B7FA, 5 | BRF_SND },		 // 12
	{ "240-v4.bin",   0x400000, 0x33A356EE, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(rbff2k, rbff2k, neogeo);
STD_ROM_FN(rbff2k);

struct BurnDriver BurnDrvrbff2k = {
	"rbff2k", "rbff2", "neogeo", "1998",
	"Real Bout Fatal Fury 2 - the newcomers (Korean)\0", "Korean version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, rbff2kRomInfo, rbff2kRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 2

static struct BurnRomInfo mslug2RomDesc[] = {
	{ "241-p1.bin",   0x100000, 0x2a53c5da, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "241-p2.bin",   0x200000, 0x38883f44, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "241-s1.bin",   0x020000, 0xf3d32f0f, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "241-c1.bin",   0x800000, 0x394b5e0d, 3 | BRF_GRA },		 //  3 Sprite data
	{ "241-c2.bin",   0x800000, 0xe5806221, 3 | BRF_GRA },		 //  4
	{ "241-c3.bin",   0x800000, 0x9f6bfa6f, 3 | BRF_GRA },		 //  5
	{ "241-c4.bin",   0x800000, 0x7d3e306f, 3 | BRF_GRA },		 //  6

	{ "241-m1.bin",   0x020000, 0x94520ebd, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "241-v1.bin",   0x400000, 0x99ec20e8, 5 | BRF_SND },		 //  8 Sound data
	{ "241-v2.bin",   0x400000, 0xecb16799, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(mslug2, mslug2, neogeo);
STD_ROM_FN(mslug2);

struct BurnDriver BurnDrvMSlug2 = {
	"mslug2", NULL, "neogeo", "1998",
	"Metal Slug 2 - super vehicle-001/II\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, mslug2RomInfo, mslug2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '98 (encrypted)

static struct BurnRomInfo kof98RomDesc[] = {
	{ "yz98-p1.160",  0x200000, 0x8893DF89, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "242-p2.bin",   0x400000, 0x980ABA4C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "242-s1.bin",   0x020000, 0x7F7B4805, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "242-c1.bin",   0x800000, 0xE564ECd6, 3 | BRF_GRA },		 //  3 Sprite data
	{ "242-c2.bin",   0x800000, 0xBD959B60, 3 | BRF_GRA },		 //  4
	{ "242-c3.bin",   0x800000, 0x22127B4F, 3 | BRF_GRA },		 //  5
	{ "242-c4.bin",   0x800000, 0x0B4FA044, 3 | BRF_GRA },		 //  6
	{ "242-c5.bin",   0x800000, 0x9D10bED3, 3 | BRF_GRA },		 //  7
	{ "242-c6.bin",   0x800000, 0xDA07B6A2, 3 | BRF_GRA },		 //  8
	{ "242-c7.bin",   0x800000, 0xF6D7A38A, 3 | BRF_GRA },		 //  9
	{ "242-c8.bin",   0x800000, 0xC823E045, 3 | BRF_GRA },		 // 10

	{ "242-m1a.bin",  0x040000, 0x4EF7016B, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "242-v1.bin",   0x400000, 0xB9EA8051, 5 | BRF_SND },		 // 12 Sound data
	{ "242-v2.bin",   0x400000, 0xCC11106E, 5 | BRF_SND },		 // 13
	{ "242-v3.bin",   0x400000, 0x044EA4E1, 5 | BRF_SND },		 // 13
	{ "242-v4.bin",   0x400000, 0x7985EA30, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof98, kof98, neogeo);
STD_ROM_FN(kof98);

static int kof98Init()
{
	pNeoInitCallback = kof98Decrypt;
	pNeoProtectionCallback = kof98ProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvKof98 = {
	"kof98", NULL, "neogeo", "1998",
	"The King of Fighters '98 - the slugfest\0King of Fighters '98 - dream match never ends\0", "Encrypted", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof98RomInfo, kof98RomName, neogeoInputInfo, neogeoDIPInfo,
	kof98Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '98 (encrypted, Korean version)

static struct BurnRomInfo kof98kRomDesc[] = {
	{ "yz98-p1.160",  0x200000, 0x8893DF89, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "242-p2.bin",   0x400000, 0x980ABA4C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "242-s1.bin",   0x020000, 0x7F7B4805, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "242-c1.bin",   0x800000, 0xE564ECd6, 3 | BRF_GRA },		 //  3 Sprite data
	{ "242-c2.bin",   0x800000, 0xBD959B60, 3 | BRF_GRA },		 //  4
	{ "242-c3.bin",   0x800000, 0x22127B4F, 3 | BRF_GRA },		 //  5
	{ "242-c4.bin",   0x800000, 0x0B4FA044, 3 | BRF_GRA },		 //  6
	{ "242-c5.bin",   0x800000, 0x9D10bED3, 3 | BRF_GRA },		 //  7
	{ "242-c6.bin",   0x800000, 0xDA07B6A2, 3 | BRF_GRA },		 //  8
	{ "242-c7.bin",   0x800000, 0xF6D7A38A, 3 | BRF_GRA },		 //  9
	{ "242-c8.bin",   0x800000, 0xC823E045, 3 | BRF_GRA },		 // 10

	{ "242-m1k.bin",  0x040000, 0xCE12dA0C, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "242-v1.bin",   0x400000, 0xB9EA8051, 5 | BRF_SND },		 // 12 Sound data
	{ "242-v2.bin",   0x400000, 0xCC11106E, 5 | BRF_SND },		 // 13
	{ "242-v3.bin",   0x400000, 0x044EA4E1, 5 | BRF_SND },		 // 13
	{ "242-v4.bin",   0x400000, 0x7985EA30, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof98k, kof98k, neogeo);
STD_ROM_FN(kof98k);

struct BurnDriver BurnDrvKof98k = {
	"kof98k", "kof98", "neogeo", "1998",
	"The King of Fighters '98 - the slugfest\0King of Fighters '98 - dream match never ends (Korean m1)\0", "Encrypted, Korea region", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof98kRomInfo, kof98kRomName, neogeoInputInfo, neogeoDIPInfo,
	kof98Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '98 (non encrypted)

static struct BurnRomInfo kof98nRomDesc[] = {
	{ "242-p1.bin",   0x100000, 0x61AC868A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "242-p2.bin",   0x400000, 0x980ABA4C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "242-s1.bin",   0x020000, 0x7F7B4805, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "242-c1.bin",   0x800000, 0xE564ECd6, 3 | BRF_GRA },		 //  3 Sprite data
	{ "242-c2.bin",   0x800000, 0xBD959B60, 3 | BRF_GRA },		 //  4
	{ "242-c3.bin",   0x800000, 0x22127B4F, 3 | BRF_GRA },		 //  5
	{ "242-c4.bin",   0x800000, 0x0B4FA044, 3 | BRF_GRA },		 //  6
	{ "242-c5.bin",   0x800000, 0x9D10bED3, 3 | BRF_GRA },		 //  7
	{ "242-c6.bin",   0x800000, 0xDA07B6A2, 3 | BRF_GRA },		 //  8
	{ "242-c7.bin",   0x800000, 0xF6D7A38A, 3 | BRF_GRA },		 //  9
	{ "242-c8.bin",   0x800000, 0xC823E045, 3 | BRF_GRA },		 // 10

	{ "242-m1.bin",   0x040000, 0x4E7A6B1B, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "242-v1.bin",   0x400000, 0xB9EA8051, 5 | BRF_SND },		 // 12 Sound data
	{ "242-v2.bin",   0x400000, 0xCC11106E, 5 | BRF_SND },		 // 13
	{ "242-v3.bin",   0x400000, 0x044EA4E1, 5 | BRF_SND },		 // 13
	{ "242-v4.bin",   0x400000, 0x7985EA30, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof98n, kof98n, neogeo);
STD_ROM_FN(kof98n);

struct BurnDriver BurnDrvKof98n = {
	"kof98n", "kof98", "neogeo", "1998",
	"The King of Fighters '98 - the slugfest\0King of Fighters '98 - dream match never ends (non encrypted)\0", "Non encrypted", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof98nRomInfo, kof98nRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '98 (alternate version)

static struct BurnRomInfo kof98aRomDesc[] = {
	{ "242-p1.bin",   0x100000, 0x61AC868A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "242-p2.bin",   0x400000, 0x980ABA4C, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "242-s1.bin",   0x020000, 0x7F7B4805, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "242-c1.bin",   0x800000, 0xE564ECd6, 3 | BRF_GRA },		 //  3 Sprite data
	{ "242-c2.bin",   0x800000, 0xBD959B60, 3 | BRF_GRA },		 //  4
	{ "242-c3.bin",   0x800000, 0x22127B4F, 3 | BRF_GRA },		 //  5
	{ "242-c4.bin",   0x800000, 0x0B4FA044, 3 | BRF_GRA },		 //  6
	{ "242-c5.bin",   0x800000, 0x9D10bED3, 3 | BRF_GRA },		 //  7
	{ "242-c6.bin",   0x800000, 0xDA07B6A2, 3 | BRF_GRA },		 //  8
	{ "242-c7.bin",   0x800000, 0xF6D7A38A, 3 | BRF_GRA },		 //  9
	{ "242-c8.bin",   0x800000, 0xC823E045, 3 | BRF_GRA },		 // 10

	{ "242-m1a.bin",  0x040000, 0x4EF7016B, 1 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "242-v1.bin",   0x400000, 0xB9EA8051, 5 | BRF_SND },		 // 12 Sound data
	{ "242-v2.bin",   0x400000, 0xCC11106E, 5 | BRF_SND },		 // 13
	{ "242-v3.bin",   0x400000, 0x044EA4E1, 5 | BRF_SND },		 // 13
	{ "242-v4.bin",   0x400000, 0x7985EA30, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof98a, kof98a, neogeo);
STD_ROM_FN(kof98a);

struct BurnDriverX BurnDrvKof98a = {
	"kof98a", "kof98", "neogeo", "1998",
	"The King of Fighters '98 - the slugfest\0King of Fighters '98 - dream match never ends (Alternate set)\0", "Alternate version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof98aRomInfo, kof98aRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The Last Blade 2 (Japanesse Version)

static struct BurnRomInfo lastbld2RomDesc[] = {
	{ "243-pg1.bin",  0x100000, 0xAF1E6554, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "243-pg2.bin",  0x400000, 0xADD4A30B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "243-s1.bin",   0x020000, 0xC9CD2298, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "243-c1.bin",   0x800000, 0x5839444D, 3 | BRF_GRA },		 //  3 Sprite data
	{ "243-c2.bin",   0x800000, 0xDD087428, 3 | BRF_GRA },		 //  4
	{ "243-c3.bin",   0x800000, 0x6054CBE0, 3 | BRF_GRA },		 //  5
	{ "243-c4.bin",   0x800000, 0x8BD2A9D2, 3 | BRF_GRA },		 //  6
	{ "243-c5.bin",   0x800000, 0x6A503DCF, 3 | BRF_GRA },		 //  7
	{ "243-c6.bin",   0x800000, 0xEC9C36D0, 3 | BRF_GRA },		 //  8

	{ "243-m1.bin",   0x020000, 0xACF12D10, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "243-v1.bin",   0x400000, 0xF7EE6FBB, 5 | BRF_SND },		 // 10 Sound data
	{ "243-v2.bin",   0x400000, 0xAA9E4DF6, 5 | BRF_SND },		 // 11
	{ "243-v3.bin",   0x400000, 0x4AC750B2, 5 | BRF_SND },		 // 12
	{ "243-v4.bin",   0x400000, 0xF5C64BA6, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(lastbld2, lastbld2, neogeo);
STD_ROM_FN(lastbld2);

struct BurnDriver BurnDrvlastbld2 = {
	"lastbld2", NULL, "neogeo", "1998",
	"The Last Blade 2\0Bakumatsu Roman Dai Ni Maku - Gekka No Kenshi\0", "Japanese MVS version", "SNK", "Neo Geo",
	L"The Last Blade 2\0\u5E55\u672B\u6D6A\u6F2B\u7B2C\u4E8C\u5E55 - \u6708\u83EF\u306E\u5263\u58EB - \u6708\u306B\u54B2\u304F\u83EF\u3001\u6563\u308A\u3086\u304F\u82B1\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, lastbld2RomInfo, lastbld2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo-Geo Cup '98

static struct BurnRomInfo neocup98RomDesc[] = {
	{ "244-p1.bin",   0x200000, 0xf8fdb7a5, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "244-s1.bin",   0x020000, 0x9bddb697, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "244-c1.bin",   0x800000, 0xd2c40ec7, 3 | BRF_GRA },		 //  3 Sprite data
	{ "244-c2.bin",   0x800000, 0x33aa0f35, 3 | BRF_GRA },		 //  4

	{ "244-m1.bin",   0x020000, 0xa701b276, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "244-v1.bin",   0x400000, 0x79def46d, 5 | BRF_SND },		 // 12 Sound data
	{ "244-v2.bin",   0x200000, 0xb231902f, 5 | BRF_SND },		 // 13
};

STDROMPICKEXT(neocup98, neocup98, neogeo);
STD_ROM_FN(neocup98);

struct BurnDriver BurnDrvNeocup98 = {
	"neocup98", NULL, "neogeo", "1998",
	"Neo-Geo Cup '98 - the road to the victory\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, neocup98RomInfo, neocup98RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Breakers Revenge

static struct BurnRomInfo breakrevRomDesc[] = {
	{ "245-p1.bin",   0x200000, 0xC828876D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "245-s1.bin",   0x020000, 0xE7660A5D, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "230-c1.bin",   0x400000, 0x68D4AE76, 3 | BRF_GRA },		 //  2 Sprite data
	{ "230-c2.bin",   0x400000, 0xFDEE05CD, 3 | BRF_GRA },		 //  3
	{ "230-c3.bin",   0x400000, 0x645077F3, 3 | BRF_GRA },		 //  4
	{ "230-c4.bin",   0x400000, 0x63AEB74C, 3 | BRF_GRA },		 //  5
	{ "245-c5.bin",   0x200000, 0x28FF1792, 3 | BRF_GRA },		 //  6
	{ "245-c6.bin",   0x200000, 0x23C65644, 3 | BRF_GRA },		 //  7

	{ "245-m1.bin",   0x020000, 0x00F31C66, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "245-v1.bin",   0x400000, 0xE255446C, 5 | BRF_SND },		 //  9 Sound data
	{ "245-v2.bin",   0x400000, 0x9068198A, 5 | BRF_SND },		 // 10
};

STDROMPICKEXT(breakrev, breakrev, neogeo);
STD_ROM_FN(breakrev);

struct BurnDriver BurnDrvBreakRev = {
	"breakrev", "breakers", "neogeo", "1998",
	"Breakers Revenge\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, breakrevRomInfo, breakrevRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Shock Troopers - 2nd Squad

static struct BurnRomInfo shocktr2RomDesc[] = {
	{ "246-p1.bin",   0x100000, 0x6D4B7781, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "246-p2.bin",   0x400000, 0x72EA04C3, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "246-s1.bin",   0x020000, 0x2A360637, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "246-c1.bin",   0x800000, 0x47AC9EC5, 3 | BRF_GRA },		 //  3 Sprite data
	{ "246-c2.bin",   0x800000, 0x7bCAB64F, 3 | BRF_GRA },		 //  4
	{ "246-c3.bin",   0x800000, 0xDB2F73E8, 3 | BRF_GRA },		 //  5
	{ "246-c4.bin",   0x800000, 0x5503854E, 3 | BRF_GRA },		 //  6
	{ "246-c5.bin",   0x800000, 0x055B3701, 3 | BRF_GRA },		 //  7
	{ "246-c6.bin",   0x800000, 0x7E2CAAE1, 3 | BRF_GRA },		 //  8

	{ "246-m1.bin",   0x020000, 0xD0604AD1, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "246-v1.bin",   0x400000, 0x16986FC6, 5 | BRF_SND },		 // 10 Sound data
	{ "246-v2.bin",   0x400000, 0xADA41E83, 5 | BRF_SND },		 // 11
	{ "246-v3.bin",   0x200000, 0xA05BA5DB, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(shocktr2, shocktr2, neogeo);
STD_ROM_FN(shocktr2);

struct BurnDriver BurnDrvshocktr2 = {
	"shocktr2", NULL, "neogeo", "1998",
	"Shock Troopers - 2nd squad\0", NULL, "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, shocktr2RomInfo, shocktr2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Battle Flip Shot

static struct BurnRomInfo flipshotRomDesc[] = {
	{ "247-p1.bin",   0x080000, 0xd2e7a7e3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "247-s1.bin",   0x020000, 0x6300185c, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "247-c1.bin",   0x200000, 0xc9eedcb2, 3 | BRF_GRA },		 //  2 Sprite data
	{ "247-c2.bin",   0x200000, 0x7d6d6e87, 3 | BRF_GRA },		 //  3

	{ "247-m1.bin",   0x020000, 0xa9fe0144, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "247-v1.bin",   0x200000, 0x42ec743d, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(flipshot, flipshot, neogeo);
STD_ROM_FN(flipshot);

struct BurnDriver BurnDrvFlipshot = {
	"flipshot", NULL, "neogeo", "1998",
	"Battle Flip Shot\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, flipshotRomInfo, flipshotRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Puzzle Bobble 2

static struct BurnRomInfo pbobbl2nRomDesc[] = {
	{ "248-p1.bin",   0x100000, 0x9d6c0754, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "248-s1.bin",   0x020000, 0x0a3fee41, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "248-c1.bin",   0x400000, 0xd9115327, 3 | BRF_GRA },		 //  2 Sprite data
	{ "248-c2.bin",   0x400000, 0x77f9fdac, 3 | BRF_GRA },		 //  3
	{ "248-c3.bin",   0x100000, 0x8890bf7c, 3 | BRF_GRA },		 //  4
	{ "248-c4.bin",   0x100000, 0x8efead3f, 3 | BRF_GRA },		 //  5

	{ "248-m1.bin",   0x020000, 0x883097a9, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "248-v1.bin",   0x400000, 0x57fde1fa, 5 | BRF_SND },		 //  7	Sound data
	{ "248-v2.bin",   0x400000, 0x4b966ef3, 5 | BRF_SND },		 //  8
};

STDROMPICKEXT(pbobbl2n, pbobbl2n, neogeo);
STD_ROM_FN(pbobbl2n);

struct BurnDriver BurnDrvPbobbl2n = {
	"pbobbl2n", NULL, "neogeo", "1999",
	"Puzzle Bobble 2\0Bust-A-Move Again\0", NULL, "Taito", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, pbobbl2nRomInfo, pbobbl2nRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Captain Tomaday

static struct BurnRomInfo ctomadayRomDesc[] = {
	{ "249-p1.bin",   0x200000, 0xC9386118, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "249-s1.bin",   0x020000, 0xDC9EB372, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "249-c1.bin",   0x400000, 0x041FB8EE, 3 | BRF_GRA },		 //  2 Sprite data
	{ "249-c2.bin",   0x400000, 0x74F3CDF4, 3 | BRF_GRA },		 //  3

	{ "249-m1.bin",   0x020000, 0x80328A47, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "249-v1.bin",   0x400000, 0xDE7C8F27, 5 | BRF_SND },		 //  5 Sound data
	{ "249-v2.bin",   0x100000, 0xC8E40119, 5 | BRF_SND },		 //  6
};

STDROMPICKEXT(ctomaday, ctomaday, neogeo);
STD_ROM_FN(ctomaday);

struct BurnDriver BurnDrvCTomaday = {
	"ctomaday", NULL, "neogeo", "1999",
	"Captain Tomaday\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ctomadayRomInfo, ctomadayRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug X

static struct BurnRomInfo mslugxRomDesc[] = {
	{ "250-p1.bin",   0x100000, 0x81f1f60b, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "250-p2.bin",   0x400000, 0x1fda2e12, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "250-s1.bin",   0x020000, 0xfb6f441d, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "250-c1.bin",   0x800000, 0x09a52c6f, 3 | BRF_GRA },		 //  3 Sprite data
	{ "250-c2.bin",   0x800000, 0x31679821, 3 | BRF_GRA },		 //  4
	{ "250-c3.bin",   0x800000, 0xfd602019, 3 | BRF_GRA },		 //  5
	{ "250-c4.bin",   0x800000, 0x31354513, 3 | BRF_GRA },		 //  6
	{ "250-c5.bin",   0x800000, 0xa4b56124, 3 | BRF_GRA },		 //  7
	{ "250-c6.bin",   0x800000, 0x83e3e69d, 3 | BRF_GRA },		 //  8

	{ "250-m1.bin",   0x020000, 0xfd42a842, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "250-v1.bin",   0x400000, 0xc79ede73, 5 | BRF_SND },		 // 10 Sound data
	{ "250-v2.bin",   0x400000, 0xea9aabe1, 5 | BRF_SND },		 // 11
	{ "250-v3.bin",   0x200000, 0x2ca65102, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(mslugx, mslugx, neogeo);
STD_ROM_FN(mslugx);

static int mslugxInit()
{
	pNeoInitCallback = mslugxProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvMSlugX = {
	"mslugx", NULL, "neogeo", "1999",
	"Metal Slug X - super vehicle-001\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, mslugxRomInfo, mslugxRomName, neogeoInputInfo, neogeoDIPInfo,
	mslugxInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '99

static struct BurnRomInfo kof99RomDesc[] = {
	{ "251-sma.kc",   0x040000, 0x6C9D0647, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "251-p1.bin",   0x400000, 0x006e4532, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "251-pg2.bin",  0x400000, 0xD9057F51, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "251-c1.bin",   0x800000, 0x0f9e93fe, 3 | BRF_GRA },		 //  3 Sprite data
	{ "251-c2.bin",   0x800000, 0xe71e2ea3, 3 | BRF_GRA },		 //  4
	{ "251-c3.bin",   0x800000, 0x238755d2, 3 | BRF_GRA },		 //  5
	{ "251-c4.bin",   0x800000, 0x438c8b22, 3 | BRF_GRA },		 //  6
	{ "251-c5.bin",   0x800000, 0x0b0abd0a, 3 | BRF_GRA },		 //  7
	{ "251-c6.bin",   0x800000, 0x65bbf281, 3 | BRF_GRA },		 //  8
	{ "251-c7.bin",   0x800000, 0xff65f62e, 3 | BRF_GRA },		 //  9
	{ "251-c8.bin",   0x800000, 0x8d921c68, 3 | BRF_GRA },		 // 10

	{ "251-m1.bin",   0x020000, 0x5e74539c, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "251-v1.bin",   0x400000, 0xef2eecc8, 5 | BRF_SND },		 // 12 Sound data
	{ "251-v2.bin",   0x400000, 0x73e211ca, 5 | BRF_SND },		 // 13
	{ "251-v3.bin",   0x400000, 0x821901da, 5 | BRF_SND },		 // 14
	{ "251-v4.bin",   0x200000, 0xb49e6178, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(kof99, kof99, neogeo);
STD_ROM_FN(kof99);

static int kof99Init()
{
	nNeoProtectionXor = 0x00;
	return NeoSMAInit(1, kof99WriteWordBankswitch, 0x2FFFF8, 0x2FFFFA);
}

struct BurnDriver BurnDrvkof99 = {
	"kof99", NULL, "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (set 1)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, kof99RomInfo, kof99RomName, neogeoInputInfo, neogeoDIPInfo,
	kof99Init, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '99 (alternate version)

static struct BurnRomInfo kof99aRomDesc[] = {
	{ "251-sma.ka",   0x040000, 0x7766d09e, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "251-p1.bin",   0x400000, 0x006e4532, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "251-p2.bin",   0x400000, 0x90175f15, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "251-c1.bin",   0x800000, 0x0f9e93fe, 3 | BRF_GRA },		 //  3 Sprite data
	{ "251-c2.bin",   0x800000, 0xe71e2ea3, 3 | BRF_GRA },		 //  4
	{ "251-c3.bin",   0x800000, 0x238755d2, 3 | BRF_GRA },		 //  5
	{ "251-c4.bin",   0x800000, 0x438c8b22, 3 | BRF_GRA },		 //  6
	{ "251-c5.bin",   0x800000, 0x0b0abd0a, 3 | BRF_GRA },		 //  7
	{ "251-c6.bin",   0x800000, 0x65bbf281, 3 | BRF_GRA },		 //  8
	{ "251-c7.bin",   0x800000, 0xff65f62e, 3 | BRF_GRA },		 //  9
	{ "251-c8.bin",   0x800000, 0x8d921c68, 3 | BRF_GRA },		 // 10

	{ "251-m1.bin",   0x020000, 0x5e74539c, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "251-v1.bin",   0x400000, 0xef2eecc8, 5 | BRF_SND },		 // 12 Sound data
	{ "251-v2.bin",   0x400000, 0x73e211ca, 5 | BRF_SND },		 // 13
	{ "251-v3.bin",   0x400000, 0x821901da, 5 | BRF_SND },		 // 14
	{ "251-v4.bin",   0x200000, 0xb49e6178, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(kof99a, kof99a, neogeo);
STD_ROM_FN(kof99a);

struct BurnDriver BurnDrvkof99a = {
	"kof99a", "kof99", "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, kof99aRomInfo, kof99aRomName, neogeoInputInfo, neogeoDIPInfo,
	kof99Init, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '99 (earlier version)

static struct BurnRomInfo kof99eRomDesc[] = {
	{ "251-sma.ka",   0x040000, 0x7766d09e, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "251-ep1.p1",   0x200000, 0x1e8d692d, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "251-ep2.p2",   0x200000, 0xd6206e5a, 1 | BRF_ESS | BRF_PRG }, //  2
	{ "251-ep3.p3",   0x200000, 0xd58c3ef8, 1 | BRF_ESS | BRF_PRG }, //  3
	{ "251-ep4.p4",   0x200000, 0x52de02ae, 1 | BRF_ESS | BRF_PRG }, //  4

	{ "251-c1.bin",   0x800000, 0x0f9e93fe, 3 | BRF_GRA },		 //  5 Sprite data
	{ "251-c2.bin",   0x800000, 0xe71e2ea3, 3 | BRF_GRA },		 //  6
	{ "251-c3.bin",   0x800000, 0x238755d2, 3 | BRF_GRA },		 //  7
	{ "251-c4.bin",   0x800000, 0x438c8b22, 3 | BRF_GRA },		 //  8
	{ "251-c5.bin",   0x800000, 0x0b0abd0a, 3 | BRF_GRA },		 //  9
	{ "251-c6.bin",   0x800000, 0x65bbf281, 3 | BRF_GRA },		 // 10
	{ "251-c7.bin",   0x800000, 0xff65f62e, 3 | BRF_GRA },		 // 11
	{ "251-c8.bin",   0x800000, 0x8d921c68, 3 | BRF_GRA },		 // 12

	{ "251-m1.bin",   0x020000, 0x5e74539c, 4 | BRF_ESS | BRF_PRG }, // 13 Z80 code

	{ "251-v1.bin",   0x400000, 0xef2eecc8, 5 | BRF_SND },		 // 14 Sound data
	{ "251-v2.bin",   0x400000, 0x73e211ca, 5 | BRF_SND },		 // 15
	{ "251-v3.bin",   0x400000, 0x821901da, 5 | BRF_SND },		 // 16
	{ "251-v4.bin",   0x200000, 0xb49e6178, 5 | BRF_SND },		 // 17
};

STDROMPICKEXT(kof99e, kof99e, neogeo);
STD_ROM_FN(kof99e);

struct BurnDriver BurnDrvkof99e = {
	"kof99e", "kof99", "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (earlier)\0", "Earlier version", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, kof99eRomInfo, kof99eRomName, neogeoInputInfo, neogeoDIPInfo,
	kof99Init, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*---------------------------------------------------------------------------------------

		Interesting that the Px roms are labeled 152. Not only this, but the
	Neo-Geo id# embedded in the roms is also 152.

---------------------------------------------------------------------------------------*/

// The King of Fighters '99 (not encrypted)

static struct BurnRomInfo kof99nRomDesc[] = {
	{ "152-p1.bin",   0x100000, 0xF2C7DDFA, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "152-p2.bin",   0x400000, 0x274EF47A, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "251-c1.bin",   0x800000, 0x0F9E93FE, 3 | BRF_GRA },		 //  2 Sprite data
	{ "251-c2.bin",   0x800000, 0xE71E2EA3, 3 | BRF_GRA },		 //  3
	{ "251-c3.bin",   0x800000, 0x238755D2, 3 | BRF_GRA },		 //  4
	{ "251-c4.bin",   0x800000, 0x438C8B22, 3 | BRF_GRA },		 //  5
	{ "251-c5.bin",   0x800000, 0x0B0ABD0A, 3 | BRF_GRA },		 //  6
	{ "251-c6.bin",   0x800000, 0x65BBF281, 3 | BRF_GRA },		 //  7
	{ "251-c7.bin",   0x800000, 0xFF65F62E, 3 | BRF_GRA },		 //  8
	{ "251-c8.bin",   0x800000, 0x8D921C68, 3 | BRF_GRA },		 //  9

	{ "251-m1.bin",   0x020000, 0x5E74539C, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "251-v1.bin",   0x400000, 0xEF2EECC8, 5 | BRF_SND },		 // 11 Sound data
	{ "251-v2.bin",   0x400000, 0x73E211CA, 5 | BRF_SND },		 // 12
	{ "251-v3.bin",   0x400000, 0x821901DA, 5 | BRF_SND },		 // 13
	{ "251-v4.bin",   0x200000, 0xB49E6178, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof99n, kof99n, neogeo);
STD_ROM_FN(kof99n);

static int kof99nInit()
{
	nNeoProtectionXor = 0x00;
	return NeoInit();
}

struct BurnDriver BurnDrvkof99n = {
	"kof99n", "kof99", "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (non encrypted P)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, kof99nRomInfo, kof99nRomName, neogeoInputInfo, neogeoDIPInfo,
	kof99nInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '99 - Millennium Battle (prototype)

static struct BurnRomInfo kof99pRomDesc[] = {
	{ "251-p1p.bin",  0x100000, 0xf37929c4, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "251-p2p.bin",  0x400000, 0x739742ad, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "251-s1p.bin",  0x020000, 0xfb1498ed, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "251-c1p.bin",  0x800000, 0xe5d8ffa4, 3 | BRF_GRA },		 //  3 Sprite data
	{ "251-c2p.bin",  0x800000, 0xd822778f, 3 | BRF_GRA },		 //  4
	{ "251-c3p.bin",  0x800000, 0xf20959e8, 3 | BRF_GRA },		 //  5
	{ "251-c4p.bin",  0x800000, 0x54ffbe9f, 3 | BRF_GRA },		 //  6
	{ "251-c5p.bin",  0x800000, 0xd87a3bbc, 3 | BRF_GRA },		 //  7
	{ "251-c6p.bin",  0x800000, 0x4d40a691, 3 | BRF_GRA },		 //  8
	{ "251-c7p.bin",  0x800000, 0xa4479a58, 3 | BRF_GRA },		 //  9
	{ "251-c8p.bin",  0x800000, 0xead513ce, 3 | BRF_GRA },		 // 10

	{ "251-m1.bin",   0x020000, 0x5e74539c, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "251-v1.bin",   0x400000, 0xeF2eecc8, 5 | BRF_SND },		 // 12 Sound data
	{ "251-v2.bin",   0x400000, 0x73e211ca, 5 | BRF_SND },		 // 13
	{ "251-v3.bin",   0x400000, 0x821901da, 5 | BRF_SND },		 // 14
	{ "251-v4.bin",   0x200000, 0xb49e6178, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(kof99p, kof99p, neogeo);
STD_ROM_FN(kof99p);

struct BurnDriver BurnDrvkof99p = {
	"kof99p", "kof99", "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (prototype)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_PROTOTYPE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof99pRomInfo, kof99pRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ganryu

static struct BurnRomInfo ganryuRomDesc[] = {
	{ "252-p1.bin",   0x200000, 0x4B8AC4FB, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "252-c1.bin",   0x800000, 0x50EE7882, 3 | BRF_GRA },		 //  1 Sprite data
	{ "252-c2.bin",   0x800000, 0x62585474, 3 | BRF_GRA },		 //  2

	{ "252-m1.bin",   0x020000, 0x30CC4099, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "252-v1.bin",   0x400000, 0xE5946733, 5 | BRF_SND },		 //  4 Sound data
};

STDROMPICKEXT(ganryu, ganryu, neogeo);
STD_ROM_FN(ganryu);

static int ganryuInit()
{
	nNeoProtectionXor = 0x07;
	return NeoInit();
}

struct BurnDriver BurnDrvGanryu = {
	"ganryu", NULL, "neogeo", "1999",
	"Ganryu\0Musashi Ganryuki\0", NULL, "Visco", "Neo Geo",
	L"Ganryu\0\u6B66\u8535\u5DCC\u6D41\u8A18\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SWAPP,
	NULL, ganryuRomInfo, ganryuRomName, neogeoInputInfo, neogeoDIPInfo,
	ganryuInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Garou

static struct BurnRomInfo garouRomDesc[] = {
	{ "253-sma.bin",  0x040000, 0x98bc93dc, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "253-ep1.p1",   0x200000, 0xea3171a4, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "253-ep2.p2",   0x200000, 0x382f704b, 1 | BRF_ESS | BRF_PRG }, //  2
	{ "253-ep3.p3",   0x200000, 0xe395bfdd, 1 | BRF_ESS | BRF_PRG }, //  3
	{ "253-ep4.p4",   0x200000, 0xda92c08e, 1 | BRF_ESS | BRF_PRG }, //  4

	{ "253-c1.bin",   0x800000, 0x0603e046, 3 | BRF_GRA },		 //  5 Sprite data
	{ "253-c2.bin",   0x800000, 0x0917d2a4, 3 | BRF_GRA },		 //  6
	{ "253-c3.bin",   0x800000, 0x6737c92d, 3 | BRF_GRA },		 //  7
	{ "253-c4.bin",   0x800000, 0x5ba92ec6, 3 | BRF_GRA },		 //  8
	{ "253-c5.bin",   0x800000, 0x3eab5557, 3 | BRF_GRA },		 //  9
	{ "253-c6.bin",   0x800000, 0x308d098b, 3 | BRF_GRA },		 // 10
	{ "253-c7.bin",   0x800000, 0xc0e995ae, 3 | BRF_GRA },		 // 11
	{ "253-c8.bin",   0x800000, 0x21a11303, 3 | BRF_GRA },		 // 12

	{ "253-m1.bin",   0x040000, 0x36a806be, 4 | BRF_ESS | BRF_PRG }, // 13 Z80 code

	{ "253-v1.bin",   0x400000, 0x263e388c, 5 | BRF_SND },		 // 14 Sound data
	{ "253-v2.bin",   0x400000, 0x2c6bc7be, 5 | BRF_SND },		 // 15
	{ "253-v3.bin",   0x400000, 0x0425b27d, 5 | BRF_SND },		 // 16
	{ "253-v4.bin",   0x400000, 0xa54be8a9, 5 | BRF_SND },		 // 17
};

STDROMPICKEXT(garou, garou, neogeo);
STD_ROM_FN(garou);

static int garouInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x06;
	return NeoSMAInit(2, garouWriteWordBankswitch, 0x2FFFCC, 0x2FFFF0);
}

struct BurnDriver BurnDrvGarou = {
	"garou", NULL, "neogeo", "1999",
	"Garou - mark of the wolves (set 1)\0", NULL, "SNK", "Neo Geo",
	L"\u9913\u72FC - mark of the wolves\0Garou\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, garouRomInfo, garouRomName, neogeoInputInfo, neogeoDIPInfo,
	garouInit, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Garou [Set 2]

static struct BurnRomInfo garouoRomDesc[] = {
	{ "253-smao.bin", 0x040000, 0x96c72233, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "253-p1.bin",   0x400000, 0x18ae5d7e, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "253-p2.bin",   0x400000, 0xafffa779, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "253-c1.bin",   0x800000, 0x0603e046, 3 | BRF_GRA },		 //  3 Sprite data
	{ "253-c2.bin",   0x800000, 0x0917d2a4, 3 | BRF_GRA },		 //  4
	{ "253-c3.bin",   0x800000, 0x6737c92d, 3 | BRF_GRA },		 //  5
	{ "253-c4.bin",   0x800000, 0x5ba92ec6, 3 | BRF_GRA },		 //  6
	{ "253-c5.bin",   0x800000, 0x3eab5557, 3 | BRF_GRA },		 //  7
	{ "253-c6.bin",   0x800000, 0x308d098b, 3 | BRF_GRA },		 //  8
	{ "253-c7.bin",   0x800000, 0xc0e995ae, 3 | BRF_GRA },		 //  9
	{ "253-c8.bin",   0x800000, 0x21a11303, 3 | BRF_GRA },		 // 10

	{ "253-m1.bin",   0x040000, 0x36a806be, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "253-v1.bin",   0x400000, 0x263e388c, 5 | BRF_SND },		 // 12 Sound data
	{ "253-v2.bin",   0x400000, 0x2c6bc7be, 5 | BRF_SND },		 // 13
	{ "253-v3.bin",   0x400000, 0x0425b27d, 5 | BRF_SND },		 // 14
	{ "253-v4.bin",   0x400000, 0xa54be8a9, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(garouo, garouo, neogeo);
STD_ROM_FN(garouo);

static int garouoInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x06;
	return NeoSMAInit(3, garouoWriteWordBankswitch, 0x2FFFCC, 0x2FFFF0);
}

struct BurnDriver BurnDrvGarouo = {
	"garouo", "garou", "neogeo", "1999",
	"Garou - mark of the wolves (set 2)\0", "Alternate version", "SNK", "Neo Geo",
	L"\u9913\u72FC - mark of the wolves\0Garou\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, garouoRomInfo, garouoRomName, neogeoInputInfo, neogeoDIPInfo,
	garouoInit, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Garou [Prototype version]

static struct BurnRomInfo garoupRomDesc[] = {
	{ "253-p1p.bin",  0x100000, 0xc72f0c16, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "253-p2p.bin",  0x400000, 0xbf8de565, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "253-s1p.bin",  0x020000, 0x779989de, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "253-c1p.bin",  0x800000, 0x5bb5d137, 3 | BRF_GRA },		 //  3 Sprite data
	{ "253-c2p.bin",  0x800000, 0x5c8d2960, 3 | BRF_GRA },		 //  4
	{ "253-c3p.bin",  0x800000, 0x234d16fc, 3 | BRF_GRA },		 //  5
	{ "253-c4p.bin",  0x800000, 0xb9b5b993, 3 | BRF_GRA },		 //  6
	{ "253-c5p.bin",  0x800000, 0x722615d2, 3 | BRF_GRA },		 //  7
	{ "253-c6p.bin",  0x800000, 0x0a6fab38, 3 | BRF_GRA },		 //  8
	{ "253-c7p.bin",  0x800000, 0xd68e806f, 3 | BRF_GRA },		 //  9
	{ "253-c8p.bin",  0x800000, 0xf778fe99, 3 | BRF_GRA },		 // 10

	{ "253-m1p.bin",  0x040000, 0xbbe464f7, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "253-v1p.bin",  0x400000, 0x274f3923, 5 | BRF_SND },		 // 12	Sound data
	{ "253-v2p.bin",  0x400000, 0x8f86dabe, 5 | BRF_SND },		 // 13
	{ "253-v3p.bin",  0x400000, 0x05fd06cd, 5 | BRF_SND },		 // 14
	{ "253-v4p.bin",  0x400000, 0x14984063, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(garoup, garoup, neogeo);
STD_ROM_FN(garoup);

struct BurnDriver BurnDrvGaroup = {
	"garoup", "garou", "neogeo", "1999",
	"Garou - mark of the wolves (prototype)\0", NULL, "SNK", "Neo Geo",
	L"\u9913\u72FC - mark of the wolves\0Garou\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_PROTOTYPE, 2, HARDWARE_SNK_NEOGEO,
	NULL, garoupRomInfo, garoupRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Strikers 1945 plus

static struct BurnRomInfo s1945pRomDesc[] = {
	{ "254-p1.bin",   0x100000, 0xFF8EFCFF, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "254-p2.bin",   0x400000, 0xEFDFD4DD, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "254-c1.bin",   0x800000, 0xAE6FC8EF, 3 | BRF_GRA },		 //  2 Sprite data
	{ "254-c2.bin",   0x800000, 0x436FA176, 3 | BRF_GRA },		 //  3
	{ "254-c3.bin",   0x800000, 0xE53FF2DC, 3 | BRF_GRA },		 //  4
	{ "254-c4.bin",   0x800000, 0x818672F0, 3 | BRF_GRA },		 //  5
	{ "254-c5.bin",   0x800000, 0x4580EACD, 3 | BRF_GRA },		 //  6
	{ "254-c6.bin",   0x800000, 0xE34970FC, 3 | BRF_GRA },		 //  7
	{ "254-c7.bin",   0x800000, 0xF2323239, 3 | BRF_GRA },		 //  8
	{ "254-c8.bin",   0x800000, 0x66848C7D, 3 | BRF_GRA },		 //  9

	{ "254-m1.bin",   0x020000, 0x994B4487, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "254-v1.bin",   0x400000, 0x844F58FB, 5 | BRF_SND },		 // 11 Sound data
	{ "254-v2.bin",   0x400000, 0xD9A248F0, 5 | BRF_SND },		 // 12
	{ "254-v3.bin",   0x400000, 0x0B0D2D33, 5 | BRF_SND },		 // 13
	{ "254-v4.bin",   0x400000, 0x6D13DC91, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(s1945p, s1945p, neogeo);
STD_ROM_FN(s1945p);

static int s1945pInit()
{
	nNeoProtectionXor = 0x05;
	return NeoInit();
}

struct BurnDriver BurnDrvs1945p = {
	"s1945p", NULL, "neogeo", "1999",
	"Strikers 1945 plus\0", NULL, "Psikyo", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, s1945pRomInfo, s1945pRomName, neogeoInputInfo, neogeoDIPInfo,
	s1945pInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Prehistoric Isle 2 (encrypted graphics)

static struct BurnRomInfo preisle2RomDesc[] = {
	{ "255-p1.bin",   0x100000, 0xDFA3C0F3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "255-p2.bin",   0x400000, 0x42050B80, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "255-c1.bin",   0x800000, 0xEA06000B, 3 | BRF_GRA },		 //  2 Sprite data
	{ "255-c2.bin",   0x800000, 0x04E67D79, 3 | BRF_GRA },		 //  3
	{ "255-c3.bin",   0x800000, 0x60E31E08, 3 | BRF_GRA },		 //  4
	{ "255-c4.bin",   0x800000, 0x40371D69, 3 | BRF_GRA },		 //  5
	{ "255-c5.bin",   0x800000, 0x0B2E6ADF, 3 | BRF_GRA },		 //  6
	{ "255-c6.bin",   0x800000, 0xB001BDD3, 3 | BRF_GRA },		 //  7

	{ "255-m1.bin",   0x020000, 0x8EFD4014, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "255-v1.bin",   0x400000, 0x5A14543D, 5 | BRF_SND },		 // 11 Sound data
	{ "255-v2.bin",   0x200000, 0x6610D91A, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(preisle2, preisle2, neogeo);
STD_ROM_FN(preisle2);

static int preisle2Init()
{
	nNeoProtectionXor = 0x9F;
	return NeoInit();
}

struct BurnDriver BurnDrvpreisle2 = {
	"preisle2", NULL, "neogeo", "1999",
	"Prehistoric Isle 2\0", NULL, "Yumekobo / Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, preisle2RomInfo, preisle2RomName, neogeoInputInfo, neogeoDIPInfo,
	preisle2Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 3 (encrypted code & graphics)

static struct BurnRomInfo mslug3RomDesc[] = {
	{ "256-sma.bin",  0x040000, 0x9CD55736, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "256-p1.bin",   0x400000, 0xB07EDFD5, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "256-p2.bin",   0x400000, 0x6097C26B, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "256-c1.bin",   0x800000, 0x5A79C34E, 3 | BRF_GRA },		 //  3 Sprite data
	{ "256-c2.bin",   0x800000, 0x944C362C, 3 | BRF_GRA },		 //  4
	{ "256-c3.bin",   0x800000, 0x6E69D36F, 3 | BRF_GRA },		 //  5
	{ "256-c4.bin",   0x800000, 0xB755B4EB, 3 | BRF_GRA },		 //  6
	{ "256-c5.bin",   0x800000, 0x7AACAB47, 3 | BRF_GRA },		 //  7
	{ "256-c6.bin",   0x800000, 0xC698FD5D, 3 | BRF_GRA },		 //  8
	{ "256-c7.bin",   0x800000, 0xCFCEDDD2, 3 | BRF_GRA },		 //  9
	{ "256-c8.bin",   0x800000, 0x4D9BE34C, 3 | BRF_GRA },		 // 10

	{ "256-m1.bin",   0x080000, 0xEAEEC116, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "256-v1.bin",   0x400000, 0xF2690241, 5 | BRF_SND },		 // 12 Sound data
	{ "256-v2.bin",   0x400000, 0x7E2A10BD, 5 | BRF_SND },		 // 13
	{ "256-v3.bin",   0x400000, 0x0EAEC17C, 5 | BRF_SND },		 // 14
	{ "256-v4.bin",   0x400000, 0x9B4B22D4, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(mslug3, mslug3, neogeo);
STD_ROM_FN(mslug3);

static int mslug3Init()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0xAD;
	return NeoSMAInit(4, mslug3WriteWordBankswitch, 0, 0);
}

struct BurnDriver BurnDrvmslug3 = {
	"mslug3", NULL, "neogeo", "2000",
	"Metal Slug 3\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SMA_PROTECTION,
	NULL, mslug3RomInfo, mslug3RomName, neogeoInputInfo, neogeoDIPInfo,
	mslug3Init, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 3 (encrypted graphics)

static struct BurnRomInfo mslug3nRomDesc[] = {
	{ "256-ph1.rom",  0x100000, 0x9C42CA85, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "256-ph2.rom",  0x400000, 0x1F3D8CE8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "256-c1.bin",   0x800000, 0x5A79C34E, 3 | BRF_GRA },		 //  2 Sprite data
	{ "256-c2.bin",   0x800000, 0x944C362C, 3 | BRF_GRA },		 //  3
	{ "256-c3.bin",   0x800000, 0x6E69D36F, 3 | BRF_GRA },		 //  4
	{ "256-c4.bin",   0x800000, 0xB755B4EB, 3 | BRF_GRA },		 //  5
	{ "256-c5.bin",   0x800000, 0x7AACAB47, 3 | BRF_GRA },		 //  6
	{ "256-c6.bin",   0x800000, 0xC698FD5D, 3 | BRF_GRA },		 //  7
	{ "256-c7.bin",   0x800000, 0xCFCEDDD2, 3 | BRF_GRA },		 //  8
	{ "256-c8.bin",   0x800000, 0x4D9BE34C, 3 | BRF_GRA },		 //  9

	{ "256-m1.bin",   0x080000, 0xEAEEC116, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "256-v1.bin",   0x400000, 0xF2690241, 5 | BRF_SND },		 // 11 Sound data
	{ "256-v2.bin",   0x400000, 0x7E2A10BD, 5 | BRF_SND },		 // 12
	{ "256-v3.bin",   0x400000, 0x0EAEC17C, 5 | BRF_SND },		 // 13
	{ "256-v4.bin",   0x400000, 0x9B4B22D4, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(mslug3n, mslug3n, neogeo);
STD_ROM_FN(mslug3n);

static int mslug3nInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0xAD;
	return NeoInit();
}

struct BurnDriver BurnDrvmslug3n = {
	"mslug3n", "mslug3", "neogeo", "2000",
	"Metal Slug 3 (non encrypted P)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, mslug3nRomInfo, mslug3nRomName, neogeoInputInfo, neogeoDIPInfo,
	mslug3nInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2000 (encrypted code & graphics)

static struct BurnRomInfo kof2000RomDesc[] = {
	{ "257-sma.bin",           0x040000, 0x71C6E6BB, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "257-p1.bin",            0x400000, 0x60947B4C, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "257-p2.bin",            0x400000, 0x1B7EC415, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "257-c1.bin",            0x800000, 0xCEF1CDFA, 3 | BRF_GRA },		  //  3 Sprite data
	{ "257-c2.bin",            0x800000, 0xF7BF0003, 3 | BRF_GRA },		  //  4
	{ "257-c3.bin",            0x800000, 0x101E6560, 3 | BRF_GRA },		  //  5
	{ "257-c4.bin",            0x800000, 0xBD2FC1B1, 3 | BRF_GRA },		  //  6
	{ "257-c5.bin",            0x800000, 0x89775412, 3 | BRF_GRA },		  //  7
	{ "257-c6.bin",            0x800000, 0xFA7200D5, 3 | BRF_GRA },		  //  8
	{ "257-c7.bin",            0x800000, 0x7DA11FE4, 3 | BRF_GRA },		  //  9
	{ "257-c8.bin",            0x800000, 0xB1AFA60B, 3 | BRF_GRA },		  // 10

	{ "257-m1_decrypted.bin",  0x040000, 0xD404DB70, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code (decrypted)
	{ "257-m1.bin",            0x040000, 0x4B749113, 0 | BRF_PRG | BRF_OPT }, // 11 Z80 code

	{ "257-v1.bin",            0x400000, 0x17CDE847, 5 | BRF_SND },		  // 12 Sound data
	{ "257-v2.bin",            0x400000, 0x1aFB20FF, 5 | BRF_SND },		  // 13
	{ "257-v3.bin",            0x400000, 0x4605036A, 5 | BRF_SND },		  // 14
	{ "257-v4.bin",            0x400000, 0x764BBD6B, 5 | BRF_SND },		  // 15
};

STDROMPICKEXT(kof2000, kof2000, neogeo);
STD_ROM_FN(kof2000);

static int kof2000Init()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x00;
	return NeoSMAInit(5, kof2000WriteWordBankswitch, 0x2FFFD8, 0x2FFFDA);
}

struct BurnDriver BurnDrvkof2000 = {
	"kof2000", NULL, "neogeo", "2000",
	"The King of Fighters 2000\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_SMA_PROTECTION,
	NULL, kof2000RomInfo, kof2000RomName, neogeoInputInfo, neogeoDIPInfo,
	kof2000Init, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2000 (encrypted graphics)

static struct BurnRomInfo kof2000nRomDesc[] = {
	{ "257-p1n.bin",           0x100000, 0x5F809DBE, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "257-p2n.bin",           0x400000, 0x693C2C5E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "257-c1.bin",            0x800000, 0xCEF1CDFA, 3 | BRF_GRA },		  //  2 Sprite data
	{ "257-c2.bin",            0x800000, 0xF7BF0003, 3 | BRF_GRA },		  //  3
	{ "257-c3.bin",            0x800000, 0x101E6560, 3 | BRF_GRA },		  //  4
	{ "257-c4.bin",            0x800000, 0xBD2FC1B1, 3 | BRF_GRA },		  //  5
	{ "257-c5.bin",            0x800000, 0x89775412, 3 | BRF_GRA },		  //  6
	{ "257-c6.bin",            0x800000, 0xFA7200D5, 3 | BRF_GRA },		  //  7
	{ "257-c7.bin",            0x800000, 0x7DA11FE4, 3 | BRF_GRA },		  //  8
	{ "257-c8.bin",            0x800000, 0xB1AFA60B, 3 | BRF_GRA },		  //  9

	{ "257-m1_decrypted.bin",  0x040000, 0xD404DB70, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "257-m1.bin",            0x040000, 0x4B749113, 0 | BRF_PRG | BRF_OPT }, // 10 Z80 code

	{ "257-v1.bin",            0x400000, 0x17CDE847, 5 | BRF_SND },		  // 11 Sound data
	{ "257-v2.bin",            0x400000, 0x1aFB20FF, 5 | BRF_SND },		  // 12
	{ "257-v3.bin",            0x400000, 0x4605036A, 5 | BRF_SND },		  // 13
	{ "257-v4.bin",            0x400000, 0x764BBD6B, 5 | BRF_SND },		  // 14
};

STDROMPICKEXT(kof2000n, kof2000n, neogeo);
STD_ROM_FN(kof2000n);

static int kof2000nInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x00;
	return NeoInit();
}

struct BurnDriver BurnDrvkof2000n = {
	"kof2000n", "kof2000", "neogeo", "2000",
	"The King of Fighters 2000 (non encrypted P)\0", NULL, "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, kof2000nRomInfo, kof2000nRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2000nInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// 0258 SNK vs. Capcom?


/* -------------------------------------------------------------------------------------------

	Info from Billy Pitt's Neo-Geo proto page:
		  http://www.neobitz.com/protos/games/bb.htm

		A sports game by Visco that was shown at the European ENADA show in the 
	year 2000. It is the sequel to Battle Flip Shot. Only a handfull of copies were 
	produced and have been found. I am the proud owner of the first one that was ever 
	discovered in Italy. The game plays much faster then Flip Shot and offers 
	improvements in all areas of gameplay such as graphics, sounds, options, etc. The 
	game had been incorrectly called "Bang Head" by some previous sources prior to 
	it's discovery, which caused much confusion as well.

-------------------------------------------------------------------------------------------- */


// Bang Bead (encrypted graphics)

static struct BurnRomInfo bangbeadRomDesc[] = {
	{ "259-p1.bin",   0x200000, 0x88A37F8B, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "259-c1.bin",   0x800000, 0x1F537F74, 3 | BRF_GRA },		 //  1 Sprite data
	{ "259-c2.bin",   0x800000, 0x0EFD98FF, 3 | BRF_GRA },		 //  2

	{ "259-m1.bin",   0x020000, 0x85668EE9, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "259-v1.bin",   0x400000, 0x088EB8AB, 5 | BRF_SND },		 //  4 Sound data
	{ "259-v2.bin",   0x100000, 0x97528FE9, 5 | BRF_SND },		 //  5
};

STDROMPICKEXT(bangbead, bangbead, neogeo);
STD_ROM_FN(bangbead);

static int bangbeadInit()
{
	nNeoProtectionXor = 0xF8;
	return NeoInit();
}

struct BurnDriver BurnDrvbangbead = {
	"bangbead", NULL, "neogeo", "2000",
	"Bang Bead\0", NULL, "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SWAPP,
	NULL, bangbeadRomInfo, bangbeadRomName, neogeoInputInfo, neogeoDIPInfo,
	bangbeadInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Bang Bead (prototype)

static struct BurnRomInfo bangbedpRomDesc[] = {
	{ "259-p1.bin",   0x200000, 0x88A37F8B, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "259-s1.bin",   0x020000, 0xBB50FB2D, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "259-c1p.bin",  0x200000, 0xE3919E44, 3 | BRF_GRA },		 //  2 Sprite data
	{ "259-c2p.bin",  0x200000, 0xBAF5A320, 3 | BRF_GRA },		 //  3
	{ "259-c3p.bin",  0x100000, 0xC8E52157, 3 | BRF_GRA },		 //  4
	{ "259-c4p.bin",  0x100000, 0x69FA8E60, 3 | BRF_GRA },		 //  5

	{ "259-m1.bin",   0x020000, 0x85668EE9, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code

	{ "259-v1p.bin",  0x200000, 0xE97B9385, 5 | BRF_SND },		 //  7 Sound data
	{ "259-v2p.bin",  0x200000, 0xB0CBD70A, 5 | BRF_SND },		 //  8
	{ "259-v3p.bin",  0x100000, 0x97528FE9, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(bangbedp, bangbedp, neogeo);
STD_ROM_FN(bangbedp);

struct BurnDriver BurnDrvbangbedp = {
	"bangbedp", "bangbead", "neogeo", "2000",
	"Bang Bead (prototype)\0", "All (decrypted) data identical to bangbead", "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_PROTOTYPE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, bangbedpRomInfo, bangbedpRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Nightmare in the Dark

static struct BurnRomInfo nitdRomDesc[] = {
	{ "260-p1.bin",   0x080000, 0x61361082, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "260-c1.bin",   0x800000, 0x147B0C7F, 3 | BRF_GRA },		 //  1 Sprite data
	{ "260-c2.bin",   0x800000, 0xD2B04B0D, 3 | BRF_GRA },		 //  2

	{ "260-m1.bin",   0x080000, 0x6407C5E5, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "260-v1.bin",   0x400000, 0x24B0480C, 5 | BRF_SND },		 //  4 Sound data
};

STDROMPICKEXT(nitd, nitd, neogeo);
STD_ROM_FN(nitd);

static int nitdInit()
{
	nNeoProtectionXor = 0xFF;
	return NeoInit();
}

struct BurnDriver BurnDrvNitD = {
	"nitd", NULL, "neogeo", "2000",
	"Nightmare in the Dark\0", NULL, "Eleven / Gavaking", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, nitdRomInfo, nitdRomName, neogeoInputInfo, neogeoDIPInfo,
	nitdInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sengoku 3

static struct BurnRomInfo sengoku3RomDesc[] = {
	{ "261-p1.bin",   0x200000, 0xE0D4BC0A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
//	{ "261-p1.bin",   0x200000, 0x5B557201, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (this one is almost certainly bad)

	{ "261-c1.bin",   0x800000, 0xDED84D9C, 3 | BRF_GRA },		 //  1 Sprite data
	{ "261-c2.bin",   0x800000, 0xB8EB4348, 3 | BRF_GRA },		 //  2
	{ "261-c3.bin",   0x800000, 0x84E2034A, 3 | BRF_GRA },		 //  3
	{ "261-c4.bin",   0x800000, 0x0B45AE53, 3 | BRF_GRA },		 //  4

	{ "261-m1.bin",   0x020000, 0x36ED9CDD, 4 | BRF_ESS | BRF_PRG }, //  5 Z80 code

	{ "261-v1.bin",   0x400000, 0x64C30081, 5 | BRF_SND },		 //  6 Sound data
	{ "261-v2.bin",   0x400000, 0x392A9C47, 5 | BRF_SND },		 //  7
	{ "261-v3.bin",   0x400000, 0xC1A7EBE3, 5 | BRF_SND },		 //  8
	{ "261-v4.bin",   0x200000, 0x9000D085, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(sengoku3, sengoku3, neogeo);
STD_ROM_FN(sengoku3);

static int sengoku3Init()
{
	nNeoProtectionXor = 0xFE;
	return NeoInit();
}

struct BurnDriver BurnDrvSengoku3 = {
	"sengoku3", NULL, "neogeo", "2001",
	"Sengoku 3\0Sengoku Denshou 2001\0", NULL, "SNK", "Neo Geo",
	L"Sengoku 3\0\u6226\u56FD\u4F1D\u627F\uFF12\uFF10\uFF10\uFF11\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A | HARDWARE_SNK_SWAPP,
	NULL, sengoku3RomInfo, sengoku3RomName, neogeoInputInfo, neogeoDIPInfo,
	sengoku3Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 (encrypted graphics)

static struct BurnRomInfo kof2001RomDesc[] = {
	{ "262-p1.bin",                0x100000, 0x9381750D, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-p2.bin",                0x400000, 0x8E0D8329, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "262-c1.bin",                0x800000, 0x99CC785A, 3 | BRF_GRA },		//  2 Sprite data
	{ "262-c2.bin",                0x800000, 0x50368CBF, 3 | BRF_GRA },		//  3
	{ "262-c3.bin",                0x800000, 0xFB14FF87, 3 | BRF_GRA },		//  4
	{ "262-c4.bin",                0x800000, 0x4397FAF8, 3 | BRF_GRA },		//  5
	{ "262-c5.bin",                0x800000, 0x91F24BE4, 3 | BRF_GRA },		//  6
	{ "262-c6.bin",                0x800000, 0xA31E4403, 3 | BRF_GRA },		//  7
	{ "262-c7.bin",                0x800000, 0x54D9D1EC, 3 | BRF_GRA },		//  8
	{ "262-c8.bin",                0x800000, 0x59289A6B, 3 | BRF_GRA },		//  9

	{ "265-262_decrypted-m1.bin",  0x020000, 0x2FB0A8A5, 4 | BRF_ESS | BRF_PRG },	// 10 Z80 code (decrypted)
	{ "265-262-m1.bin",            0x020000, 0x1D5AAB51, 0 | BRF_PRG | BRF_OPT },	// 11 Z80 code

	{ "262-v1.bin",                0x400000, 0x83D49ECF, 5 | BRF_SND },		// 12 Sound data
	{ "262-v2.bin",                0x400000, 0x003F1843, 5 | BRF_SND },		// 13
	{ "262-v3.bin",                0x400000, 0x2AE38DBE, 5 | BRF_SND },		// 14
	{ "262-v4.bin",                0x400000, 0x26EC4DD9, 5 | BRF_SND },		// 15
};

STDROMPICKEXT(kof2001, kof2001, neogeo);
STD_ROM_FN(kof2001);

static int kof2001Init()
{
	nNeoProtectionXor = 0x1E;
	return NeoInit();
}

struct BurnDriver BurnDrvkof2001 = {
	"kof2001", NULL, "neogeo", "2001",
	"The King of Fighters 2001 (set 1)\0", "MVS Version", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, kof2001RomInfo, kof2001RomName, neogeoInputInfo, neogeoDIPInfo,
	kof2001Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 (aes version, encrypted graphics)

static struct BurnRomInfo kof2001hRomDesc[] = {
	{ "262-pg1.bin",               0x100000, 0x2AF7E741, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-pg2.bin",               0x400000, 0x91EEA062, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "262-c1.bin",                0x800000, 0x99CC785A, 3 | BRF_GRA },		//  2 Sprite data
	{ "262-c2.bin",                0x800000, 0x50368CBF, 3 | BRF_GRA },		//  3
	{ "262-c3.bin",                0x800000, 0xFB14FF87, 3 | BRF_GRA },		//  4
	{ "262-c4.bin",                0x800000, 0x4397FAF8, 3 | BRF_GRA },		//  5
	{ "262-c5.bin",                0x800000, 0x91F24BE4, 3 | BRF_GRA },		//  6
	{ "262-c6.bin",                0x800000, 0xA31E4403, 3 | BRF_GRA },		//  7
	{ "262-c7.bin",                0x800000, 0x54D9D1EC, 3 | BRF_GRA },		//  8
	{ "262-c8.bin",                0x800000, 0x59289A6B, 3 | BRF_GRA },		//  9

	{ "265-262_decrypted-m1.bin",  0x020000, 0x2FB0A8A5, 4 | BRF_ESS | BRF_PRG },	// 10 Z80 code (decrypted)
	{ "265-262-m1.bin",            0x020000, 0x1D5AAB51, 0 | BRF_PRG | BRF_OPT },	// 11 Z80 code

	{ "262-v1.bin",                0x400000, 0x83D49ECF, 5 | BRF_SND },		// 12 Sound data
	{ "262-v2.bin",                0x400000, 0x003F1843, 5 | BRF_SND },		// 13
	{ "262-v3.bin",                0x400000, 0x2AE38DBE, 5 | BRF_SND },		// 14
	{ "262-v4.bin",                0x400000, 0x26EC4DD9, 5 | BRF_SND },		// 15
};

STDROMPICKEXT(kof2001h, kof2001h, neogeo);
STD_ROM_FN(kof2001h);

struct BurnDriver BurnDrvkof2001h = {
	"kof2001h", "kof2001", "neogeo", "2001",
	"The King of Fighters 2001 (set 2)\0", "AES version", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, kof2001hRomInfo, kof2001hRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2001Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 4 (encrypted graphics / sound)

static struct BurnRomInfo mslug4RomDesc[] = {
	{ "263-p1.bin",            0x100000, 0x27E4DEF3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "263-p2.bin",            0x400000, 0xFDB7AED8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "263-c1.bin",            0x800000, 0x84865F8A, 3 | BRF_GRA },		  //  2 Sprite data
	{ "263-c2.bin",            0x800000, 0x81DF97F2, 3 | BRF_GRA },		  //  3
	{ "263-c3.bin",            0x800000, 0x1A343323, 3 | BRF_GRA },		  //  4
	{ "263-c4.bin",            0x800000, 0x942CFB44, 3 | BRF_GRA },		  //  5
	{ "263-c5.bin",            0x800000, 0xA748854F, 3 | BRF_GRA },		  //  6
	{ "263-c6.bin",            0x800000, 0x5C8BA116, 3 | BRF_GRA },		  //  7

	{ "263-m1_decrypted.bin",  0x010000, 0x0C4C42F8, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code (decrypted)
	{ "263-m1.bin",            0x010000, 0x38FFAD14, 0 | BRF_PRG | BRF_OPT }, //  8 Z80 code

	// Uses Neo-PCM2 SNK(c) 1999 protection chip
	{ "263-v1.bin",            0x800000, 0x01E9B9CD, 5 | BRF_SND },		  //  9 Sound data
	{ "263-v2.bin",            0x800000, 0x4AB2BF81, 5 | BRF_SND },		  // 10
};

STDROMPICKEXT(mslug4, mslug4, neogeo);
STD_ROM_FN(mslug4);

static int mslug4Init()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x31;
	nNeoPCM2SNKProtection = 8;
	return NeoInit();
}

struct BurnDriver BurnDrvmslug4 = {
	"mslug4", NULL, "neogeo", "2002",
	"Metal Slug 4\0", NULL, "Playmore Corporation / Mega Enterprise", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, mslug4RomInfo, mslug4RomName, neogeoInputInfo, neogeoDIPInfo,
	mslug4Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Rage of the Dragons (encrypted graphics / sound)

static struct BurnRomInfo rotdRomDesc[] = {
	{ "264-p1.bin",            0x800000, 0xB8CC969D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "264-c1.bin",            0x800000, 0x4F148FEE, 3 | BRF_GRA },		  //  1 Sprite data
	{ "264-c2.bin",            0x800000, 0x7CF5FF72, 3 | BRF_GRA },		  //  2
	{ "264-c3.bin",            0x800000, 0x64D84C98, 3 | BRF_GRA },		  //  3
	{ "264-c4.bin",            0x800000, 0x2F394A95, 3 | BRF_GRA },		  //  4
	{ "264-c5.bin",            0x800000, 0x6B99B978, 3 | BRF_GRA },		  //  5
	{ "264-c6.bin",            0x800000, 0x847D5C7D, 3 | BRF_GRA },		  //  6
	{ "264-c7.bin",            0x800000, 0x231D681E, 3 | BRF_GRA },		  //  7
	{ "264-c8.bin",            0x800000, 0xC5EDB5C4, 3 | BRF_GRA },		  //  8

	{ "264-m1_decrypted.bin",  0x010000, 0x7E06206D, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code (decrypted)
	{ "264-m1.bin",            0x010000, 0x9ABD048C, 0 | BRF_PRG | BRF_OPT }, // 10 Z80 code

	// Uses Neo-PCM2 SNK(c) 1999 protection chip
	{ "264-v1.bin",            0x800000, 0xFA005812, 5 | BRF_SND },		  // 11 Sound data
	{ "264-v2.bin",            0x800000, 0xC3DC8BF0, 5 | BRF_SND },		  // 12
};

STDROMPICKEXT(rotd, rotd, neogeo);
STD_ROM_FN(rotd);

static int rotdInit()
{
	nNeoProtectionXor = 0x3F;
	nNeoPCM2SNKProtection = 16;
	return NeoInit();
}

struct BurnDriver BurnDrvrotd = {
	"rotd", NULL, "neogeo", "2002",
	"Rage of the Dragons\0", NULL, "Evoga / Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, rotdRomInfo, rotdRomName, neogeoInputInfo, neogeoDIPInfo,
	rotdInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002

static struct BurnRomInfo kof2002RomDesc[] = {
	{ "265-p1.bin",            0x100000, 0x9EDE7323, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "265-p2.bin",            0x400000, 0x327266b8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "265-c1.bin",            0x800000, 0x2B65A656, 3 | BRF_GRA },		  //  2 Sprite data
	{ "265-c2.bin",            0x800000, 0xADF18983, 3 | BRF_GRA },		  //  3
	{ "265-c3.bin",            0x800000, 0x875E9Fd7, 3 | BRF_GRA },		  //  4
	{ "265-c4.bin",            0x800000, 0x2DA13947, 3 | BRF_GRA },		  //  5
	{ "265-c5.bin",            0x800000, 0x61BD165D, 3 | BRF_GRA },		  //  6
	{ "265-c6.bin",            0x800000, 0x03FDD1EB, 3 | BRF_GRA },		  //  7
	{ "265-c7.bin",            0x800000, 0x1A2749D8, 3 | BRF_GRA },		  //  8
	{ "265-c8.bin",            0x800000, 0xAB0BB549, 3 | BRF_GRA },		  //  9

	{ "265-m1_decrypted.bin",  0x020000, 0x1C661A4B, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "265-m1.bin",            0x020000, 0x85AAA632, 0 | BRF_PRG | BRF_OPT }, // 11 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "265-v1.bin",            0x800000, 0x15E8F3F5, 5 | BRF_SND },		  // 12
	{ "265-v2.bin",            0x800000, 0xDA41D6F9, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(kof2002, kof2002, neogeo);
STD_ROM_FN(kof2002);

static int kof2002Init()
{
	nNeoProtectionXor = 0xEC;
	pNeoInitCallback = kof2002Decrypt;
	nNeoPCM2PLAYMOREProtection = 1;
	return NeoInit();
}

struct BurnDriver BurnDrvkof2002 = {
	"kof2002", NULL, "neogeo", "2002",
	"The King of Fighters 2002 - challenge to ultimate battle\0", NULL, "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, kof2002RomInfo, kof2002RomName, neogeoInputInfo, neogeoDIPInfo,
	kof2002Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Matrimelee (encrypted graphics / sound)

static struct BurnRomInfo matrimRomDesc[] = {
	{ "266-p1.bin",            0x100000, 0x5d4c2dc7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "266-p2.bin",            0x400000, 0xa14b1906, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "266-c1.bin",            0x800000, 0x505f4e30, 3 | BRF_GRA },		  //  2 Sprite data
	{ "266-c2.bin",            0x800000, 0x3cb57482, 3 | BRF_GRA },		  //  3
	{ "266-c3.bin",            0x800000, 0xf1cc6ad0, 3 | BRF_GRA },		  //  4
	{ "266-c4.bin",            0x800000, 0x45b806b7, 3 | BRF_GRA },		  //  5
	{ "266-c5.bin",            0x800000, 0x9a15dd6b, 3 | BRF_GRA },		  //  6
	{ "266-c6.bin",            0x800000, 0x281cb939, 3 | BRF_GRA },		  //  7
	{ "266-c7.bin",            0x800000, 0x4b71f780, 3 | BRF_GRA },		  //  8
	{ "266-c8.bin",            0x800000, 0x29873d33, 3 | BRF_GRA },		  //  9

	{ "266-m1_decrypted.bin",  0x020000, 0xD2F3742D, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "266-m1.bin",            0x020000, 0x456c3e6c, 0 | BRF_PRG | BRF_OPT }, // 11 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "266-v1.bin",            0x800000, 0xa4f83690, 5 | BRF_SND },		  // 12
	{ "266-v2.bin",            0x800000, 0xd0f69eda, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(matrim, matrim, neogeo);
STD_ROM_FN(matrim);

static int matrimInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x6A;
	pNeoInitCallback = kof2002Decrypt;
	nNeoPCM2PLAYMOREProtection = 2;
	return NeoInit();
}

struct BurnDriver BurnDrvmatrim = {
	"matrim", NULL, "neogeo", "2002",
	"Matrimelee\0Shin gouketsuzi ichizoku - Toukon\0", NULL, "Playmore / Noise Factory / Atlus", "Neo Geo",
	L"\u65B0\u8C6A\u8840\u5BFA\u4E00\u65CF - \u95D8\u5A5A\0Matrimelee\0", NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, matrimRomInfo, matrimRomName, neogeoInputInfo, neogeoDIPInfo,
	matrimInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Pochi and Nyaa

static struct BurnRomInfo pnyaaRomDesc[] = {
	{ "267-ep1.bin",           0x100000, 0x112fe2c0, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "267-c1.bin",            0x800000, 0x5eebee65, 3 | BRF_GRA },		  //  1 Sprite data
	{ "267-c2.bin",            0x800000, 0x2b67187b, 3 | BRF_GRA },		  //  2

	{ "267-m1_decrypted.bin",  0x080000, 0xd58eaa8e, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code (decrypted)
	{ "267-m1.bin",            0x080000, 0xc7853ccd, 0 | BRF_PRG | BRF_OPT }, //  4 Z80 code

	// Uses Neo-PCM2 SNK(c) 1999 protection chip
	{ "267-v1.bin",            0x400000, 0xe2e8e917, 5 | BRF_SND },		  //  5 Sound data
};

STDROMPICKEXT(pnyaa, pnyaa, neogeo);
STD_ROM_FN(pnyaa);

static int pnyaaInit()
{
	nNeoPCM2SNKProtection = 4;
	nNeoProtectionXor = 0x2E;
	return NeoInit();
}

struct BurnDriver BurnDrvpnyaa = {
	"pnyaa", NULL, "neogeo", "2003",
	"Pochi and Nyaa\0", NULL, "Aiky", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, pnyaaRomInfo, pnyaaRomName, neogeoInputInfo, neogeoDIPInfo,
	pnyaaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*-------------------------------------------------------------------------------------

	Metal Slug 5 PCB likely has very similar protections to that of SVCPCB &
	kf2k3pcb.

	The Cx protection chip is not labeled CMC like the MVS, and is labeled:

		SNK	     // svc: ""
		90G06CF7050  // svc: ""
		JAPAN 0337EA // svc: JAPAN 0245EA
		B0021DAA     // svc: 50014AAC

	Next is the NEO-PVC (Px protection) chip.  It is labeled:

		PLAYMORE
		NEO-PVC
		(C) PLAYMORE 2003
		0333 Z08

	Last is the NEO-PCM2 (Vx protection) chip. It is labeled:

		PLAYMORE
		NEO-PCM2
		(C)PLAYMORE 2002
		0331 Z32

	Metal Slug 5 (MVS and PCB) is the least protected of the NEO-PVC games
	in the 68K Code. It does not have the extra ram bank or the the pallete
	calculations that SVC and kof2003 do.  Also, the bankswitch in this
	games is not checked well, so you can use a very simple driver just
	using the data that is written to 0x2FFFF2 and bitshifting it.
	
	This, however, is not correct. It should use the entire	PVC bankswitch
	handler.

---------------------------------------------------------------------------------------*/

// Metal Slug 5 (PCB board)

static struct BurnRomInfo ms5pcbRomDesc[] = {
	// The Program ROMs are the same as the MVS cart, but labeled different.
	{ "268-p1r.bin",           0x400000,  0xd0466792, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "268-p2r.bin",           0x400000,  0xfbf6b61e, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "268-c1.bin",            0x1000000, 0x802042e8, 3 | BRF_GRA }, 	   //  2 Sprite data
	{ "268-c2.bin",            0x1000000, 0x3b89fb9f, 3 | BRF_GRA }, 	   //  3
	{ "268-c3.bin",            0x1000000, 0x0f3f59e3, 3 | BRF_GRA }, 	   //  4
	{ "268-c4.bin",            0x1000000, 0x3ad8435a, 3 | BRF_GRA }, 	   //  5

	{ "268-m1_decrypted.bin",  0x080000,  0x2f621a2b, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code (decrypted)
	{ "268-m1.bin",            0x080000,  0x4a5a6e0e, 0 | BRF_PRG | BRF_OPT }, //  7 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "268-v1.bin",            0x1000000, 0x8458afe5, 5 | BRF_SND }, 	   //  8 Sound data
};

STDROMPICKEXT(ms5pcb, ms5pcb, PCB268);
STD_ROM_FN(ms5pcb);

static int ms5pcbInit()
{
	nNeoProtectionXor = 0x19;
	return NeoPVCInit(1, NULL, 3, 7);
}

struct BurnDriver BurnDrvms5pcb = {
	"ms5pcb", NULL, NULL, "2003", // boardrom is NULL because it NOT a neogeo cart
	"Metal Slug 5 (JAMMA PCB)\0", "PCB Custom board", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_PCB_BIOS,
	NULL, ms5pcbRomInfo, ms5pcbRomName, neogeoInputInfo, PCB268DIPInfo,
	ms5pcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 5 (MVS Cart)

static struct BurnRomInfo mslug5RomDesc[] = {
	{ "268-p1cr.bin",          0x400000, 0xd0466792, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "268-p2cr.bin",          0x400000, 0xfbf6b61e, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "268-c1c.bin",           0x800000, 0xab7c389a, 3 | BRF_GRA },		  //  2 Sprite data
	{ "268-c2c.bin",           0x800000, 0x3560881b, 3 | BRF_GRA },		  //  3
	{ "268-c3c.bin",           0x800000, 0x3af955ea, 3 | BRF_GRA },		  //  4
	{ "268-c4c.bin",           0x800000, 0xc329c373, 3 | BRF_GRA },		  //  5
	{ "268-c5c.bin",           0x800000, 0x959c8177, 3 | BRF_GRA },		  //  6
	{ "268-c6c.bin",           0x800000, 0x010a831b, 3 | BRF_GRA },		  //  7
	{ "268-c7c.bin",           0x800000, 0x6d72a969, 3 | BRF_GRA },		  //  8
	{ "268-c8c.bin",           0x800000, 0x551d720e, 3 | BRF_GRA },		  //  9

	{ "268-m1_decrypted.bin",  0x080000, 0x2f621a2b, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "268-m1.bin",            0x080000, 0x4a5a6e0e, 0 | BRF_PRG | BRF_OPT }, // 11 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "268-v1c.bin",           0x800000, 0xae31d60c, 5 | BRF_SND },		  // 12 Sound data
	{ "268-v2c.bin",           0x800000, 0xc40613ed, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(mslug5, mslug5, neogeo);
STD_ROM_FN(mslug5);

static int mslug5Init()
{
	nNeoProtectionXor = 0x19;
	return NeoPVCInit(1, NULL, 3, 0);
}

struct BurnDriver BurnDrvmslug5 = {
	"mslug5", NULL, "neogeo", "2003",
	"Metal Slug 5 (MVS)\0", "MVS Version", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, mslug5RomInfo, mslug5RomName, neogeoInputInfo, neogeoDIPInfo,
	mslug5Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* -----------------------------------------------------------------------------

  SVCPCB has some very nasty encryptions.  The P1 is unusual in that it
  has 8mb of usable data, 8 more mb of dummy data, and then 16 more mb
  of junk data.  The dummy data was just to serve as a buffer zone
  between the real and the junk.

  The P is different from the other neo-pvc protected roms in that the
  data is stored in a linear fashion.  I have been told that there is
  at least one more board revision of this game which offers different
  protections, but using the same methods as the current one.

  The Cx data is stored quite differently from any other neogeo rom as
  well. Normally Neo-Geo Cx roms are stored in a way that 1 byte must
  come from the c1, and then 1 byte from the c2, 1 byte from the c1,
  and so on.  These are stored so that bytes 0 - 0x1FFFFFF are stored
  in C1 and bytes 0x2000000-0x3FFFFFF are stored in the C2.  The ROMs
  also have a very nasty protection on them, it is a 32bit bitswap on
  the data, a 24bit bitswap on the address and then a xor on the address. 
  After that, there is also the normal CMC50 (kof2000-type encryption).

  Supposedly all of this protection is done in a small buffer in one chip.
  The M rom seems to have the standard protection on it, so nothing
  really new there.

  The Vx roms are encrypted using the standard NEO-PCM2 V2 ©2002
  SNK-Playmore revision chip.  see info of this on neo_decrypt.cpp

  The last bit of data is the 269 bios.  This bios contains copies of
  the Jap. J3 bios and copies of the Asia S3 bios.  The region of the
  game can be switched by using a switch or jumper on the pcb itself.

------------------------------------------------------------------------------ */

// SvC Chaos - SNK vs CAPCOM (PCB board, set 1)

static struct BurnRomInfo svcpcbRomDesc[] = {
	{ "269-p1.bin",            0x2000000, 0x432CFDFC, 1 | BRF_ESS | BRF_PRG }, // 0 68K code

	{ "269-c1.bin",            0x2000000, 0x1B608F9C, 3 | BRF_GRA },	   // 1 Sprite data
	{ "269-c2.bin",            0x2000000, 0x5A95F294, 3 | BRF_GRA },	   // 2

	{ "269-m1_decrypted.bin",  0x080000,  0x7b7bf462, 4 | BRF_ESS | BRF_PRG }, // 3 Z80 code (decrypted)
	{ "269-m1.bin",            0x080000,  0xf6819d00, 0 | BRF_PRG | BRF_OPT }, // 4

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "269-v1.bin",            0x800000,  0xC659B34C, 5 | BRF_SND },	   // 5 Sound data
	{ "269-v2.bin",            0x800000,  0xDD903835, 5 | BRF_SND },	   // 6
};

STDROMPICKEXT(svcpcb, svcpcb, PCB269);
STD_ROM_FN(svcpcb);

static int svcpcbInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x57;
	return NeoPVCInit(2, NULL, 4, 7);
}

struct BurnDriver BurnDrvsvcpcb = {
	"svcpcb", NULL, NULL, "2003", // boardrom is NULL because it NOT a neogeo cart
	"SvC Chaos - SNK vs CAPCOM (JAMMA PCB, set 1)\0", "PCB Custom board / Asia / Japan", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_PCB_BIOS,
	NULL, svcpcbRomInfo, svcpcbRomName, neogeoInputInfo, PCB269DIPInfo,
	svcpcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* -------------------------------------------------------------------------

   This is an alternate version of the PCB, 68K ROMs and BIOS aren't
   confirmed, but it seems that the 68K is identical to MVS one and
   BIOS identical to the one used in svcpcb.

-------------------------------------------------------------------------- */

// SvC Chaos - SNK vs CAPCOM (PCB board, set 2)

static struct BurnRomInfo svcpcbaRomDesc[] = {
	{ "269-p1.rom",            0x400000,  0x38e2005e, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "269-p2.rom",            0x400000,  0x6d13797c, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "269-c1.rom",            0x1000000, 0xE64D2B0C, 3 | BRF_GRA },	   // 2 Sprite data
	{ "269-c2.rom",            0x1000000, 0x249089C2, 3 | BRF_GRA },	   // 3
	{ "269-c3.rom",            0x1000000, 0xD32F2FAB, 3 | BRF_GRA },	   // 4
	{ "269-c4.rom",            0x1000000, 0xBF77E878, 3 | BRF_GRA },	   // 5

	{ "269-m1_decrypted.bin",  0x080000,  0x7b7bf462, 4 | BRF_ESS | BRF_PRG }, // 6 Z80 code (decrypted)
	{ "269-m1.bin",            0x080000,  0xf6819d00, 0 | BRF_PRG | BRF_OPT }, // 7

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "269-v1.rom",            0x1000000, 0xA6AF4753, 5 | BRF_SND },	   // 8 Sound data
};

STDROMPICKEXT(svcpcba, svcpcba, PCB269);
STD_ROM_FN(svcpcba);

struct BurnDriver BurnDrvsvcpcba = {
	"svcpcba", "svcpcb", NULL, "2003", // boardrom is NULL because it NOT a neogeo cart
	"SvC Chaos - SNK vs CAPCOM (JAMMA PCB, set 2)\0", "Alternate PCB Custom board / Asia / Japan", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_PCB_BIOS,
	NULL, svcpcbaRomInfo, svcpcbaRomName, neogeoInputInfo, PCB269DIPInfo,
	svcpcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM (MVS Cart)

static struct BurnRomInfo svcchaosRomDesc[] = {
	{ "269-p1.bin",            0x400000, 0x38e2005e, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "269-p2.bin",            0x400000, 0x6d13797c, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "269-c1r.bin",           0x800000, 0x887b4068, 3 | BRF_GRA },		  // 2 Sprite data
	{ "269-c2r.bin",           0x800000, 0x4e8903e4, 3 | BRF_GRA },		  // 3
	{ "269-c3r.bin",           0x800000, 0x7d9c55b0, 3 | BRF_GRA },		  // 4
	{ "269-c4r.bin",           0x800000, 0x8acb5bb6, 3 | BRF_GRA },		  // 5
	{ "269-c5r.bin",           0x800000, 0x097a4157, 3 | BRF_GRA },		  // 6
	{ "269-c6r.bin",           0x800000, 0xe19df344, 3 | BRF_GRA },		  // 7
	{ "269-c7r.bin",           0x800000, 0xd8f0340b, 3 | BRF_GRA },		  // 8
	{ "269-c8r.bin",           0x800000, 0x2570b71b, 3 | BRF_GRA },		  // 9

	{ "269-m1_decrypted.bin",  0x080000, 0x7b7bf462, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "269-m1.bin",            0x080000, 0xf6819d00, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Protection chip
	{ "269-v1.bin",            0x800000, 0xC659B34C, 5 | BRF_SND },		  // 12 Sound data
	{ "269-v2.bin",            0x800000, 0xDD903835, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(svcchaos, svcchaos, neogeo);
STD_ROM_FN(svcchaos);

static int svcchaosInit()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x57;
	return NeoPVCInit(2, NULL, 4, 0);
}

struct BurnDriver BurnDrvsvcchaos = {
	"svcchaos", NULL, "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM (MVS)\0", "MVS version", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, svcchaosRomInfo, svcchaosRomName, neogeoInputInfo, neogeoDIPInfo,
	svcchaosInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V (MVS Cart)

static struct BurnRomInfo samsho5RomDesc[] = {
	{ "270-p1.bin",            0x400000, 0x4a2a09e6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "270-p2.bin",            0x400000, 0xe0c74c85, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "270-c1.bin",            0x800000, 0x14ffffac, 3 | BRF_GRA },		  //  2 Sprite data
	{ "270-c2.bin",            0x800000, 0x401f7299, 3 | BRF_GRA },		  //  3
	{ "270-c3.bin",            0x800000, 0x838f0260, 3 | BRF_GRA },		  //  4
	{ "270-c4.bin",            0x800000, 0x041560a5, 3 | BRF_GRA },		  //  5
	{ "270-c5.bin",            0x800000, 0xbd30b52d, 3 | BRF_GRA },		  //  6
	{ "270-c6.bin",            0x800000, 0x86a69c70, 3 | BRF_GRA },		  //  7
	{ "270-c7.bin",            0x800000, 0xd28fbc3c, 3 | BRF_GRA },		  //  8
	{ "270-c8.bin",            0x800000, 0x02c530a6, 3 | BRF_GRA },		  //  9

	{ "270-m1_decrypted.bin",  0x080000, 0x65495887, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "270-m1.bin",            0x080000, 0x49c9901a, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "270-v1.bin",            0x800000, 0x62e434eb, 5 | BRF_SND },		  // 12
	{ "270-v2.bin",            0x800000, 0x180f3c9a, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(samsho5, samsho5, neogeo);
STD_ROM_FN(samsho5);

static int samsho5Init()
{
	nNeoProtectionXor = 0x0f;
	pNeoInitCallback = samsho5Decrypt;
	nNeoPCM2PLAYMOREProtection = 5;
	return NeoInit();
}

struct BurnDriver BurnDrvSamSho5 = {
	"samsho5", NULL, "neogeo", "2003",
	"Samurai Shodown V\0Samurai Spirits Zero (set 1)\0", "MVS Version", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, samsho5RomInfo, samsho5RomName, neogeoInputInfo, neogeoDIPInfo,
	samsho5Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V (AES cart)

static struct BurnRomInfo samsho5hRomDesc[] = {
	{ "270-p1c.bin",           0x400000, 0xbf956089, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "270-p2c.bin",           0x400000, 0x943a6b1d, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "270-c1.bin",            0x800000, 0x14ffffac, 3 | BRF_GRA },		  //  2 Sprite data
	{ "270-c2.bin",            0x800000, 0x401f7299, 3 | BRF_GRA },		  //  3
	{ "270-c3.bin",            0x800000, 0x838f0260, 3 | BRF_GRA },		  //  4
	{ "270-c4.bin",            0x800000, 0x041560a5, 3 | BRF_GRA },		  //  5
	{ "270-c5.bin",            0x800000, 0xbd30b52d, 3 | BRF_GRA },		  //  6
	{ "270-c6.bin",            0x800000, 0x86a69c70, 3 | BRF_GRA },		  //  7
	{ "270-c7.bin",            0x800000, 0xd28fbc3c, 3 | BRF_GRA },		  //  8
	{ "270-c8.bin",            0x800000, 0x02c530a6, 3 | BRF_GRA },		  //  9

	{ "270-m1_decrypted.bin",  0x080000, 0x65495887, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "270-m1.bin",            0x080000, 0x49c9901a, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "270-v1.bin",            0x800000, 0x62e434eb, 5 | BRF_SND },		  // 12
	{ "270-v2.bin",            0x800000, 0x180f3c9a, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(samsho5h, samsho5h, neogeo);
STD_ROM_FN(samsho5h);

struct BurnDriver BurnDrvSamSho5h = {
	"samsho5h", "samsho5", "neogeo", "2003",
	"Samurai Shodown V\0Samurai Spirits Zero (set 2)\0", "AES Version", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, samsho5hRomInfo, samsho5hRomName, neogeoInputInfo, neogeoDIPInfo,
	samsho5Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*---------------------------------------------------------------------------------------

   King of Fighters 2003 PCB seems to have the destinction of being the absolute
   most protected Neo-Geo game.  The Cx roms have a second layer of encryption
   on them involving address & data xors & bitswaps.  Also, the Cx are loaded
   differently than any other neogeo game. They are loaded interleaved word-wise.
   Next, the m1 seems to have an extra bitswap on it (this can be found when comparing 
   the m1c).  The P1 & P2 have somewhat standard Neo-PVC encryption on them (though the 
   1st mb of the program roms are not xored), The V rom has the Neo-PCM2 v2 (Playmore)
   type encryption.  The bios rom has a somewhat unusual scrambling method on it, using
   bits from other parts of the addresses to xor itself. The bios contains some program
   code that is required. And last, but not least, it has the modified bankswitch and
   Pallete modification that SVC also has.
   
   The more interesting part is the p3 rom that it has. Suprisingly, this part of the
   rom was not as nasty as I expected it to be.  I discovered quickly, after I had
   figured out the address scrambling, that the data xor was being done by using the
   data from the p2 rom. It uses data from 0x80000-0xFFFFF twice and then moves
   to the next xor.

   These are in the Px data. I think they are the compile dates & times
   Mon Nov 24 17:02:55 2003 // kf2k3 pcb
   Mon Dec 01 17:13:48 2003 // kf2k3 mvs

----------------------------------------------------------------------------------------*/

// The King of Fighters 2003 (PCB board)

static struct BurnRomInfo kf2k3pcbRomDesc[] = {
	{ "271-p1.bin",            0x400000,  0xb9da070c, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "271-p2.bin",            0x400000,  0xda3118c4, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "271-p3.bin",            0x100000,  0x5cefd0d2, 1 | BRF_PRG | BRF_OPT }, //  2

	{ "271-c1.bin",            0x1000000, 0xf5ebb327, 3 | BRF_GRA },	   //  3 Sprite data
	{ "271-c2.bin",            0x1000000, 0x2be21620, 3 | BRF_GRA },	   //  4
	{ "271-c3.bin",            0x1000000, 0xddded4ff, 3 | BRF_GRA },	   //  5
	{ "271-c4.bin",            0x1000000, 0xd85521e6, 3 | BRF_GRA },	   //  6
	{ "271-c5.bin",            0x1000000, 0x18aa3540, 3 | BRF_GRA },	   //  7 (The last 2 Cx roms contains S1-ROM)
	{ "271-c6.bin",            0x1000000, 0x1c40de87, 3 | BRF_GRA },	   //  8 (data only, no sprite data)

	{ "271-m1_decrypted.bin",  0x080000,  0x0e86af8f, 4 | BRF_ESS | BRF_PRG }, //  9  Z80 code (decrypted)
	{ "271-m1.bin",            0x080000,  0xd6bcf2bc, 0 | BRF_PRG | BRF_OPT }, // 10 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "271-v1.bin",            0x1000000, 0x1d96154b, 5 | BRF_SND },	   // 11 Sound data
};

STDROMPICKEXT(kf2k3pcb, kf2k3pcb, PCB271);
STD_ROM_FN(kf2k3pcb);

static int kf2k3pcbInit()
{
	nNeoTextROMSize = 0x100000; // This should be 512 KB... taking 1 MB by now.
	nNeoProtectionXor = 0x9d;
	return NeoPVCInit(3, kf2k3pcbBIOSDecrypt, 6, 7);
}

struct BurnDriver BurnDrvkf2k3pcb = {
	"kf2k3pcb", NULL, NULL, "2003", // boardrom is NULL because it NOT a neogeo cart
	"The King of Fighters 2003 (JAMMA PCB)\0", "PCB Custom board / Japan", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_PCB_BIOS,
	NULL, kf2k3pcbRomInfo, kf2k3pcbRomName, neogeoInputInfo, PCB271DIPInfo,
	kf2k3pcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2003 (MVS Cart)

static struct BurnRomInfo kof2003RomDesc[] = {
	{ "271-p1c.bin",            0x400000, 0x530ecc14,  1 | BRF_ESS | BRF_PRG }, //  0 68K code (not interleaved?)
	{ "271-p2c.bin",            0x400000, 0xfd568da9,  1 | BRF_ESS | BRF_PRG }, //  1
	{ "271-p3c.bin",            0x100000, 0xaec5b4a9,  1 | BRF_PRG | BRF_OPT }, //  2

	{ "271-c1c.bin",            0x800000, 0xb1dc25d0,  3 | BRF_GRA },	    //  3 Sprite data
	{ "271-c2c.bin",            0x800000, 0xd5362437,  3 | BRF_GRA },	    //  4
	{ "271-c3c.bin",            0x800000, 0x0a1fbeab,  3 | BRF_GRA },	    //  5
	{ "271-c4c.bin",            0x800000, 0x87b19a0c,  3 | BRF_GRA },	    //  6
	{ "271-c5c.bin",            0x800000, 0x704ea371,  3 | BRF_GRA },	    //  7
	{ "271-c6c.bin",            0x800000, 0x20a1164c,  3 | BRF_GRA },	    //  8
	{ "271-c7c.bin",            0x800000, 0x189aba7f,  3 | BRF_GRA },	    //  9
	{ "271-c8c.bin",            0x800000, 0x20ec4fdc,  3 | BRF_GRA },	    // 10

	{ "271-m1c_decrypted.bin",  0x080000, 0x4374cb5c,  4 | BRF_ESS | BRF_PRG }, // 11 Z80 code (decrypted)
	{ "271-m1c.bin",            0x080000, 0xf5515629,  0 | BRF_PRG | BRF_OPT }, // 12 Z80 code

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "271-v1c.bin",            0x800000, 0xffa3f8c7,  5 | BRF_SND },	    // 13 Sound data (comming from 16 MB PCB Sample...)
	{ "271-v2c.bin",            0x800000, 0x5382c7d1,  5 | BRF_SND },	    // 14
};

STDROMPICKEXT(kof2003, kof2003, neogeo);
STD_ROM_FN(kof2003);

static int kof2003Init()
{
	nNeoTextROMSize = 0x080000;
	nNeoProtectionXor = 0x9d;
	return NeoPVCInit(4, NULL, 6, 0);
}

struct BurnDriver BurnDrvkof2003 = {
	"kof2003", NULL, "neogeo", "2003",
	"The King of Fighters 2003 (MVS)\0", "MVS Version", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_ENCRYPTED_B,
	NULL, kof2003RomInfo, kof2003RomName, neogeoInputInfo, neogeoDIPInfo,
	kof2003Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* -----------------------------------------------------------------------------

  There are three different variations of official samsho5sp carts.
  The first to appear on the net was a dump of the AES cart. This original
  cart had the fatalities locked out and inaccesable.  Later, after this 
  was added to mame, the other two were released.  They are: the MVS cart,
  which has full & complete fatalities, and the AES reprogrammed cart. This
  is what people got when they sent in their "fatalities removed" cart.

----------------------------------------------------------------------------- */

// Samurai Shodown V Special (Uncensored version)

static struct BurnRomInfo samsh5spRomDesc[] = {
	{ "272-p1.bin",            0x400000, 0xfb7a6bba, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "272-p2.bin",            0x400000, 0x63492ea6, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "272-c1.bin",            0x800000, 0x4F97661A, 3 | BRF_GRA },		  // 2 Sprite data
	{ "272-c2.bin",            0x800000, 0xA3AFDA4F, 3 | BRF_GRA },		  // 3
	{ "272-c3.bin",            0x800000, 0x8C3C7502, 3 | BRF_GRA },		  // 4
	{ "272-c4.bin",            0x800000, 0x32D5E2E2, 3 | BRF_GRA },		  // 5
	{ "272-c5.bin",            0x800000, 0x6CE085BC, 3 | BRF_GRA },		  // 6
	{ "272-c6.bin",            0x800000, 0x05C8DC8E, 3 | BRF_GRA },		  // 7
	{ "272-c7.bin",            0x800000, 0x1417B742, 3 | BRF_GRA },		  // 8
	{ "272-c8.bin",            0x800000, 0xD49773CD, 3 | BRF_GRA },		  // 9

	{ "272-m1_decrypted.bin",  0x080000, 0x203d744e, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "272-m1.bin",            0x080000, 0xADEEBF40, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "272-v1.bin",            0x800000, 0x76A94127, 5 | BRF_SND },		  // 12 Sound data
	{ "272-v2.bin",            0x800000, 0x4BA507F1, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(samsh5sp, samsh5sp, neogeo);
STD_ROM_FN(samsh5sp);

static int samsh5spInit()
{
	nNeoProtectionXor = 0x0d;
	pNeoInitCallback = samsh5spDecrypt;
	nNeoPCM2PLAYMOREProtection = 7;
	return NeoInit();
}

struct BurnDriver BurnDrvsamsh5sp = {
	"samsh5sp", NULL, "neogeo", "2004",
	"Samurai Shodown V Special\0Samurai Spirits Zero Special (set 1)\0", "Uncensored version", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, samsh5spRomInfo, samsh5spRomName, neogeoInputInfo, neogeoDIPInfo,
	samsh5spInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V Special (Censored version)

static struct BurnRomInfo samsh5shRomDesc[] = {
	{ "272-p1c.bin",           0x400000, 0x9291794d, 1 | BRF_ESS | BRF_PRG }, // 0 68K code (AES dumps does have MVS protection?)
	{ "272-p2c.bin",           0x400000, 0xfa1a7dd8, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "272-c1.bin",            0x800000, 0x4F97661A, 3 | BRF_GRA },		  // 2 Sprite data
	{ "272-c2.bin",            0x800000, 0xA3AFDA4F, 3 | BRF_GRA },		  // 3
	{ "272-c3.bin",            0x800000, 0x8C3C7502, 3 | BRF_GRA },		  // 4
	{ "272-c4.bin",            0x800000, 0x32D5E2E2, 3 | BRF_GRA },		  // 5
	{ "272-c5.bin",            0x800000, 0x6CE085BC, 3 | BRF_GRA },		  // 6
	{ "272-c6.bin",            0x800000, 0x05C8DC8E, 3 | BRF_GRA },		  // 7
	{ "272-c7.bin",            0x800000, 0x1417B742, 3 | BRF_GRA },		  // 8
	{ "272-c8.bin",            0x800000, 0xD49773CD, 3 | BRF_GRA },		  // 9

	{ "272-m1_decrypted.bin",  0x080000, 0x203d744e, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "272-m1.bin",            0x080000, 0xADEEBF40, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "272-v1.bin",            0x800000, 0x76A94127, 5 | BRF_SND },		  // 12 Sound data
	{ "272-v2.bin",            0x800000, 0x4BA507F1, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(samsh5sh, samsh5sh, neogeo);
STD_ROM_FN(samsh5sh);

struct BurnDriver BurnDrvsamsh5sh = {
	"samsh5sh", "samsh5sp", "neogeo", "2004",
	"Samurai Shodown V Special\0Samurai Spirits Zero Special (set 2)\0", "Censored version", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, samsh5shRomInfo, samsh5shRomName, neogeoInputInfo, neogeoDIPInfo,
	samsh5spInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V Special (Less censored version)

static struct BurnRomInfo samsh5snRomDesc[] = {
	{ "272-p1ca.bin",          0x400000, 0xc30a08dd, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "272-p2ca.bin",          0x400000, 0xbd64a518, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "272-c1.bin",            0x800000, 0x4F97661A, 3 | BRF_GRA },		  // 2 Sprite data
	{ "272-c2.bin",            0x800000, 0xA3AFDA4F, 3 | BRF_GRA },		  // 3
	{ "272-c3.bin",            0x800000, 0x8C3C7502, 3 | BRF_GRA },		  // 4
	{ "272-c4.bin",            0x800000, 0x32D5E2E2, 3 | BRF_GRA },		  // 5
	{ "272-c5.bin",            0x800000, 0x6CE085BC, 3 | BRF_GRA },		  // 6
	{ "272-c6.bin",            0x800000, 0x05C8DC8E, 3 | BRF_GRA },		  // 7
	{ "272-c7.bin",            0x800000, 0x1417B742, 3 | BRF_GRA },		  // 8
	{ "272-c8.bin",            0x800000, 0xD49773CD, 3 | BRF_GRA },		  // 9

	{ "272-m1_decrypted.bin",  0x080000, 0x203d744e, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)
	{ "272-m1.bin",            0x080000, 0xADEEBF40, 0 | BRF_PRG | BRF_OPT }, // 11

	// This uses Neo-PCM2 PLAYMORE(c) 2002 Chip Protection
	{ "272-v1.bin",            0x800000, 0x76A94127, 5 | BRF_SND },		  // 12 Sound data
	{ "272-v2.bin",            0x800000, 0x4BA507F1, 5 | BRF_SND },		  // 13
};

STDROMPICKEXT(samsh5sn, samsh5sn, neogeo);
STD_ROM_FN(samsh5sn);

struct BurnDriver BurnDrvsamsh5sn = {
	"samsh5sn", "samsh5sp", "neogeo", "2004",
	"Samurai Shodown V Special\0Samurai Spirits Zero Special (set 3)\0", "Less censored version", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B,
	NULL, samsh5snRomInfo, samsh5snRomName, neogeoInputInfo, neogeoDIPInfo,
	samsh5spInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// -----------------------------------------------------------------------------
// Free / homebrew / prototype games


// Beast Demo (Sega bassed)

static struct BurnRomInfo beastnRomDesc[] = {
	{ "2002-p1.bin",  0x080000, 0x1f9e62a4, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "2002-s1.bin",  0x020000, 0x05a417f5, 2 | BRF_GRA }, 		 //  1 Text data

	{ "2002-c1.bin",  0x080000, 0xe1974741, 3 | BRF_GRA }, 		 //  2 Sprite data
	{ "2002-c2.bin",  0x080000, 0x9f5b9cf6, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(beastn, beastn, neogeo);
STD_ROM_FN(beastn);

struct BurnDriver BurnDrvbeastn = {
	"beastn", "puzzledp", "neogeo", "2004",
	"Shadow of the Beast\0", "Sega bassed", "Jeff Kurtz", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, beastnRomInfo, beastnRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Columns (Sega bassed)

static struct BurnRomInfo columnsnRomDesc[] = {
	{ "2000-p1.bin",  0x080000, 0xc6c9888d, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "2000-s1.bin",  0x020000, 0x089a28a8, 2 | BRF_GRA },		 //  1 Text data

	{ "2000-c1.bin",  0x080000, 0x9a579cab, 3 | BRF_GRA },		 //  2 Sprite data
	{ "2000-c2.bin",  0x080000, 0x91d14043, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(columnsn, columnsn, neogeo);
STD_ROM_FN(columnsn);

struct BurnDriver BurnDrvcolumnsn = {
	"columnsn", "puzzledp", "neogeo", "2004",
	"Columns\0", NULL, "Jeff Kurtz", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, columnsnRomInfo, columnsnRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Poker Night

static struct BurnRomInfo poknightRomDesc[] = {
	{ "2003-p1.bin",  0x080000, 0x750421ee, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "2003-s1.bin",  0x020000, 0xa26d2f09, 2 | BRF_GRA },		 //  1 Text data

	{ "2003-c1.bin",  0x080000, 0x5fb2b761, 3 | BRF_GRA },		 //  2 Sprite data
	{ "2003-c2.bin",  0x080000, 0xf2b570e3, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(poknight, poknight, neogeo);
STD_ROM_FN(poknight);

struct BurnDriver BurnDrvpoknight = {
	"poknight", "puzzledp", "neogeo", "2003",
	"Poker Night\0", NULL, "Jeff Kurtz", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, poknightRomInfo, poknightRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo-Demo

static struct BurnRomInfo neodemoRomDesc[] = {
	{ "ndm-p1.bin", 0x080000, 0xfbfce2a4, 	1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "ndm-s1.bin", 0x020000, 0xcd19264f,   2 | BRF_GRA }, 	 	 //  1 Text layer tiles

	{ "ndm-c1.bin", 0x100000, 0x870b28ea,   3 | BRF_GRA }, 	 	 //  2 Sprite data
	{ "ndm-c2.bin", 0x100000, 0x1ecf8128,   3 | BRF_GRA }, 	 	 //  3

	{ "202-m1.bin", 0x020000, 0x9c0291ea,   4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin", 0x080000, 0xdebeb8fb,   5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neodemo, neodemo, neogeo);
STD_ROM_FN(neodemo);

struct BurnDriver BurnDrvNeodemo = {
	"neodemo", "puzzledp", "neogeo", "2002",
	"Neo-Demo\0", NULL, "Rastersoft / CDoty", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neodemoRomInfo, neodemoRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// 2500 Neo Demo

static struct BurnRomInfo neo2500RomDesc[] = {
	{ "2500-p1.bin", 0x080000, 0x2321C0D8, 1 | BRF_ESS | BRF_PRG },   //  0 68K code

	{ "2500-s1.bin", 0x010000, 0x1A37925C, 2 | BRF_GRA },			//  1 Text data

	{ "2500-c1.bin", 0x080000, 0x8C304B56, 3 | BRF_GRA },			//  2 Sprite data
	{ "2500-c2.bin", 0x080000, 0x9A0758D6, 3 | BRF_GRA },			//  3

	{ "202-m1.bin",  0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG },   //  4 Z80 code

	{ "202-v1.bin",  0x080000, 0xdebeb8fb, 5 | BRF_SND },			//  5 Sound data
}; 

STDROMPICKEXT(neo2500, neo2500, neogeo); 
STD_ROM_FN(neo2500);

struct BurnDriver BurnDrvneo2500 = {
	"neo2500", "puzzledp", "neogeo", "2004",
	"Neo 2500 Demo\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neo2500RomInfo, neo2500RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo No Panepon (2002-10-05)

static struct BurnRomInfo neonoponRomDesc[] = {
	{ "nnp-p1.bin",   0x080000, 0x8A792271, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "nnp-s1.bin",   0x010000, 0x93E6FE7D, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "nnp-c1.bin",   0x100000, 0x4A718AE3, 3 | BRF_GRA },		 //  2 Sprite data
	{ "nnp-c2.bin",   0x100000, 0x0E2CBC25, 3 | BRF_GRA },		 //  3

	{ "nnp-m1.bin",   0x010000, 0x7669DE64, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "nnp-v1.bin",   0x080000, 0x504BF849, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neonopon, neonopon, neogeo);
STD_ROM_FN(neonopon);

struct BurnDriver BurnDrvNeonopon = {
	"neonopon", NULL, "neogeo", "2002",
	"Neo No Panepon (2002-10-05)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neonoponRomInfo, neonoponRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo No Panepon (2002-07-07 #1)

static struct BurnRomInfo neonpon1RomDesc[] = {
	{ "nnp1-p1.bin",  0x080000, 0x43b7c759, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "nnp1-s1.bin",  0x010000, 0xe28ea706, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "nnp1-c1.bin",  0x100000, 0x24dcba77, 3 | BRF_GRA },		 //  2 Sprite data
	{ "nnp1-c2.bin",  0x100000, 0x57c41e26, 3 | BRF_GRA },		 //  3

	{ "nnp-m1.bin",   0x010000, 0x7669DE64, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "nnp-v1.bin",   0x080000, 0x504BF849, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neonpon1, neonpon1, neogeo);
STD_ROM_FN(neonpon1);

struct BurnDriver BurnDrvNeonpon1 = {
	"neonpon1", "neonopon", "neogeo", "2002",
	"Neo No Panepon (2002-07-07 #1)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, neonpon1RomInfo, neonpon1RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo No Panepon (2002-07-07 #2)

static struct BurnRomInfo neonpon2RomDesc[] = {
	{ "nnp1-p1.bin",  0x080000, 0x43b7c759, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "nnp1-s1.bin",  0x010000, 0xe28ea706, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "nnp2-c1.bin",  0x100000, 0x0833c9e7, 3 | BRF_GRA },		 //  2 Sprite data
	{ "nnp2-c2.bin",  0x100000, 0xfbf5f67f, 3 | BRF_GRA },		 //  3

	{ "nnp-m1.bin",   0x010000, 0x7669DE64, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "nnp-v1.bin",   0x080000, 0x504BF849, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neonpon2, neonpon2, neogeo);
STD_ROM_FN(neonpon2);

struct BurnDriver BurnDrvNeonpon2 = {
	"neonpon2", "neonopon", "neogeo", "2002",
	"Neo No Panepon (2002-07-07 #2)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, neonpon2RomInfo, neonpon2RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo No Panepon (2002-08-22)

static struct BurnRomInfo neonpon3RomDesc[] = {
	{ "nnp1-p1.bin",  0x080000, 0x43b7c759, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "nnp-s1.bin",   0x010000, 0x93e6fe7d, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "nnp3-c1.bin",  0x100000, 0xe0573498, 3 | BRF_GRA },		 //  2 Sprite data
	{ "nnp2-c2.bin",  0x100000, 0xfbf5f67f, 3 | BRF_GRA },		 //  3

	{ "nnp-m1.bin",   0x010000, 0x7669DE64, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "nnp-v1.bin",   0x080000, 0x504BF849, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(neonpon3, neonpon3, neogeo);
STD_ROM_FN(neonpon3);

struct BurnDriver BurnDrvNeonpon3 = {
	"neonpon3", "neonopon", "neogeo", "2002",
	"Neo No Panepon (2002-08-22)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, neonpon3RomInfo, neonpon3RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo Pong (v1.1)

static struct BurnRomInfo neopongRomDesc[] = {
	{ "npg-p1.bin",  0x020000, 0x9F35E29D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "npg-s1.bin",  0x020000, 0xCD19264F, 2 | BRF_GRA }, 		//  1 Text layer tiles

	{ "npg-c1.bin",  0x100000, 0xF5A57D1A, 3 | BRF_GRA }, 		//  2 Sprite data
	{ "npg-c2.bin",  0x100000, 0xAFFDE64E, 3 | BRF_GRA }, 		//  3

	{ "npg-m1.bin",  0x020000, 0x78C851CB, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "npg-v1.bin",  0x200000, 0x6C31223C, 5 | BRF_SND }, 		//  5 Sound data
};

STDROMPICKEXT(neopong, neopong, neogeo);
STD_ROM_FN(neopong);

struct BurnDriver BurnDrvNeopong = {
	"neopong", NULL, "neogeo", "2002",
	"Neo Pong (v1.1)\0", NULL, "Neodev Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, neopongRomInfo, neopongRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo Pong (v1.0)

static struct BurnRomInfo npong10RomDesc[] = {
	{ "np0-p1.bin",  0x020000, 0x31b724d7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "npg-s1.bin",  0x020000, 0xCD19264F, 2 | BRF_GRA }, 		//  1 Text layer tiles

	{ "np0-c1.bin",  0x100000, 0xd7587282, 3 | BRF_GRA }, 		//  2 Sprite data
	{ "np0-c2.bin",  0x100000, 0xfefc9d06, 3 | BRF_GRA }, 		//  3

	{ "np0-m1.bin",  0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "np0-v1.bin",  0x200000, 0xdebeb8fb, 5 | BRF_SND }, 		//  5 Sound data
};

STDROMPICKEXT(npong10, npong10, neogeo);
STD_ROM_FN(npong10);

struct BurnDriver BurnDrvNpong10 = {
	"npong10", "neopong", "neogeo", "2002",
	"Neo Pong (v1.0)\0", NULL, "Neodev Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, npong10RomInfo, npong10RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Neo-Geo System Check

static struct BurnRomInfo syscheckRomDesc[] = {
	{ "sys-p1.rom",  0x080000, 0xa4adbe1e, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "sys-s1.rom",  0x010000, 0x4774f28e, 2 | BRF_GRA }, 		//  1 Text data

	{ "sys-c1.rom",  0x080000, 0x75660aac, 3 | BRF_GRA }, 		//  2 Sprite data
	{ "sys-c2.rom",  0x080000, 0x75660aac, 3 | BRF_GRA }, 		//  3

	{ "nnp-m1.bin",  0x010000, 0x7669de64, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "nnp-v1.bin",  0x080000, 0x504bf849, 5 | BRF_SND }, 		//  5 Sound data
};

STDROMPICKEXT(syscheck, syscheck, neogeo);
STD_ROM_FN(syscheck);

struct BurnDriver BurnDrvsyscheck = {
	"syscheck", "neonopon", "neogeo", "2002",
	"Neo-System Check (v1.0b)\0", "Checks hardware status, obsolete due to \"Uni-bios\"", "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, syscheckRomInfo, syscheckRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Frog Feast

static struct BurnRomInfo frogfestRomDesc[] = {
	{ "frg-p1.bin",   0x080000, 0xdb0417ec, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "frg-s1.bin",   0x010000, 0x29814a2c, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "frg-c1.bin",   0x100000, 0x22a65cea, 3 | BRF_GRA },		 //  2 Sprite data
	{ "frg-c2.bin",   0x100000, 0x63ddd657, 3 | BRF_GRA },		 //  3

	{ "202-m1.bin",   0x020000, 0x9c0291ea, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "202-v1.bin",   0x080000, 0xdebeb8fb, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(frogfest, frogfest, neogeo);
STD_ROM_FN(frogfest);

struct BurnDriver BurnDrvfrogfest = {
	"frogfest", "puzzledp", "neogeo", "2005",
	"Frog Feast\0", NULL, "Rastersoft / CDoty", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO,
	NULL, frogfestRomInfo, frogfestRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

//---------------------------------------------------------------------------------
//
//	This is not exactly homebrew and not exactly a bootleg.  It seems to use
//	a tiny amount of code from karnov's revenge and was developed for as a
//	commercial game.  It, however, is very incomplete & buggy.  It also was
//	from an actual MVS cart, so it should be included in all Neo-Geo emulators.
//
//---------------------------------------------------------------------------------

// Diggerman

static struct BurnRomInfo diggermaRomDesc[] = {
	{ "dig_p1.rom",   0x080000, 0xEDA433D7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "dig_s1.rom",   0x010000, 0x75A88C1F, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "dig_c1.rom",   0x080000, 0x3DB0A4ED, 3 | BRF_GRA },		 //  2 Sprite data
	{ "dig_c2.rom",   0x080000, 0x3E632161, 3 | BRF_GRA },		 //  3

	{ "dig_m1.rom",   0x010000, 0x833CDF1B, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "dig_v1.rom",   0x080000, 0xEE15BDA4, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(diggerma, diggerma, neogeo);
STD_ROM_FN(diggerma);

struct BurnDriver BurnDrvdiggerma = {
	"diggerma", NULL, "neogeo", "1994 / 2000",
	"Digger Man\0", NULL, "Face", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_PROTOTYPE, 2, HARDWARE_SNK_NEOGEO,
	NULL, diggermaRomInfo, diggermaRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Jonas Indiana and the Lost Temple of RA

static struct BurnRomInfo ltorb1RomDesc[] = {
	{ "lt1_p1.rom", 0x040000, 0x353F6B05, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "lt1_s1.rom", 0x010000, 0x8224D8B7, 2 | BRF_GRA },           //  1 Text layer tiles

	{ "lt1_c1.rom", 0x080000, 0x8B607198, 3 | BRF_GRA },           //  2 Sprite data
	{ "lt1_c2.rom", 0x080000, 0x6B96B59C, 3 | BRF_GRA },           //  3

	{ "lt1_m1.rom", 0x010000, 0x6847Fd52, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "lt1_v1.rom", 0x080000, 0x0329C2E7, 5 | BRF_SND },           //  5 Sound data
};

STDROMPICKEXT(ltorb1, ltorb1, neogeo);
STD_ROM_FN(ltorb1);

struct BurnDriver BurnDrvLtorb1 = {
	"ltorb1", NULL, "neogeo", "2005",
	"Jonas Indiana and the Lost Temple of RA (beta 2005-07-17)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 1, HARDWARE_SNK_NEOGEO,
	NULL, ltorb1RomInfo, ltorb1RomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Codename - Blut Engel

static struct BurnRomInfo cnbeRomDesc[] = {
	{ "cnbe-p1.bin", 0x080000, 0x7ece4186, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "cnbe-s1.bin", 0x010000, 0x40a4698f, 2 | BRF_GRA },           //  1 Text layer tiles

	{ "cnbe-c1.bin", 0x100000, 0x0f4fea6f, 3 | BRF_GRA },           //  2 Sprite data
	{ "cnbe-c2.bin", 0x100000, 0x3d5fc36f, 3 | BRF_GRA },           //  3

	{ "cnbe-m1.bin", 0x010000, 0xa5821c9c, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "cnbe-v1.bin", 0x080000, 0x70191764, 5 | BRF_SND },           //  5 Sound data
};

STDROMPICKEXT(cnbe, cnbe, neogeo);
STD_ROM_FN(cnbe);

struct BurnDriver BurnDrvcnbe = {
	"cnbe", NULL, "neogeo", "2006",
	"Codename - Blut Engel (2006-01-19)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 1, HARDWARE_SNK_NEOGEO,
	NULL, cnbeRomInfo, cnbeRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// NGEM2K

static struct BurnRomInfo ngem2kRomDesc[] = {
	{ "ngem-p1.bin", 0x080000, 0xf2c42fe3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "ngem-s1.bin", 0x010000, 0xfb3c02d2, 2 | BRF_GRA },           //  1 Text layer tiles

	{ "ngem-c1.bin", 0x100000, 0xa8e2ab47, 3 | BRF_GRA },           //  2 Sprite data
	{ "ngem-c2.bin", 0x100000, 0xa738ea1c, 3 | BRF_GRA },           //  3

	{ "ngem-m1.bin", 0x010000, 0xb1f44a15, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "ngem-v1.bin", 0x080000, 0xc32199f0, 5 | BRF_SND },           //  5 Sound data
};

STDROMPICKEXT(ngem2k, ngem2k, neogeo);
STD_ROM_FN(ngem2k);

struct BurnDriver BurnDrvngem2k = {
	"ngem2k", NULL, "neogeo", "2006",
	"NGEM2K (beta 2006-01-18)\0", NULL, "blastar@gmx.net", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 1, HARDWARE_SNK_NEOGEO,
	NULL, ngem2kRomInfo, ngem2kRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// -----------------------------------------------------------------------------
// Pre-decrypted ROMsets


// Zupapa! (decrypted C-ROMs)

static struct BurnRomInfo zupapanRomDesc[] = {
	{ "070-p1.bin",   0x100000, 0x5A96203E, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "zupan_c1.rom", 0x800000, 0x65d73348, 3 | BRF_GRA },		 //  1 Sprite data
	{ "zupan_c2.rom", 0x800000, 0xc498708f, 3 | BRF_GRA },		 //  2

	{ "070-m1.bin",   0x020000, 0x5A3B3191, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "070-v1.bin",   0x200000, 0xD3A7E1FF, 5 | BRF_SND },		 //  4 Sound data
};

STDROMPICKEXT(zupapan, zupapan, neogeo);
STD_ROM_FN(zupapan);

struct BurnDriver BurnDrvzupapan = {
	"zupapan", "zupapa", "neogeo", "2001",
	"Zupapa! (decrypted C)\0", "decrypted C-ROMs", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, zupapanRomInfo, zupapanRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '99 (Non-encrypted P-ROMs, decrypted C-ROMs)

static struct BurnRomInfo kof99ndRomDesc[] = {
	{ "152-p1.bin",   0x100000, 0xF2C7DDFA, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "152-p2.bin",   0x400000, 0x274EF47A, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "kf99n_c1.rom", 0x800000, 0xb3d88546, 3 | BRF_GRA },		 //  2 Sprite data
	{ "kf99n_c2.rom", 0x800000, 0x915c8634, 3 | BRF_GRA },		 //  3
	{ "kf99n_c3.rom", 0x800000, 0xb047c9d5, 3 | BRF_GRA },		 //  4
	{ "kf99n_c4.rom", 0x800000, 0x6bc8e4b1, 3 | BRF_GRA },		 //  5
	{ "kf99n_c5.rom", 0x800000, 0x9746268c, 3 | BRF_GRA },		 //  6
	{ "kf99n_c6.rom", 0x800000, 0x238b3e71, 3 | BRF_GRA },		 //  7
	{ "kf99n_c7.rom", 0x800000, 0x2f68fdeb, 3 | BRF_GRA },		 //  8
	{ "kf99n_c8.rom", 0x800000, 0x4c2fad1e, 3 | BRF_GRA },		 //  9

	{ "251-m1.bin",   0x020000, 0x5E74539C, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "251-v1.bin",   0x400000, 0xEF2EECC8, 5 | BRF_SND },		 // 11 Sound data
	{ "251-v2.bin",   0x400000, 0x73E211CA, 5 | BRF_SND },		 // 12
	{ "251-v3.bin",   0x400000, 0x821901DA, 5 | BRF_SND },		 // 13
	{ "251-v4.bin",   0x200000, 0xB49E6178, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof99nd, kof99nd, neogeo);
STD_ROM_FN(kof99nd);

struct BurnDriver BurnDrvkof99nd = {
	"kof99nd", "kof99", "neogeo", "1999",
	"The King of Fighters '99 - millennium battle (non encrypted P, decrypted C)\0", "Non-encrypted P-ROMs, decrypted C-ROMs", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof99ndRomInfo, kof99ndRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Ganryu (decrypted C-ROMs)

static struct BurnRomInfo ganryunRomDesc[] = {
	{ "252-p1.bin",   0x200000, 0x4B8AC4FB, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "gann_c1.rom",  0x800000, 0x6BF7605B, 3 | BRF_GRA }, 		 //  1 Sprite data
	{ "gann_c2.rom",  0x800000, 0x596792CE, 3 | BRF_GRA }, 		 //  2

	{ "252-m1.bin",   0x020000, 0x30CC4099, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "252-v1.bin",   0x400000, 0xE5946733, 5 | BRF_SND },		 //  4 Sound data
};

STDROMPICKEXT(ganryun, ganryun, neogeo);
STD_ROM_FN(ganryun);

struct BurnDriver BurnDrvGanryun = {
	"ganryun", "ganryu", "neogeo", "1999",
	"Ganryu\0Musashi Ganryuki (decrypted C)\0", "decrypted C-ROMs", "Visco", "Neo Geo",
	L"Ganryu\0\u6B66\u8535\u5DCC\u6D41\u8A18 (decrypted C)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, ganryunRomInfo, ganryunRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Garou (decrypted C-ROMs)

static struct BurnRomInfo garounRomDesc[] = {
	{ "253-sma.bin",  0x040000, 0x98bc93dc, 9 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "253-ep1.p1",   0x200000, 0xea3171a4, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "253-ep2.p2",   0x200000, 0x382f704b, 1 | BRF_ESS | BRF_PRG }, //  2
	{ "253-ep3.p3",   0x200000, 0xe395bfdd, 1 | BRF_ESS | BRF_PRG }, //  3
	{ "253-ep4.p4",   0x200000, 0xda92c08e, 1 | BRF_ESS | BRF_PRG }, //  4

	{ "motwn_c1.rom", 0x800000, 0x497be3f2, 3 | BRF_GRA },		 //  5 Sprite data
	{ "motwn_c2.rom", 0x800000, 0x6a9e95ca, 3 | BRF_GRA },		 //  6
	{ "motwn_c3.rom", 0x800000, 0x39373d2f, 3 | BRF_GRA },		 //  7
	{ "motwn_c4.rom", 0x800000, 0x4de23f6c, 3 | BRF_GRA },		 //  8
	{ "motwn_c5.rom", 0x800000, 0x16634ba5, 3 | BRF_GRA },		 //  9
	{ "motwn_c6.rom", 0x800000, 0x95671ffd, 3 | BRF_GRA },		 // 10
	{ "motwn_c7.rom", 0x800000, 0xe36ce77f, 3 | BRF_GRA },		 // 11
	{ "motwn_c8.rom", 0x800000, 0xddbd1096, 3 | BRF_GRA },		 // 12

	{ "253-m1.bin",   0x040000, 0x36a806be, 4 | BRF_ESS | BRF_PRG }, // 13 Z80 code

	{ "253-v1.bin",   0x400000, 0x263e388c, 5 | BRF_SND },		 // 14 Sound data
	{ "253-v2.bin",   0x400000, 0x2c6bc7be, 5 | BRF_SND },		 // 15
	{ "253-v3.bin",   0x400000, 0x0425b27d, 5 | BRF_SND },		 // 16
	{ "253-v4.bin",   0x400000, 0xa54be8a9, 5 | BRF_SND },		 // 17
};

STDROMPICKEXT(garoun, garoun, neogeo);
STD_ROM_FN(garoun);

struct BurnDriver BurnDrvGaroun = {
	"garoun", "garou", "neogeo", "1999",
	"Garou - mark of the wolves (decrypted C)\0", "decrypted C-ROMs", "SNK", "Neo Geo",
	L"\u9913\u72FC - mark of the wolves\0Garou (decrypted C)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SMA_PROTECTION,
	NULL, garounRomInfo, garounRomName, neogeoInputInfo, neogeoDIPInfo,
	garouInit, NeoSMAExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Strikers 1945 plus (decrypted C-ROMs)

static struct BurnRomInfo s1945pnRomDesc[] = {
	{ "254-p1.bin",   0x100000, 0xFF8EFCFF, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "254-p2.bin",   0x400000, 0xEFDFD4DD, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "s45pn_c1.rom", 0x800000, 0x7b6902f9, 3 | BRF_GRA },		 //  2 Sprite data
	{ "s45pn_c2.rom", 0x800000, 0x51bd4252, 3 | BRF_GRA },		 //  3
	{ "s45pn_c3.rom", 0x800000, 0xa38993e4, 3 | BRF_GRA },		 //  4
	{ "s45pn_c4.rom", 0x800000, 0xd5696530, 3 | BRF_GRA },		 //  5
	{ "s45pn_c5.rom", 0x800000, 0x28764bd6, 3 | BRF_GRA },		 //  6
	{ "s45pn_c6.rom", 0x800000, 0x9931bdf1, 3 | BRF_GRA },		 //  7
	{ "s45pn_c7.rom", 0x800000, 0x6e12afcd, 3 | BRF_GRA },		 //  8
	{ "s45pn_c8.rom", 0x800000, 0x178d4684, 3 | BRF_GRA },		 //  9

	{ "254-m1.bin",   0x020000, 0x994B4487, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "254-v1.bin",   0x400000, 0x844F58FB, 5 | BRF_SND },		 // 11 Sound data
	{ "254-v2.bin",   0x400000, 0xD9A248F0, 5 | BRF_SND },		 // 12
	{ "254-v3.bin",   0x400000, 0x0B0D2D33, 5 | BRF_SND },		 // 13
	{ "254-v4.bin",   0x400000, 0x6D13DC91, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(s1945pn, s1945pn, neogeo);
STD_ROM_FN(s1945pn);

struct BurnDriver BurnDrvs1945pn = {
	"s1945pn", "s1945p", "neogeo", "1999",
	"Strikers 1945 plus (decrypted C)\0", "decrypted C-ROMs", "Psikyo", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, s1945pnRomInfo, s1945pnRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Prehistoric Isle 2 (decrypted C-ROMs)

static struct BurnRomInfo preisl2nRomDesc[] = {
	{ "255-p1.bin",   0x100000, 0xDFA3C0F3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "255-p2.bin",   0x400000, 0x42050B80, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "pi2n_c1.rom",  0x800000, 0x50fd785e, 3 | BRF_GRA },		 //  2 Sprite data
	{ "pi2n_c2.rom",  0x800000, 0xab913f1e, 3 | BRF_GRA },		 //  3
	{ "pi2n_c3.rom",  0x800000, 0xbc0ee75c, 3 | BRF_GRA },		 //  4
	{ "pi2n_c4.rom",  0x800000, 0x29908823, 3 | BRF_GRA },		 //  5
	{ "pi2n_c5.rom",  0x800000, 0x83c56bca, 3 | BRF_GRA },		 //  6
	{ "pi2n_c6.rom",  0x800000, 0x59e0e805, 3 | BRF_GRA },		 //  7

	{ "255-m1.bin",   0x020000, 0x8EFD4014, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "255-v1.bin",   0x400000, 0x5A14543D, 5 | BRF_SND },		 // 11 Sound data
	{ "255-v2.bin",   0x200000, 0x6610D91A, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(preisl2n, preisl2n, neogeo);
STD_ROM_FN(preisl2n);

struct BurnDriver BurnDrvpreisl2n = {
	"preisl2n", "preisle2", "neogeo", "1999",
	"Prehistoric Isle 2 (decrypted C)\0", "decrypted C-ROMs", "Yumekobo", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, preisl2nRomInfo, preisl2nRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 3 (Non-encrypted P-ROMs, decrypted C-ROMs)

static struct BurnRomInfo mslug3ndRomDesc[] = {
	{ "256-ph1.rom",  0x100000, 0x9C42CA85, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "256-ph2.rom",  0x400000, 0x1F3D8CE8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ms3n_c1.rom",  0x800000, 0x3540398c, 3 | BRF_GRA },		 //  2 Sprite data
	{ "ms3n_c2.rom",  0x800000, 0xbdd220f0, 3 | BRF_GRA },		 //  3
	{ "ms3n_c3.rom",  0x800000, 0xbfaade82, 3 | BRF_GRA },		 //  4
	{ "ms3n_c4.rom",  0x800000, 0x1463add6, 3 | BRF_GRA },		 //  5
	{ "ms3n_c5.rom",  0x800000, 0x48ca7f28, 3 | BRF_GRA },		 //  6
	{ "ms3n_c6.rom",  0x800000, 0x806eb36f, 3 | BRF_GRA },		 //  7
	{ "ms3n_c7.rom",  0x800000, 0x9395b809, 3 | BRF_GRA },		 //  8
	{ "ms3n_c8.rom",  0x800000, 0xa369f9d4, 3 | BRF_GRA },		 //  9

	{ "256-m1.bin",   0x080000, 0xEAEEC116, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "256-v1.bin",   0x400000, 0xF2690241, 5 | BRF_SND },		 // 11 Sound data
	{ "256-v2.bin",   0x400000, 0x7E2A10BD, 5 | BRF_SND },		 // 12
	{ "256-v3.bin",   0x400000, 0x0EAEC17C, 5 | BRF_SND },		 // 13
	{ "256-v4.bin",   0x400000, 0x9B4B22D4, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(mslug3nd, mslug3nd, neogeo);
STD_ROM_FN(mslug3nd);

struct BurnDriver BurnDrvmslug3nd = {
	"mslug3nd", "mslug3", "neogeo", "2000",
	"Metal Slug 3 (non encrypted P, decrypted C)\0", "Non-encrypted P-ROMs, decrypted C-ROMs", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, mslug3ndRomInfo, mslug3ndRomName, neogeoInputInfo, neogeoDIPInfo,
	mslug3nInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2000 (Non-encrypted P-ROMs, decrypted C-ROMs)

static struct BurnRomInfo kof2kndRomDesc[] = {
	{ "257-p1n.bin",          0x100000, 0x5F809DBE, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "257-p2n.bin",          0x400000, 0x693C2C5E, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "kof2k_c1.rom",         0x800000, 0xabcdd424, 3 | BRF_GRA },		 //  2 Sprite data
	{ "kof2k_c2.rom",         0x800000, 0xcda33778, 3 | BRF_GRA },		 //  3
	{ "kof2k_c3.rom",         0x800000, 0x087fb15b, 3 | BRF_GRA },		 //  4
	{ "kof2k_c4.rom",         0x800000, 0xfe9dfde4, 3 | BRF_GRA },		 //  5
	{ "kof2k_c5.rom",         0x800000, 0x03ee4bf4, 3 | BRF_GRA },		 //  6
	{ "kof2k_c6.rom",         0x800000, 0x8599cc5b, 3 | BRF_GRA },		 //  7
	{ "kof2k_c7.rom",         0x800000, 0x71dfc3e2, 3 | BRF_GRA },		 //  8
	{ "kof2k_c8.rom",         0x800000, 0x0fa30e5f, 3 | BRF_GRA },		 //  9

	{ "257-m1_decrypted.bin", 0x040000, 0xD404DB70, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "257-v1.bin",           0x400000, 0x17CDE847, 5 | BRF_SND },		 // 11 Sound data
	{ "257-v2.bin",           0x400000, 0x1aFB20FF, 5 | BRF_SND },		 // 12
	{ "257-v3.bin",           0x400000, 0x4605036A, 5 | BRF_SND },		 // 13
	{ "257-v4.bin",           0x400000, 0x764BBD6B, 5 | BRF_SND },		 // 14
};

STDROMPICKEXT(kof2knd, kof2knd, neogeo);
STD_ROM_FN(kof2knd);

struct BurnDriver BurnDrvkof2knd = {
	"kof2knd", "kof2000", "neogeo", "2000",
	"The King of Fighters 2000 (non encrypted P, decrypted C)\0", "Non-encrypted P-ROMs, decrypted C-ROMs", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, kof2kndRomInfo, kof2kndRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2000nInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Bang Bead (decrypted C-ROMs)

static struct BurnRomInfo bngbeadnRomDesc[] = {
	{ "259-p1.bin",   0x200000, 0x88A37F8B, 1 | BRF_ESS | BRF_PRG}, //  0 68K code

	{ "bgn_c1.rom",   0x800000, 0xc50a91c3, 3 | BRF_GRA}, 		//  1 Sprite data
	{ "bgn_c2.rom",   0x800000, 0x820ab36e, 3 | BRF_GRA},		//  2

	{ "259-m1.bin",   0x020000, 0x85668EE9, 4 | BRF_ESS | BRF_PRG}, //  3 Z80 code

	{ "259-v1.bin",   0x400000, 0x088eb8ab, 5 | BRF_SND}, 		//  4 Sound data
	{ "259-v2.bin",   0x100000, 0x97528fe9, 5 | BRF_SND}, 		//  5
};

STDROMPICKEXT(bngbeadn, bngbeadn, neogeo);
STD_ROM_FN(bngbeadn);

struct BurnDriver BurnDrvbngbeadn= {
	"bngbeadn", "bangbead", "neogeo", "2000",
	"Bang Bead (decrypted C)\0", "decrypted C-ROMs", "Visco", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, bngbeadnRomInfo, bngbeadnRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Nightmare in the Dark (Decrypted C-ROMs)

static struct BurnRomInfo nitdnRomDesc[] = {
	{ "260-p1.bin",   0x080000, 0x61361082, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "nitdn_c1.rom", 0x800000, 0xf3ff4953, 3 | BRF_GRA }, 		 //  1 Sprite data
	{ "nitdn_c2.rom", 0x800000, 0xf1e49faa, 3 | BRF_GRA }, 		 //  2

	{ "260-m1.bin",   0x080000, 0x6407C5E5, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code

	{ "260-v1.bin",   0x400000, 0x24B0480C, 5 | BRF_SND }, 		 //  4 Sound data
};

STDROMPICKEXT(nitdn, nitdn, neogeo);
STD_ROM_FN(nitdn);

struct BurnDriver BurnDrvnitdn = {
	"nitdn", "nitd", "neogeo", "2000",
	"Nightmare in the Dark (decrypted C)\0", "decrypted C-ROMs", "Eleven / Gavaking", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, nitdnRomInfo, nitdnRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Sengoku 3 (decrypted C-ROMs)

static struct BurnRomInfo sngoku3nRomDesc[] = {
	{ "261-p1.bin",   0x200000, 0xE0D4BC0A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "sen3n_c1.rom", 0x800000, 0x9af7cbca, 3 | BRF_GRA },		 //  1 Sprite data
	{ "sen3n_c2.rom", 0x800000, 0x2a1f874d, 3 | BRF_GRA },		 //  2
	{ "sen3n_c3.rom", 0x800000, 0x5403adb5, 3 | BRF_GRA },		 //  3
	{ "sen3n_c4.rom", 0x800000, 0x18926df6, 3 | BRF_GRA },		 //  4

	{ "261-m1.bin",   0x020000, 0x36ED9CDD, 4 | BRF_ESS | BRF_PRG }, //  5 Z80 code

	{ "261-v1.bin",   0x400000, 0x64C30081, 5 | BRF_SND },		 //  6 Sound data
	{ "261-v2.bin",   0x400000, 0x392A9C47, 5 | BRF_SND },		 //  7
	{ "261-v3.bin",   0x400000, 0xC1A7EBE3, 5 | BRF_SND },		 //  8
	{ "261-v4.bin",   0x200000, 0x9000D085, 5 | BRF_SND },		 //  9
};

STDROMPICKEXT(sngoku3n, sngoku3n, neogeo);
STD_ROM_FN(sngoku3n);

struct BurnDriver BurnDrvsngoku3n = {
	"sngoku3n", "sengoku3", "neogeo", "2001",
	"Sengoku 3\0Sengoku Denshou 2001 (decrypted C)\0", "decrypted C-ROMs", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_SWAPP,
	NULL, sngoku3nRomInfo, sngoku3nRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 (decrypted C-ROMs)

static struct BurnRomInfo kof2k1ndRomDesc[] = {
	{ "262-p1.bin",               0x100000, 0x9381750D, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-p2.bin",               0x400000, 0x8E0D8329, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "kf2k1_c1.rom",             0x800000, 0x103225b1, 3 | BRF_GRA },		//  2 Sprite data
	{ "kf2k1_c2.rom",             0x800000, 0xf9d05d99, 3 | BRF_GRA },		//  3
	{ "kf2k1_c3.rom",             0x800000, 0x4c7ec427, 3 | BRF_GRA },		//  4
	{ "kf2k1_c4.rom",             0x800000, 0x1d237aa6, 3 | BRF_GRA },		//  5
	{ "kf2k1_c5.rom",             0x800000, 0xc2256db5, 3 | BRF_GRA },		//  6
	{ "kf2k1_c6.rom",             0x800000, 0x8d6565a9, 3 | BRF_GRA },		//  7
	{ "kf2k1_c7.rom",             0x800000, 0xd1408776, 3 | BRF_GRA },		//  8
	{ "kf2k1_c8.rom",             0x800000, 0x954d0e16, 3 | BRF_GRA },		//  9

	{ "265-262_decrypted-m1.bin", 0x020000, 0x2FB0A8A5, 4 | BRF_ESS | BRF_PRG },	// 10 Z80 code (decrypted)

	{ "262-v1.bin",               0x400000, 0x83D49ECF, 5 | BRF_SND },		// 11 Sound data
	{ "262-v2.bin",               0x400000, 0x003F1843, 5 | BRF_SND },		// 12
	{ "262-v3.bin",               0x400000, 0x2AE38DBE, 5 | BRF_SND },		// 13
	{ "262-v4.bin",               0x400000, 0x26EC4DD9, 5 | BRF_SND },		// 14
};

STDROMPICKEXT(kof2k1nd, kof2k1nd, neogeo);
STD_ROM_FN(kof2k1nd);

struct BurnDriver BurnDrvkof2k1nd = {
	"kof2k1nd", "kof2001", "neogeo", "2001",
	"The King of Fighters 2001 (decrypted C)\0", "decrypted C-ROMs", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof2k1ndRomInfo, kof2k1ndRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 4 (decrypted C-ROMs)

static struct BurnRomInfo mslug4ndRomDesc[] = {
	{ "263-p1.bin",           0x100000, 0x27E4DEF3, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "263-p2.bin",           0x400000, 0xFDB7AED8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ms4n_c1.rom",          0x800000, 0xa75ffcde, 3 | BRF_GRA },		 //  2 Sprite data
	{ "ms4n_c2.rom",          0x800000, 0x5ab0d12b, 3 | BRF_GRA },		 //  3
	{ "ms4n_c3.rom",          0x800000, 0x61af560c, 3 | BRF_GRA },		 //  4
	{ "ms4n_c4.rom",          0x800000, 0xf2c544fd, 3 | BRF_GRA },		 //  5
	{ "ms4n_c5.rom",          0x800000, 0x84c66c44, 3 | BRF_GRA },		 //  6
	{ "ms4n_c6.rom",          0x800000, 0x5ed018ab, 3 | BRF_GRA },		 //  7

	{ "263-m1_decrypted.bin", 0x010000, 0x0C4C42F8, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "263-v1.bin",           0x800000, 0x01E9B9CD, 5 | BRF_SND },		 //  9 Sound data
	{ "263-v2.bin",           0x800000, 0x4AB2BF81, 5 | BRF_SND },		 // 10
};

STDROMPICKEXT(mslug4nd, mslug4nd, neogeo);
STD_ROM_FN(mslug4nd);

struct BurnDriver BurnDrvmslug4nd = {
	"mslug4nd", "mslug4", "neogeo", "2002",
	"Metal Slug 4 (decrypted C)\0", "decrypted C-ROMs", "Playmore Corporation / Mega Enterprise", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, mslug4ndRomInfo, mslug4ndRomName, neogeoInputInfo, neogeoDIPInfo,
	mslug4Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Rage of the Dragons (decrypted C-ROMs)

static struct BurnRomInfo rotdndRomDesc[] = {
	{ "264-p1.bin",           0x800000, 0xB8CC969D, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "rodn_c1.rom",          0x800000, 0xec9d18c0,	3 | BRF_GRA },		 //  1 Sprite data
	{ "rodn_c2.rom",          0x800000, 0xb1069066,	3 | BRF_GRA },		 //  2
	{ "rodn_c3.rom",          0x800000, 0x7e636d49,	3 | BRF_GRA },		 //  3
	{ "rodn_c4.rom",          0x800000, 0x76892fda,	3 | BRF_GRA },		 //  4
	{ "rodn_c5.rom",          0x800000, 0x469061bc,	3 | BRF_GRA },		 //  5
	{ "rodn_c6.rom",          0x800000, 0x2200220a,	3 | BRF_GRA },		 //  6
	{ "rodn_c7.rom",          0x800000, 0xedda4baf,	3 | BRF_GRA },		 //  7
	{ "rodn_c8.rom",          0x800000, 0x82b1ba22,	3 | BRF_GRA },		 //  8

	{ "264-m1_decrypted.bin", 0x010000, 0x7E06206D, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code (decrypted)

	{ "264-v1.bin",           0x800000, 0xFA005812, 5 | BRF_SND },		 // 10 Sound data
	{ "264-v2.bin",           0x800000, 0xC3DC8BF0, 5 | BRF_SND },		 // 11
};

STDROMPICKEXT(rotdnd, rotdnd, neogeo);
STD_ROM_FN(rotdnd);

struct BurnDriver BurnDrvrotdnd = {
	"rotdnd", "rotd", "neogeo", "2002",
	"Rage of the Dragons (decrypted C)\0", "decrypted C-ROMs", "Evoga / Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, rotdndRomInfo, rotdndRomName, neogeoInputInfo, neogeoDIPInfo,
	rotdInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 (decrypted C-ROMs)

static struct BurnRomInfo kof2k2ndRomDesc[] = {
	{ "265-p1.bin",           0x100000, 0x9EDE7323, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "265-p2.bin",           0x400000, 0x327266b8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "kf2k2_c1.rom",         0x800000, 0x7efa6ef7, 3 | BRF_GRA },		 //  2 Sprite data
	{ "kf2k2_c2.rom",         0x800000, 0xaa82948b, 3 | BRF_GRA },		 //  3
	{ "kf2k2_c3.rom",         0x800000, 0x959fad0B, 3 | BRF_GRA },		 //  4
	{ "kf2k2_c4.rom",         0x800000, 0xefe6a468, 3 | BRF_GRA },		 //  5
	{ "kf2k2_c5.rom",         0x800000, 0x74bba7c6, 3 | BRF_GRA },		 //  6
	{ "kf2k2_c6.rom",         0x800000, 0xe20d2216, 3 | BRF_GRA },		 //  7
	{ "kf2k2_c7.rom",         0x800000, 0x8a5b561c, 3 | BRF_GRA },		 //  8
	{ "kf2k2_c8.rom",         0x800000, 0xbef667a3, 3 | BRF_GRA },		 //  9

	{ "265-m1_decrypted.bin", 0x020000, 0x1C661A4B, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "265-v1.bin",           0x800000, 0x15E8F3F5, 5 | BRF_SND },		 // 11
	{ "265-v2.bin",           0x800000, 0xDA41D6F9, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(kof2k2nd, kof2k2nd, neogeo);
STD_ROM_FN(kof2k2nd);

struct BurnDriver BurnDrvkof2k2nd = {
	"kof2k2nd", "kof2002", "neogeo", "2002",
	"The King of Fighters 2002 - challenge to ultimate battle (decrypted C)\0", "decrypted C-ROMs", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof2k2ndRomInfo, kof2k2ndRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2002Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Matrimelee (decrypted C-ROMs)

static struct BurnRomInfo matrimndRomDesc[] = {
	{ "266-p1.bin",           0x100000, 0x5d4c2dc7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "266-p2.bin",           0x400000, 0xa14b1906, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "matr_c1.rom",          0x800000, 0x0ab54c54, 3 | BRF_GRA },		 //  2 Sprite data
	{ "matr_c2.rom",          0x800000, 0xb834dd89, 3 | BRF_GRA },		 //  3
	{ "matr_c3.rom",          0x800000, 0xf31d68d4, 3 | BRF_GRA },		 //  4
	{ "matr_c4.rom",          0x800000, 0x58cfb6e9, 3 | BRF_GRA },		 //  5
	{ "matr_c5.rom",          0x800000, 0xf3c0e3fd, 3 | BRF_GRA },		 //  6
	{ "matr_c6.rom",          0x800000, 0xb53c8dcf, 3 | BRF_GRA },		 //  7
	{ "matr_c7.rom",          0x800000, 0x3c1fb02a, 3 | BRF_GRA },		 //  8
	{ "matr_c8.rom",          0x800000, 0x5ee31f80, 3 | BRF_GRA },		 //  9

	{ "266-m1_decrypted.bin", 0x020000, 0xd2f3742d, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "266-v1.bin",           0x800000, 0xa4f83690, 5 | BRF_SND },		 // 11
	{ "266-v2.bin",           0x800000, 0xd0f69eda, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(matrimnd, matrimnd, neogeo);
STD_ROM_FN(matrimnd);

struct BurnDriver BurnDrvmatrimnd = {
	"matrimnd", "matrim", "neogeo", "2002",
	"Matrimelee\0Shin gouketsuzi ichizoku - Toukon (decrypted C)\0", "decrypted C-ROMs", "Playmore / Noise Factory / Atlus", "Neo Geo",
	L"\u65B0\u8C6A\u8840\u5BFA\u4E00\u65CF - \u95D8\u5A5A\0Matrimelee (decrypted C)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, matrimndRomInfo, matrimndRomName, neogeoInputInfo, neogeoDIPInfo,
	matrimInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Pochi and Nyaa (decrypted C-ROMs)

static struct BurnRomInfo pnyaanRomDesc[] = {
	{"267-ep1.bin",           0x100000, 0x112fe2c0, 1 | BRF_ESS | BRF_PRG}, //  0 68K code

	{"pnyaa_c1.rom",          0x800000, 0x75fa4f27, 3 | BRF_GRA},		//  1 Sprite data
	{"pnyaa_c2.rom",          0x800000, 0x02345689, 3 | BRF_GRA},		//  2

	{"267-m1_decrypted.bin",  0x080000, 0xd58eaa8e, 4 | BRF_ESS | BRF_PRG}, //  3 Z80 code

	{"267-v1.bin",            0x400000, 0xe2e8e917, 5 | BRF_SND},		//  4 Sound data
};

STDROMPICKEXT(pnyaan, pnyaan, neogeo);
STD_ROM_FN(pnyaan);

struct BurnDriver BurnDrvpnyaan = {
	"pnyaan", "pnyaa", "neogeo", "2003",
	"Pochi and Nyaa (decrypted C)\0", "decrypted C-ROMs", "Aiky", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, pnyaanRomInfo, pnyaanRomName, neogeoInputInfo, neogeoDIPInfo,
	pnyaaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 5 (PCB board, decrypted C-ROMs)

static struct BurnRomInfo ms5pcbnRomDesc[] = {
	{ "268-p1r.bin",           0x400000,  0xd0466792, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "268-p2r.bin",           0x400000,  0xfbf6b61e, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ms5n_c1.rom",           0x1000000, 0x996debed, 3 | BRF_GRA }, 	   //  2 Sprite data
	{ "ms5n_c2.rom",           0x1000000, 0x960a9764, 3 | BRF_GRA }, 	   //  3
	{ "ms5n_c3.rom",           0x1000000, 0xf699994f, 3 | BRF_GRA }, 	   //  4
	{ "ms5n_c4.rom",           0x1000000, 0x49e902e8, 3 | BRF_GRA }, 	   //  5

	{ "268-m1_decrypted.bin",  0x080000,  0x2f621a2b, 4 | BRF_ESS | BRF_PRG }, //  6 Z80 code (decrypted)

	{ "268-v1.bin",            0x1000000, 0x8458afe5, 5 | BRF_SND }, 	   //  7 Sound data
};

STDROMPICKEXT(ms5pcbn, ms5pcbn, PCB268);
STD_ROM_FN(ms5pcbn);

struct BurnDriver BurnDrvms5pcbn = {
	"ms5pcbn", "ms5pcb", NULL, "2003",
	"Metal Slug 5 (JAMMA PCB, decrypted C)\0", "PCB Custom board, decrypted C-ROMs", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_PCB_BIOS,
	NULL, ms5pcbnRomInfo, ms5pcbnRomName, neogeoInputInfo, PCB268DIPInfo,
	ms5pcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 5 (MVS, decrypted C-ROMs)

static struct BurnRomInfo mslug5ndRomDesc[] = {
	{ "268-p1cr.bin",         0x400000, 0xd0466792, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "268-p2cr.bin",         0x400000, 0xfbf6b61e, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ms5n_c1c.rom",         0x800000, 0xe8239365, 3 | BRF_GRA },		 //  2 Sprite data
	{ "ms5n_c2c.rom",         0x800000, 0x89b21d4c, 3 | BRF_GRA },		 //  3
	{ "ms5n_c3c.rom",         0x800000, 0x3cda13a0, 3 | BRF_GRA },		 //  4
	{ "ms5n_c4c.rom",         0x800000, 0x9c00160d, 3 | BRF_GRA },		 //  5
	{ "ms5n_c5c.rom",         0x800000, 0x38754256, 3 | BRF_GRA },		 //  6
	{ "ms5n_c6c.rom",         0x800000, 0x59d33e9c, 3 | BRF_GRA },		 //  7
	{ "ms5n_c7c.rom",         0x800000, 0xc9f8c357, 3 | BRF_GRA },		 //  8
	{ "ms5n_c8c.rom",         0x800000, 0xfafc3eb9, 3 | BRF_GRA },		 //  9

	{ "268-m1_decrypted.bin", 0x080000, 0x2f621a2b, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "268-v1c.bin",          0x800000, 0xae31d60c, 5 | BRF_SND },		 // 11 Sound data
	{ "268-v2c.bin",          0x800000, 0xc40613ed, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(mslug5nd, mslug5nd, neogeo);
STD_ROM_FN(mslug5nd);

struct BurnDriver BurnDrvmslug5nd = {
	"mslug5nd", "mslug5", "neogeo", "2003",
	"Metal Slug 5 (MVS, decrypted C)\0", "MVS Version, decrypted C-ROMs", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, mslug5ndRomInfo, mslug5ndRomName, neogeoInputInfo, neogeoDIPInfo,
	mslug5Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM (PCB board, decrypted C-ROMs)

static struct BurnRomInfo svcpcbnRomDesc[] = {
	{ "269-p1.bin",           0x2000000, 0x432CFDFC, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "svcn_c1.rom",          0x2000000, 0x382ce01f, 3 | BRF_GRA },		  //  1 Sprite data
	{ "svcn_c2.rom",          0x2000000, 0x88ad01ec, 3 | BRF_GRA },		  //  2

	{ "269-m1_decrypted.bin", 0x080000,  0x7b7bf462, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code (decrypted)

	{ "269-v1.bin",           0x800000,  0xc659b34c, 5 | BRF_SND },		  //  4 Sound data
	{ "269-v2.bin",           0x800000,  0xdd903835, 5 | BRF_SND },		  //  5
};

STDROMPICKEXT(svcpcbn, svcpcbn, PCB269);
STD_ROM_FN(svcpcbn);

struct BurnDriver BurnDrvsvcpcbn = {
	"svcpcbn", "svcpcb", NULL, "2003",
	"SvC Chaos - SNK vs CAPCOM (JAMMA PCB, decrypted C)\0", "PCB Custom board / Asia / Japan, decrypted C-ROMs", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_PCB_BIOS,
	NULL, svcpcbnRomInfo, svcpcbnRomName, neogeoInputInfo, PCB269DIPInfo,
	svcpcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM (MVS, decrypted C-ROMs)

static struct BurnRomInfo svcndRomDesc[] = {
	{ "269-p1.bin",           0x400000, 0x38e2005e, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "269-p2.bin",           0x400000, 0x6d13797c, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "svcn_c1r.rom",         0x800000, 0x465d473b, 3 | BRF_GRA },		 //  2 Sprite data
	{ "svcn_c2r.rom",         0x800000, 0x3eb28f78, 3 | BRF_GRA },		 //  3
	{ "svcn_c3r.rom",         0x800000, 0xf4d4ab2b, 3 | BRF_GRA },		 //  4
	{ "svcn_c4r.rom",         0x800000, 0xa69d523a, 3 | BRF_GRA },		 //  5
	{ "svcn_c5r.rom",         0x800000, 0xba2a7892, 3 | BRF_GRA },		 //  6
	{ "svcn_c6r.rom",         0x800000, 0x37371ca1, 3 | BRF_GRA },		 //  7
	{ "svcn_c7r.rom",         0x800000, 0x5595b6cc, 3 | BRF_GRA },		 //  8
	{ "svcn_c8r.rom",         0x800000, 0xb17dfcf9, 3 | BRF_GRA },		 //  9

	{ "269-m1_decrypted.bin", 0x080000, 0x7b7bf462, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code

	{ "269-v1.bin",           0x800000, 0xc659b34c, 5 | BRF_SND },		 // 11 Sound data
	{ "269-v2.bin",           0x800000, 0xdd903835, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(svcnd, svcnd, neogeo);
STD_ROM_FN(svcnd);

struct BurnDriver BurnDrvsvcnd = {
	"svcnd", "svcchaos", "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM (MVS, decrypted C)\0", "MVS, decrypted C-ROMs", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, svcndRomInfo, svcndRomName, neogeoInputInfo, neogeoDIPInfo,
	svcchaosInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V (decrypted C-ROMs)

static struct BurnRomInfo samsh5ndRomDesc[] = {
	{ "270-p1.bin",           0x400000, 0x4a2a09e6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "270-p2.bin",           0x400000, 0xe0c74c85, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ss5n_c1.rom",          0x800000, 0x9adec562, 3 | BRF_GRA },		 //  2 Sprite data
	{ "ss5n_c2.rom",          0x800000, 0xac0309e5, 3 | BRF_GRA },		 //  3
	{ "ss5n_c3.rom",          0x800000, 0x82db9dae, 3 | BRF_GRA },		 //  4
	{ "ss5n_c4.rom",          0x800000, 0xf8041153, 3 | BRF_GRA },		 //  5
	{ "ss5n_c5.rom",          0x800000, 0xe689d62d, 3 | BRF_GRA },		 //  6
	{ "ss5n_c6.rom",          0x800000, 0xa993bdcf, 3 | BRF_GRA },		 //  7
	{ "ss5n_c7.rom",          0x800000, 0x707d56a0, 3 | BRF_GRA },		 //  8
	{ "ss5n_c8.rom",          0x800000, 0xf5903adc, 3 | BRF_GRA },		 //  9

	{ "270-m1_decrypted.bin", 0x080000, 0x65495887, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "270-v1.bin",           0x800000, 0x62e434eb, 5 | BRF_SND },		 // 11
	{ "270-v2.bin",           0x800000, 0x180f3c9a, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(samsh5nd, samsh5nd, neogeo);
STD_ROM_FN(samsh5nd);

struct BurnDriver BurnDrvSamSh5nd = {
	"samsh5nd", "samsho5", "neogeo", "2003",
	"Samurai Shodown V\0Samurai Spirits Zero (decrypted C)\0", "decrypted C-ROMs", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING  | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, samsh5ndRomInfo, samsh5ndRomName, neogeoInputInfo, neogeoDIPInfo,
	samsho5Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2003 (PCB board, decrypted C-ROMs)

static struct BurnRomInfo kf2k3pcnRomDesc[] = {
	{ "271-p1.bin",           0x400000,  0xb9da070c, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "271-p2.bin",           0x400000,  0xda3118c4, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "271-p3.bin",           0x100000,  0x5cefd0d2, 1 | BRF_PRG | BRF_OPT }, //  2

	{ "kf2k3_c1.rom",         0x1000000, 0xc29acd28, 3 | BRF_GRA },		  //  3 Sprite data
	{ "kf2k3_c2.rom",         0x1000000, 0x328e80b1, 3 | BRF_GRA },		  //  4
	{ "kf2k3_c3.rom",         0x1000000, 0x020a11f1, 3 | BRF_GRA },		  //  5
	{ "kf2k3_c4.rom",         0x1000000, 0x991b5ed2, 3 | BRF_GRA },		  //  6
	{ "kf2k3_c5.rom",         0x1000000, 0xc2de8b66, 3 | BRF_GRA },		  //  7
	{ "kf2k3_c6.rom",         0x1000000, 0x3ff750db, 3 | BRF_GRA },		  //  8

	{ "271-m1_decrypted.bin", 0x080000,  0x0e86af8f, 4 | BRF_ESS | BRF_PRG }, //  9  Z80 code

	{ "271-v1.bin" ,          0x1000000, 0x1d96154b, 5 | BRF_SND },		  // 10 Sound data
};

STDROMPICKEXT(kf2k3pcn, kf2k3pcn, PCB271);
STD_ROM_FN(kf2k3pcn);

struct BurnDriver BurnDrvkf2k3pcn = {
	"kf2k3pcn", "kf2k3pcb", NULL, "2003",
	"The King of Fighters 2003 (JAMMA PCB, decrypted C)\0", "PCB Custom board / Japan, decrypted C-ROMs", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT | HARDWARE_SNK_PCB_BIOS,
	NULL, kf2k3pcnRomInfo, kf2k3pcnRomName, neogeoInputInfo, PCB271DIPInfo,
	kf2k3pcbInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2003 (MVS Cart, decrypted C-ROMs)

static struct BurnRomInfo kof2k3ndRomDesc[] = {
	{ "271-p1c.bin",           0x400000, 0x530ecc14,  1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "271-p2c.bin",           0x400000, 0xfd568da9,  1 | BRF_ESS | BRF_PRG }, //  1
	{ "271-p3c.bin",           0x100000, 0xaec5b4a9,  1 | BRF_PRG | BRF_OPT }, //  2

	{ "kf2k3_c1c.rom",         0x800000, 0xe42fc226,  3 | BRF_GRA },	   //  3 Sprite data
	{ "kf2k3_c2c.rom",         0x800000, 0x1b5e3b58,  3 | BRF_GRA },	   //  4
	{ "kf2k3_c3c.rom",         0x800000, 0xd334fdd9,  3 | BRF_GRA },	   //  5
	{ "kf2k3_c4c.rom",         0x800000, 0x0d457699,  3 | BRF_GRA },	   //  6
	{ "kf2k3_c5c.rom",         0x800000, 0x8a91aae4,  3 | BRF_GRA },	   //  7
	{ "kf2k3_c6c.rom",         0x800000, 0x9f8674b8,  3 | BRF_GRA },	   //  8
	{ "kf2k3_c7c.rom",         0x800000, 0x8ee6b43c,  3 | BRF_GRA },	   //  9
	{ "kf2k3_c8c.rom",         0x800000, 0x6d8d2d60,  3 | BRF_GRA },	   // 10

	{ "271-m1c_decrypted.bin", 0x080000, 0x4374cb5c,  4 | BRF_ESS | BRF_PRG }, // 11  Z80 code

	{ "271-v1c.bin",           0x800000, 0xffa3f8c7,  5 | BRF_SND },	   // 12 Sound data
	{ "271-v2c.bin",           0x800000, 0x5382c7d1,  5 | BRF_SND },	   // 13
};

STDROMPICKEXT(kof2k3nd, kof2k3nd, neogeo);
STD_ROM_FN(kof2k3nd);

struct BurnDriver BurnDrvkof2k3nd = {
	"kof2k3nd", "kof2003", "neogeo", "2003",
	"The King of Fighters 2003 (MVS, decrypted C)\0", "MVS Version, decrypted C-ROMs", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, kof2k3ndRomInfo, kof2k3ndRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2003Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V Special (Decrypted C-ROMs)

static struct BurnRomInfo ss5spndRomDesc[] = {
	{ "272-p1.bin",           0x400000, 0xfb7a6bba, 1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "272-p2.bin",           0x400000, 0x63492ea6, 1 | BRF_ESS | BRF_PRG }, // 1

	{ "ss5s_c1.rom",          0x800000, 0x8548097E, 3 | BRF_GRA },		 // 2 Sprite data
	{ "ss5s_c2.rom",          0x800000, 0x8C1B48D0, 3 | BRF_GRA },		 // 3
	{ "ss5s_c3.rom",          0x800000, 0x96DDB28C, 3 | BRF_GRA },		 // 4
	{ "ss5s_c4.rom",          0x800000, 0x99EF7A0A, 3 | BRF_GRA },		 // 5
	{ "ss5s_c5.rom",          0x800000, 0x772E8B1E, 3 | BRF_GRA },		 // 6
	{ "ss5s_c6.rom",          0x800000, 0x5FFF21FC, 3 | BRF_GRA },		 // 7
	{ "ss5s_c7.rom",          0x800000, 0x9AC56A0E, 3 | BRF_GRA },		 // 8
	{ "ss5s_c8.rom",          0x800000, 0xCFDE7AFF, 3 | BRF_GRA },		 // 9

	{ "272-m1_decrypted.bin", 0x080000, 0x203d744e, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (decrypted)

	{ "272-v1.bin",           0x800000, 0x76A94127, 5 | BRF_SND },		 // 11 Sound data
	{ "272-v2.bin",           0x800000, 0x4BA507F1, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(ss5spnd, ss5spnd, neogeo);
STD_ROM_FN(ss5spnd);

struct BurnDriver BurnDrvss5spnd = {
	"ss5spnd", "samsh5sp", "neogeo", "2004",
	"Samurai Shodown V Special\0Samurai Spirits Zero Special (decrypted C)\0", "decrypted C-ROMs", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, ss5spndRomInfo, ss5spndRomName, neogeoInputInfo, neogeoDIPInfo,
	samsh5spInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};


// ----------------------------------------------------------------------------
// Hacks / bootlegs


// Zintrick (hacked Neo CD version)

static struct BurnRomInfo zintrckbRomDesc[] = {
	{ "zin_p1.rom",   0x100000, 0x06C8FCA7, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "zin_s1.rom",   0x020000, 0xA7AB0E81, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "zin_c1.rom",   0x200000, 0x76AEE189, 3 | BRF_GRA },		 //  2 Sprite data
	{ "zin_c2.rom",   0x200000, 0x844ED4B3, 3 | BRF_GRA },		 //  3

	{ "zin_m1.rom",   0x020000, 0xFD9627CA, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "zin_v1.rom",   0x200000, 0xC09F74F1, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(zintrckb, zintrckb, neogeo);
STD_ROM_FN(zintrckb);

struct BurnDriver BurnDrvzintrckb = {
	"zintrckb", NULL, "neogeo", "1996",
	"Zintrick\0Oshidashi Zentri (set 1)\0", "Hacked Neo CD version (fake prototype)", "ADK / SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, zintrckbRomInfo, zintrckbRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Zintrick (hacked Neo CD version)

static struct BurnRomInfo zintrkcdRomDesc[] = {
	{ "211-p1.bin",   0x100000, 0x9A0BFE0A, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "211-s1.bin",   0x020000, 0x56D16AFA, 2 | BRF_GRA },		 //  1 Text layer tiles

	{ "zin_c1.rom",   0x200000, 0x76AEE189, 3 | BRF_GRA },		 //  2 Sprite data
	{ "zin_c2.rom",   0x200000, 0x844ED4B3, 3 | BRF_GRA },		 //  3

	{ "211-m1.bin",   0x010000, 0xFCAE1407, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code

	{ "211-v1.bin",   0x100000, 0x781439DA, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(zintrkcd, zintrkcd, neogeo);
STD_ROM_FN(zintrkcd);

struct BurnDriver BurnDrvzintrkcd = {
	"zintrkcd", "zintrckb", "neogeo", "1996",
	"Zintrick\0Oshidashi Zentri (set 2)\0", "Hacked Neo CD version (Razoola's convertion)", "ADK / SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, zintrkcdRomInfo, zintrkcdRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '96 Plus (bootleg / hack)

static struct BurnRomInfo kof96plsRomDesc[] = {
	{ "214-p1.bin",        0x100000, 0x52755d74, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "214-p2.bin",        0x200000, 0x002ccb73, 1 | BRF_ESS | BRF_PRG },	//  1
	{ "kof96m_ep1.rom",    0x080000, 0xe5f2fb43, 1 | BRF_ESS | BRF_PRG },	//  2 68K code patch

	{ "214-s1.bin",        0x020000, 0x1254cbdb, 2 | BRF_GRA },		//  3 Text layer tiles

	{ "214-c1.bin",        0x400000, 0x7ecf4aa2, 3 | BRF_GRA },		//  4 Sprite data
	{ "214-c2.bin",        0x400000, 0x05b54f37, 3 | BRF_GRA },		//  5
	{ "214-c3.bin",        0x400000, 0x64989a65, 3 | BRF_GRA },		//  6
	{ "214-c4.bin",        0x400000, 0xafbea515, 3 | BRF_GRA },		//  7
	{ "214-c5.bin",        0x400000, 0x2a3bbd26, 3 | BRF_GRA },		//  8
	{ "214-c6.bin",        0x400000, 0x44d30dc7, 3 | BRF_GRA },		//  9
	{ "214-c7.bin",        0x400000, 0x3687331b, 3 | BRF_GRA },		// 10
	{ "214-c8.bin",        0x400000, 0xfa1461ad, 3 | BRF_GRA },		// 11

	{ "214-m1.bin",        0x020000, 0xdabc427c, 4 | BRF_ESS | BRF_PRG },	// 12 Z80 code

	{ "214-v1.bin",        0x400000, 0x63f7b045, 5 | BRF_SND },		// 13 Sound data
	{ "214-v2.bin",        0x400000, 0x25929059, 5 | BRF_SND },		// 14
	{ "214-v3.bin",        0x200000, 0x92a2257d, 5 | BRF_SND },		// 15
};

STDROMPICKEXT(kof96pls, kof96pls, neogeo);
STD_ROM_FN(kof96pls);

static int kof96plsInit()
{
	pNeoInitCallback = kof96plsDecrypt;
 	return NeoInit();
}

struct BurnDriver BurnDrvkof96pls = {
	"kof96pls", "kof96", "neogeo", "1996",
	"The King of Fighters '96 Plus\0", "Hack of \"The King of Fighters '96\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof96plsRomInfo, kof96plsRomName, neogeoInputInfo, neogeoDIPInfo,
	kof96plsInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '97 Plus (bootleg / hack, set 1)

static struct BurnRomInfo kof97plsRomDesc[] = {
	{ "232-p1p.bin",  0x100000, 0xC01FDA46, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "232-p2p.bin",  0x400000, 0x5502B020, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "232-s1p.bin",  0x020000, 0x73254270, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "232-c1.bin",   0x800000, 0x5F8BF0A1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "232-c2.bin",   0x800000, 0xE4D45C81, 3 | BRF_GRA },		 //  4
	{ "232-c3.bin",   0x800000, 0x581D6618, 3 | BRF_GRA },		 //  5
	{ "232-c4.bin",   0x800000, 0x49BB1E68, 3 | BRF_GRA },		 //  6
	{ "232-c5.bin",   0x400000, 0x34fC4E51, 3 | BRF_GRA },		 //  7
	{ "232-c6.bin",   0x400000, 0x4FF4D47B, 3 | BRF_GRA },		 //  8

	{ "232-m1.bin",   0x020000, 0x45348747, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "232-v1.bin",   0x400000, 0x22A2B5B5, 5 | BRF_SND },		 // 10 Sound data
	{ "232-v2.bin",   0x400000, 0x2304E744, 5 | BRF_SND },		 // 11
	{ "232-v3.bin",   0x400000, 0x759EB954, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(kof97pls, kof97pls, neogeo);
STD_ROM_FN(kof97pls);

struct BurnDriver BurnDrvKof97p = {
	"kof97pls", "kof97", "neogeo", "1997",
	"The King of Fighters '97 Plus (set 1)\0", "Hack of \"The King of Fighters '97\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof97plsRomInfo, kof97plsRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters '97 Plus (bootleg / hack, set 2)

static struct BurnRomInfo kf97plsaRomDesc[] = {
	{ "232-p1pa.bin", 0x100000, 0xD5D92967, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "232-p2.bin",   0x400000, 0x158B23F6, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "232-s1pa.bin", 0x020000, 0x4EE2149A, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "232-c1.bin",   0x800000, 0x5F8BF0A1, 3 | BRF_GRA },		 //  3 Sprite data
	{ "232-c2.bin",   0x800000, 0xE4D45C81, 3 | BRF_GRA },		 //  4
	{ "232-c3.bin",   0x800000, 0x581D6618, 3 | BRF_GRA },		 //  5
	{ "232-c4.bin",   0x800000, 0x49BB1E68, 3 | BRF_GRA },		 //  6
	{ "232-c5.bin",   0x400000, 0x34fC4E51, 3 | BRF_GRA },		 //  7
	{ "232-c6.bin",   0x400000, 0x4FF4D47B, 3 | BRF_GRA },		 //  8

	{ "232-m1.bin",   0x020000, 0x45348747, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "232-v1.bin",   0x400000, 0x22A2B5B5, 5 | BRF_SND },		 // 10 Sound data
	{ "232-v2.bin",   0x400000, 0x2304E744, 5 | BRF_SND },		 // 11
	{ "232-v3.bin",   0x400000, 0x759EB954, 5 | BRF_SND },		 // 12
};

STDROMPICKEXT(kf97plsa, kf97plsa, neogeo);
STD_ROM_FN(kf97plsa);

static int kf97plsaInit()
{
	nNeoTextROMFixType = 3;
	return NeoInit();
}

struct BurnDriver BurnDrvKof97pl = {
	"kf97plsa", "kof97", "neogeo", "1997",
	"The King of Fighters '97 Plus (set 2)\0", "Alternate hack of \"The King of Fighters '97\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf97plsaRomInfo, kf97plsaRomName, neogeoInputInfo, neogeoDIPInfo,
	kf97plsaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Gladiator (bootleg / hack)

static struct BurnRomInfo kogRomDesc[] = {
	{ "5232-p1.bin",   0x200000, 0xd2413ec6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "232-p2.bin",    0x400000, 0x158b23f6, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "5232-s1.bin",   0x020000, 0x0bef69da, 2 | BRF_GRA },		  //  2 Text layer tiles

	// This is either bad dumped or bad emulated
	{ "5232-c1a.bin",  0x800000, 0x4eab9b0a, 3 | BRF_GRA },		  //  3 Sprite data
	{ "5232-c2a.bin",  0x800000, 0x697f8fd0, 3 | BRF_GRA },		  //  4
	{ "5232-c1b.bin",  0x800000, 0x1143fdf3, 3 | BRF_GRA },		  //  5
	{ "5232-c2b.bin",  0x800000, 0xea82cf8f, 3 | BRF_GRA },		  //  6
	{ "5232-c3.bin",   0x400000, 0xabd1be07, 3 | BRF_GRA },		  //  7
	{ "5232-c4.bin",   0x400000, 0xd2bd967b, 3 | BRF_GRA },		  //  8

	{ "232-m1.bin",    0x020000, 0x45348747, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "232-v1.bin",    0x400000, 0x22a2b5b5, 5 | BRF_SND },		  // 10 Sound data
	{ "232-v2.bin",    0x400000, 0x2304e744, 5 | BRF_SND },		  // 11
	{ "232-v3.bin",    0x400000, 0x759eb954, 5 | BRF_SND },		  // 12
};

STDROMPICKEXT(kog, kog, neogeo);
STD_ROM_FN(kog);

static int kogInit()
{
	pNeoInitCallback = kogDecrypt;
	pNeoProtectionCallback = kogProtectionInstall;
	nNeoTextROMFixType = 3;
	return NeoInit();
}

struct BurnDriver BurnDrvKog = {
	"kog", "kof97", "neogeo", "2005",
	"King of Gladiator\0", "Hack of \"The King of Fighters '97\", Some GFX Missing", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kogRomInfo, kogRomName, neogeoInputInfo, neogeoDIPInfo,
	kogInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Lansquenet 2004 (bootleg / hack)

static struct BurnRomInfo lans2004RomDesc[] = {
	{ "lnsq-p1.bin",  0x200000, 0xb40a879a,    1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "lnsq-p21.bin", 0x200000, 0xecdb2d42,    1 | BRF_ESS | BRF_PRG },	//  1
	{ "lnsq-p22.bin", 0x200000, 0xfac5e2e7,    1 | BRF_ESS | BRF_PRG },	//  2

	{ "lnsq-s1.bin",  0x020000, 0x39e82897,    2 | BRF_GRA },		//  3 Text data

	{ "lnsq-c1.bin",  0x800000, 0xb83de59f,    3 | BRF_GRA },		//  4 Sprite data
	{ "lnsq-c2.bin",  0x800000, 0xe08969fd,    3 | BRF_GRA },		//  5
	{ "lnsq-c3.bin",  0x800000, 0x013f2cda,    3 | BRF_GRA },		//  6
	{ "lnsq-c4.bin",  0x800000, 0xd8c3a758,    3 | BRF_GRA },		//  7
	{ "lnsq-c5.bin",  0x800000, 0x75500b82,    3 | BRF_GRA },		//  8
	{ "lnsq-c6.bin",  0x800000, 0x670ac13b,    3 | BRF_GRA },		//  9

	{ "246-m1.bin",   0x020000, 0xd0604ad1,    4 | BRF_ESS | BRF_PRG },	//  10 Z80 code

	{ "lnsq-v1.bin",  0x400000, 0x4408ebc3,    5 | BRF_SND },		//  11 Sound data
	{ "lnsq-v2.bin",  0x400000, 0x3d953975,    5 | BRF_SND },		//  12
	{ "lnsq-v3.bin",  0x200000, 0x437d1d8e,    5 | BRF_SND },		//  13
};

STDROMPICKEXT(lans2004, lans2004, neogeo);
STD_ROM_FN(lans2004);

static int lans2004Init()
{
	pNeoInitCallback = lans2004Decrypt;
	nNeoTextROMFixType = 3;
	nNeoBootlegSoundProtection = 3;
	return NeoInit();
}

struct BurnDriver BurnDrvlans2004 = {
	"lans2004", "shocktr2", "neogeo", "2004",
	"Lansquenet 2004\0", "Hack of \"Shock Troopers 2\"", "Saurus", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, lans2004RomInfo, lans2004RomName, neogeoInputInfo, neogeoDIPInfo,
	lans2004Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 (bootleg / hack)

static struct BurnRomInfo kof2k1blRomDesc[] = {
	{ "262-p1.bin",    0x100000, 0x9381750d, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-p2bl.bin",  0x400000, 0xc01720aa, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "262-s1bl.bin",  0x020000, 0xde828076, 2 | BRF_GRA },			//  2 Text data

	{ "262-c1bl.bin",  0x800000, 0xf298b87b, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "kf2k1_c2.rom",  0x800000, 0xf9d05d99, 3 | BRF_GRA }, 		//  4
	{ "kf2k1_c3.rom",  0x800000, 0x4c7ec427, 3 | BRF_GRA }, 		//  5
	{ "kf2k1_c4.rom",  0x800000, 0x1d237aa6, 3 | BRF_GRA }, 		//  6
	{ "kf2k1_c5.rom",  0x800000, 0xc2256db5, 3 | BRF_GRA }, 		//  7
	{ "kf2k1_c6.rom",  0x800000, 0x8d6565a9, 3 | BRF_GRA }, 		//  8
	{ "262-c7bl.bin",  0x800000, 0xef682ed2, 3 | BRF_GRA }, 		//  9
	{ "kf2k1_c8.rom",  0x800000, 0x954d0e16, 3 | BRF_GRA }, 		// 10

	{ "262-m1bl.bin",  0x020000, 0x73c1f5b0, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code

	// same as kof2001
	{ "262-v1.bin",    0x400000, 0x83d49ecf, 5 | BRF_SND }, 		// 12 Sound data
	{ "262-v2.bin",    0x400000, 0x003f1843, 5 | BRF_SND }, 		// 13
	{ "262-v3.bin",    0x400000, 0x2ae38dbe, 5 | BRF_SND }, 		// 14
	{ "262-v4.bin",    0x400000, 0x26ec4dd9, 5 | BRF_SND }, 		// 15
};

STDROMPICKEXT(kof2k1bl, kof2k1bl, neogeo);
STD_ROM_FN(kof2k1bl);

struct BurnDriver BurnDrvkof2k1bl = {
	"kof2k1bl", NULL, "neogeo", "2001",
	"The King of Fighters 2001 (bootleg)\0", "Bootleg of \"The King of Fighters 2001\"", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof2k1blRomInfo, kof2k1blRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 Plus (bootleg / hack, set 1)

static struct BurnRomInfo kf2k1plsRomDesc[] = {
	// Confirmed that uses P2 ROM from AES version...
	{ "262-p1p.bin",   0x100000, 0x758529a7, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-pg2.bin",   0x400000, 0x91eea062, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "262-s1p.bin",   0x020000, 0x088657e6, 2 | BRF_GRA }, 		//  2 Text data

	// Does the sprite data should come from decrypted AES version?
	{ "262-c1bl.bin",  0x800000, 0xf298b87b, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "kf2k1_c2.rom",  0x800000, 0xf9d05d99, 3 | BRF_GRA }, 		//  4
	{ "kf2k1_c3.rom",  0x800000, 0x4c7ec427, 3 | BRF_GRA }, 		//  5
	{ "kf2k1_c4.rom",  0x800000, 0x1d237aa6, 3 | BRF_GRA }, 		//  6
	{ "kf2k1_c5.rom",  0x800000, 0xc2256db5, 3 | BRF_GRA }, 		//  7
	{ "kf2k1_c6.rom",  0x800000, 0x8d6565a9, 3 | BRF_GRA }, 		//  8
	{ "262-c7bl.bin",  0x800000, 0xef682ed2, 3 | BRF_GRA }, 		//  9
	{ "kf2k1_c8.rom",  0x800000, 0x954d0e16, 3 | BRF_GRA }, 		// 10

	{ "262-m1bl.bin",  0x020000, 0x73c1f5b0, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code

	{ "262-v1.bin",    0x400000, 0x83d49ecf, 5 | BRF_SND }, 		// 12 Sound data
	{ "262-v2.bin",    0x400000, 0x003f1843, 5 | BRF_SND }, 		// 13
	{ "262-v3.bin",    0x400000, 0x2ae38dbe, 5 | BRF_SND }, 		// 14
	{ "262-v4.bin",    0x400000, 0x26ec4dd9, 5 | BRF_SND }, 		// 15
};

STDROMPICKEXT(kf2k1pls, kf2k1pls, neogeo);
STD_ROM_FN(kf2k1pls);

struct BurnDriver BurnDrvkf2k1pls = {
	"kf2k1pls", "kof2k1bl", "neogeo", "2001",
	"The King of Fighters 2001 Plus (set 1)\0", "Hack of \"The King of Fighters 2001\"", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k1plsRomInfo, kf2k1plsRomName, neogeoInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2001 Plus (bootleg / hack, set 2)

static struct BurnRomInfo kf2k1plaRomDesc[] = {
	// Confirmed that uses P2 ROM from AES version...
	{ "262-p1pa.bin",  0x100000, 0xf8a71b6f, 1 | BRF_ESS | BRF_PRG },	//  0 68K code
	{ "262-pg2.bin",   0x400000, 0x91eea062, 1 | BRF_ESS | BRF_PRG },	//  1

	{ "2k1-s1pa.bin",  0x020000, 0x50986eeb, 2 | BRF_GRA }, 		//  2 Text data

	// Does the sprite data should come from decrypted AES version?
	{ "262-c1bl.bin",  0x800000, 0xf298b87b, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "kf2k1_c2.rom",  0x800000, 0xf9d05d99, 3 | BRF_GRA }, 		//  4
	{ "kf2k1_c3.rom",  0x800000, 0x4c7ec427, 3 | BRF_GRA }, 		//  5
	{ "kf2k1_c4.rom",  0x800000, 0x1d237aa6, 3 | BRF_GRA }, 		//  6
	{ "kf2k1_c5.rom",  0x800000, 0xc2256db5, 3 | BRF_GRA }, 		//  7
	{ "kf2k1_c6.rom",  0x800000, 0x8d6565a9, 3 | BRF_GRA }, 		//  8
	{ "262-c7bl.bin",  0x800000, 0xef682ed2, 3 | BRF_GRA }, 		//  9
	{ "kf2k1_c8.rom",  0x800000, 0x954d0e16, 3 | BRF_GRA }, 		// 10

	{ "262-m1bl.bin",  0x020000, 0x73c1f5b0, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code

	{ "262-v1.bin",    0x400000, 0x83d49ecf, 5 | BRF_SND }, 		// 12 Sound data
	{ "262-v2.bin",    0x400000, 0x003f1843, 5 | BRF_SND }, 		// 13
	{ "262-v3.bin",    0x400000, 0x2ae38dbe, 5 | BRF_SND }, 		// 14
	{ "262-v4.bin",    0x400000, 0x26ec4dd9, 5 | BRF_SND }, 		// 15
};

STDROMPICKEXT(kf2k1pla, kf2k1pla, neogeo);
STD_ROM_FN(kf2k1pla);

static int kf2k1plaInit()
{
	nNeoTextROMFixType = 1;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k1pla = {
	"kf2k1pla", "kof2k1bl", "neogeo", "2001",
	"The King of Fighters 2001 Plus (set 2)\0", "Alternate hack of \"The King of Fighters 2001\"", "SNK / Eolith", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k1plaRomInfo, kf2k1plaRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k1plaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Crouching Tiger Hidden Dragon 2003 (bootleg / hack, set 1)

static struct BurnRomInfo cthd2003RomDesc[] = {
	{ "5003-p1.bin",  0x100000, 0xBB7602C1, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "5003-p2.bin",  0x400000, 0xADC1C22B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "5003-s1.bin",  0x020000, 0x5BA29AAB, 2 | BRF_GRA },		 //  2 Text layer tiles

	{ "5003-c1.bin",  0x800000, 0x68F54B67, 3 | BRF_GRA },		 //  3 Sprite data
	{ "5003-c2.bin",  0x800000, 0x2F8849D5, 3 | BRF_GRA },		 //  4
	{ "5003-c3.bin",  0x800000, 0xAC4AFF71, 3 | BRF_GRA },		 //  5
	{ "5003-c4.bin",  0x800000, 0xAFEF5D66, 3 | BRF_GRA },		 //  6
	{ "5003-c5.bin",  0x800000, 0xC7C1AE50, 3 | BRF_GRA },		 //  7
	{ "5003-c6.bin",  0x800000, 0x613197F9, 3 | BRF_GRA },		 //  8
	{ "5003-c7.bin",  0x800000, 0x64DDFE0F, 3 | BRF_GRA },		 //  9
	{ "5003-c8.bin",  0x800000, 0x917A1439, 3 | BRF_GRA },		 // 10

	{ "5003-m1.bin",  0x020000, 0x1A8C274B, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	// Identical to kof2001
	{ "262-v1.bin",   0x400000, 0x83D49ECF, 5 | BRF_SND },		 // 12 Sound data
	{ "262-v2.bin",   0x400000, 0x003F1843, 5 | BRF_SND },		 // 13
	{ "262-v3.bin",   0x400000, 0x2AE38DBE, 5 | BRF_SND },		 // 14
	{ "262-v4.bin",   0x400000, 0x26EC4DD9, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(cthd2003, cthd2003, neogeo);
STD_ROM_FN(cthd2003);

static int cthd2003Init()
{
	nNeoTextROMFixType = 4;
	pNeoInitCallback = cthd2003Decrypt;
	pNeoBankswitchCallback = cthd2003MapBank;
	pNeoProtectionCallback = cthd2003ProtectionInstall;
	nBurnCPUSpeedAdjust = 0x10D; // Fix issues in the character selection screen
	return NeoInit();
}

struct BurnDriver BurnDrvcthd2003 = {
	"cthd2003", NULL, "neogeo", "2003",
	"Crouching Tiger Hidden Dragon 2003 (set 1)\0", "Hack of \"The King of Fighters 2001\"", "Phenixsoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, cthd2003RomInfo, cthd2003RomName, neogeoInputInfo, neogeoDIPInfo,
	cthd2003Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Crouching Tiger Hidden Dragon 2003 (bootleg / hack, set 2)

static struct BurnRomInfo cthd2k3aRomDesc[] = {
	{ "5003-p1a.bin",  0x100000, 0x83783954, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (unprotected)
	{ "5003-p2a.bin",  0x400000, 0x84B0B164, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "5003-s1a.bin",  0x020000, 0x174CCFFD, 2 | BRF_GRA },		  //  2 Text layer tiles

	{ "5003-c1a.bin",  0x800000, 0xDC90C563, 3 | BRF_GRA },		  //  3 Sprite data
	{ "5003-c2a.bin",  0x800000, 0x7B08D331, 3 | BRF_GRA },		  //  4
	{ "5003-c3.bin",   0x800000, 0xAC4AFF71, 3 | BRF_GRA },		  //  5
	{ "5003-c4.bin",   0x800000, 0xAFEF5D66, 3 | BRF_GRA },		  //  6
	{ "5003-c5.bin",   0x800000, 0xC7C1AE50, 3 | BRF_GRA },		  //  7
	{ "5003-c6.bin",   0x800000, 0x613197F9, 3 | BRF_GRA },		  //  8
	{ "5003-c7a.bin",  0x800000, 0xAD2D72B3, 3 | BRF_GRA },		  //  9
	{ "5003-c8a.bin",  0x800000, 0x8C3FC1B5, 3 | BRF_GRA },		  // 10

	{ "5003-m1a.bin",  0x020000, 0xA37CC447, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "262-v1.bin",    0x400000, 0x83D49ECF, 5 | BRF_SND },		  // 12 Sound data
	{ "5003-v2.bin",   0x400000, 0x2B498449, 5 | BRF_SND },		  // 13
	{ "262-v3.bin",    0x400000, 0x2AE38DBE, 5 | BRF_SND },		  // 14
	{ "262-v4.bin",    0x400000, 0x26EC4DD9, 5 | BRF_SND },		  // 15
};

STDROMPICKEXT(cthd2k3a, cthd2k3a, neogeo);
STD_ROM_FN(cthd2k3a);

static int cthd2k3aInit()
{
	nNeoTextROMFixType = 4;
	pNeoInitCallback = cthd2k3aDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvcthd2k3a = {
	"cthd2k3a", "cthd2003", "neogeo", "2003",
	"Crouching Tiger Hidden Dragon 2003 (set 2)\0", "Alternate hack of \"The King of Fighters 2001\"", "Phenixsoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, cthd2k3aRomInfo, cthd2k3aRomName, neogeoInputInfo, neogeoDIPInfo,
	cthd2k3aInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Crouching Tiger Hidden Dragon 2003 Super Plus (bootleg / hack)

static struct BurnRomInfo ct2k3spRomDesc[] = {
	{ "5003-p1sp.bin",  0x100000, 0xAB5C4DE0, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "5003-p2.bin",    0x400000, 0xADC1C22B, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "5003-s1sp.bin",  0x040000, 0x6C355AB4, 2 | BRF_GRA },	   //  2 Text layer tiles

	{ "5003-c1.bin",    0x800000, 0x68F54B67, 3 | BRF_GRA },	   //  3 Sprite data
	{ "5003-c2.bin",    0x800000, 0x2F8849D5, 3 | BRF_GRA },	   //  4
	{ "5003-c3.bin",    0x800000, 0xAC4AFF71, 3 | BRF_GRA },	   //  5
	{ "5003-c4.bin",    0x800000, 0xAFEF5D66, 3 | BRF_GRA },	   //  6
	{ "5003-c5.bin",    0x800000, 0xC7C1AE50, 3 | BRF_GRA },	   //  7
	{ "5003-c6.bin",    0x800000, 0x613197F9, 3 | BRF_GRA },	   //  8
	{ "5003-c7.bin",    0x800000, 0x64DDFE0F, 3 | BRF_GRA },	   //  9
	{ "5003-c8.bin",    0x800000, 0x917A1439, 3 | BRF_GRA },	   // 10

	{ "5003-m1.bin",    0x020000, 0x1A8C274B, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "262-v1.bin",     0x400000, 0x83D49ECF, 5 | BRF_SND },	   // 12 Sound data
	{ "262-v2.bin",     0x400000, 0x003F1843, 5 | BRF_SND },	   // 13
	{ "262-v3.bin",     0x400000, 0x2AE38DBE, 5 | BRF_SND },	   // 14
	{ "262-v4.bin",     0x400000, 0x26EC4DD9, 5 | BRF_SND },	   // 15
};

STDROMPICKEXT(ct2k3sp, ct2k3sp, neogeo);
STD_ROM_FN(ct2k3sp);

static int ct2k3spInit()
{
	nNeoTextROMFixType = 5;
	pNeoInitCallback = cthd2003Decrypt;
	pNeoBankswitchCallback = cthd2003MapBank;
	pNeoProtectionCallback = cthd2003ProtectionInstall;
	nBurnCPUSpeedAdjust = 0x10D; // Fix issues in the character selection screen
	return NeoInit();
}

struct BurnDriver BurnDrvct2k3sp = {
	"ct2k3sp", "cthd2003", "neogeo", "2003",
	"Crouching Tiger Hidden Dragon 2003 Super Plus\0", "Hack of \"Crouching Tiger Hidden Dragon 2003\"", "Phenixsoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, ct2k3spRomInfo, ct2k3spRomName, neogeoInputInfo, neogeoDIPInfo,
	ct2k3spInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 4 Plus (bootleg / hack)

static struct BurnRomInfo ms4plusRomDesc[] = {
	{ "263-p1p.bin",          0x100000, 0xac75c892, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (encrypted)
	{ "263-p2.bin",           0x400000, 0xfdb7aed8, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "263-s1p.bin",          0x020000, 0x07ff87ce, 2 | BRF_GRA }, 		 //  2 Text data

	// Confirmed, uses decrypted Sprite data, z80 and Samples from mslug4
	{ "ms4n_c1.rom",          0x800000, 0xa75ffcde, 3 | BRF_GRA },		 //  3 Sprite data
	{ "ms4n_c2.rom",          0x800000, 0x5ab0d12b, 3 | BRF_GRA },		 //  4
	{ "ms4n_c3.rom",          0x800000, 0x61af560c, 3 | BRF_GRA },		 //  5
	{ "ms4n_c4.rom",          0x800000, 0xf2c544fd, 3 | BRF_GRA },		 //  6
	{ "ms4n_c5.rom",          0x800000, 0x84c66c44, 3 | BRF_GRA },		 //  7
	{ "ms4n_c6.rom",          0x800000, 0x5ed018ab, 3 | BRF_GRA },		 //  8

	{ "263-m1_decrypted.bin", 0x010000, 0x0C4C42F8, 4 | BRF_ESS | BRF_PRG }, //  9 Z80 code

	{ "ms4n_v1.rom",          0x800000, 0xfd6b982e, 5 | BRF_SND }, 		 // 10 Sound data
	{ "ms4n_v2.rom",          0x800000, 0x20125227, 5 | BRF_SND }, 		 // 11
};

STDROMPICKEXT(ms4plus, ms4plus, neogeo);
STD_ROM_FN(ms4plus);

static int ms4plusInit()
{
	pNeoInitCallback = PLUSDecryptP;
	return NeoInit();
}

struct BurnDriver BurnDrvms4plus = {
	"ms4plus", "mslug4", "neogeo", "2002",
	"Metal Slug 4 Plus\0", "Hack of \"Metal Slug 4\"", "Playmore Corporation / Mega Enterprise", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, ms4plusRomInfo, ms4plusRomName, neogeoInputInfo, neogeoDIPInfo,
	ms4plusInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 (bootleg / hack)

static struct BurnRomInfo kof2k2blRomDesc[] = {
	{ "265-p1.bin",    0x100000, 0x9ede7323, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code
	{ "265-p2bl.bin",  0x400000, 0x6dbee4df, 1 | BRF_ESS | BRF_PRG }, 	//  1

	{ "265-s1bl.bin",  0x020000, 0x2255f5bf, 2 | BRF_GRA }, 		//  2 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	// Confirmed, this DOESN'T use encrypted samples from kof2002, m1 is bad decrypted
	{ "265-m1bl.bin",  0x020000, 0xab9d360e, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kof2k2bl, kof2k2bl, neogeo);
STD_ROM_FN(kof2k2bl);

static int kof2k2blInit()
{
	nNeoTextROMFixType = 8;
	pNeoInitCallback = kof2k2blDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkof2k2bl = {
	"kof2k2bl", NULL, "neogeo", "2002",
	"The King of Fighters 2002 - challenge to ultimate battle (bootleg)\0", "Bootleg of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof2k2blRomInfo, kof2k2blRomName, neogeoInputInfo, neogeoDIPInfo,
	kof2k2blInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 Plus (bootleg / hack, set 1)

static struct BurnRomInfo kf2k2plsRomDesc[] = {
	{ "265-p1p.bin",   0x100000, 0x4b818ef5, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code (encrypted)
	{ "265-p2bl.bin",  0x400000, 0x6dbee4df, 1 | BRF_ESS | BRF_PRG }, 	//  1

	{ "265-s1p.bin",   0x020000, 0x595e0006, 2 | BRF_GRA }, 		//  2 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	// Latest voice fix used on the PLUS bootlegs (kof10th uses this one also)
	{ "265-m1p.bin",   0x020000, 0xf6fab859, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code (alternate z80)

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kf2k2pls, kf2k2pls, neogeo);
STD_ROM_FN(kf2k2pls);

static int kf2k2plsInit()
{
	pNeoInitCallback = kf2k2plsDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k2pls = {
	"kf2k2pls", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Plus - challenge to ultimate battle (set 1)\0", "Hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2plsRomInfo, kf2k2plsRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2plsInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 Plus (bootleg / hack, set 2)

static struct BurnRomInfo kf2k2plaRomDesc[] = {
	{ "265-p1pa.bin",  0x100000, 0x6a3a02f3, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code
	{ "265-p2bl.bin",  0x400000, 0x6dbee4df, 1 | BRF_ESS | BRF_PRG }, 	//  1

	{ "265-s1pa.bin",  0x020000, 0x1a3ed064, 2 | BRF_GRA }, 		//  2 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	{ "265-m1p.bin",   0x020000, 0xf6fab859, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code (alternate z80)

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kf2k2pla, kf2k2pla, neogeo);
STD_ROM_FN(kf2k2pla);

static int kf2k2plaInit()
{
	pNeoInitCallback = kof2k2blDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k2pla = {
	"kf2k2pla", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Plus - challenge to ultimate battle (set 2)\0", "Alternate hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2plaRomInfo, kf2k2plaRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2plaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 Plus (bootleg / hack, set 3)

static struct BurnRomInfo kf2k2plbRomDesc[] = {
	{ "265-p1pl.bin",  0x100000, 0xea1b6e9c, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code
	{ "265-p2bl.bin",  0x400000, 0x6dbee4df, 1 | BRF_ESS | BRF_PRG }, 	//  1

	{ "265-s1pl.bin",  0x020000, 0x7df52924, 2 | BRF_GRA },		 	//  2 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	{ "265-m1bl.bin",  0x020000, 0xab9d360e, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kf2k2plb, kf2k2plb, neogeo);
STD_ROM_FN(kf2k2plb);

struct BurnDriver BurnDrvkf2k2plb = {
	"kf2k2plb", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Plus - challenge to ultimate battle (set 3)\0", "Alternate hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2plbRomInfo, kf2k2plbRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2plaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/* ----------------------------------------------------------------------------

	This is a real bootleg.  JotaCE dumped this, confirmed that all of
	the roms are fully decrypted, Px, Cx, M1, and Vx except	the S1.
	It it should have 4 Vx roms.
	The decrypted ROMs come from kof2002 encrypted set, so bootleg
	z80 used in the PLUS bootlegs is not used here.
	Some people use the encrypted ROMs from kof2002, but as the real
	layout is confirmed and that is not accurate, I'll use the original
	one from the cart.

------------------------------------------------------------------------------ */

// The King of Fighters 2002 Super (bootleg / hack)

static struct BurnRomInfo kf2k2sprRomDesc[] = {
	{ "265-p1sr.bin",          0x100000, 0xebedae17, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (decrypted)
	{ "265-p2sr.bin",          0x400000, 0x432fdf53, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "265-s1sr.bin",          0x020000, 0xfecbb589, 2 | BRF_GRA },		  //  2 Text data (scrambled)

	{ "kf2k2_c1.rom",          0x800000, 0x7efa6ef7, 3 | BRF_GRA },		  //  3 Sprite data (decrypted)
	{ "kf2k2_c2.rom",          0x800000, 0xaa82948b, 3 | BRF_GRA },		  //  4
	{ "kf2k2_c3.rom",          0x800000, 0x959fad0B, 3 | BRF_GRA },		  //  5
	{ "kf2k2_c4.rom",          0x800000, 0xefe6a468, 3 | BRF_GRA },		  //  6
	{ "kf2k2_c5.rom",          0x800000, 0x74bba7c6, 3 | BRF_GRA },		  //  7
	{ "kf2k2_c6.rom",          0x800000, 0xe20d2216, 3 | BRF_GRA },		  //  8
	{ "kf2k2_c7.rom",          0x800000, 0x8a5b561c, 3 | BRF_GRA },		  //  9
	{ "kf2k2_c8.rom",          0x800000, 0xbef667a3, 3 | BRF_GRA },		  // 10

	{ "265-m1_decrypted.bin",  0x020000, 0x1c661a4b, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code (decrypted)

	{ "265-v1sr.bin",          0x400000, 0x13d98607, 5 | BRF_SND },		  // 12 Sound data (decrypted)
	{ "265-v2sr.bin",          0x400000, 0x9cf74677, 5 | BRF_SND },		  // 13
	{ "265-v3sr.bin",          0x400000, 0x8e9448b5, 5 | BRF_SND },		  // 14
	{ "265-v4sr.bin",          0x400000, 0x067271b5, 5 | BRF_SND },		  // 15
};

STDROMPICKEXT(kf2k2spr, kf2k2spr, neogeo);
STD_ROM_FN(kf2k2spr);

static int kf2k2sprInit()
{
	nNeoTextROMFixType = 6;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k2spr = {
	"kf2k2spr", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Super - challenge to ultimate battle\0", "Hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2sprRomInfo, kf2k2sprRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2sprInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 Magic Plus (bootleg / hack)

static struct BurnRomInfo kf2k2mpRomDesc[] = {
	{ "kf02m-p1.bin",  0x400000, 0xff7c6ec0, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code
	{ "kf02m-p2.bin",  0x400000, 0x91584716, 1 | BRF_ESS | BRF_PRG }, 	//  1

	{ "kf02m-s1.bin",  0x020000, 0x348d6f2c, 2 | BRF_GRA }, 	  	//  3 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	{ "265-m1p.bin",   0x020000, 0xf6fab859, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code (alternate z80)

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kf2k2mp, kf2k2mp, neogeo);
STD_ROM_FN(kf2k2mp);

static int kf2k2mpInit()
{
	nNeoTextROMFixType = 6;
	pNeoInitCallback = kf2k2mpDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k2mp = {
	"kf2k2mp", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Magic Plus - challenge to ultimate battle\0", "Hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2mpRomInfo, kf2k2mpRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2mpInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2002 Magic Plus II (bootleg / hack)

static struct BurnRomInfo kf2k2mp2RomDesc[] = {
	{ "k2k2m2p1.bin",  0x200000, 0x1016806c, 1 | BRF_ESS | BRF_PRG }, 	//  0 68K code
	{ "k2k2m2p2.bin",  0x400000, 0x432fdf53, 1 | BRF_ESS | BRF_PRG }, 	//  1 (decrypted)

	{ "k2k2m2s1.bin",  0x020000, 0x446e74c5, 2 | BRF_GRA }, 	  	//  2 Text data

	{ "265-c1bl.bin",  0x800000, 0xf25d3d66, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "265-c2bl.bin",  0x800000, 0xe3e66f1d, 3 | BRF_GRA }, 		//  4
	{ "265-c3bl.bin",  0x800000, 0x8732fa30, 3 | BRF_GRA }, 		//  5
	{ "265-c4bl.bin",  0x800000, 0x0989fd40, 3 | BRF_GRA }, 		//  6
	{ "265-c5bl.bin",  0x800000, 0x60635cd2, 3 | BRF_GRA }, 		//  7
	{ "265-c6bl.bin",  0x800000, 0xbd736824, 3 | BRF_GRA }, 		//  8
	{ "265-c7bl.bin",  0x800000, 0x2da8d8cf, 3 | BRF_GRA }, 		//  9
	{ "265-c8bl.bin",  0x800000, 0x2048404a, 3 | BRF_GRA }, 		// 10

	{ "265-m1p.bin",   0x020000, 0xf6fab859, 4 | BRF_ESS | BRF_PRG }, 	// 11 Z80 code (alternate z80)

	{ "265-v2bl.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 		// 12 Sound data
	{ "265-v1bl.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 		// 13
};

STDROMPICKEXT(kf2k2mp2, kf2k2mp2, neogeo);
STD_ROM_FN(kf2k2mp2);

static int kf2k2mp2Init()
{
	nNeoTextROMFixType = 3;
	pNeoInitCallback = kf2k2mp2Decrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k2mp2 = {
	"kf2k2mp2", "kof2k2bl", "neogeo", "2002",
	"The King of Fighters 2002 Magic Plus II - challenge to ultimate battle\0", "Hack of \"The King of Fighters 2002\"", "Eolith / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k2mp2RomInfo, kf2k2mp2RomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k2mp2Init, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters Special Edition 2004 (bootleg / hack)

static struct BurnRomInfo kf2k4speRomDesc[] = {
	{ "k2k4s-p1.bin",  0x400000, 0xe6c50566, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (P2 ROM)
	{ "k2k4s-p2.bin",  0x080000, 0x21a84084, 1 | BRF_ESS | BRF_PRG }, //  1 (P1 ROM, 1st chunk)
	{ "k2k4s-p3.bin",  0x080000, 0xfebb484e, 1 | BRF_ESS | BRF_PRG }, //  2 (P1 ROM, 2nd chunk)

	{ "k2k4s-s1.bin",  0x020000, 0xa3c9b2d8, 2 | BRF_GRA }, 	  //  3 Text data

	{ "k2k4s-c4.bin",  0x800000, 0x7a050288, 3 | BRF_GRA }, 	  //  4 Sprite data
	{ "k2k4s-c8.bin",  0x800000, 0xe924afcf, 3 | BRF_GRA }, 	  //  5
	{ "k2k4s-c3.bin",  0x800000, 0x959fad0b, 3 | BRF_GRA }, 	  //  6  (Same as kof2k2nd)
	{ "k2k4s-c7.bin",  0x800000, 0xefe6a468, 3 | BRF_GRA }, 	  //  7  (Same as kof2k2nd)
	{ "k2k4s-c2.bin",  0x800000, 0x74bba7c6, 3 | BRF_GRA }, 	  //  8  (Same as kof2k2nd)
	{ "k2k4s-c6.bin",  0x800000, 0xe20d2216, 3 | BRF_GRA }, 	  //  9  (Same as kof2k2nd)
	{ "k2k4s-c1.bin",  0x800000, 0xfa705b2b, 3 | BRF_GRA }, 	  // 10
	{ "k2k4s-c5.bin",  0x800000, 0x2c912ff9, 3 | BRF_GRA },		  // 11

	{ "k2k4s-m1.bin",  0x020000, 0x5a47d9ad, 4 | BRF_ESS | BRF_PRG }, // 12 Z80 code

	{ "k2k4s-v2.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 	  // 13 Sound data
	{ "k2k4s-v1.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 	  // 14
};

STDROMPICKEXT(kf2k4spe, kf2k4spe, neogeo);
STD_ROM_FN(kf2k4spe);

static int kf2k4speInit()
{
	pNeoInitCallback = kf2k4speDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k4spe = {
	"kf2k4spe", NULL, "neogeo", "2004",
	"The King of Fighters Special Edition 2004\0", "Hack of \"The King of Fighters 2002\"", "Dragon Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k4speRomInfo, kf2k4speRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k4speInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters Special Edition 2004 Plus (bootleg / hack)

static struct BurnRomInfo kf2k4splRomDesc[] = {
	{ "k2k4s-p1p.bin", 0x200000, 0xed97c684, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (scrambled)
	{ "k2k4s-p1.bin",  0x400000, 0xe6c50566, 1 | BRF_ESS | BRF_PRG }, //  1 (is the same as k2k4s-p1.bin)

	{ "k2k4s-s1p.bin", 0x020000, 0xcc0ab564, 2 | BRF_GRA }, 	  //  2 Text data (scrambled)

	{ "k2k4s-c4.bin",  0x800000, 0x7a050288, 3 | BRF_GRA }, 	  //  3 Sprite data
	{ "k2k4s-c8.bin",  0x800000, 0xe924afcf, 3 | BRF_GRA }, 	  //  4
	{ "k2k4s-c3.bin",  0x800000, 0x959fad0b, 3 | BRF_GRA }, 	  //  5  (Same as kof2k2nd)
	{ "k2k4s-c7.bin",  0x800000, 0xefe6a468, 3 | BRF_GRA }, 	  //  6  (Same as kof2k2nd)
	{ "k2k4s-c2.bin",  0x800000, 0x74bba7c6, 3 | BRF_GRA }, 	  //  7  (Same as kof2k2nd)
	{ "k2k4s-c6.bin",  0x800000, 0xe20d2216, 3 | BRF_GRA }, 	  //  8  (Same as kof2k2nd)
	{ "k2k4s-c1.bin",  0x800000, 0xfa705b2b, 3 | BRF_GRA }, 	  //  9
	{ "k2k4s-c5.bin",  0x800000, 0x2c912ff9, 3 | BRF_GRA },		  // 10

	{ "k2k4s-m1.bin",  0x020000, 0x5a47d9ad, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "k2k4s-v2.bin",  0x800000, 0x8ad2edbd, 5 | BRF_SND }, 	  // 12 Sound data
	{ "k2k4s-v1.bin",  0x800000, 0xb887d287, 5 | BRF_SND }, 	  // 13
};

STDROMPICKEXT(kf2k4spl, kf2k4spl, neogeo);
STD_ROM_FN(kf2k4spl);

static int kf2k4splInit()
{
	nNeoTextROMFixType = 3;
	pNeoInitCallback = kf2k4splDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k4spl = {
	"kf2k4spl", "kf2k4spe", "neogeo", "2004",
	"The King of Fighters Special Edition 2004 Plus\0", "Hack of \"The King of Fighters Special Edition 2004\"", "Dragon Co.", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k4splRomInfo, kf2k4splRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k4splInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 10th Anniversary (bootleg / hack)

static struct BurnRomInfo kof10thRomDesc[] = {
	{ "kf10-p1.bin",  0x800000, 0xB1FD0C43, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (includes text data)

	{ "kf10-c1a.bin", 0x400000, 0x3BBC0364, 3 | BRF_GRA }, 		 //  1 Sprite data
	{ "kf10-c2a.bin", 0x400000, 0x91230075, 3 | BRF_GRA }, 		 //  2
	{ "kf10-c1b.bin", 0x400000, 0xB5ABFC28, 3 | BRF_GRA }, 		 //  3
	{ "kf10-c2b.bin", 0x400000, 0x6CC4C6E1, 3 | BRF_GRA }, 		 //  4
	{ "kf10-c3a.bin", 0x400000, 0x5B3D4A16, 3 | BRF_GRA }, 		 //  5
	{ "kf10-c4a.bin", 0x400000, 0xC6F3419B, 3 | BRF_GRA }, 		 //  6
	{ "kf10-c3b.bin", 0x400000, 0x9D2BBA19, 3 | BRF_GRA }, 		 //  7
	{ "kf10-c4b.bin", 0x400000, 0x5A4050CB, 3 | BRF_GRA }, 		 //  8
	{ "kf10-c5a.bin", 0x400000, 0xA289D1E1, 3 | BRF_GRA }, 		 //  9
	{ "kf10-c6a.bin", 0x400000, 0xE6494B5D, 3 | BRF_GRA }, 		 //  10
	{ "kf10-c5b.bin", 0x400000, 0x404FFF02, 3 | BRF_GRA }, 		 //  11
	{ "kf10-c6b.bin", 0x400000, 0xF2CCFC9E, 3 | BRF_GRA }, 		 //  12
	{ "kf10-c7a.bin", 0x400000, 0xBE79C5A8, 3 | BRF_GRA }, 		 //  13
	{ "kf10-c8a.bin", 0x400000, 0xA5952CA4, 3 | BRF_GRA }, 		 //  14
	{ "kf10-c7b.bin", 0x400000, 0x3FDB3542, 3 | BRF_GRA }, 		 //  15
	{ "kf10-c8b.bin", 0x400000, 0x661B7A52, 3 | BRF_GRA }, 		 //  16

	{ "kf10-m1.bin",  0x020000, 0xF6FAB859, 4 | BRF_ESS | BRF_PRG }, //  17 Z80 code

	{ "kf10-v1.bin",  0x800000, 0x0FC9A58D, 5 | BRF_SND }, 		 //  18 Sound data (decrypted kof2002 samples)
	{ "kf10-v2.bin",  0x800000, 0xB8C475A4, 5 | BRF_SND }, 		 //  19
};

STDROMPICKEXT(kof10th, kof10th, neogeo);
STD_ROM_FN(kof10th);

static int kof10thInit()
{
	pNeoInitCallback = kof10thDecrypt;
	pNeoBankswitchCallback = kof10thMapBank;
	pNeoScanCallback = kof10thScan;
	pNeoProtectionCallback = kof10thProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvkof10th = {
	"kof10th", NULL, "neogeo", "2004",
	"The King of Fighters 10th Anniversary - all team battle\0", "Hack of \"The King of Fighters 2002\"", "SNK Playmore / Winter", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof10thRomInfo, kof10thRomName, neogeoInputInfo, neogeoDIPInfo,
	kof10thInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 10th Anniversary Extra Plus (bootleg / hack)

static struct BurnRomInfo kf10thepRomDesc[] = {
	{ "5008-p1.rom",    0x200000, 0xbf5469ba, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "5008-p2.rom",    0x400000, 0xa649ec38, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "5008-p3.rom",    0x200000, 0xe629e13c, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "5008-s1.rom",    0x020000, 0x92410064, 2 | BRF_GRA }, 	   //  3 Text data

	{ "kf10-c1a.bin",   0x400000, 0x3bbc0364, 3 | BRF_GRA }, 	   //  4 Sprite data
	{ "kf10-c2a.bin",   0x400000, 0x91230075, 3 | BRF_GRA }, 	   //  5
	{ "kf10-c1b.bin",   0x400000, 0xb5abfc28, 3 | BRF_GRA }, 	   //  6
	{ "5008-c2b.rom",   0x400000, 0xb1f565e1, 3 | BRF_GRA }, 	   //  7
	{ "kf10-c3a.bin",   0x400000, 0x5b3d4a16, 3 | BRF_GRA }, 	   //  8
	{ "kf10-c4a.bin",   0x400000, 0xc6f3419b, 3 | BRF_GRA }, 	   //  9
	{ "kf10-c3b.bin",   0x400000, 0x9d2bba19, 3 | BRF_GRA }, 	   //  10
	{ "kf10-c4b.bin",   0x400000, 0x5a4050cb, 3 | BRF_GRA }, 	   //  11
	{ "kf10-c5a.bin",   0x400000, 0xa289d1e1, 3 | BRF_GRA }, 	   //  12
	{ "kf10-c6a.bin",   0x400000, 0xe6494b5d, 3 | BRF_GRA }, 	   //  13
	{ "kf10-c5b.bin",   0x400000, 0x404fff02, 3 | BRF_GRA }, 	   //  14
	{ "kf10-c6b.bin",   0x400000, 0xf2ccfc9e, 3 | BRF_GRA }, 	   //  15
	{ "kf10-c7a.bin",   0x400000, 0xbe79c5a8, 3 | BRF_GRA }, 	   //  16
	{ "kf10-c8a.bin",   0x400000, 0xa5952ca4, 3 | BRF_GRA }, 	   //  17
	{ "5008-c7b.rom",   0x400000, 0x33604ef0, 3 | BRF_GRA }, 	   //  18
	{ "5008-c8b.rom",   0x400000, 0x51f6a8f8, 3 | BRF_GRA }, 	   //  19

	// Alternate z80...
	{ "5008-m1.rom",    0x020000, 0x5a47d9ad, 4 | BRF_ESS | BRF_PRG }, //  20 Z80 code

	{ "kf10-v1.bin",    0x800000, 0x0fc9a58d, 5 | BRF_SND }, 	   //  21 Sound data
	{ "kf10-v2.bin",    0x800000, 0xb8c475a4, 5 | BRF_SND }, 	   //  22
};

STDROMPICKEXT(kf10thep, kf10thep, neogeo);
STD_ROM_FN(kf10thep);

static int kf10thepInit()
{
	nNeoTextROMFixType = 3;
	pNeoInitCallback = kf10thepDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf10thep = {
	"kf10thep", "kof10th", "neogeo", "2004",
	"The King of Fighters 10th Anniversary Extra Plus - all team battle\0", "Hack of \"The King of Fighters 10th Anniversary\"", "SNK Playmore / Winter", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf10thepRomInfo, kf10thepRomName, neogeoInputInfo, neogeoDIPInfo,
	kf10thepInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 10th Anniversary 2005 Unique (bootleg / hack, set 1)

static struct BurnRomInfo kof10thuRomDesc[] = {
	{ "5006-p1.rom",   0x800000, 0xdd135fb6, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "5006-s1.rom",   0x020000, 0x7612e182, 2 | BRF_GRA }, 	  //  1 Text data

	{ "kf10-c1a.bin",  0x400000, 0x3bbc0364, 3 | BRF_GRA }, 	  //  2 Sprite data
	{ "kf10-c2a.bin",  0x400000, 0x91230075, 3 | BRF_GRA }, 	  //  3
	{ "kf10-c1b.bin",  0x400000, 0xb5abfc28, 3 | BRF_GRA }, 	  //  4
	{ "kf10-c2b.bin",  0x400000, 0x6CC4C6E1, 3 | BRF_GRA }, 	  //  5
	{ "kf10-c3a.bin",  0x400000, 0x5b3d4a16, 3 | BRF_GRA }, 	  //  6
	{ "kf10-c4a.bin",  0x400000, 0xc6f3419b, 3 | BRF_GRA }, 	  //  7
	{ "kf10-c3b.bin",  0x400000, 0x9d2bba19, 3 | BRF_GRA }, 	  //  8
	{ "kf10-c4b.bin",  0x400000, 0x5a4050cb, 3 | BRF_GRA }, 	  //  9
	{ "kf10-c5a.bin",  0x400000, 0xa289d1e1, 3 | BRF_GRA }, 	  //  10
	{ "kf10-c6a.bin",  0x400000, 0xe6494b5d, 3 | BRF_GRA }, 	  //  11
	{ "kf10-c5b.bin",  0x400000, 0x404fff02, 3 | BRF_GRA }, 	  //  12
	{ "kf10-c6b.bin",  0x400000, 0xf2ccfc9e, 3 | BRF_GRA }, 	  //  13
	{ "kf10-c7a.bin",  0x400000, 0xbe79c5a8, 3 | BRF_GRA }, 	  //  14
	{ "kf10-c8a.bin",  0x400000, 0xa5952ca4, 3 | BRF_GRA }, 	  //  15
	{ "kf10-c7b.bin",  0x400000, 0x3FDB3542, 3 | BRF_GRA }, 	  //  16
	{ "kf10-c8b.bin",  0x400000, 0x661B7A52, 3 | BRF_GRA }, 	  //  17

	{ "kf10-m1.bin",   0x020000, 0xF6FAB859, 4 | BRF_ESS | BRF_PRG }, //  18 Z80 code

	{ "kf10-v1.bin",   0x800000, 0x0fc9a58d, 5 | BRF_SND }, 	  //  19 Sound data
	{ "kf10-v2.bin",   0x800000, 0xb8c475a4, 5 | BRF_SND }, 	  //  20
};

STDROMPICKEXT(kof10thu, kof10thu, neogeo);
STD_ROM_FN(kof10thu);

static int kof10thuInit()
{
	pNeoInitCallback = kof10thuDecrypt;
	nNeoTextROMFixType = 6;
	return NeoInit();
}

struct BurnDriver BurnDrvkof10thu = {
	"kof10thu", "kof10th", "neogeo", "2005",
	"The King of Fighters 10th Anniversary 2005 Unique - all team battle (set 1)\0", "Hack of \"The King of Fighters 10th Anniversary\"", "SNK Playmore / Winter", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof10thuRomInfo, kof10thuRomName, neogeoInputInfo, neogeoDIPInfo,
	kof10thuInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 10th Anniversary 2005 Unique (hack / bootleg, set 2)

static struct BurnRomInfo kf2k5uniRomDesc[] = {
	// Same code as kof10thu, but separated in 2 custom chips on board
	{ "5006-p2a.bin",  0x400000, 0xced883a2, 1 | BRF_ESS | BRF_PRG },  //  0 68K code
	{ "5006-p1.bin",   0x400000, 0x72c39c46, 1 | BRF_ESS | BRF_PRG },  //  1

	{ "5006-s1.bin",   0x020000, 0x91f8c544, 2 | BRF_GRA },		   //  2 Text data (encrypted in a different way)

	{ "kf10-c1a.bin",  0x400000, 0x3BBC0364, 3 | BRF_GRA }, 	   //  3 Sprite data
	{ "kf10-c2a.bin",  0x400000, 0x91230075, 3 | BRF_GRA }, 	   //  4
	{ "kf10-c1b.bin",  0x400000, 0xB5ABFC28, 3 | BRF_GRA }, 	   //  5
	{ "kf10-c2b.bin",  0x400000, 0x6CC4C6E1, 3 | BRF_GRA }, 	   //  6
	{ "kf10-c3a.bin",  0x400000, 0x5B3D4A16, 3 | BRF_GRA }, 	   //  7
	{ "kf10-c4a.bin",  0x400000, 0xC6F3419B, 3 | BRF_GRA }, 	   //  8
	{ "kf10-c3b.bin",  0x400000, 0x9D2BBA19, 3 | BRF_GRA }, 	   //  9
	{ "kf10-c4b.bin",  0x400000, 0x5A4050CB, 3 | BRF_GRA }, 	   //  10
	{ "kf10-c5a.bin",  0x400000, 0xA289D1E1, 3 | BRF_GRA }, 	   //  11
	{ "kf10-c6a.bin",  0x400000, 0xE6494B5D, 3 | BRF_GRA }, 	   //  12
	{ "kf10-c5b.bin",  0x400000, 0x404FFF02, 3 | BRF_GRA }, 	   //  13
	{ "kf10-c6b.bin",  0x400000, 0xF2CCFC9E, 3 | BRF_GRA }, 	   //  14
	{ "kf10-c7a.bin",  0x400000, 0xBE79C5A8, 3 | BRF_GRA }, 	   //  15
	{ "kf10-c8a.bin",  0x400000, 0xA5952CA4, 3 | BRF_GRA }, 	   //  16
	{ "kf10-c7b.bin",  0x400000, 0x3FDB3542, 3 | BRF_GRA }, 	   //  17
	{ "kf10-c8b.bin",  0x400000, 0x661B7A52, 3 | BRF_GRA }, 	   //  18

	{ "5006-m1.bin",   0x020000, 0x9050bfe7, 4 | BRF_ESS | BRF_PRG },  //  19 Z80 code (encrypted)

	{ "kf10-v1.bin",   0x800000, 0x0FC9A58D, 5 | BRF_SND }, 	   //  20 Sound data
	{ "kf10-v2.bin",   0x800000, 0xB8C475A4, 5 | BRF_SND }, 	   //  21

};

STDROMPICKEXT(kf2k5uni, kf2k5uni, neogeo);
STD_ROM_FN(kf2k5uni);

static int kf2k5uniInit()
{
	nNeoTextROMFixType = 9;
	pNeoInitCallback = kf2k5uniDecrypt;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k5uni = {
	"kf2k5uni", "kof10th", "neogeo", "2005",
	"The King of Fighters 10th Anniversary 2005 Unique - all team battle (set 2)\0", "Alternate hack of \"The King of Fighters 10th Anniversary\"", "SNK Playmore / Winter", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k5uniRomInfo, kf2k5uniRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k5uniInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Matrimelee (bootleg / hack)

static struct BurnRomInfo matrimblRomDesc[] = {
	{ "266-p1.bin",    0x100000, 0x5d4c2dc7,  1 | BRF_ESS | BRF_PRG }, // 0 68K code
	{ "266-p2.bin",    0x400000, 0xa14b1906,  1 | BRF_ESS | BRF_PRG }, // 1

	{ "mart_c1.rom",   0x800000, 0xa5595656,  3 | BRF_GRA },	   // 2 sprite data (has 64 bit-swap like cthd2003)
	{ "mart_c2.rom",   0x800000, 0xc5f7c300,  3 | BRF_GRA }, 	   // 3
	{ "mart_c3.rom",   0x800000, 0x574efd7d,  3 | BRF_GRA },	   // 4
	{ "mart_c4.rom",   0x800000, 0x109d54d9,  3 | BRF_GRA },	   // 5
	{ "mart_c5.rom",   0x800000, 0x15c9e882,  3 | BRF_GRA },	   // 6
	{ "mart_c6.rom",   0x800000, 0x77497b97,  3 | BRF_GRA },	   // 7
	{ "mart_c7.rom",   0x800000, 0xab481bb6,  3 | BRF_GRA },	   // 8
	{ "mart_c8.rom",   0x800000, 0x906cf267,  3 | BRF_GRA },	   // 9

	{ "mart_m1.rom",   0x020000, 0x3ea96ab1,  4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (bit-swaped)

	{ "mart_v1.rom",   0x400000, 0x352b0a07,  5 | BRF_SND },	   // 11 Sound data
	{ "mart_v2.rom",   0x400000, 0x1e9bd59e,  5 | BRF_SND },	   // 12 (byteswapped)
	{ "mart_v3.rom",   0x400000, 0xe8362fcc,  5 | BRF_SND },	   // 13
	{ "mart_v4.rom",   0x400000, 0xc8c79b19,  5 | BRF_SND },	   // 14 (byteswapped)
};

STDROMPICKEXT(matrimbl, matrimbl, neogeo);
STD_ROM_FN(matrimbl);

static int matrimblInit()
{
	nNeoTextROMSize = 0x080000;
	pNeoInitCallback = matrimblDecrypt;
	nNeoBootlegSoundProtection = 1;
	return NeoInit();
}

struct BurnDriver BurnDrvmatrimbl = {
	"matrimbl", "matrim", "neogeo", "2002",
	"Matrimelee\0Shin gouketsuzi ichizoku - Toukon (bootleg)\0", NULL, "Playmore / Noise Factory / Atlus", "Neo Geo",
	L"\u65B0\u8C6A\u8840\u5BFA\u4E00\u65CF - \u95D8\u5A5A\0Matrimelee (bootleg)\0", NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ALTERNATE_TEXT,
	NULL, matrimblRomInfo, matrimblRomName, neogeoInputInfo, neogeoDIPInfo,
	matrimblInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 5 (bootleg / hack)

static struct BurnRomInfo ms5bootRomDesc[] = {
	{ "268-p1bl.bin", 0x100000, 0xe6d297af, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "268-p2bl.bin", 0x200000, 0x3fc46cfa, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "268-p3bl.bin", 0x200000, 0x742c955a, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "268-s1bl.bin", 0x020000, 0x52a8c09b, 2 | BRF_GRA }, 		 //  3 Text layer tiles (scrambled)

	// Unconfirmed sprite and sample data, maybe scrambled like svcboot
	{ "ms5-c1.bin",   0x800000, 0x969c0d62, 3 | BRF_GRA }, 		 //  4 Sprite data
	{ "ms5-c2.bin",   0x800000, 0xc69ae867, 3 | BRF_GRA }, 		 //  5
	{ "ms5-c3.bin",   0x800000, 0xd7beaeaf, 3 | BRF_GRA }, 		 //  6
	{ "ms5-c4.bin",   0x800000, 0xe1b1131b, 3 | BRF_GRA }, 		 //  7 (Watermarked ROM...)
	{ "ms5-c5.bin",   0x800000, 0x2fa1a5ad, 3 | BRF_GRA }, 		 //  8
	{ "ms5-c6.bin",   0x800000, 0x6de89589, 3 | BRF_GRA }, 		 //  9
	{ "ms5-c7.bin",   0x800000, 0x97bd0c0a, 3 | BRF_GRA }, 		 // 10
	{ "ms5-c8.bin",   0x800000, 0xc0d5bc20, 3 | BRF_GRA }, 		 // 11

	{ "268-m1bl.bin", 0x040000, 0x792e07c1, 4 | BRF_ESS | BRF_PRG }, // 12 Z80 code

	{ "ms5-v1.bin",   0x400000, 0xc3540e0d, 5 | BRF_SND }, 		 // 13 Sound data
	{ "ms5-v2.bin",   0x400000, 0x077bd2f4, 5 | BRF_SND }, 		 // 14
	{ "ms5-v3.bin",   0x400000, 0x39b14567, 5 | BRF_SND }, 		 // 15
	{ "ms5-v4.bin",   0x400000, 0x969ff3b2, 5 | BRF_SND }, 		 // 16
};

STDROMPICKEXT(ms5boot, ms5boot, neogeo);
STD_ROM_FN(ms5boot);

static int ms5bootInit()
{
	nNeoTextROMFixType = 2;
	pNeoProtectionCallback = ms5bootProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvms5boot = {
	"ms5boot", NULL, "neogeo", "2003",
	"Metal Slug 5 (bootleg)\0", "Bootleg of \"Metal Slug 5\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, ms5bootRomInfo, ms5bootRomName, neogeoInputInfo, neogeoDIPInfo,
	ms5bootInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 5 Plus (bootleg / hack)

static struct BurnRomInfo ms5plusRomDesc[] = {
	{ "268-p1p.bin",  0x100000, 0x106b276f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (protected code)
	{ "268-p2p.bin",  0x200000, 0xd6a458e8, 1 | BRF_ESS | BRF_PRG }, //  1
	{ "268-p3p.bin",  0x200000, 0x439ec031, 1 | BRF_ESS | BRF_PRG }, //  2

	{ "268-s1p.bin",  0x020000, 0x21e04432, 2 | BRF_GRA }, 		 //  3 Text layer tiles (scrambled)

	{ "ms5-c1.bin",   0x800000, 0x969c0d62, 3 | BRF_GRA }, 		 //  4 Sprite data
	{ "ms5-c2.bin",   0x800000, 0xc69ae867, 3 | BRF_GRA }, 		 //  5
	{ "ms5-c3.bin",   0x800000, 0xd7beaeaf, 3 | BRF_GRA }, 		 //  6
	{ "ms5-c4.bin",   0x800000, 0xe1b1131b, 3 | BRF_GRA }, 		 //  7 (Watermarked ROM...)
	{ "ms5-c5.bin",   0x800000, 0x2fa1a5ad, 3 | BRF_GRA }, 		 //  8
	{ "ms5-c6.bin",   0x800000, 0x6de89589, 3 | BRF_GRA }, 		 //  9
	{ "ms5-c7.bin",   0x800000, 0x97bd0c0a, 3 | BRF_GRA }, 		 // 10
	{ "ms5-c8.bin",   0x800000, 0xc0d5bc20, 3 | BRF_GRA }, 		 // 11

	{ "268-m1bl.bin", 0x040000, 0x792e07c1, 4 | BRF_ESS | BRF_PRG }, // 12 Z80 code

	{ "ms5-v1.bin",   0x400000, 0xc3540e0d, 5 | BRF_SND }, 		 // 13 Sound data
	{ "ms5-v2.bin",   0x400000, 0x077bd2f4, 5 | BRF_SND }, 		 // 14
	{ "ms5-v3.bin",   0x400000, 0x39b14567, 5 | BRF_SND }, 		 // 15
	{ "ms5-v4.bin",   0x400000, 0x969ff3b2, 5 | BRF_SND }, 		 // 16
};

STDROMPICKEXT(ms5plus, ms5plus, neogeo);
STD_ROM_FN(ms5plus);

static int ms5plusInit()
{
	nNeoTextROMFixType = 3;
	pNeoProtectionCallback = ms5plusProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvms5plus = {
	"ms5plus", "ms5boot", "neogeo", "2003",
	"Metal Slug 5 Plus\0", "Hack of \"Metal Slug 5\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, ms5plusRomInfo, ms5plusRomName, neogeoInputInfo, neogeoDIPInfo,
	ms5plusInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Metal Slug 6 (bootleg / hack)

static struct BurnRomInfo ms6bootRomDesc[] = {
	{ "299-p1.bin",   0x200000, 0x5F2FE228, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "299-p2.bin",   0x400000, 0x193FA835, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "299-s1.bin",   0x020000, 0x6F8B9635, 2 | BRF_GRA },		 //  2 Text layer tiles

	// I guess that this is incorrect, a cart pic shows 14 sprite chips...
	{ "256-c1.bin",   0x800000, 0x5A79C34E, 3 | BRF_GRA },		 //  3 Sprite data
	{ "256-c2.bin",   0x800000, 0x944C362C, 3 | BRF_GRA },		 //  4
	{ "256-c3.bin",   0x800000, 0x6E69D36F, 3 | BRF_GRA },		 //  5
	{ "256-c4.bin",   0x800000, 0xB755B4EB, 3 | BRF_GRA },		 //  6
	{ "256-c5.bin",   0x800000, 0x7AACAB47, 3 | BRF_GRA },		 //  7
	{ "256-c6.bin",   0x800000, 0xC698FD5D, 3 | BRF_GRA },		 //  8
	{ "256-c7.bin",   0x800000, 0xCFCEDDD2, 3 | BRF_GRA },		 //  9
	{ "256-c8.bin",   0x800000, 0x4D9BE34C, 3 | BRF_GRA },		 // 10

	// This should be correct?
	{ "256-m1.bin",   0x080000, 0xEAEEC116, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "256-v1.bin",   0x400000, 0xF2690241, 5 | BRF_SND },		 // 12 Sound data
	{ "256-v2.bin",   0x400000, 0x7E2A10BD, 5 | BRF_SND },		 // 13
	{ "256-v3.bin",   0x400000, 0x0EAEC17C, 5 | BRF_SND },		 // 14
	{ "256-v4.bin",   0x400000, 0x9B4B22D4, 5 | BRF_SND },		 // 15
};

STDROMPICKEXT(ms6boot, ms6boot, neogeo);
STD_ROM_FN(ms6boot);

static int ms6bootInit()
{
	pNeoInitCallback = ms6bootDecrypt;
	nNeoTextROMFixType = 6;
	nNeoProtectionXor = 0xAD;
	return NeoInit();
}

struct BurnDriver BurnDrvms6boot = {
	"ms6boot", "mslug3", "neogeo", "2000",
	"Metal Slug 6 (bootleg)\0", "Bootleg of \"Metal Slug 3\"", "SNK", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_A,
	NULL, ms6bootRomInfo, ms6bootRomName, neogeoInputInfo, neogeoDIPInfo,
	ms6bootInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM (bootleg / hack)

static struct BurnRomInfo svcbootRomDesc[] = {
	{ "svc-p1.bin",  0x800000, 0x0348f162, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (bit-swaped)

	{ "svc-s1.bin",  0x020000, 0x70b44df1, 2 | BRF_GRA }, 		//  1 Text data (scrambled)

	{ "svc-c1.bin",  0x800000, 0xa7826b89, 3 | BRF_GRA }, 		//  2 Sprite data (bit-swaped)
	{ "svc-c2.bin",  0x800000, 0xed3c2089, 3 | BRF_GRA }, 		//  3
	{ "svc-c3.bin",  0x800000, 0x71ed8063, 3 | BRF_GRA }, 		//  4
	{ "svc-c4.bin",  0x800000, 0x250bde2d, 3 | BRF_GRA }, 		//  5
	{ "svc-c5.bin",  0x800000, 0x9817c082, 3 | BRF_GRA }, 		//  6
	{ "svc-c6.bin",  0x800000, 0x2bc0307f, 3 | BRF_GRA }, 		//  7
	{ "svc-c7.bin",  0x800000, 0x4358d7b9, 3 | BRF_GRA }, 		//  8
	{ "svc-c8.bin",  0x800000, 0x366deee5, 3 | BRF_GRA }, 		//  9

	{ "svc-m1.bin",  0x020000, 0x804328c3, 4 | BRF_ESS | BRF_PRG }, // 10 Z80 code (scrambled)

	{ "svc-v2.bin",  0x400000, 0xb5097287, 5 | BRF_SND }, 		// 11 Sound data (bit-swaped)
	{ "svc-v1.bin",  0x400000, 0xbd3a391f, 5 | BRF_SND }, 		// 12
	{ "svc-v4.bin",  0x400000, 0x33fc0b37, 5 | BRF_SND }, 		// 13
	{ "svc-v3.bin",  0x400000, 0xaa9849a0, 5 | BRF_SND }, 		// 14
};

STDROMPICKEXT(svcboot, svcboot, neogeo);
STD_ROM_FN(svcboot);

static int svcbootInit()
{
	memset(CartRAM, 0, sizeof(CartRAM));

	pNeoInitCallback = svcbootDecrypt;
	nNeoTextROMFixType = 2;
	nNeoBootlegSoundProtection = 2;
	pNeoBankswitchCallback = NeoPVCBankswitch;
	pNeoProtectionCallback = PVCProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvsvcboot = {
	"svcboot", NULL, "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM (bootleg)\0", "Bootleg of \"SNK vs CAPCOM\"", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, svcbootRomInfo, svcbootRomName, neogeoInputInfo, neogeoDIPInfo,
	svcbootInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM Plus (bootleg / hack, set 1)

static struct BurnRomInfo svcplusRomDesc[] = {
	{ "svc-p1p.bin", 0x200000, 0xa194d842, 1 | BRF_ESS | BRF_PRG },  //  0 68K code
	{ "svc-p2p.bin", 0x200000, 0x50c0e2b7, 1 | BRF_ESS | BRF_PRG },  //  1
	{ "svc-p3p.bin", 0x200000, 0x58cdc293, 1 | BRF_ESS | BRF_PRG },  //  2

	{ "svc-s1p.bin", 0x020000, 0x73344711, 2 | BRF_GRA }, 		 //  3 Text data

	{ "svc-c1.bin",  0x800000, 0xa7826b89, 3 | BRF_GRA }, 		 //  4 Sprite data
	{ "svc-c2.bin",  0x800000, 0xed3c2089, 3 | BRF_GRA }, 		 //  5
	{ "svc-c3.bin",  0x800000, 0x71ed8063, 3 | BRF_GRA }, 		 //  6
	{ "svc-c4.bin",  0x800000, 0x250bde2d, 3 | BRF_GRA }, 		 //  7
	{ "svc-c5.bin",  0x800000, 0x9817c082, 3 | BRF_GRA }, 		 //  8
	{ "svc-c6.bin",  0x800000, 0x2bc0307f, 3 | BRF_GRA }, 		 //  9
	{ "svc-c7.bin",  0x800000, 0x4358d7b9, 3 | BRF_GRA }, 		 // 10
	{ "svc-c8.bin",  0x800000, 0x366deee5, 3 | BRF_GRA }, 		 // 11

	{ "svc-m1p.bin", 0x020000, 0x5aaa6764, 4 | BRF_ESS | BRF_PRG },  // 12 Z80 code

	{ "svc-v2.bin",  0x400000, 0xb5097287, 5 | BRF_SND }, 		 // 13 Sound data
	{ "svc-v1.bin",  0x400000, 0xbd3a391f, 5 | BRF_SND }, 		 // 14
	{ "svc-v4.bin",  0x400000, 0x33fc0b37, 5 | BRF_SND }, 		 // 15
	{ "svc-v3.bin",  0x400000, 0xaa9849a0, 5 | BRF_SND }, 		 // 16
};

STDROMPICKEXT(svcplus, svcplus, neogeo);
STD_ROM_FN(svcplus);

static int svcplusInit()
{
	pNeoInitCallback = svcplusDecrypt;
	nNeoTextROMFixType = 3;
	nNeoBootlegSoundProtection = 2;
	return NeoInit();
}

struct BurnDriver BurnDrvsvcplus = {
	"svcplus", "svcboot", "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM Plus (set 1)\0", "Hack of \"SNK vs CAPCOM\"", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, svcplusRomInfo, svcplusRomName, neogeoInputInfo, neogeoDIPInfo,
	svcplusInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM Plus (bootleg / hack, set 2)

static struct BurnRomInfo svcplusaRomDesc[] = {
	{ "svc-p1pl.bin",0x200000, 0x16b44144, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "svc-p2pl.bin",0x400000, 0x7231ace2, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "svc-s1pl.bin",0x020000, 0xca3c735e, 2 | BRF_GRA }, 		//  2 Text data

	{ "svc-c1.bin",  0x800000, 0xa7826b89, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "svc-c2.bin",  0x800000, 0xed3c2089, 3 | BRF_GRA }, 		//  4
	{ "svc-c3.bin",  0x800000, 0x71ed8063, 3 | BRF_GRA }, 		//  5
	{ "svc-c4.bin",  0x800000, 0x250bde2d, 3 | BRF_GRA }, 		//  6
	{ "svc-c5.bin",  0x800000, 0x9817c082, 3 | BRF_GRA }, 		//  7
	{ "svc-c6.bin",  0x800000, 0x2bc0307f, 3 | BRF_GRA }, 		//  8
	{ "svc-c7.bin",  0x800000, 0x4358d7b9, 3 | BRF_GRA }, 		//  9
	{ "svc-c8.bin",  0x800000, 0x366deee5, 3 | BRF_GRA }, 		// 10

	{ "svc-m1p.bin", 0x020000, 0x5aaa6764, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "svc-v2.bin",  0x400000, 0xb5097287, 5 | BRF_SND }, 		// 12 Sound data
	{ "svc-v1.bin",  0x400000, 0xbd3a391f, 5 | BRF_SND }, 		// 13
	{ "svc-v4.bin",  0x400000, 0x33fc0b37, 5 | BRF_SND }, 		// 14
	{ "svc-v3.bin",  0x400000, 0xaa9849a0, 5 | BRF_SND }, 		// 15
};

STDROMPICKEXT(svcplusa, svcplusa, neogeo);
STD_ROM_FN(svcplusa);

static int svcplusaInit()
{
	pNeoInitCallback = svcplusaDecrypt;
	nNeoTextROMFixType = 2;
	nNeoBootlegSoundProtection = 2;
	return NeoInit();
}

struct BurnDriver BurnDrvsvcplusa = {
	"svcplusa", "svcboot", "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM Plus (set 2)\0", "Alternate hack of \"SNK vs CAPCOM\"", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, svcplusaRomInfo, svcplusaRomName, neogeoInputInfo, neogeoDIPInfo,
	svcplusaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// SvC Chaos - SNK vs CAPCOM Super Plus (bootleg / hack)

static struct BurnRomInfo svcsplusRomDesc[] = {
	{ "svc-p1sp.bin",0x400000, 0x2601902f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code
	{ "svc-p2sp.bin",0x400000, 0x0ca13305, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "svc-s1sp.bin",0x020000, 0x233d6439, 2 | BRF_GRA }, 		//  2 Text data

	{ "svc-c1.bin",  0x800000, 0xa7826b89, 3 | BRF_GRA }, 		//  3 Sprite data
	{ "svc-c2.bin",  0x800000, 0xed3c2089, 3 | BRF_GRA }, 		//  4
	{ "svc-c3.bin",  0x800000, 0x71ed8063, 3 | BRF_GRA }, 		//  5
	{ "svc-c4.bin",  0x800000, 0x250bde2d, 3 | BRF_GRA }, 		//  6
	{ "svc-c5.bin",  0x800000, 0x9817c082, 3 | BRF_GRA }, 		//  7
	{ "svc-c6.bin",  0x800000, 0x2bc0307f, 3 | BRF_GRA }, 		//  8
	{ "svc-c7.bin",  0x800000, 0x4358d7b9, 3 | BRF_GRA }, 		//  9
	{ "svc-c8.bin",  0x800000, 0x366deee5, 3 | BRF_GRA }, 		// 10

	{ "svc-m1.bin",  0x020000, 0x804328c3, 4 | BRF_ESS | BRF_PRG }, // 11 Z80 code

	{ "svc-v2.bin",  0x400000, 0xb5097287, 5 | BRF_SND }, 		// 12 Sound data
	{ "svc-v1.bin",  0x400000, 0xbd3a391f, 5 | BRF_SND }, 		// 13
	{ "svc-v4.bin",  0x400000, 0x33fc0b37, 5 | BRF_SND }, 		// 14
	{ "svc-v3.bin",  0x400000, 0xaa9849a0, 5 | BRF_SND }, 		// 15
};

STDROMPICKEXT(svcsplus, svcsplus, neogeo);
STD_ROM_FN(svcsplus);

static int svcsplusInit()
{
	memset(CartRAM, 0, sizeof(CartRAM));

	pNeoInitCallback = svcsplusDecrypt;
	nNeoTextROMFixType = 6;
	nNeoBootlegSoundProtection = 2;
	pNeoBankswitchCallback = NeoPVCBankswitch;
	pNeoProtectionCallback = PVCProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvsvcsplus = {
	"svcsplus", "svcboot", "neogeo", "2003",
	"SvC Chaos - SNK vs CAPCOM Super Plus\0", "Hack of \"SNK vs CAPCOM\"", "Capcom / Playmore Corporation", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, svcsplusRomInfo, svcsplusRomName, neogeoInputInfo, neogeoDIPInfo,
	svcsplusInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// Samurai Shodown V (bootleg / hack)

static struct BurnRomInfo samsh5blRomDesc[] = {
	{ "ssv-p2.bin",  0x400000,  0x5023067f, 1 | BRF_ESS | BRF_PRG }, //  0 68K code (scrambled)
	{ "ssv-p1.bin",  0x400000,  0xb6cbe386, 1 | BRF_ESS | BRF_PRG }, //  1

	{ "ssv-s1.bin",  0x020000,  0x70f667d0, 2 | BRF_GRA },		 //  2 Text layer tiles (scrambled)

	{ "ssv-c1.bin",  0x1000000, 0x9c564a01, 3 | BRF_GRA },		 //  3 Sprite data (has 32 bit byte-swap)
	{ "ssv-c2.bin",  0x1000000, 0x4b73b8da, 3 | BRF_GRA },		 //  4
	{ "ssv-c3.bin",  0x1000000, 0x029f9bb5, 3 | BRF_GRA },		 //  5
	{ "ssv-c4.bin",  0x1000000, 0x75722430, 3 | BRF_GRA },		 //  6

	{ "ssv-m1.bin",  0x020000,  0x18114fb1, 4 | BRF_ESS | BRF_PRG }, //  7 Z80 code

	{ "ssv-v1.bin",  0x400000,  0xa3609761, 5 | BRF_SND },		 //  8 Sound data (bitswapped)
	{ "ssv-v2.bin",  0x400000,  0xcbd6ebd5, 5 | BRF_SND },		 //  9
	{ "ssv-v3.bin",  0x400000,  0x6f1c2703, 5 | BRF_SND },		 // 10
	{ "ssv-v4.bin",  0x400000,  0x5020c055, 5 | BRF_SND },		 // 11
};

STDROMPICKEXT(samsh5bl, samsh5bl, neogeo);
STD_ROM_FN(samsh5bl);

static int samsh5blInit()
{
	pNeoInitCallback = samsh5blDecrypt;
	nNeoTextROMFixType = 3;
	nNeoBootlegSoundProtection = 3;
	return NeoInit();
}

struct BurnDriver BurnDrvsamsh5bl = {
	"samsh5bl", "samsho5", "neogeo", "2003",
	"Samurai Shodown V\0Samurai Spirits Zero (bootleg)\0", "Bootleg of \"Samurai Shodown 5\"", "Yuki Enterprise / SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO,
	NULL, samsh5blRomInfo, samsh5blRomName, neogeoInputInfo, neogeoDIPInfo,
	samsh5blInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2003 (bootleg / hack, set 1)

static struct BurnRomInfo kf2k3blRomDesc[] = {
	{ "271-p1bl.bin", 0x400000, 0x92ed6ee3, 1 | BRF_ESS | BRF_PRG },  //  0 68K code (protected)
	{ "271-p2bl.bin", 0x400000, 0x5d3d8bb3, 1 | BRF_ESS | BRF_PRG },  //  1

	{ "271-s1bl.bin", 0x020000, 0x482c48a5, 2 | BRF_GRA }, 		  //  2 Text layer tiles (scrambled)

	{ "2k3-c1.bin",   0x800000, 0xe42fc226, 3 | BRF_GRA }, 		  //  3 Sprite data
	{ "2k3-c2.bin",   0x800000, 0x1b5e3b58, 3 | BRF_GRA }, 		  //  4
	{ "2k3-c3.bin",   0x800000, 0xd334fdd9, 3 | BRF_GRA }, 		  //  5
	{ "2k3-c4.bin",   0x800000, 0x0d457699, 3 | BRF_GRA }, 		  //  6
	{ "2k3-c5.bin",   0x800000, 0x8a91aae4, 3 | BRF_GRA }, 		  //  7
	{ "2k3-c6.bin",   0x800000, 0x9f8674b8, 3 | BRF_GRA }, 		  //  8
	{ "2k3-c7.bin",   0x800000, 0x374ea523, 3 | BRF_GRA }, 		  //  9
	{ "2k3-c8.bin",   0x800000, 0x75211f4d, 3 | BRF_GRA }, 		  //  10

	{ "271-m1bl.bin", 0x020000, 0x3a4969ff, 4 | BRF_ESS | BRF_PRG },  //  11 Z80 code

	{ "2k3-v1.bin",   0x400000, 0xd2b8aa5e, 5 | BRF_SND }, 		  //  12 Sound data
	{ "2k3-v2.bin",   0x400000, 0x71956ee2, 5 | BRF_SND }, 		  //  13
	{ "2k3-v3.bin",   0x400000, 0xddbbb199, 5 | BRF_SND }, 		  //  14
	{ "2k3-v4.bin",   0x400000, 0x01b90c4f, 5 | BRF_SND }, 		  //  15
};

STDROMPICKEXT(kf2k3bl, kf2k3bl, neogeo);
STD_ROM_FN(kf2k3bl);

static int kf2k3blInit()
{
	memset(CartRAM, 0, sizeof(CartRAM));

	nNeoTextROMFixType = 3;
	pNeoInitCallback = kf2k3blDecrypt;
	pNeoBankswitchCallback = NeoPVCBankswitch;
	pNeoProtectionCallback = kf2k3blProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k3bl = {
	"kf2k3bl", NULL, "neogeo", "2003",
	"The King of Fighters 2003 (bootleg, set 1)\0", "Bootleg of \"The King of Fighters 2003\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k3blRomInfo, kf2k3blRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k3blInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2003 (bootleg / hack, set 2)

static struct BurnRomInfo kf2k3blaRomDesc[] = {
	{ "271-p1bl.rom", 0x100000, 0x4ea414dd, 1 | BRF_ESS | BRF_PRG },  //  0 68K code
	{ "271-p3bl.rom", 0x400000, 0x370acbff, 1 | BRF_ESS | BRF_PRG },  //  1
	{ "271-p2bl.rom", 0x200000, 0x9c04fc52, 1 | BRF_ESS | BRF_PRG },  //  2

	{ "271-s1bl.bin", 0x020000, 0x482c48a5, 2 | BRF_GRA }, 		  //  3 Text layer tiles

	{ "2k3-c1.bin",   0x800000, 0xe42fc226, 3 | BRF_GRA }, 		  //  4 Sprite data
	{ "2k3-c2.bin",   0x800000, 0x1b5e3b58, 3 | BRF_GRA }, 		  //  5
	{ "2k3-c3.bin",   0x800000, 0xd334fdd9, 3 | BRF_GRA }, 		  //  6
	{ "2k3-c4.bin",   0x800000, 0x0d457699, 3 | BRF_GRA }, 		  //  7
	{ "2k3-c5.bin",   0x800000, 0x8a91aae4, 3 | BRF_GRA }, 		  //  8
	{ "2k3-c6.bin",   0x800000, 0x9f8674b8, 3 | BRF_GRA }, 		  //  9
	{ "2k3-c7.bin",   0x800000, 0x374ea523, 3 | BRF_GRA }, 		  //  10
	{ "2k3-c8.bin",   0x800000, 0x75211f4d, 3 | BRF_GRA }, 		  //  11

	{ "271-m1bl.bin", 0x020000, 0x3a4969ff, 4 | BRF_ESS | BRF_PRG },  //  12 Z80 code

	{ "2k3-v1.bin",   0x400000, 0xd2b8aa5e, 5 | BRF_SND }, 		  //  13 Sound data
	{ "2k3-v2.bin",   0x400000, 0x71956ee2, 5 | BRF_SND }, 		  //  14
	{ "2k3-v3.bin",   0x400000, 0xddbbb199, 5 | BRF_SND }, 		  //  15
	{ "2k3-v4.bin",   0x400000, 0x01b90c4f, 5 | BRF_SND }, 		  //  16
};

STDROMPICKEXT(kf2k3bla, kf2k3bla, neogeo);
STD_ROM_FN(kf2k3bla);

static int kf2k3blaInit()
{
	memset(CartRAM, 0, sizeof(CartRAM));

	nNeoTextROMFixType = 3;
	pNeoInitCallback = kf2k3blaDecrypt;
	pNeoBankswitchCallback = kf2k3blaBankswitch;
	pNeoProtectionCallback = kf2k3blaProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k3bla = {
	"kf2k3bla", "kf2k3bl", "neogeo", "2003",
	"The King of Fighters 2003 (bootleg, set 2)\0", "Alternate bootleg of \"The King of Fighters 2003\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k3blaRomInfo, kf2k3blaRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k3blaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2004 EX Hero (bootleg / hack)

static struct BurnRomInfo kof2k4exRomDesc[] = {
	{ "271-p1pl.bin", 0x100000, 0x07b84112, 1 | BRF_ESS | BRF_PRG },  //  0 68K code
	{ "271-p3bl.rom", 0x400000, 0x370acbff, 1 | BRF_ESS | BRF_PRG },  //  1
	{ "271-p2bl.rom", 0x200000, 0x9c04fc52, 1 | BRF_ESS | BRF_PRG },  //  2

	{ "271-s1pl.bin", 0x020000, 0xad548a36, 2 | BRF_GRA }, 		  //  3 Text layer tiles

	{ "2k3-c1.bin",   0x800000, 0xe42fc226, 3 | BRF_GRA }, 		  //  3 Sprite data
	{ "2k3-c2.bin",   0x800000, 0x1b5e3b58, 3 | BRF_GRA }, 		  //  4
	{ "2k3-c3.bin",   0x800000, 0xd334fdd9, 3 | BRF_GRA }, 		  //  5
	{ "2k3-c4.bin",   0x800000, 0x0d457699, 3 | BRF_GRA }, 		  //  6
	{ "2k3-c5.bin",   0x800000, 0x8a91aae4, 3 | BRF_GRA }, 		  //  7
	{ "2k3-c6.bin",   0x800000, 0x9f8674b8, 3 | BRF_GRA }, 		  //  8
	{ "2k3-c7.bin",   0x800000, 0x374ea523, 3 | BRF_GRA }, 		  //  9
	{ "2k3-c8.bin",   0x800000, 0x75211f4d, 3 | BRF_GRA }, 		  //  10

	{ "271-m1bl.bin", 0x020000, 0x3a4969ff, 4 | BRF_ESS | BRF_PRG },  //  11 Z80 code

	{ "2k3-v1.bin",   0x400000, 0xd2b8aa5e, 5 | BRF_SND }, 		  //  12 Sound data
	{ "2k3-v2.bin",   0x400000, 0x71956ee2, 5 | BRF_SND }, 		  //  13
	{ "2k3-v3.bin",   0x400000, 0xddbbb199, 5 | BRF_SND }, 		  //  14
	{ "2k3-v4.bin",   0x400000, 0x01b90c4f, 5 | BRF_SND }, 		  //  15
};

STDROMPICKEXT(kof2k4ex, kof2k4ex, neogeo);
STD_ROM_FN(kof2k4ex);

struct BurnDriver BurnDrvkof2k4ex = {
	"kof2k4ex", "kf2k3bl", "neogeo", "2003",
	"The King of Fighters 2004 EX Hero\0", "Hack of \"The King of Fighters 2003\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kof2k4exRomInfo, kof2k4exRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k3blaInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// The King of Fighters 2004 EX Ultra Plus (bootleg / hack)

static struct BurnRomInfo kf2k4uplRomDesc[] = {
	{ "2k3-p1up.bin", 0x800000, 0x87294c01, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "2k3-s1up.bin", 0x020000, 0xe5708c0c, 2 | BRF_GRA }, 		 //  1 Text layer tiles (scrambled)

	{ "2k3-c1.bin",   0x800000, 0xe42fc226, 3 | BRF_GRA }, 		 //  2 Sprite data
	{ "2k3-c2.bin",   0x800000, 0x1b5e3b58, 3 | BRF_GRA }, 		 //  3
	{ "2k3-c3.bin",   0x800000, 0xd334fdd9, 3 | BRF_GRA }, 		 //  4
	{ "2k3-c4.bin",   0x800000, 0x0d457699, 3 | BRF_GRA }, 		 //  5
	{ "2k3-c5.bin",   0x800000, 0x8a91aae4, 3 | BRF_GRA }, 		 //  6
	{ "2k3-c6.bin",   0x800000, 0x9f8674b8, 3 | BRF_GRA }, 		 //  7
	{ "2k3-c7.bin",   0x800000, 0x374ea523, 3 | BRF_GRA }, 		 //  8
	{ "2k3-c8.bin",   0x800000, 0x75211f4d, 3 | BRF_GRA }, 		 //  9

	{ "271-m1bl.bin", 0x020000, 0x3a4969ff, 4 | BRF_ESS | BRF_PRG }, //  11 Z80 code

	{ "2k3-v1.bin",   0x400000, 0xd2b8aa5e, 5 | BRF_SND }, 		 //  11 Sound data
	{ "2k3-v2.bin",   0x400000, 0x71956ee2, 5 | BRF_SND }, 		 //  12
	{ "2k3-v3.bin",   0x400000, 0xddbbb199, 5 | BRF_SND }, 		 //  13
	{ "2k3-v4.bin",   0x400000, 0x01b90c4f, 5 | BRF_SND }, 		 //  14
};

STDROMPICKEXT(kf2k4upl, kf2k4upl, neogeo);
STD_ROM_FN(kf2k4upl);

static int kf2k4uplInit()
{
	memset(CartRAM, 0, sizeof(CartRAM));

	nNeoTextROMFixType = 6;
	pNeoInitCallback = kf2k4uplDecrypt;
	pNeoBankswitchCallback = NeoPVCBankswitch;
	pNeoProtectionCallback = kf2k3blProtectionInstall;
	return NeoInit();
}

struct BurnDriver BurnDrvkf2k4upl = {
	"kf2k4upl", "kf2k3bl", "neogeo", "2003",
	"The King of Fighters 2004 EX Ultra Plus\0", "Hack of \"The King of Fighters 2003\"", "SNK Playmore", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, kf2k4uplRomInfo, kf2k4uplRomName, neogeoInputInfo, neogeoDIPInfo,
	kf2k4uplInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// ----------------------------------------------------------------------------
// Non Oficially Supported Games section

// -------------------------------------
// CD convertions / Hacks / Gambling games


// Mahjong Final Romance 2 (hacked Neo CD version)

static struct BurnRomInfo fr2chRomDesc[] = {
	{ "098-p1ch.bin",  0x100000, 0xA2527A5F, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "098-s1ch.bin",  0x20000,  0x764AC7AA, 2 | BRF_GRA }, 	  //  1 Text data

	{ "098-c1ch.bin",  0x100000, 0x025A7896, 3 | BRF_GRA }, 	  //  2 Sprite data
	{ "098-c2ch.bin",  0x100000, 0x1D2066B0, 3 | BRF_GRA }, 	  //  3
	{ "098-c3ch.bin",  0x100000, 0x19BD72A0, 3 | BRF_GRA }, 	  //  4
	{ "098-c4ch.bin",  0x100000, 0x46F89956, 3 | BRF_GRA }, 	  //  5
	{ "098-c5ch.bin",  0x100000, 0xC75DD306, 3 | BRF_GRA }, 	  //  6
	{ "098-c6ch.bin",  0x100000, 0xAEAAA9EB, 3 | BRF_GRA }, 	  //  7

	{ "098-m1ch.bin",  0x10000,  0xA455FA31, 4 | BRF_ESS | BRF_PRG }, //  8 Z80 code

	{ "098-v1ch.bin",  0x100000, 0x92E175F0, 5 | BRF_SND }, 	  //  9 Sound data
};

STDROMPICKEXT(fr2ch, fr2ch, neogeo);
STD_ROM_FN(fr2ch);

static int fr2chInit()
{
	pNeoInitCallback = fr2chCallback;
	return NeoInit();
}

struct BurnDriver BurnDrvfr2ch = {
	"fr2ch", NULL, "neogeo", "1995",
	"Mahjong Final Romance 2\0", "Hacked Neo CD convertion", "Video Systems", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_BOOTLEG, 2, HARDWARE_SNK_NEOGEO,
	NULL, fr2chRomInfo, fr2chRomName, neogeoInputInfo, neogeoDIPInfo,
	fr2chInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*------------------------------------------------------------------------------------

	There is another Sun Amusement (gambling) game titled 
	"Poker Kingdom/Bingo Island." This game very likely uses a similar,
	if not the same board as the other gambling games; this suspicion
	is because the cart has a communication port like vliner. The cart
	is labeled "Poker Kingdom Bingo Island VER 1.00"

------------------------------------------------------------------------------------*/

// Jockey Grand Prix

static struct BurnRomInfo jockeygpRomDesc[] = {
	{ "jgp-p1.bin",           0x100000, 0x2fb7f388, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "jgp-c1.bin",           0x800000, 0xa9acbf18, 3 | BRF_GRA },		 //  1 Sprite data
	{ "jgp-c2.bin",           0x800000, 0x6289eef9, 3 | BRF_GRA },		 //  2

	{ "jgp-m1_decrypted.bin", 0x080000, 0x1cab4de2, 4 | BRF_ESS | BRF_PRG }, //  3 Z80 code (decrypted)
	{ "jgp-m1.bin",           0x080000, 0xd163c690, 0 | BRF_PRG | BRF_OPT }, //  4 Z80 code

	{ "jgp-v1.bin",           0x200000, 0x443eadba, 5 | BRF_SND },		 //  5 Sound data
};

STDROMPICKEXT(jockeygp, jockeygp, neogeo);
STD_ROM_FN(jockeygp);

static int jockeygpInit()
{
	nNeoProtectionXor = 0xAC;
	return NeoInit();
}

struct BurnDriver BurnDrvjockeygp = {
	"jockeygp", NULL, "neogeo", "2001",
	"Jockey Grand Prix\0", NULL, "Sun Amusement / BrezzaSoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_ENCRYPTED_B | HARDWARE_SNK_GAMBLING,
	NULL, jockeygpRomInfo, jockeygpRomName, jockeygpInputInfo, neogeoDIPInfo,
	jockeygpInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

/*---------------------------------------------------------------------------------

	Vliner has more peculiarities than JockeyGP in that it does not have a 
	"V" (sample/PCM) rom. All of the audio in the game is synthesized by the
	"M" (Z80) rom.	Also, the game requires that the coin button is mapped to
	0x280000 & inverted.  Also, it has a different timer function (see 
	vliner_timer16_r in MAME) mapped at 0x320000.  There's also something 
	mapped to 0x2C0000, but its purpose is unknown.

	The Vliner board has 2 small Winbond (32kb?) RAM chips, a Panasonic CR2032
	3V battery, and a controller port sticking through the top.  This is labeled
	"CON1" which I'm assuming is used to connect the standard slot-machine arm.

---------------------------------------------------------------------------------------*/

// V-Liner (set 1)

static struct BurnRomInfo vlinerRomDesc[] = {
	// The photo of this board shows a sticker on the p1 that says "VP 1"
	{ "vl_p1.rom",   0x080000, 0x72a2c043, 1 | BRF_ESS | BRF_PRG }, //  0 68K code

	{ "vl_s1.rom",   0x020000, 0x972d8c31, 2 | BRF_GRA },		//  1 Text layer tiles

	{ "vl_c1.rom",   0x080000, 0x5118f7c0, 3 | BRF_GRA },		//  2 Sprite data
	{ "vl_c2.rom",   0x080000, 0xefe9b33e, 3 | BRF_GRA },		//  3

	{ "vl_m1.rom",   0x010000, 0x9b92b7d1, 4 | BRF_ESS | BRF_PRG }, //  4 Z80 code
};

STDROMPICKEXT(vliner, vliner, neogeo);
STD_ROM_FN(vliner);

struct BurnDriver BurnDrvvliner = {
	"vliner", NULL, "neogeo", "2001",
	"V-Liner (set 1)\0", "Missing sound", "Dyna / BrezzaSoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_GAMBLING,
	NULL, vlinerRomInfo, vlinerRomName, vlinerInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};

// V-Liner (set 2)

static struct BurnRomInfo vlineroRomDesc[] = {
	{ "vl_p1_54.rom", 0x080000, 0x172efc18, 1 | BRF_ESS | BRF_PRG },  //  0 68K code

	{ "vl_s1.rom",    0x020000, 0x972d8c31, 2 | BRF_GRA },		  //  1 Text layer tiles

	{ "vl_c1.rom",    0x080000, 0x5118f7c0, 3 | BRF_GRA },		  //  2 Sprite data
	{ "vl_c2.rom",    0x080000, 0xefe9b33e, 3 | BRF_GRA },		  //  3

	{ "vl_m1.rom",    0x010000, 0x9b92b7d1, 4 | BRF_ESS | BRF_PRG },  //  4 Z80 code
};

STDROMPICKEXT(vlinero, vlinero, neogeo);
STD_ROM_FN(vlinero);

struct BurnDriver BurnDrvvlinero = {
	"vlinero", "vliner", "neogeo", "2001",
	"V-Liner (set 2)\0", "Missing sound", "Dyna / BrezzaSoft", "Neo Geo",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SNK_NEOGEO | HARDWARE_SNK_GAMBLING,
	NULL, vlineroRomInfo, vlineroRomName, vlinerInputInfo, neogeoDIPInfo,
	NeoInit, NeoExit, NeoFrame, NeoRender, NeoScan, &NeoRecalcPalette,
	nNeoScreenWidth, 224, 4, 3
};
