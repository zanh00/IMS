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
#define MIN_MENU_NUM 1
#define MIN_SUB_MENU_NUM 1
#define MAX_MENU_NUM 5
#define MAX_SUB_MENU_NUM 3
#define MIN_ID_NUM 100000
#define MAX_ID_NUM 199999

/*       GLOBAL VARIABLES       */

map<string, Item> GeneralItem;                      // holds general items name and parameters (descp., quant.)
map<uint32_t, ExactItem> SpeificItem;               // holds all specific item (exacItem obejcts) with their ID
map<string, vector<uint32_t>> GeneralItemIDs;       // holds all specific item IDs for each general item

/*      FUNCTIONS           */

void addItemOne();
uint32_t IDgenerator();
int MainMenuSelection();
void RemoveItem();
void DisplayInventory();

int main() {

    //addItemOne();
    // Item a = GeneralItem["test"];
    // cout << a.getName() << a.getDescription();
    //int a = MainMenuSelection();
    //cout << a;
    
    while(1)
    {
        switch (MainMenuSelection())
        {
        case 1:
            
            break;        
        case 2:
            addItemOne();
            break;
        case 3:
            RemoveItem();
            break;
        case 4:
            DisplayInventory();
            break;
        case 5:
            return 0;
            break;
        default:
            return 0;
            break;
        }
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
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        cout << "Invalid input! You can only provide a NUMBER between 0 and 200" << endl;
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
        uniform_int_distribution<uint32_t>RGENERATION(MIN_ID_NUM, MAX_ID_NUM);
        ID = RGENERATION(RENGINE);
    } while (SpeificItem.count(ID) != 0);
    
    return ID;
}

/**
 * @brief Displays menu to the console and gets the selection from user
 * @return Number of selected option (proof checked)
*/
int MainMenuSelection()
{
    int menuSelection = 0;
    cout << "--------------------------------" << endl << "INVENTORY MANAGEMENT SYSTEM" << endl << "--------------------------------" << endl
    << "Main Menu" << endl << "1) Search Item" << endl << "2) Add Item" << endl << "3) Remove Item\n4) Display Inventory \n5) Exit program" << endl;

    while (!(cin >> menuSelection) || menuSelection < MIN_MENU_NUM || menuSelection > MAX_MENU_NUM) {  
        cout << "Invalid input! You can only provide a NUMBER between 1 and 5" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return menuSelection;
}

/**
 * @brief firs displays remove item menu and accepts a valid option, than removs items from inventory either by name (all of them) or by ID depending on the option selected.
*/
void RemoveItem()
{
    int removeOption = 0;
    string removeName;
    uint32_t removeID;
    vector <uint32_t> IDsForRemoval;
    cout << "REMOVE ITEM menu:" << endl << "1) Remove Item by Name (all items by this name will be removed)" << endl
    << "2) Remove Item by ID \n3) Back to Main Menu" << endl;
    while (!(cin >> removeOption) || removeOption < MIN_SUB_MENU_NUM || removeOption > MAX_SUB_MENU_NUM) {          // acceppts one of the 3 menu options
        cout << "Invalid input! You can only provide a NUMBER between 1 and 3" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(removeOption)
    {
        default:
            return;
        break;

        case 1:                                                                                                    //  Remove Item by name
            cout << "Provide the name of an item you wish to remove from the inventory" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, removeName);
            if(GeneralItem.count(removeName) != 0)                                                                // if this item exsist
            {
                GeneralItem.erase(removeName);                                                                    // removal from GeneralItem map
                IDsForRemoval = GeneralItemIDs[removeName];                                                       // stores all IDs of general item to be removed 
                for (auto i = IDsForRemoval.begin(); i != IDsForRemoval.end(); ++i)                               // removes all specific items from SpecificItem map
                {
                    SpeificItem.erase(*i);
                }

                GeneralItemIDs.erase(removeName);                                                                  // erases the vector that held all the IDs of the removed item
                cout << IDsForRemoval.size() << " items have been removed" << endl;                                // prenits how many items have been removed
                IDsForRemoval.clear();
            }
            else                                                                                               
            {
                cout << "Item with this name does not exsist. " << endl;
            }
           
        break;

        case 2:                                                                                                     // Remove by ID
            cout << "Provide ID number of item that you want to remove" << endl;
            while (!(cin >> removeID) || removeID < MIN_ID_NUM || removeID > MAX_ID_NUM) {                          // gets ID of an item to be removed from the user
            cout << "Invalid input! ID numbers are from range of " << MIN_ID_NUM << " to " << MAX_ID_NUM << "!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(SpeificItem.count(removeID) != 0)                                                                    // if item with this ID exsist than it erases it
            {
                // iterator that finds the position of ID in the vector of general Item -> find(vector.begin(), vector.end(), removeID) 
                auto it = find(GeneralItemIDs[SpeificItem[removeID].getName()].begin(), GeneralItemIDs[SpeificItem[removeID].getName()].end(), removeID); 
                if (it != GeneralItemIDs[SpeificItem[removeID].getName()].end())
                {
                    GeneralItemIDs[SpeificItem[removeID].getName()].erase(it);                                      // Removes ID from vector map of general item
                }
                SpeificItem.erase(removeID);                                                                        // Removes ID from specific item map
                cout << "Item has been removed" << endl;
            }
            else
            {
                cout << "Item with this ID does not exsist" << endl;
            }

        break;

        case 3:
            return;
        break;

    }

}

void DisplayInventory()
{
    for (auto i : GeneralItemIDs)
    {
        cout << i.first << ":" << endl;
        for (auto j = i.second.begin(); j != i.second.end(); ++j)
        {
            cout << "\t- " << *j << endl;
        }
    }
}
