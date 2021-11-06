#include<iostream>
#include<map>
#include<string> //access to getline() function
#include<fstream> //open/read files 
#include<sstream> //write/read data from/in strings
// #include<utility> //access std::pair object
 
using namespace std;


//Task:  Read the text from the file and store it in a multimap that keeps track of \
lines in which a word appears and the position in line where it appears. 
//Input: text file iliad.txt
//Output: Print the word, its line, and inline position. 

int main()
{
   ifstream in ("iliad.txt"); //open file
   multimap<string, pair<int, int>> wordPosition; //multimap of strings and pairs of ints
   int lineNumber = 0; 
   int worldInLine = 0; 
   string line = ""; 

    while (!in.eof()){
        getline(in, line); 
        lineNumber++; 

        istringstream iss(line); 
        while(!iss.eof()){
            worldInLine++; 
            string word; 
            iss >> word;
            wordPosition.insert(make_pair(word, make_pair(lineNumber, worldInLine)));
        }
        worldInLine = 0; 
    }

    cout << "Number of lines is " << lineNumber << endl; 

    for (auto it = wordPosition.begin(); it !=wordPosition.end(); it++){
        cout << it->first << " appears in line " << it->second.first << ", at position " << it->second.second << endl;  
    
    }
}
