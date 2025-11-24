#pragma once

#include "Player.h"

class Fighting
{
public:
    // Spustí jeden souboj, vrátí true pokud hráè pøežil (vyhrál nebo utekl)
    static bool startFight(Player& player);
};