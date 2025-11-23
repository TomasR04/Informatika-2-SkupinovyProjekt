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
		static void processInput(string input);
        static void moveUp();
        static void moveDown();
        static void moveLeft();
        static void moveRight();
        static void changePosition(int positionX, int positionY);
        static pair<int, int> getPosition();
};