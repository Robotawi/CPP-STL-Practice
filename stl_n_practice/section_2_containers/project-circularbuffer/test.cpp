#include "circularbuffer.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    CircularBuffer<int, 10> buff;
    for (int i = 0; i < 50; i++)
    {
        buff
        .push_back(i);
    }

    while(!buff.empty()){
        cout << "Popping: " << buff.head() << endl;
        buff.pop();
    }
    cout << "all elements poped. Size is "<<  buff.size() << endl; 
    
    return 0;
}
