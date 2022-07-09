//
// Created by 東口拓也 on 2022/07/09.
//

#include "pd_uitl.h"

LCDBitmap *loadImageAtPath(PlaydateAPI* pd, const char *path)
{
    const char *outErr = NULL;
    LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
    if ( outErr != NULL ) {
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}

LCDFont *loadFontAtPath(PlaydateAPI* pd, const char *path)
{
    const char *outErr = NULL;
    LCDFont *font = pd->graphics->loadFont(path, &outErr);
    if ( outErr != NULL ) {
        pd->system->logToConsole("Error loading font at path '%s': %s", path, outErr);
    }
    return font;
}

