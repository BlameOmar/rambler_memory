/**************************************************************************************************
 * @file    MemoryManager.hpp
 * @date    2014-12-13
 * @author  Omar Stefan Evans
 **************************************************************************************************/

#include "MemoryManager.hpp"

#include <cstdlib>
#include <iostream>

#include "SafeInt3.hpp"

namespace rambler { namespace memory {
    
    MemoryManager * MemoryManager::default_manager() {
        static MemoryManager * _default_manager = new MemoryManager;

        return _default_manager;
    }



    void * MemoryManager::reserve_memory(size_t n, size_t size) {
        size_t amount;
        if (!SafeMultiply(n, size, amount)) {
            return nullptr;
        }

        return reserve_memory(amount);
    }



    void * MemoryManager::reserve_memory(size_t amount) {
        void * ptr = calloc(amount, 1);

        if (ptr == nullptr) {
            return ptr;
        }

#ifdef DEBUG_SHARED_MEMORY
        std::cout << "Reserved " << amount << " bytes of memory at " << ptr << std::endl;
#endif

        share_memory(ptr);

        return ptr;
    }



    void MemoryManager::release_memory(void * ptr) {
        /* NOTE: Replace lock/unlock with lock_shared/unlock_shared once shared_timed_mutex
         * becomes available.
         */

        mutex.lock();

        if (ref_count.count(ptr) == 0) {
            mutex.unlock();
            return; // Consider throwing an exception instead.
        }

        if (--ref_count.at(ptr) == 0) {
            mutex.unlock();

#ifdef DEBUG_SHARED_MEMORY
            std::cout << "Released shared memory at " << ptr << std::endl;
            std::cout << "No longer sharing memory at " << ptr << std::endl;
#endif

            return free_memory(ptr);
        }

        mutex.unlock();
        std::cout << "Released shared memory at " << ptr << std::endl;
    }



    void MemoryManager::share_memory(void * ptr) {
        /* NOTE: Replace lock/unlock with lock_shared/unlock_shared, where appropriate,
         * once shared_timed_mutex becomes available.
         */

        mutex.lock();

        if (ref_count.count(ptr) == 0) {
            ref_count[ptr] = 1;

#ifdef DEBUG_SHARED_MEMORY
            std::cout << "Shared memory at " << ptr << std::endl;
#endif

        } else {
            ++ref_count.at(ptr);

#ifdef DEBUG_SHARED_MEMORY
            std::cout << "Sharing shared memory at " << ptr << std::endl;
#endif
        }

        mutex.unlock();
    }




    void MemoryManager::free_memory(void * ptr) {
        /* NOTE: Replace lock/unlock with lock_shared/unlock_shared once shared_timed_mutex
         * becomes available.
         */

        mutex.lock();

        if (ref_count.count(ptr) == 0) {
            mutex.unlock();
            return; // Consider throwing an exception instead.
        }

        ref_count.erase(ptr);

        mutex.unlock();

        free(ptr);

#ifdef DEBUG_SHARED_MEMORY
        std::cout << "Freed memory at " << ptr << std::endl;
#endif
    }



}}
