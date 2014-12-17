/**************************************************************************************************
 * @file    example.c
 * @date    2014-12-13
 * @author  Omar Stefan Evans
 * @brief   An example of how to use rambler_memory
 **************************************************************************************************/


#include <stdio.h>

#include "shared_memory.h"

int main(int argc, const char * argv[]) {

    size_t array_size = 11;
    int *array = shared_memory_reserve(array_size, sizeof(int));

    for (size_t i = 0; i < array_size; ++i) {
        array[i] = (int)(i * i);
    }

    for (size_t i = 0; i < array_size; ++i) {
        printf("%i ", array[i]);
    }
    puts("");

    shared_memory_release(array);

    return 0;
}
