//Task read sensor data from file and count the occurances of every value

//Seems good to use a map for this
//Read file, stream into string, and count using map

#include <iostream>
#include <fstream>
#include <queue>
#include <string> //to access getline function
#include <array>
#include <exception>
#include <numeric>

#include <mutex>

using namespace std;

template <typename T, int cap, typename Container = std::array<T, cap>>

class CircularBuffer
{
public:
    CircularBuffer() : _head(0), _tail(0), _current(0), _size(0), _capacity(cap)
    {
        for (auto &elem : c)
        {
            elem = 0;
        }
    }

    //head first element, tail last element, current is one before
    T &head()
    {
        return c.at(_head);
    }

    T &tail()
    {
        return c.at(_tail);
    }

    void push_back(T val) noexcept
    { //insertion at current
        if (_current >= _capacity)
        {
            _current = 0;
        }
        c.at(_current++) = val;
        _tail = _current - 1;

        //make sure things wrap around correctly
        if (_size++ >= _capacity)
        {
            _size = _capacity;
            _head++;
            if (_head >= _capacity)
            {
                _head = 0;
            }
        }
    }

    bool full()
    {
        return _size >= _capacity;
    }

    bool empty()
    {
        return _size <= 0;
    }

    void pop()
    {
        if (empty())
        {
            throw underflow_error("Buffer is empty: pop()");
        }

        c.at(_head) = 0;
        _head++;
        if (_head >= _capacity)
        {
            _head = 0;
        }
        _size--;
    }

    float moving_avarage()
    {
        cout << "Moving average: size is " << _size << ", and sum is " << accumulate(c.begin(), c.end(), 0) << endl;
        if (_size > 0 && accumulate(c.begin(), c.end(), 0) > 0)
        {
            return accumulate(c.begin(), c.end(), 0) / _size;
        }
        return 0;
    }

private:
    Container c;
    int _head;
    int _tail;
    int _current;
    int _size;
    int _capacity;
};

int main(int argc, char const *argv[])
{
    CircularBuffer<int, 10> buff;

    for (int i = 0; i <= 15; i++)
    {
        cout << "Pushing " << i << endl;
        buff.push_back(i);
        cout << "moving average is " << buff.moving_avarage() << endl;
    }

    while (!buff.empty())
    {
        cout << "Popping: " << buff.head() << endl;
        buff.pop();
        cout << "moving average is " << buff.moving_avarage() << endl;
    }
}
