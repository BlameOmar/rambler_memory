# rambler_memory #

Rambler_memory is a tiny C++ library that enables manual reference counting using actual pointers.
In most cases std::shared_ptr in C++11 will be sufficient and you’ll have  no need for this library.
In fact, std::shared_ptr is probably better most of the time.  However, occasionally you may find
that is not sufficient to have an object that simply acts like a pointer (for example, when
interacting with a language that doesn’t support C++ objects, which is most of them).  In those
cases, you may find this library very useful.


## How to use rambler_memory ##

Memory management is done through the `MemoryManager` class.  The MemoryManager class has a
default manager, accessible through the static function `default_manager`.  You should use the
default manager whenever possible, but you can also create your own instances.  Memory management is
accomplished through the `reserve_memory`, `share_memory` and `release_memory` functions.
`reserve_memory` returns a zero-initialized region of memory that is already considered to be
shared. `share_memory` is used to start sharing memory that has not already been shared (ie. memory
allocated with `malloc`, but not `::new`) and to increase the reference count of memory that is
currently being shared.  `release_memory` decreases the reference count of any shared_memory, and
causes it to be freed when there is nothing sharing it anymore.


### Caution ###

* No region of memory should be managed by more than one memory manager.  This will lead to
  undefined and possibly catestrophic behavior.
* Memory that is being shared should not be freed directly.  Always use `release_memory`.


## STL Support ##

While you can use MemoryManager directly in your code, you can use the included
`SharedMemoryAllocator` class to use MemoryManager with STL classes like std::vector,
std::unordered_map, and even std::shared_ptr.  Instead of calling `new` and `delete`, through
the standard allocator, STL classes can be made to use the same `reserve_memory` and `share_memory`
functions on a MemoryManager instance of your choice.  Afterwards, you can then get the raw
pointer (usually through a function called `data` or `ptr`) and manually call those functions if
you need to.


## C-API ##

This library also exports a C-API so that it may be used widely.  The functions
`shared_memory_reserve`, `shared_memory_share`, and `shared_memory_release` equivalent to the
fuctions `reserve_memory`, `share_memory` and `release_memory` when called on the default manager.


## License ##

This library is licensed under a permisive (MIT) license.  See "LICENSE.md" for details.
