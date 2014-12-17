/**************************************************************************************************
 * @file    shared_memory.cpp
 * @date    2014-12-13
 * @author  Omar Stefan Evans
 **************************************************************************************************/

#include "shared_memory.h"
#include "MemoryManager.hpp"

void * shared_memory_reserve(size_t n, size_t size) {
    return rambler::memory::MemoryManager::default_manager()->reserve_memory(n, size);
}

void shared_memory_release(void * ptr) {
    return rambler::memory::MemoryManager::default_manager()->release_memory(ptr);
}

void shared_memory_share(void * ptr) {
    return rambler::memory::MemoryManager::default_manager()->share_memory(ptr);
}
