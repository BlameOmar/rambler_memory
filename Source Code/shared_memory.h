/**************************************************************************************************
 * @file    shared_memory.h
 * @date    2014-12-13
 * @author  Omar Stefan Evans
 **************************************************************************************************/

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Reserves a region of shared memory large enough to hold n objects
 * that are size bytes each and returns a pointer to it. Every byte
 * will be set to zero.
 * @param  n the number of objects
 * @param  size the size of each object
 * @return a pointer to the reserved region of shared memory, or NULL if there is an error.
 * @post   on success: n * size bytes of shared memory will have been reserved;
 *         on failure: zero bytes of memory will have been on reserved.
 * @see    shared_memory_release
 * @see    shared_memory_share
 */
void * shared_memory_reserve(size_t n, size_t size);

/**
 * Releases the shared memory pointed to by ptr.
 * The memory will be freed if nothing else is sharing it.
 * @pre   ptr points to the begining of a region of shared memory
 * @param ptr the memory to release
 * @post  The memory pointed to by ptr will have been released,
 *        and freed if nothing else is sharing it.
 * @see   free
 */
void shared_memory_release(void * ptr);

/**
 * Shares the memory pointed to by ptr.
 * @pre   ptr points to either the begining of a region of shared memory,
 *        or to the begining of a region of memory on which may be freed.
 * @param ptr the memory to share
 * @post  The memory pointed to by ptr will be shared.
 * @see   free
 */
void shared_memory_share(void * ptr);

#ifdef __cplusplus
}
#endif
