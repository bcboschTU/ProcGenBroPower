//
//  level.h
//  opengl
//
//  Created by Bert Bosch on 16-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#ifndef __opengl__level__
#define __opengl__level__

#include <iostream>
#include "tile.h"
#include <vector>
using std::vector;

class Level
{
public:
    Level(int sizeX, int sizeY);
    void setLevelSize(int sizeX, int SizeY);
    int getLevelWidth();
    int getLevelHeight();
    Tile getTile(int x, int y);
    void addTile(Tile tile, int x, int y);
    void draw();
private:
    int _sizeX;
    int _sizeY;
    vector<vector<Tile>> _tiles;
    
};
#endif /* defined(__opengl__level__) */