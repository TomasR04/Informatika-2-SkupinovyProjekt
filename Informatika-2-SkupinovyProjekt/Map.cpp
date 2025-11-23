#include "Map.h"
#include "Controls.h"

#include <string>
#include <iostream>
#include <utility>

using namespace std;

vector<vector<string>> Map::mainMap = {
    {"🌲", "🌲", "🌱", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲"},
    {"🌲", "🌲", "🌱", "🌱", "🍺", "🌲", "🌲", "🌲", "🌲", "🌲", "🏰", "🌲"},
    {"🌲", "🌱", " ○ ", "👣", "🏠", "👣", "👣", "👣", "🌱", "🌲", "🌲", "🌲"},
    {"🌲", "🌱", "🌱", "👣", "👣", "🌱", "🌱", "🌲", "🌲", "🌲", "🌱", "🌲"},
    {"🌲", "🌲", "🌲", "🌲", "👣", "🌲", "🌱", "🌲", "🌲", "🌱", "🌱", "🌲"},
    {"🌲", "🌱", "🌲", "🌲", "👣", "👣", "👣", "👣", "👣", "🌱", "🌱", "🌲"},
    {"🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌱", "👣", "🏠", "🍺", "🏠", "🌲"},
    {"🌱", "🌲", "🌲", "🌲", "🌲", "🌱", "🌲", "👣", "🌱", "🏠", "🌲", "🌲"},
    {"🌲", "🌲", "🌱", "🌲", "🌲", "👣", "👣", "👣", "🌲", "🌲", "🌲", "🌲"},
    {"🌱", "🏠", "🍺", "🌱", "🌲", "👣", "🌱", "🌲", "🌲", "🌲", "🌲", "🌲"},
    {"🏠", "🏰", "🏠", "👣", "👣", "👣", "🌲", "🌲", "🌱", "🌲", "🕳️", "🌲"},
    {"🌱", "🏠", "🏠", "🌱", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲", "🌲"},
};

/*
    Legenda k mape:
    - 🌲 = les
    - 🌱 = plan
    - 👣 = cesta
    - 🍺 = hospoda
    - 🏰 = hrad
    - 🏠 = mesto
    - ○ = spawn
    - ● = hrac
    - 🕳️ = podzemi

    asi jeste pridam někam vstup do podzemí kde bude dalsi mapa
*/

vector<vector<string>> Map::castleOneMap = {
    {" # ", "👣", "👣", " B ", "👣", "👣", "📦"},
    {" # ", "👣", " # ", " # ", " # ", " # ", " # "},
    {" # ", " E ", "👣", "👣", "👣", " E ", "👣"},
    {" # ", " #", " # ", "⚠️", " # ", " # ", "👣"},
    {" # ", "👣", "👣", " E ", "👣", "👣", "👣"},
    {" # ", "📦", " # ", "👣", " # ", " # ", " # "},
    {" # ", " # ", " # ", "🚪", " # ", " # ", " # "}};

/*
    - # = zed
    - 👣 = cesta
    - E = nepritel
    - B = hlavni nepritel
    - 📦 = loot
    - ⚠️ = past
    - 🚪 = vstup/vystup
*/

vector<vector<string>> Map::dungeon = {
    {" # ", " # ", " # ", " # ", " # ", " # ", " # ", " # ", " # ", " # "},
    {" # ", " E ", "👣", "👣", "📦", "👣", "👣", "👣", " B ", " # "},
    {" # ", "👣", " # ", " # ", "👣", " # ", " # ", "📦", "👣", " # "},
    {" # ", "👣", "⚠️", "👣", "👣", "👣", " # ", "👣", "⚠️", " # "},
    {" # ", " E ", " # ", "👣", " # ", "⚠️", " # ", " # ", "👣", " # "},
    {" # ", "👣", "👣", "👣", " # ", "👣", " E ", "⚠️", "👣", " # "},
    {" # ", "👣", " # ", " E ", "👣", "👣", "👣", " # ", "👣", " # "},
    {" # ", "⚠️", " # ", " # ", " # ", " # ", "👣", " # ", "👣", " # "},
    {" # ", "👣", "📦", "👣", " E ", "👣", "👣", "👣", "👣", " # "},
    {" # ", " # ", " # ", " # ", " # ", " # ", "🚪", " # ", " # ", " # "}};

// defaultní mapa
vector<vector<string>> Map::currentMap = Map::mainMap;

vector<vector<string>> Map::getCurrentMap()
{
    return Map::currentMap;
}

pair<int, int> Map::getMapSize()
{
    vector<vector<string>> current = Map::getCurrentMap();

    return {current[0].size(), current.size()};
}

vector<vector<string>> Map::getMapByName(string mapName)
{
    if (mapName == "main")
    {
        return Map::mainMap;
    }

    if (mapName == "castleOneMap")
    {
        return Map::castleOneMap;
    }

    if (mapName == "dungeon")
    {
        return Map::dungeon;
    }

    // default
    cerr << "MAP WITH NAME: " << mapName << " NOT FOUND!";
    return Map::mainMap;
}

/*
if posX and posY aren't passed as arguments current position will be used
same with mapName
 */
string *Map::getTileInfo(int posX = -1, int posY = -1, string mapName = "")
{
    vector<vector<string>> selectedMap = Map::getCurrentMap();

    if (!mapName.empty())
    {
        selectedMap = Map::getMapByName(mapName);
    }

    string *selectedTile;

    if (posX >= 0 && posY >= 0)
    {
        selectedTile = &selectedMap[posY][posX];
    }
    else
    {
        auto position = Controls::getPosition();

        int positionX = position.first;
        int positionY = position.second;

        selectedTile = &selectedMap[positionY][positionX];
    }

    return selectedTile;
}

void Map::setMap(string mapName)
{
    Map::currentMap = getMapByName(mapName);
}

void Map::checkTile(int positionX = -1, int positionY = -1, int beforeX = -1, int beforeY = -1)
{
    auto position = Controls::getPosition();

    int currentX = position.first;
    int currentY = position.second;

    if (positionX <= -1)
    {
        positionX = currentX;
    }

    if (positionY <= -1) {
        positionY = currentY;
    }

    string tileInfo = *getTileInfo(positionX, positionY);

    if (tileInfo == "🏰")
    {
        Map::setMap("castleOneMap");
    }

    if (tileInfo == "🕳️")
    {
        Map::setMap("dungeon");
    }

    if (tileInfo == "🚪")
    {
        Map::setMap("main");
    }

    if (tileInfo == "#") {
        if (beforeX >= 0) {
            Controls::changePosition(beforeX, positionY);
        }
        if (beforeY >= 0) {
            Controls::changePosition(positionX, beforeY);
        }
    }
}
// TBD
// string castletwomap[][] =
//??string forest??
//??string plains??