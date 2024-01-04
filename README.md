# P11_LRU_Cache
Simulate a fully-associative LRU cache

# Introduction
* It's a direct-mapped cache, so each block has a tag.
* Each memory address is 16 bits (EX: 0x0000). 
* Each memory address stores 8-bit of data (1 byte) and is byte-addressable.
* The cache block is structured as

| Valid | Tag | Data |
|------:|----:|-----:|


* There are 16 cache blocks, each could hold 4 bytes of data and is byte-addressable.

| Tag | Index | Block Offset |
|----:|------:|-------------:|
|  10 |     4 |            2 |
* For each memory address, the first 2 bits are the offset bits, the next 4 bit are the index bit, and the 10 bits are tag bits.

## How to Use this Program
* read: read the data of a memory address from the cache. If it's not present, move it to the cache.


