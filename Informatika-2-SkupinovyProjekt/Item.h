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

// define equality so algorithms like std::find can compare Items
inline bool operator==(const Item& a, const Item& b) {
    return a.name == b.name && a.basePrice == b.basePrice && a.value == b.value
        && a.duration == b.duration && a.type == b.type;
}

inline bool operator!=(const Item& a, const Item& b) {
    return !(a == b);
}

