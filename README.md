<img align="left" src="ressource/coink_256.png" alt="coink logo">


# CoinkEngine 
Coink is a all-in one engine in an add-on library for the Simple Direct Media (SDL) cross-platform API layer.

In long term my goal is to move Coink from SDL to OpenGL.

See the [WIKI](https://github.com/Nimajjj/Coink/wiki) ! 

<br><br>
## Features
* Basic graphics primitives (line, circle, rect ...)
* Text printing
* Texture
* Sprite animation
* Particles system
* Verlet integration based physics engine
* More comming soon


## Basic exemple
In this exemple a window is created and "Hello Coink!" is print in it.
```c++
#include "engine.h"

int main(int argc, char** argv) {
    Coink("Coink [DEMO] v0.1.1", 1280, 720);

    while (ShouldNotQuit()) {
        LoopBegin();

        Print("Hello Coink!", 0, 0, 32);

        LoopEnd();
    }

    Close();
    return 0;
}
```


## Build - Installation
See the [Getting Started](https://github.com/Nimajjj/Coink/wiki/Getting-Started)


## Version History - Changelogs
* 0.1.1
  * ! Complete update of source code structure
  * ! Update project files structure
  * Begin verlet integration physics
  * Add ./exemples directory
  * Add first exemple : verlet integration cloth simulation
  * Add ./dependencies directory which contain .dll files

  

* 0.1.0
    * Initial Release
    * Shapes drawing
    * Images drawing
    * Basic object motion
    * Limited framerate
    * Basic particles system [WIP]
    * GUI class set up
    * First functionall button


## License
This project is licensed under the MIT License - see the LICENSE.md file for details

Made with ❤️