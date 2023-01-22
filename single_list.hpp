#ifndef SINGLE_LIST_HPP
#define SINGLE_LIST_HPP

#include "resource_allocator.hpp"
#include <initializer_list>
#ifdef MY_DEBUG
#include "print.hpp"
#endif

namespace my
{
template <class A> struct SingleLinkedListNode
{
    A val;
    SingleLinkedListNode<A> *next;
    SingleLinkedListNode(A t_val, SingleLinkedListNode<A> *t_next = nullptr) : val(t_val), next(t_next)
    {
    }
};

#define Node SingleLinkedListNode
template <class A> class single_list
{
  public:
    using sizeType = std::size_t;
    using valueType = A;
    using referenceType = valueType &;
    using ptrType = valueType *;

  private:
    Node<A> *mHead;
    Node<A> *mTail;
    sizeType mSize;
    sizeType nodeCount;

  public: /* Constructors and Destructors */
    single_list();
    single_list(std::initializer_list<valueType> initMe);
    single_list(const single_list<A> &otherList);

  public: /* Inserting into the List */
    void push_front(referenceType data);
    void push_front(valueType &&data);
    void push_back(referenceType data);
    void push_back(valueType data);
    void push_index(referenceType data);
    void push_index(valueType data);

  public: /* Deletion from the List */
    void pop_front();
    void pop_back();

  public: /* Other common utility */
    void reverse();
    referenceType back();
    referenceType top();
    sizeType size() const;
    bool empty();
    void swap(single_list<A> &otherList);
#ifdef MY_DEBUG
    void __repr__();
#endif

  public: /* Iterator */
  public: /* Destructor */
    ~single_list();
};


template <class A> inline single_list<A>::single_list() : mHead(nullptr), mTail(nullptr), mSize(0), nodeCount(0)
{
}

template <class A> inline single_list<A>::single_list(std::initializer_list<A> initMe)
{
    for (auto &i : initMe)
    {
        this->push_back(i);
    }
}
template <class A> inline single_list<A>::single_list(const single_list<A> &otherList)
{
}
template <class A> inline void single_list<A>::push_front(A &data)
{
    auto temp = my::allocate<Node<A>>(data);
    temp->next = mHead;
    mHead = temp;
    if (mTail == nullptr)
    {
        mTail = mHead;
    }
    nodeCount++;
}
template <class A> inline void single_list<A>::push_front(A &&data)
{
    auto temp = my::allocate<Node<A>>(data);
    temp->next = mHead;
    mHead = temp;
    if (mTail == nullptr)
    {
        mTail = mHead;
    }
    nodeCount++;
}
template <class A> inline void single_list<A>::push_back(A &data)
{
    if (mTail == nullptr)
    {
        return push_front(data);
    }
    auto temp = my::allocate<Node<A>>(data);
    mTail->next = temp;
    mTail = temp;
    nodeCount++;
}
template <class A> inline void single_list<A>::push_back(A data)
{
    if (mTail == nullptr)
    {
        return push_front(data);
    }
    auto temp = my::allocate<Node<A>>(data);
    mTail->next = temp;
    mTail = temp;
    nodeCount++;
}
template <class A> inline void single_list<A>::pop_front()
{
    if (mHead)
    {
        auto t = mHead;
        mHead = mHead->next;
        my::deallocate<Node<A>>(t);
        nodeCount--;
        if (nodeCount == 0)
        {
            mTail = mHead = nullptr;
        }
    }
}
template <class A> inline void single_list<A>::pop_back()
{
}
template <class A> inline void single_list<A>::reverse()
{
}
template <class A> inline A &single_list<A>::back()
{
    if (nodeCount == 0)
    {
        throw std::runtime_error("single_list<A> is empty");
    }
    return mTail->val;
}
template <class A> inline A &single_list<A>::top()
{
    if (this->nodeCount == 0)
    {
        throw std::runtime_error("single_list<A> is empty");
    }
    return mHead->val;
}
template <class A> inline std::size_t single_list<A>::size() const
{
    return this->nodeCount;
}
template <class A> inline bool single_list<A>::empty()
{
    return nodeCount == 0;
}
#ifdef MY_DEBUG
template <class A> inline void single_list<A>::__repr__()
{
    auto temp = mHead;
    while (temp)
    {
        my::print(temp->val);
        temp = temp->next;
    }
    my::print('\n', '\0');
}
#endif

template <class A> inline single_list<A>::~single_list()
{
    Node<A> *temp = mHead;
    while (mHead)
    {
        temp = mHead->next;
        my::deallocate(mHead);
        mHead = temp;
    }
}

#undef Node
} // namespace my

#endif // SINGLE_LIST_HPP
