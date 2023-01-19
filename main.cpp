#include <iostream>
#include "utility.hpp"

#include <ctime>


int main() {
    auto b = my::make_pair(2, 3);
    std::cout << b.first() << " " << b.second() << std::endl;
}
