#include "LRUCache.h"
#include <unordered_map>
#include <iostream>

/*
 * I/O: The constructor accepts a positive integer size, then creates an LRUCache object.
 *
 * Description: The LRUCache constructor initializes every attribute and the cacheBlock list.
 */
LRUCache::LRUCache(int capacity) {
    if (capacity <= 0) throw std::invalid_argument("Invalid Cache Size");
    setCapacity = capacity;
    blockCount = 0, readCount = 0, hitCount = 0, missCount = 0;
    LRU = -1;
    head = new cacheBlock(-1);
}

/*
 * I/O: The read() method accepts any 16-bit positive integer address and returns true if the read is a cache hit and false if it's a cache miss.
 *
 * Description: read() has a time complexity of O(1).
 *              It looks up a tag through the hash-map (cacheSet) and uses a doubly linked list (cacheBlock) to record the ordering for the LRU policy.
 *              Each tag is associated with a cacheBlock pointer in the cacheSet, so we could locate each cacheBlock in constant time.
 *
 *              The read method takes the input memory address, extracts the tag bits, then checks if the tag is present in the cacheSet.
 *              If it's present (cache hit), reorder the cacheBlock as the MRU.
 *              If it's not present (cache miss), add it to the cacheSet, the list of cacheBlocks, and make it as MRU. If the cache is full, evict LRU first then add.
 *              The readCount is incremented every time read() is called. The hitCount is incremented for cache hit, and missCount for cache miss.
 */
bool LRUCache::read(int address) {
    // Extracts the tag from the memory address and checks invalid input
    int tag = getTag(address);
    if (address > 0xFFFF) throw std::invalid_argument("Invalid Address: Input Address Must Be 16 bits");
    if (address < 0) throw std::invalid_argument("Invalid Address: Input Must Be An Positive Integer");
    readCount++;

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

/*
 * I/O: the printCache method prints the current cache hit, miss, and the stored tag in hexadecimal with the two LSB as 0.
 *      The tags are printed from LRU (top) to MRU (bottom).
 *
 * Description: It performs arithmetics on hitCount, missCount, and readCount to calculate the hit-and-miss rate.
 *              It first locates the LRU block in the cacheBlock list, prints it, then traverses backward to head and prints cacheBlocks along the way.
 *
 */
void LRUCache::printCache() {
    double hitRate = hitCount / readCount * 100;
    double missRate = missCount / readCount * 100;
    std::cout<<"Hit Rate: "<<hitRate<<std::endl;
    std::cout<<"Miss Rate: "<<missRate<<std::endl;
    std::cout<<"Memory Address"<<std::endl;
    cacheBlock* printer = cacheSet[LRU];
    std::cout<<"LRU:    "<<std::hex<<(printer->tag)<<std::endl;
    printer = printer->prev;
    while (printer != head) {
        if (printer->prev == head) {
            std::cout<<"MRU:    "<<std::hex<<(printer->tag)<<std::endl;
        }
        else {
            std::cout<<"        "<<std::hex<<(printer->tag)<<std::endl;
        }
        printer = printer->prev;
    }
}

/*
 * Description: the destructor function deletes all dynamically created cacheBlocks in the linked list when the LRUCache object is deleted.
 */
LRUCache::~LRUCache() {
    // creates a separate remover pointer to delete all added blocks
    cacheBlock* remover = head->next;
    head->next = nullptr;
    while (remover) {
        cacheBlock* temp = remover->next;
        delete remover;
        remover = temp;
    }
    return;
}

/*
 * I/O: The private method blockToMRU takes the tag and its cacheBlock, and a bool variable, present, that indicates if the cacheBlock is present already.
 *       Regardless the present is true or not, the blockToMRU make the cacheBlock the MRU.
 *
 * Description: If a cacheBlock is present (true), make it the MRU by relinking the cacheBlock to head->next.
 *              If not present (false), link the cacheBlock to head->next and make it MRU.
 *
 * Note: We must be careful when relinking the linked list. There could be edge cases such as a cacheBlock is present and
 *       is the current LRU. Before making it head->next, we must update the LRU to the prev cacheBlock.
 *
 *       To ensure the relinking works properly, 24 test cases with different read combinations are included in the test folder.
 */
void LRUCache::blockToMRU(int tag, cacheBlock* block, bool present) {
    // If the cacheBlock is present
    if (present) {
        // Return if the block is MRU currently
        if (head->next == block) return;
        cacheBlock* temp = head->next;
        block->prev->next = block->next;

        // If the block is LRU, make sure the LRU is passed to the prev cacheBlock.
        if (LRU == block->tag) LRU = block->prev->tag;
        //If the block is not LRU, it means that block->next != nullptr, so we could access it
        else block->next->prev = block->prev;


        temp->prev = block;
        block->next = temp;
        block->prev = head;
        head->next = block;
        return;
    }

    // If the cacheBlock is not present
    // If there's no cacheBlock in LRUCache
    if (!head->next) {
        head->next = block;
        block->prev = head;
        // Initialize the LRU
        LRU = tag;
    }
    else {
        cacheBlock* temp = head->next;
        temp->prev = block;
        block->next = temp;
        head->next = block;
        block->prev = head;
    }
    return;
}

/*
 * I/O: The getTag() method takes the memory address as the input and return only the unique 14-bits tag with 2 zeros at the 2 LSB.
 *
 * Description: getTag() uses bit manipulation to extract the 14 bits on the left.
 */
int LRUCache::getTag(int address) {
    return 0xFFFC & address;
}

/*
 * I/O: The evict() method removes the current LRU cacheBlock from the list and cacheSet.
 */
void LRUCache::evict() {
    // Initialize the new LRU as the cacheBlock->prev of current LRU;
    cacheBlock* new_LRU = cacheSet[LRU]->prev;
    new_LRU->next = nullptr;
    delete cacheSet[LRU];
    cacheSet.erase(LRU);
    LRU = new_LRU->tag;
}

