#pragma once
#include <string>
using namespace std;
class Item
{
public:
	string name;
	int basePrice;
	int value;
	int duration;
	static enum Type {
		FOOD,
		MELEE_WEAPON,
		RANGED_WEAPON,
		POTION
	};
	Type type;
	Item(string name, int basePrice, int value,int duration, Type type);
	
};

