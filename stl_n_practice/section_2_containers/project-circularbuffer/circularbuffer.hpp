#ifndef CIRCULAR_BUFER_HPP
#define CIRCULAR_BUFER_HPP

#include <array>
#include <iostream>

template <typename T, int cap, typename Container = std::array<T, cap>>
class CircularBuffer
{

public:
    // We need to constuct buffer, provide head and tail, const ref to head and tail, \

    CircularBuffer() : _size(0), _capacity(cap), _head(0), _tail(0), _current(0) {}
    T &head()
    { //at because it throws exception.\
      if something goes wrong, we get an exception
        return c.at(_head);
    }

    T &tail()
    {
        return c.at(_tail);
    }

    T const &head() const
    {
        return c.at(_head);
    }

    T const &tail() const
    {
        return c.at(_tail);
    }

    //Override the elements if more than capacity is pushed
    void push_back(T value) noexcept
    { //set the current, tail, and head values
        if (_current >= _capacity)
        {
            _current = 0;
        }
        c.at(_current++) = value; //push, then increment current
        _tail = _current - 1;     //always tail = current - 1

        //make sure when things wrap around, the values are shifted in right way
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

    //This one throws if capacity is reached\
    it uses push_back()
    void place_back()
    {
        if (full())
        {
            throw std::overflow_error("place_back(): full buffer");
        }
    }

    //Void to cope with STL containers
    void pop()
    {
        if (empty())
        {
            throw std::underflow_error("pop(): empty buffer");
        }
        c.at(_head) = 0;
        _head++;
        if (_head >= _capacity)
        {
            _head = 0;
        }
        _size--;
    }

    std::size_t size() noexcept
    {
        return _size;
    }

    std::size_t capacity() noexcept
    {
        return _capacity;
    }

    bool full() noexcept
    {
        return _size >= capacity;
    }

    bool empty() noexcept
    {
        return _size <= 0;
    }

private:
    Container c;
    int _head;     //points to first pushed element
    int _tail;     //points to last pushed element
    int _current;  //points to available next position to push at
    int _size;     //current size
    int _capacity; //capacity of this buffer
};

#endif