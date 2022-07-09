//
// Created by 東口拓也 on 2022/07/09.
//
#include "name_drawer.h"
#include "log.h"
#include "pd_uitl.h"

static PlaydateAPI* _pd;

static LCDBitmap *_ballImage = NULL;
static LCDSprite *_sprites[8] = {NULL};

void initName(PlaydateAPI* pd)
{
    _pd = pd;

    _ballImage = loadImageAtPath(pd, "images/33.png");

    LCDSprite *sprite = _pd->sprite->newSprite();
    _pd->sprite->setImage(sprite, _ballImage, kBitmapUnflipped);
    _pd->sprite->setZIndex(sprite, 999);

    _sprites[0] = sprite;
    _pd->sprite->addSprite(_sprites[0]);
}

void updateName(void)
{
    _pd->sprite->moveTo(_sprites[0], 0.0f, 120.0f);
}
