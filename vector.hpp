#ifndef VECTOR_HPP
#define VECTOR_HPP 1
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include "resource_allocator.hpp"
#ifdef MY_DEBUG
#include "print.hpp"
#endif // MY_DEBUG
namespace my
{

  template <class T> class vector
  {
  public:
    using sizeType = std::size_t;
    using valueType = T;
    using referenceType = T&;
    using rValueReferenceType = T&&;
    using ptrType = T*;

  private:
    sizeType mCapacity;
    sizeType mSize;
    ptrType mArr;

  public: /* Constructor */
    vector();
    vector(sizeType t_size);
    vector(sizeType t_size, valueType t_default_value);
    vector(const vector<valueType>& t_other_vector);
    vector(const std::initializer_list<valueType>&& t_initMe);
  public: /* boolean properties */
    bool is_empty();
  public: /* Methods For Accessing Elements */
    referenceType front();
    referenceType back();
    referenceType at(sizeType t_index);
    referenceType operator[](sizeType t_index);
    sizeType size() { return mSize; }
    sizeType capacity() { return mCapacity; };

  public: /* Methods for inserting and deleting elements */
    void push_back(referenceType data);
    void pop_back();
  public: /* Debugging utilies */
#ifdef MY_DEBUG
    void __repr__();
#endif  // MY_DEBUG
  public: /* Resizing and Reserving Memory utility */
    void shirik_to_fit();
    void reserve(sizeType sizeToReserve);
  public: /* Destructor */
    ~vector();
  };

  template <class T> inline vector<T>::vector(): mCapacity(0), mSize(0), mArr(nullptr)
  {
  }
  template <class T>
  inline vector<T>::vector(sizeType t_size) : mCapacity(t_size), mSize(t_size), mArr(my::array::allocate<T>(t_size))
  {
  }

  template <class T> inline vector<T>::vector(sizeType t_size, valueType t_default_value) : vector(t_size)
  {
    for (auto i = 0; i < mSize; i++)
    {
      mArr[i] = t_default_value;
    }
  }

  template<class T>
  inline vector<T>::vector(const vector<valueType>& t_other_vec)
    : mCapacity(t_other_vec.mCapacity), mSize(t_other_vec.mSize), mArr(my::array::allocate<valueType>(mSize))
  {
    my::linear_container::copy<T>(mArr, t_other_vec.mArr, mSize);
  }
  template<class T>
  inline vector<T>::vector(const std::initializer_list<valueType>&& initMe)
    : mCapacity(initMe.size()), mSize(initMe.size()), mArr(my::array::allocate<T>(initMe.size()))
  {
    sizeType i = 0;
    for (const auto& elem : initMe)
    {
      mArr[i] = elem;
      i++;
    }
  }
  template<class T>
  inline bool vector<T>::is_empty()
  {
    return mSize == 0;
  }
  template<class T>
  inline T& vector<T>::at(sizeType t_index)
  {
    if (mSize == 0)
    {
      throw std::runtime_error("Container is empty!");
    }
    if (t_index > mSize || t_index < 0)
    {
      throw std::runtime_error("Accessing memory that hasn't been located to you!");
    }
    return mArr[t_index];
  }
  template<class T>
  inline T& vector<T>::operator[](sizeType t_index)
  {
    return mArr[t_index];
  }
  template<class T>
  inline void vector<T>::push_back(referenceType data)
  {
    // if container is empty
    if (mArr == nullptr)
    {
      mSize = 0;
      mCapacity = 2;
      mArr = my::array::allocate<T>(mCapacity);
    }
    // if the container is full
    if (mSize == mCapacity)
    {
      mCapacity = mCapacity + mCapacity / 2;
      auto t = my::array::allocate<T>(mSize);
      my::linear_container::copy(t, mArr, mSize);
      my::array::deallocate<T>(mArr);
      mArr = my::array::allocate<T>(mCapacity);
      my::linear_container::copy(mArr, t, mSize);
      my::array::deallocate<T>(t);
    }
    mArr[mSize] = data;
    mSize++;
  }
  template<class T>
  inline void vector<T>::shirik_to_fit()
  {
    /* If container is already full */
    (if (mCapacity == mSize)
    {
      return;
    }
    mCapacity = mSize;
    auto t = my::array::allocate<T>(mSize);
    my::linear_container::copy(t, mArr, mSize);
    my::array::deallocate<T>(mArr);
    mArr = my::array::allocate<T>(mSize);
    my::linear_container::copy(mArr, t, mSize);
    my::array::deallocate<T>(t);
  }
  template<class T>
  inline void vector<T>::reserve(sizeType sizeToReserve)
  {
    if (mArr != nullptr)
    {
      my::array::deallocate<T>(mArr);
    }
    mArr = my::array::allocate<T>(sizeToReserve);
    mSize = 0;
    mCapacity = sizeToReserve;
  }
  template <class T> inline vector<T>::~vector()
  {
    my::array::deallocate<T>(mArr);
  }

#ifdef MY_DEBUG
  template<class T> inline void vector<T>::__repr__()
  {
    for (sizeType i = 0; i < mSize; i++)
    {
      my::print(mArr[i]);
    }
    my::print('\n');
  }
#endif // MY_DEBUG

} // namespace my
#endif // VECTOR_HPP
