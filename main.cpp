#define MY_DEBUG 1
#include "copying_mechanism.hpp"
#include "resource_allocator.hpp"
#include "vector.hpp"
#include <iostream>
template<class T>
void print(T* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

int main()
{
    my::vector<int> v;
    std::cout << "size = " << v.size() << " " << "capacity = " << v.capacity() << std::endl;
    for (int i = 0; i < 22; i++)
    {
        v.push_back(i);
        std::cout << "size = " << v.size() << " " << "capacity = " << v.capacity() << std::endl;
    }
}

