		 _____________	  ______________    ______________
		|	      || |     ____     || |     ____     ||
		|     ________|| |    |    \    || |    ||   |    ||
		|     ||	 |    |     |   || |    ||___|    ||
		|     ||_____    |    |____/    || |              ||
		|	    ||   |	       //  |    _____     ||
		|     ______||   |	      //   |    ||   |    ||
		|     ||         |     ___    \\   |    ||   |    ||
		|     ||         |    |   \    \\  |    ||   |    ||
		|     ||         |    |    |    || |    ||   |    ||
		|     ||         |    |    |    || |    ||   |    ||
		|     ||	 |    |___/     || |    ||   |    ||
		|_____||	 |______________|| |____||   |____||
		|______|	 |_______________| |_____|   |_____| Plus!

Final Burn Alpha Plus! Readme

Want to contact me? send your suggestions to:
ferchogt4@hotmail.com
------------------------------------------
"Oficial" FB Alpha Plus! home page:
http://fbap.1emulation.com
------------------------------------------
Oficcial FB Alpha home page:
http://fba.emuunlim.com
------------------------------------------
Please, let this readme with this versions of FBA if you want to distrubute it, take in
mind that this FBA supports some UNSUPPORTED sets and is NOT the official version, just
a modification, if you want the official version go to the official home page mentioned
before.
Read this readme COMPLETELY :P, you'll need it ;)
------------===============================================================--------------

FB Alpha Plus! is an arcade emulator supporting the same hardware as FB Alpha, but with
some small modifications:

 - Capcom CPS-1
 - Capcom CPS-2
 - Cave
 - Neo Geo
 - Toaplan
 - Taito Rainbow Islands/Operation Wolf/Rastan
 - Psikyo 68EC020 based hardware
 - misc stuff we like

------------===============================================================--------------

Whats new:
----------
I'd like to thank specially to IQ_132 for all the help, inits, layouts and ROMs
given to this version, also for confirming, correcting and beta testing my build
:P thanks man!! :D
Also thanks to JhonBoy for the correct info about pnyaa.

v0.2.95.23 [u7] - 23/04/2006
=============================
Updated:

Drivers
-------
New Games:
- Street Fighter II' - champion edition (M-8) [CPS-1 / Hack].
- Street Fighter II' - champion edition (M-13) [CPS-1 / Hack].
- Street Fighter II' - champion edition (990804 Hispanic) [CPS-1 / Hack].
- Street Fighter II' - champion edition (Slay the Dragon, set 1) [CPS-1 / Hack].
- Street Fighter II' - champion edition (Slay the Dragon, set 2) [CPS-1 / Hack].
- Street Fighter II' - champion edition (Slay the Dragon, set 3) [CPS-1 / Hack].
- The King of Dragons (bootleg) [CPS-1 / Hack].
- Legend of Three Kingdoms' Heroes (set 1) [CPS-1 / Hack].
- Legend of Three Kingdoms' Heroes (set 2) [CPS-1 / Hack].
- Three Sword Masters [CPS-1 / Hack].
- Three Holy Swords (set 1) [CPS-1 / Hack].
- Three Holy Swords (set 2) [CPS-1 / Hack].
- Holy Sword Three Kingdoms (set 1) [CPS-1 / Hack].
- Holy Sword Three Kingdoms (set 2) [CPS-1 / Hack].
- Metal Slug 5 (JAMMA PCB, decrypted C) [Neo-Geo].
- Metal Slug 6 (bootleg) [Neo-Geo / Bootleg].
- Pochy and Nyaa (decrypted C) [Neo-Geo].
- SvC Chaos - SNK Vs CAPCOM (JAMMA PCB, set 2) [Neo-Geo].

Working Now New Games:
- Knights of the Round (bootleg) [CPS-1 / Hack].
- Street Fighter II' - champion edition (M-1) [CPS-1 / Hack].
- Street Fighter II' - champion edition (M-2) [CPS-1 / Hack].
- Metal Slug 5 (JAMMA PCB) [Neo-Geo].

Not Working New Games:
- Holy Sword Three Kingdoms (set 3) [CPS-1 / Hack].

------------------------------------------------------------

- [Neo-Geo] Added the latest infos about ms5pcb, the BIOS still missing,
  but you can use the asia-s3.bin bios just copy 4 times (512 KB) this bios
  and rename into 268-bios.bin in your ms5pcb zip file, this however is not
  correct at all, because is not confirmed if this set uses svcpcb or
  kf2k3pcb BIOS type.
- [Neo-Geo] Changed kf2k2spr layout, the dumper confirmed the rest of the
  ROMs.
- [Neo-Geo] Emulated WatchDog protection, this was patched before.
- [Neo-Geo] Reordered a bit trhe src and added a new callback for bankswitch
  handlers.
- [Neo-Geo] Fixed (partially) the character selection screen bug in cthd2003
  and cthd2k3sp, this however stills incorrect, because the problem comes
  directly from the 68K core used by now.
- [Neo-Geo] Confirmed pnyaa sprite dumps and added decrypted C set.
- [Neo-Geo] Added and updated comments in the src that contains info about
  games and their protections :D.
- [CPS-1] Removed sf2cebr, is not a real hack or bootleg.

*NOTE: ms6bbot is not correct, this set is missing the real sprite data, by
now it's using mslug3 sprite ROMs.



v0.2.95.23 [u6a] - 02/04/2006
=============================
Updated:

- [Neo-Geo] Emulated remaining kf2k3pcb and kof2003 p3 PVC protection
  (thanks to IQ_132).
- [Neo-Geo] Fixed some decryption functions.
- [Neo-Geo] Removed ms4boot, was a fake bootleg, ms4plus now uses the
  same MAME layout, that is the real and correct one, also made it clone
  of mslug4.
- [Neo-Geo] Renamed some ROMs.
- [Neo-Geo] Remodifyed the SMA decryption functions.
- [Neo-Geo] Removed patches for Uni-BIOS v2.2, they caused strange resets
  in some games. (thanks to Kaamos for the advice)



v0.2.95.23 [u6] - 24/02/2006
=============================
Phew!!! new year's first release... and come's heavy XD
Thanks to IQ_132, Jimmy_Page, robber804, Razoola and the MAME Team
for all the info.

Updated:

Drivers
-------
New Games:
- Art of Fighting 3 - the path of the warrior (Korean) [Neo-Geo].
- Pochy and Nyaa [Neo-Geo]. (GFX CRC's not confirmed yet)
- Metal Slug 5 (JAMMA PCB) [Neo-Geo]. (Not working, missing CRC info)
- Metal Slug 5 (MVS) [Neo-Geo].
- Metal Slug 5 (MVS, decrypted C) [Neo-Geo].
- Metal Slug 5 (bootleg) [Neo-Geo / Bootleg].
- Metal Slug 5 Plus [Neo-Geo / Bootleg].
- SvC Chaos - SNK Vs CAPCOM (JAMMA PCB) [Neo-Geo].
- SvC Chaos - SNK Vs CAPCOM (JAMMA PCB, decrypted C) [Neo-Geo].
- SvC Chaos - SNK Vs CAPCOM (MVS) [Neo-Geo].
- SvC Chaos - SNK Vs CAPCOM (MVS, decrypted C) [Neo-Geo].
- SvC Chaos - SNK Vs CAPCOM (bootleg) [Neo-Geo / Bootleg].
- SvC Chaos - SNK Vs CAPCOM Plus (set 1) [Neo-Geo / Bootleg].
- SvC Chaos - SNK Vs CAPCOM Plus (set 2) [Neo-Geo / Bootleg].
- SvC Chaos - SNK Vs CAPCOM Super Plus [Neo-Geo / Bootleg].
- Fighting Swords (Samurai Shodown 3 Korean version) [Neo-Geo].
- Samurai Shodown V (set 1) [Neo-Geo].
- Samurai Shodown V (set 2) [Neo-Geo].
- Samurai Shodown V (decrypted C) [Neo-Geo].
- Samurai Shodown V (bootleg) [Neo-Geo / Bootleg].
- The King of Fighters 2003 (JAMMA PCB) [Neo-Geo]. (Japanese version only)
- The King of Fighters 2003 (JAMMA PCB, decrypted C) [Neo-Geo].
- The King of Fighters 2003 (MVS) [Neo-Geo].
- The King of Fighters 2003 (MVS, decrypted C) [Neo-Geo].
- The King of Fighters 2003 (bootleg, set 1) [Neo-Geo / Bootleg].
- The King of Fighters 2003 (bootleg, set 2) [Neo-Geo / Bootleg].
- The King of Fighters 2004 EX Hero [Neo-Geo / Bootleg].
- The King of Fighters 2004 EX Ultra Plus [Neo-Geo / Bootleg].
- The Last Soldier (Korean version of The Last Blade) [Neo-Geo].
- Real Bout - Fatal Fury 2 (Korean) [Neo-Geo].
- Samurai Shodown V Special (set 1) [Neo-Geo]. (uncensored)
- Samurai Shodown V Special (set 2) [Neo-Geo]. (censored)
- Samurai Shodown V Special (set 3) [Neo-Geo]. (less censored)
- Samurai Shodown V Special (decrypted C) [Neo-Geo].

Working now new games:
- Maghong Final Romance 2 (bootleg) [Neo-Geo].

Not Working New Games:
- Marvel Vs Capcom - clash of super heroes (980112 Euro). [CPS-2]
- Marvel Super Heroes Vs Street Fighter (970625 Euro). [CPS-2]
- Super Street Fighter II - the tournament battle (930911 World). [CPS-2]
- X-Men vs Street Fighter (961004 Euro). [CPS-2]
- X-Men vs Street Fighter (960919 Asia). [CPS-2]

------------------------------------------------------------

- [Neo-Geo] Added support for Razoola's Uni-Bios 2.2.
- [Neo-Geo] Changed name of The King of Fighters 2003 Ultra Plus into The
  King of Fighters 2004 EX Ultra Plus and romset name into kof2k4up.
- [Neo-Geo] Changed ROMs in kof2k4ex to match real encrypted dumps.
- [Neo-Geo] Changed PVC bankswitch and init to make all PVC games use the
  same handlers.
- [Neo-Geo] Changed several romset names in bootleg sets to reflect that they
  are bootlegs (like kof2002b -> kof2k2bl or mslug5b -> ms5boot).
- [Neo-Geo] Added the real dumps of 68K, z80 and Text ROMs of ms5boot.
  (thanks to robber804 for the real info)
- [Neo-Geo] Added the routine to decrypt kf2k3pcb C-ROMs (thanks to Jimmy_Page,
  unfortunately due some problems it will take more RAM than I spected to decrypt)
- [Neo-Geo] FIxed bug in "How to play" screen in kof2002 (thanks to IQ_132).
- [Neo-Geo] Optimized code to patch BIOS (thanks to IQ_132).
- [Neo-Geo] Changed DIP settings for standalone PCB games, with that the region hack
  is removed finally, kf2k3pcb doesn't use that... has only a japanese BIOS, and
  svcpcb has included the Asia and Japan regions in the BIOS, so it can cahnge region
  with a jumper in the hardware (thenak to MAME team for the info).
- [Neo-Geo] Reordered almost all Neo-Geo src, now the decryption routines are located
  in neo_decrypt.cpp, bankswitch and protections in neo_prot.cpp and bootleg stuff in
  neo_boot.cpp.
- [Neo-Geo] Fixed Main screen in kog, now it changes Japanese / English depending of
  the region enabled. (thanks to IQ_132 and Razoola)
- [Neo-Geo] Changed some z80 ROMs in bootlegs like:
  - The King of Fighters 2002 Plus (set 1)
  - The King of Fighters 2002 Plus (set 2)
  - The King of Fighters 2002 Super
  - The King of Fighters 2002 Magic Plus
  - The King of Fighters 2002 Magic Plus II
  - SvC Chaos: SNK vs CAPCOM Plus (set 1)
  - SvC Chaos: SNK vs CAPCOM Plus (set 2)
  This because this are the real dumps used in the carts and not the old ones.
- [Neo-Geo] Changed C-ROMs and V-ROMs in kf2k2spr, it's confirmed that this set
  uses decrypted ROMs from kof2002 and not watermarked or protected.
  (thanks to IQ_132 and the dumper XD).
- [Neo-Geo] Replaced old kf2k2pls and ms4plus p1 dumps with the original ones.
  (thanks to robber804).
- [Neo-Geo] Fixed booting in jockeygp and controls in gambling games, vliner
  stills without sound though...
- [CPS-2] Renamed old mvsc into mvscu to match MAME.
- [CPS-2] Renamed old mshvsf into mshvsfu to match MAME.
- [CPS-2] Renamed some ROMs of spf and clones to match MAME.
- [CPS-2] Renamed old xmvsf into xmvsfr1 to match MAME.
- [Misc] Renamed all ROMs in tmnt sets to match MAME.

NOTE: Encypted z80 data is 100% accurate due the fact of having the data table
in the 0xf800 - 0xffff range, decrypted data is the best at the moment (over
99% to 100%). MAME data is incorrect due the lack of the data. Thanks to KanyEro



v0.2.95.23 [u5] - 07/12/2005
=============================
Updated:

Drivers
-------
New Games:
- Varth - Operation Thunderstorm (920714 World) [CPS-1].
- King of Gladiator [Neo-Geo].
- Lansquenet 2004 [Neo-Geo].
- The King of Fighters '96 Plus [Neo-Geo].
- The King of Fighters 2002 Magic Plus II - Challenge to Ultimate Battle [Neo-Geo].
- The King of Fighters 2005 Unique - All Team Battle (set 2) [Neo-Geo].

Working now new games:
- Super Puzzle Fighter II Turbo (960529 Asia) [CPS-2].

------------------------------------------------------------

- [Neo-Geo] Changed name in The King of Fighters Unique - All Team Battle into
  The King of Fighters 2005 Unique - All Team Battle (set 1) to match with
  title screen.
- [Neo-Geo] Optimized code to emulate sound in Lansquenet 2004.
- [CPS-2] Renamed sfz3a into sfz3ar1 to match latest MAME.
- [CPS-2] Renamed ROMs in ddtod to match latest MAME.
- [CPS-2] Renamed mshvsf into mshvsfu to match latest MAME.
- [CPS-2] Renamed ddsomr1 into ddsomr2 to match latest MAME.

*Thanks to Jimmy_Page, IQ_132 and Robbert for their help and drivers.



v0.2.95.23 [u4b] - 04/10/2005 (private)
=======================================
Updated:

- [Neo-Geo] Changed bankswitch for PVC games again, now svcchaos
  and kof2003 doesn't need patches any more.
- [Neo-Geo] Changed kof2k4ex bankswitch to use PVC Reading handler.
- [Neo-Geo] Changed some other bootleg handlers / inits.



v0.2.95.23 [u4a] - 22/09/2005
=============================
Updated:

- [Neo-Geo] Fixed a bug with svcboot and svcsplus, emulation was broken in [u4].

Misc
----
- Added code to change the default image showed in preview section in the Game
  List dialog, it will change if you select a background skin for the emulator.



v0.2.95.23 [u4] - 15/09/2005
=============================
Updated:

Drivers
-------
New Games:
- The King of Fighters 2002 Magic Plus - Challenge to Ultimate Battle [Neo-Geo].
- Neo No Panepon (2002-07-07 #1) [Neo-Geo].
- Neo No Panepon (2002-07-07 #2) [Neo-Geo].
- Neo No Panepon (2002-08-22) [Neo-Geo].
- Neo Pong (v1.0) [Neo-Geo].

Working now new games:
- The King of Fighters 2003 (set 2) [Neo-Geo] (I think it works now...).
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo].

------------------------------------------------------------

- [Neo-Geo] Cleaned up a bit the Neo-PVC code... now it looks "cleaner", also
  fixed savestate bugs with PVC bankswitched games. (thanks to IQ_132).
- [Neo-Geo] Fixed again svcchaos C saving code, now it should work (thanks to Jimmy_page).
- [Neo-Geo] Updated a member of the BurnRomInfo structure to accept long file names, with
  this fixed all the decrypted m1 ROMs are updated to MAME naming conventions.

Misc
----
- Added menu items for loading a skin with a dialog, also for unloading it, this avoid
  the use of editing manually the ini file, this options are located in .:[Video]:.
  menu. (thanks to Captain CPS-X).
- Fixed a bug with translation templates, if you add a pop-up item as last menu item
  that menu was taken as the last to traduce, so I moved some items to fix that.
- Added an item in .:[Misc]:. menu to reset a template to default language.



v0.2.95.23 [u3] - 15/07/2005
=============================
Updated:

Drivers
-------
New games:
- The King of Fighters 10th Anniversary Unique - All team Battle [Neo-Geo].
  (This set seems to be an alternate one... it doesn't have bankswitch x_x).

Working now new games:
- X-Men vs. Street Fighter (961023 US) [CPS-2]

Not working new games:
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo].
  (It seems to have a different protection from kof10th).

------------------------------------------------------------

- [Neo-Geo] Changed zontrick s1 ROM, it did not match MAME data
- [Neo-Geo] Changed the patching routine fro Neo-Geo BIOS, now it patches almost any
  BIOS, including the commented ones, if you need to use another BIOS, just comment out
  the actual one and uncomment the BIOS you want to enable, this aply for the matching
  case in neo_run.cpp, this also will work for irrmaze and kof2003 BIOSes (thanks to
  IQ_132).
- [Neo-Geo] Changed extra decryption function in svcchaos, now it takes less memory to
  work. (thanks to IQ_132)
- [Neo-Geo] Fixed a sound bug in irrmaze, the v2 ROM was used as a A sample instead of
  a B sample of the ADPCM data.
- [Neo-Geo] Fixed lyout in kf10thep, I missed some different ROMs from the original cart.
  (thanks to fataku)
- [Neo-Geo] Fixed lyout in kf2k2spr, the 2 Mo P1 was a bad dump.
- [CPS-1] Added some more "chinesse" hacks for wof. They seem to be from an original
  cart so here they are.

Misc
----
- Added a variable in makefile (makefile and makefile.mingw) to enable or disable the
  use of hacks for Neo-Geo BIOSes. If you're not happy with BIOS hacks just comment out
  the USE_NEOGEO_HACKS = 1 line in makefile, and then recompile your own version.
- Fixed a remaining bug in IPS patching, some games were having problems with certain
  patches, now that is fixed (thanks to emufan).
- Fixed datfile printing in UNICODE, the app version wasn't printed correctly, that is
  weird in some ways because in ASCII that was printed fully, also game names were fixed.
- Fixed chinesse and japanesse (non latin) languages support, it seems that some functions
  such as datfile printing had bugs with that languages, now that is fixed (I guess... I
  don't have a chinesse windows XD)
- Added an option for autoswitching fullscreen after game loading. (thanks to emufan)
- FINALLY!!! fixed a bug with skins on Win9x and ME OSes, well is an addition but works
  anyway, you need to disable the "Preview blitter" option in order to see the skin, even
  now you can use your custom skins (like WinKawaks does). If you are Win2000 or XP user
  you don't need to disable the "Preview blitter" option.
- Improved a bit the Disable CRC option, now it disables CRC and size checking (thanks to
  Shoometsu).



v0.2.95.23 [u2] - 20/06/2005
============================
Updated:

Drivers
-------
New games:
- The King of Fighters 2002 Plus - Challenge to Ultimate Battle (set 3) [Neo-Geo]
  (thanks to tlalocex).
- The King of Fighters 2002 Super - Challenge to Ultimate Battle [Neo-Geo]
  (The driver isn't fully correct :( )
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo] (thanks
  to birtkof).

Working now new games:
- Warriors of Fate (hack) [CPS-1] (thanks to bms888, it has no sound though)

Not working new games:
- Choko (010820 Japan) [CPS-2] (Most ROMs aren't dumped yet)
- Hyper Street Fighter II - the anniversary edition (Asia 040202) [CPS-2] (no XOR,
  preliminar driver, of course is locked due the recent date of release [2004])
- Hyper Street Fighter II - the anniversary edition (Japan 031222) [CPS-2] (no XOR).
- Jyangokushi - Haoh no Saihai (Japan 990527) [CPS-2] (no XOR).

------------------------------------------------------------

- [Neo-Geo] Added support for Unibios 2.1 from Razzola.
- [Neo-Geo] Re-writed the whole kof10th driver, the old one was all wrong, it patched
  the text extraction routines and several things instead of reading directly like
  the real cart, this one now works at 100%. (thanks to Black Diamond)
- [Neo-Geo] Changed PCM2 SNK code, now is shorter.
- [Neo-Geo] Changed almost all CRC's in mslug5 and mslug5nd sets, the GFX, sound, and
  z80 ROMs were redumped fully. (thanks to JhonBoy)
- [Neo-Geo] Rewrited the driver for mslug5 and clones (thanks to IQ_132).
- [Neo-Geo] Fixed a z80 error in some Homebrew games. (thanks to Salvador)
- [Neo-Geo] Fixed z80 error in roboarma (thanks to Salvador).
- [Neo-Geo] Fixed ROMnames in jockeygp to match MAME.
- [Neo-Geo] Fixed decryption in SvC Chaos - SNK vs. CAPCOM (set 1). (thanks to sabrinor,
  Jimmy_Page and IQ_132).
- [Neo-Geo] Re-added the asia-s3 BIOS ROM and patched it for faster booting (thanks to
  IQ_132).
- [CPS-1] Moved some read and write routines for wofh, now it works... with no sound
  but works. (thanks to bms888)
- [Misc] Fixed booting bug in rastan.

Misc
----
- Fixed ALL intriduced bugs in IPS patching support, now all menus work perfectly.
  (thanks to sabrinor and emufan)
- Added a menu item in .:[Misc]:. menu for disable or enable FB Alpha Plus! splash
  screen. (thanks to IQ_132)
- Fixed a bug with ROM mannagers dat file printing and Kaillera fixes when compiling
  UNICODE versions of FB Alpha Plus!, now that is fixed and should compile correctly
  (thanks to bms888, IQ_132 and Jimmy_Page). WATCH OUT: Is not the same saving a dat file
  with the UNICODE version than saving it with the non-UNICODE version, there are different
  functions for each build.
- Added 500% of overclock for CPU overclock dialog.
- Fixed a bug with macros and certain games, it seems that it couldn't read correctly
  the inputs for games that are clones of games that depends of another one... in short
  clones of clones.
- Fixed exe name in unicode build, it still was fba.exe, now is fbap.exe, the other builds
  are also affected by this (For example: NON unicode build name should be fbapa.exe).
- Fixed an issue with turbo mode, if you quited a game with turbo enabled, when you load
  another one you got an error in the past, now that is fixed, every time you load or quit
  a game, turbo mode will be disabled automaticaly. (thanks to Salvador)
- Rewrited and modifyed all the save decrypted ROMs routines, now they take less RAM and
  save the ID in the ROM name, no more xxx-s1d.bin or similar. (thanks to IQ_132)

ABOUT IPS PATCHES: I have to clarify this, because some people had problems with cer-
tain games, if you intend to use a AES IPS patch over patched games (like kof2000 or
rotd) you'll probably have problems with it, just don't use AES IPS patches because
that routines are already patched in FB Alpha Plus!.
UNICODE BUILDS: As you know, there aren't any UNICODE version of FB Alpha Plus! (binaries)
because I cannot test them due my S.O. limitations. If anyone is voluntier for compiling
UNICODE builds for Pentium and K6 CPU's, wellcome all.



v0.2.95.23 [u1a] - 08/04/2005
=============================
Updated:

- [Neo-Geo] Fixed driver in kof10th, now it's emulated at 100% (thanks to bms888), any-
  way they still glitches on text layers.

Misc
----
- Fixed a bug in IPS patching support, now if you open "select game" dialog, right-click
  end exit the menu, the main menu always work (thanks to sabrinor). Maybe they could be
  any other bug though, if you notice any, please advice me :).



v0.2.95.23 [u1] - 08/04/2005
============================
Updated:

Drivers
-------
New games:
- Frog Feast [Neo-Geo / Homebrew]

Working now new games:
- The King of Fighters 10th Anniversary [Neo-Geo] (thanks to BDiamond and IQ_132)

Not working new games:
- Warriors of Fate (hack) [By some strange reason doesn't work anymore :(, CPS-1]

-----------------------------------------------------------------------------

- [Neo-Geo] Fixed text bugs in ct2003sp, it seems that FB Alpha Plus! treated the
  s1 of 256 KB as a 512 KB one, so there was some "missing" data, now that is fixed.
- [Neo-Geo] Replaced the old function for gfx decrypt of cthd2003, ct2003sp, svcboot
  svcplus, svcplusa and svcsplus, now they use less RAM thanks to IQ_132 :)
- [Neo-Geo] Fixed a bug in socbrawl, the v2 ROM was treated as a GFX ROM instead of
  sound.
- [Neo-Geo] Fixed decryption in kof2002b (thanks to IQ_132).
- [Neo-Geo] Fixed reset bug in kof10th.
- [Neo-Geo] Added just for reference tha p3 and p3c ROMs in kof2003 and kof2003a ROMsets.
- [Neo-Geo] Fixed naming issues in some ROMs of mslug4b and ms4plus.
- [CPS-1] Fixed some game naming issues
- [CPS-2] Fixed some game naming issues

Misc
----
- Fixed a bug in Kaillera and DAT files saving, the game name wasn't printed fully.
- Modified the macros format, now they use the Kawaks / FB Alpha combo format, this
  is better in some ways because it allows to add combinatins and even autofire,
  thanks to IQ_132, Jimmy_Page, emufan, Gangta and Mr. K (aka MHz).
- Added IPS patching support, this will allow to play more games that cannot be on the
  gamelist. (thanks to IQ_132 and emufan)
- Remodifyed the WHOLE readme, so read it completely to know about the whole functions
  of FB Alpha Plus!



v0.2.95.23 - 15/03/2005
=======================
Updated:

Drivers
-------
New games:
- Puzz Loop 2 (010205 Japan) [CPS-2]
- Strikers 1945 (set 2) [Misc]
- Crouching Tiger Hidden Dragon 2003 (hack, set 2) [Neo-Geo]

Working now new games:
- 19XX: The War Against Destiny (951207 Asia) [CPS-2]
- Alien vs. Predator (940520 Asia) [CPS-2]

Not working new games:
- The King of Fighters 10th Anniversary (hack) [Neo-Geo]

-----------------------------------------------------------------

- [Neo-Geo] Fixed Text layers in "Rage of the Dragons" and "The King of Fighters 2002"
  the text layers were of 512 KB (by FB Alpha team) but in fact they are of 128.
- [Neo-Geo] Added the real bankswitch for svcchaos and kof2003 (+ clones that uses it)
  now they are emulated correctly. (thanks to bms888)
- [Neo-Geo] Fixed some V-ROMs loading issues. (thanks to netbug).
- [Neo-Geo] Changed lyout in svcnd set, now it uses 2 C-ROMs of 32 MB each instead of 8
  C-ROMs of 8 MB, also fixed the C-ROMs saving routine to save correctly the data from
  svcchaos. (thanks to IQ_132).
- [CPS-1] Added a booting patch for "Ghouls and Ghosts". (thanks to IQ_132)
- [CPS-2] Fixed some ROM names in some SIMM type games.

Misc
----
- Upgraded to version 0.2.95.23
- Fixed about menu bug (thanks to netbug)
- Added a menu item for turbo mode
- Readded some Neo-Geo macros.

Important: Sega games support was removed due some compatibility issues with this FBA
version.
------------============================================================----------------

System requirements
-------------------

OS:	You need Windows 98 or higher, preferably Windows 2000 or higher.
	DirectX7 or higher must be installed, some features require DirectX 9.
	Normal (unicode) builds will run only on Windows 2000/XP (or higher).
	non-unicode builds will run on Windows 98/Me as well.
CPU:	CPU speed should be at least equivalent to a Pentium 233MHz, to play
        all games at reasonable	framerates at least 366MHz is required. Exact
        requirements can vary by system or game, as well as video and audio
        settings.
	Normal builds require a Pentium II or higher, or an Athlon or higher.
	A seperate build is available for Pentium and K6 CPUs (MMX is not
	required, although some effects will not work without).
	The about box and the version info both show what CPU your build was
	optimised for (you can check the version info by right-clicking
	fba.exe	in the explorer and selecting properties, then the version
	tab on the window that appears). i586 optimised builds run on
	Pentium/K6 CPUs.
RAM:	192MB or more is recommended. At least 128MB is needed to run all
	games, 64MB should be considered the bare minimum.
VIDEO:	15/16/24/32bpp displays are supported.
	Basic blitter: DirectDraw7 support is required.
	The Basic blitter will work with any videocard that supports
	the minimum requirements.

	Enhanced blitter: DirectDraw7 + Direct3D7 support is required.
	The Enhanced blitter will not work with every video card available,
	specifically older Voodoo cards (up Voodoo 3000) will not work.
	Experimental blitter: DirectX Graphics 9 support is required.

	The Experimental blitter has limited functionality with DirectX 8.1
	compatible hardware, but needs DirectX 9 for full functionality.
	For optimal results, Geforce FX 5900 series or Radeon 9800 series
	(or faster) graphics cards are required. For these cards, select
	the appropriate filter version from the Advanced options submenu.
	For all other compatible cards (e.g. Geforce FX series or Radeon 8500
	and higher), select the high-performance option.

SOUND:	Any sound hardware supporting DirectSound3 should work.
	Sound is optional.
INPUT:	The keyboard and system mouse will always work. There is preliminary
	support for additional mice, and devices such as the X Arcade joystick
	which act as a keyboard are supported. All standard or DirectInput7
	compatible joysticks/joypads, and mice should work.


How to use FB Alpha Plus!
-------------------------

Make sure your ROMs are zipped and correct for use with FB Alpha Plus! (it can
write out dat files for ClrMame pro and Romcenter). Make sure FB Alpha Plus! knows
where to find your ROMs by specifying them in the ROM dirs dialog (accessible
from via the "Load Game" option). When adding new games, use the Rescan Roms
button, again accessible via the "Load Game" option. When viewing the "Load
Game" dialog, if a game doesn't appear as available, you do not have a
compatible or complete ROMset for that game. If you are missing only some
non-default optional files (e.g. alternative Neo Geo BIOSes), the game will
be faintly hightlighted. Uncheck the "Show available only" option to show
unavailable (they will show up highlighted).

Do NOT ask us where to get the ROMs for any game.

Select the game you want to play and click "OK". When the game is loaded, you
can set up inputs for it by selecting "Map game inputs" from the Game menu.
Double-click an input to assign it, or choose a preset for each player using
the drop-down boxes, and click the "Use preset" button to use that preset for
just this game or session, or click "Make default" to make that preset the
default for all games.

If you have equivalent ROMs for certain ROMsets in FB Alpha Plus! or any
decrypted game that doesn't have the same CRC's as the driver in FB Alpha
Plus!, you can, you can disable the CRC check by unchecking the "Disable
CRC checking" option, anyway it will show up a warning because this cannot
work for every game, in adittion to that you'll need to rename the roms
exactly as FB Alpha Plus! needs.

You can also play against people on the internet by selecting the "Play via
Kaillera" option from the Game menu instead of "Load game".


Commandline interface
---------------------

FB Alpha Plus! can also be invoked with command line options. When invoked this
way, FB Alpha Plus! will automatically switch to fullscreen mode when a game is
loaded, and the Escape key quits FB Alpha Plus!. The options are as follows;

fba <game> [-listinfo|-w|-a|-r <width>x<height>x<depth>]

<game>      = The game's romname. You can specify the filename of
              a savestate or input recording instead.
-w          = Run in a window instead of fullscreen.
-a          = Use the same resolution as the original arcade game.
-r          = Specify a resolution. Depth is optional.

If neither -a nor -r are specified, the default fullscreen resolution is
used.

Examples:

fba sfa3 -r 800x600x32

fba awesome_sfzch_recording.fr -w

fba vsav2 -a

For front-ends, you can also do fba -listinfo which will output information
about the supported games to stdout, and the ROM files they need in a MAME
compatible format.


Creating your own input presets
-------------------------------

You can add to the included presets by creating a .ini file in the
config\presets folder. A file example.ini is provided already as an example.
The preset name will be the filename without the ".ini", eg, example.ini is
displayed as example. In the .ini file it is possible to use specific names
such as "P1 Low Punch" or generic names such as "P1 Fire 1". When a game is
allocating inputs it will look for the specific names first, and then the
generic ones. The example provided has generic inputs only (unzip
"preset-example.zip" in the FB Alpha Plus! directory).


Usage/optimisation tips
-----------------------

Video

 - If the Enhanced blitter works on your system, use it, esp. for 32-bit
   screenmodes. Try to switch off the "Use DirectX texture management",
   as this can sometimes result in better speed, esp. if you have an nVidia
   card.
 - If the Enhanced blitter is very slow in windowed mode, hit alt-enter
   twice, going into full-screen mode and back. This will force DirectX to
   reorganise the memory on your video card.
 - If you have a monitor that can be rotated to a vertical orientation,
   uncheck "Rotate vertically aligned games" in the video menu. If vertical
   games don't have the correct orientation, check "Mirrored vertical
   alignment" in the "Monitor Properties" submenu as well.
 - Use "Double size", "Triple size", etc. options to control the window size
   and the resolution used for fullscreen mode. This will ensure all games
   will look similar without per-system or per-game settings.
   Note that: To view some games at 4x zoom requires a resolution higher than
	      1600x1200. If you can add custom resolutions to your videocard,
	      1712x1284 is a good choice.
	    - At high resolutions, RGB effects and triple-buffering require
	      large amounts of video memory. You may not be able to use them
	      both at the same time for all games if your videocard has less
	      then 64MB video RAM.
 - If you can add custom resolutions to your videocard, you can instruct
   FB Alpha Plus! to try to use the exact same resolutions the original game uses.
   To do this, select "Arcade" from the fullscreen resolution submenu. Then
   load a game and hit Alt-Enter to go to fullscreen mode. When this fails,
   FB Alpha Plus! will report the exact resolution you need to add to display this
   particular game so the image fits the screen without stretching (it will
   also take into account rotation for vertical games).

Sound

 - For the best sound sound quality, enable 4-point interpolation and
   FM interpolation.
 - If you have a really slow PC, set the sound samplerate at 22050 or 11025
   Hz, and make sure FM interpolation is disabled.

Input

 - If the mouse sensitivity is not to your liking, it can be changed for each
   game individually in the corresponding .ini file in the config\games
   directory. The label is "analog" and the default is 0x0100 (256 in decimal
   notation). Use higher values for faster movement, lower values result in
   slower movement.
 - If you turn off Auto-save input mapping, all games will have their input
   mapped according to the currently selected preset.
 - For difficult controller games, is better to use a Joystick or Joypad.

Misc

 - There are 8 directories that FB Alpha Plus! will search for ROMs available via
   the GUI.
 - You can record AVI movies if you enable the "Record AVI" option in "Game" menu.
 - You can throttle a game (enable turbo) if you select the "Enable turbo mode"
   option in the "Game" menu.
 - You can play certain hacks that aren't supported in the game list, just use the
   same IPS patches that MAME Plus! uses and place them in the ips directory, then
   right-click any game that has IPS patches and then select the desired hack.
 - For Neo Geo games, FB Alpha Plus! can read\write (though not create) MAME memory
   cards.
 - You can edit the default macros for FB Alpha Plus! if you edit the macros.dat
   file located in the config\macros folder, read also the howtomacro.txt in order
   to learn how to write a macro.
 - You can replace the F logo image used for the blitter preview with your
   own image. Create a 32bpp .bmp image, in a resolution similar to the games
   FB Alpha Plus! supports (e.g. 304x224), and edit the szPlaceHolder in
   config\fbaap.ini, or load it from .:[Misc]:. menu.
 - You can use multiple versions of FB Alpha Plus! from the same directory. Just
   rename one of the two fba.exe files. If you name the second .exe file
   fba2.exe, the application settings wil be stored in config\fba2.ini. Note
   that there might be problems if you use both versions to play the same
   game; the game's settings, but not control assignments, can be lost.
 - Should you ever want to return to the initial, default settings, delete
   the config subdirectory in your FB Alpha Plus! directory.
 - To hide the menu, right-click on the window. A second right mouse-click
   will restore it. While the menu is hidden in windowed mode, drag anywhere
   on the window to move it, and left-click to show the menu. Alternatively,
   you can use Ctrl + Enter to hide/show the menu.
 - If you select "associate with .fs and .fr extensions" from the Misc menu,
   FB Alpha Plus! will add some registry keys so that your savestates and input
   recordings can be started by simply double-clicking them in the explorer
   or on the desktop. Select "disassociate from .fs and .fr extensions" to
   remove the created registry keys completely.
 - You can still load the savestates created using savestate slots normally
   via the dialog or by double-clicking them.
 - There are some shortcut keys not listed in the menu. They are:
   Escape	Return to Windowed mode (from full-screen mode)
   F1		When in pause mode, run emulation for one frame
		When not in pause mode, enables turbo mode
   ALT + -	Sound volume down
   ALT + +	Sound volume up
   backspace	Toggle Frames per Second indicator
   T		On-Screen chat (during netplay only)
   Shift + F12  Saves a Game preview image
   INGAME shortcuts:
   F2		(For some games) Enters BIOS settings
   F3		Resets the current game


Troubleshooting [FAQ]
---------------------

FB Alpha Plus! isn't a perfect emulator, if you notice any bug please report to
the given E-Mail in the beginnig of this readme, here a mini-FAQ for some incon-
veniencies solving.

 1.- I don't see any game in my gamelist and I even defined the directories...
     What I am doing wrong?
 R.- Maybe you don't have the correct ROMset for FB Apha Plus!, you have bad BIOS
     or you didn't place the \ at the end of the ROMpath, anyway generate a
     romcenter or clrmame dat in order to see if your sets are OK.
 2.- What weird! I get a blue forbidden sign in some Neo-Geo games... Why?
 R.- Maybe you're missing some optional BIOS ROMs, anyway you can load the game
     and play without any problem.
 3.- Damm... I cannot confugure any macro...
 R.- Are you sure you have macros.dat in config\macros folder?, also get sure that
     you have enabled "Enable game input macros" in the ".:[Misc]:." menu.
 4.- How in heck can I add a macro? I have no idea...
 R.- Read the howtomacro.txt included with FB Alpha Plus!
 5.- The IPS patching features doesn't seems to work...
 R.- Get sure the you have the corresponding folder for that certain game in the ips
     directory.
 6.- Well, I disabled CRC cheking, but FB Alpha Plus! doesn't recognize mi game anyways
 R.- Are you sure the new ROM you zipped has the same name as the old one?
 7.- Some games doesn't seems to work if I disable CRC checking...
 R.- Well... some games have certain protections, so, if you intend to use decrypted ROMs
     or a ROM that is incompatible with the portection used in the game, it won't work,
     some of this protections are either the Neo-SMA SNK Protection, or the Neo-PVC
     PLAYMORE Protection, also this includes GFX encription (CMC45 or CMC50). In this
     cases the replacement ROMs should have this protection in order to be emulated.
     Here a little list with Protected games:
	- (The King of Fighters '98 - the slugfest) kof98, kof98k.
	- (The King of Fighters '99 - millenium battle) kof99, kof99a, kof99e.
	- (Garou - mark of the wolves) garou, garoun, garouo.
	- (Metal Slug 3) mslug3.
	- (The King of Fghters 2000) kof2000.
	- (The King of Fighters 2002 - challenge to ultimate battle) kof2002,
	  kof2k2nd, kof2002b, kf2k2pls, kf2k2pla, kf2k4spe, kf2k4spl, kof10th.
	- (Shin Gouketsuju Ichizoku - Toukon) matrim, matrimnd, matrimbl.
 8.- The old cheats I have since old FB Alpha Plus! releases doesn't seems to work now
 R.- FB Alpha changed the cheat formats (FB Alpha Plus! also, because this port is bassed
     on FB Alpha), so the old formats aren't recognized, you'll need the most up-to-date
     cheat files (ini INI format), you can get them in the FB Alpha Plus! site
 9.- Some games have a grey mark... What about them?
 R.- They are not working games, either they haven't emulated protections or important ROMs
     that aren't dumped yet, you can load them anyway but they will surely not work and FB
     Alpha Plus! will advice when trying to load a non-working game.


Acknowledgements
----------------

Thanks to: Dave, ElSemi, Gangta, OG, Razoola, Logiqx, TRAC, CrashTest,
           Andrea Mazzoleni, Derek Liauw Kie Fa, Dirk Stevens, Maxim Stepin,
           the MAME team, Shawn and Craig at XGaming.

Also to:   IQ_132, BDiamond, bms888, stg, evilS0u, BlackJack, James33, TerryXP
	   Rock Bogard, HalRin, fataku, Wesker, JImmy_Page, Vorador, sabrinor,
	   emufan, Salvador (He´s my best tester XD) and anyone that
	   I forgot. :).

Thanks also to everyone who has made suggestions, submitted code, or helped
in any other way.
