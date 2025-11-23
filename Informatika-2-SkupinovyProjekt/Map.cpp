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
    auto position = Controls::getPosition();

    int positionX = position.first;
    int positionY = position.second;

    return Map::currentMap;
}

pair<int, int> Map::getMapSize() {
    vector<vector<string>> current = Map::getCurrentMap();

    return { current[0].size(), current.size() };
}

string* Map::getCurrentTile() {
    vector<vector<string>> current = Map::getCurrentMap();

    auto position = Controls::getPosition();

    int positionX = position.first;
    int positionY = position.second;

    return &current[positionY][positionX];
}

void Map::setMap(string mapName) {
   if (mapName == "main") {
        Map::currentMap = Map::mainMap;
   }

   if (mapName == "castleOneMap") {
        Map::currentMap = Map::castleOneMap;
   }

   if (mapName == "dungeon") {
        Map::dungeon = Map::dungeon;
   }
}
// TBD
// string castletwomap[][] =
//??string forest??
//??string plains??