//
// Created by 東口拓也 on 2022/07/17.
//
#include <stdlib.h>
#include "include/lottery.h"

static const int NAME_NUM = 16;

static const char *_names[NAME_NUM] = { 0 };
static int _registerNum = 0;

void registerLottery(const char* name)
{
    if (_registerNum >= NAME_NUM)
        return;

    _names[_registerNum] = name;
    _registerNum++;
}

static void swapName(int a, int b)
{
    const char *tmp = _names[a];
    _names[a] = _names[b];
    _names[b] = tmp;
}

const char* lottery(void)
{
    if (_registerNum == 0)
        return "";

    const int rnd = rand() % _registerNum;
    const char *ret = _names[rnd];

    swapName(rnd, _registerNum - 1);
    _registerNum--;

    return ret;
}
