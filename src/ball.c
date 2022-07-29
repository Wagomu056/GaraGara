//
// Created by 東口拓也 on 2022/07/29.
//

#include "ball.h"
#include "pd_uitl.h"
#include "vec2.h"
#include "math_util.h"

static const float FLOOR_HEIGHT = 220.0f;
static const float ADD_VEL = 1.0f;

static PlaydateAPI* _pd;
static LCDBitmap *_image = NULL;
static LCDSprite *_sprite = NULL;

static struct Vec2 _pos = {0.0f, 0.0f};
static float _velX = 0.0f;
static float _velY = 0.0f;

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
    _velX = -1.0f;
    _velY = 0.0f;

    _pd->sprite->addSprite(_sprite);
    _pos.x = x,
    _pos.y = y;
}

void updateBall(void)
{
    _pos.x += _velX;

    _velY += ADD_VEL;
    _pos.y += _velY;

    if (_velY > 0.0f && _pos.y >= FLOOR_HEIGHT) {
        _velY *= -0.7f;
        _velX = clamp(_velX + 0.2f, -1.0f, 0.0f);
    }

    if (_pos.y >= FLOOR_HEIGHT) {
        _pos.y = FLOOR_HEIGHT;
    }

    _pd->sprite->moveTo(_sprite,
                        _pos.x, _pos.y);
}