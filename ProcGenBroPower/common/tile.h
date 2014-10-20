//
//  Tile.h
//  opengl
//
//  Created by Bert Bosch on 15-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#ifndef __opengl__Tile__
#define __opengl__Tile__

#include <iostream>
#include <GLUT/GLUT.h>
class Tile
{
public:
    Tile();
    void setPosition(float x, float y);
    float getPosX();
    float getPosY();
    int getSpriteSheet();
    void setTexture(GLuint texture,float sheetPosX, float sheetPosY,float sheetWitdh,float sheetHeight);
    void draw();
private:
    float _posX;        // X position of a tile
    float _posY;        // Y position of a tile
    double _length;     // Length of a tile
    double _width;    // Breadth of a tile
    double _height;     // Height of a tile
    float _sheetPosX;   // SheetPosX of the texture
    float _sheetPosY;   //SheetPosy of the texture
    float _sheetWitdh;  //Witdh of the texture
    float _sheetHeight; //Height of the texture
    int _spriteSheet;
    GLuint _texture;
};

#endif /* defined(__opengl__Tile__) */
