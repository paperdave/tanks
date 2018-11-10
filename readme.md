# Dave's Tanks (Post-Camp Rewrite)
Shoot Stuff! You have one life to kill other tanks in a fast paced battle arena.

## Build Instructions
1. Grab a copy of [SFML](https://www.sfml-dev.org/download.php), extract it to `\sfml\*`
2. Open Visual Studio Solution
3. *Compiling from CTRL+SHIFT+B Should do the trick*

## Packing final binary
1. Touch pch.h to make sure the date macro is up to date
2. Build in Visual Studio.
3. Run `pack.bat`
4. That will open an extra explorer window of the exported game.