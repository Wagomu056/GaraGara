//
// Created by 東口拓也 on 2022/07/23.
//

#ifndef BOUND_BALL_GARA_H
#define BOUND_BALL_GARA_H

#include <pd_api.h>

typedef void (* BallSpawnHandler)(void);

void initGara(PlaydateAPI* pd);
void updateGara(float garaRotDeg);
void registerBallSpawn(BallSpawnHandler handler);
void clearIsBallIn(void);

#endif //BOUND_BALL_GARA_H
