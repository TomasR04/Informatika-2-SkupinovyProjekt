#include "Controls.h"
#include "Map.h"
#include "Player.h"

#include <iostream>
#include <utility>
#include <string>

using namespace std;

int Controls::x = 0;
int Controls::y = 0;

int Controls::oldX = 0;
int Controls::oldY = 0;

Controls::GameState Controls::gameState = Controls::GameState::TRAVELING;




// key X or arrow Up
void Controls::moveUp()
{
    int beforeY = y;
    if (y > 0)
    {
        y--;
       Map::checkTile(-1, y, -1, beforeY); // -1 means current position
    }
}

// key S or arrow down
void Controls::moveDown()
{
    auto mapSize = Map::getMapSize();
    int maxY = mapSize.second;
	int beforeY = y;
    if (y < (maxY - 1))
    {
        y++;
       Map::checkTile(-1, y, -1, beforeY);
    }
}

// key A or arrow left
void Controls::moveLeft()
{
    int beforeX = x;
    if (x > 0)
    {
        x--;
        Map::checkTile(x, -1, beforeX);
    }
}

// key D or arrow right
void Controls::moveRight()
{
    auto mapSize = Map::getMapSize();
    int maxX = mapSize.first;
	int beforeX = x;

    if (x < (maxX - 1))
    {
        x++;
        Map::checkTile(x, -1, beforeX);
    }
}

/*

auto position = controls.getPosition();

int positionX = position.first;
int positionY = position.second;

*/
pair<int, int> Controls::getPosition()
{
    return {Controls::x, Controls::y};
}

void Controls::changePosition(int positionX, int positionY) {
    Controls::x = positionX;
    Controls::y = positionY;
}
void Controls::updatePosition() {
	Map::checkTile(Controls::x, Controls::y, Controls::oldX, Controls::oldY);

}
void savePosition() {
	Controls::oldX = Controls::x;
	Controls::oldY = Controls::y;
}
void Controls::processInput(string input)
{
    /*if (input == "w" || input == "W" || input == "up")
    {
        Controls::moveUp();
        return;
    }

    if (input == "s" || input == "S" || input == "down")
    {
        Controls::moveDown();
        return;
    }

    if (input == "a" || input == "A" || input == "left")
    {
        Controls::moveLeft();
        return;
    }


*/

	if (input == "w" || input == "W")
	{
		savePosition();
		Controls::y--;
		Controls::updatePosition();
		return;
	}
	if (input == "s" || input == "S")
	{
		savePosition();
		Controls::y++;
		Controls::updatePosition();
		return;
	}
	if (input == "a" || input == "A")
	{
		savePosition();
		Controls::x--;
		Controls::updatePosition();
		return;
	}
	if (input == "d" || input == "D")
	{
		savePosition();
		Controls::x++;
		Controls::updatePosition();
		return;
	}

    if (input == "stats") {
		// Display player stats
		cout << "Player Stats:" << endl;
		cout << hranyHrac.toString() << endl;
		cout << "Pro využití itemu zadej èíslo položky. Jinak zadej exit." << endl;
		string itemInput;
		cout << "> ";
		cin >> itemInput;
        if (itemInput == "exit") {
            return;
        }
        else
        {            
            try
            {
				int itemIndex = stoi(itemInput);
				Player::useItem(hranyHrac, itemIndex);
            }
            catch (const std::exception&)
            {
				cout << "Neplatný vstup pro použití itemu." << endl;
            }

        }

        
    }

    if (input == "exit")
    {
        cout << "Exiting the game..." << endl;
        exit(0);
    }
}