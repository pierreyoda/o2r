# Open Rodent's Revenge

C++ remake of the famous Microsoft game "Rodent's Revenge" (1991) made with [Qt][qt], [SFML][sfml] and [MicroPather][micropather].

Please note that this project is incomplete and outdated, but anyone is welcome to build upon it.


## Screenshots (0.7)
![Open Rodent's Revenge 0.7 Gameplay](screens/o2r-0_7.png?raw=true "Open Rodent's Revenge 0.7 Gameplay")
![Open Rodent's Revenge 0.7 Launcher](screens/o2r-launcher-0_7.png?raw=true "Open Rodent's Revenge 0.7 Launcher")


## Features (0.7)
- Same gameplay as the first levels of the original game : you (the mouse) must move blocks around to trap cats which then transform into cheese after a certain amount of time. The cats can move diagonally, and will compute a path to you if one is available (A* algorithm). Otherwise, they will just move around randomly.
- Level editor : place different blocks and the mouse's starting position and save your own levels in a simple text file.
- Levels of any size (within reasonable limits) with sprites rescaling or dynamic screen size (launcher option).
- "Modding" system : replace any sprite with a new one and combine your modification with others ; the loading order will determine which file to use.
- Game launcher : a simple launcher that can be used to configure a game or a level editing session (uses the command line arguments internally). You can also choose different mods to use with convenient priority reordering. Your options will be remembered.
- Tiled Map batch rendering for better performance (one drawing call for each sprite type).

## History
The original version (of which 0.7 is the latest iteration) was started in 2010 and consists in two different programs : a launcher made with Qt 4 and the actual game made with SFML 2 and Micropather. Original [sourceforge] project repository.

I started a rewrite for 1.0 but wasn't able to finish it at the time. This version uses Qt 5 and SFML 2 in order to have a single game window.

## Notes

[qt]: https://www.qt.io/
[sfml]: https://www.sfml-dev.org/
[micropather]: http://www.grinninglizard.com/MicroPather/
[sourceforge]: https://sourceforge.net/projects/o2r/?source=typ_redirect
