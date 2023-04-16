# Project Title

A 2D Level editor utilizing imGUI and SFML in c++

## Table of Contents

- [Installation](#installation)
- [Instructions](#instructions)
- [Demo](#demo)
- [Code Overview](#code)

## Installation
- clone the repository
- install sfml for linux https://www.sfml-dev.org/tutorials/2.5/start-linux.php
- Run the command “make all”

The repository includes all code for imGUI and imGUI-sfml in the ./include folder. For more information refer to:
https://github.com/ocornut/imgui
https://github.com/SFML/imgui-sfml


## Instructions
- Open the application with ./main.exe
- Add your Sprite Sheet into the ./images folder
- Enter FileName.png in the filename field
- Enter 32 in the tile size field and click the Import button 
- Select a tile from the grid by left clicking
- Left click anywhere on the grid spaces, the tile should be drawn over the background
- Create a game world using the tile set!
- Enter ExportFileName.png in the export filename field
- Click the Export button 
- Close the application and open the exported file to check your world 

## Demo
- Initial Engine Window
- Adding SpriteSheet Information
- Selecting Tile to Draw
- Exporting Image

## Code
**Application.cpp**
- runs the applications main loop. The game loop calls helper methods to handle user input, gui rendering, and drawing to the SFML window. The Application object stores a Board and SpriteSheet class as member variables. 

**Board.cpp**
- Represents the background of the SFML drawable window. Given dimensions and tile width, it creates a Vertex Array. Board is a SFML::Drawable object which allows the Application loop to call window.draw(board). Every loop the Application class draws the Boards vertex array displaying a background grid. 

**SpriteSheet.cpp**
- Stores the ImageTexture of the sprite sheet and the tiles drawn to the board. Given a filepath the class will attempt to use SFML texture import methods. Stores a vector of integers to keep track of tiles drawn to the world. Each tile of the spritesheet is represented by an integer index. When the mouse is clicked, SpriteSheet is given the coordinates and determines the position of the tile in the vector and updates its value to the given tile value. The SpriteSheet class then creates a VertexArray that maps textures to each tile based on the vector's indexes. 


