//Task 1 read herodotus.txt and calculate number of occurrences, lines, and line positions.
//Task 2 process the words to keep only alphabetic characters 

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>

#include <algorithm> // for remove_if to erase non alphapetic chars
int main(int argc, char const *argv[])
{
    using namespace std;

    ifstream in_file("herodotus.txt");
    multimap<string, pair<int, int>> wordPositions;

    if (in_file.is_open())
    {
        string line;
        int numLines = 0;
        int wordLinePos = 0;

        while (!in_file.eof())
        {
            numLines++;
            getline(in_file, line);
            istringstream iss(line);
            string word = "";
            while (!iss.eof())
            {
                iss >> word;
                wordLinePos++;
                wordPositions.insert(make_pair(word, make_pair(numLines, wordLinePos)));
            }
            wordLinePos = 0;
        }
    }

    // for (auto u_it = wordPositions.cbegin(), o_it = u_it; o_it != wordPositions.cend(); u_it = o_it)
    // {
    //     cout << "Word: " << u_it->first << " occurs " << wordPositions.count(u_it->first) << " times in: ";
    //     for (; u_it->first == o_it->first && o_it != wordPositions.cend(); o_it++)
    //     {
    //         cout << "line " << o_it->second.first << ", position " << o_it->second.second << endl;
    //     }
    // }

    //Task 2 process the words to keep only alphabetic characters 

    std::string test_key = "";
    for (auto it = wordPositions.begin(); it != wordPositions.end();)
    {
        test_key = it->first;
        test_key.erase(remove_if(test_key.begin(), test_key.end(), [](auto &c)
                                 { return !(isalpha(c)); }),
                       test_key.end());
        if (test_key != it->first)
        {
            // cout << "it->first is: " << it->first << " after processing, it becomes: " << test_key << endl;
            wordPositions.insert(make_pair(test_key, make_pair(it->second.first, it->second.second)));
            it = wordPositions.erase(it);
        }
        else
        {
            it++;
        }
    }

    //Print the result
    for (auto u_it = wordPositions.cbegin(), o_it = u_it; o_it != wordPositions.cend(); u_it = o_it)
    {
        cout << "Word: " << u_it->first << " occurs " << wordPositions.count(u_it->first) << " times in: \n";
        for (; u_it->first == o_it->first && o_it != wordPositions.cend(); o_it++)
        {
            cout << "line " << o_it->second.first << ", position " << o_it->second.second << endl;
        }
    }

    return 0;
}
