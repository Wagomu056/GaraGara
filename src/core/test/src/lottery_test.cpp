//
// Created by 東口拓也 on 2022/07/17.
//
#include "gtest/gtest.h"

extern "C" {
#include <lottery.h>
}

TEST(Lottery, lotteryOne) {
    registerLottery("ABC");
    const char *ret = lottery();
    EXPECT_STREQ("ABC", ret);
}

static std::vector<std::string> returns;
static std::vector<std::string> registered;
TEST(Lottery, lotteryMulti) {
    registerLottery("ABC"); registered.push_back("ABC");
    registerLottery("EFG"); registered.push_back("EFG");
    registerLottery("HIJ"); registered.push_back("HIJ");
    registerLottery("KLM"); registered.push_back("KLM");

    for (int i = 0; i < 4; i++) {
        const char *ret = lottery();
        for (auto pair : returns) {
            EXPECT_STRNE(pair.c_str(), ret);
        }
        returns.push_back(ret);

        bool exists = false;
        for (auto pair : registered) {
            if (strcmp(pair.c_str(), ret) == 0) {
                exists = true;
                break;
            }
        }
        EXPECT_TRUE(exists);
    }
}
