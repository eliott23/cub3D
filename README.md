# Ray-Casting

This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way.

## Description

### General

  A 3D basic game engine, the recipe is pure C,  [minilibx](https://harm-smits.github.io/42docs/libs/minilibx): a graphics api as its a requirement of the 42 subject to work with this particular library.The graphics are implemented using [ray-casting](https://en.wikipedia.org/wiki/Ray_casting).

### Performance optimizations : DDR algorithm

  Instead of checking every point of the ray (and we have  many of them forming the FOF) reaches an obstacle so it renders on the screen, AND since we can only possibly find an obstacle while cutting a lane from the grid map, we can use some math to determine only the necessary points to be checked for obstacles in the map.
  
  ![alt text](https://github.com/walywest/Cub3D/blob/master/raycasthit-0000.jpg)

## requirements :

  - [minilibx](https://harm-smits.github.io/42docs/libs/minilibx).

## Usage :

  The program's only parameter is the map file, it will be parsed, should contain other informations and should be named *.cub. Controls are pretty intuitive to figure out (reagular w,a,s,d + right and left buttons);

## Parameters : Example of a map file ==>

  ![alt text](https://github.com/walywest/Cub3D/blob/master/cub3d/mapexample_cub3d.png)

- C --> ceiling RGB color.
- F --> floor RGB color.
- SO EA NO WE respectively south, east, north abd west wall textures (followed by path to xpm).

  As you can see the map is formed by 1 and 0, 1 are obstacles and 0 is empty spaces. be nice and **make sure the map is closed so you don't fall into another spooky digital dimension**.

# Enjoy the maze!
  Enjoy the maze.

