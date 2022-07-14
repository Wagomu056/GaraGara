//
// Created by 東口拓也 on 2022/07/09.
//

#ifndef BOUND_BALL_NAME_DRAWER_H
#define BOUND_BALL_NAME_DRAWER_H

#include <pd_api.h>

void initName(PlaydateAPI* pd);
void startName(const char *name, int count);
void updateName(LCDRect* drawRect);

#endif //BOUND_BALL_NAME_DRAWER_H
