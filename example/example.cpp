/**************************************************************************************************
 * @file    example.cpp
 * @date    2014-12-16
 * @author  Omar Stefan Evans
 * @brief   An example of how to use rambler_memory
 **************************************************************************************************/


#include <iostream>
#include <vector>

#include "SharedMemoryAllocator.hpp"

int main(int argc, const char * argv[]) {

    std::vector<int, rambler::memory::SharedMemoryAllocator<int>> array(11);

    int i = 0;
    for (auto && element : array) {
        element = i * i;
        ++i;
    }

    for (auto element : array) {
        std::cout << element << " ";
    }

    std::cout << std::endl;

    return 0;

}
