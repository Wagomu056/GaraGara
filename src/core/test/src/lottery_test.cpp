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
TEST(Lottery, lotteryMulti) {
    registerLottery("ABC");
    registerLottery("EFG");
    registerLottery("HIJ");
    registerLottery("KLM");

    for (int i = 0; i < 4; i++) {
        const char *ret = lottery();
        for (auto pair : returns) {
            EXPECT_STRNE(pair.c_str(), ret);
        }

        returns.push_back(ret);
    }
}
