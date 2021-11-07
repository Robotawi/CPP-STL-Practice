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

    //Remove duplicates due to non alphabetic chars

    for (auto it = words_set.begin(); it != words_set.end();)
    {
        string word_trim = *it;
        word_trim.erase(remove_if(word_trim.begin(), word_trim.end(), [](auto &c)
                                  { return !isalpha(c); }),
                        word_trim.end());

        if (word_trim != *it)
        {
            it = words_set.erase(it); //notice this point very well
            words_set.insert(word_trim);
        }
        else
        {
            it++;
        }
    }

    cout << "Unique words number after trimming is " << words_set.size() << endl;

    return 0;
}
