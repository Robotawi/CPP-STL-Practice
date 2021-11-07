//Task: count the unique words in a text file

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <algorithm>
int main(int argc, char const *argv[])
{
    using namespace std;

    set<string> words_set;
    ifstream in_file("iliad.txt");
    string line = "";
    string word;
    if (in_file.is_open())
    {
        while (!in_file.eof())
        {
            getline(in_file, line);

            istringstream iss(line);
            while (!iss.eof())
            {
                iss >> word;

                words_set.insert(word);
            }
        }
    }

    cout << "Unique words number is " << words_set.size() << endl;

    for (auto &w : words_set)
    {
        cout << w << ", ";
    }

    return 0;
}
