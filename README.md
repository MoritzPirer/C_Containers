# C Containers

This library provides different Data Structures written in C17. All data structures are written in a way that they can be used with any constant-size type, i.e. they work with any type as long as the type has a fixed size (so, for example, no structs with flexible arrays). This is done internally using void pointers, which however looses the compile-time type checking. See the `READMEs` folder for READMEs for each individual data structure or the individual header files for more information.

## Finished Data Structures
- **vec**: Dynamically resizing array, including a bidirectional iterator
- **hset**: Unordered set implemented as a hash table, including a forward iterator

## Planned Data Structures

Upcoming data structures, in roughly the order the will be implemented:
- String (dynamically resizing)

- (Doubly) linked list
- Stack, queue, deque (wrappers around linked list)
- unordered map implemented as hash table
- ordered set & ordered map (implemented as some form of self-balancing binary tree)
- min / max heap
- bit set
- circle buffer
