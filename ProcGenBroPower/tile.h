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
class Tile
{
public:
    Tile();
    void setPosition(float x, float y);
    float getPosx();
    float getPosY();
private:
    float _posX;     // X position of a tile
    float _posY;     // Y position of a tile
    double _length;   // Length of a tile
    double _breadth;  // Breadth of a tile
    double _height;   // Height of a tile
};

#endif /* defined(__opengl__Tile__) */
