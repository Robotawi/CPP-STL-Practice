#include <iostream>
#include <array>

using namespace std;

/**
 * The Dutch National Flag problem is a three way partitioning problem. This
 * is one possible solution. 
 */
template <typename T>
void dutch_flag_sort(T arr[], int size, T midVal)
{
    int i = 0, j = 0;
    int n = size - 1;

    while (j <= n)
    {
        if (arr[j] < midVal)
        {
            T temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
            j++;
        }
        else if (arr[j] > midVal)
        {
            T temp = arr[j];
            arr[j] = arr[n];
            arr[n] = temp;
            n--;
        }
        else
        {
            j++;
        }
    }
}

int main(int argc, char const *argv[])
{
    int numbers1[10]{0, 1, 0, 1, 0, 1, 2, 1, 2, 0};
    array<int, 10> numbers2{0, 1, 0, 1, 0, 1, 2, 1, 2, 0};

    //Different ways of calling the same function with
    dutch_flag_sort(numbers1, 10, 1);
    dutch_flag_sort(numbers2.data(), numbers2.size(), 1);
    dutch_flag_sort(&numbers2[0], numbers2.size(), 1);
    
    //Notice: range-based for loops works on C-style array
    for (int &elem : numbers1)
    {
        cout << elem << " ";
    }
    cout << "\n";

    for (int &elem : numbers2)
    {
        cout << elem << " ";
    }
    cout << "\n";

    return 0;
}
