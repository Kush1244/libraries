#ifndef COPY_MECHANISM
#define COPY_MECHANISM 1

#include <cstddef>
using sizeType = std::size_t;

namespace my
{
    namespace linear_container
    {
        /* Definitions */
        template<class T>
        void copy(T* to_copy, T* from_copy, sizeType size);

        /// @brief Copies data from one array into another array
        /// @tparam T data type of the container 
        /// @param to_copy container to put data into
        /// @param from_copy the container from data is taken 
        /// @param size length of the container
        template<class T>
        void copy(T* to_copy, T* from_copy, sizeType size)
        {
            for (sizeType i = 0; i < size; i++)
            {
                to_copy[i] = from_copy[i];
            }
        }
    } // namespace linear_container

} // namespace my


#endif // COPY_MECHANISM