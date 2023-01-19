#ifndef MATH_HPP
#define MATH_HPP

#include <initializer_list>

/* Square */
namespace my {
    namespace square {
        template<typename numeric_type>
        double square(numeric_type& num) {
            return num * num;
        }

        template<typename numeric_type>
        double square(std::initializer_list<numeric_type>&& sum_of_squares) {
            double _square = 0.0;
            for(auto i : sum_of_squares) {
                _square += square<numeric_type>(i);
            }
            return _square;
        }
    }

    namespace square_root {

    }
}



#endif // MATH_HPP