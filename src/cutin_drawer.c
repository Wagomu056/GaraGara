//
// Created by 東口拓也 on 2022/07/09.
//

#include "cutin_drawer.h"
#include "defines.h"
#include "math_util.h"

static const float DISPLAY_CENTER = 120.0f;
static const int BOARDER_WIDTH = 2;

static const int DOUBLE_LINE_GAP = 5;

static const float MOVE_SPEED = 1.0f / 10.0f;
static const float MOVE_START = 0.0;
static const float MOVE_DEST = -75.0f;

static PlaydateAPI* _pd;
static float _moveRatio = 1.0f;
static int _isStarted = 0;

void initCutin(PlaydateAPI* pd)
{
    _pd = pd;
}

void startCutin(void)
{
    _moveRatio = 0.0f;
    _isStarted = 1;
}

static void updateMoveRatio(float *ratio)
{
    if (*ratio >= 1.0f) return;

    *ratio += MOVE_SPEED;
    if (*ratio >= 1.0f) {
        *ratio = 1.0f;
    }
}

static void drawBorderLine(float y)
{
    const float dy = DISPLAY_CENTER + y;
    _pd->graphics->drawLine(0, dy, DISPLAY_WIDTH, dy, BOARDER_WIDTH,
                            kColorBlack);
}

static void drawDoubleLine(float y, float gap)
{
    drawBorderLine(y);
    drawBorderLine(y - gap);
}

void updateCutin(void)
{
    if (!_isStarted) return;

    updateMoveRatio(&_moveRatio);

    const float ratio = easeInOut(_moveRatio);
    const float lineY = linear(MOVE_START, MOVE_DEST, ratio);
    drawDoubleLine(lineY, DOUBLE_LINE_GAP);
    drawDoubleLine(-1.0f * lineY, -1.0f * DOUBLE_LINE_GAP);

    _pd->graphics->fillRect( 0.0f, DISPLAY_CENTER + lineY,
                             DISPLAY_WIDTH, -2.0f * lineY, kColorBlack );

    const float CHAR_WIDTH = 45;
    const float CHAR_HEIGHT = 45;
    _pd->graphics->fillRect( 20.0f, DISPLAY_CENTER - (CHAR_HEIGHT * 0.5f),
                             CHAR_WIDTH, CHAR_HEIGHT, kColorWhite );
}