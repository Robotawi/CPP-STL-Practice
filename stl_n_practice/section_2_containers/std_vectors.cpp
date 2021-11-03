#include <vector>
#include <iostream>
#include <exception>

using namespace std;

template <typename T>
void printVector(vector<T> &vec)
{
    cout << "Vector has size " << vec.size() << ", capacity " << vec.capacity()
         << ", and max size of " << vec.max_size() << "\n";

    for (auto &elem : vec)
    {
        cout << elem << ", ";
    }
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    vector<int> numbers1 = {1, 2, 3};
    vector<int> numbers2;

    numbers2.push_back(1);
    numbers2.push_back(2);
    numbers2.push_back(3);

    printVector(numbers1);
    printVector(numbers2);

    //bad access
    cout << "Got junk of value " <<numbers1[30] << "\n";

    try
    {
        cout << numbers1.at(30); 
    }
    catch (std::out_of_range& e)
    {
        cout << e.what() << "\n"; 
    }

    return 0;
}
