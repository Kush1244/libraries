#ifndef ARRAY_HPP
#define ARRAY_HPP
#define MY_DEBUG
#include <cstddef>
#include <stdexcept>
#ifdef MY_DEBUG
#include "print.hpp"
#endif
namespace my
{
template <typename T, std::size_t N> class static_array
{
  private: /* Member Variables */
    T arr[N];
    size_t mSize;
    size_t mCapacity;

  public:
    static_array();
    static_array(T defaultValue);

  public: /* Methods */
    [[nodiscard]] inline size_t size();
    [[nodiscard]] inline size_t capacity();
    void push_back(T &data);
    void push_back(T &&data);
    void pop_back();
    [[nodiscard]] inline T &front();
    [[nodiscard]] inline T &back();
    [[nodiscard]] inline T *data();
    [[nodiscard]] T &at(size_t index);
    [[nodiscard]] T &operator[](size_t index);
#ifdef MY_DEBUG
    void __repr__();
#endif
};

template <typename T, size_t N> static_array<T, N>::static_array() : mSize(0), mCapacity(N)
{
}

template <typename T, size_t N> static_array<T, N>::static_array(T defualt_value) : static_array()
{
    for (size_t i = 0; i < mCapacity; i++)
    {
        arr[i] = defualt_value;
        mSize++;
    }
}

template <typename T, size_t N> [[nodiscard]] inline size_t static_array<T, N>::size()
{
    return mSize;
}

template <typename T, size_t N> [[nodiscard]] inline size_t static_array<T, N>::capacity()
{
    return mCapacity;
}

template <typename T, size_t N> void static_array<T, N>::push_back(T &data)
{
    if (mSize < mCapacity)
    {
        arr[mSize] = data;
        mSize++;
    }
}
template <typename T, size_t N> void static_array<T, N>::push_back(T &&data)
{
    if (mSize < mCapacity)
    {
        arr[mSize] = data;
        mSize++;
    }
}

template <typename T, size_t N> void static_array<T, N>::pop_back()
{
    if (mSize > 0)
        mSize--;
}

template <typename T, size_t N> [[nodiscard]] inline T &static_array<T, N>::front()
{
    if (mSize != 0)
    {
        return arr[0];
    }
    throw std::runtime_error("Array is empty! Can't Access the first element");
}

template <typename T, size_t N> [[nodiscard]] inline T &static_array<T, N>::at(size_t index)
{
    if (index >= mSize)
    {
        throw std::runtime_error("Accessing Location that hasn't been allocated to you!");
    }
    return this->arr[index];
}

template <typename T, size_t N> [[nodiscard]] inline T &static_array<T, N>::operator[](size_t index)
{
    return arr[index];
}

#ifdef MY_DEBUG
template<typename T, size_t N> inline void static_array<T, N>::__repr__()
{
    for(auto i = 0; i < this->size(); i++)
    {
        my::print(arr[i]);
    }
    my::print('\n');
}
#endif
} // namespace my
#endif // ARRAY_HPP
