//
//  Tile.cpp
//  opengl
//
//  Created by Bert Bosch on 15-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "tile.h"

Tile::Tile() :
    _texture(0),
    _posX(0),
    _posY(0),
    _length(1),
    _width(1),
    _height(1)
{}

void Tile::setPosition(float x, float y){
    _posX = x;
    _posY = y;
}

float Tile::getPosX(){
    return _posX;
}

float Tile::getPosY(){
    return _posY;
}

int Tile::getSpriteSheet(){
    return _spriteSheet;
}

void Tile::setTexture(GLuint texture,float sheetPosX, float sheetPosY,float sheetWitdh,float sheetHeight){
    _texture = texture;
    _sheetPosX = sheetPosX;
    _sheetPosY = sheetPosY;
    _sheetWitdh = sheetWitdh;
    _sheetHeight = sheetHeight;
}

void Tile::draw(){
    if(_texture != 0){
        glColor4f(1.f, 1.f, 1.f,1.0f);
        glBegin(GL_QUADS);
        glTexCoord2d( _sheetPosX,  _sheetPosY);
        glVertex2f(_posX,       _posY);
        glTexCoord2d( _sheetPosX + _sheetWitdh,  _sheetPosY);
        glVertex2f(_posX +_width,     _posY);
        glTexCoord2d( _sheetPosX + _sheetWitdh,  _sheetPosY + _sheetHeight);
        glVertex2f(_posX +_width,     _posY+_height);
        glTexCoord2d( _sheetPosX,  _sheetPosY + _sheetHeight);
        glVertex2f(_posX,     _posY + _height);
        glEnd();
    }
}