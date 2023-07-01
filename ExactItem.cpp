#include "ExactItem.h"

ExactItem::ExactItem(const string name, const string description, uint32_t newID)
{
    Item(name, description);
    ID = newID;
}

ExactItem::~ExactItem()
{
}

uint32_t ExactItem::getID()
{
    return ID;
}
