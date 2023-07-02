#pragma once
#include "Item.h"
class ExactItem :
    protected Item
{
    private: 
        uint32_t ID;

    public:
        ExactItem();
        ExactItem(const string name, const string description, uint32_t newID);
        ~ExactItem();

        uint32_t getID();
};

