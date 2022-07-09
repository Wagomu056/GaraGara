//
// Created by 東口拓也 on 2022/07/09.
//

#include "cutin_drawer.h"
#include "defines.h"
#include "math_util.h"
#include "pd_uitl.h"

static const float DISPLAY_CENTER_X = DISPLAY_WIDTH * 0.5f;
static const float DISPLAY_CENTER_Y = DISPLAY_HEIGHT * 0.5f;

static const float MOVE_SPEED = 1.0f / 10.0f;
static const float MOVE_START = 0.0;
static const float MOVE_DEST = -75.0f;

static PlaydateAPI* _pd;
static float _moveRatio = 1.0f;
static int _isStarted = 0;

static LCDBitmap *_image = NULL;

static const int BOARDER_NUM = 2;
static LCDSprite *_sprites[BOARDER_NUM] = {NULL};

void initCutin(PlaydateAPI* pd)
{
    _pd = pd;
    _image = loadImageAtPath(pd, "images/boarder.png");

    for (int i = 0; i < BOARDER_NUM; i++)
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _image, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 999);
        _sprites[i] = sprite;
    }
}

void startCutin(void)
{
    _moveRatio = 0.0f;
    _isStarted = 1;

    for (int i = 0; i < BOARDER_NUM; i++)
    {
        _pd->sprite->addSprite(_sprites[i]);
        _pd->sprite->moveTo(_sprites[i], DISPLAY_CENTER_X, DISPLAY_CENTER_Y);
    }
}

static void updateMoveRatio(float *ratio)
{
    if (*ratio >= 1.0f) return;

    *ratio += MOVE_SPEED;
    if (*ratio >= 1.0f) {
        *ratio = 1.0f;
    }
}

static void moveBoarder(int idx, float y)
{
    _pd->sprite->moveTo(_sprites[idx], DISPLAY_CENTER_X, DISPLAY_CENTER_Y + y);
}

void updateCutin(void)
{
    if (!_isStarted) return;

    updateMoveRatio(&_moveRatio);

    const float ratio = easeInOut(_moveRatio);
    const float lineY = linear(MOVE_START, MOVE_DEST, ratio);
    moveBoarder(0, lineY);
    moveBoarder(1, -1.0f * lineY);
}