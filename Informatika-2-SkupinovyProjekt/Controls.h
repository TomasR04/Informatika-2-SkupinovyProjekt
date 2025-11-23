#pragma once

#include <iostream>
#include <utility>

using namespace std;

class Controls {
    private:
        
    public:
        Controls();
		static void processInput(string input);
        static void moveUp();
        static void moveDown();
        static void moveLeft();
        static void moveRight();
        static void changePosition(int positionX, int positionY);
        static pair<int, int> getPosition();
		static void updatePosition();
        static int x;
        static int y;
        static int oldX;
        static int oldY;
        static enum GameState {
			TRAVELING,
			FIGHTING,
            TRADING
        };
		static GameState gameState;
};