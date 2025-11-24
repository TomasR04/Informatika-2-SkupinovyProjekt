#include "Item.h"

 Item::Item(string name, int basePrice, int value,int duration, Type type) {
	this->name = name;
	this->basePrice = basePrice;
	this->value = value;
	this->type = type;
	this->duration = duration;
}
