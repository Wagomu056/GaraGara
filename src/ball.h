//
// Created by 東口拓也 on 2022/07/29.
//

#ifndef BOUND_BALL_BALL_H
#define BOUND_BALL_BALL_H

#include <pd_api.h>

typedef void (* BallStopHandler)(void);

void initBall(PlaydateAPI* pd);
void spawnBall(int x, int y);
void updateBall(void);
void registerBallStop(BallStopHandler handler);
void clearBall(void);

#endif //BOUND_BALL_BALL_H
