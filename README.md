# Open Rodent's Revenge

C++ remake of the famous Microsoft game "Rodent's Revenge" (1991) made with [Qt][qt], [SFML][sfml] and [MicroPather][micropather].

Download link for the [0.7 version for Windows].


I have absolutely no rights over the original property and multiple alternate sprite sets are included that completely replace the reproduced sprites.


## Screenshots (0.7)
![Open Rodent's Revenge 0.7 Gameplay](screens/o2r-0_7.png?raw=true "Open Rodent's Revenge 0.7 Gameplay")
![Open Rodent's Revenge 0.7 Launcher](screens/o2r-launcher-0_7.png?raw=true "Open Rodent's Revenge 0.7 Launcher")


## Features (0.7)
- Same gameplay as the first levels of the original game : you (the mouse) must move blocks around to trap cats which then transform into cheese after a certain amount of time. The cats can move diagonally, and will compute a path to you if one is available (A* algorithm). Otherwise, they will just move around randomly.
- Level editor : place different blocks and the mouse's starting position and save your own levels in a simple text file.
- Levels of any size (within reasonable limits) with sprites rescaling or dynamic screen size (launcher option).
- "Modding" system : replace any sprite with a new one and combine your modification with others ; the loading order will determine which file to use. You can see an example of such a modification in the gameplay screenshot above where the lives display uses hearts instead of mouses ("zelda" mod). 
- Game launcher : a simple launcher that can be used to configure a game or a level editing session (uses the command line arguments internally). You can also choose different mods to use with convenient priority reordering. Your options will be remembered.
- Tiled Map batch rendering for better performance (one drawing call for each sprite type).

## History
The original version (of which 0.7 is the latest iteration) was developped and released in 2010 and consists in two different programs : a launcher made with Qt 4 and the actual game made with SFML 2 and Micropather. You can download a Linux build or older versions of the game on the original [Sourceforge] project repository. All versions included (mostly 0.6 and 0.7), this game was downloaded more than 40 thousand times.

I started a rewrite for 1.0 but wasn't able to finish it at the time. This version uses Qt 5 and SFML 2 in order to have a single game window. Note that this would most likely make a port to mobile platforms pretty straightforward.

This project is currently incomplete and somewhat outdated (limited modern C++ usage), but anyone is welcome to build upon it.

[0.7 version for Windows]: https://github.com/pierreyoda/o2r/releases/tag/v0.7
[qt]: https://www.qt.io/
[sfml]: https://www.sfml-dev.org/
[micropather]: http://www.grinninglizard.com/MicroPather/
[sourceforge]: https://sourceforge.net/projects/o2r/?source=typ_redirect
