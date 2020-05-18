# Rubik's Cube simulator
Program first reads cube size and then executes commands rotating given layers of specified wall by desirable angle.
It also prints current state of the cube when Enter key is hit.
Simulator accepts commands consisting of 3 parts: wall, number of layers to rotate and rotation angle.

Wall is designated by one of the following letters:

`u` upper wall,

`l` left wall,

`f` front wall,

`r` right wall,

`b` back wall,

`d` down wall.

If number of layers is omitted, then it defaults to 1.
Otherwise, it is positive number not greater than size of the cube.

If angle is omitted, then it defaults to 90 degrees clockwise rotation. Otherwise, it is designated as follows:

`'` 90 degrees counterclockwise rotation,

`"` 180 degrees rotation.

Executing rotation command, with wall `W`, number of layers `L` and angle `A`,
causes simultaneous rotation of `L` layers by angle `A`, looking from the direction of wall `W`.

The cube is printed as follows:

      u 
    l|f|r|b
      d

where `u`, `l`, `f`, `r`, `b`, `d` denote, respectively, walls: upper, left, front, right, back and down.

Walls' stickers are denoted as follows:
 
`0` upper wall sticker,

`1` left wall sticker,

`2` front wall sticker,

`3` right wall sticker,

`4` back wall sticker,

`5` down wall sticker.

For left, front, right and back wall the stickers are printed in the order consistent with the order one would
see if after rotating whole cube, from the direction of upper or down wall, by the multiple of right angle .

For upper and down wall the stickers are printed in the order consistent with the order
one would see after rotating whole cube, from the direction of left or right wall, by the multiple of right angle.

For examples, see `examples` directory.

#### **Use**
In order to use simulator, execute following commands:

`git clone https://github.com/Czyzmanski/Rubik-s-Cube Rubik-s-Cube`

`cd Rubik-s-Cube`

`mkdir release`

`cd release`

`cmake ..`

`make`

`./simulator`
