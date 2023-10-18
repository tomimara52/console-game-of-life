https://github.com/tomimara52/console-game-of-life/assets/67428296/450a3604-1585-4488-9070-2bd471aa15d1

# Compilation
  `gcc -O3 src/main.c src/game.c -o main`

# Usage
## Create initial set up from file
  `./main <name-of-file>`

  It then lets you add or remove cells.

## Start with empty board
  `./main`

  Then you can add or remove cells interactively.

## Controls
### Editing mode
  When the program first starts you are in editing mode. You can use `wasd` to
move the cursor and press `SPACE` to switch the state of the current cell.
To start the simulation press `r`.

### Run mode
  Here you can press `p` to pause the game and then press `n` to advance the
simulation one step at a time. Press `q` at any time to exit the program.


 ## File format
  The format of the files to read the inital set up is the following:

```
<x dimension of board>x<y dimension of board>
<x pos of live cell>,<y pos of live cell>
<x pos of live cell>,<y pos of live cell>
<x pos of live cell>,<y pos of live cell>
```

  Replace <...> with actual numbers. You can see the example `gosper-gun.txt`.
