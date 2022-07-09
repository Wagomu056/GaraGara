
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "log.h"
#include "cutin_drawer.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static PlaydateAPI* _pd;

int update(void* ud)
{
    PDButtons pushed;
    _pd->system->getButtonState(NULL, &pushed, NULL);
    if ( pushed & kButtonA )
    {
        startCutin();
    }

    _pd->graphics->clear(kColorWhite);
    _pd->sprite->updateAndDrawSprites();
    updateCutin();
    return 1;
}

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        _pd = pd;
        LOG("init");
        initCutin(pd);
        pd->system->setUpdateCallback(update, NULL);
    }

    return 0;
}