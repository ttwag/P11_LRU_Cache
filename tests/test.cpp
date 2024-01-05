#include <gtest/gtest.h>
#include "../LRUCache.h"
/*
 * Program's Vulnerability:
 * 1) Invalid memory address.
 * 2) Access null pointer in the doubly linked list.
 * 3) Improper ordering of doubly linked list nodes.
 * 4) Wrongly identifies the LRU block.
 */


// Invalid input into LRUCache constructor
TEST(Input, Test1) {
    EXPECT_NO_THROW(LRUCache* cache = new LRUCache(2));
    EXPECT_NO_THROW(LRUCache* cache = new LRUCache(1));
    EXPECT_NO_THROW(LRUCache* cache = new LRUCache(INT_MAX));
    EXPECT_THROW(LRUCache* cache = new LRUCache(-100), std::invalid_argument);
    EXPECT_THROW(LRUCache* cache = new LRUCache(INT_MIN), std::invalid_argument);
}
// Basic input into cache->read()
TEST(Input, Test2) {
    LRUCache* cache = new LRUCache(1);
    EXPECT_NO_THROW(cache->read(0x123c));
    EXPECT_NO_THROW(cache->read(0x0000));
    EXPECT_NO_THROW(cache->read(8));
    EXPECT_NO_THROW(cache->read(1));
    delete cache;
}

// Negative number
TEST(Input, Test3) {
    LRUCache* cache = new LRUCache(1);
    EXPECT_NO_THROW(cache->read(-0x0000));
    EXPECT_THROW(cache->read(-0x1000), std::invalid_argument);
    EXPECT_THROW(cache->read(-0x0001), std::invalid_argument);
    EXPECT_THROW(cache->read(-0xFFFF), std::invalid_argument);
    EXPECT_THROW(cache->read(-1), std::invalid_argument);
    EXPECT_THROW(cache->read(-5), std::invalid_argument);
    delete cache;
}

// Large Numbers and out of range
TEST(Input, Test4) {
    LRUCache* cache = new LRUCache(1);
    EXPECT_THROW(cache->read(INT_MAX), std::invalid_argument);
    EXPECT_THROW(cache->read(INT_MIN), std::invalid_argument);
    EXPECT_THROW(cache->read(0x11111), std::invalid_argument);
    EXPECT_THROW(cache->read(0x1FFFF), std::invalid_argument);
    EXPECT_THROW(cache->read(0x11111), std::invalid_argument);
    EXPECT_THROW(cache->read(0x10000), std::invalid_argument);
    delete cache;
}

// Boundary Numbers
TEST(Input, Test5) {
    LRUCache* cache = new LRUCache(1);
    EXPECT_NO_THROW(cache->read(0xFFFF));
    EXPECT_NO_THROW(cache->read(0x00000));
    delete cache;
}

// Replacement When Size is 1
TEST(LRU_Replace, Test6) {
    LRUCache* cache = new LRUCache(1);
    // Test different tag
    for (int i = 0; i < 100; i++) {
        EXPECT_FALSE(cache->read(0x1114));
        EXPECT_FALSE(cache->read(0x1118));
    }
    // Test three tags. The First two are the same, and the last one is different
    for (int i = 0; i < 100; i++) {
        EXPECT_FALSE(cache->read(0x1114));
        EXPECT_TRUE(cache->read(0x1116));
        EXPECT_FALSE(cache->read(0x111F));
    }
    delete cache;
}

// Test replacement of first added address with cache size 4
TEST(LRU_Replace, Test7) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_FALSE(cache->read(0xFFFF));
    EXPECT_TRUE(cache->read(0xFFFF));
    EXPECT_FALSE(cache->read(0x1234));
}

// Test replacement of first added address with cache size 4
TEST(LRU_Replace, TEST8) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0xFF12));
    EXPECT_TRUE(cache->read(0xFF12));
    EXPECT_FALSE(cache->read(0x1234));
    delete cache;
}

// Test replacement of first added address with cache size 4
TEST(LRU_Replace, TEST9) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_FALSE(cache->read(0xFFFF));
    EXPECT_TRUE(cache->read(0xFFFF));
    EXPECT_FALSE(cache->read(0x1234));
    delete cache;
}
// Test replacement of first added address with cache size 4

TEST(LRU_Replace, Test10) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0xFFF1));
    EXPECT_TRUE(cache->read(0xFFF2));
    EXPECT_FALSE(cache->read(0x1234));
    delete cache;
}

// Test replacement of first added address with cache size 4
TEST(LRU_Replace, Test11) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0xFFF3));
    EXPECT_TRUE(cache->read(0xFFF2));
    EXPECT_FALSE(cache->read(0x1234));
    delete cache;
}

// Test replacement of first added address with cache size 4
TEST(LRU_Replace, Test12) {
    LRUCache* cache = new LRUCache(4);
    EXPECT_FALSE(cache->read(0x1234));
    EXPECT_FALSE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0x3456));
    EXPECT_FALSE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x4567));
    EXPECT_TRUE(cache->read(0x3456));
    EXPECT_TRUE(cache->read(0x2345));
    EXPECT_FALSE(cache->read(0xFFFC));
    EXPECT_TRUE(cache->read(0xFFFD));
    EXPECT_FALSE(cache->read(0x1234));
    delete cache;
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

