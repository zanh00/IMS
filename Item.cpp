#include "Item.h"

Item::Item()
{
}

Item::Item(string itemName, string description)
{
    this-> itemName = itemName;
    this-> description = description;
}

Item::Item(string itemName, string description, int quantity)
{
    this-> itemName = itemName;
    this-> quantity = quantity;
    this-> description = description;
}

Item::~Item()
{
}

void Item::setQuantity(int newQuantity)
{
    quantity = newQuantity;
}

int Item::getQuantity()
{
    return quantity;
}

void Item::setDescription(string newDescription)
{
    description = newDescription;
}

string Item::getDescription()
{
    return description;
}
