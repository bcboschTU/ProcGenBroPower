//
//  level.cpp
//  opengl
//
//  Created by Bert Bosch on 16-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "level.h"

Level::Level(int sizeX, int sizeY) :
    _tiles(),
    _sizeX(sizeX),
    _sizeY(sizeY)
{
    setLevelSize(sizeX, sizeY);
};

void Level::setLevelSize(int sizeX, int sizeY){
    _tiles.resize(sizeX);
    for (int i = 0; i < sizeX; ++i)
        _tiles[i].resize(sizeY);
}

Tile Level::getTile(int x, int y){
    return _tiles[x][y];
}

void Level::addTile(Tile tile, int x, int y){
    _tiles[x][y] = tile;
}

int Level::getLevelWidth(){
    return _sizeX;
}
int Level::getLevelHeight(){
    return _sizeY;
}

void Level::draw(){
    for(int i = 0; i<_sizeX; i++){
        for (int j = 0; j<_sizeY; j++) {
            _tiles[i][j].draw();
        }
    }
}