//Task: read the odyssey.txt file and count unique words.

//Tasl: read the odyssey.txt file and save the number of lines and line positions for every word.

#include <fstream>
#include <sstream>

#include <iostream>
#include <map>     // for multimap
#include <string>  // for getline
#include <utility> // for pair

using namespace std;
int main(int argc, char const *argv[])
{
    ifstream in_file("odyssey.txt");
    multimap<string, pair<int, int>> wordPositions;
    int lineNumber = 0;
    int wordInLinePosition = 0;

    string line;

    if (in_file.is_open())
    {
        while (!in_file.eof())
        {
            getline(in_file, line);
            lineNumber++;
            istringstream iss(line);
            while (!iss.eof())
            {
                string word;
                iss >> word;

                wordInLinePosition++;
                // three ways of insertion, three ways to make pairs
                // wordPositions.insert(make_pair(word, make_pair(lineNumber, wordInLinePosition)));
                // wordPositions.insert(pair<string, pair<int, int>>(word, make_pair(lineNumber, wordInLinePosition)));
                wordPositions.insert({word, make_pair(lineNumber, wordInLinePosition)});
            }

            wordInLinePosition = 0;
        }
    }

    // cout one value per all occurrences in the multimap, and loop over them 
    for (auto it = wordPositions.cbegin(), it2 = it; it != wordPositions.end(); it = it2)
    {
        unsigned int count = wordPositions.count(it->first);
        cout << "Word: \"" << it->first << "\" occurs " << count << " times and appears in\n";
        for (; it2->first == it->first && it2 != wordPositions.cend(); it2++)
        {
            cout << "line " << it2->second.first << " at position " << it2->second.second << endl;
        }
    }


    return 0;
}
