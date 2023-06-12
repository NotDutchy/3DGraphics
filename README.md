# OpenGL TowerDefense

![GameScreen](/resource/GameScreen.png)

## Description
Concept Towerdefense game made for the 3D-Graphics module for Computer science. Enemies move along the path and its your job to defend against the coming horde!

## Features
 - Fly around and place towers wherever you want.
 - Lightning and shading effects using OpenGL.
 - Keyboard input to move the player.
## Usage
 - Use the AWSD-keys to fly around the world.
 - You can use Leftctrl to fly down and use space to fly up.
 - During buildingphase (When there are no more enemies and none are spawning), press 1 to enter building mode.
 - Whilst in building mode, press return to place the turret on the nearest tile.

## Dependencies
This project uses the following dependencies:
 - OpenGL
 - C++

## Known Bugs
 - Turrets are placeable on top of the path
 - After building 1 turret the building preview stays in the position of the first turret build.

## Requirements

| Criteria                                                                                                                                                                                	| Voldaan 	| Toelichting                                                                                                                            	|
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|---------	|----------------------------------------------------------------------------------------------------------------------------------------	|
| De code bevat geen overbodige #defines en bevat geen magische constanten.                                                                                                               	| x       	| N.V.T.                                                                                                                                 	|
| Gebruik maken van OO-principes in C++, zoals gebruik van klassen met constructors en destructors, polymorfisme en/of inheritance.                                                       	| x       	| Alle classes hebben een constructor en destructor. Component                                                                           	|
| De code gebruikt op ten minste 1 plek op een zinnige wijze van overerving en virtuele functie(s).                                                                                       	| x       	| Component structuur heeft veel overerving.                                                                                             	|
| De code heeft ten minste 1 unit-test waarbij het resultaat in een bestand wordt weggeschreven.                                                                                          	| x       	| PathGeneratorTest Test.cpp Schrijft naar TestResults.txt                                                                               	|
| Met behulp van FileIO, bestanden kunnen lezen en schrijven.                                                                                                                             	| x       	| PathGenerator.cpp Lezen: regel 47-66 Schrijven: 157-165                                                                                	|
| Toepassen van standaard datastructuren in C++.                                                                                                                                          	| x       	| Gebruik gemaakt van EntityComponent structuur.                                                                                         	|
| Gebruik maken van streams.                                                                                                                                                              	| x       	| Fileio maakt gebruik van streams.                                                                                                      	|
| Rekening gehouden met het voorkomen van memory leaks.                                                                                                                                   	| x       	| Gamemanager.cpp Regel: 67                                                                                                              	|
| Zinnige foutmeldingen mocht er iets fout gaan, afhandeling via exceptions                                                                                                               	| x       	| N.V.T.                                                                                                                                 	|
| Gebruik maken van C++ standaard, dus niet op C manier alloceren.                                                                                                                        	| x       	| N.V.T.                                                                                                                                 	|
| Weloverwogen gebruik van algoritmes binnen de applicatie (zowel zelfgeschreven alsmede de STL-bibliotheek).                                                                             	| x       	| Pathgenerator.cpp Regel: 45- 134 Wordt gebruikt om de initiële map te genereren.                                                       	|
| De documentatie bevat een overzichtstabel waarin staat aan welke criteria de code voldoet, en, voor zover zinnig, specifiek welke delen van de code (files en waar nodig regelnummers). 	| x       	| Dit bestand.                                                                                                                           	|
| De applicatie leest gegevens in vanuit een tekst-file naar in-memory data, volgens het factory pattern.                                                                                 	|         	| N.V.T.                                                                                                                                 	|
| Smart pointers.                                                                                                                                                                         	| x       	| Alle gameobjects zijn smart pointers.                                                                                                  	|
| Gebruik maken van Template Metaprogramming                                                                                                                                              	|         	| N.V.T.                                                                                                                                 	|
| Ervoor zorgen dat je programma const, constexpr en override correct is.                                                                                                                 	|         	| N.V.T.                                                                                                                                 	|
| Lambda expressies, denk hierbij ook aan een typedef                                                                                                                                     	| x       	| Gamemanager heeft een lambda expressie voor het verwijderen van objecten uit de gameobject lijst.                                      	|
| Pointer to implementation, scherm een structure of klasse af                                                                                                                            	|         	| N.V.T.                                                                                                                                 	|
| Proxy-patroon: Protection proxy                                                                                                                                                         	|         	| N.V.T.                                                                                                                                 	|
| Nested datatypes                                                                                                                                                                        	| x       	| Pathgenerator maakt gebruik van Cell deze is in pathgenerator.h definieert. Verder gebruikt Obj model natuurlijk ook nested datatypes. 	|
| De code voldoet aantoonbaar aan andere, wenselijke (kwaliteit verhogende) en gespecificeerde criteria                                                                                   	|         	| N.V.T.                                                                                                                                 	|