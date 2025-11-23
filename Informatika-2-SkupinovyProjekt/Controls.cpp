#include "Controls.h"
#include "Map.h"

#include <iostream>
#include <utility>

using namespace std;

int Controls::x = 0;
int Controls::y = 0;

// key X or arrow Up
void Controls::moveUp() { 
    if (y > 0) {
        y--;
    }
}

// key S or arrow down
void Controls::moveDown() {
    auto mapSize = Map::getMapSize();
    int maxY = mapSize.second;

    if (y < (maxY - 1)) {
        y++;
    }
}

// key A or arrow left
void Controls::moveLeft() {
    if (x > 0) {
         x--;
    }
} 

// key D or arrow right
void Controls::moveRight() {
    auto mapSize = Map::getMapSize();
    int maxX = mapSize.first;

    if (x < (maxX - 1)) {
        x++;
    }
}

/*

auto position = controls.getPosition();

int positionX = position.first;
int positionY = position.second;

*/
pair<int, int> Controls::getPosition() {
    return {Controls::x, Controls::y};
}

