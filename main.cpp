#include "complex.hpp"
#include <any>
#include <iostream>
int main()
{
	my::complex<> a(1, 2);
	std::cout << a.real() << " " << a.img() << std::endl;
	std::cout << a.mag() << " " << a.norm() << std::endl;
}
