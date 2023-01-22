#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
namespace my
{
    template <typename T>
    void print(T& data, char seperator = ' ')
    {
        data.__repr__();
        std::cout << seperator;
    }

    void print(int data, char seperator = ' ')
    {
        std::cout << data << seperator;
    }

    void print(char data, char seperator = ' ')
    {
        std::cout << data << seperator;
    }

    void print(long long data, char seperator = ' ')
    {
        std::cout << data << seperator;
    }

    void print(std::string data, char seperator = ' ')
    {
        std::cout << data << seperator;
    }
    void print(bool data, char seperator = ' ', bool boolInstring = false)
    {
        if (boolInstring == false)
            std::cout << std::boolalpha << data << seperator;
        else
            std::cout << data << seperator;
    }

    void print(const char *str, char seperator = ' ')
    {
        std::cout << str << seperator;
    }
}
#endif // PRINT_HPP