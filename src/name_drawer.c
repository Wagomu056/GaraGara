//
// Created by 東口拓也 on 2022/07/09.
//
#include <stdio.h>
#include "name_drawer.h"
#include "log.h"
#include "pd_uitl.h"
#include "math_util.h"

static PlaydateAPI* _pd;

static const int ALPHABET_NUM = 26;
static LCDBitmap *_images[ALPHABET_NUM] = {NULL};

static const int SPRITE_NUM = 8;
static LCDSprite *_sprites[SPRITE_NUM] = {NULL};

LCDBitmap* findBitmap(char c)
{
    int cIdx = (int)c - 65;
    cIdx = clampI(cIdx, 0, ALPHABET_NUM - 1);
    LOG("%c:%d", c, cIdx);

    return _images[cIdx];
}

LCDSprite* createSprite(PlaydateAPI* pd, LCDBitmap* bitmap)
{
    LCDSprite *sprite = pd->sprite->newSprite();
    pd->sprite->setImage(sprite, bitmap, kBitmapUnflipped);
    pd->sprite->setZIndex(sprite, 999);
    return sprite;
}

void initName(PlaydateAPI* pd)
{
    _pd = pd;

    char pathTmp[16];
    static const int A_FILE_NUMBER = 33;
    for (int i = 0; i < ALPHABET_NUM; i++) {
        snprintf(pathTmp, sizeof(pathTmp), "font/%d.png", A_FILE_NUMBER + i);
        _images[i] = loadImageAtPath(_pd, pathTmp);
    }
}

static void clearSprites()
{
    for(int i = 0; i < SPRITE_NUM; i++) {
        _sprites[i] = NULL;
    }
}

void startName(const char *name, int count)
{
    clearSprites();

    const int cnt = (count <= SPRITE_NUM) ? count : SPRITE_NUM;
    for (int i = 0; i < cnt; i++)
    {
        if (name[i] == '\0') break;

        LCDBitmap *bitmap = findBitmap(name[i]);
        _sprites[i] = createSprite(_pd, bitmap);
        _pd->sprite->addSprite(_sprites[i]);
    }
}

static const int CHAR_WIDTH = 48;
void updateName(void)
{
    for (int i = 0; i < SPRITE_NUM; i++)
    {
        if (_sprites[i] == NULL) break;

        const int x = (CHAR_WIDTH / 2) + (CHAR_WIDTH * i);
        _pd->sprite->moveTo(_sprites[i], x, 120.0f);
    }
}
