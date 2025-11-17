#pragma once

#include <iostream>
#include <utility>

using namespace std;

class Controls {
    private:
        int x = 0;
        int y = 0;
    public:
        Controls();
        
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        pair<int, int> getPosition();
};