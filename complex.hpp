#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <cmath>
#include "math.hpp"

#ifdef DEBUG
    #include <iostream>
#endif

template<typename numeric_type = float>
class complex {
private:
    numeric_type mReal;
    numeric_type mImg;
    numeric_type mNorm;
    numeric_type mMagnitude;
public: /* constructors */
    complex(); // Default constructor
    complex(numeric_type all_equal);
    complex(numeric_type real, numeric_type img);
    complex(const complex<numeric_type>& cmplx);

public: /* member functions */
    inline numeric_type& real();
    inline numeric_type& img();
    numeric_type mag();
    inline numeric_type norm();
    complex conj();

public: /* Member Operator */
    bool operator == (const complex<numeric_type>& other);
    bool operator == (const complex<numeric_type>&& other);
    bool operator != (const complex<numeric_type>& other);
    bool operator != (const complex<numeric_type>&& other);
    complex<numeric_type>& operator = (const complex<numeric_type>& other);
    complex<numeric_type>& operator = (const complex<numeric_type>&& other);
    complex<numeric_type>& operator = (const float& a);
    complex<numeric_type>& operator = (const float&& a);
};

template<typename T>
complex<T>::complex() : complex(0.0, 0.0)
{

}

template<typename T>
complex<T>::complex(T all_equal) : complex(all_equal, all_equal)
{

}

template<typename T>
complex<T>::complex(T real, T img) : mReal(real), mImg(img), 
    mNorm(my::square::square({real, img})) ,mMagnitude(sqrt(mNorm))
{

}

template<typename T>
complex<T>::complex(const complex<T>& cmplex) : complex(cmplex.mReal, cmplex.mImg)
{
    std::cout << "copy constructor called" << std::endl;
}

template<typename T>
inline T& complex<T>::real() {
    return mReal;
}

template<typename T>
inline T& complex<T>::img() {
    return mImg;
}

template<typename T>
T complex<T>::mag()  {
    return mMagnitude;
}

template<typename T>
inline complex<T> complex<T>::conj() {
    return complex(this->mReal, -this->mImg);
}

template<typename T>
inline T complex<T>::norm() {
    return mNorm;
}


/* MEMBER OPERATOR */
template<typename T>
bool complex<T>::operator == (const complex<T>& other) {
    return this->mReal == other.mReal && this->mImg == other.mImg;
}

template<typename T>
bool complex<T>::operator == (const complex<T>&& other) {
    return this->mReal == other.mImg && this->mImg == other.mImg;
}

template<typename T>
bool complex<T>::operator != (const complex<T>& other) {
    return !(*this == other);
}


template<typename T>
bool complex<T>::operator != (const complex<T>&& other) {
    return !(*this == other);
}

template<typename T>
complex<T>& complex<T>::operator = (const complex<T>& other) {
    this->mReal = other.mReal;
    this->mImg = other.mImg;
    return *this;
}

template<typename T>
complex<T>& complex<T>::operator = (const complex<T>&& other) {
    this->mReal = other.mReal;
    this->mImg = other.mImg;
    return *this;
}

template<typename T>
complex<T>& complex<T>::operator = (const float& num) {
    this->mReal = num;
    this->mImg = num;
    return *this;
}

template<typename T>
complex<T>& complex<T>::operator = (const float&& num) {
    this->mReal = num;
    this->mImg = num;
    return *this;
}


/* Arithmetic Operations on Complex Number */

template<typename T>
complex<T> operator + (complex<T>& lhs, complex<T>& rhs) {
    complex<T> a(lhs.real() + rhs.real(), lhs.img() + rhs.img());
    return a;
}

template<typename T>
complex<T> operator - (complex<T>& lhs, complex<T>& rhs) {
    return complex(lhs.real() - rhs.real(), lhs.img() - rhs.img());
}

template<typename T>
complex<T> operator * (complex<T>& lhs, complex<T>& rhs) {
    auto real = lhs.real() * rhs.real() - lhs.img() * lhs.img();
    auto img = lhs.real() * rhs.img() + lhs.img() + rhs.real();
    return complex(real, img);
}

template<typename T>
complex<T> operator * (complex<T>& lhs, complex<T>&& rhs) {
    auto real = lhs.real() * rhs.real() - lhs.img() * lhs.img();
    auto img = lhs.real() * rhs.img() + lhs.img() + rhs.real();
    return complex(real, img);
}

template<typename T>
complex<T> operator * (complex<T>& lhs, T num) {
    return complex(lhs.real() * num, lhs.img() * num);
}

template<typename T> 
complex<T> operator / (complex<T> lhs, T num) {
    return complex<T>(lhs.real() / num, lhs.img() / num); 
}

template<typename T>
complex<T> operator / (complex<T>& lhs, complex<T>& rhs) {
    if(rhs.norm() == 0) {
        throw std::runtime_error("Can't divided with complex number having magnitude Zero\n");
    }
    auto t = lhs;
    t *= rhs.conj();
    t /= rhs.mag();
}

template<typename T>
complex<T> operator ~ (complex<T>& cn) {
    return cn.conj();
}

template<typename T>
complex<T> operator ~ (complex<T>&& cn) {
    return cn.conj();
}

#endif // COMPLEX_HPP
