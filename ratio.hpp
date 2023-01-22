#ifndef RATIO_HPP
#define RATIO_HPP

#include <algorithm>
#include <iostream>

namespace my
{
    template <typename non_floating_point_number>
    class ratio
    {
    public:
        typedef non_floating_point_number number;

    private:
        number mNum;
        number mDeno;

    private:
        inline void simpify()
        {
            auto factor = std::__gcd(mNum, mDeno);
            mNum /= factor;
            mDeno /= factor;
        }

    public:
        ratio(number a, number b)
            : mNum(a), mDeno(b) { simpify(); }

        explicit ratio(number a)
            : mNum(a, 1) {}

        ratio();

        [[nodiscard]] inline const number &num() const { return mNum; }

        [[nodiscard]] inline const number &deno() const { return mDeno; }

        void display() const
        {
            std::cout << mNum << " " << mDeno << std::endl;
        }
    };
    /* Comparision Operator */
    template <typename number>
    [[nodiscard]] bool operator==(const ratio<number> a, const ratio<number> b)
    {
        return (a.deno() == b.deno() && a.num() == b.num());
    }

    template <typename number>
    [[nodiscard]] bool operator!=(const ratio<number> a, const ratio<number> b)
    {
        return !(a == b);
    }

    template <typename number>
    [[nodiscard]] ratio<number> operator+(const ratio<number> a, const ratio<number> b)
    {
        return ratio<number>(a.num() * b.deno() + b.num() * a.deno(), a.deno() * b.deno());
    }

    template <typename number>
    [[nodiscard]] ratio<number> operator*(const ratio<number> a, const ratio<number> b)
    {
        return ratio<number>(a.num() * b.num(), a.deno() * b.deno());
    }

    template <typename number>
    [[nodiscard]] ratio<number> operator/(const ratio<number> a, const ratio<number> b)
    {
        return ratio<number>(a.num() * b.deno(), a.deno() * b.num());
    }

    template <typename number>
    [[nodiscard]] ratio<number> operator-(const ratio<number> a, const ratio<number> b)
    {
        return ratio<number>(a.num() * b.deno() - b.num() * a.deno(), a.deno() * b.deno());
    }

    template <typename number>
    [[nodiscard]] ratio<number> lcm(const ratio<number> a, const ratio<number> b)
    {
        return ratio<number>((a.num() * b.num()) / std::__gcd(a.num(), b.num()), std::__gcd(a.deno(), b.deno()));
    }
}

#endif // RATIO_HPP