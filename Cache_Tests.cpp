//
// Created by Michael Patterson on 18/10/2020.
//
#include <gtest/gtest.h>
#include "Cache.h"
#include "IP_Address.h"

using testing::Eq;

struct CacheTests : public testing::Test
{
    Cache* test_cache;

    CacheTests()  {
        test_cache = new Cache(4);
    }

    ~CacheTests() override{
        delete test_cache;
    }
};

TEST_F (CacheTests, CacheSizeDoesNotIncreaseWhenConnectionExists) {

    IP_Address *IP1,*IP2;
    IP1 = new IP_Address(192,168,0,1);
    IP2 = new IP_Address(193,168,0,1);

    uint16_t port1 = 12;
    uint16_t port2 = 18;

    test_cache->add_cache(IP1, port1, IP2, port2);
    test_cache->add_cache(IP1, port1, IP2, port2);

    ASSERT_EQ(test_cache->get_size(), 1);
}

TEST_F (CacheTests, NumberofLookUpsInCreasesWithExistingEntryTest) {

    IP_Address *IP1,*IP2;
    IP1 = new IP_Address(192,168,0,1);
    IP2 = new IP_Address(193,168,0,1);

    uint16_t port1 = 12;
    uint16_t port2 = 18;

    test_cache->add_cache(IP1, port1, IP2, port2);
    test_cache->add_cache(IP1, port1, IP2, port2);

    ASSERT_EQ(test_cache->lookup_cache(IP1, port1, IP2, port2).second, 3);
}

TEST_F (CacheTests, DisplaySpecificationSequenceTest) {

    IP_Address *IP1,*IP2,*IP3,*IP4;
    IP1 = new IP_Address(192,168,0,1);
    IP2 = new IP_Address(193,168,0,1);
    IP3 = new IP_Address(193,167,0,1);
    IP4 = new IP_Address(193,167,4,1);

    uint16_t port1 = 12;
    uint16_t port2 = 18;
    uint16_t port3 = 11;
    uint16_t port4 = 14;

    std::pair<std::string,int> ans;

    ans = test_cache->add_cache(IP1, port1, IP2, port2);
    ASSERT_STREQ(ans.first.c_str(), "new");
    ASSERT_EQ(ans.second, 1);

    ans = test_cache->lookup_cache(IP3, port3, IP1, port1);
    ASSERT_STREQ(ans.first.c_str(), "F");
    ASSERT_EQ(ans.second, 0);

    ans = test_cache->add_cache(IP1, port1, IP3, port3);
    ASSERT_STREQ(ans.first.c_str(), "new");
    ASSERT_EQ(ans.second, 1);

    ans = test_cache->lookup_cache(IP2, port2, IP1, port1);
    ASSERT_STREQ(ans.first.c_str(), "T");
    ASSERT_EQ(ans.second, 2);

    ans = test_cache->add_cache(IP2, port2, IP1, port1);
    ASSERT_STREQ(ans.first.c_str(), "existing");
    ASSERT_EQ(ans.second, 3);

    ans = test_cache->add_cache(IP1, port1, IP2, port2);
    ASSERT_STREQ(ans.first.c_str(), "existing");
    ASSERT_EQ(ans.second, 4);

    ans = test_cache->lookup_cache(IP1, port1, IP2, port2);
    ASSERT_STREQ(ans.first.c_str(), "T");
    ASSERT_EQ(ans.second, 5);

    ans = test_cache->lookup_cache(IP1, port1, IP3, port3);
    ASSERT_STREQ(ans.first.c_str(), "T");
    ASSERT_EQ(ans.second, 2);

    ans = test_cache->lookup_cache(IP1, port1, IP4, port4);
    ASSERT_STREQ(ans.first.c_str(), "F");
    ASSERT_EQ(ans.second, 0);


    // code to redirect std output to a stringsteam
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    test_cache->dump();
    std::cout.rdbuf(sbuf);

    std::string output = buffer.str();
    ASSERT_STREQ(output.c_str(), "192.168.0.1,0 <-> 193.167.0.1,0: 2\n192.168.0.1,0 <-> 193.168.0.1,0: 5\n");






}


