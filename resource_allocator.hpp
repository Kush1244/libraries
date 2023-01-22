#ifndef RESOURCE_ALLOCATOR
#define RESOURCE_ALLOCATOR 1

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#define sizeType std::size_t

namespace my
{

#ifdef TRACK_ALLOCATION

    class _memory_map
    {
        std::unordered_map<std::string, std::size_t> memMap;
        sizeType _Allocated_Mem = 0;
        sizeType _Deallocated_Mem = 0;

    public:
        void insert(std::string memory, std::size_t size)
        {
            // checking if the memory is already present in the map
            // If memory is already present then we raise an error
            //
            if (memMap.find(memory) == memMap.end())
            {
                memMap.insert({ memory, size });
                return;
            }
            if (memMap[memory] == 0)
            {
                return;
            }
            // Allocating without deleting the previous allocatd memeory
            std::cerr << "First delete the memory address at " << memory << std::endl;
            throw std::runtime_error(" Can create Dangling Pointer ");
        }

        void remove(std::string memory)
        {
            /* We are trying to remove the map that hasn't been allocated By resource_allocator.hpp */
            if (memMap.find(memory) == memMap.end())
            {
                throw std::runtime_error("Removing memory that hasn't been allocated to you\n");
            }
            memMap[memory] = 0;
        }
        ~_memory_map()
        {
            if (memMap.size() != 0)
            {
                std::cerr << "All memory hasn't been freed\n" << std::endl;
            }
        }
    };
    static _memory_map mem_map;
    template <class T> std::string convertAddressIntoString(T* memory)
    {
        std::ostringstream oss;
        oss << memory;
        return std::string(oss.str());
    }
#endif
    template <class T> [[nodiscard]] T* allocate()
    {
#ifdef TRACK_ALLOCATION
        auto a = new T;
        mem_map.insert(convertAddressIntoString(&a), sizeof(T));
        return a;
#endif // TRACK_ALLOCATION
        return new T;
    }

    template <class T> [[nodiscard]] T* allocate(T data)
    {
#ifdef TRACK_ALLOCATION
        auto a = new T(data);
        mem_map.insert(convertAddressIntoString(&a), sizeof(T));
        return a;
#endif // TRACK_ALLOCATION
        return new T(data);
    }

    template <class T> void deallocate(T* heap_allocated_memory)
    {
#ifdef TRACK_ALLOCATION
        mem_map.remove(convertAddressIntoString(&heap_allocated_memory));
#endif // TRACK_ALLOCATION
        delete heap_allocated_memory;
        heap_allocated_memory = nullptr;
    }

    namespace array
    {
        template <class T> T* allocate(sizeType size)
        {
#ifdef TRACK_ALLOCATION
            auto a = new T[size];
            mem_map.insert(convertAddressIntoString((void*)a), size * sizeof(T));
            return a;
#endif // TRACK_ALLOCATION
            return new T[size];
        }

        template<class T> T* allocate(sizeType size, T defVal)
        {
            auto temp = new T[size];
            for (sizeType i = 0; i < size; i++)
            {
                temp[i] = defVal;
            }
            return temp;
        }
    
        template <class T> void deallocate(T* heap_allocated_continuous_memory)
        {
            delete[] heap_allocated_continuous_memory;
        }
    } // namespace array
} // namespace my
#undef sizeType

#endif // RESOURCE_ALLOCATOR
