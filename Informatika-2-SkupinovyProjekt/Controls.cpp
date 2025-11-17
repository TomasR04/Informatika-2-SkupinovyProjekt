#include "Controls.h"
#include <iostream>
#include <utility>

using namespace std;

// key X or arrow Up
void Controls::moveUp() { 
    y--;
}

// key S or arrow down
void Controls::moveDown() {
    y++;
}

// key A or arrow left
void Controls::moveLeft() {
    x--;
} 

// key D or arrow right
void Controls::moveRight() {
    x++;
}

/*

auto position = controls.getPosition();

int positionX = position.first;
int positionY = position.second;

*/
pair<int, int> Controls::getPosition() {
    return {x, y};
}

