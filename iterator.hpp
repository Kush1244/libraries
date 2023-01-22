#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace my
{
    template <class A>
    class forward_iterator
    {
    private:
        A *mBegin;
        A *mEnd;

    public:
        typedef A *ptrType;
        typedef A &referenceType;
        typedef A valueType;

    public:
    };

    template <class A>
    class backward_iterator
    {
    };

    template <class A>
    class bidirectional_iterator
    {
    };

    template <class A>
    class random_access_iterator
    {
    };
}

#endif // ITERATOR_HPP
