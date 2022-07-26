//
// Created by 東口拓也 on 2022/07/23.
//

#include "pd_uitl.h"

#include "gara.h"
#include "math_util.h"

static PlaydateAPI* _pd;
static LCDBitmap *_image = NULL;
static LCDBitmap *_image_base = NULL;

void initGara(PlaydateAPI* pd)
{
    _pd = pd;

    _image = loadImageAtPath(pd, "images/garagara.png");
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _image, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 800);
        //_pd->sprite->addSprite(sprite);
        //_pd->sprite->moveTo(sprite, 200, 120);
    }

    _image_base = loadImageAtPath(pd, "images/gara-base.png");
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->sprite->setImage(sprite, _image_base, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 850);
        //_pd->sprite->addSprite(sprite);
        //_pd->sprite->moveTo(sprite, 200, 180);
    }
}

void updateGara(float garaRotDeg)
{
    _pd->graphics->drawRotatedBitmap(_image, 200, 120,
                                     garaRotDeg, 0.5f, 0.5f, 1.0f, 1.0f);

    _pd->graphics->drawBitmap(_image_base, 125, 103, kBitmapUnflipped);
}

