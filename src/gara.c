//
// Created by 東口拓也 on 2022/07/23.
//

#include "pd_uitl.h"
#include "gara.h"
#include "log.h"

static PlaydateAPI* _pd;
static LCDBitmap *_garaImageOriginal = NULL;
static LCDBitmap *_garaImage = NULL;
static LCDSprite *_garaSprite = NULL;

static LCDBitmap *_image_base = NULL;

static float _prevRot = 0.0f;
static float _rotSpeed = 0.0f;
static int _isBallIn = 0;
static BallSpawnHandler _handler = NULL;

void initGara(PlaydateAPI* pd)
{
    _pd = pd;

    _garaImageOriginal = loadImageAtPath(pd, "images/garagara.png");
    {
        _garaSprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(_garaSprite, _garaImageOriginal, kBitmapUnflipped);
        _pd->sprite->setZIndex(_garaSprite, 800);
        _pd->sprite->addSprite(_garaSprite);
        _pd->sprite->moveTo(_garaSprite, 200, 120);
    }

    _image_base = loadImageAtPath(pd, "images/gara-base.png");
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _image_base, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 850);
        _pd->sprite->addSprite(sprite);
        _pd->sprite->moveTo(sprite, 200, 175);
    }
}

void updateGara(float garaRotDeg)
{
    if (_garaImage != NULL) {
        _pd->graphics->freeBitmap(_garaImage);
        _garaImage = NULL;
    }

    int allocSize;
    _garaImage = _pd->graphics->rotatedBitmap(_garaImageOriginal,
                                              garaRotDeg, 1.0f, 1.0f, &allocSize);
    _pd->sprite->setImage(_garaSprite, _garaImage, kBitmapUnflipped);

    if (garaRotDeg >= _prevRot) {
        _rotSpeed = garaRotDeg - _prevRot;
    }
    else {
       _rotSpeed = garaRotDeg - (_prevRot - 360.0f);
    }

    if (garaRotDeg >= 45.0f && _prevRot < 45.0f) {
        if (_rotSpeed < 10.0f) {
            _isBallIn = 1;
            LOG("IN");
        }
    }

    if (garaRotDeg >= 340.0f && _prevRot < 340.0f) {
        if (_rotSpeed < 10.0f && _isBallIn) {
            _isBallIn = 0;
            LOG("SPAWN");
            if (_handler) { _handler(); }
        }
    }

    _prevRot = garaRotDeg;
}

void registerBallSpawn(BallSpawnHandler handler)
{
    _handler = handler;
}
