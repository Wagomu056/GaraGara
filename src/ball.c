//
// Created by 東口拓也 on 2022/07/29.
//

#include "ball.h"
#include "pd_uitl.h"
#include "vec2.h"
#include "math_util.h"
#include "log.h"

static const float FLOOR_HEIGHT = 220.0f;
static const float ADD_VEL = 1.0f;

static PlaydateAPI* _pd;
static LCDBitmap *_image = NULL;
static LCDSprite *_sprite = NULL;

static struct Vec2 _pos = {0.0f, 0.0f};
static struct Vec2 _prevPos = {0.0f, 0.0f};
static float _velX = 0.0f;
static float _velY = 0.0f;

static int _isSpawn = 0;
static int _stopTime = 0;
static BallStopHandler _handler = NULL;

void initBall(PlaydateAPI* pd)
{
    _pd = pd;

    _image = loadImageAtPath(pd, "images/ball.png");
    {
        _sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(_sprite, _image, kBitmapUnflipped);
        _pd->sprite->setZIndex(_sprite, 700);
    }
}

void spawnBall(int x, int y)
{
    _velX = 2.0f;
    _velY = 0.0f;

    _pd->sprite->addSprite(_sprite);
    _pos.x = x,
    _pos.y = y;
    _pd->sprite->moveTo(_sprite,
                        _pos.x, _pos.y);

    _isSpawn = 1;
}

int checkStop(void)
{
    if (_pos.x != _prevPos.x) {
        _stopTime = 0;
        _prevPos = _pos;
        return 0;
    }

    if (_pos.y != _prevPos.y) {
        _stopTime = 0;
        _prevPos = _pos;
        return 0;
    }

    _stopTime++;
    _prevPos = _pos;
    return (_stopTime >= 30) ? 1 : 0;
}

void updateBall(void)
{
    if (!_isSpawn) return;

    _pos.x += _velX;

    _velY += ADD_VEL;
    _pos.y += _velY;

    if (_velY > 0.0f && _pos.y >= FLOOR_HEIGHT) {
        _velY *= -0.6f;
        _velX = clamp(_velX - 0.3f, 0.0f, 2.0f);
    }

    if (_pos.y >= FLOOR_HEIGHT) {
        _pos.y = FLOOR_HEIGHT;
    }

    _pd->sprite->moveTo(_sprite,
                        _pos.x, _pos.y);

    if (checkStop()) {
        _isSpawn = 0;
        if (_handler) _handler();
    }
}

void registerBallStop(BallStopHandler handler)
{
    _handler = handler;
}

void clearBall(void)
{
    _pd->sprite->removeSprite(_sprite);
}