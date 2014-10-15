//
//  Tile.cpp
//  opengl
//
//  Created by Bert Bosch on 15-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "tile.h"

Tile::Tile() :
    _posX(0),
    _posY(0),
    _length(1),
    _breadth(1),
    _height(1)
{}

void Tile::setPosition(float x, float y){
    _posX = x;
    _posY = y;
}

float Tile::getPosx(){
    return _posX;
}