#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random>

///////////////// USER INCLUDES ////////////////////
#include "Item.h"
#include "ExactItem.h" 

using namespace std;

/////////////////// DEFINES ////////////////////
#define MAX_NUMBER_OF_ITEM 200

////////////////// GLOBAL VARIABLES //////////////////
map<string, Item> GeneralItem;
map<uint32_t, ExactItem> SpeificItem; 
map<string, vector<uint32_t>> GeneralItemIDs;

///////////////// FUNCTIONS //////////////////////
void addItemOne();
uint32_t IDgenerator();

int main() {

    addItemOne();
    Item a = GeneralItem["test"];
    cout << a.getName() << a.getDescription();
    for(auto i = GeneralItemIDs["test"].begin(); i != GeneralItemIDs["test"].end(); ++i)
    {
        cout << *i << endl;
    }
    
    


}

void addItemOne()
{
    string getName;
    string getDescription;
    bool nameExsist = false;
    int numOfItemsToAdd = 0;
    int numOfPreviousItems = 0;
    uint32_t ID;

    cout << "Provide the name of an item you wish to add to the inventory" << endl;
    getline(cin, getName);

    if(GeneralItem.count(getName) != 0)
    {
        getDescription = GeneralItem[getName].getDescription();
        nameExsist = true;
    }
    else
    {
        cout << "Provide a description for the item: " << getName << endl;
        getline(cin, getDescription);
        nameExsist = false;
    }

    cout << "How many items would you like to add?" << endl;
    while (!(cin >> numOfItemsToAdd) || numOfItemsToAdd < 0 || numOfItemsToAdd > MAX_NUMBER_OF_ITEM) {
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if(!nameExsist)
    {
        GeneralItem[getName] = Item(getName, getDescription, numOfItemsToAdd);
    }
    else
    {
        numOfPreviousItems = GeneralItem[getName].getQuantity();
        GeneralItem[getName] = Item(getName, getDescription, numOfPreviousItems + numOfItemsToAdd);
    }

    for (int i = 0; i < numOfItemsToAdd; i++)
    {
        ID = IDgenerator();
        SpeificItem[ID] = ExactItem(getName, getDescription, ID);
        GeneralItemIDs[getName].push_back(ID);
    } 

}

uint32_t IDgenerator()
{
    uint32_t ID;
    do
    {      
        random_device RDEVICE;
        default_random_engine RENGINE(RDEVICE());
        uniform_int_distribution<uint32_t>RGENERATION(100000, 199999);
        ID = RGENERATION(RENGINE);
    } while (SpeificItem.count(ID) != 0);
    
    return ID;
}
