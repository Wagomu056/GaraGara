//
// Created by 東口拓也 on 2022/07/09.
//

#include "cutin_drawer.h"
#include "defines.h"
#include "math_util.h"
#include "pd_uitl.h"
#include "name_drawer.h"

static const float DISPLAY_CENTER_X = DISPLAY_WIDTH * 0.5f;
static const float DISPLAY_CENTER_Y = DISPLAY_HEIGHT * 0.5f;

static const float QUICK_SPEED = 1.0f / 20.0f;
static const float QUICK_WAIT_SPEED = 1.0f / 20.0f;
static const float MAIN_OPEN_SPEED = 1.0f / 5.0f;

static const float QUICK_OPEN_START = 0.0;
static const float QUICK_OPEN_DEST = -15.0f;
static const float MAIN_OPEN_DEST = -75.0f;

static const int SPRITE_Z = 900;

static PlaydateAPI* _pd;
static float _moveRatio = 1.0f;

static LCDBitmap *_image = NULL;
static const int BOARDER_NUM = 2;
static LCDSprite *_sprites[BOARDER_NUM] = {NULL};

static LCDBitmap *_tileImage = NULL;
static LCDSprite *_tileSprite = NULL;

static CutinEndHandler _cutinEndHandler = NULL;

enum CutinStatus
{
    CUTIN_ST_NONE = 0,
    CUTIN_ST_QUICK,
    CUTIN_ST_QUICK_STOP,
    CUTIN_ST_MAIN,
};
static enum CutinStatus _status = CUTIN_ST_NONE;

void initCutin(PlaydateAPI* pd)
{
    _pd = pd;
    _image = loadImageAtPath(pd, "images/boarder.png");

    for (int i = 0; i < BOARDER_NUM; i++)
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _image, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, SPRITE_Z);
        _sprites[i] = sprite;
    }

    {
        _tileImage = loadImageAtPath(pd, "images/back_wa.png");
        _pd->graphics->tileBitmap(_tileImage, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, kBitmapUnflipped);

        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _tileImage, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, SPRITE_Z);
        _pd->sprite->moveTo(sprite, DISPLAY_CENTER_X, DISPLAY_CENTER_Y);

        _tileSprite = sprite;
    }

    initName(pd);
}

void startCutin(const char *name)
{
    _moveRatio = 0.0f;
    _status = CUTIN_ST_QUICK;

    for (int i = 0; i < BOARDER_NUM; i++)
    {
        _pd->sprite->addSprite(_sprites[i]);
        _pd->sprite->moveTo(_sprites[i], DISPLAY_CENTER_X, DISPLAY_CENTER_Y);
    }
    _pd->sprite->addSprite(_tileSprite);

    startName(name, sizeof(name));
}

static void updateMoveRatio(float *ratio, float speed)
{
    if (*ratio >= 1.0f) return;

    *ratio += speed;
    if (*ratio >= 1.0f) {
        *ratio = 1.0f;
    }
}

static void moveBoarder(int idx, float y)
{
    _pd->sprite->moveTo(_sprites[idx], DISPLAY_CENTER_X, DISPLAY_CENTER_Y + y);
}

static int updateCutinImpl(float *ratioWork, float speed, float start, float dest)
{
    updateMoveRatio(ratioWork, speed);

    const float ratio = easeInOut(*ratioWork);
    const float lineY = linear(start, dest, ratio);
    moveBoarder(0, lineY);
    moveBoarder(1, -1.0f * lineY);

    LCDRect rect = {0, DISPLAY_WIDTH,
                    DISPLAY_CENTER_Y + lineY + 4, DISPLAY_CENTER_Y + -1.0f * lineY - 4};
    _pd->sprite->setClipRect(_tileSprite, rect);

    updateName(&rect);

    return (*ratioWork >= 1.0f);
}

static int updateTimeOnly(float *ratioWork, float speed)
{
    updateMoveRatio(ratioWork, speed);
    return (*ratioWork >= 1.0f);
}

void updateCutin(void)
{
    switch (_status) {
        case CUTIN_ST_NONE:
            return;
        case CUTIN_ST_QUICK:
        {
            const int isEnd =
                    updateCutinImpl(&_moveRatio,
                                    QUICK_SPEED,
                                    QUICK_OPEN_START, QUICK_OPEN_DEST);
            if (isEnd) {
                _status = CUTIN_ST_QUICK_STOP;
                _moveRatio = 0.0f;
            }
            break;
        }
        case CUTIN_ST_QUICK_STOP:
        {
            const int isEnd =
                    updateTimeOnly(&_moveRatio, QUICK_WAIT_SPEED * 1.5f);
            if (isEnd) {
                _status = CUTIN_ST_MAIN;
                _moveRatio = 0.0f;
            }
           break;
        }
        case CUTIN_ST_MAIN:
        {
            updateCutinImpl( &_moveRatio,
                             MAIN_OPEN_SPEED,
                             QUICK_OPEN_DEST, MAIN_OPEN_DEST);
            break;
        }
    }
}

void registerCutinEnd(CutinEndHandler handler)
{
    _cutinEndHandler = handler;
}
