/**************************************************************************************************
 * @file    SharedMemoryAllocator.hpp
 * @date    2014-12-16
 * @author  Omar Stefan Evans
 **************************************************************************************************/

#pragma once

#include <limits>
#include "MemoryManager.hpp"

namespace rambler { namespace memory {

    template <typename T>
    class SharedMemoryAllocator {
    private:
        MemoryManager * memory_manager;
    public:
        using value_type        = T;
        using pointer           = value_type *;
        using const_pointer     = const pointer;
        using reference         = value_type &;
        using const_reference   = const reference;
        using size_type         = size_t;
        using difference_type   = ptrdiff_t;
        template< class U > struct rebind { typedef SharedMemoryAllocator<U> other; };

        SharedMemoryAllocator() : memory_manager(MemoryManager::default_manager()) {}
        SharedMemoryAllocator(MemoryManager * mm) : memory_manager(mm) {}
        SharedMemoryAllocator(const SharedMemoryAllocator & other) = default;

        template< class U >
        SharedMemoryAllocator(const SharedMemoryAllocator<U> & other) {}

        pointer allocate(size_type n, std::allocator<void>::const_pointer hint = 0) {
            return static_cast<pointer>(memory_manager->reserve_memory(n, sizeof(T)));
        }

        void deallocate(pointer p, size_type n) {
            memory_manager->release_memory(p);
        }

        size_type max_size() const {
            return std::numeric_limits<size_type>::max();
        }

        template< class U, class... Args >
        void construct(U* p, Args &&... args) {
            ::new((void *)p) U(std::forward<Args>(args)...);
        }

        template< class U >
        void destroy(U * p) {
            p->~U();
        }
    };
    
}}
