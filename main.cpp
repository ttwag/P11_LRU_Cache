#include "LRUCache.h"

int main() {
    // Demo
    LRUCache* myCache = new LRUCache(1);
    myCache->read(0x1111);  // If the cache is empty, this is a cache miss
    myCache->read(0x1111);  // This is a cache hit
    myCache->read(0x1113);  // This is a cache hit, 0x1111 and 0x1113 has the same tag
    myCache->read(0x1121);  // This is a cache miss, LRU will replace 0x1111's tag with that of 0x1121
    myCache->read(0x1111);  // This is a cache miss,
    myCache->printCache();
    return 0;
}