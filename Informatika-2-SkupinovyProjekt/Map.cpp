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
//fix this :(
vector<vector<string>> Map::castleOneMap = { 
    {"#", "👣", "👣", "B", "👣", "👣", "📦"},
    {"#", "👣", "#", "#", "#", "#", "#"},
    {"#", "E", "👣", "👣", "👣", "E", "👣"},
    {"#", "#", "#", "⚠️", "#", "#", "👣"},
    {"#", "👣", "👣", "E", "👣", "👣", "👣"},
    {"#", "📦", "#", "👣", "#", "#", "#"},
    {"#", "#", "#", "🚪", "#", "#", "#"}};

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

string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos) return ""; // jen whitespace

    return s.substr(start, end - start + 1);
}

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
string Map::getTileInfo(int posX, int posY, string mapName)
{
    vector<vector<string>> selectedMap = Map::getCurrentMap();

    if (!mapName.empty())
    {
        selectedMap = Map::getMapByName(mapName);
    }

    string selectedTile;

    if (posX >= 0 && posY >= 0)
    {
        //selectedTile = selectedMap[posY][posX];
		selectedTile = selectedMap[posY][posX];
        cout << "Getting tile info at position: (" << posX << ", " << posY << ")" << endl;
    }
    else
    {
		
        auto position = Controls::getPosition();

        int positionX = position.first;
        int positionY = position.second;
		
        selectedTile = selectedMap[positionX][positionY];
    }

    return selectedTile;
}

void Map::setMap(string mapName)
{
    Map::currentMap = getMapByName(mapName);
}

void Map::checkTile(int positionX, int positionY, int beforeX, int beforeY)
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

    string tileInfo = getTileInfo(positionX, positionY);
	cout << "Stepped on tile: " << tileInfo << endl;
    if (trim(tileInfo) == "🏰")
    {
		cout << "Entering the castle..." << endl;
		Controls::changePosition(3, 5); // nastaví pozici hráče na začátek hradu
        Map::setMap("castleOneMap");
    }

    if (trim(tileInfo) == "🕳️")
    {
		cout << "Entering the dungeon..." << endl;
		Controls::changePosition(0, 0); // nastaví pozici hráče na začátek podzemí
        Map::setMap("dungeon");
    }

    if (trim(tileInfo) == "🚪")
    {
		cout << "Exiting to the main map..." << endl;
		Controls::changePosition(0, 0); // nastaví pozici hráče na začátek hlavní mapy
        Map::setMap("main");
    }
    if (trim(tileInfo) == "🍺") {
		string input;
		cout << "Chceš vstoupit do hospody? (y/n): ";
		cin >> input;
        if (input == "y" || input == "Y") {
            Controls::gameState = Controls::TRADING;
        }

        
    }
	if (trim(tileInfo)== "E" || trim(tileInfo)=="B") {
		Controls::gameState = Controls::FIGHTING;
	}

    if (trim(tileInfo) == "#") {
		cout << "You hit a wall! Reverting to previous position." << endl;
		Controls::changePosition(beforeX, beforeY);
        /*if (beforeX >= 0) {
            Controls::changePosition(beforeX, positionY);
        }
        if (beforeY >= 0) {
            Controls::changePosition(positionX, beforeY);
        }*/
    }
	cout << "Current position: (" << positionX << ", " << positionY << ")" << endl;
}
// TBD
// string castletwomap[][] =
//??string forest??
//??string plains??