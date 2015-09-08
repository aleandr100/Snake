# Qt online snake [![Build Status](https://travis-ci.org/angular/material.svg)](https://github.com/aleandr100/Snake)

[Snake](https://github.com/aleandr100/Snake) Snake game written in C ++ is an analog of the original Snake with the possibility of playing between two people.
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

Main window:
![main_window](https://raw.githubusercontent.com/aleandr100/Snake/master/resources/main_window.png)

This project is in early pre-release. Angular Material is both a reference implementation of
Material Design and a complementary effort to the [Polymer](https://www.polymer-project.org/)
project's [Paper Elements](https://www.polymer-project.org/docs/elements/paper-elements.html)
collection.

Quick Links:

*  [API & Demos](#demos)
*  [Contributing](#contributing)
*  [Building](#building)
*  [Installing](#installing)


Please note that using Angular Material requires the use of **Angular 1.3.x** or higher. Angular
Material is targeted for all browsers with versions n-1; where n is the current browser version.

## <a name="demos"></a> Online Documentation (and Demos)

<div style="border: 1px solid #ccc">
  <img src="https://cloud.githubusercontent.com/assets/1045233/6678772/12afad78-cbfc-11e4-8c9f-a13e336fb6a6.png" alt="Angular Material docs website" style="display:block;">
</div>

- Visit [Material.AngularJS.org](https://material.angularjs.org/) online to review the API, see the
  components in action with live Demos, and study the Layout system.
- Or you can build the documentation and demos locally; see
  [Build Docs & Demos](https://github.com/angular/material/tree/master/docs/README.md) for details.

## <a name="contributing"></a> Contributing

Developers interested in contributing should read the following guidelines:

- [Issue Guidelines](docs/guides/CONTRIBUTING.md#submit)
- [Contributing Guidelines](docs/guides/CONTRIBUTING.md)
- [Coding Guidelines](docs/guides/CODING.md)
- [ChangeLog](CHANGELOG.md)

> Please do **not** ask general questions in an issue. Issues are only to report bugs, request
  enhancements, or request new features. For general questions and discussions, use the
  [Angular Material Forum](https://groups.google.com/forum/#!forum/ngmaterial).

It is important to note that for each release, the [ChangeLog](CHANGELOG.md) is a resource that will
itemize all:

- Bug Fixes
- New Features
- Breaking Changes

## <a name="building"></a> Building

Developers can easily build Angular Material using NPM and gulp.

* [Builds - Under the Hood](docs/guides/BUILD.md)

First install or update your local project's **npm** tools:

```bash
# First install all the NPM tools:
npm install

# Or update
npm update
```

Then run the **gulp** tasks:

```bash
# To build `angular-material.js/.css` and `Theme` files in the `/dist` directory
gulp build

# To build the Angular Material Docs and Demos in `/dist/docs` directory
gulp docs
```

For more details on how the build process works and additional commands (available for testing and
debugging) developers should read the [Build Instructions](docs/guides/BUILD.md).

## <a name="installing"></a> Installing Build (Distribution Files)

#### Bower

For developers not interested in building the Angular Material library... use **bower** to install
and use the Angular Material distribution files.

Change to your project's root directory.

```bash
# To get the latest stable version, use Bower from the command line.
bower install angular-material

# To get the most recent, latest committed-to-master version use:
bower install angular-material#master
```

Visit [Bower-Material](https://github.com/angular/bower-material/blob/master/README.md) for more
details on how to install and use the Angular Material distribution files within your own local
project.

#### CDN

CDN versions of Angular Material are now available at
[Google Hosted Libraries](https://developers.google.com/speed/libraries/#angular-material).

With the Google CDN, you will not need to download local copies of the distribution files. Instead
simply reference the CDN urls to easily use those remote library files. This is especially useful
when using online tools such as [CodePen](http://codepen.io/), [Plunkr](http://plnkr.co/), or
[JSFiddle](http://jsfiddle.net/).

```html
  <head>

    <!-- Angular Material CSS now available via Google CDN; version 0.10 used here -->
    <link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/angular_material/0.10.0/angular-material.min.css">

  </head>
  <body>

    <!-- Angular Material Dependencies -->
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular-animate.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular-aria.min.js"></script>


    <!-- Angular Material Javascript now available via Google CDN; version 0.10 used here -->
    <script src="https://ajax.googleapis.com/ajax/libs/angular_material/0.10.0/angular-material.min.js"></script>
  </body>
```

> Note that the above sample references the 0.10.0 CDN release. Your version will change based on the latest stable release version.

Developers seeking the latest, most-current build versions can use [GitCDN.xyz](//gitcdn.xyz) to
pull directly from the distribution GitHub
[Bower-Material](https://github.com/angular/bower-material) repository:

```html
  <head>

    <!-- Angular Material CSS using GitCDN to load directly from `bower-material/master` -->
    <link rel="stylesheet" href="https://gitcdn.xyz/repo/angular/bower-material/master/angular-material.css">

  </head>
  <body>

    <!-- Angular Material Dependencies -->
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular-animate.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.3.15/angular-aria.js"></script>

    <!-- Angular Material Javascript using GitCDN to load directly from `bower-material/master` -->
    <script src="https://gitcdn.xyz/repo/angular/bower-material/master/angular-material.js"></script>

  </body>
```

