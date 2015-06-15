# Snake
Simple terminal-based snake game, written in C with the help of the ncurses library

## "Installing"
Make sure you have ```ncurses``` installed on your system, as well as ```gcc```.

*ncurses* can be installed via:

| Distro         | Installation command                 |
| -------------- | ---------------------------------    |
| Ubuntu/Debian  | `$ apt-get install libncurses5-dev`  |
| Fedora         | `$ yum install ncurses-devel`        |
| Arch Linux     | _comes by default in_ `base-devel`   |
| OS X           | `$ brew tap homebrew/dupes`<br>`$ brew link ncurses --force`        |

Then, run:
```
$ make
$ ./snake
```

And you should be good to go.

Note: If you do not use or want to use the gcc compiler, feel free to compile it yourself.

## Game
Controls are fairly simple. Up, down, left and right arrow keys to move the snake,
q to quit the game.

Holding down a directional key speeds up the snake.
