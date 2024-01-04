#include <unordered_map>
#ifndef P11_LRU_CACHE_LRUCACHE_H
#define P11_LRU_CACHE_LRUCACHE_H


class LRUCache {
private:
    struct cacheNode;
    int max_capacity;
    int curr_capacity;
    std::unordered_map<int, cacheNode*> cache_table;
    int LRU;
    cacheNode* head;
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
    ~LRUCache();
};


#endif
