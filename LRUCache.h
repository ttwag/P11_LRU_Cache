#include <unordered_map>
#ifndef P11_LRU_CACHE_LRUCACHE_H
#define P11_LRU_CACHE_LRUCACHE_H


class LRUCache {
public:
    LRUCache(int capacity);
    bool read(int address);
    void printCache();
    ~LRUCache();
private:
// Definition of a cacheBlock as a linked list
struct cacheBlock {
    int tag;
    cacheBlock* next;
    cacheBlock* prev;
    cacheBlock(int x): tag(x), next(nullptr), prev(nullptr){};
};
// Attributes
std::unordered_map<int, cacheBlock*> cacheSet;
cacheBlock* head;
int setCapacity;
int blockCount;
double readCount;
double hitCount;
double missCount;
int LRU; // LRU is always the last node of the cacheBlock linked list
// Methods
int getTag(int address);
void blockToMRU(int tag, cacheBlock* block, bool present);
void evict();
};
#endif
