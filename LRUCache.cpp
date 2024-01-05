#include "LRUCache.h"
#include <unordered_map>
#include <iostream>

LRUCache::LRUCache(int capacity) : blockCount(0), readCount(0), hitCount(0), missCount(0), LRU(-1){
    if (capacity <= 0) throw std::invalid_argument("Invalid Cache Size");
    setCapacity = capacity;
    blockCount = 0, readCount = 0, hitCount = 0, missCount = 0;
    LRU = -1;
    head = new cacheBlock(-1);
}
bool LRUCache::read(int address) {
    // Extracts the tag from the memory address
    int tag = getTag(address);
    if (address > 0xFFFF) throw std::invalid_argument("Invalid Address: Input Address Must Be 16 bits");
    if (address < 0) throw std::invalid_argument("Invalid Address: Input Must Be An Positive Integer");
    readCount++;
//    int tag = address;

    // If the tag is in the cache set
    if (cacheSet.find(tag) != cacheSet.end()) {
        blockToMRU(tag, cacheSet[tag], true);
        hitCount++;
        return true;
    }

    // If the tag is not in the cache set
    cacheBlock* block = new cacheBlock(tag);
    if (blockCount == setCapacity) {
        evict();
        blockCount--;
    }
    cacheSet[tag] = block;
    blockToMRU(tag, block, false);
    blockCount++;
    missCount++;
    return false;
}

void LRUCache::printCache() {
    double hitRate = hitCount / readCount * 100;
    double missRate = missCount / readCount * 100;
    std::cout<<"Hit Rate: "<<hitRate<<std::endl;
    std::cout<<"Miss Rate: "<<missRate<<std::endl;
    std::cout<<"Memory Address"<<std::endl;
    cacheBlock* printer = cacheSet[LRU];
    std::cout<<"LRU:    "<<std::hex<<(printer->tag << 2)<<std::endl;
    printer = printer->prev;
    while (printer != head) {
        if (printer->prev == head) {
            std::cout<<"MRU:    "<<std::hex<<(printer->tag << 2)<<std::endl;
        }
        else {
            std::cout<<"        "<<std::hex<<(printer->tag << 2)<<std::endl;
        }
        printer = printer->prev;
    }
}

LRUCache::~LRUCache() {
    cacheBlock* remover = head->next;
    head->next = nullptr;
    while (remover) {
        cacheBlock* temp = remover->next;
        delete remover;
        remover = temp;
    }
    return;
}

// If a block is present (1), make it MRU. If not, create a block and make it MRU.
void LRUCache::blockToMRU(int tag, cacheBlock* block, bool present) {
    // If the block is present
    if (present) {
        // Return if the block is MRU currently
        if (head->next == block) return;

        cacheBlock* temp = head->next;
        block->prev->next = block->next;
        // Make sure the LRU is passed to the prev cacheBlock
        if (LRU == block->tag) LRU = block->prev->tag;
        else block->next->prev = block->prev;
        temp->prev = block;
        block->next = temp;
        block->prev = head;
        head->next = block;
        return;
    }

    // If there's no block
    if (!head->next) {
        head->next = block;
        block->prev = head;
        // Initialize the LRU
        LRU = tag;
    }
    // If there are blocks
    else {
        cacheBlock* temp = head->next;
        temp->prev = block;
        block->next = temp;
        head->next = block;
        block->prev = head;
    }
    return;
}
    int LRUCache::getTag(int address) {
        // Extracts the tag
        return (0x3 | address) >> 2;
    }
void LRUCache::evict() {
    // Remove LRU;
    cacheBlock* new_LRU = cacheSet[LRU]->prev;
    new_LRU->next = nullptr;
    delete cacheSet[LRU];
    cacheSet.erase(LRU);
    LRU = new_LRU->tag;
}

