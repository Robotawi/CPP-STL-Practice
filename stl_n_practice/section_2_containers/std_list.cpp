#include <iostream>
#include <list>

using namespace std;

int main(int argc, char const *argv[])
{
    list<int> numbers1{10, 20, 30, 40, 50};
    list<int> numbers2{25, 35, 60, 70, 80, 90};

    numbers1.merge(numbers2);

    cout << "Size of numbers1 list is " << numbers1.size() << "\n";
    cout << "Size of numbers2 list is " << numbers2.size() << "\n";

    for (auto it = numbers1.begin(); it != numbers1.end(); it++)
    {
        cout << *it << " ";
    }

    cout << "\n";

    return 0;
}
