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
// Definition of a cacheBlock as a doubly linked list
struct cacheBlock {
    int tag;
    cacheBlock* next;
    cacheBlock* prev;
    cacheBlock(int x): tag(x), next(nullptr), prev(nullptr){};
};

// Attributes
// cacheSet uses an unordered_map to look up the tag
std::unordered_map<int, cacheBlock*> cacheSet;
cacheBlock* head; //head is always the beginning of the cacheBlock linked list
int setCapacity;
int blockCount;
double readCount;
double hitCount;
double missCount;
int LRU; // LRU is always the last block's tag in the cacheBlock linked list

// Methods
void blockToMRU(int tag, cacheBlock* block, bool present);
int getTag(int address);
void evict();
};
#endif
