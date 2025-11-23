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
        Map();
        static vector<vector<string>> getCurrentMap();
        static pair<int, int> getMapSize();
        static void setMap(string mapName);
        static string* getCurrentTile();
};

