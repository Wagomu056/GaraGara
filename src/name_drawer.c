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

static const int CHAR_PADDING = 2;
static const int CHAR_NUM = 8;

static int NAME_START_PADDING = 20;

static int isDrawing = 0;

struct NameChar
{
    LCDSprite *sprite;
    int width;
};
static struct NameChar _nameChars[CHAR_NUM] = {0};

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

void clearName(void)
{
    if (!isDrawing)
        return;

    isDrawing = 0;

    for(int i = 0; i < CHAR_NUM; i++) {
        LCDSprite *sprite = _nameChars[i].sprite;
        if (sprite) {
            _pd->sprite->removeSprite(sprite);
        }

        _nameChars[i].sprite = NULL;
        _nameChars[i].width = 0;
    }
}

void startName(const char *name, int count)
{
    clearName();

    isDrawing = 1;

    const int cnt = (count <= CHAR_NUM) ? count : CHAR_NUM;
    for (int i = 0; i < cnt; i++)
    {
        if (name[i] == '\0') break;

        LCDBitmap *bitmap = findBitmap(name[i]);
        _nameChars[i].sprite = createSprite(_pd, bitmap);
        _pd->graphics->getBitmapData(bitmap, &(_nameChars[i].width),
                                     NULL, NULL, NULL, NULL);
        _pd->sprite->addSprite(_nameChars[i].sprite);
    }
}

void updateName(LCDRect* drawRect)
{
    if (_nameChars[0].sprite == NULL)
        return;

    int currentWidth = NAME_START_PADDING;
    for (int i = 0; i < CHAR_NUM; i++)
    {
        LCDSprite *sprite = _nameChars[i].sprite;
        if (sprite == NULL) break;

        const int width = _nameChars[i].width / 2;
        currentWidth += width;
        _pd->sprite->moveTo(sprite, currentWidth, 120.0f);

        if (drawRect) {
            _pd->sprite->setClipRect(sprite, *drawRect);
        }

        currentWidth += width + CHAR_PADDING;
    }
}
