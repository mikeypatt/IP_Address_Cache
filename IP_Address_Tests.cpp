//
// Created by Michael Patterson on 18/10/2020.
//
#include <gtest/gtest.h>
#include "IP_Address.h"

using testing::Eq;

struct IPAddressTests : public testing::Test
{
    IP_Address* Address1;
    IP_Address* Address2;

    IPAddressTests()  {
        Address1 = new IP_Address(192,168,0,1);
        Address2 = new IP_Address(194,168,0,1);
    }

    ~IPAddressTests() override{
        delete Address1;
        delete Address2;
    }
};

TEST_F (IPAddressTests, displayIPAddressTest) {
    ASSERT_STREQ(Address1->format().c_str(),"192.168.0.1");
    ASSERT_STREQ(Address2->format().c_str(),"194.168.0.1");
}

TEST_F (IPAddressTests, ComparingTwoAddressTest) {
    ASSERT_TRUE(Address1<Address2);
}
