#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Map //�imon
{
    // protože je Šimon línej tak to musím dělat já ;)
    private:
        static vector<vector<string>> mainMap;
        static vector<vector<string>> castleOneMap;
        static vector<vector<string>> dungeon;
        static vector<vector<string>> currentMap;
    public:
        //Map();
        static vector<vector<string>> getCurrentMap();
        static pair<int, int> getMapSize();
        static vector<vector<string>> getMapByName(string mapName);
        static void setMap(string mapName);
        static string getTileInfo(int posX = -1, int posY = -1, string mapName = "");
        static void checkTile(int positionX = -1, int positionY = -1, int beforeX = -1, int beforeY = -1);
		static void overwriteTile(int posX, int posY, string newTile);
};

