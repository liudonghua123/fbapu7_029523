		 ______________   ______________    ______________
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

Quieren contactarme? mandenme sus sugerencias a:
ferchogt4@hotmail.com
------------------------------------------
Pagina oficial del FB Alpha Plus!:
http://fbap.1emulation.com
------------------------------------------
Pagina oficial del FB Aplha Original:
http://fba.emuunlim.com
------------------------------------------
Por favor, deja este readme con estas versiones de FBA si deseas distrubuirlo, ademas ten
en cuenta que este FBA tiene sets que NO SON soportados oficialmente por FBA, ademas
aclaro que esta NO ES LA VERSION OFICIAL, sino una modificacion, si quieren la version
oficial vayan a la pagina antes citada unas lineas arriba.
Lean TODO el readme :P les conviene ;)
------------===============================================================--------------

FB Alpha Plus! es un emulador que soporta los mismos sistemas que FB Alpha, pero con
alguna que otra optimizacion o cambio...

 - Capcom CPS-1
 - Capcom CPS-2
 - Cave
 - Neo Geo
 - Toaplan
 - Taito Rainbow Islands/Operation Wolf/Rastan
 - Psikyo 68EC020 hardware
 - alguna otra cosilla

------------===============================================================--------------

¿Que hay de nuevo?
------------------
Quiero agradecer enormemente a IQ_132 por toda la ayuda brindada a esta versión
en específico, gracias a el varios inits, layouts y ROMs estan correctamente
emuladas y confirmadas, ademas de que fue mi beta tester :P Gracias IQ!!! :D
Gracias también a JhonBoy por su oportuna informacion sobre pnyaa.

v0.2.95.23 [u7] - 23/04/2006
=============================
Actualizado:

Drivers
-------
Juegos Nuevos:
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

Juegos nuevos ahora funcionales:
- Knights of the Round (bootleg) [CPS-1 / Hack].
- Street Fighter II' - champion edition (M-1) [CPS-1 / Hack].
- Street Fighter II' - champion edition (M-2) [CPS-1 / Hack].
- Metal Slug 5 (JAMMA PCB) [Neo-Geo].

Juegos nuevos no funcionales:
- Holy Sword Three Kingdoms (set 3) [CPS-1 / Hack].

------------------------------------------------------------

- [Neo-Geo] Añadidos los datos restantes de ms5pcb, sin embargo la BIOS aún
  no esta dumpeada, para subsanar este pequeño inconveniente pueden tomar
  la BIOS asia-s3.bin, copiarla 4 veces (512 KB) y añadirla en el zip del
  pcb nombrada como 268-bios.bin, con eso pueden correrlo, aunque no es 100%
  correcto debido que no se sabe si la BIOS es como svcpcb o como la de
  kf2k3pcb.
- [Neo-Geo] Cambiado nuevamente el layout de kf2k2spr, ahora todas las ROMs
  estan confirmadas y este layout es válido.
- [Neo-Geo] Emulado el WatchDog de la Neo-Geo, antes se usaba un hack para
  parchar la proteccion SRAM usada en algunos juegos que ahora ya no es
  necesario.
- [Neo-Geo] Reordenado un poco el codigo fuente y limpiado d_neogeo.cpp
  usando un nuevo callback para manipuladores de bankswitch.
- [Neo-Geo] Arreglado el bug (parcialmente) de la pantalla de selección de
  personajes en cthd2003 y cthd2k3sp, esto de cualquier manera no es
  del todo correcto debido a que el problema proviene directamente del core
  usado para emular el CPU del 68K.
- [Neo-Geo] Confirmados los verdaderos dumps para las ROMs de graficos de
  pnyaa, añadido el decrypted C también.
- [Neo-Geo] Añadidos y cambiados varios comentarios en el codigo fuente de
  Neo-Geo de IQ_132, que ahondan mas sobre información vital en los sets.
- [CPS-1] Eliminado el set sf2cebr, no es un dump real o un bootleg prove-
  niente de un cartucho, solo es un hack falso.

*NOTA: ms6boot no esta completo, se estan usando las ROMs de mslug3 para
completar lo que falta, sin embargo ese no es el verdadero layout.



v0.2.95.23 [u6a] - 02/04/2006
=============================
Actualizado:

- [Neo-Geo] Emulada la proteccion remanente PVC de la p3 de kf2k3pcb y
  kof2003 (gracias a IQ_132).
- [Neo-Geo] Arregladas alguna funciones de desencriptacion.
- [Neo-Geo] Eliminado el set ms4boot, no era un set verdadero, ahora
  ms4plus usa el mismo layout de MAME y es clon de mslug4, ya que es
  lo correcto.
- [Neo-Geo] Arreglados algunos nombres de ROMs.
- [Neo-Geo] Remodificadas las rutinas para la proteccion SMA.
- [Neo-Geo] Removidos los parches para las Uni-BIOS v2.2, causaban
  reseteos raros en algunos juegos. (gracias a Kaamos por avisar)



v0.2.95.23 [u6] - 24/02/2006
=============================
Phew!!! primer version del año... y viene cargadito XD
Gracias antes que nada a IQ_132, Jimmy_Page y robber804 por la info y
drivers.
Igualmente a Razoola por la info dada al MAME team y al MAME team por
la mayoria de sus drivers e info sobre la BIOS de svcpcb.

Actualizado:

Drivers
-------
Juegos Nuevos:
- Art of Fighting 3 - the path of the warrior (Korean) [Neo-Geo].
- Pochy and Nyaa [Neo-Geo]. (los CRC's no estan confirmados aún)
- Metal Slug 5 (JAMMA PCB) [Neo-Geo]. (Aún no funciona y faltan CRC's)
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
- The King of Fighters 2003 (JAMMA PCB) [Neo-Geo]. (Versión japonesa solamente)
- The King of Fighters 2003 (JAMMA PCB, decrypted C) [Neo-Geo].
- The King of Fighters 2003 (MVS) [Neo-Geo].
- The King of Fighters 2003 (MVS, decrypted C) [Neo-Geo].
- The King of Fighters 2003 (bootleg, set 1) [Neo-Geo / Bootleg].
- The King of Fighters 2003 (bootleg, set 2) [Neo-Geo / Bootleg].
- The King of Fighters 2004 EX Hero [Neo-Geo / Bootleg].
- The King of Fighters 2004 EX Ultra Plus [Neo-Geo / Bootleg].
- The Last Soldier (Korean version of The Last Blade) [Neo-Geo].
- Real Bout - Fatal Fury 2 (Korean) [Neo-Geo].
- Samurai Shodown V Special (set 1) [Neo-Geo]. (sin censura)
- Samurai Shodown V Special (set 2) [Neo-Geo]. (con censura)
- Samurai Shodown V Special (set 3) [Neo-Geo]. (menos censurado)
- Samurai Shodown V Special (decrypted C) [Neo-Geo].

Juegos nuevos ahora funcionales:
- Maghong Final Romance 2 (bootleg) [Neo-Geo].

Juegos nuevos no funcionales:
- Marvel Vs Capcom - clash of super heroes (980112 Euro). [CPS-2]
- Marvel Super Heroes Vs Street Fighter (970625 Euro). [CPS-2]
- Super Street Fighter II - the tournament battle (930911 World). [CPS-2]
- X-Men vs Street Fighter (961004 Euro). [CPS-2]
- X-Men vs Street Fighter (960919 Asia). [CPS-2]

------------------------------------------------------------

- [Neo-Geo] Añadido soporte para las Uni-Bios 2.2 de Razoola.
- [Neo-Geo] Cambiado el nombre de The King of Fighters 2003 Ultra Plus a
  The King of Fighters 2004 EX Ultra Plus para empatar con la pantalla de
  presentación, de igual forma el romset ahora se llama kof2k4up.
- [Neo-Geo] Cambiadas las roms diferentes en kof2k4ex, ahora usa los ver-
  daderos dumps con protección, que en si es la misma proteccion que en
  kf2k3bla.
- [Neo-Geo] Remodificado un poco el codigo para emular el bankswitch para
  la protección Neo-PVC, ahora todos los juegos que presenten esta protección
  usan el mismo manipulador.
- [Neo-Geo] Renombrados varios sets bootleg para reflejar que eso son, por
  ejemplo de kof2002b el nombre ahora es kof2k2bl, o de mslug5b a ms5boot.
- [Neo-Geo] Cambiadas las ROMs del 68K, z80 y añadida la de textos a ms5boot.
  (gracias a robber804 por la verdadera info)
- [Neo-Geo] Añadido codigo para emular la protección de las C-ROMs de kf2k3pcb
  (gracias a IQ_132 y a Jimmy_Page) Aunque gastara mas RAM de la debida (192
  en lugar de 128).
- [Neo-Geo] Arreglado un bug en el "How to play" de kof2002 (gracias a IQ_132).
- [Neo-Geo] Optimizado el codigo para parchar las BIOS (gracias a IQ_132).
- [Neo-Geo] Cambiados los DIPswitches para los juegos que sean placas PCB, de
  tal suerte que ya no son necesarios los hacks de idioma que antes estaban.
  Solo svcpcb puede cambiar de idioma debido a que la BIOS es 2 en 1 y el
  hardware original posee un jumper para tal efecto. (gracias por la info al
  MAME Team).
- [Neo-Geo] Reorganizado casi todo el codigo fuente de Neo-Geo, las funciones
  y protecciones ya no estarán directamente en d_neogeo.cpp, sino que ahora
  las rutinas de desencriptación se encuentran en neo_decrypt.cpp, los
  dispositivos de proteccion en neo_prot.cpp y rutinas para bootlegs en
  neo_boot.cpp.
- [Neo-Geo] Arreglado un problema con la pantalla de presentacion en kog,
  ahora cambiara a japones si se usa la bios japonesa, o ingles si se usa la
  BIOS de USA o la de Asia / Euro. (gracias a IQ_132 y Razoola)
- [Neo-Geo] Cambiadas varias ROMs z80 en sets bootleg como:
  - The King of Fighters 2002 Plus (set 1)
  - The King of Fighters 2002 Plus (set 2)
  - The King of Fighters 2002 Super
  - The King of Fighters 2002 Magic Plus
  - The King of Fighters 2002 Magic Plus II
  - SvC Chaos: SNK vs CAPCOM Plus (set 1)
  - SvC Chaos: SNK vs CAPCOM Plus (set 2)
  Esto debido a que las placas originales usan estas ROMs y no las anteriores.
- [Neo-Geo] Cambiadas varias ROMs en kf2k2spr, ya que se comprobo que usa C-ROMs
  y V-ROMs desencriptadas del set MVS original, es decir, sin protecciones o
  marcas de agua (gracias a IQ_132 y al dumper XD).
- [Neo-Geo] Cambiadas las P1 en kf2k2pls y ms4plus, usan su verdadero dump ahora.
  (gracias a robber804).
- [Neo-Geo] Añadidas rutinas de lectura de protección par los juegos de azar
  como jockeygp o vliner, aunque vliner no tiene sonido. Jockeygp funciona sin
  problemas...
- [CPS-2] Renombrado el antiguo set mvsc a mvscu para empatar con MAME.
- [CPS-2] Renombrado el antiguo set mshvsf a mshvsfu para empatar con MAME.
- [CPS-2] Renombradas algunas roms de spf y clones para empatar con MAME.
- [CPS-2] Renombrado el antiguo set xmvsf a xmvsfr1 para empatar con MAME.
- [Misc] Renombradas varias roms en todos los sets de tmnt para emparat con MAME.

NOTA: La informacion de las ROMs encriptadas es 100% correcta, ya que esta comprobado
que poseen las tablas de desencriptacion de los rangos 0xf800 - 0xffff, cosa que los
dumps de mame no tienen (son malos dumps), las m1 desencriptadas son las mas correctas
aunque no del todo debido a que les faltan datos aun (99% - 100%). Gracias a KanyEro



v0.2.95.23 [u5] - 07/12/2005
=============================
Actualizado:

Drivers
-------
Juegos Nuevos:
- Varth - Operation Thunderstorm (920714 World) [CPS-1].
- King of Gladiator [Neo-Geo].
- Lansquenet 2004 [Neo-Geo].
- The King of Fighters '96 Plus [Neo-Geo].
- The King of Fighters 2002 Magic Plus II - Challenge to Ultimate Battle [Neo-Geo].
- The King of Fighters 2005 Unique - All Team Battle (set 2) [Neo-Geo].

Juegos nuevos ahora funcionales:
- Super Puzzle Fighter II Turbo (960529 Asia) [CPS-2].

------------------------------------------------------------

- [Neo-Geo] Cambiado el nombre de The King of Fighters Unique - All Team Battle a
  The King of Fighters 2005 Unique - All Team Battle (set 1) para empatar con la
  pantalla de presentacion.
- [Neo-Geo] Optimizado codigo para poder emular correctamente las v's del
  Lansquenet 2004.
- [CPS-2] Renombrado sfz3a a sfz3ar1 para empatar con el ultimo MAME.
- [CPS-2] Renombradas ROMs en ddtod para empatar con el ultimo MAME.
- [CPS-2] Renombrado mshvsf a mshvsfu para empatar con el ultimo MAME.
- [CPS-2] Renombrado ddsomr1 a ddsomr2 para empatar con el ultimo MAME.

*Gracias Jimmy_Page, IQ_132 y a Robbert por su ayuda y drivers



v0.2.95.23 [u4b] - 04/10/2005 (privado)
=======================================
Actualizado:

- [Neo-Geo] Remodificado nuevamente el bankswitch para juegos PVC, ahora
  svcchaos y kof2003 ya no necesitan parches para poder iniciar.
- [Neo-Geo] Cambiado el bankswitch para kof2k4ex para que use la misma
  rutina de lectura del bankswitch PVC.
- [Neo-Geo] Cambiadas algunas rutinas para otros bootlegs de Neo-Geo.



v0.2.95.23 [u4a] - 22/09/2005
=============================
Actualizado:

- [Neo-Geo] Arreglado un bug con svcboot y svcsplus, en [u4] no funcionaban.

Miscelaneos
-----------
- Cambiado codigo para que tambien cambie la imagen por defecto del recuadro
  de vistas previas de la lista de juegos (el dialogo) cuando se elija un
  fondo para el emulador.



v0.2.95.23 [u4] - 15/09/2005
=============================
Actualizado:

Drivers
-------
Juegos Nuevos:
- The King of Fighters 2002 Magic Plus - Challenge to Ultimate Battle [Neo-Geo].
- Neo No Panepon (2002-07-07 #1) [Neo-Geo].
- Neo No Panepon (2002-07-07 #2) [Neo-Geo].
- Neo No Panepon (2002-08-22) [Neo-Geo].
- Neo Pong (v1.0) [Neo-Geo].

Juegos nuevos ahora funcionales:
- The King of Fighters 2003 (set 2) [Neo-Geo] (al menos creo que funciona).
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo].

------------------------------------------------------------

- [Neo-Geo] Limpiado un poco el codigo para la Neo-PVC... al menos ya se ve un
  poco mas "limpio", tambien se arreglaron problemas con los savestates de
  juegos que usan el bankswitch del PVC (gracias a IQ_132)
- [Neo-Geo] Remodificado el codigo de cuardar c's de svcchaos, ahora deberia funcionar
  bien (gracias a Jimmy_Page).
- [Neo-Geo] Actualizado un miembro de la estructura BurnRomInfo para aceptar nombres
  largos. Gracias a esto ahora las roms m1 desencriptadas tienen el nombre actualizado
  al estandar de MAME.

Miscelaneos
-----------
- Añadidos Items en el menu .:[Video]:. para cargar skins con cuandro de dialogo,
  igualmente se añadio una opcion para resetear el skin y no tener que estar editando
  el ini cada que se quiera cambiar o quitar un skin (gracias al Capitan CPS-X).
- Arreglado un bug con las plantillas de traduccion del FBA Plus!, parece que tiene
  problemas si se deja una opcion "pop-up" al final de un menu, asi que movi unas
  cuantas cosillas.
- Añadido un item en el menu .:[Misc]:. para poder resetear la plantilla de traduccion
  si esta aplicada al emulador.



v0.2.95.23 [u3] - 15/07/2005
=============================
Actualizado:

Drivers
-------
Juegos Nuevos:
- The King of Fighters 10th Anniversary Unique - All team Battle [Neo-Geo].
  (Este set parece ser un alterno... no posee bankswitch x_x).

Juegos nuevos ahora funcionales:
- X-Men vs. Street Fighter (961023 US) [CPS-2]

Juegos nuevos no funcionales:
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo].
  (la proteccion parece distinta del original kof10th)

------------------------------------------------------------

- [Neo-Geo] Cambiado el CRC de la s1 del zintrckb, el otro era incorrecto (no empataba
  la del MAME).
- [Neo-Geo] Modificada la rutina de parchado de las BIOS, ahora es capaz de parchar
  cualquier BIOS (excepto debug y unibios), inclusive las que estan comentadas, solo
  asegurense de ponerle lineas de comentario a la BIOS que quieren quitar, y
  eliminarselas a la BIOS que quieran habilitar, igualmente aplica para la rutina de
  parchado en neo_run.cpp, tambien se ha agregado esta opcion para las BIOS del irrmaze
  y kof2003 (gracias a IQ_132).
- [Neo-Geo] Cambiada la rutina de desencriptacion extra de svcchaos, ahora usa menos
  memoria (gracias a IQ_132).
- [Neo-Geo] Arreglado un bug en el sonido del irrmaze, la v2 era tomada como el sample
  A del ADPCM en lugar de ser el sample B.
- [Neo-Geo] Corregido el lyout de kf10thep, faltaban otras ROMs que eran distintas del
  set principal (gracias a fataku).
- [Neo-Geo] Eliminada la p1 de 2 MB del kf2k2spr, es un mal dump (al parecer).
- [CPS-1] Añadidos un par de hacks mas del wof... son versiones "chinas".

Miscelaneos
-----------
- Añadida una variable para habilitar o deshabilitar los hacks de booteo de las BIOS
  para Neo-Geo en el makefile (makefile y makefile.mingw), si no les agradan los hacks
  en las BIOS, tan solo comenten la linea USE_NEOGEO_HACKS = 1 en el makefile, con eso
  ya no se parcharan las BIOS, eso si, deberan recompilar para que surta efecto.
- Arreglado un bug que persistia en el soporte a parches IPS, al parecer algunos juegos
  tenian problemas con ciertos parches, ahora eso esta arreglado (gracias a emufan).
- Arreglado un bug con la impresion de la version del emulador en los dats de ClrMAME pro
  y RomCenter... extrañamente solo ocurria en la version UNICODE, asi mismo tambien quedo
  arreglado un bug con los nombres de los juegos.
- Arreglado el soporte a idiomas no latinos como el chino o japones, parece ser que algunas
  funciones tenian problemas imprimiendo en esos idiomas, para variar solo en UNICODE.
- Añadida la opcion de pasar a modo pantalla completa automaticamente despues de cargar un
  juego (gracias a emufan).
- POR FIN!!! arreglado el problema con los skins en FB Alpha Plus!, no es un arreglo del
  pero bueno, al menos funcionara para los sistemas como Windows 98 y Windows ME, si
  deshabilitan la opcion "Preview blitter" podran ahora visualizar de todas formas el
  skin por defecto, e inclusive poder usar los que mas les convengan (mas o menos como
  WinKawaks). Claro, solo los que usen Win9x o ME deben deshabilitar esta opcion, los
  usuarios de Win2000 o XP no necesitan hacerlo.
- Mejorado un poco la opcion de deshabilitar el CRC, ahora deshabilita el cheuqeo tanto
  de CRC como de tamaño.



v0.2.95.23 [u2] - 20/06/2005
============================
Actualizado:

Drivers
-------
Juegos Nuevos:
- The King of Fighters 2002 Plus - Challenge to Ultimate Battle (set 3) [Neo-Geo]
  (gracias a tlalocex).
- The King of Fighters 2002 Super - Challenge to Ultimate Battle [Neo-Geo]
  (El driver no esta bien emulado :( )
- The King of Fighters 10th Anniversary Extra Plus - All team Battle [Neo-Geo] (gracias
  a birtkof).

Juegos nuevos ahora funcionales:
- Warriors of Fate (hack) [CPS-1] (gracias a bms888, aunque aun le falla el sonido)

Juegos nuevos no funcionales:
- Choko (010820 Japan) [CPS-2] (La mayoria de las ROMs no estan dumpeadas)
- Hyper Street Fighter II - the anniversary edition (Asia 040202) [CPS-2] (sin XOR, driver
  preliminar, que por supuesto esta bloqueado por ser muy reciente [2004])
- Hyper Street Fighter II - the anniversary edition (Japan 031222) [CPS-2] (sin XOR).
- Jyangokushi - Haoh no Saihai (Japan 990527) [CPS-2] (sin XOR).

------------------------------------------------------------

- [Neo-Geo] Añadido soporte para las UniBios 2.1 de Razoola.
- [Neo-Geo] Reescrito completamente el driver para kof10th, el anterior parchaba el chip
  de la RAM de textos en lugar de leerlo y escribirlo como se supone que debe hacerlo.
  (gracias a Black Diamond)
- [Neo-Geo] Cambiado por completo el codigo para el PCM2 de SNK, ahora es mas corto.
- [Neo-Geo] Cambiados varios CRC's en mslug5 y mslug5nd, las ROMs de sonido, graficos
  y z80 han sido redumpeadas (gracias a JhonBoy).
- [Neo-Geo] Reescrito el driver para mslug5 y clones (gracias a IQ_132)
- [Neo-Geo] Arreglado un problema de z80 con algunos juegos HomeBrew. (gracias a Salvador)
- [Neo-Geo] Arreglado el error z80 en roboarma (gracias a Salvador).
- [Neo-Geo] Arreglados los nombres de ROMs del jockeygp para empatar con MAME.
- [Neo-Geo] Arreglada la desencriptacion en SvC Chaos - SNK vs. CAPCOM (set 1). (gracias
  a sabrinor, Jimmy_Page e IQ_132).
- [Neo-Geo] Reincorporadas las BIOS asia-s3 en la region europea y parchado el boteo de
  las mismas (gracias a IQ_132).
- [CPS-1] Movidas de lugar las rutinas de lectura y escritura en la RAM de wofh, gracias
  a eso ahora ya funciona... sin sonido pero funciona. (gracias a bms888)
- [Misc] Arreglado un bug en el booteo del rastan.

Miscelaneos
-----------
- Arreglados TODOS los bugs con lo del soporte a parches IPS, los menues funcionan
  perfectamente ahora. (gracias a sabrinor y emufan)
- Agregado un item en el menu .:[Misc]:. para habilitar o deshabilitar la pantalla
  del logo de FB Alpha Plus!. (gracias a IQ_132)
- Arreglado un bug de compilacion con las versiones UNICODE del FB Alpha Plus!, ahora
  el error que salia entes esta arreglado y debe compilar sin problemas. (gracias a
  bms888, IQ_132 y a Jimmy_Page). OJO: No va a ser lo mismo imprimir un dat en la version
  UNICODE que en la version no-UNICODE, ya que cada uno tiene una función distinta.
- Añadido 500% de overclock en el dialogo de CPU Overclock.
- Arreglado un bug con las macros en los sets plus de kof2002 y otros, al parecer no
  leia correctamente las macros para clones de juegos que dependen de otros, o lo que
  es mas simple... clones de clones.
- Arreglado el nombre del ejecutable para unicode, seguia siendo fba en lugar de fbap...
  por lo mismo los nombres de los demas builds han cambiado (P.EJ: la version NO unicode
  ahora se llama fbapa.exe).
- Arreglado un bug con el modo turbo, si se dejaba habilitado a la hora de salir de un
  juego, al cargar otro provocaba un error, ahora cada que se cargue o se salga de algun
  juego, el modo turbo se deshabilitará automaticamente. (gracias a Salvador)
- Reescritas y modificadas las rutinas de guardado de ROMs desencriptadas, ahora usan
  menos RAM que antes y ademas guarda las ROMs con el ID de carticho que debe ser, ya no
  mas xxx-s1d.bin ni cosas por el estilo. (gracias a IQ_132)

ACERCA DE LOS PARCHES IPS: Debo aclarar esto debido a que algunos usuarios han tenido
problemas con algunos juegos, si tratan de usar un parche IPS para la proteccion AES
con juegos que la tengan (como kof2000 o rotd) seguramente tendran probemas, asi que
eviten los parches IPS para el modo AES, ya que estas rutinas ya estan parchadas en
FB Alpha Plus!.
VERSIONES UNICODE: Como saben, FB Alpha Plus! no tiene versiones (en binario) UNICODE, ya
ye no puedo probarlas debido al S.O. que poseo, si alguien se ofrece de voluntario para
crear versiones UNICODE tanto para Pentium como para K6, bienvenido sea.



v0.2.95.23 [u1a] - 10/04/2005
=============================
Actualizado:

- [Neo-Geo] Arreglado el driver de ko10th ahora si esta emulado al 100% (gracias a bms888)
  aunque los textos fallan un poco aun.

Miscelaneos
-----------
- Arreglado un bug con respecto al soporte para parches IPS, por lo menos ahora el menu
  responde si se sale del menu de "Select game" dando click derecho sin seleccionar nada
  de hacks IPS (gracias a sabrinor). Aun esto puede presentar uno que otro bug... si lo
  notan reportenlo.



v0.2.95.23 [u1] - 08/04/2005
============================
Actualizado:

Drivers
-------
Juegos Nuevos:
- Frog Feast [Neo-Geo / Homebrew]

Juegos nuevos ahora funcionales:
- The King of Fighters 10th Anniversary [Neo-Geo] (gracias a BDiamond e IQ_132)

Juegos nuevos no funcionales:
- Warriors of Fate (hack) [Extrañamente ya no funciona :(, CPS-1]

------------------------------------------------------------

- [Neo-Geo] Arreglado un bug con los textos en ct2003sp :D, al parecer FB Alpha Plus!
  trataba la rom s1 de 256 KB como si fuera de 512 y por ende "faltaban" datos, ahora
  la ROM se carga normalmente.
- [Neo-Geo] Cambiada las función para cthd2003, ct2003sp, svcboot, svcplus, svcplusa y
  svcsplus para desencriptar los graficos, ahora cargan mas rapido por que necesitan menos
  memoria para correr (ahora solo usan 2 KB extra), gracias a IQ_132.
- [Neo-Geo] Arreglado un bug en socbrawl, la v2 era tratada como graficos en lugar de
  sonido.
- [Neo-Geo] Arregada la desencriptacion de kof2002b (gracias a IQ_132).
- [Neo-Geo] Arreglado un bug en el reset en kof10th, sin embargo aun no esta emulado al
  100% ya que hay uno que otro error en los textos y faltan caracteristicas especiales.
- [Neo-Geo] Añadidas solo por referencia las ROMs p3 y p3c en los sets kof2003 y kof2003a
  kof2k3nd sigue con el mismo layout.
- [Neo-Geo] Arreglados los nombres en algunas ROMs de mslug4b y ms4plus.
- [CPS-1] Arreglados algunos nombres de juegos
- [CPS-2] Arreglados algunos nombres de juegos

Miscelaneos
-----------
- Arreglado un bug tanto en Kaillera como a la hora de guardar dats para algun gestor de
  ROMs, ahora el nombre completo del juego es impreso.
- Remodificadas todas las macros, ahora usaran el formato de Kawaks / FB Alpha Combo
  (gracias a Jimmy Page, IQ_132, emufan, Mr. K (aka MHz) y a Gangta :)) lean por favor el
  howtomacro.txt para que sepan como pueden agregar macros y sus limitantes. Por otro
  lado sobra decir que con este nuevo tipo de macros se pueden hacer combinaciones e
  inclusive agregar autofire.
- Agegado el soporte a parches IPS, con eso se pueden jugar roms hack y mas. (gracias a
  IQ_132 y a emufan).
- Remodificado TODO el Readme... LEANLO COMPLETO!!! asi sabran como usar el FB Alpha Plus!



v0.2.95.23 - 15/03/2005
=======================
Actualizado:

Drivers
-------
Juegos Nuevos:
- Puzz Loop 2 (010205 Japan) [CPS-2]
- Strikers 1945 (set 2) [Misc]
- Crouching Tiger Hidden Dragon 2003 (hack, set 2) [Neo-Geo]

Juegos nuevos ahora funcionales:
- 19XX: The War Against Destiny (951207 Asia) [CPS-2]
- Alien vs. Predator (940520 Asia) [CPS-2]

Juegos nuevos no funcionales:
- The King of Fighters 10th Anniversary (hack) [Neo-Geo]

-----------------------------------------------------------------

- [Neo-Geo] Arreglados los textos en "Rage of the Dragons" y "The King of Fighters 2002"
  antes eran de 512 KB segun el FB Alpha team, pero en realidad son de 128 KB
- [Neo-Geo] Agregado el bankswitch para kof2003 y svcchaos (+ clones que lo usen)
  ahora se usa la emulacion correcta. (gracias a bms888)
- [Neo-Geo] Arreglados algunos problemas en la carga de las V-ROMs en general (gracias a
  netbug).
- [Neo-Geo] Cambiado el lyout de svcnd, ahora usa 2 C-ROMs de 32 MB cada una en vez de
  8 de 8 MB, tambien arreglada la rutina de guardado de C-ROms desencriptadas expresamente
  para svcchaos. (gracias a IQ_132)
- [CPS-1] Añadido un parche para el bootleo del "Ghouls and Ghosts" (gracias a
  IQ_132).
- [CPS-2] Arreglados algunos nombres de juegos de tipo SIMM

Miscelaneos
-----------
- Actualizado a la version 0.2.95.23
- Arreglado un bug con el about menu (gracias a netbug)
- Añadido un Item en el menu Game para el modo turbo
- Reañadidas algunas macros de Neo-Geo

Importante: El soporte para juegos de Sega ha sido removido debido a problemas de compa-
tibilidad con esta version de FBA.

------------===============================================================--------------

Requerimientos de Sistema:
--------------------------

SO:      Necesitaras de Windows 98 en adelante, las versiones normales (unicode)
         solo funcionaran en Windows 2000/XP, las versiones no-unicode funciona-
         ran desde Windows 98 en adelante. Necesitaran tambien DirectX7 y para
         blitters mas elaborados DirectX 9.
CPU:     Por lo menos el equivalente a un Pentium 233Mhz, para jugar todos los
	 juegos a un framerate razomable por lo menos uno de 366MHz. Los
	 requerimientos exactos varian segun el juego.
	 Versiones normales pueden requerir in Pentium I/II o mayor o un Athlon
	 o mayor. Ejecutables para K6 estan disponibles aparte, en la ventana
	 de "about" veras para que CPU esta optimizada tu version.
RAM:	 Por lo menos necesitaras 64MB de RAM, recomendable seria 128MB.
VIDEO:	 15/16/24 y 32 bits son soportados.

	 - El blitter basico funcionara en cualquier tarjeta de video que tenga
	   los minimos requerimientos y cuente con DirectDraw7.
	
	 - El blitter Mejorado necesitara DirectDraw7 + Direct3D7 puede que
	   no fuencione en cualquier tarjeta de video.
	
	 - El blitter experimental necesitara Directx9 y hardware compatible
	   con el, para mejores resultados es mejor usar una Geforce FX 5900
	   o una Raedon 9800 series (o mas rapida).
SONIDO:  Cualquier hardware de sonido que soporte DirectSound3 bastara.
CONTROL: Teclado y mouse serviran siempre, hay soporte preliminar para
	 ratones extra, y dispositivos como el X-Arcade que funcionan como
	 teclado son soportados, cualquier Joystick compatible con DirectInput7
	 funcionara.


Como usar FB Alpha Plus!
------------------------

Asegurate de que tus roms esten zippeadas y que son correctas para usar
con FB Alpha Plus!, FB Alpha Plus! usa ROMsets estandar de MAME, por lo
que cualquier set de los sistemas emulados por MAME que emule FB Alpha
Plus! tambien seran compatibles, de cualquier manera puedes exportar un
dat de ClrMAMEPro o RomCenter para checar que esten en condiciones.
Asegurate tambien de que FB Alpha Plus! sabe donde estan tus ROMs, edi-
tando tanto el ini, como desde el dialogo de Directorios en la opcion
"Load Game", Obviamente si tu set no es compatible no aparecera en la
lista de disponibles y tendra una marca roja. los juegos que necesiten
BIOs extra aparte de las necesarias y no las encuentren tendran una
marca azul, para ver todos tus juegos no disponibles desmarca la casilla
"Show only available"

NO nos preguntes donde conseguir ROMs para ningun juego.

Selecciona algun juego que quieras cargar y presiona el boton "Load Game"
para iniciar la carga y emulacion, para cambiar los controles por defecto
tambien puedes elegir ya cargado el juego la opcion "Map Game Inputs" del
menu "Game" tambien puedes elegir "Use Preset" si ya tienes alguno o de
la lista por defecto, si usas la opcion "Make Default" usaras esa configu-
racion por defecto en todos los juegos.

Si tienes ROMs equivalentes a algun driver soportado por FB Alpha Plus! o
a algun juego desencriptado, que no tenga los mismos CRC's puedes desha-
bilitar el checkeo de CRC clickeando la opcion "Disable CRC check", de
cualquier manera saldra una advertencia ya que esto puede no funcionar
para cualquier juego, ademas si deshabilitas esta opcion necesitaras que
tus ROMs se llamen igual a como pide el FB Alpha Plus!

Tambien puedes jugar contra gente online, tan solo elige la opcion "Play
via Kaillera" en lugar de "Load Game".


Interface de linea de comando
------------------------------

FB Alpha Plus! tambien puede ser llamado de esta manera, asi como FB Alpha,
cuando es llamado de esta forma automaticamente pasara a modo pantalla
completa cuando cargues un juego, la tecla Escape (Esc) hace que salgas del
emulador, las opciones son las siguientes:

fba <juego> [-listinfo|-w|-a|-r <ancho>x<alto>x<resolucion>]

<juego>     = Nombre del zip del juego, tambien puedes poner el
	      nombre de un savestate que tengas disponible.
-w          = Correr en ventana.
-a          = Usar la misma resolucion que el arcade original.
-r          = Especificar una resolucion, la profundidad es opcional.

Si -a o -r no son especificados, la resolucion por defecto en modo pantalla
completa es usada.

Ejemplos:

fba sfa3 -r 800x600x32

fba awesome_sfzch_recording.fr -w

fba vsav2 -a

Para Front-Ends puedes hacer fba -listinfo que sacara la informacion acerca
de los juegos soportados a stdout, y los ROMs necesarios en un formato MAME
compatible.


Creando tus propios presets
----------------------------

Puedes poner presets extra en la lista si agregas sus correspondientes inis
en la carpeta config\presets, el nombre que le pongas a tu ini sera el que
aparezca en la lista de presets (por ejemplo Neo-Joy.ini, aparecera como
Neo-Joy). Puedes usar nombres especificos como "P1 Low Punch" o genericos
como "P1 Fire 1". Cuando un juego busca sus inputs buscara los nombres es-
pecificos primero, despues los genericos, el ejemplo que viene trae solo
genericos (preset-example.ini en el directorio del FB Alpha Plus!).


Tips de uso/optimizacion
------------------------

Video

 - Si el blitter mejorado funciona en tu sistema, usalo, especialmente
   para resoluciones de 32 bit de profundidad, desmarca "Use DirectX
   texture management" para incrementar la velocidad, especialmente si
   usas una tarjeta nVidia.
 - Si el blitter mejorado corre muy lento, presiona alt-enter 2 veces
   para que DirectDraw force a reorganizar la memoria en tu tarjeta de
   video.
 - Si tienes un monitor que puede ser rotado a una orientacion vertical,
   deschequea la opcion "Rotate vertically aligned games", en el menu
   Video, si no tienen la oriantacion correcta checkea "Mirrored vertical
   alignment en las opciones de monitor.
 - Usa "Double size", "triple size", etc. para controlar el tamaño de la
   ventana y la resolucion usada en modo pantalla completa, eso asegurara
   que los juegos se vena igual todos sin que se tengan que configurar cada
   uno por separado.
   Notese que: Para ver algunos juegos al zoom 4x requeriras una resolucion
   mayor que 1600x1200, si puedes agregar resoluciones personalizadas a tu
   tarjeta de video 1712x1284 es una buena opcion. A resoluciones altas, los
   efectos RGB y el triple-buffer requieren muchas cantidades de memoria, no
   podras usarlas las dos al mismo tiempo si tu targeta no tiene por lo menos
   64MB de videoRAM 
 - Si pones resoluciones personalizadas a tu tarjta de video, puedes decirle
   a FB Alpha Plus! que use las mismas resoluciones que el juego original usa
   Para hacer esto selecciona "Arcade" en el submenu de "Full screen resolu-
   tion", carga un juego y presiona alt-enter, si falla FB Alpha Plus! lo re-
   portara y te dira que resolucion necesitas para que se vea el juego.

Sonido

 - Para mejor calidad de sonido habilita las interpolaciones de 4 puntos
   normal y FM.
 - Si tienes una PC realmente lenta, pon los samplerates a 22050 o 11025 y
   deshabilita la interpolacion FM.

Controles

 - Si la sensibilidad del mouse no te agrada, puedes cambiarlo por cada juego
   en su ini correspondiente localizado en config\games, la etiqueta es "analog"
   y el default es 0x100 (256 en Hexadecimal). Usa valores mayores para mayor
   velocidad, y menores para mas lento.
 - Si deshabilitas "Auto-save input mapping" todos los juegos tendran sus inputs
   configurados de acuerdo al preset actual.
 - Para juegos que tengan controles muy dificiles, es recomendable usar un Joystick
   o JoyPad.

Miscelaneos

 - Puedes configurar hasta 8 directorios para ROMs en FB Alpha Plus!
 - Puedes grabar videos en formato AVI si usal la opcion "Record AVI"
   en el menu "Game".
 - Puedes habilitar modo turbo si eliges la opcion "Enable turbo mode"
   en el menu "Game".
 - FB Alpha Plus! puede crear tarjetas de memoria para Neo-Geo como el
   FB Alpha.
 - Puedes jugar hacks de juegos que no esten en la lista (ej. kof2002
   remix ultra by jason), tan solo usa los parches IPS que MAME Plus!
   utiliza y coloca la carpeta del juego en la carpeta ips de FB Alpha
   Plus!, cuando cargues un juego en lugar de cargar normalmente, tan
   solo da click derecho al juego que dispone de IPSs y elije el hack
   de tu preferencia.
 - Puedes editar las macros por default que usa FB Alpha Plus!, leete
   el archivo howtomacro.txt para que aprendas como agregar macros al
   macros.dat localizado en la carpeta config\macros.
 - Puedes cambiar el fondo con el que FB Alpha Plus! inicia, tan solo
   pon una imagen .bmp de 32bits con una resolucion similar a la que
   usan los juegos soportados por FB Alpha Plus! (Ej. 304x224), y edita
   el szPlaceHolder en config\fbaap.ini o cargalo desde el menu .:[Misc]:.
 - Puedes usar varias versiones de FB Alpha Plus! y de FB Alpha en el mismo
   directorio, solo renombra el otro exe a como tu quieras, sus configura-
   ciones se guardaran en un ini con el mismo nombre, de cualquier manera
   no es muy recomendable dado que pueden darse problemas con los juegos.
 - Si quieres resetar a los settings por default, borra el fbaap.ini o el
   directorio config.
 - Para esconder el menu y la barra de titulo puedes dar click derecho o
   ctrl-enter, aun asi puedes mover la ventana clickenado en X zona.
 - Puedes seleccionar "associate with .fs and .fr extensions" para asociar
   FB Alpha Plus! con los rec-inputs o configuraciones de juegos, y poderles
   dar dloble click para llamar a FB Alpha Plus! automaticamente, tambien
   puedes desasociarlos con "disassociate from .fs and .fr extensions" para
   que los registros se borren.
 - Puedes aun usar savestates normalmente usando los slots via dialogo o
   con doble-click-
 - Hay algunas combinaciones no presentes en el menu de FB Alpha Plus!, estas
   son:
   Escape	Regresar a modo ventana.
   F1		Cuando esta en modo pausa, avanza frame por frame, si no
		habilita el modo turbo
   ALT + -	Sube el volumen
   ALT + +	Baja el volumen
   backspace	Saca el dialogo de Frames x segundo o lo quita
   T		Chat en pantalla (solo netplay)
   Shift + F12  Guarda Previews
   Combianciones INGAME:
   F2		(Para algunos juegos) Entra a la configuracion del BIOS
   F3		Resetea el juego actual.


Bugs o problemas de uso [FAQ]
-----------------------------

FB Alpha Plus! no es un emulador perfecto, si encuentran algun bug reportenlo al
E-Mail proporcionado al principio de este readme. A continuacion un mini-FAQ para
resolver algunos posibles inconvenientes.

 1.- No me aparece nada en mi lista de juegos y ya configure los directorios... ¿Que
     hice mal?
 R.- Al parecer, o no tienes la BIOS correcta para FB Alpha Plus! (en el caso de la
     Neo-Geo) o te faltan ROMs, tambien es posible que configuraras mal tus directo-
     rios, checa que tengan \ al final siempre, de lo contrario FB Alpha Plus! no
     podra leerlos, recuerda crear un dat de RomCenter o ClrMAMEPro para ver si tus
     ROMsets estan bien.
 2.- Que raro... me sale un signo de prohibido en azul en algunos juegos de Neo-Geo
     ¿Por que sera?
 R.- Posiblemente te falte alguna BIOS opcional que FB Alpha Plus! necesita, de todas
     formas el juego cargara sin problemas aun no teniendo mas que la BIOS basica.
 3.- Mhhh... no puedo configurar ninguna macro...
 R.- ¿Estas seguro de que en el directorio config\macros tienes el macros.dat?, tam-
     bien revisa si habilitaste "Enable game input macros" en el menu ".:[Misc]:.".
 4.- ¿Como pongo una macro? no tengo ni la mas remota idea...
 R.- Leete el howtomacro.txt incluido con FB Alpha Plus!
 5.- La opcion de parchar ROMs con IPS parece no funcionar...
 R.- Te aseguraste de tener una carpeta con el nombre del zip del juego en cuestion
     (como en MAME Plus!)... ¿Verdad?
 6.- Vaya... cambie una ROM por otra, y desmarque la casilla de "Disable CRC cheking"
     ¿Por que aun asi no me reconoce mi juego?
 R.- ¿Esa ROM que pusiste tiene el mismo nombre que la anterior... verdad?
 7.- Algunos juegos parecen no funcionar si desmarco "Disable CRC cheking"
 R.- Varios juegos poseen algun tipo de proteccion, por ejemplo despues de kof97 co-
     menzaron a salir juegos con el programa protegido por algun bankswitch simple
     (kof98), o protecciones diversas que van desde la Proteccion Neo-SMA SNK 1999
     (garou, kof99, kof2000, mslug3) y aparte encriptacion en los graficos (CMC45 o
     CMC50). Otros pueden tener tambien protecciones mas elaboradas como la Neo-PVC
     PLAYMORE 2002, hasta protecciones simples como la de svcboot o similares, en
     cualquier caso, si tratas de ponerle a algun ROMset con proteccion alguna
     ROM desencriptada, muy posiblemente no funcione, a continuacion una lista de
     juegos con protecciones soportados por FB Alpha Plus! por referencia:
	- (The King of Fighters '98 - the slugfest) kof98, kof98k.
	- (The King of Fighters '99 - millenium battle) kof99, kof99a, kof99e.
	- (Garou - mark of the wolves) garou, garoun, garouo.
	- (Metal Slug 3) mslug3.
	- (The King of Fghters 2000) kof2000.
	- (The King of Fighters 2002 - challenge to ultimate battle) kof2002,
	  kof2k2nd, kof2002b, kf2k2pls, kf2k2pla, kf2k4spe, kf2k4spl, kof10th.
	- (Shin Gouketsuju Ichizoku - Toukon) matrim, matrimnd, matrimbl.
 8.- Parece que los cheats no funcionan y antes si se podian usar... ¿Por que?
 R.- El formato de los cheats para FB Alpha Plus! (y para FB Alpha) han cambiado,
     por lo que ahora solo los lee en formato INI, asegurate de tener un pack de
     cheats actualizado (hay uno en la pagina del FB Alpha Plus!).
 9.- Hay juegos que tienen una marca gris... ¿Que con ellos?
 R.- Esos juegos no funcionan por que o tienen una poteccion no emulada aun o les
     falta alguna parte vital que no se ha dumpeado. Puedes cargarlos, pero te saldra
     una advertencia, aparte de que podria no funcionar (por eso tiene esa etiqueta XD).


Agradecimientos:
----------------

Gracias a: Jan, Dave, ElSemi, Gangta, OG, Razoola, Logiqx, TRAC, CrashTest,
           Andrea Mazzoleni, Derek Liauw Kie Fa, Dirk Stevens, Maxim Stepin,
           the MAME team, Shawn and Craig at XGaming.

Tambien a: IQ_132, BDiamond, bms888, stg, evilS0u, BlackJack, James33, TerryXP
	   Rock Bogard, HalRin, fataku, Wesker, JImmy_Page, Vorador, sabrinor,
	   emufan, Salvador (Uno de mis mejores testers XD) y a quien haya
	   olvidado :).

Gracias tambien a cualquiera que hace sugerencias o ayuda de alguna forma :).
