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

    for (auto &elem : wordPositions)
    {
        cout << "Word: " << elem.first << " appears in line " << elem.second.first << " at position " << elem.second.second << endl;
    }
    return 0;
}
