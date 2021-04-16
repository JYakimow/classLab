#include "Card.hpp"
#include "URL.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv)
{
    URL* u1 = new URL("https://api.hearthstonejson.com/v1/25770/enUS/cards.json");
    string jsonString = u1->getContents();
    json parsedJson = json::parse(jsonString);
    Card* theCards[parsedJson.size()];

    int len = parsedJson.size();

    if(parsedJson.is_array())
    {
        for(int i = 0; i < parsedJson.size(); i++)
        {
            json currValue = parsedJson[i];
            if(currValue.is_object())
            {
                string name = currValue.value("name", "N/A");
                int attack = currValue.value("attack", -1);
                int defense = currValue.value("health", -1);
                int manaCost = currValue.value("cost", -1);
                string type = currValue.value("type", "N/A");
                theCards[i] = new Card(name, manaCost, attack, defense, type);
                //theCards[i]->display();
            }
        }
    }
    cout << "Number of Cards: " << parsedJson.size() << endl;

    for (int i = 0; i < parsedJson.size(); i++)
    {
        int temp;
        int follower;
        for(int curr = 1; curr < parsedJson.size(); curr++)
        {
            follower = curr;
            while(follower > 0 && theCards[follower]->getDefense() < theCards[follower-1]->getDefense())
            {
                theCards[temp] = theCards[follower];
                theCards[follower] = theCards[follower-1];
                theCards[follower-1] = theCards[temp];
                follower--;
            }
        }
    }
    //display
    for(int i = 0; i < len; i++)
    {
        theCards[i]->display();
    }
    return 0;
}