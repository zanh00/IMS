#pragma once
#include <string>
using namespace std;

class Item
{
    private:
        int quantity;

    protected:
        string itemName;
        string description;

    public:
        Item();
        Item(string itemName, string description);
        Item(string itemName, string description, int quantity);
        ~Item();

        void setQuantity(int newQuantity);
        int getQuantity();
        void setDescription(string newDescription);
        string getDescription();

	
};

