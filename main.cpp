#include <iostream>
#include "LRUCache.h"

int main() {
    LRUCache* cache = new LRUCache(2);
    cache->read(0x1234);
    cache->read(0x1235);
    cache->read(0x1236);
    cache->read(0x1235);
    cache->read(0x1238);
    cache->read(0x1239);
    cache->read(0x1239);
    cache->printCache();
    return 0;
}