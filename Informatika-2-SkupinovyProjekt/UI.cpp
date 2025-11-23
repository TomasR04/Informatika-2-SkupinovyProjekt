#include "UI.h"
#include "Map.h"
#include "Controls.h"

#include <iostream>

using namespace std;

string symbolPlayer = "●";

void UI::showMap()
{
    vector<vector<string>> currentMap = Map::getCurrentMap();

    for (int r = 0; r < currentMap.size(); r++)
    {
        for (int c = 0; c < currentMap[r].size(); c++)
        {
            auto position = Controls::getPosition();
            int positionX = position.first;
            int positionY = position.second;

            string tile = currentMap[c][r];

            if (r == positionY && c == positionX) {
                tile = symbolPlayer;
            }

            cout << tile;
        }
        cout << endl;
    }
}