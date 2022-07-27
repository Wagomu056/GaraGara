//
// Created by 東口拓也 on 2022/07/09.
//

#ifndef BOUND_BALL_CUTIN_DRAWER_H
#define BOUND_BALL_CUTIN_DRAWER_H

#include <pd_api.h>

typedef void (* CutinEndHandler)(void);

void initCutin(PlaydateAPI* pd);
void startCutin(const char *name);
void updateCutin(void);
void registerCutinEnd(CutinEndHandler handler);
void clearCutin(void);

#endif //BOUND_BALL_CUTIN_DRAWER_H
