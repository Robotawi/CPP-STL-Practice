#include <iostream>
#include <map>

using namespace std;

struct simpleObject
{
    int a, b;
    string c;
    simpleObject() : a(1), b(2), c("no input") {}
    simpleObject(int a, int b, string c) : a(a), b(b), c(c) {}
};

int main(int argc, char const *argv[])
{

    map<string, simpleObject> simpleMap;

    simpleMap.insert(pair<string, simpleObject>("first", simpleObject()));
    simpleMap.insert(pair<string, simpleObject>("second", simpleObject(3, 4, "second")));

    simpleMap.insert({"third", simpleObject(5, 6, "third")}); //initializer list creates a pair.

    simpleMap["fourth"] = simpleObject(7, 8, "fourth");

    simpleMap.insert(make_pair("fifth", simpleObject(9, 10, "fifth")));

    //Insertion with insert() returns a pair<iterator, bool> \
    where the bool is true if the insertion was successful.
    auto it = simpleMap.insert({"fifth", simpleObject(11, 12, "fifth")});

    if (it.second == true)
    {
        cout << "Inserted successfully" << endl;
    }
    else
    {
        cout << "Insertion failed" << endl;
    }
    cout << "-----------------" << endl;
    cout << "printing simpleMap" << endl;
    cout << "simpleMap.size() = " << simpleMap.size() << endl;
    
    cout << "Notice that the elements are printed in a random order" << endl;

    //Go through each element in the map

    for (auto it = simpleMap.begin(); it != simpleMap.end(); it++)
    {
        cout << it->first << " " << it->second.a << " " << it->second.b << " " << it->second.c << endl;
    }

    //Insertion with [] operator returns a reference to the mapped value.
    // If the key does not exist, a new element is inserted. \
    if it exists, the existing value is overwritten.
    simpleMap["fifth"] = simpleObject(13, 14, "new fifth ** OVERWRITTEN **");

    //Another way to go through each element in the map
    //Print with range-based for loop
    cout << "-----------------" << endl;
    cout << "printing simpleMap" << endl;
    for (auto elem : simpleMap)
    {
        cout << elem.first << " " << elem.second.a << " " << elem.second.b << " " << elem.second.c << endl;
    }

    //Erase some elements
    simpleMap.erase("fifth");
    simpleMap.erase("fourth");

    cout << "-----------------" << endl;
    cout << "printing simpleMap" << endl;
    for (auto elem : simpleMap)
    {
        cout << elem.first << " " << elem.second.a << " " << elem.second.b << " " << elem.second.c << endl;
    }

    //Find an element with find()
   auto search_result = simpleMap.find("second");
    if (search_result != simpleMap.end())
    {
        cout << "Search result: Found. " << search_result->first << " " << search_result->second.a << " " << search_result->second.b << " " << search_result->second.c << endl;
    }
    else
    {
        cout << "Search result: Not found. " << endl;
    }

    //Clear the map
    simpleMap.clear();
    cout << "objectMap size now is " << simpleMap.size() << endl;

    return 0;
}