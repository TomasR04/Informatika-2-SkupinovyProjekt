#pragma once

#include <iostream>
#include <utility>

using namespace std;

class Controls {
    private:
        static int x;
        static int y;
    public:
        Controls();
        
        static void moveUp();
        static void moveDown();
        static void moveLeft();
        static void moveRight();
        static pair<int, int> getPosition();
};