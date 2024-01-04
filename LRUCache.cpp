//
// Created by ttwag on 1/3/24.
//

#include "LRUCache.h"
#include <unordered_map>

struct LRUCache::cacheNode {
    std::pair<int, int> key_val = {};
    cacheNode* next;
    cacheNode* prev;
    cacheNode(int x, int y): key_val{x, y}, next(nullptr), prev(nullptr){};
};

LRUCache::LRUCache(int capacity) : max_capacity(capacity), curr_capacity(0), LRU(-1) {
    //std::unordered_map<int, cacheNode*> cache_table;
    head = new cacheNode(-1, -1);
}

int LRUCache::get(int key) {
// If the key is present
    if (cache_table.find(key) != cache_table.end()) {
        cacheNode* MRU = cache_table[key];
        if (head->next == MRU) return MRU->key_val.second;
        // Move the key to most recently used
        if (LRU == MRU->key_val.first) LRU = MRU->prev->key_val.first;
        cacheNode* temp = head->next;
        MRU->prev->next = MRU->next;
        if (MRU->next) MRU->next->prev = MRU->prev;
        temp->prev = MRU;
        MRU->next = temp;
        MRU->prev = head;
        head->next = MRU;
        return MRU->key_val.second;
    }
    // If the key is not present
    return -1;
}

void LRUCache::put(int key, int value) {
// Update the old key if it's present
    if (cache_table.find(key) != cache_table.end()) {
        // Move the key to most recently used
        get(key);
        cache_table[key]->key_val.second = value;
        return;
    }

    // Insert a new key if it's not present
    cacheNode* MRU = new cacheNode(key, value);
    cache_table[key] = MRU;

    // Discard a key if the table is full
    if (curr_capacity == max_capacity) {
        cacheNode* new_LRU = cache_table[LRU]->prev;
        new_LRU->next = nullptr;
        delete cache_table[LRU];
        cache_table.erase(LRU);
        LRU = new_LRU->key_val.first;
        curr_capacity--;
    }
    // Move MRU next to head as most recently used
    if (!head->next) {
        head->next = MRU;
        MRU->prev = head;
        // Initialize the LRU
        LRU = key;
    }
    else {
        cacheNode* temp = head->next;
        temp->prev = MRU;
        MRU->next = temp;
        head->next = MRU;
        MRU->prev = head;
    }
    curr_capacity++;
    return;
}

LRUCache::~LRUCache() {};