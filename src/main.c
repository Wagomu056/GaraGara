
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "log.h"
#include "cutin_drawer.h"
#include "lottery.h"

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
        const char *name = lottery();
        if (strcmp(name, "") != 0) {
            startCutin(name);
        }
    }

    _pd->graphics->clear(kColorWhite);
    updateCutin();

    _pd->sprite->drawSprites();

    return 1;
}

void cutinEnd(void)
{
    LOG("Cut in end.");
}

static void initialize()
{
    initCutin(_pd);
    registerCutinEnd(&cutinEnd);

    registerLottery("AZUMA");
    registerLottery("AOKI");
    registerLottery("TATSUYA");
    registerLottery("MIURA");
    registerLottery("ITO");
    registerLottery("KAMIHAMA");
    registerLottery("YOSHIDA");
    registerLottery("KAKI");
}

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        _pd = pd;
        pd->system->setUpdateCallback(update, NULL);

        initialize();
    }

    return 0;
}