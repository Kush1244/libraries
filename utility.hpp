#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "print.hpp"

namespace my
{
    template <class A, class B>
    class pair
    {
    private:
        A mFirstData;
        B mSecondData;
        std::size_t sizeOfTuple;

    public: /* Constructors */
        pair(A First, B Second);
        pair(const pair<A, B> &other);
        pair();

    public: /* Operator Overloads */
        pair &operator=(const pair<A, B> &other);

    public: /* Methods */
        inline A &first();
        inline B &second();
        inline std::size_t size();
        void swap(pair<A, B> &other);
#ifdef MY_DEBUG
        void __repr__();
#endif
    };
    /* Helper Functions */
    template <class A, class B>
    pair<A, B> make_pair(A First, B Second);
}

template <class A, class B>
my::pair<A, B>::pair()
    : sizeOfTuple(sizeof(A) + sizeof(B))
{
}

template <class A, class B>
my::pair<A, B>::pair(A First, B Second)
    : pair()
{
    mFirstData = First;
    mSecondData = Second;
}

template <class A, class B>
my::pair<A, B>::pair(const pair<A, B> &other)
    : pair(other.mFirstData, other.mSecondData)
{
}

template <class A, class B>
my::pair<A, B> &my::pair<A, B>::operator=(const my::pair<A, B> &other)
{
    this->first = other.mFirstData;
    this->second = other.mSecondData;
    return *this;
}

template <class A, class B>
inline A &my::pair<A, B>::first()
{
    return this->mFirstData;
}

template <class A, class B>
inline B &my::pair<A, B>::second()
{
    return this->mSecondData;
}

template <class A, class B>
inline std::size_t my::pair<A, B>::size()
{
    return this->sizeOfTuple;
}

template <class A, class B>
void my::pair<A, B>::swap(pair<A, B> &other)
{
    std::swap(this->first, other.mFirstData);
    std::swap(this->mSecondData, other.mSecondData);
}

#ifdef MY_DEBUG
template <class A, class B>
inline void my::pair<A, B>::__repr__()
{
    my::print(mFirstData);
    my::print(mSecondData);
}
#endif
template <class A, class B>
my::pair<A, B> my::make_pair(A First, B Second)
{
    return my::pair<A, B>(First, Second);
}

#endif // UTILITY_HPP
