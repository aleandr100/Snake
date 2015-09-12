# Qt online snake [![Build Status](https://travis-ci.org/angular/material.svg)](https://github.com/aleandr100/Snake)

[Snake](https://en.wikipedia.org/wiki/Snake_%28video_game%29) Snake game written in C ++ is an analog of the original Snake with the possibility of playing between two people.
Rules:
- On the field at the same time moving the two snakes (one for the player, the initial length of the snake - 3 square), the player controls only the snake turns, the speed of both snakes is always the same;
- On the field there are two squares that give the snakes food; if the snake eats a box (Chairman snake falls on it), its length is increased by 1;
- As soon as the snake eats a box, the box disappears and the second on the back appear in random places two squares (squares appear in the same places, ie, can not appear inside the snakes)
- The speed of snakes, depending on the choice of the player that you create a game
- Snake can eat the tip of the tail of the snake-rival, while the snake becomes longer by 1, and the snake-competitor shorter by 1;
- Snake can eat "neck" (the dice right behind his head) snake-competitor, then it wins;
- The purpose of the game - to collect a length that is specified when creating the game (minimum - 15);
- If the two snakes at the same time gain the necessary length, the game continues until one of the snakes will not be long;
- If a snake crashes into the edge of the playing field, it automatically loses;
- If the snake bumps into itself, or into another snake (except eaten tail or "neck" other snakes), from its length subtracted the value of the penalty (specified when creating the game), and is compared with the length of the snake-competitor who has more, he also won.

![main window](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/main_window.png)

Quick Links:

*  [Demos](#demos)
*  [Building](#building)
*  [Installing](#installing)

> Please note that using "Qt Snake" requires the use of **Qt 4.8.x** or higher. Qt
  Snake is targeted for all platforms with support "OpenGL".

## <a name="demos"></a> Demos
**During the game**
![during the game](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/during_the_game.png)

- First screen during the game
- Two snakes with size 7 (blue) and 8 (pink)

**Out of the abord**
![out of the abord](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/out_of_the_abroad.png)

- The pink snake out of the border and lose 

**On max size**
![on max size](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/on_max_size.png)

- The blue snake reached victorious length and win

**Collision**
![collision](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/collision.png)

- The blue snake bite in the body (not in neck and not in tail)
- End of game the pink snake is win

**Bite in the neck**
![bite in the neck](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/bite_in_the_neck.png)

- The pink snake bite in the neck and win

**Bite in the body**
![bite in the body](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/bite_in_the_body.png)

- The pink snake bite yourself, she got a fine and compare the size with rival
- The pink snake is win

## <a name="building"></a> Building

#### Linux:
(At first start the console and go to the folder with the project)
```
cd Snake/client/
#There is your path to qmake
/home/maxim/Qt5.5.0/5.5/gcc_64/bin/qmake -project
/home/maxim/Qt5.5.0/5.5/gcc_64/bin/qmake client.pro
make
#Well done to build "server"
```
#### Windows:
(If you are using Windows and installed version of Qt Open
source code with the compiler MinGW, you get a shortcut to the window MS-
DOS, in which environment variables are set up correctly on Qt. Calling this window
you can compile it into Qt-applications using the above
Team qmake and make. Generated executables are placed in a folder
debug or release "for example, C:\qt-book\hello\release\hello.exe")
```
dir Snake/client/
qmake -tp vc hello.pro
nmake
```
#### Mac OS X:
(If you are using Xcode on Mac OS X, you can generate an Xcode project using the following command)
```
qmake -spec macx-xcode hello.pro
```

## <a name="installing"></a> Installing

#### Linux
For developers not interested in building the project use **OpenGL** to install
```
#At first library
sudo apt-get install freeglut3-dev
#and compiling (if without qt library)
gcc -o <output file> <input file.cpp> -lglut -lGLU -lGL -lm
```

#### Windows
First of all, download the **GLUT** (**The OpenGL Utility Toolkit**) c the official website:
[OpenGL](https://www.opengl.org/resources/libraries/glut/)

This part will show how to install the glut libraries and dll's (to download it go [http://reality.sgi.com/opengl/glut3/glut3.html](http://reality.sgi.com/opengl/glut3/glut3.html))

1. After you have downloaded the glut.zip file (you should get the latest ver 3.7) unzip it into a folder
2. Inside the folder you should have:
```glut.dll glut32.dll glut.h glut.lib glut32.lib```
3. Copy both **glut.dll** and **glut32.dll** into your windows directory (windows or winnt, depends on if you are using Windows95/98 or Windows NT)
4. Copy your **glut.h** to:
<drive>:\<VC++ path>\include\GL\glut.h
*put the drive where you installed VC++ instead of the <drive>*
*put the directory where you installed VC++ instead of the <VC++ path>*
5. Copy your **glut.lib** and **glut32.lib** to:
<drive>:\<VC++ path>\lib\glut.lib
<drive>:\<VC++ path>\lib\glut32.lib
*put the drive where you installed VC++ instead of the <drive>*
*put the directory where you installed VC++ instead of the <VC++ path>*
6. That should be it for installed the glut libraries. The rest of this letter shows you how to setup VC++ so that you can use the glut libraries.
This will show you how to start up an opengl project and setup the setting so that you will be able to compile and run the program. This is assuming that you have already downloaded the appropriatefiles and installed them in the directories that there documentation tell you to. If you have not done that you need to do it before you can run or write an opengl program.

7. Start VC++ and create a new project.
8. The project has to be a "Win32 Console Application"
9. Type in the name of the project and where it will be on your hard drive.
10. Chose an empty project and click next or finish
11. First thing you need to do when the project opens up is to click on the "Project" menu item from the top.
12. Chose "Settings" (a window will come up)
13. On the left side of the window there are tabs, chose the "Link" tab
14. The string field labeled "Object/library modules" has a few lib files already set in it
15. Go to the end of this string field and enter:
``` opengl32.lib glut32.lib glu32.lib ```
16. Chose "OK" and that will include all the opengl libraries that you need
17. Now all you need to do is include <gl\glut.h> and you are ready to go