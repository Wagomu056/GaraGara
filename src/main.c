
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "log.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static PlaydateAPI* _pd;

int update(void* ud)
{
    _pd->sprite->updateAndDrawSprites();
    return 1;
}

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        _pd = pd;
        LOG("init");
        pd->system->setUpdateCallback(update, NULL);
    }

    return 0;
}