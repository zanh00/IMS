#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random>

/*      USER INCLUDES     */

#include "Item.h"
#include "ExactItem.h" 

using namespace std;

/*      DEFINES             */

#define MAX_NUMBER_OF_ITEM 200

/*       GLOBAL VARIABLES       */

map<string, Item> GeneralItem;                      // holds general items name and parameters (descp., quant.)
map<uint32_t, ExactItem> SpeificItem;               // holds all specific item (exacItem obejcts) with their ID
map<string, vector<uint32_t>> GeneralItemIDs;       // holds all specific item IDs for each general item

/*      FUNCTIONS           */

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

/**
    @brief Function adds new items to the datatbase
*/ 
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

    if(GeneralItem.count(getName) != 0)                                                                 // if item already exsists than get its description
    {
        getDescription = GeneralItem[getName].getDescription();
        nameExsist = true;
    }
    else                                                                                                // if not than ask user to provide it
    {
        cout << "Provide a description for the item: " << getName << endl;
        getline(cin, getDescription);
        nameExsist = false;
    }

    cout << "How many items would you like to add?" << endl;
    while (!(cin >> numOfItemsToAdd) || numOfItemsToAdd < 0 || numOfItemsToAdd > MAX_NUMBER_OF_ITEM) {  // user enters a valid number between 0 and Max number of items that can be added at once
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if(!nameExsist)                                                                                     // if gneral item doesnt exist than create it  and add it to the map
    {
        GeneralItem[getName] = Item(getName, getDescription, numOfItemsToAdd);
    }
    else                                                                                                // if it does checks how many specific items it already has and sums it wiht num. to be added
    {
        numOfPreviousItems = GeneralItem[getName].getQuantity();
        GeneralItem[getName] = Item(getName, getDescription, numOfPreviousItems + numOfItemsToAdd);
    }

    cout << numOfItemsToAdd << " new items added with the following IDs:" << endl;
    for (int i = 0; i < numOfItemsToAdd; i++)                                                           // adds new spcific items and its IDs to the vector
    {
        ID = IDgenerator();
        SpeificItem[ID] = ExactItem(getName, getDescription, ID);
        GeneralItemIDs[getName].push_back(ID);
        cout << i + 1 << " " << ID << endl;
    } 

}

/// @brief generates a random ID and chechks the databes if it is free (repets if necessary)
/// @return the unique ID
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


