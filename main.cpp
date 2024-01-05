#include "LRUCache.h"

int main() {
    // Demo
    LRUCache* cache = new LRUCache(4);
    cache->read(0x1234);
    cache->read(0x1235);
    cache->read(0x1236);
    cache->read(0x1235);
    cache->read(0x1238);
    cache->read(0x1239);
    cache->read(0x1239);
    cache->read(0xFFFF);
    cache->read(0xFFFE);
    cache->read(0xFFFE);
    cache->read(0x3245);
    cache->read(0x3333);
    cache->printCache();
    return 0;
}