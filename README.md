# Heap-Management-Scheme

Implemented a program in C to demonstrate heap management scheme using ‘allocate’ and ‘free’ functions ensuring that adjacent free blocks are merged together.

While allocating memory, metadata(data about the memory) is stored adjacent to allocated memory in order to keep a track of all other memory blocks. Using first fit strategy I allocated memory using 'Malloc' function and seperated allocated blocks from freelist. Implemented free function and merged adjacent blocks using merge function.

**This repository contains a .c file where the whole source code is written and a pdf file where the scheme is clearly demonstrated. 
